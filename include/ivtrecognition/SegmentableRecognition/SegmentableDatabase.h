// *****************************************************************
// Filename:  SegmentableDatabase.h
// Copyright: Pedram Azad, Chair Prof. Dillmann (IAIM),
//            Institute for Computer Science and Engineering (CSE),
//            University of Karlsruhe. All rights reserved.
// Author:	  Pedram Azad
// Date:      03.12.2007
// *****************************************************************


#ifndef _SEGMENTABLE_DATABASE_H_
#define _SEGMENTABLE_DATABASE_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include <string>
#include <map>


// *****************************************************************
// forward class declarations
// *****************************************************************

class CByteImage;
class CFloatMatrix;
class CDynamicArray;
class COpenGLVisualizer;
class CObjectFinderStereo;
class CStereoCalibration;
class CDatabaseEntry;
struct Transformation3d;
struct Mat3d;
struct Vec3d;



// *****************************************************************
// CSegmentableDatabase
// *****************************************************************

class CSegmentableDatabase
{
public:
	// constructor
	CSegmentableDatabase();
	
	// destructor
	~CSegmentableDatabase();
	
	
	// public methods
		
	// for recognition
	bool Init(const char *pConfigurationFilename, const char *pCameraParameterFilename, const char* pViewDataBasePathPrefix = 0);
	bool Init(const char *pConfigurationFilename, CStereoCalibration* pStereoCalibration, const char* pViewDataBasePathPrefix = 0);
    bool Init(CStereoCalibration* pStereoCalibration);
    bool AddClass(const std::string& classPath, const std::string& dataBasePrefix, std::string overrideClassName = "");

	void SetStereoCalibration(CStereoCalibration *pStereoCalibration);
	bool FindBestMatch(const CFloatMatrix *pInputData, const CByteImage *pMask, const Vec3d &initialPosition, int nSize,
		Transformation3d &resultPose, float &fResultError, int &nResultClass, int &nResultView, float &fResultRatio, float &fResultCorrelation,
		const char *pObjectName);
	
	// set recognition thresholds
	void SetRecognitionThresholds(float fSizeRatioThreshold, float fCorrelationThreshold);
	
	// set verbose mode
	void SetVerbose(bool bVerbose) { m_bVerbose = bVerbose; }
	
	// member access
	int GetNumberOfClasses();
	int GetInputDimension() { return m_nInputDimension; }
	const CDatabaseEntry* GetDatabaseEntry(int nClass);

	// pose correction
	bool CalculateCorrectedPosition(const char *pOIVFilePath, const Vec3d &triangulatedPosition, const Mat3d &orientation, const CByteImage *pMask, int nSize,
	Vec3d &correctedPosition, float &fRatio, float &fCorrelation);
	void CalculateCorrectedOrientation(const Vec3d &position, const Mat3d &orientation, Mat3d &resultOrientation);
	
	// static methods
	static bool DrawObjectFromFile(COpenGLVisualizer *pVisualizer, const char *pOIVFilePath, const Transformation3d &pose);
	static void Cleanup(); // call this method at the end of your programm to free memory for static objects


private:
	// private methods
	int SimulateSize(const char *pOIVFilePath, const Transformation3d &pose, CByteImage *pObjectImage);
  	bool InitDatabase(const char *pConfigurationFilename, const char* pViewDataBasePathPrefix = 0);
	
	// private attributes
	CDynamicArray *m_pViewDatabaseList;
	int m_nInputDimension;

	COpenGLVisualizer *m_pOpenGLVisualizer;
	CObjectFinderStereo *m_pObjectFinderStereo;
	
	float m_fSizeRatioThreshold;
	float m_fCorrelationThreshold;
	
	bool m_bVerbose;
};



#endif /* _SEGMENTABLE_DATABASE_H_ */
