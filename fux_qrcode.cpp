/*
 *  fux_qrcode.cpp
 *  gem_darwin
 *
 *  Created by chris clepper on Mon Oct 07 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "fux_qrcode.h"
#include <zxing/Result.h>
#include <cstring>

CPPEXTERN_NEW(fux_qrcode)

/////////////////////////////////////////////////////////
//
// fux_qrcode
//
/////////////////////////////////////////////////////////
// Constructor
//
/////////////////////////////////////////////////////////
//
using namespace zxing;
using namespace zxing::qrcode;

fux_qrcode :: fux_qrcode()
{	

long size,src,i;    
//inletBlur = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("amount"));
//inletLength = inlet_new(this->x_obj, &this->x_obj->ob_pd, &s_float, gensym("length"));

}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
fux_qrcode :: ~fux_qrcode()
{
  //delete saved;
  //relocate this to on external deletion
}

void fux_qrcode::decode(imageStruct& image, bool adaptive) {

  //post("trying to decode");

  try {
    Ref<fuxPixelsBitmapSource> source(new fuxPixelsBitmapSource(image));
    
    Ref<Binarizer> binarizer(NULL);
    if(adaptive) {
      binarizer = new HybridBinarizer(source);
    } else {
      binarizer = new GlobalHistogramBinarizer(source);
    }
    

    Ref<BinaryBitmap> image(new BinaryBitmap(binarizer));
    QRCodeReader reader;
    DecodeHints hints;
    hints.addFormat(BarcodeFormat_QR_CODE);
    hints.setTryHarder(true);
    
    Ref<Result> result(reader.decode(image, hints));
    post("QRcode detected");
	
	std::string QRtext = result->getText()->getText();
	
	
	
  } catch (zxing::Exception& e) {
   	//post(e.what()); // << e.what() << endl;
  }

}


/////////////////////////////////////////////////////////
// processImage
//
/////////////////////////////////////////////////////////
void fux_qrcode :: processRGBAImage(imageStruct &image)
{
  //int h,w,hlength;
  //int R,G,B;
  //unsigned char *pixels=image.data;

  decode(image,true);

  //hlength = image.xsize;

}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void fux_qrcode :: obj_setupCallback(t_class *classPtr)
{

    class_addmethod(classPtr, (t_method)&fux_qrcode::blurCallback,gensym("amount"), A_DEFFLOAT, A_NULL);
    class_addmethod(classPtr, (t_method)&fux_qrcode::lengthCallback,gensym("length"), A_DEFFLOAT, A_NULL);

}

void fux_qrcode :: blurCallback(void *data, t_floatarg value)
{
	//GetMyClass(data)->m_glitchAmount=(value);
}

void fux_qrcode :: lengthCallback(void *data, t_floatarg value)
{
	//GetMyClass(data)->m_glitchLength=(value);
}
