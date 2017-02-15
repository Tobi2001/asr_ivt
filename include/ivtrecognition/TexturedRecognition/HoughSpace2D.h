// *****************************************************************
// Filename:  HoughSpace2D.h
// Copyright: Pedram Azad, Chair Prof. Dillmann (IAIM),
//            Institute for Computer Science and Engineering (CSE),
//            University of Karlsruhe. All rights reserved.
// Author:    Pedram Azad
// Date:      2005
// *****************************************************************


#ifndef _HOUGH_SPACE_2D_H_
#define _HOUGH_SPACE_2D_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include "DataStructures/DynamicArray.h"


// *****************************************************************
// define
// *****************************************************************



// *****************************************************************
// forward declarations
// *****************************************************************

class CFeatureEntry;
class CByteImage;
struct Mat3d;
struct Vec2d;



// *****************************************************************
// CFeatureSet
// *****************************************************************

class CHoughSpace2D
{
public:
	// constructor
	CHoughSpace2D(int nImageWidth, int nImageHeight, float fScale);

	// CFeatureSet
	~CHoughSpace2D();

	
	// public methods
	void InitNextRun();
	void Vote(const CFeatureEntry *pFeature, const CFeatureEntry *pMatchedFeature, const Vec2d &center);
	bool CheckAndDetermineHomography(Mat3d &A, Vec2d &centroid, int &nResultMatches, float &fResultError, CByteImage *pResultImage = 0);
	
	void SetRecognitionThresholds(int nMinValidFeatures, float fMaxError);
	
	void WriteHoughSpaceImage();
	
	const Vec2d* GetValidFeatures() { return m_pValidFeatures; }
	const Vec2d* GetMatchedFeatures() { return m_pMatchedFeatures; }
	int GetNumberOfValidFeatures() { return m_nValidFeatures; }
	
	void SetVerbose(bool bVerbose) { m_bVerbose = bVerbose; }
	
	
private:
	// private class definitions
	class CHoughSpace2DBin
	{
	public:
		CHoughSpace2DBin()
		{
			nID = 0;
			nHits = 0;
		}
		
		int nID;
		unsigned short nHits;
	};
	
	class CFeaturePair : public CDynamicArrayElement
	{
	public:
		CFeaturePair(const CFeatureEntry *pFeature_, const CFeatureEntry *pMatchedFeature_) : pFeature(pFeature_), pMatchedFeature(pMatchedFeature_)
		{
		}
		
		const CFeatureEntry *pFeature;
		const CFeatureEntry *pMatchedFeature;
		int offsets[6];
	};

	// private attributes
	CHoughSpace2DBin **m_ppHoughSpace;
	int m_nWidth;
	int m_nHeight;
	float m_fScale;
	int m_nCurrentID;
	int m_nMaxHits;
	int m_nBestOffset;
	float m_fBestScale;
	
	CDynamicArray *m_pPairList;
	
	Vec2d *m_pValidFeatures;
	Vec2d *m_pMatchedFeatures;
	int m_nValidFeatures;
	
	int m_nMinValidFeatures;
	float m_fMaxError;
	
	bool m_bVerbose;
};



#endif /* _HOUGH_SPACE_2D_H_ */
