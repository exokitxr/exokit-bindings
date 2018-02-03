#ifndef BINDINGS_H_
#define BINDINGS_H_

#include <v8.h>
#include <node.h>
#include <image-context.h>
#include <imageData-context.h>
#include <imageBitmap-context.h>
#include <canvas-context.h>
#include <path2d-context.h>
#include <webgl.h>

v8::Local<v8::Object> makeGl();
v8::Local<v8::Object> makeImage();
v8::Local<v8::Object> makeImageData();
v8::Local<v8::Object> makeImageBitmap();
v8::Local<v8::Object> makeCanvasRenderingContext2D(Local<Value> imageDataCons);
v8::Local<v8::Object> makePath2D();

#endif
