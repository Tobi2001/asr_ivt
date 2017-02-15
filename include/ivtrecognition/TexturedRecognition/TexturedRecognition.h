// *****************************************************************
// -----------------------------------------------------------------
// TexturedRecognition.h 
// -----------------------------------------------------------------
// *****************************************************************

// *****************************************************************
// Author:  Pedram Azad
// Date:    2006/09/23
// *****************************************************************


// *****************************************************************
// double-include protection
// *****************************************************************

#ifndef _TEXTURED_RECOGNITION_H_
#define _TEXTURED_RECOGNITION_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include "Structs/ObjectDefinitions.h"


// *****************************************************************
// forwards
// *****************************************************************

class CByteImage;
class CTexturedObjectDatabase;
class CHarrisSIFTFeatureCalculator;
class CStereoCalibration;




class CTexturedRecognition
{
public:
	// constructor
    /**
     * Construct CTexturedRecognition
     * 
     * @param nImageWidth width of image
     * @param nImageHeight height of image
     * @param fSIFTThreshold threshold for extracting harris interest points (default is 0.01)
     */	
	CTexturedRecognition(int nImageWidth, int nImageHeight, float fSIFTThreshold = 0);
	
	// destructor
	~CTexturedRecognition();
	

    /**
     * Init textured recognition and load calibration from file
     * 
     * @param pObjectDatabaseFilePath relative or absolute path to configuration file for textured recognition
     * @param pCameraParameterFileName relative or absolute path to camera calibration file
     * @param pDataFilePathPrefix path prefix for entries in configuration file
     */	
    bool Init(const char *pObjectDatabaseFilePath, const char *pCameraParameterFileName = 0, const char* pDataFilePath = 0);

    /**
     * Init textured recognition 
     * 
     * @param pObjectDatabaseFilePath relative or absolute path to configuration file for textured recognition
     * @param pStereoCalibration pointer to stereo calibration
     * @param pDataFilePathPrefix path prefix for entries in configuration file
     */	
	bool Init(const char *pObjectDatabaseFilePath, CStereoCalibration *pStereoCalibration, bool bCloneCalibration, const char* pDataFilePath = 0);
	
    /**
     * Do recognition of all known objects 
     * 
     * @param ppInputImages left and right RGB images in the correct size
     * @param ppResultImages visualization images can be NULL
     * @param bLocalizeWithStereo needs to be true of stereo localization is used @see SetStereo()
     * @param nUseKdTree whether to use KdTree for search (default is 0 - no)
     * @param bInputImagesAreUndistorted whether input images have been undistorted
     */	
	void DoRecognition(const CByteImage * const *ppInputImages, CByteImage **ppResultImages, bool bLocalizeWithStereo = false, int nUseKdTree = 0, bool bInputImagesAreUndistorted = false);

    /**
     * Do recognition of all known objects 
     * 
     * @param ppInputImages left and right RGB images in the correct size
     * @param ppResultImages visualization images can be NULL
     * @param pObjectName name of the object to recognize
     * @param bLocalizeWithStereo needs to be true of stereo localization is used @see SetStereo()
     * @param nUseKdTree whether to use KdTree for search (default is 0 - no)
     * @param bInputImagesAreUndistorted whether input images have been undistorted
     */	
	void DoRecognitionSingleObject(const CByteImage * const *ppInputImages, CByteImage **ppResultImages, const char *pObjectName,
		bool bLocalizeWithStereo = false, int nUseKdTree = 0, bool bInputImagesAreUndistorted = false);
	
    /**
     * Enable verbose mode
     *
     * @param bVerbose make textured recognition verbose
     */
	void SetVerbose(bool bVerbose);

    /**
     * Set stereo localization (default is true). 
     *
     * @param bStereo 3D-3D localization if true - 2D-3D localization if false
     */    
	void SetStereo(bool bStereo);

    /**
     * Set quality threshold for Harris interest point calculation (defaults to 0.01).
     * Smaller means more features.
     *
     * @param fQualityThreshold the quality threshols
     */    
	void SetQualityThreshold(float fQualityThreshold);

    /**
     * Set recognition threshold 
     *
     * @param nMinValidFeatures minimum number of features in Houghspace (default is 10)
     * @param fMaxError maximum error after application of homography on valid features (default is 3.3f)
     */    
	void SetRecognitionThresholds(int nMinValidFeatures, float fMaxError);
	
    /**
     * Retrieve objects recognized in the last recognition step
     *
     * @return list of Object3DEntry containing recognized objects
     */
	const Object3DList& GetObject3DList();
    
    /**
     * Retrieve object database 
     *
     * @return object database
     */    
	CTexturedObjectDatabase* GetObjectDatabase() { return m_pObjectDatabase; }
	
	
private:
	// private methods
	void _DoRecognition(const CByteImage * const *ppInputImages, CByteImage **ppResultImages, const char *pObjectName,
		bool bLocalizeWithStereo, int nUseKdTree, bool bInputImagesAreUndistorted);
	
	// private methods
	CTexturedObjectDatabase *m_pObjectDatabase;
	CHarrisSIFTFeatureCalculator *m_pFeatureCalculator;

	CByteImage *m_ppGrayImages[2];
	
	int m_nImageWidth;
	int m_nImageHeight;
	
	bool m_bVerbose;
};



#endif /* _TEXTURED_RECOGNITION2_H_ */
