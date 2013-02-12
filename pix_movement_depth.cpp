////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-1998 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////


#include "pix_movement_depth.h"
#include <math.h>

CPPEXTERN_NEW_WITH_ONE_ARG(pix_movement_depth,t_floatarg, A_DEFFLOAT);

/////////////////////////////////////////////////////////
//
// pix_movement_depth
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
pix_movement_depth :: pix_movement_depth(t_floatarg f) : m_active(true)
{
    m_threshold = (int) f;
    inlet_new(this->x_obj, &this->x_obj->ob_pd, gensym("float"), gensym("thresh"));
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
pix_movement_depth :: ~pix_movement_depth()
{ }

/////////////////////////////////////////////////////////
// processImage
//
/////////////////////////////////////////////////////////
void pix_movement_depth :: processRGBAImage(imageStruct &image)
{
  if (m_active) { // just filter if active (default true)
    
    int datasize = image.xsize * image.ysize;
    
    // check if buffer has right size
    if (buffer.size() < datasize)
    {
      buffer.resize(datasize,0);
    }
    
    unsigned char *base = image.data;
    int value = 0;
    
    for(int i=0; i<datasize ; i++)    {
      
      if (base[chAlpha]) { // filter out alpha=0 values
        
        value = ((int)base[chRed] << 8) + (int)base[chGreen];
        
        if ((value == 0) || (buffer[i] == 0)) { // filter out noise!
          base[chAlpha] = 0;
        } else {
          if ( abs(value - buffer[i]) < m_threshold ) {
            base[chAlpha] = 0; // just set alpha channel to zero
          }
        }
      }
      
      // store value to buffer for next frame
      buffer[i] = value;
      
      base += 4;
    }
  }
}



/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void pix_movement_depth :: obj_setupCallback(t_class *classPtr)
{
    class_addfloat(classPtr, reinterpret_cast<t_method>(&pix_movement_depth::activeMessCallback));
    class_addmethod(classPtr, reinterpret_cast<t_method>(&pix_movement_depth::threshMessCallback),
                    gensym("threshold"), A_FLOAT, A_NULL);
    class_addmethod(classPtr, reinterpret_cast<t_method>(&pix_movement_depth::threshMessCallback),
                    gensym("thresh"), A_FLOAT, A_NULL);
}

void pix_movement_depth :: threshMessCallback(void *data, t_floatarg value)
{
    GetMyClass(data)->m_threshold = (int) value;
}

void pix_movement_depth :: activeMessCallback(void *data, t_floatarg value)
{
  if (value < 0.5) {
    GetMyClass(data)->m_active = false;
  } else {
    GetMyClass(data)->m_active = true;
  }
  
}
