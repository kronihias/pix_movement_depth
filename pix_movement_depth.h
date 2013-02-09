/*-----------------------------------------------------------------
LOG
GEM - Graphics Environment for Multimedia

Clamp pixel values to a threshold

Copyright (c) 1997-1998 Mark Danks. mark@danks.org
Copyright (c) Günther Geiger. geiger@epy.co.at
Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
Copyright (c) 2002 James Tittle & Chris Clepper
For information on usage and redistribution, and for a DISCLAIMER OF ALL
WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

-----------------------------------------------------------------*/

#ifndef _INCLUDE__GEM_PIXES_pix_movement_depth_H_
#define _INCLUDE__GEM_PIXES_pix_movement_depth_H_

#include "Base/GemPixObj.h"
#include <RTE/MessageCallbacks.h>


/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    pix_movement_depth
    
    Clamp pixel values to a threshold

KEYWORDS
    pix
    
DESCRIPTION

    Extract movement from a depth stream of the Kinect sensor
   
-----------------------------------------------------------------*/
#ifdef _WIN32
class GEM_EXPORT pix_movement_depth : public GemPixObj
#else
class GEM_EXTERN pix_movement_depth : public GemPixObj
#endif
{
    CPPEXTERN_HEADER(pix_movement_depth, GemPixObj);

    public:

        //////////
        // Constructor
    	pix_movement_depth(t_floatarg f);
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~pix_movement_depth();

    	//////////
    	// Do the processing
    	virtual void 	processRGBAImage(imageStruct &image);
    	

    	//////////

    	//////////
    	// Set the new threshold value
        static void threshMessCallback(void *data, float value);

		int m_threshold;
		std::vector<int> buffer;
};

#endif	// for header file
