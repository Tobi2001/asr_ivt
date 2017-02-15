// *****************************************************************
// Filename:  DatabaseEntry.h
// Copyright: Pedram Azad, Chair Prof. Dillmann (IAIM),
//            Institute for Computer Science and Engineering (CSE),
//            University of Karlsruhe. All rights reserved.
// Author:	  Pedram Azad
// Date:      2005
// *****************************************************************


#ifndef _DATABASE_ENTRY_H_
#define _DATABASE_ENTRY_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include <string>
#include "Math/Math3d.h"


// *****************************************************************
// forward class declarations
// *****************************************************************

struct Transformation3d;



// *****************************************************************
// CDatabaseEntry
// *****************************************************************

class CDatabaseEntry
{
public:
	// constructor
	CDatabaseEntry();
	
	// destructor
	~CDatabaseEntry();
	
	
	// public methods
	int GetNumberOfSamples() const { return m_nSamples; }
	void SetNumberOfSamples(int nSamples);
	bool GetPose(int nIndex, Transformation3d &pose) const;
	bool SetPose(int nIndex, const Transformation3d &pose);
	

	// public attributes
	std::string sPath;
	std::string sOivPath;
	std::string sInfoPath;
	std::string sName;
	
	
private:
	// private attributes
	Transformation3d *m_pPoseData;
	int m_nSamples;
};



#endif /* _DATABASE_ENTRY_H_ */
