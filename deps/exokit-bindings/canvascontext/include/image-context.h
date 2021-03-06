#ifndef _CANVASCONTEXT_IMAGE_H_
#define _CANVASCONTEXT_IMAGE_H_

#include <v8.h>
#include <nan/nan.h>
#include <defines.h>
#include <canvas/include/Context.h>
#include <canvas/include/Image.h>
#include <canvas/include/ImageData.h>
#include <canvas/include/Resources.h>
#include <SkData.h>
#include <SkImage.h>
#include <nanosvg.h>
#include <nanosvgrast.h>
#include <string>

using namespace v8;
using namespace node;

class Image : public ObjectWrap {
public:
  static Handle<Object> Initialize(Isolate *isolate);
  unsigned int GetWidth();
  unsigned int GetHeight();
  unsigned int GetNumChannels();
  // unsigned char *GetData();
  bool Load(const unsigned char *buffer, size_t size, std::string *error = nullptr);
  // void Set(canvas::Image *image);

protected:
  static NAN_METHOD(New);
  static NAN_GETTER(WidthGetter);
  static NAN_GETTER(HeightGetter);
  static NAN_GETTER(DataGetter);
  static NAN_METHOD(LoadMethod);

  Image();
  ~Image();

private:
  sk_sp<SkImage> image;
  Nan::Persistent<Uint8ClampedArray> dataArray;

  friend class CanvasRenderingContext2D;
  friend class ImageData;
  friend class ImageBitmap;
};

#include "canvas-context.h"

#endif
