
#include "stdafx.h"
#include "FrameProcess.h"
#include "License.c"


FrameProcess::FrameProcess(){

	m_facetsDir = Facet_Dir;
		
#ifdef _WIN32
	// Necessary only with Windows; call before any other FACET call
	EMOTIENT::FacetSDK::InitializeLicensing(FACET);
#endif
	
	int retVal;
	retVal = m_frameAnalyzer.Initialize(m_facetsDir.c_str(), "FrameAnalyzerConfig.json");
	if (retVal != EMOTIENT::FacetSDK::SUCCESS) {
		std::cout << std::endl;
		std::cout << "========================================================" << std::endl;
		std::cout << "Could not initialize the EMOTIENT::FacetSDK::FrameAnalyzer" << std::endl;
		std::cout << "Check that Facet_Dir is pointing to the correct location relative to the working directory." << std::endl;
		std::cout << "Error code = " << EMOTIENT::FacetSDK::DefineErrorCode(retVal) << std::endl;
		std::cout << "Input any key to exit." << std::endl;
		std::cin.ignore(2);
		exit(retVal);
		
	}

}


FrameProcess::~FrameProcess(){

}

void FrameProcess::analyzeFrame(cv::Mat& grayFrame){
	if (grayFrame.empty())  return;
	m_frameAnalyzer.Analyze(grayFrame.data, grayFrame.rows, grayFrame.cols, m_frameAnalysis);
	if (m_frameAnalysis.NumFaces() > 0){
		m_frameAnalysis.LargestFace(m_largestFace);
	}

}

void FrameProcess::baseline(){}

EMOTIENT::FacetSDK::Face   FrameProcess::getLargestFace(){
	return m_largestFace;
}

//set the dir of Facets license and Config file, for upgrade 
void FrameProcess::setFacetsDir(std::string dirPath){
	m_facetsDir = dirPath;

}

