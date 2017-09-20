

#pragma once


#include "emotient.hpp"
#include <opencv2/opencv.hpp>

//#define Facet_Dir   "C:\\facets"   //for Sheen's PC
#define Facet_Dir   "c:\\Emotient\\sdk\\facets"    //for Lab Win 7 Server

class FrameProcess{
private:
	EMOTIENT::FacetSDK::FrameAnalyzer m_frameAnalyzer;
	EMOTIENT::FacetSDK::FrameAnalysis m_frameAnalysis;
	EMOTIENT::FacetSDK::Face m_largestFace;
	std::string m_facetsDir; //facetSDK License and Config file Dir

public:
	FrameProcess();
	~FrameProcess();

	void analyzeFrame(cv::Mat& grayFrame);
	void baseline();
	EMOTIENT::FacetSDK::Face getLargestFace();
	void setFacetsDir(std::string dirPath);


};



