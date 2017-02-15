// ****************************************************************************
// Filename:  FeatureEntry.h
// Author:    Pedram Azad
// Date:      2005
// ****************************************************************************


#ifndef _TEXTURED_FEATURE_SET_H_
#define _TEXTURED_FEATURE_SET_H_


// ****************************************************************************
// Necessary includes
// ****************************************************************************

#include "Features/FeatureEntry.h"
#include "Math/Math2d.h"
#include "Math/Math3d.h"
#include <string>


// ****************************************************************************
// Forward declarations
// ****************************************************************************

class CDynamicArray;
class CByteImage;



// ****************************************************************************
// CTexturedFeatureSet
// ****************************************************************************

/*!
	\ingroup FeatureRepresentations
	\brief Data structure for handling of sets of features, represented as instances of CFeatureEntry (resp. subclasses of).
*/
class CTexturedFeatureSet : public CDynamicArrayElement
{
public:
	// constructor
	CTexturedFeatureSet(const char *pName);

	// CTexturedFeatureSet
	~CTexturedFeatureSet();

	
	// public methods
	bool AddFeature(CFeatureEntry *pFeatureEntry, bool bAddUniqueOnly = true);
	const CFeatureEntry* GetFeature(int nIndex) const;
	const CFeatureEntry* FindBestMatch(const CFeatureEntry *pFeature, float &error) const;
	void Clear();
	bool DeleteElement(int nElement);
	int DeleteAllMatches(const CFeatureEntry *pElement);
	void SetCornerPoints(Vec2d &point1, Vec2d &point2, Vec2d &point3, Vec2d &point4);
	void SetCornerPoints3D(Vec3d &point1, Vec3d &point2, Vec3d &point3, Vec3d &point4);
	
	int GetSize() const;
	const char* GetName() const { return m_sName.c_str(); }
	const char* GetModelFilePath() const { return m_sOivFilePath.c_str(); }

	bool SaveToFile(const char *pFileName);
	bool LoadFromFile(const char *pFileName);
	void SetModelFilePath(const char *pFilePath);


private:
	// private attribute
	CDynamicArray *m_pFeatureArray;

	std::string m_sName;
	std::string m_sOivFilePath;
	
public:
	Vec2d m_point1;
	Vec2d m_point2;
	Vec2d m_point3;
	Vec2d m_point4;
	Vec2d m_center;
	
	Vec3d m_3dPoint1;
	Vec3d m_3dPoint2;
	Vec3d m_3dPoint3;
	Vec3d m_3dPoint4;
};



#endif /* _TEXTURED_FEATURE_SET_H_ */
