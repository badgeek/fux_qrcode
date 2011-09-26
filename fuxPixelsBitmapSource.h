#pragma once

#include <zxing/LuminanceSource.h>
#include "Base/GemPixObj.h"

namespace zxing {

// modeled off the Image Magick demo
class fuxPixelsBitmapSource : public LuminanceSource {
private:
  imageStruct& image_;
  int width;
  int height;
	const unsigned char* pixel_cache;

public:
  fuxPixelsBitmapSource(imageStruct& image);

  ~fuxPixelsBitmapSource();

  int getWidth() const;
  int getHeight() const;
  unsigned char* getRow(int y, unsigned char* row);
  unsigned char* getMatrix();
  bool isRotateSupported() const;
  Ref<LuminanceSource> rotateCounterClockwise();
};

}
