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
	outletQR = outlet_new(this->x_obj, 0);
}

/////////////////////////////////////////////////////////
// Destructor
//
/////////////////////////////////////////////////////////
fux_qrcode :: ~fux_qrcode()
{
	outlet_free(outletQR);
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
	std::string QRtext = result->getText()->getText();
	
	char *a=new char[QRtext.size()+1];
	a[QRtext.size()]=0;
	memcpy(a,QRtext.c_str(),QRtext.size());

	outlet_symbol(outletQR, gensym(a));

	delete a;
	
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
  decode(image,true);
}

/////////////////////////////////////////////////////////
// static member function
//
/////////////////////////////////////////////////////////
void fux_qrcode :: obj_setupCallback(t_class *classPtr)
{

}
