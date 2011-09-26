/*
 *  fux_qrcode.h
 *  gem_darwin
 *
 *  Created by chris clepper on Mon Oct 07 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INCLUDE_fux_qrcode_H_ 
#define INCLUDE_fux_qrcode_H_ 

#include "Base/GemPixObj.h"

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <zxing/Result.h>
#include <zxing/Exception.h>

#include "fuxPixelsBitmapSource.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    fux_qrcode
    
    

KEYWORDS
    pix
    yuv
    
DESCRIPTION

  old motion blur object.  soon to be an abstraction for pix_convolve ??
   
-----------------------------------------------------------------*/



class GEM_EXTERN fux_qrcode : public GemPixObj
{
CPPEXTERN_HEADER(fux_qrcode, GemPixObj)

    public:

	//////////
	// Constructor
    	fux_qrcode();
	void decode(imageStruct &pixels, bool adaptive = true);
    	
    protected:
    	
    	//////////
    	// Destructor
    	virtual ~fux_qrcode();
    	virtual void processRGBAImage(imageStruct &image);
        
        unsigned int	*saved;
        t_inlet         *inletBlur;
        t_inlet         *inletLength;
	t_outlet	*outletQR;
    private:
    
    	//////////
    	// Static member functions
	static void lengthCallback(void *data, t_floatarg value);
        static void blurCallback(void *data, t_floatarg value);


};

#endif

