// *****************************************************************
// Filename:  ViewDatabase.h
// Copyright: Pedram Azad, Chair Prof. Dillmann (IAIM),
//            Institute for Computer Science and Engineering (CSE),
//            University of Karlsruhe. All rights reserved.
// Author:	  Pedram Azad
// Date:      2005
// *****************************************************************


#ifndef _VIEW_DATABASE_H_
#define _VIEW_DATABASE_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include <string>
#include "DatabaseEntry.h"


// *****************************************************************
// forward class declarations
// *****************************************************************

class CFloatMatrix;
class CByteImage;
struct MyRegion;
struct Transformation3d;
struct Vec3d;



// *****************************************************************
// CViewDatabase
// *****************************************************************

class CViewDatabase
{
public:
	// constructor
	CViewDatabase();
	
	// destructor
	~CViewDatabase();
	
	
	// public methods
	
	// for recognition
	bool Init(const char *pConfigurationFilename);
	bool InitRecognition();
	bool LearnTrainingData();
	int FindBestMatch(const CFloatMatrix *pInputData, float &error);
	bool GetView(int nGlobalIndex, int &nResultClass, int &nResultView);
	bool GetPose(int nClass, int nView, Transformation3d &poseData);
	
	// helpers
	static int GetNumberOfSamples(const char *pFileName, int &nInputDimension);
	static bool ReadData(const char *pFileName, float *pData, int nExpectedDimension);
	static void Normalize(const CByteImage *pInputImage, CByteImage *pOutputImage, const MyRegion &region);
	static void NormalizeIntensity(float *pData, int nLength);
	
	// member access
	int GetNumberOfClasses() { return m_nClasses; }
	int GetInputDimension() { return m_nInputDimension; }
	int GetTargetDimension() { return m_nTargetDimension; }
	int GetTotalNumberOfSamples() { return m_nTotalSamples; }
	const CDatabaseEntry* GetDatabaseEntry(int nIndex);



private:
	// private methods
	void DeleteMatrices();
	void DeleteDatabase();
	bool ReadConfigurationFile(const char *pConfigurationFilename);
	bool WriteConfigurationFile(const char *pConfigurationFilename);
	
	
	// private attributes
	std::string m_sFullTransformationMatrixFilename;
	std::string m_sEigenvalueMatrixFilename;
	std::string m_sTransformationMatrixFilename;
	std::string m_sTrainingDataFilename;
	
	int m_nClasses;
	int m_nInputDimension;
	int m_nTargetDimension;
	int m_nTotalSamples;
	
	std::string m_sConfigurationFilename;
	
	CFloatMatrix *m_pTransformationMatrix;
	CFloatMatrix *m_pTrainedData;
	
	CDatabaseEntry **m_ppDatabaseEntries;
	
	bool m_bWriteConfigurationFile;
};



#endif /* _VIEW_DATABASE_H_ */
