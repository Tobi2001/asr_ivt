// *****************************************************************
// Filename:  ViewDatabase2.h
// Copyright: Pedram Azad, Chair Prof. Dillmann (IAIM),
//            Institute for Computer Science and Engineering (CSE),
//            University of Karlsruhe. All rights reserved.
// Author:	  Pedram Azad
// Date:      04.12.2007
// *****************************************************************


#ifndef _VIEW_DATABASE2_H_
#define _VIEW_DATABASE2_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include <string>
#include "DatabaseEntry.h"
#include "DataStructures/DynamicArray.h"


// *****************************************************************
// forward class declarations
// *****************************************************************

class CFloatMatrix;
class CByteImage;
struct MyRegion;
struct Vec3d;



// *****************************************************************
// CViewDatabase2
// *****************************************************************

class CViewDatabase2 : public CDynamicArrayElement
{
public:
	// constructor
	CViewDatabase2();
	
	// destructor
	~CViewDatabase2();
	
	
	// public methods
	
	// for recognition
	bool Init(const char *pBasePath, const char* pPathPrefix = 0, std::string overrideClassName = "");
	bool InitRecognition();
	bool LearnTrainingData();
	int FindBestMatch(const CFloatMatrix *pInputData, float &error) const;
	bool GetView(int nGlobalIndex, int &nResultClass, int &nResultView);
	bool GetPose(int nView, Transformation3d &pose);
	
	// helpers
	static int GetNumberOfSamples(const char *pFileName, int &nInputDimension);
	static bool ReadData(const char *pFileName, float *pData, int nExpectedDimension);
	static void Normalize(const CByteImage *pInputImage, CByteImage *pOutputImage, const MyRegion &region);
	static void NormalizeIntensity(float *pData, int nLength);
	
	// member access
	int GetInputDimension() { return m_nInputDimension; }
	int GetTargetDimension() { return m_nTargetDimension; }
	int GetNumberOfSamples() { return m_nSamples; }
	const CDatabaseEntry* GetDatabaseEntry() const { return m_pDatabaseEntry; }



private:
	// private methods
	void DeleteMatrices();
	bool ReadConfigurationFile(const char *pBasePath);
	bool WriteConfigurationFile(const char *pConfigurationFilename);
	
	
	// private attributes
	std::string m_sFullTransformationMatrixFilename;
	std::string m_sEigenvalueMatrixFilename;
	std::string m_sTransformationMatrixFilename;
	std::string m_sTrainingDataFilename;
	
	int m_nInputDimension;
	int m_nTargetDimension;
	int m_nSamples;
	
	std::string m_sConfigurationFilename;
	
	CFloatMatrix *m_pTransformationMatrix;
	CFloatMatrix *m_pTrainedData;
	
	CDatabaseEntry *m_pDatabaseEntry;
};



#endif /* _VIEW_DATABASE2_H_ */
