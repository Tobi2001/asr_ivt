// *****************************************************************
// -----------------------------------------------------------------
// SegmentableRecognition.h 
// -----------------------------------------------------------------
// *****************************************************************

// *****************************************************************
// Author:  Pedram Azad
// Date:    2006/02/23
// *****************************************************************


// *****************************************************************
// double-include protection
// *****************************************************************

#ifndef _SEGMENTABLE_RECOGNITION_H_
#define _SEGMENTABLE_RECOGNITION_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include "Structs/ObjectDefinitions.h"


// *****************************************************************
// forwards
// *****************************************************************

class CObjectFinder;
class CObjectFinderStereo;
class CStereoCalibration;
class CRegionFilterInterface;
class CByteImage;
class CSegmentableDatabase;
class CColorParameterSet;




class CSegmentableRecognition
{
public:
	// constructor
	CSegmentableRecognition();
	
	// destructor
	~CSegmentableRecognition();
	

    /**
     * Init the segmentable recognition.
     * 
     * @param pColorParameterFile relative or absolute path to colors file
     * @param pCameraParameterFileDeprecated leave empty
     * @param pCameraParameterFile relative or absolute path to calibration file
     * @param pObjectDatabaseConfigurationFile relative or absolute path to configuration file for segmentable recognition
     * @param pDataPathPrefix prefix added to all paths in the database configuration file. Allows to keep database file and object data in separate paths.
     * 
     */
	bool Init(const char *pColorParameterFile, const char *pCameraParameterFileDeprecated, const char *pCameraParameterFile,
			  const char *pObjectDatabaseConfigurationFile, const char* pDataPathPrefix = 0);

    /**
     * Init the segmentable recognition.
     * 
     * @param pColorParameterSet color parameter set
     * @param pStereoCalibration stereo calibration
     * @param pObjectDatabaseConfigurationFile relative or absolute path to configuration file for segmentable recognition
     * 
     */
    bool Init(CColorParameterSet* pColorParameterSet, CStereoCalibration* pStereoCalibration, const char *pObjectDatabaseConfigurationFile);

    /**
     * Init the segmentable recognition without reading database. Use this initialization if classes are to be added later with AddClass()
     * 
     * @param pColorParameterSet color parameter set
     * @param pStereoCalibration stereo calibration
     * 
     */
    bool InitWithoutDatabase(CColorParameterSet* pColorParameterSet, CStereoCalibration* pStereoCalibration);
    
    /**
     * Adds a object class to segmentablerecognition which is loaded from the given classPath
     * 
     * @param classPath path to data files for sementable objects
     * 
     */
    bool AddClass(const std::string& classPath);

    /**
     * Override stereo calibration as set in Init.
     * 
     * @param pStereoCalibration a stereo calibration pointer
     */
	void SetStereoCalibration(CStereoCalibration *pStereoCalibration);

    /**
     * Override default recognition thresholds
     * @param fSizeRatioThreshold size ratio between original and detected object (defaults to 0.8)
     * @param fCorrelationThreshold minimum correlation between segmented mask and rendered model (defaults to 0.85)
     */
	void SetRecognitionThresholds(float fSizeRatioThreshold, float fCorrelationThreshold);
	
    /**
     * Perform recognition for all objects in the database
     *
     * @param ppInputImages left and right RGB images in the correct size
     * @param ppResultImages visualization images can be NULL
     * @param nMinPixelsPerRegion minimum number of pixels to accept region
     * @param bBlobsOnly only detect blobs, do not perform recognition and localization
     * @param fMaxEpipolarDistance maximum distance to epipolar line in order to accept match
     * @param color objects of which color (eNone means all colors: eRed, eRed2, eBlue, eBlue2, eGreen, eGreen2)
     * @param bTrack track objects over successive frames
     * @param bInputImagesAreUndistorted whether input images have been undistorted
     */
	void DoRecognition(const CByteImage * const *ppInputImages, CByteImage **ppResultImages,
		int nMinPixelsPerRegion, bool bBlobsOnly = false, float fMaxEpipolarDistance = 10,
		ObjectColor color = eNone, bool bTrack = false, bool bInputImagesAreUndistorted = false);
		
    /**
     * Perform recognition for a single object
     *
     * @param ppInputImages left and right RGB images in the correct size
     * @param ppResultImages visualization images can be NULL
     * @param pObjectName name of the object to recognize
     * @param nMinPixelsPerRegion minimum number of pixels to accept region
     * @param bBlobsOnly only detect blobs, do not perform recognition and localization
     * @param fMaxEpipolarDistance maximum distance to epipolar line in order to accept match
     * @param color objects of which color (eNone means all colors: eRed, eRed2, eBlue, eBlue2, eGreen, eGreen2)
     * @param bTrack track objects over successive frames
     * @param bInputImagesAreUndistorted whether input images have been undistorted
     */
	void DoRecognitionSingleObject(const CByteImage * const *ppInputImages, CByteImage **ppResultImages, const char *pObjectName,
		int nMinPixelsPerRegion, float fMaxEpipolarDistance = 10,
		ObjectColor color = eNone, bool bTrack = false, bool bInputImagesAreUndistorted = false);
	
    /**
     * Retrieve objects recognized in the last recognition step
     *
     * @return list of Object3DEntry containing recognized objects
     */
	const Object3DList& GetObject3DList() { return m_object3DList; }

    /**
     * Retrieve current stereo calibration
     *
     * @return pointer to stereo calibration
     */
	const CStereoCalibration* GetStereoCalibration();

    /**
     * Retrieve current color parameter set
     *
     * @return pointer to color parameter set
     */
	const CColorParameterSet* GetColorParameterSet() { return m_pColorParameterSet; }
	
    /**
     * Retrieve pointer to object database
     *
     * @return pointer to object database
     */
	CSegmentableDatabase* GetObjectDatabase() { return m_pSegmentableDatabase; }

    /**
     * Enable verbose mode
     *
     * @param bVerbose make segmentable recognition verbose
     */
	void SetVerbose(bool bVerbose);
	
	
private:
	// private methods
	void _DoRecognition(const CByteImage * const *ppInputImages, CByteImage **ppResultImages, const char *pObjectName = 0,
		int nMinPixelsPerRegion = 500, bool bBlobsOnly = false, float fMaxEpipolarDistance = 10,
		ObjectColor color = eNone, bool bTrack = false, bool bInputImagesAreUndistorted = false);
	void FindAndClassifyBlobs(CObjectFinderStereo *pObjectFinderStereo, const CByteImage * const *ppInputImages,
			CByteImage **pResultImages, CByteImage *pGrayImage, const char *pObjectName, ObjectColor color,
			int nMinPixelsPerRegion, bool bBlobsOnly, float fMaxEpipolarDistance, bool bInputImagesAreUndistorted);
	bool RecognizeAndLocalizeObject(CByteImage *pGrayImage, Object3DEntry &entry, const char *pObjectName);
	void PostProcessResultList();
	
	// public attributes
	CRegionFilterInterface *m_pCompactRegionFilter;
	
	CObjectFinderStereo *m_pObjectFinderStereo;
	
	CSegmentableDatabase *m_pSegmentableDatabase;
	
	CByteImage *m_pGrayImageBig;
	CByteImage *m_pGrayImageSmall;
	
	CColorParameterSet *m_pColorParameterSet;
	
	Object3DList m_object3DList;
	
	bool m_bVerbose;
};



#endif /* _SEGMENTABLE_RECOGNITION_H_ */
