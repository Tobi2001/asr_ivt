// *****************************************************************
// Filename:  TexturedObjectDatabase.h
// Copyright: Pedram Azad, Chair Prof. Dillmann (IAIM),
//            Institute for Computer Science and Engineering (CSE),
//            University of Karlsruhe. All rights reserved.
// Author:    Pedram Azad
// Date:      2006
// *****************************************************************


#ifndef _TEXTURED_OBJECT_DATABASE_H_
#define _TEXTURED_OBJECT_DATABASE_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include "Features/FeatureEntry.h"
#include "DataStructures/DynamicArray.h"
#include "Structs/ObjectDefinitions.h"
#include <string>


// *****************************************************************
// define
// *****************************************************************

#define MAXIMUM_NUMBER_OF_CLASSES 50


// *****************************************************************
// forward declarations
// *****************************************************************

class CDynamicArray;
class CByteImage;
class CTexturedFeatureSet;
class CHoughSpace2D;
class CStereoMatcher;
class CStereoCalibration;
class CKdTree;
struct Object3DEntry;




// *****************************************************************
// CTexturedObjectDatabase
// *****************************************************************

class CTexturedObjectDatabase
{
public:
	// constructor
	CTexturedObjectDatabase(int nImageWidth, int nImageHeight);

	// destructor
	~CTexturedObjectDatabase();

	
	// public methods
	
	// loads stereo calibration from file (optional; needed for 3d localization only)
	bool LoadCameraParameters(const char *pFileName);
	void InitCameraParameters(CStereoCalibration *pStereoCalibration, bool bCloneCalibration);
	
	// loads database from configuration file
	bool LoadDatabase(const char *pConfigurationFilename, const char* pDataFilePathPrefix = 0);
	
	// set thresholds
	void SetRecognitionThresholds(int nMinValidFeatures, float fMaxError);
	
	// add feature set to database
	bool AddFeatureSet(CTexturedFeatureSet *pFeatureSet);
	bool AddClass(const std::string& sClassName, const std::string& sFeatureSetFileName);
    
	// remove feature set from database
	bool RemoveFeatureSet(int nIndex);
	bool RemoveFeatureSet(const char *pName);
		
	// high level method for analyzing features in a scene
	int AnalyzeFeatures(CDynamicArray *pFeatures, CByteImage *pResultImage,
		const CByteImage * const *ppInputImagesFor3DLocalization = 0,
		const Vec2d *pInterestPoints = 0, int nInterestPoints = 0,
		int nUseKdTree = 0, bool bInputImagesAreUndistorted = false,
		const char *pObjectName = 0);
	
	// returns feature set for a given index
	const CTexturedFeatureSet* GetFeatureSet(int nIndex);
	
	// returns number of objects in database
	int GetSize();

	
	// set methods
	void SetVerbose(bool bVerbose);
	void SetStereo(bool bStereo) { m_bLocalizeWithStereo = bStereo; }

	void SetCorrelationParameters(int nWindowSize, float fMinZ, float fMaxZ, float fThreshold)
	{
		m_nCorrelationWindowSize = nWindowSize;
		m_fCorrelationMinZ = fMinZ;
		m_fCorrelationMaxZ = fMaxZ;
		m_fCorrelationThreshold = fThreshold;
	}


private:
	// private class definitions
	class CFeatureMapEntry : public CDynamicArrayElement
	{
	public:
		CFeatureMapEntry(const CFeatureEntry *pFeature_, const CFeatureEntry *pMatchedFeature_, const CTexturedFeatureSet *pFeatureSet_) :
			pFeature(pFeature_), pMatchedFeature(pMatchedFeature_), pFeatureSet(pFeatureSet_)
		{
		}
		
		const CFeatureEntry *pFeature;
		const CFeatureEntry *pMatchedFeature;
		const CTexturedFeatureSet *pFeatureSet;
	};
	
	// private methods
	bool BuildKdTree(int nObjectIndex);
	bool Localize3D(const Vec2d &p1, const Vec2d &p2, const Vec2d &p3, const Vec2d &p4,
		const Vec3d &p1_3d, const Vec3d &p2_3d, const Vec3d &p3_3d, const Vec3d &p4_3d,
		const Vec2d *pFeatures, int nFeatures, const CByteImage * const *ppImages,
		CByteImage *pResultImage, Object3DEntry &entry, bool bInputImagesAreUndistorted);	
	
	// private attributes
	CDynamicArray *m_pObjectArray;
	CDynamicArray **m_ppObjectFeatureMap;
	CKdTree **m_ppKdTrees;
	CHoughSpace2D *m_pHoughSpace;
	
	int m_nImageWidth;
	int m_nImageHeight;
	
	CStereoMatcher *m_pStereoMatcher;
	CStereoCalibration *m_pStereoCalibration;
	bool m_bStereoInitialized;
	bool m_bOwnStereoCalibrationObject;
	
	bool m_bVerbose;

	int m_nCorrelationWindowSize;
	float m_fCorrelationMinZ;
	float m_fCorrelationMaxZ;
	float m_fCorrelationThreshold;

	bool m_bLocalizeWithStereo;

	
public:
	Object3DList m_objectList;
};



#endif /* _OBJECT_DATABASE_H_ */
