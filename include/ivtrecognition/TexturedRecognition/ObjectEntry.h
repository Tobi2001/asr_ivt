// *****************************************************************
// Filename:  ObjectEntry.h
// Copyright: Pedram Azad, Chair Prof. Dillmann (IAIM),
//            Institute for Computer Science and Engineering (CSE),
//            University of Karlsruhe. All rights reserved.
// Author:	  Pedram Azad
// Date:      2006
// *****************************************************************


#ifndef _OBJECT_ENTRY_H_
#define _OBJECT_ENTRY_H_


// *****************************************************************
// necessary includes
// *****************************************************************

#include <string>


// *****************************************************************
// forward class declarations
// *****************************************************************




// *****************************************************************
// CObjectEntry
// *****************************************************************

class CObjectEntry
{
public:
	// constructor
	CObjectEntry(const char *pName, const char *pPath);
	
	// destructor
	~CObjectEntry();
	
	
	// public methods
	bool Init();
	

	// public attributes
	
	std::string m_sName;
	
	
private:
	// private attributes
};



#endif /* _OBJECT_ENTRY_H_ */
