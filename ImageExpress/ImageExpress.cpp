// ImageExpress.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FaceContainer.h"
#include "ImageProcess.h"
#include "FrameProcess.h"



int _tmain(int argc, _TCHAR* argv[])
{
	//Blank the head of dos windows
	std::cout << std::endl << std::endl;
	
	ImageProcess imageProcess;
	FaceContainer faceContainer;
	FrameProcess frameProcess;

	//Get Image Files, -1 is quit program;
	if (-1 == imageProcess.inputImagesSource()) return -1;
	int nNumOfImages = imageProcess.getImageFileVector().size();
	
	while (0 == nNumOfImages){
		std::cout << std::endl;
		std::cout << "********************************************************" << std::endl;
		std::cout << "**********The dir you input has no image file.**********" << std::endl;
		std::cout << "********************************************************" << std::endl;
		std::cout << std::endl << std::endl;

		if (-1 == imageProcess.inputImagesSource()) return -1;
		nNumOfImages = imageProcess.getImageFileVector().size();
	}
	
	//Read images and Extract Faces
	std::cout << std::endl;
	std::cout << "Now Read Images and Extract Faces:" << std::endl;
	for (int i = 0; i < nNumOfImages; i++){
		std::string imageName = imageProcess.getImageFileVector().at(i);
		cv::Mat& imageFrame = imageProcess.getGrayImageAndFrameProperty(imageName);
		
		std::cout << ".";

		if (imageFrame.empty()) {
			imageProcess.deleteFileUnopened(i);
			i--;
			nNumOfImages--;
			continue;
		}

		frameProcess.analyzeFrame(imageFrame);
		faceContainer.addFace(frameProcess.getLargestFace());
		faceContainer.addFrameProperty(imageProcess.getFrameProperty());
		
	}
	std::cout << std::endl;
	
	//Analyse Faces and Print Result:
	nNumOfImages = imageProcess.getImageFileVector().size();
	if (nNumOfImages > 0){
		faceContainer.openOutputFile(imageProcess.getImagesDir());
		faceContainer.printCSVHead();
		faceContainer.printAllResult();
		faceContainer.closeOutputFile();
	}
	imageProcess.printFileUnopend();
	
	std::cout << std::endl << "==========================END===========================" << std::endl;
	std::cout << "Press at least 2 keys to quit." << std::endl;
	std::cin.ignore(2);

	return 0;
}

