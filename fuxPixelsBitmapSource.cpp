#include "fuxPixelsBitmapSource.h"

namespace zxing {

fuxPixelsBitmapSource::fuxPixelsBitmapSource(imageStruct& pixels) : image_(pixels) {
  width = pixels.xsize;
  height = pixels.ysize;
  pixel_cache = pixels.data;
}

fuxPixelsBitmapSource::~fuxPixelsBitmapSource() {

}

int fuxPixelsBitmapSource::getWidth() const {
  return width;
}

int fuxPixelsBitmapSource::getHeight() const {
  return height;
}

unsigned char* fuxPixelsBitmapSource::getRow(int y, unsigned char* row) {
  if (row == NULL) {
    row = new unsigned char[width];
  }
  for (int x = 0; x < width; x++) {
    const unsigned char* p = &pixel_cache[4 * (y * width + x)];
    *p++;
    row[x] = (unsigned char)((
				306 * (int)(*p++) +
				601 * (int)(*p++) +
				117 * (int)(*p++) + 0x200) >> 10);
  }
  return row;

}

unsigned char* fuxPixelsBitmapSource::getMatrix() {
  int width = getWidth();
  int height =  getHeight();
  unsigned char* matrix = new unsigned char[width*height];
  unsigned char* m = matrix;
  const unsigned char* p = pixel_cache;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
    *p++;
			*m= (unsigned char)((
				306 * (int)(*p++) +
				601 * (int)(*p++) +
				117 * (int)(*p++) + 0x200) >> 10);
      m++;
    }
  }
  return matrix;
}

bool fuxPixelsBitmapSource::isRotateSupported() const {
  return false;
}

Ref<LuminanceSource> fuxPixelsBitmapSource::rotateCounterClockwise() {
  return Ref<fuxPixelsBitmapSource> (NULL);
}

}

