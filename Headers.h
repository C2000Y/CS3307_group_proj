
//////////////////////////////////////////////////////////////
// Short description: Collection of MSDN provided Header/libraries
//
//////////////////////////////////////////////////////////////
#ifndef Headers_h__
#define Headers_h__

///* Jong *///
// Let's try to keep most of our headers in this section
// It is neater to keep it that way.
///* Jong *///



// C++ Lib
#include <iostream>
#include <cstdlib>		// srand, rand 
#include <ctime>        // time 
#include <cmath>
#include <map>			// STL
#include <list>			// STL
#include <vector>		// STL
#include <fstream>		// file I/O
#include <string>		// for string
#include <algorithm>	// for sorting STL
#include <functional>	// for sorting STL greater less etc
#include <ctime>	
#include <limits>
// for random 
#include <random>
#include <sstream>


// C Lib

// for leak check
#include <crtdbg.h> // _CrtDumpMemoryLeaks()
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif





#endif
