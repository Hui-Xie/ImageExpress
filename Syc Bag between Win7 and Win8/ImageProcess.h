

#pragma once

#include <vector>
#include <opencv2/opencv.hpp>
#include "FaceContainer.h"


class ImageProcess{
private:
	std::string m_dir;
	std::string m_fileName;
	std::vector < std::string > m_vectorFileFullPathName;  
	FrameProperty m_frameProperty;
	cv::Mat m_grayMatFrame;
	std::string m_imageExtNameList;
	std::vector <std::string> m_vectorFileUnopened;
	

public:
	ImageProcess();
	~ImageProcess();

	bool isQuit(std::string str);
	bool isImageExtName(const std::string& fileName);
	void setImageFileVector();
	int inputImagesSource();

	std::vector < std::string >& getImageFileVector();
	
	cv::Mat& getGrayImageAndFrameProperty(std::string fileFullPath);
	FrameProperty getFrameProperty();
	void setImagesDir(std::string dir);
	std::string getImagesDir();
	void deleteFileUnopened(int index);
	void printFileUnopend();

};