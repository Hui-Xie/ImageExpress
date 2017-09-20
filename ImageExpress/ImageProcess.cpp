
#include "stdafx.h"
#include "ImageProcess.h"
#include <string>
#include <iostream>
#include <algorithm>


/*===== File Extention Name List================

Windows bitmaps - *.bmp, *.dib 
JPEG files - *.jpeg, *.jpg, *.jpe 
JPEG 2000 files - *.jp2 
Portable Network Graphics - *.png 
Portable image format - *.pbm, *.pgm, *.ppm 
Sun rasters - *.sr, *.ras 
TIFF files - *.tiff, *.tif 
*/


ImageProcess::ImageProcess(){
	m_imageExtNameList = "..tiff.tif.jpg.jpeg.jpe.jp2.gif.bmp.dib.png.gif.pbm.pgm.ppm.sr.ras..";
	m_dir.clear();
	m_fileName.clear();
	m_vectorFileFullPathName.clear();
	m_vectorFileUnopened.clear();
	//cv::Mat m_grayMatFrame;
	
}

ImageProcess::~ImageProcess(){}

bool ImageProcess::isQuit(std::string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	if (0 == str.compare("quit")) return true;
	else return false;
}

int ImageProcess::inputImagesSource(){
	std::cout << "========================================================" << std::endl;
	std::cout << "=================Images Expression Analysis=============" << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << "Caution: Facets license and config files are in correct dir." << std::endl;
	std::cout << "========================================================" << std::endl;
	std::cout << std::endl;
	std::cout << "You may have 3 kinds of input:" << std::endl;
	std::cout << "   Quit to quit program. e.g. quit" << std::endl;
	std::cout << "   Image filename which will be analyzed. e.g. D2P2B.jpg" << std::endl;
	std::cout << "   A Directory in which all image files will be analyed. e.g. C:\\test\\image"<< std::endl;
	std::cout << "========================================================" << std::endl;
	
	std::string inputString;
	std::cout << "Your input:  ";
	std::getline(std::cin, inputString);
	if (0 == inputString.length()) inputString = ".";
	else if (isQuit(inputString)) return -1;
	
	CFileFind fileFinder;
	BOOL isPathOrFile = fileFinder.FindFile(inputString.c_str(),0);

	while (!isPathOrFile){
		std::cout << "      Wrong input, please check." << std::endl << std::endl;
		std::cout << "Your input again:  ";
		std::getline(std::cin, inputString);
		if (0 == inputString.length()) inputString = ".";
		else if (isQuit(inputString)) {
			     fileFinder.Close();
			     return -1;
	    }
		isPathOrFile = fileFinder.FindFile(inputString.c_str(), 0);
		
	}
	
	fileFinder.FindNextFile();
	m_dir = fileFinder.GetFilePath();//return Full Path File Name or Path
	SetCurrentDirectory(m_dir.c_str());
	bool isDirectory = fileFinder.IsDirectory();
	fileFinder.Close();

	if (!isDirectory){
		m_vectorFileFullPathName.clear();
		m_fileName = m_dir;
		if (isImageExtName(m_fileName)) m_vectorFileFullPathName.push_back(m_fileName);
		
		//extract path from m_dir;
		m_dir = m_dir.substr(0, m_dir.find_last_of("\\"));
    }
	else {
		setImageFileVector();
		m_fileName.clear();
	}
	
	
	std::cout << "Your Files Dir:  "<< m_dir << std::endl;
	int size = m_vectorFileFullPathName.size();
	if (1 == size) {
		std::cout << "Your File Name:  " << m_vectorFileFullPathName.at(0) << std::endl;
	}
	else {
		std::cout << "Your File(s):    " << "There are " << size << " image files in above dir." << std::endl;
	}
	std::cout << "========================================================" << std::endl;
	
	return 1;
}

bool ImageProcess::isImageExtName(const std::string& fullFileName){
	std::string extName = fullFileName.substr(fullFileName.find_last_of(".") + 1);
	std::transform(extName.begin(), extName.end(), extName.begin(), ::tolower);
	std::size_t length = extName.length();
	int extFirstPos = m_imageExtNameList.find(extName, 0);
	const int lengthOfExtList = m_imageExtNameList.length();
	if (length >= 2 && length <= 4 && extFirstPos > 0 && extFirstPos < lengthOfExtList) return true;
	else return false;
}

void ImageProcess::setImageFileVector(){
	
	m_vectorFileFullPathName.clear();
	CFileFind fileFinder;
	BOOL isWorking = fileFinder.FindFile(NULL, 0);
	while (isWorking){
		isWorking = fileFinder.FindNextFile();
		std::string fullPathName = fileFinder.GetFilePath();
		if (isImageExtName(fullPathName)) {
			m_vectorFileFullPathName.push_back(fullPathName);
		}
	}

	fileFinder.Close();
	
}

std::vector < std::string >& ImageProcess::getImageFileVector(){
	return m_vectorFileFullPathName;

}

cv::Mat& ImageProcess::getGrayImageAndFrameProperty(std::string fileFullPath){
	
	m_grayMatFrame.release();

	m_grayMatFrame = cv::imread(fileFullPath, CV_LOAD_IMAGE_GRAYSCALE);

	if (NULL != m_grayMatFrame.data){
		CFileStatus rStatus;
		m_frameProperty.m_frameName = fileFullPath;
		CFile::GetStatus(fileFullPath.c_str(), rStatus);
		m_frameProperty.m_time = rStatus.m_mtime;   //The date and time the file was last modified instead of created.
		m_frameProperty.m_frameNO = 0;   //reserve of video
		m_frameProperty.m_millisecond = 0;  //reserve for video's frame
	}
	return m_grayMatFrame;

}

FrameProperty ImageProcess::getFrameProperty(){

	return m_frameProperty;

}

void ImageProcess::deleteFileUnopened(int index){
	m_vectorFileUnopened.push_back(m_vectorFileFullPathName.at(index));
	m_vectorFileFullPathName.erase(m_vectorFileFullPathName.begin()+index);
}

std::string ImageProcess::getImagesDir(){
	return m_dir;
}

void ImageProcess::printFileUnopend(){
	int num = m_vectorFileUnopened.size();
	if (num > 0){
		std::cout << std::endl;
		std::cout << "********************************************************" << std::endl;
		std::cout << "List of unopend image files:" << std::endl;
		std::cout << std::endl;
		for (int i = 0; i < num; i++){
			std::cout << m_vectorFileUnopened.at(i) << std::endl;
		}
	}

}