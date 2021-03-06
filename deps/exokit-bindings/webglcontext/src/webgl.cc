#include <cstring>
#include <vector>

#include <webglcontext/include/webgl.h>
#include <canvascontext/include/imageData-context.h>
// #include <node.h>

/* #include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "glesjs", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "glesjs", __VA_ARGS__)) */

// using namespace node;
using namespace v8;
using namespace std;

// forward declarations
/* enum GLObjectType {
  GLOBJECT_TYPE_BUFFER,
  GLOBJECT_TYPE_FRAMEBUFFER,
  GLOBJECT_TYPE_PROGRAM,
  GLOBJECT_TYPE_RENDERBUFFER,
  GLOBJECT_TYPE_SHADER,
  GLOBJECT_TYPE_TEXTURE,
};

void registerGLObj(GLObjectType type, GLuint obj);
void unregisterGLObj(GLuint obj); */

// WebGLRenderingContext

// Used to be a macro, hence the uppercase name.
#define JS_GL_SET_CONSTANT(name, constant) proto->Set(JS_STR( name ), JS_INT(constant))

#define JS_GL_CONSTANT(name) JS_GL_SET_CONSTANT(#name, GL_ ## name)

Handle<Object> WebGLRenderingContext::Initialize(Isolate *isolate) {
  Nan::EscapableHandleScope scope;

  // constructor
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(New);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(JS_STR("WebGLRenderingContext"));

  // prototype
  Local<ObjectTemplate> proto = ctor->PrototypeTemplate();

  Nan::SetMethod(proto, "destroy", Destroy);
  Nan::SetMethod(proto, "getWindowHandle", GetWindowHandle);
  Nan::SetMethod(proto, "setWindowHandle", SetWindowHandle);
  Nan::SetMethod(proto, "isDirty", IsDirty);
  Nan::SetMethod(proto, "clearDirty", ClearDirty);

  Nan::SetMethod(proto, "uniform1f", glCallWrap<Uniform1f>);
  Nan::SetMethod(proto, "uniform2f", glCallWrap<Uniform2f>);
  Nan::SetMethod(proto, "uniform3f", glCallWrap<Uniform3f>);
  Nan::SetMethod(proto, "uniform4f", glCallWrap<Uniform4f>);
  Nan::SetMethod(proto, "uniform1i", glCallWrap<Uniform1i>);
  Nan::SetMethod(proto, "uniform2i", glCallWrap<Uniform2i>);
  Nan::SetMethod(proto, "uniform3i", glCallWrap<Uniform3i>);
  Nan::SetMethod(proto, "uniform4i", glCallWrap<Uniform4i>);
  Nan::SetMethod(proto, "uniform1fv", glCallWrap<Uniform1fv>);
  Nan::SetMethod(proto, "uniform2fv", glCallWrap<Uniform2fv>);
  Nan::SetMethod(proto, "uniform3fv", glCallWrap<Uniform3fv>);
  Nan::SetMethod(proto, "uniform4fv", glCallWrap<Uniform4fv>);
  Nan::SetMethod(proto, "uniform1iv", glCallWrap<Uniform1iv>);
  Nan::SetMethod(proto, "uniform2iv", glCallWrap<Uniform2iv>);
  Nan::SetMethod(proto, "uniform3iv", glCallWrap<Uniform3iv>);
  Nan::SetMethod(proto, "uniform4iv", glCallWrap<Uniform4iv>);
  Nan::SetMethod(proto, "pixelStorei", glCallWrap<PixelStorei>);
  Nan::SetMethod(proto, "bindAttribLocation", glCallWrap<BindAttribLocation>);
  Nan::SetMethod(proto, "getError", glCallWrap<GetError>);
  Nan::SetMethod(proto, "drawArrays", glCallWrap<DrawArrays>);
  Nan::SetMethod(proto, "drawArraysInstancedANGLE", glCallWrap<DrawArraysInstancedANGLE>);
  Nan::SetMethod(proto, "uniformMatrix2fv", glCallWrap<UniformMatrix2fv>);
  Nan::SetMethod(proto, "uniformMatrix3fv", glCallWrap<UniformMatrix3fv>);
  Nan::SetMethod(proto, "uniformMatrix4fv", glCallWrap<UniformMatrix4fv>);

  Nan::SetMethod(proto, "generateMipmap", glCallWrap<GenerateMipmap>);

  Nan::SetMethod(proto, "getAttribLocation", glCallWrap<GetAttribLocation>);
  Nan::SetMethod(proto, "depthFunc", glCallWrap<DepthFunc>);
  Nan::SetMethod(proto, "viewport", glCallWrap<Viewport>);
  Nan::SetMethod(proto, "createShader", glCallWrap<CreateShader>);
  Nan::SetMethod(proto, "shaderSource", glCallWrap<ShaderSource>);
  Nan::SetMethod(proto, "compileShader", glCallWrap<CompileShader>);
  Nan::SetMethod(proto, "getShaderParameter", glCallWrap<GetShaderParameter>);
  Nan::SetMethod(proto, "getShaderInfoLog", glCallWrap<GetShaderInfoLog>);
  Nan::SetMethod(proto, "createProgram", glCallWrap<CreateProgram>);
  Nan::SetMethod(proto, "attachShader", glCallWrap<AttachShader>);
  Nan::SetMethod(proto, "linkProgram", glCallWrap<LinkProgram>);
  Nan::SetMethod(proto, "getProgramParameter", glCallWrap<GetProgramParameter>);
  Nan::SetMethod(proto, "getUniformLocation", glCallWrap<GetUniformLocation>);
  Nan::SetMethod(proto, "clearColor", glCallWrap<ClearColor>);
  Nan::SetMethod(proto, "clearDepth", glCallWrap<ClearDepth>);

  Nan::SetMethod(proto, "disable", glCallWrap<Disable>);
  Nan::SetMethod(proto, "createTexture", glCallWrap<CreateTexture>);
  Nan::SetMethod(proto, "bindTexture", glCallWrap<BindTexture>);
  // Nan::SetMethod(proto, "flipTextureData", glCallWrap<FlipTextureData>);
  Nan::SetMethod(proto, "texImage2D", glCallWrap<TexImage2D>);
  Nan::SetMethod(proto, "compressedTexImage2D", glCallWrap<CompressedTexImage2D>);
  Nan::SetMethod(proto, "texParameteri", glCallWrap<TexParameteri>);
  Nan::SetMethod(proto, "texParameterf", glCallWrap<TexParameterf>);
  Nan::SetMethod(proto, "clear", glCallWrap<Clear>);
  Nan::SetMethod(proto, "useProgram", glCallWrap<UseProgram>);
  Nan::SetMethod(proto, "createFramebuffer", glCallWrap<CreateFramebuffer>);
  Nan::SetMethod(proto, "bindFramebuffer", glCallWrap<BindFramebuffer>);
  Nan::SetMethod(proto, "framebufferTexture2D", glCallWrap<FramebufferTexture2D>);
  Nan::SetMethod(proto, "createBuffer", glCallWrap<CreateBuffer>);
  Nan::SetMethod(proto, "bindBuffer", glCallWrap<BindBuffer>);
  Nan::SetMethod(proto, "bufferData", glCallWrap<BufferData>);
  Nan::SetMethod(proto, "bufferSubData", glCallWrap<BufferSubData>);
  Nan::SetMethod(proto, "enable", glCallWrap<Enable>);
  Nan::SetMethod(proto, "blendEquation", glCallWrap<BlendEquation>);
  Nan::SetMethod(proto, "blendFunc", glCallWrap<BlendFunc>);
  Nan::SetMethod(proto, "enableVertexAttribArray", glCallWrap<EnableVertexAttribArray>);
  Nan::SetMethod(proto, "vertexAttribPointer", glCallWrap<VertexAttribPointer>);
  Nan::SetMethod(proto, "activeTexture", glCallWrap<ActiveTexture>);
  Nan::SetMethod(proto, "drawElements", glCallWrap<DrawElements>);
  Nan::SetMethod(proto, "drawElementsInstancedANGLE", glCallWrap<DrawElementsInstancedANGLE>);
  Nan::SetMethod(proto, "flush", glCallWrap<Flush>);
  Nan::SetMethod(proto, "finish", glCallWrap<Finish>);

  Nan::SetMethod(proto, "vertexAttrib1f", glCallWrap<VertexAttrib1f>);
  Nan::SetMethod(proto, "vertexAttrib2f", glCallWrap<VertexAttrib2f>);
  Nan::SetMethod(proto, "vertexAttrib3f", glCallWrap<VertexAttrib3f>);
  Nan::SetMethod(proto, "vertexAttrib4f", glCallWrap<VertexAttrib4f>);
  Nan::SetMethod(proto, "vertexAttrib1fv", glCallWrap<VertexAttrib1fv>);
  Nan::SetMethod(proto, "vertexAttrib2fv", glCallWrap<VertexAttrib2fv>);
  Nan::SetMethod(proto, "vertexAttrib3fv", glCallWrap<VertexAttrib3fv>);
  Nan::SetMethod(proto, "vertexAttrib4fv", glCallWrap<VertexAttrib4fv>);
  Nan::SetMethod(proto, "vertexAttribDivisorANGLE", glCallWrap<VertexAttribDivisorANGLE>);

  Nan::SetMethod(proto, "blendColor", BlendColor);
  Nan::SetMethod(proto, "blendEquationSeparate", BlendEquationSeparate);
  Nan::SetMethod(proto, "blendFuncSeparate", BlendFuncSeparate);
  Nan::SetMethod(proto, "clearStencil", ClearStencil);
  Nan::SetMethod(proto, "colorMask", ColorMask);
  Nan::SetMethod(proto, "copyTexImage2D", CopyTexImage2D);
  Nan::SetMethod(proto, "copyTexSubImage2D", CopyTexSubImage2D);
  Nan::SetMethod(proto, "cullFace", CullFace);
  Nan::SetMethod(proto, "depthMask", DepthMask);
  Nan::SetMethod(proto, "depthRange", DepthRange);
  Nan::SetMethod(proto, "disableVertexAttribArray", DisableVertexAttribArray);
  Nan::SetMethod(proto, "hint", Hint);
  Nan::SetMethod(proto, "isEnabled", IsEnabled);
  Nan::SetMethod(proto, "lineWidth", LineWidth);
  Nan::SetMethod(proto, "polygonOffset", PolygonOffset);

  Nan::SetMethod(proto, "scissor", Scissor);
  Nan::SetMethod(proto, "stencilFunc", StencilFunc);
  Nan::SetMethod(proto, "stencilFuncSeparate", StencilFuncSeparate);
  Nan::SetMethod(proto, "stencilMask", StencilMask);
  Nan::SetMethod(proto, "stencilMaskSeparate", StencilMaskSeparate);
  Nan::SetMethod(proto, "stencilOp", StencilOp);
  Nan::SetMethod(proto, "stencilOpSeparate", StencilOpSeparate);
  Nan::SetMethod(proto, "bindRenderbuffer", BindRenderbuffer);
  Nan::SetMethod(proto, "createRenderbuffer", CreateRenderbuffer);

  Nan::SetMethod(proto, "deleteBuffer", DeleteBuffer);
  Nan::SetMethod(proto, "deleteFramebuffer", DeleteFramebuffer);
  Nan::SetMethod(proto, "deleteProgram", DeleteProgram);
  Nan::SetMethod(proto, "deleteRenderbuffer", DeleteRenderbuffer);
  Nan::SetMethod(proto, "deleteShader", DeleteShader);
  Nan::SetMethod(proto, "deleteTexture", DeleteTexture);
  Nan::SetMethod(proto, "detachShader", DetachShader);
  Nan::SetMethod(proto, "framebufferRenderbuffer", FramebufferRenderbuffer);
  Nan::SetMethod(proto, "getVertexAttribOffset", GetVertexAttribOffset);

  Nan::SetMethod(proto, "isBuffer", glCallWrap<IsBuffer>);
  Nan::SetMethod(proto, "isFramebuffer", glCallWrap<IsFramebuffer>);
  Nan::SetMethod(proto, "isProgram", glCallWrap<IsProgram>);
  Nan::SetMethod(proto, "isRenderbuffer", glCallWrap<IsRenderbuffer>);
  Nan::SetMethod(proto, "isShader", glCallWrap<IsShader>);
  Nan::SetMethod(proto, "isTexture", glCallWrap<IsTexture>);

  Nan::SetMethod(proto, "renderbufferStorage", glCallWrap<RenderbufferStorage>);
  Nan::SetMethod(proto, "getShaderSource", glCallWrap<GetShaderSource>);
  Nan::SetMethod(proto, "validateProgram", glCallWrap<ValidateProgram>);

  Nan::SetMethod(proto, "texSubImage2D", glCallWrap<TexSubImage2D>);
  Nan::SetMethod(proto, "readPixels", glCallWrap<ReadPixels>);
  Nan::SetMethod(proto, "getTexParameter", glCallWrap<GetTexParameter>);
  Nan::SetMethod(proto, "getActiveAttrib", glCallWrap<GetActiveAttrib>);
  Nan::SetMethod(proto, "getActiveUniform", glCallWrap<GetActiveUniform>);
  Nan::SetMethod(proto, "getAttachedShaders", glCallWrap<GetAttachedShaders>);
  Nan::SetMethod(proto, "getParameter", glCallWrap<GetParameter>);
  Nan::SetMethod(proto, "getBufferParameter", glCallWrap<GetBufferParameter>);
  Nan::SetMethod(proto, "getFramebufferAttachmentParameter", glCallWrap<GetFramebufferAttachmentParameter>);
  Nan::SetMethod(proto, "getProgramInfoLog", glCallWrap<GetProgramInfoLog>);
  Nan::SetMethod(proto, "getRenderbufferParameter", glCallWrap<GetRenderbufferParameter>);
  Nan::SetMethod(proto, "getVertexAttrib", glCallWrap<GetVertexAttrib>);
  Nan::SetMethod(proto, "getSupportedExtensions", glCallWrap<GetSupportedExtensions>);
  Nan::SetMethod(proto, "getExtension", glCallWrap<GetExtension>);
  Nan::SetMethod(proto, "checkFramebufferStatus", glCallWrap<CheckFramebufferStatus>);

  Nan::SetMethod(proto, "frontFace", glCallWrap<FrontFace>);

  Nan::SetMethod(proto, "setDefaultFramebuffer", SetDefaultFramebuffer);

  // OpenGL ES 2.1 constants

  /* ClearBufferMask */
  JS_GL_CONSTANT(DEPTH_BUFFER_BIT);
  JS_GL_CONSTANT(STENCIL_BUFFER_BIT);
  JS_GL_CONSTANT(COLOR_BUFFER_BIT);

  /* Boolean */
  JS_GL_CONSTANT(FALSE);
  JS_GL_CONSTANT(TRUE);

  /* BeginMode */
  JS_GL_CONSTANT(POINTS);
  JS_GL_CONSTANT(LINES);
  JS_GL_CONSTANT(LINE_LOOP);
  JS_GL_CONSTANT(LINE_STRIP);
  JS_GL_CONSTANT(TRIANGLES);
  JS_GL_CONSTANT(TRIANGLE_STRIP);
  JS_GL_CONSTANT(TRIANGLE_FAN);

  /* AlphaFunction (not supported in ES20) */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* BlendingFactorDest */
  JS_GL_CONSTANT(ZERO);
  JS_GL_CONSTANT(ONE);
  JS_GL_CONSTANT(SRC_COLOR);
  JS_GL_CONSTANT(ONE_MINUS_SRC_COLOR);
  JS_GL_CONSTANT(SRC_ALPHA);
  JS_GL_CONSTANT(ONE_MINUS_SRC_ALPHA);
  JS_GL_CONSTANT(DST_ALPHA);
  JS_GL_CONSTANT(ONE_MINUS_DST_ALPHA);

  /* BlendingFactorSrc */
  /*      GL_ZERO */
  /*      GL_ONE */
  JS_GL_CONSTANT(DST_COLOR);
  JS_GL_CONSTANT(ONE_MINUS_DST_COLOR);
  JS_GL_CONSTANT(SRC_ALPHA_SATURATE);
  /*      GL_SRC_ALPHA */
  /*      GL_ONE_MINUS_SRC_ALPHA */
  /*      GL_DST_ALPHA */
  /*      GL_ONE_MINUS_DST_ALPHA */

  /* BlendEquationSeparate */
  JS_GL_CONSTANT(FUNC_ADD);
  JS_GL_CONSTANT(BLEND_EQUATION);
  JS_GL_CONSTANT(BLEND_EQUATION_RGB);    /* same as BLEND_EQUATION */
  JS_GL_CONSTANT(BLEND_EQUATION_ALPHA);

  /* BlendSubtract */
  JS_GL_CONSTANT(FUNC_SUBTRACT);
  JS_GL_CONSTANT(FUNC_REVERSE_SUBTRACT);

  /* Separate Blend Functions */
  JS_GL_CONSTANT(BLEND_DST_RGB);
  JS_GL_CONSTANT(BLEND_SRC_RGB);
  JS_GL_CONSTANT(BLEND_DST_ALPHA);
  JS_GL_CONSTANT(BLEND_SRC_ALPHA);
  JS_GL_CONSTANT(CONSTANT_COLOR);
  JS_GL_CONSTANT(ONE_MINUS_CONSTANT_COLOR);
  JS_GL_CONSTANT(CONSTANT_ALPHA);
  JS_GL_CONSTANT(ONE_MINUS_CONSTANT_ALPHA);
  JS_GL_CONSTANT(BLEND_COLOR);

  /* Buffer Objects */
  JS_GL_CONSTANT(ARRAY_BUFFER);
  JS_GL_CONSTANT(ELEMENT_ARRAY_BUFFER);
  JS_GL_CONSTANT(ARRAY_BUFFER_BINDING);
  JS_GL_CONSTANT(ELEMENT_ARRAY_BUFFER_BINDING);

  JS_GL_CONSTANT(STREAM_DRAW);
  JS_GL_CONSTANT(STATIC_DRAW);
  JS_GL_CONSTANT(DYNAMIC_DRAW);

  JS_GL_CONSTANT(BUFFER_SIZE);
  JS_GL_CONSTANT(BUFFER_USAGE);

  JS_GL_CONSTANT(CURRENT_VERTEX_ATTRIB);

  /* CullFaceMode */
  JS_GL_CONSTANT(FRONT);
  JS_GL_CONSTANT(BACK);
  JS_GL_CONSTANT(FRONT_AND_BACK);

  /* DepthFunction */
  /*      GL_NEVER */
  /*      GL_LESS */
  /*      GL_EQUAL */
  /*      GL_LEQUAL */
  /*      GL_GREATER */
  /*      GL_NOTEQUAL */
  /*      GL_GEQUAL */
  /*      GL_ALWAYS */

  /* EnableCap */
  JS_GL_CONSTANT(TEXTURE_2D);
  JS_GL_CONSTANT(CULL_FACE);
  JS_GL_CONSTANT(BLEND);
  JS_GL_CONSTANT(DITHER);
  JS_GL_CONSTANT(STENCIL_TEST);
  JS_GL_CONSTANT(DEPTH_TEST);
  JS_GL_CONSTANT(SCISSOR_TEST);
  JS_GL_CONSTANT(POLYGON_OFFSET_FILL);
  JS_GL_CONSTANT(SAMPLE_ALPHA_TO_COVERAGE);
  JS_GL_CONSTANT(SAMPLE_COVERAGE);

  /* ErrorCode */
  JS_GL_CONSTANT(NO_ERROR);
  JS_GL_CONSTANT(INVALID_ENUM);
  JS_GL_CONSTANT(INVALID_VALUE);
  JS_GL_CONSTANT(INVALID_OPERATION);
  JS_GL_CONSTANT(OUT_OF_MEMORY);

  /* FrontFaceDirection */
  JS_GL_CONSTANT(CW);
  JS_GL_CONSTANT(CCW);

  /* GetPName */
  JS_GL_CONSTANT(LINE_WIDTH);
  JS_GL_CONSTANT(ALIASED_POINT_SIZE_RANGE);
  JS_GL_CONSTANT(ALIASED_LINE_WIDTH_RANGE);
  JS_GL_CONSTANT(CULL_FACE_MODE);
  JS_GL_CONSTANT(FRONT_FACE);
  JS_GL_CONSTANT(DEPTH_RANGE);
  JS_GL_CONSTANT(DEPTH_WRITEMASK);
  JS_GL_CONSTANT(DEPTH_CLEAR_VALUE);
  JS_GL_CONSTANT(DEPTH_FUNC);
  JS_GL_CONSTANT(STENCIL_CLEAR_VALUE);
  JS_GL_CONSTANT(STENCIL_FUNC);
  JS_GL_CONSTANT(STENCIL_FAIL);
  JS_GL_CONSTANT(STENCIL_PASS_DEPTH_FAIL);
  JS_GL_CONSTANT(STENCIL_PASS_DEPTH_PASS);
  JS_GL_CONSTANT(STENCIL_REF);
  JS_GL_CONSTANT(STENCIL_VALUE_MASK);
  JS_GL_CONSTANT(STENCIL_WRITEMASK);
  JS_GL_CONSTANT(STENCIL_BACK_FUNC);
  JS_GL_CONSTANT(STENCIL_BACK_FAIL);
  JS_GL_CONSTANT(STENCIL_BACK_PASS_DEPTH_FAIL);
  JS_GL_CONSTANT(STENCIL_BACK_PASS_DEPTH_PASS);
  JS_GL_CONSTANT(STENCIL_BACK_REF);
  JS_GL_CONSTANT(STENCIL_BACK_VALUE_MASK);
  JS_GL_CONSTANT(STENCIL_BACK_WRITEMASK);
  JS_GL_CONSTANT(VIEWPORT);
  JS_GL_CONSTANT(SCISSOR_BOX);
  /*      GL_SCISSOR_TEST */
  JS_GL_CONSTANT(COLOR_CLEAR_VALUE);
  JS_GL_CONSTANT(COLOR_WRITEMASK);
  JS_GL_CONSTANT(UNPACK_ALIGNMENT);
  JS_GL_CONSTANT(PACK_ALIGNMENT);
  JS_GL_CONSTANT(MAX_TEXTURE_SIZE);
  JS_GL_CONSTANT(MAX_VIEWPORT_DIMS);
  JS_GL_CONSTANT(SUBPIXEL_BITS);
  JS_GL_CONSTANT(RED_BITS);
  JS_GL_CONSTANT(GREEN_BITS);
  JS_GL_CONSTANT(BLUE_BITS);
  JS_GL_CONSTANT(ALPHA_BITS);
  JS_GL_CONSTANT(DEPTH_BITS);
  JS_GL_CONSTANT(STENCIL_BITS);
  JS_GL_CONSTANT(POLYGON_OFFSET_UNITS);
  /*      GL_POLYGON_OFFSET_FILL */
  JS_GL_CONSTANT(POLYGON_OFFSET_FACTOR);
  JS_GL_CONSTANT(TEXTURE_BINDING_2D);
  JS_GL_CONSTANT(SAMPLE_BUFFERS);
  JS_GL_CONSTANT(SAMPLES);
  JS_GL_CONSTANT(SAMPLE_COVERAGE_VALUE);
  JS_GL_CONSTANT(SAMPLE_COVERAGE_INVERT);

  /* GetTextureParameter */
  /*      GL_TEXTURE_MAG_FILTER */
  /*      GL_TEXTURE_MIN_FILTER */
  /*      GL_TEXTURE_WRAP_S */
  /*      GL_TEXTURE_WRAP_T */

  JS_GL_CONSTANT(NUM_COMPRESSED_TEXTURE_FORMATS);
  JS_GL_CONSTANT(COMPRESSED_TEXTURE_FORMATS);

  /* HintMode */
  JS_GL_CONSTANT(DONT_CARE);
  JS_GL_CONSTANT(FASTEST);
  JS_GL_CONSTANT(NICEST);

  /* HintTarget */
  JS_GL_CONSTANT(GENERATE_MIPMAP_HINT);

  /* DataType */
  JS_GL_CONSTANT(BYTE);
  JS_GL_CONSTANT(UNSIGNED_BYTE);
  JS_GL_CONSTANT(SHORT);
  JS_GL_CONSTANT(UNSIGNED_SHORT);
  JS_GL_CONSTANT(INT);
  JS_GL_CONSTANT(UNSIGNED_INT);
  JS_GL_CONSTANT(FLOAT);
// #ifndef __APPLE__
  JS_GL_CONSTANT(FIXED);
// #endif

  /* PixelFormat */
  JS_GL_CONSTANT(DEPTH_COMPONENT);
  JS_GL_CONSTANT(ALPHA);
  JS_GL_CONSTANT(RGB);
  JS_GL_CONSTANT(RGBA);
  JS_GL_CONSTANT(LUMINANCE);
  JS_GL_CONSTANT(LUMINANCE_ALPHA);

  /* PixelType */
  /*      GL_UNSIGNED_BYTE */
  JS_GL_CONSTANT(UNSIGNED_SHORT_4_4_4_4);
  JS_GL_CONSTANT(UNSIGNED_SHORT_5_5_5_1);
  JS_GL_CONSTANT(UNSIGNED_SHORT_5_6_5);

  /* Shaders */
  JS_GL_CONSTANT(FRAGMENT_SHADER);
  JS_GL_CONSTANT(VERTEX_SHADER);
  JS_GL_CONSTANT(MAX_VERTEX_ATTRIBS);
// #ifndef __APPLE__
  JS_GL_CONSTANT(MAX_VERTEX_UNIFORM_VECTORS);
  JS_GL_CONSTANT(MAX_VARYING_VECTORS);
// #endif
  JS_GL_CONSTANT(MAX_COMBINED_TEXTURE_IMAGE_UNITS);
  JS_GL_CONSTANT(MAX_VERTEX_TEXTURE_IMAGE_UNITS);
  JS_GL_CONSTANT(MAX_TEXTURE_IMAGE_UNITS);
// #ifndef __APPLE__
  JS_GL_CONSTANT(MAX_FRAGMENT_UNIFORM_VECTORS);
// #endif
  JS_GL_CONSTANT(SHADER_TYPE);
  JS_GL_CONSTANT(DELETE_STATUS);
  JS_GL_CONSTANT(LINK_STATUS);
  JS_GL_CONSTANT(VALIDATE_STATUS);
  JS_GL_CONSTANT(ATTACHED_SHADERS);
  JS_GL_CONSTANT(ACTIVE_UNIFORMS);
  JS_GL_CONSTANT(ACTIVE_UNIFORM_MAX_LENGTH);
  JS_GL_CONSTANT(ACTIVE_ATTRIBUTES);
  JS_GL_CONSTANT(ACTIVE_ATTRIBUTE_MAX_LENGTH);
  JS_GL_CONSTANT(SHADING_LANGUAGE_VERSION);
  JS_GL_CONSTANT(CURRENT_PROGRAM);

  /* StencilFunction */
  JS_GL_CONSTANT(NEVER);
  JS_GL_CONSTANT(LESS);
  JS_GL_CONSTANT(EQUAL);
  JS_GL_CONSTANT(LEQUAL);
  JS_GL_CONSTANT(GREATER);
  JS_GL_CONSTANT(NOTEQUAL);
  JS_GL_CONSTANT(GEQUAL);
  JS_GL_CONSTANT(ALWAYS);

  /* StencilOp */
  /*      GL_ZERO */
  JS_GL_CONSTANT(KEEP);
  JS_GL_CONSTANT(REPLACE);
  JS_GL_CONSTANT(INCR);
  JS_GL_CONSTANT(DECR);
  JS_GL_CONSTANT(INVERT);
  JS_GL_CONSTANT(INCR_WRAP);
  JS_GL_CONSTANT(DECR_WRAP);

  /* StringName */
  JS_GL_CONSTANT(VENDOR);
  JS_GL_CONSTANT(RENDERER);
  JS_GL_CONSTANT(VERSION);
  JS_GL_CONSTANT(EXTENSIONS);

  /* TextureMagFilter */
  JS_GL_CONSTANT(NEAREST);
  JS_GL_CONSTANT(LINEAR);

  /* TextureMinFilter */
  /*      GL_NEAREST */
  /*      GL_LINEAR */
  JS_GL_CONSTANT(NEAREST_MIPMAP_NEAREST);
  JS_GL_CONSTANT(LINEAR_MIPMAP_NEAREST);
  JS_GL_CONSTANT(NEAREST_MIPMAP_LINEAR);
  JS_GL_CONSTANT(LINEAR_MIPMAP_LINEAR);

  /* TextureParameterName */
  JS_GL_CONSTANT(TEXTURE_MAG_FILTER);
  JS_GL_CONSTANT(TEXTURE_MIN_FILTER);
  JS_GL_CONSTANT(TEXTURE_WRAP_S);
  JS_GL_CONSTANT(TEXTURE_WRAP_T);

  /* TextureTarget */
  /*      GL_TEXTURE_2D */
  JS_GL_CONSTANT(TEXTURE);

  JS_GL_CONSTANT(TEXTURE_CUBE_MAP);
  JS_GL_CONSTANT(TEXTURE_BINDING_CUBE_MAP);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_X);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_X);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_Y);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_Y);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_Z);
  JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_Z);
  JS_GL_CONSTANT(MAX_CUBE_MAP_TEXTURE_SIZE);

  /* TextureUnit */
  JS_GL_CONSTANT(TEXTURE0);
  JS_GL_CONSTANT(TEXTURE1);
  JS_GL_CONSTANT(TEXTURE2);
  JS_GL_CONSTANT(TEXTURE3);
  JS_GL_CONSTANT(TEXTURE4);
  JS_GL_CONSTANT(TEXTURE5);
  JS_GL_CONSTANT(TEXTURE6);
  JS_GL_CONSTANT(TEXTURE7);
  JS_GL_CONSTANT(TEXTURE8);
  JS_GL_CONSTANT(TEXTURE9);
  JS_GL_CONSTANT(TEXTURE10);
  JS_GL_CONSTANT(TEXTURE11);
  JS_GL_CONSTANT(TEXTURE12);
  JS_GL_CONSTANT(TEXTURE13);
  JS_GL_CONSTANT(TEXTURE14);
  JS_GL_CONSTANT(TEXTURE15);
  JS_GL_CONSTANT(TEXTURE16);
  JS_GL_CONSTANT(TEXTURE17);
  JS_GL_CONSTANT(TEXTURE18);
  JS_GL_CONSTANT(TEXTURE19);
  JS_GL_CONSTANT(TEXTURE20);
  JS_GL_CONSTANT(TEXTURE21);
  JS_GL_CONSTANT(TEXTURE22);
  JS_GL_CONSTANT(TEXTURE23);
  JS_GL_CONSTANT(TEXTURE24);
  JS_GL_CONSTANT(TEXTURE25);
  JS_GL_CONSTANT(TEXTURE26);
  JS_GL_CONSTANT(TEXTURE27);
  JS_GL_CONSTANT(TEXTURE28);
  JS_GL_CONSTANT(TEXTURE29);
  JS_GL_CONSTANT(TEXTURE30);
  JS_GL_CONSTANT(TEXTURE31);
  JS_GL_CONSTANT(ACTIVE_TEXTURE);

  /* TextureWrapMode */
  JS_GL_CONSTANT(REPEAT);
  JS_GL_CONSTANT(CLAMP_TO_EDGE);
  JS_GL_CONSTANT(MIRRORED_REPEAT);

  /* Uniform Types */
  JS_GL_CONSTANT(FLOAT_VEC2);
  JS_GL_CONSTANT(FLOAT_VEC3);
  JS_GL_CONSTANT(FLOAT_VEC4);
  JS_GL_CONSTANT(INT_VEC2);
  JS_GL_CONSTANT(INT_VEC3);
  JS_GL_CONSTANT(INT_VEC4);
  JS_GL_CONSTANT(BOOL);
  JS_GL_CONSTANT(BOOL_VEC2);
  JS_GL_CONSTANT(BOOL_VEC3);
  JS_GL_CONSTANT(BOOL_VEC4);
  JS_GL_CONSTANT(FLOAT_MAT2);
  JS_GL_CONSTANT(FLOAT_MAT3);
  JS_GL_CONSTANT(FLOAT_MAT4);
  JS_GL_CONSTANT(SAMPLER_2D);
  JS_GL_CONSTANT(SAMPLER_CUBE);

  /* Vertex Arrays */
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_ENABLED);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_SIZE);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_STRIDE);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_TYPE);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_NORMALIZED);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_POINTER);
  JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);

  /* Read Format */
// #ifndef __APPLE__
  JS_GL_CONSTANT(IMPLEMENTATION_COLOR_READ_TYPE);
  JS_GL_CONSTANT(IMPLEMENTATION_COLOR_READ_FORMAT);
// #endif

  /* Shader Source */
  JS_GL_CONSTANT(COMPILE_STATUS);
  JS_GL_CONSTANT(INFO_LOG_LENGTH);
  JS_GL_CONSTANT(SHADER_SOURCE_LENGTH);
// #ifndef __APPLE__
  JS_GL_CONSTANT(SHADER_COMPILER);
// #endif

  /* Shader Binary */
// #ifndef __APPLE__
  JS_GL_CONSTANT(SHADER_BINARY_FORMATS);
  JS_GL_CONSTANT(NUM_SHADER_BINARY_FORMATS);
// #endif

  /* Shader Precision-Specified Types */
// #ifndef __APPLE__
  JS_GL_CONSTANT(LOW_FLOAT);
  JS_GL_CONSTANT(MEDIUM_FLOAT);
  JS_GL_CONSTANT(HIGH_FLOAT);
  JS_GL_CONSTANT(LOW_INT);
  JS_GL_CONSTANT(MEDIUM_INT);
  JS_GL_CONSTANT(HIGH_INT);
// #endif

  /* Framebuffer Object. */
  JS_GL_CONSTANT(FRAMEBUFFER);
  JS_GL_CONSTANT(RENDERBUFFER);

  JS_GL_CONSTANT(RGBA4);
  JS_GL_CONSTANT(RGB5_A1);
// #ifndef __APPLE__
  //JS_GL_CONSTANT(RGB565);
// #endif
  JS_GL_CONSTANT(DEPTH_COMPONENT16);
  // JS_GL_CONSTANT(STENCIL_INDEX);
  JS_GL_CONSTANT(STENCIL_INDEX8);
  JS_GL_CONSTANT(DEPTH_STENCIL);
  JS_GL_CONSTANT(DEPTH24_STENCIL8);

  JS_GL_CONSTANT(RENDERBUFFER_WIDTH);
  JS_GL_CONSTANT(RENDERBUFFER_HEIGHT);
  JS_GL_CONSTANT(RENDERBUFFER_INTERNAL_FORMAT);
  JS_GL_CONSTANT(RENDERBUFFER_RED_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_GREEN_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_BLUE_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_ALPHA_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_DEPTH_SIZE);
  JS_GL_CONSTANT(RENDERBUFFER_STENCIL_SIZE);

  JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
  JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
  JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
  JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);

  JS_GL_CONSTANT(COLOR_ATTACHMENT0);
  JS_GL_CONSTANT(DEPTH_ATTACHMENT);
  JS_GL_CONSTANT(STENCIL_ATTACHMENT);
  JS_GL_CONSTANT(DEPTH_STENCIL_ATTACHMENT);

  JS_GL_CONSTANT(NONE);

  JS_GL_CONSTANT(FRAMEBUFFER_COMPLETE);
  JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
  JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
// #ifndef __APPLE__
  //JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_DIMENSIONS);
// #endif
  JS_GL_CONSTANT(FRAMEBUFFER_UNSUPPORTED);

  JS_GL_CONSTANT(FRAMEBUFFER_BINDING);
  JS_GL_CONSTANT(RENDERBUFFER_BINDING);
  JS_GL_CONSTANT(MAX_RENDERBUFFER_SIZE);

  JS_GL_CONSTANT(INVALID_FRAMEBUFFER_OPERATION);

  /* WebGL-specific enums */
  JS_GL_SET_CONSTANT("UNPACK_FLIP_Y_WEBGL", UNPACK_FLIP_Y_WEBGL);
  JS_GL_SET_CONSTANT("UNPACK_PREMULTIPLY_ALPHA_WEBGL", UNPACK_PREMULTIPLY_ALPHA_WEBGL);
  JS_GL_SET_CONSTANT("CONTEXT_LOST_WEBGL", CONTEXT_LOST_WEBGL);
  JS_GL_SET_CONSTANT("UNPACK_COLORSPACE_CONVERSION_WEBGL", UNPACK_COLORSPACE_CONVERSION_WEBGL);
  JS_GL_SET_CONSTANT("BROWSER_DEFAULT_WEBGL", BROWSER_DEFAULT_WEBGL);

  //////////////////////////////
  // NOT in WebGL spec
  //////////////////////////////

  // PBO
  JS_GL_SET_CONSTANT("PIXEL_PACK_BUFFER" , 0x88EB);
  JS_GL_SET_CONSTANT("PIXEL_UNPACK_BUFFER" , 0x88EC);
  JS_GL_SET_CONSTANT("PIXEL_PACK_BUFFER_BINDING" , 0x88ED);
  JS_GL_SET_CONSTANT("PIXEL_UNPACK_BUFFER_BINDING", 0x88EF);

  // external
  JS_GL_SET_CONSTANT("TEXTURE_EXTERNAL_OES", 0x8D65);

  Local<Function> ctorFn = ctor->GetFunction();
  return scope.Escape(ctorFn);
}

WebGLRenderingContext::WebGLRenderingContext() : live(true), windowHandle(nullptr), dirty(false), defaultFramebuffer(0), flipY(true), premultiplyAlpha(true), packAlignment(4), unpackAlignment(4) {}

WebGLRenderingContext::~WebGLRenderingContext() {}

NAN_METHOD(WebGLRenderingContext::New) {
  Nan::HandleScope scope;

  WebGLRenderingContext *gl = new WebGLRenderingContext();
  Local<Object> glObj = info.This();
  gl->Wrap(glObj);

  info.GetReturnValue().Set(glObj);
}

NAN_METHOD(WebGLRenderingContext::Destroy) {
  Nan::HandleScope scope;

  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
  gl->live = false;
}

NAN_METHOD(WebGLRenderingContext::GetWindowHandle) {
  Nan::HandleScope scope;

  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
  if (gl->windowHandle) {
    info.GetReturnValue().Set(pointerToArray(gl->windowHandle));
  } else {
    info.GetReturnValue().Set(Nan::Null());
  }
}

NAN_METHOD(WebGLRenderingContext::SetWindowHandle) {
  Nan::HandleScope scope;

  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
  if (info[0]->IsArray()) {
    gl->windowHandle = (GLFWwindow *)arrayToPointer(Local<Array>::Cast(info[0]));
  } else {
    gl->windowHandle = nullptr;
  }
}

NAN_METHOD(WebGLRenderingContext::IsDirty) {
  Nan::HandleScope scope;

  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
  info.GetReturnValue().Set(JS_BOOL(gl->dirty));
}

NAN_METHOD(WebGLRenderingContext::ClearDirty) {
  Nan::HandleScope scope;

  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
  gl->dirty = false;
}

// GL CALLS

// A 32-bit and 64-bit compatible way of converting a pointer to a GLuint.
static GLuint ToGLuint(const void* ptr) {
  return static_cast<GLuint>(reinterpret_cast<size_t>(ptr));
}

template<typename Type>
inline Type* getArrayData(Local<Value> arg, int* num = NULL) {
  Type *data=NULL;
  if (num) {
    *num = 0;
  }

  if (!arg->IsNull()) {
    if (arg->IsArrayBufferView()) {
      Local<ArrayBufferView> arr = Local<ArrayBufferView>::Cast(arg);
      if (num) {
        *num = arr->ByteLength()/sizeof(Type);
      }
      data = reinterpret_cast<Type*>((char *)arr->Buffer()->GetContents().Data() + arr->ByteOffset());
    } else {
      Nan::ThrowError("Bad array argument");
    }
  }

  return data;
}

inline void *getImageData(Local<Value> arg, int *num = nullptr) {
  void *pixels = nullptr;

  if (!arg->IsNull()) {
    Local<Object> obj = Local<Object>::Cast(arg);
    if (obj->IsObject()) {
      if (obj->IsArrayBufferView()) {
        pixels = getArrayData<unsigned char>(obj, num);
      } else {
        Local<String> dataString = String::NewFromUtf8(Isolate::GetCurrent(), "data", NewStringType::kInternalized).ToLocalChecked();
        if (obj->Has(dataString)) {
          Local<Value> data = obj->Get(dataString);
          pixels = getArrayData<unsigned char>(data, num);
        } else {
          Nan::ThrowError("Bad texture argument");
          // pixels = node::Buffer::Data(Nan::Get(obj, JS_STR("data")).ToLocalChecked());
        }
      }
    } else {
      Nan::ThrowError("Bad texture argument");
    }
  }
  return pixels;
}

inline void reformatImageData(char *dstData, char *srcData, size_t dstPixelSize, size_t srcPixelSize, size_t numPixels) {
  if (dstPixelSize < srcPixelSize) {
    // size_t clipSize = srcPixelSize - dstPixelSize;
    for (size_t i = 0; i < numPixels; i++) {
      memcpy(dstData + i * dstPixelSize, srcData + i * srcPixelSize, dstPixelSize);
      /* for (size_t j = 0; j < dstPixelSize; j++) {
        dstData[i * dstPixelSize + j] = srcData[i * srcPixelSize + srcPixelSize - clipSize - 1 - j];
      } */
      // memcpy(dstData + i * dstPixelSize, srcData + i * srcPixelSize + clipSize, dstPixelSize);
    }
  } else if (dstPixelSize > srcPixelSize) {
    size_t clipSize = dstPixelSize - srcPixelSize;
    for (size_t i = 0; i < numPixels; i++) {
      memcpy(dstData + i * dstPixelSize, srcData + i * srcPixelSize, srcPixelSize);
      memset(dstData + i * dstPixelSize + srcPixelSize, 0xFF, clipSize);
    }
  } else {
    // the call was pointless, but fulfill the contract anyway
    memcpy(dstData, srcData, dstPixelSize * numPixels);
  }
}

inline void flipImageData(char *dstData, char *srcData, size_t width, size_t height, size_t pixelSize) {
  size_t stride = width * pixelSize;
  size_t size = width * height * pixelSize;
  for (size_t i = 0; i < height; i++) {
    memcpy(dstData + (i * stride), srcData + size - stride - (i * stride), stride);
  }
}

NAN_METHOD(WebGLRenderingContext::Uniform1f) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  float x = (float)info[1]->NumberValue();

  glUniform1f(location, x);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform2f) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  float x = (float)info[1]->NumberValue();
  float y = (float)info[2]->NumberValue();

  glUniform2f(location, x, y);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform3f) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  float x = (float)info[1]->NumberValue();
  float y = (float)info[2]->NumberValue();
  float z = (float)info[3]->NumberValue();

  glUniform3f(location, x, y, z);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform4f) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  float x = (float)info[1]->NumberValue();
  float y = (float)info[2]->NumberValue();
  float z = (float)info[3]->NumberValue();
  float w = (float)info[4]->NumberValue();

  glUniform4f(location, x, y, z, w);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform1i) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int x = info[1]->Int32Value();

  glUniform1i(location, x);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform2i) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int x = info[1]->Int32Value();
  int y = info[2]->Int32Value();

  glUniform2i(location, x, y);

  // o.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform3i) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int x = info[1]->Int32Value();
  int y = info[2]->Int32Value();
  int z = info[3]->Int32Value();

  glUniform3i(location, x, y, z);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform4i) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int x = info[1]->Int32Value();
  int y = info[2]->Int32Value();
  int z = info[3]->Int32Value();
  int w = info[4]->Int32Value();

  glUniform4i(location, x, y, z, w);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform1fv) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int num;
  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    GLfloat *ptr = getArrayData<GLfloat>(float32Array, &num);
    glUniform1fv(location, num, ptr);
  } else {
    GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
    glUniform1fv(location, num, ptr);
  }
  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform2fv) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int num;
  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    GLfloat *ptr = getArrayData<GLfloat>(float32Array, &num);
    num /= 2;
    glUniform2fv(location, num, ptr);
  } else {
    GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
    num /= 2;
    glUniform2fv(location, num, ptr);
  }
  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform3fv) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int num;
  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    GLfloat *ptr = getArrayData<GLfloat>(float32Array, &num);
    num /= 3;
    glUniform3fv(location, num, ptr);
  } else {
    GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
    num /= 3;
    glUniform3fv(location, num, ptr);
  }
  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform4fv) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int num;
  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    GLfloat *ptr=getArrayData<GLfloat>(float32Array, &num);
    num /= 4;
    glUniform4fv(location, num, ptr);
  } else {
    GLfloat *ptr=getArrayData<GLfloat>(info[1], &num);
    num /= 4;
    glUniform4fv(location, num, ptr);
  }
  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform1iv) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int num;
  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Int32Array> int32Array = Int32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      int32Array->Set(i, array->Get(i));
    }
    GLint *ptr = getArrayData<GLint>(int32Array, &num);
    glUniform1iv(location, num, ptr);
  } else {
    GLint *ptr = getArrayData<GLint>(info[1], &num);
    glUniform1iv(location, num, ptr);
  }
  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform2iv) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int num;
  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Int32Array> int32Array = Int32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      int32Array->Set(i, array->Get(i));
    }
    GLint *ptr = getArrayData<GLint>(int32Array, &num);
    num /= 2;
    glUniform2iv(location, num, ptr);
  } else {
    GLint *ptr = getArrayData<GLint>(info[1], &num);
    num /= 2;
    glUniform2iv(location, num, ptr);
  }
  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform3iv) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int num;
  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Int32Array> int32Array = Int32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      int32Array->Set(i, array->Get(i));
    }
    GLint *ptr = getArrayData<GLint>(int32Array, &num);
    num /= 3;
    glUniform3iv(location, num, ptr);
  } else {
    GLint *ptr=getArrayData<GLint>(info[1], &num);
    num /= 3;
    glUniform3iv(location, num, ptr);
  }
  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Uniform4iv) {
  Nan::HandleScope scope;

  int location = info[0]->Int32Value();
  int num;
  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Int32Array> int32Array = Int32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      int32Array->Set(i, array->Get(i));
    }
    GLint *ptr = getArrayData<GLint>(int32Array, &num);
    num /= 4;
    glUniform4iv(location, num, ptr);
  } else {
    GLint *ptr = getArrayData<GLint>(info[1], &num);
    num /= 4;
    glUniform4iv(location, num, ptr);
  }
  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::PixelStorei) {
  Nan::HandleScope scope;

  int pname = info[0]->Int32Value();
  int param = info[1]->Int32Value();

  if (pname == UNPACK_FLIP_Y_WEBGL) {
    WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
    gl->flipY = (bool)param;
  } else if (pname == UNPACK_PREMULTIPLY_ALPHA_WEBGL) {
    WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
    gl->premultiplyAlpha = (bool)param;
  } else if (pname == GL_PACK_ALIGNMENT) {
    WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
    gl->packAlignment = param;
    glPixelStorei(pname, param);
  } else if (pname == GL_UNPACK_ALIGNMENT) {
    WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
    gl->unpackAlignment = param;
    glPixelStorei(pname, param);
  } else {
    glPixelStorei(pname, param);
  }

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::BindAttribLocation) {
  Nan::HandleScope scope;

  int program = info[0]->Int32Value();
  int index = info[1]->Int32Value();
  String::Utf8Value name(info[2]);

  glBindAttribLocation(program, index, *name);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::GetError) {
  Nan::HandleScope scope;

  GLint error = glGetError();

  info.GetReturnValue().Set(Nan::New<Integer>(error));
}


NAN_METHOD(WebGLRenderingContext::DrawArrays) {
  Nan::HandleScope scope;

  int mode = info[0]->Int32Value();
  int first = info[1]->Int32Value();
  int count = info[2]->Int32Value();

  glDrawArrays(mode, first, count);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DrawArraysInstancedANGLE) {
  Nan::HandleScope scope;

  int mode = info[0]->Int32Value();
  int first = info[1]->Int32Value();
  int count = info[2]->Int32Value();
  int primcount = info[3]->Int32Value();

  glDrawArraysInstanced(mode, first, count, primcount);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::UniformMatrix2fv) {
  Nan::HandleScope scope;

  GLint location = info[0]->Int32Value();
  GLboolean transpose = info[1]->BooleanValue();

  GLfloat *data;
  GLsizei count;
  // GLfloat* data=getArrayData<GLfloat>(info[2],&count);

  if (info[2]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[2]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    data = getArrayData<GLfloat>(float32Array, &count);
  } else {
    data = getArrayData<GLfloat>(info[2], &count);
  }

  if (count < 4) {
    Nan::ThrowError("Not enough data for UniformMatrix2fv");
  } else {
    count /= 4;
    glUniformMatrix2fv(location, count, transpose, data);

    // info.GetReturnValue().Set(Nan::Undefined());
  }
}

NAN_METHOD(WebGLRenderingContext::UniformMatrix3fv) {
  Nan::HandleScope scope;

  GLint location = info[0]->Int32Value();
  GLboolean transpose = info[1]->BooleanValue();

  GLfloat *data;
  GLsizei count;
  // GLfloat* data=getArrayData<GLfloat>(info[2],&count);

  if (info[2]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[2]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    data = getArrayData<GLfloat>(float32Array, &count);
  } else {
    data = getArrayData<GLfloat>(info[2], &count);
  }

  if (count < 9) {
    Nan::ThrowError("Not enough data for UniformMatrix3fv");
  }else{
    count /= 9;
    glUniformMatrix3fv(location, count, transpose, data);

    // info.GetReturnValue().Set(Nan::Undefined());
  }
}

NAN_METHOD(WebGLRenderingContext::UniformMatrix4fv) {
  Nan::HandleScope scope;

  GLint location = info[0]->Int32Value();
  GLboolean transpose = info[1]->BooleanValue();

  GLfloat *data;
  GLsizei count;
  // GLfloat* data=getArrayData<GLfloat>(info[2],&count);

  if (info[2]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[2]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    data = getArrayData<GLfloat>(float32Array, &count);
  } else {
    data = getArrayData<GLfloat>(info[2], &count);
  }

  if (count < 16) {
    Nan::ThrowError("Not enough data for UniformMatrix4fv");
  } else {
    count /= 16;
    glUniformMatrix4fv(location, count, transpose, data);

    // info.GetReturnValue().Set(Nan::Undefined());
  }
}

NAN_METHOD(WebGLRenderingContext::GenerateMipmap) {
  Nan::HandleScope scope;

  GLint target = info[0]->Int32Value();

  glGenerateMipmap(target);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::GetAttribLocation) {
  Nan::HandleScope scope;

  int program = info[0]->Int32Value();
  String::Utf8Value name(info[1]);

  GLint result = glGetAttribLocation(program, *name);

  info.GetReturnValue().Set(Nan::New<Number>(result));
}


NAN_METHOD(WebGLRenderingContext::DepthFunc) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glDepthFunc(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::Viewport) {
  Nan::HandleScope scope;

  int x = info[0]->Int32Value();
  int y = info[1]->Int32Value();
  int width = info[2]->Int32Value();
  int height = info[3]->Int32Value();

  glViewport(x, y, width, height);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::CreateShader) {
  Nan::HandleScope scope;

  GLint type = info[0]->Int32Value();
  /* #ifdef LOGGING
  cout<<"createShader "<<shader<<endl;
  #endif */
  // registerGLObj(GLOBJECT_TYPE_SHADER, shader);

  GLuint shaderId = glCreateShader(type);
  Local<Object> shaderObject = Nan::New<Object>();
  shaderObject->Set(JS_STR("id"), JS_INT(shaderId));

  info.GetReturnValue().Set(shaderObject);
}


NAN_METHOD(WebGLRenderingContext::ShaderSource) {
  Nan::HandleScope scope;

  GLint shaderId = info[0]->ToObject()->Get(JS_STR("id"))->Int32Value();
  String::Utf8Value code(info[1]);
  GLint length = code.length();

  const char* codes[] = {*code};
  const GLint lengths[] = {length};
  glShaderSource(shaderId, 1, codes, lengths);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::CompileShader) {
  Nan::HandleScope scope;

  GLint shaderId = info[0]->ToObject()->Get(JS_STR("id"))->Int32Value();
  glCompileShader(shaderId);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::FrontFace) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glFrontFace(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::SetDefaultFramebuffer) {
  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());

  GLuint framebuffer = info[0]->Uint32Value();
  gl->defaultFramebuffer = framebuffer;
}


NAN_METHOD(WebGLRenderingContext::GetShaderParameter) {
  Nan::HandleScope scope;

  GLint shaderId = info[0]->ToObject()->Get(JS_STR("id"))->Int32Value();
  GLint pname = info[1]->Int32Value();
  int value;
  switch (pname) {
    case GL_DELETE_STATUS:
    case GL_COMPILE_STATUS:
      glGetShaderiv(shaderId, pname, &value);
      info.GetReturnValue().Set(JS_BOOL(static_cast<bool>(value)));
      break;
    case GL_SHADER_TYPE:
      glGetShaderiv(shaderId, pname, &value);
      info.GetReturnValue().Set(JS_FLOAT(static_cast<unsigned long>(value)));
      break;
    case GL_INFO_LOG_LENGTH:
    case GL_SHADER_SOURCE_LENGTH:
      glGetShaderiv(shaderId, pname, &value);
      info.GetReturnValue().Set(JS_FLOAT(static_cast<long>(value)));
      break;
    default:
      Nan::ThrowTypeError("GetShaderParameter: Invalid Enum");
  }

  //info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::GetShaderInfoLog) {
  Nan::HandleScope scope;

  GLint shaderId = info[0]->ToObject()->Get(JS_STR("id"))->Int32Value();
  char Error[1024];
  int Len;

  glGetShaderInfoLog(shaderId, sizeof(Error), &Len, Error);

  info.GetReturnValue().Set(JS_STR(Error, Len));
}


NAN_METHOD(WebGLRenderingContext::CreateProgram) {
  Nan::HandleScope scope;

  GLuint program = glCreateProgram();
  /* #ifdef LOGGING
  cout<<"createProgram "<<program<<endl;
  #endif */
  // registerGLObj(GLOBJECT_TYPE_PROGRAM, program);

  info.GetReturnValue().Set(Nan::New<Number>(program));
}


NAN_METHOD(WebGLRenderingContext::AttachShader) {
  Nan::HandleScope scope;

  int program = info[0]->Int32Value();
  GLint shaderId = info[1]->ToObject()->Get(JS_STR("id"))->Int32Value();

  glAttachShader(program, shaderId);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::LinkProgram) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glLinkProgram(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::GetProgramParameter) {
  Nan::HandleScope scope;

  int program = info[0]->Int32Value();
  int pname = info[1]->Int32Value();
  int value;

  switch (pname) {
    case GL_DELETE_STATUS:
    case GL_LINK_STATUS:
    case GL_VALIDATE_STATUS:
      glGetProgramiv(program, pname, &value);
      info.GetReturnValue().Set(JS_BOOL(static_cast<bool>(value)));
      break;
    case GL_ATTACHED_SHADERS:
    case GL_ACTIVE_ATTRIBUTES:
    case GL_ACTIVE_UNIFORMS:
      glGetProgramiv(program, pname, &value);
      info.GetReturnValue().Set(JS_FLOAT(static_cast<long>(value)));
      break;
    default:
      Nan::ThrowTypeError("GetProgramParameter: Invalid Enum");
  }

  //info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::GetUniformLocation) {
  Nan::HandleScope scope;

  int program = info[0]->Int32Value();
  v8::String::Utf8Value name(info[1]);

  GLint location = glGetUniformLocation(program, *name);

  info.GetReturnValue().Set(JS_INT(location));
}


NAN_METHOD(WebGLRenderingContext::ClearColor) {
  Nan::HandleScope scope;

  float red = (float)info[0]->NumberValue();
  float green = (float)info[1]->NumberValue();
  float blue = (float)info[2]->NumberValue();
  float alpha = (float)info[3]->NumberValue();

  glClearColor(red, green, blue, alpha);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::ClearDepth) {
  Nan::HandleScope scope;

  GLfloat depth = info[0]->NumberValue();
  glClearDepthf(depth);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Disable) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glDisable(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Enable) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glEnable(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::CreateTexture) {
  Nan::HandleScope scope;

  GLuint texture;
  glGenTextures(1, &texture);
  /* #ifdef LOGGING
  cout<<"createTexture "<<texture<<endl;
  #endif */
  // registerGLObj(GLOBJECT_TYPE_TEXTURE, texture);
  info.GetReturnValue().Set(Nan::New<Number>(texture));
}


NAN_METHOD(WebGLRenderingContext::BindTexture) {
  Nan::HandleScope scope;

  int target = info[0]->Int32Value();
  int texture = info[1]->IsNull() ? 0 : info[1]->Int32Value();

  glBindTexture(target, texture);

  // info.GetReturnValue().Set(Nan::Undefined());
}

/* char texPixels[4096 * 4096 * 4];
NAN_METHOD(WebGLRenderingContext::FlipTextureData) {
  Nan::HandleScope scope;

  int num;
  char *pixels=(char*)getArrayData<BYTE>(info[0], &num);
  int width = info[1]->Int32Value();
  int height = info[2]->Int32Value();

  int elementSize = num / width / height;
  for (int y = 0; y < height; y++) {
    memcpy(&(texPixels[(height - 1 - y) * width * elementSize]), &pixels[y * width * elementSize], width * elementSize);
  }
  memcpy(pixels, texPixels, num);
} */

inline bool hasWidthHeight(Local<Value> &value) {
  MaybeLocal<Object> valueObject(Nan::To<Object>(value));
  if (!valueObject.IsEmpty()) {
    Local<String> widthString = Nan::New<String>("width", sizeof("width") - 1).ToLocalChecked();
    Local<String> heightString = Nan::New<String>("height", sizeof("height") - 1).ToLocalChecked();

    MaybeLocal<Number> widthValue(Nan::To<Number>(valueObject.ToLocalChecked()->Get(widthString)));
    MaybeLocal<Number> heightValue(Nan::To<Number>(valueObject.ToLocalChecked()->Get(heightString)));
    return !widthValue.IsEmpty() && !heightValue.IsEmpty();
  } else {
    return false;
  }
}

size_t getFormatSize(int format) {
  switch (format) {
    case GL_RED:
    case GL_RED_INTEGER:
    case GL_DEPTH_COMPONENT:
    case GL_LUMINANCE:
    case GL_ALPHA:
      return 1;
    case GL_RG:
    case GL_RG_INTEGER:
    case GL_DEPTH_STENCIL:
    case GL_LUMINANCE_ALPHA:
      return 2;
    case GL_RGB:
    case GL_RGB_INTEGER:
      return 3;
    case GL_RGBA:
    case GL_RGBA_INTEGER:
      return 4;
    default:
      return 4;
  }
}

size_t getTypeSize(int type) {
  switch (type) {
    case GL_UNSIGNED_BYTE:
    case GL_BYTE:
      return 1;
    case GL_UNSIGNED_SHORT:
    case GL_SHORT:
    case GL_HALF_FLOAT:
    case GL_UNSIGNED_SHORT_5_6_5:
    case GL_UNSIGNED_SHORT_4_4_4_4:
    case GL_UNSIGNED_SHORT_5_5_5_1:
      return 2;
    case GL_UNSIGNED_INT:
    case GL_INT:
    case GL_FLOAT:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
    case GL_UNSIGNED_INT_10F_11F_11F_REV:
    case GL_UNSIGNED_INT_5_9_9_9_REV:
    case GL_UNSIGNED_INT_24_8:
    case GL_FLOAT_32_UNSIGNED_INT_24_8_REV:
      return 4;
    default:
      return 4;
  }
}

int formatMap[] = {
  GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE,
  GL_RGBA8_SNORM, GL_RGBA, GL_BYTE,
  GL_RGBA4, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4,
  GL_RGB10_A2, GL_RGBA, GL_UNSIGNED_INT_2_10_10_10_REV,
  GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1,
  GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT,
  GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT_OES,
  GL_RGBA32F, GL_RGBA, GL_FLOAT,
  GL_RGBA8UI, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE,
  GL_RGBA8I, GL_RGBA_INTEGER, GL_BYTE,
  GL_RGBA16UI, GL_RGBA_INTEGER, GL_UNSIGNED_SHORT,
  GL_RGBA16I, GL_RGBA_INTEGER, GL_SHORT,
  GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT,
  GL_RGBA32I, GL_RGBA_INTEGER, GL_INT,
  GL_RGB10_A2UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT_2_10_10_10_REV,
  GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE,
  GL_RGB8_SNORM, GL_RGB, GL_BYTE,
  GL_RGB565, GL_RGB, GL_UNSIGNED_SHORT_5_6_5,
  GL_R11F_G11F_B10F, GL_RGB, GL_UNSIGNED_INT_10F_11F_11F_REV,
  GL_RGB9_E5, GL_RGB, GL_UNSIGNED_INT_5_9_9_9_REV,
  GL_RGB16F, GL_RGB, GL_HALF_FLOAT,
  GL_RGB16F, GL_RGB, GL_HALF_FLOAT_OES,
  GL_RGB32F, GL_RGB, GL_FLOAT,
  GL_RGB8UI, GL_RGB_INTEGER, GL_UNSIGNED_BYTE,
  GL_RGB8I, GL_RGB_INTEGER, GL_BYTE,
  GL_RGB16UI, GL_RGB_INTEGER, GL_UNSIGNED_SHORT,
  GL_RGB16I, GL_RGB_INTEGER, GL_SHORT,
  GL_RGB32UI, GL_RGB_INTEGER, GL_UNSIGNED_INT,
  GL_RGB32I, GL_RGB_INTEGER, GL_INT,
  GL_RG8, GL_RG, GL_UNSIGNED_BYTE,
  GL_RG8_SNORM, GL_RG, GL_BYTE,
  GL_RG16F, GL_RG, GL_HALF_FLOAT,
  GL_RG16F, GL_RG, GL_HALF_FLOAT_OES,
  GL_RG32F, GL_RG, GL_FLOAT,
  GL_RG8UI, GL_RG_INTEGER, GL_UNSIGNED_BYTE,
  GL_RG8I, GL_RG_INTEGER, GL_BYTE,
  GL_RG16UI, GL_RG_INTEGER, GL_UNSIGNED_SHORT,
  GL_RG16I, GL_RG_INTEGER, GL_SHORT,
  GL_RG32UI, GL_RG_INTEGER, GL_UNSIGNED_INT,
  GL_RG32I, GL_RG_INTEGER, GL_INT,
  GL_R8, GL_RED, GL_UNSIGNED_BYTE,
  GL_R8_SNORM, GL_RED, GL_BYTE,
  GL_R16F, GL_RED, GL_HALF_FLOAT,
  GL_R16F, GL_RED, GL_HALF_FLOAT_OES,
  GL_R32F, GL_RED, GL_FLOAT,
  GL_R8UI, GL_RED_INTEGER, GL_UNSIGNED_BYTE,
  GL_R8I, GL_RED_INTEGER, GL_BYTE,
  GL_R16UI, GL_RED_INTEGER, GL_UNSIGNED_SHORT,
  GL_R16I, GL_RED_INTEGER, GL_SHORT,
  GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT,
  GL_R32I, GL_RED_INTEGER, GL_INT,
};

int normalizeInternalFormat(int internalformat, int format, int type) {
  if (internalformat == GL_RED || internalformat == GL_RG || internalformat == GL_RGB || internalformat == GL_RGBA) {
    for (size_t i = 0; i < sizeof(formatMap)/3; i++) {
      int b = formatMap[i * 3 + 1];
      int c = formatMap[i * 3 + 2];
      if (format == b && type == c) {
        int a = formatMap[i * 3 + 0];
        internalformat = a;
        break;
      }
    }
  }
  return internalformat;
}

int getImageFormat(Local<Value> arg) {
  if (arg->IsArrayBufferView()) {
    return GL_RGBA;
  } else {
    Local<Value> constructorName = arg->ToObject()->Get(JS_STR("constructor"))->ToObject()->Get(JS_STR("name"));
    if (
      constructorName->StrictEquals(JS_STR("HTMLImageElement")) ||
      constructorName->StrictEquals(JS_STR("ImageData")) ||
      constructorName->StrictEquals(JS_STR("ImageBitmap")) ||
      constructorName->StrictEquals(JS_STR("HTMLCanvasElement"))
    ) {
      return GL_RGBA;
    } else if (constructorName->StrictEquals(JS_STR("HTMLVideoElement"))) {
      return GL_RGB;
    } else {
      return -1;
    }
  }
}

NAN_METHOD(WebGLRenderingContext::TexImage2D) {
  Isolate *isolate = Isolate::GetCurrent();

  Nan::HandleScope scope;

  Local<Value> target = info[0];
  Local<Value> level = info[1];
  Local<Value> internalformat = info[2];
  Local<Value> width = info[3];
  Local<Value> height = info[4];
  Local<Value> border = info[5];
  Local<Value> format = info[6];
  Local<Value> type = info[7];
  Local<Value> pixels = info[8];

  Local<String> widthString = String::NewFromUtf8(isolate, "width", NewStringType::kInternalized).ToLocalChecked();
  Local<String> heightString = String::NewFromUtf8(isolate, "height", NewStringType::kInternalized).ToLocalChecked();

  if (info.Length() == 6) {
    // width is now format, height is now type, and border is now pixels
    MaybeLocal<Number> targetNumber(Nan::To<Number>(target));
    MaybeLocal<Number> levelNumber(Nan::To<Number>(level));
    MaybeLocal<Number> internalformatNumber(Nan::To<Number>(internalformat));
    MaybeLocal<Number> widthNumber(Nan::To<Number>(width));
    MaybeLocal<Number> heightNumber(Nan::To<Number>(height));
    if (
      !targetNumber.IsEmpty() &&
      !levelNumber.IsEmpty() && !internalformatNumber.IsEmpty() &&
      !widthNumber.IsEmpty() && !heightNumber.IsEmpty() &&
      (border->IsNull() || hasWidthHeight(border))
    ) {
      pixels=border;
      /* if (pixels) {
        pixels = _getImageData(pixels);
      } */
      type=height;
      format=width;
      width = border->BooleanValue() ? border->ToObject()->Get(widthString) : Number::New(isolate, 1).As<Value>();
      height = border->BooleanValue() ? border->ToObject()->Get(heightString) : Number::New(isolate, 1).As<Value>();
      // return _texImage2D(target, level, internalformat, width, height, 0, format, type, pixels);
    } else {
      /* LOGI("Loaded string asset %d %d %d %d %d %d %d %d %d",
        target->TypeOf(isolate)->StrictEquals(numberString),
        level->TypeOf(isolate)->StrictEquals(numberString),
        internalformat->TypeOf(isolate)->StrictEquals(numberString),
        width->TypeOf(isolate)->StrictEquals(numberString),
        height->TypeOf(isolate)->StrictEquals(numberString),
        border->IsNull(), // 0
        !border->IsNull() && border->TypeOf(isolate)->StrictEquals(objectString), // 1
        !border->IsNull() && border->TypeOf(isolate)->StrictEquals(objectString) && border->ToObject()->Get(widthString)->TypeOf(isolate)->StrictEquals(numberString), // 0
        !border->IsNull() && border->TypeOf(isolate)->StrictEquals(objectString) && border->ToObject()->Get(heightString)->TypeOf(isolate)->StrictEquals(numberString) // 0
      ); */

      Nan::ThrowError("Expected texImage2D(number target, number level, number internalformat, number format, number type, Image pixels)");
      return;
    }
  } else if (info.Length() == 9) {
    MaybeLocal<Number> targetNumber(Nan::To<Number>(target));
    MaybeLocal<Number> levelNumber(Nan::To<Number>(level));
    MaybeLocal<Number> internalformatNumber(Nan::To<Number>(internalformat));
    MaybeLocal<Number> widthNumber(Nan::To<Number>(width));
    MaybeLocal<Number> heightNumber(Nan::To<Number>(height));
    MaybeLocal<Number> formatNumber(Nan::To<Number>(format));
    MaybeLocal<Number> typeNumber(Nan::To<Number>(type));
    if (
      !targetNumber.IsEmpty() &&
      !levelNumber.IsEmpty() && !internalformat.IsEmpty() &&
      !widthNumber.IsEmpty() && !heightNumber.IsEmpty() &&
      !formatNumber.IsEmpty() && !typeNumber.IsEmpty() &&
        (pixels->IsNull() || !Nan::To<Object>(pixels).IsEmpty())
    ) {
      /* if (pixels) {
        pixels = _getImageData(pixels);
      } */
      // return _texImage2D(target, level, internalformat, width, height, border, format, type, pixels);
    } else {
      Nan::ThrowError("Expected texImage2D(number target, number level, number internalformat, number width, number height, number border, number format, number type, ArrayBufferView pixels)");
      return;
    }
  } else {
    Nan::ThrowError("Bad texture argument");
    return;
  }

  int targetV = target->Int32Value();
  int levelV = level->Int32Value();
  int internalformatV = internalformat->Int32Value();
  int widthV = width->Int32Value();
  int heightV = height->Int32Value();
  int borderV = border->Int32Value();
  int formatV = format->Int32Value();
  int typeV = type->Int32Value();

  internalformatV = normalizeInternalFormat(internalformatV, formatV, typeV);

  // int num;
  char *pixelsV;

  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());

  if (pixels->IsNull()) {
    glTexImage2D(targetV, levelV, internalformatV, widthV, heightV, borderV, formatV, typeV, nullptr);
  } else if ((pixelsV = (char *)getImageData(pixels)) != nullptr) {
    size_t formatSize = getFormatSize(formatV);
    size_t typeSize = getTypeSize(typeV);
    size_t pixelSize = formatSize * typeSize;
    size_t srcFormatV = getImageFormat(pixels);
    size_t srcFormatSize = getFormatSize(srcFormatV);
    char *pixelsV2;
    unique_ptr<char[]> pixelsV2Buffer;
    bool needsReformat = formatSize != srcFormatSize;
    if (needsReformat) {
      pixelsV2Buffer.reset(new char[widthV * heightV * pixelSize]);
      pixelsV2 = pixelsV2Buffer.get();
      reformatImageData(pixelsV2, pixelsV, formatSize * typeSize, srcFormatSize * typeSize, widthV * heightV);

      glPixelStorei(GL_PACK_ALIGNMENT, 1);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    } else {
      pixelsV2 = pixelsV;
    }

    if (canvas::ImageData::getFlip() && gl->flipY && !pixels->IsArrayBufferView()) {
      unique_ptr<char[]> pixelsV3Buffer(new char[widthV * heightV * pixelSize]);

      flipImageData(pixelsV3Buffer.get(), pixelsV2, widthV, heightV, pixelSize);

      glTexImage2D(targetV, levelV, internalformatV, widthV, heightV, borderV, formatV, typeV, pixelsV3Buffer.get());
    } else {
      glTexImage2D(targetV, levelV, internalformatV, widthV, heightV, borderV, formatV, typeV, pixelsV2);
    }

    if (needsReformat) {
      glPixelStorei(GL_PACK_ALIGNMENT, gl->packAlignment);
      glPixelStorei(GL_UNPACK_ALIGNMENT, gl->unpackAlignment);
    }
  } else {
    Nan::ThrowError(String::Concat(JS_STR("Invalid texture argument: "), pixels->ToString()));
  }
}

NAN_METHOD(WebGLRenderingContext::CompressedTexImage2D) {
  Isolate *isolate = Isolate::GetCurrent();

  Nan::HandleScope scope;

  if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsNumber() && info[4]->IsNumber() && info[5]->IsNumber()) {
    char *dataV;
    size_t dataLengthV;
    if (info[6]->IsArrayBufferView()) {
      Local<ArrayBufferView> arrayBufferView = Local<ArrayBufferView>::Cast(info[6]);
      Local<ArrayBuffer> buffer = arrayBufferView->Buffer();
      dataV = (char *)buffer->GetContents().Data() + arrayBufferView->ByteOffset();
      dataLengthV = arrayBufferView->ByteLength();
    } else if (info[6]->IsNull()) {
      dataV = nullptr;
      dataLengthV = 0;
    } else {
      return Nan::ThrowError("compressedTexImage2D: invalid arguments");
    }

    Local<Value> target = info[0];
    Local<Value> level = info[1];
    Local<Value> internalformat = info[2];
    Local<Value> width = info[3];
    Local<Value> height = info[4];
    Local<Value> border = info[5];

    int targetV = target->Int32Value();
    int levelV = level->Int32Value();
    int internalformatV = internalformat->Int32Value();
    int widthV = width->Int32Value();
    int heightV = height->Int32Value();
    int borderV = border->Int32Value();

    glCompressedTexImage2D(targetV, levelV, internalformatV, widthV, heightV, borderV, dataLengthV, dataV);
  } else {
    Nan::ThrowError("compressedTexImage2D: invalid arguments");
  }
}

NAN_METHOD(WebGLRenderingContext::TexParameteri) {
  Nan::HandleScope scope;

  int target = info[0]->Int32Value();
  int pname = info[1]->Int32Value();
  int param = info[2]->Int32Value();

  glTexParameteri(target, pname, param);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::TexParameterf) {
  Nan::HandleScope scope;

  int target = info[0]->Int32Value();
  int pname = info[1]->Int32Value();
  float param = (float) info[2]->NumberValue();

  glTexParameterf(target, pname, param);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::Clear) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glClear(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::UseProgram) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glUseProgram(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::CreateBuffer) {
  Nan::HandleScope scope;

  GLuint buffer;
  glGenBuffers(1, &buffer);
  /* #ifdef LOGGING
  cout<<"createBuffer "<<buffer<<endl;
  #endif */
  // registerGLObj(GLOBJECT_TYPE_BUFFER, buffer);
  info.GetReturnValue().Set(Nan::New<Number>(buffer));
}

NAN_METHOD(WebGLRenderingContext::BindBuffer) {
  Nan::HandleScope scope;

  int target = info[0]->Int32Value();
  int buffer = info[1]->Uint32Value();

  glBindBuffer(target, buffer);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::CreateFramebuffer) {
  Nan::HandleScope scope;

  GLuint buffer;
  glGenFramebuffers(1, &buffer);
  /* #ifdef LOGGING
  cout<<"createFrameBuffer "<<buffer<<endl;
  #endif */
  // registerGLObj(GLOBJECT_TYPE_FRAMEBUFFER, buffer);
  info.GetReturnValue().Set(Nan::New<Number>(buffer));
}


NAN_METHOD(WebGLRenderingContext::BindFramebuffer) {
  Nan::HandleScope scope;

  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());

  int target = info[0]->Int32Value();
  int buffer = info[1]->IsNull() ?
    gl->defaultFramebuffer
  :
    info[1]->Int32Value();

  glBindFramebuffer(target, buffer);
}


NAN_METHOD(WebGLRenderingContext::FramebufferTexture2D) {
  Nan::HandleScope scope;

  int target = info[0]->Int32Value();
  int attachment = info[1]->Int32Value();
  int textarget = info[2]->Int32Value();
  int texture = info[3]->Int32Value();
  int level = info[4]->Int32Value();

  glFramebufferTexture2D(target, attachment, textarget, texture, level);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::BufferData) {
  Nan::HandleScope scope;

  int target = info[0]->Int32Value();
  if(info[1]->IsObject()) {
    Local<Object> obj = Local<Object>::Cast(info[1]);
    GLenum usage = info[2]->Int32Value();

    int element_size = 1;
    Local<ArrayBufferView> arr = Local<ArrayBufferView>::Cast(obj);
    int size = arr->ByteLength() * element_size;
    char *data = (char *)arr->Buffer()->GetContents().Data() + arr->ByteOffset();

    glBufferData(target, size, data, usage);
  } else if(info[1]->IsNumber()) {
    GLsizeiptr size = info[1]->Uint32Value();
    GLenum usage = info[2]->Int32Value();

    glBufferData(target, size, NULL, usage);
  }

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::BufferSubData) {
  Nan::HandleScope scope;

  int target = info[0]->Int32Value();
  int offset = info[1]->Int32Value();
  Local<Object> obj = Local<Object>::Cast(info[2]);

  int element_size = 1;
  Local<ArrayBufferView> arr = Local<ArrayBufferView>::Cast(obj);
  int size = arr->ByteLength() * element_size;
  char *data = (char *)arr->Buffer()->GetContents().Data() + arr->ByteOffset();

  glBufferSubData(target, offset, size, data);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::BlendEquation) {
  Nan::HandleScope scope;

  GLint mode = info[0]->Int32Value();
  glBlendEquation(mode);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::BlendFunc) {
  Nan::HandleScope scope;

  GLint sfactor = info[0]->Int32Value();
  GLint dfactor = info[1]->Int32Value();

  glBlendFunc(sfactor, dfactor);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::EnableVertexAttribArray) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glEnableVertexAttribArray(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::VertexAttribPointer) {
  Nan::HandleScope scope;

  int indx = info[0]->Int32Value();
  int size = info[1]->Int32Value();
  int type = info[2]->Int32Value();
  int normalized = info[3]->BooleanValue();
  int stride = info[4]->Int32Value();
  long offset = info[5]->Int32Value();

  //    printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
  glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid *)offset);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::ActiveTexture) {
  Nan::HandleScope scope;

  int arg = info[0]->Int32Value();
  glActiveTexture(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::DrawElements) {
  Nan::HandleScope scope;

  int mode = info[0]->Int32Value();
  int count = info[1]->Int32Value();
  int type = info[2]->Int32Value();
  GLvoid *offset = reinterpret_cast<GLvoid*>(info[3]->Uint32Value());

  glDrawElements(mode, count, type, offset);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DrawElementsInstancedANGLE) {
  Nan::HandleScope scope;

  int mode = info[0]->Int32Value();
  int count = info[1]->Int32Value();
  int type = info[2]->Int32Value();
  GLvoid *offset = reinterpret_cast<GLvoid*>(info[3]->Uint32Value());
  int primcount = info[4]->Int32Value();

  glDrawElementsInstanced(mode, count, type, offset, primcount);

  // info.GetReturnValue().Set(Nan::Undefined());
}


NAN_METHOD(WebGLRenderingContext::Flush) {
  // Nan::HandleScope scope;

  glFlush();

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Finish) {
  // Nan::HandleScope scope;

  glFinish();

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttrib1f) {
  Nan::HandleScope scope;

  GLuint indx = info[0]->Int32Value();
  GLfloat x = info[1]->NumberValue();

  glVertexAttrib1f(indx, x);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttrib2f) {
  Nan::HandleScope scope;

  GLuint indx = info[0]->Int32Value();
  float x = (float)info[1]->NumberValue();
  float y = (float)info[2]->NumberValue();

  glVertexAttrib2f(indx, x, y);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttrib3f) {
  Nan::HandleScope scope;

  GLuint indx = info[0]->Int32Value();
  float x = (float)info[1]->NumberValue();
  float y = (float)info[2]->NumberValue();
  float z = (float)info[3]->NumberValue();

  glVertexAttrib3f(indx, x, y, z);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttrib4f) {
  Nan::HandleScope scope;

  GLuint indx = info[0]->Int32Value();
  float x = (float)info[1]->NumberValue();
  float y = (float)info[2]->NumberValue();
  float z = (float)info[3]->NumberValue();
  float w = (float)info[4]->NumberValue();

  glVertexAttrib4f(indx, x, y, z, w);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttrib1fv) {
  Nan::HandleScope scope;

  int indx = info[0]->Int32Value();
  GLfloat *data;
  int num;
  // GLfloat *data = getArrayData<GLfloat>(info[1]);

  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    data = getArrayData<GLfloat>(float32Array, &num);
  } else {
    data = getArrayData<GLfloat>(info[1], &num);
  }

  glVertexAttrib1fv(indx, data);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttrib2fv) {
  Nan::HandleScope scope;

  int indx = info[0]->Int32Value();
  GLfloat *data;
  int num;
  // GLfloat *data = getArrayData<GLfloat>(info[1]);

  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    data=getArrayData<GLfloat>(float32Array, &num);
  } else {
    data=getArrayData<GLfloat>(info[1], &num);
  }

  glVertexAttrib2fv(indx, data);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttrib3fv) {
  Nan::HandleScope scope;

  int indx = info[0]->Int32Value();
  GLfloat *data;
  int num;
  // GLfloat *data = getArrayData<GLfloat>(info[1]);

  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    data = getArrayData<GLfloat>(float32Array, &num);
  } else {
    data = getArrayData<GLfloat>(info[1], &num);
  }

  glVertexAttrib3fv(indx, data);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttrib4fv) {
  Nan::HandleScope scope;

  int indx = info[0]->Int32Value();
  GLfloat *data;
  int num;
  // GLfloat *data = getArrayData<GLfloat>(info[1]);

  if (info[1]->IsArray()) {
    Local<Array> array = Local<Array>::Cast(info[1]);
    unsigned int length = array->Length();
    Local<Float32Array> float32Array = Float32Array::New(ArrayBuffer::New(Isolate::GetCurrent(), length * 4), 0, length);
    for (unsigned int i = 0; i < length; i++) {
      float32Array->Set(i, array->Get(i));
    }
    data=getArrayData<GLfloat>(float32Array, &num);
  } else {
    data=getArrayData<GLfloat>(info[1], &num);
  }

  glVertexAttrib4fv(indx, data);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::VertexAttribDivisorANGLE) {
  Nan::HandleScope scope;

  unsigned int index = info[0]->Uint32Value();
  unsigned int divisor = info[1]->Uint32Value();

  glVertexAttribDivisor(index, divisor);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DrawBuffersWEBGL) {
  Nan::HandleScope scope;

  Local<Array> buffersArray = Local<Array>::Cast(info[0]);
  GLenum buffers[32];
  size_t numBuffers = std::min<size_t>(buffersArray->Length(), sizeof(buffers)/sizeof(buffers[0]));
  for (size_t i = 0; i < numBuffers; i++) {
    buffers[i] = buffersArray->Get(i)->Uint32Value();
  }

  glDrawBuffers(numBuffers, buffers);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::BlendColor) {
  Nan::HandleScope scope;

  GLclampf r = (float)info[0]->NumberValue();
  GLclampf g = (float)info[1]->NumberValue();
  GLclampf b = (float)info[2]->NumberValue();
  GLclampf a = (float)info[3]->NumberValue();

  glBlendColor(r, g, b, a);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::BlendEquationSeparate) {
  Nan::HandleScope scope;

  GLenum modeRGB = info[0]->Int32Value();
  GLenum modeAlpha = info[1]->Int32Value();

  glBlendEquationSeparate(modeRGB, modeAlpha);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::BlendFuncSeparate) {
  Nan::HandleScope scope;

  GLenum srcRGB = info[0]->Int32Value();
  GLenum dstRGB = info[1]->Int32Value();
  GLenum srcAlpha = info[2]->Int32Value();
  GLenum dstAlpha = info[3]->Int32Value();

  glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::ClearStencil) {
  Nan::HandleScope scope;

  GLint s = info[0]->Int32Value();

  glClearStencil(s);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::ColorMask) {
  Nan::HandleScope scope;

  GLboolean r = info[0]->BooleanValue();
  GLboolean g = info[1]->BooleanValue();
  GLboolean b = info[2]->BooleanValue();
  GLboolean a = info[3]->BooleanValue();

  glColorMask(r, g, b, a);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::CopyTexImage2D) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLint level = info[1]->Int32Value();
  GLenum internalformat = info[2]->Int32Value();
  GLint x = info[3]->Int32Value();
  GLint y = info[4]->Int32Value();
  GLsizei width = info[5]->Int32Value();
  GLsizei height = info[6]->Int32Value();
  GLint border = info[7]->Int32Value();

  glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::CopyTexSubImage2D) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLint level = info[1]->Int32Value();
  GLint xoffset = info[2]->Int32Value();
  GLint yoffset = info[3]->Int32Value();
  GLint x = info[4]->Int32Value();
  GLint y = info[5]->Int32Value();
  GLsizei width = info[6]->Int32Value();
  GLsizei height = info[7]->Int32Value();

  glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::CullFace) {
  Nan::HandleScope scope;

  GLenum mode = info[0]->Int32Value();

  glCullFace(mode);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DepthMask) {
  Nan::HandleScope scope;

  GLboolean flag = info[0]->BooleanValue();

  glDepthMask(flag);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DepthRange) {
  Nan::HandleScope scope;

  GLclampf zNear = (float) info[0]->NumberValue();
  GLclampf zFar = (float) info[1]->NumberValue();

  glDepthRangef(zNear, zFar);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DisableVertexAttribArray) {
  Nan::HandleScope scope;

  GLuint index = info[0]->Int32Value();

  glDisableVertexAttribArray(index);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Hint) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLenum mode = info[1]->Int32Value();

  glHint(target, mode);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::IsEnabled) {
  Nan::HandleScope scope;

  GLenum cap = info[0]->Int32Value();
  bool ret = glIsEnabled(cap) != 0;

  info.GetReturnValue().Set(Nan::New<Boolean>(ret));
}

NAN_METHOD(WebGLRenderingContext::LineWidth) {
  Nan::HandleScope scope;

  GLfloat width = (float) info[0]->NumberValue();
  glLineWidth(width);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::PolygonOffset) {
  Nan::HandleScope scope;

  GLfloat factor = (float) info[0]->NumberValue();
  GLfloat units = (float) info[1]->NumberValue();

  glPolygonOffset(factor, units);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::SampleCoverage) {
  Nan::HandleScope scope;

  GLclampf value = info[0]->NumberValue();
  GLboolean invert = info[1]->BooleanValue();

  glSampleCoverage(value, invert);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::Scissor) {
  Nan::HandleScope scope;

  GLint x = info[0]->Int32Value();
  GLint y = info[1]->Int32Value();
  GLsizei width = info[2]->Int32Value();
  GLsizei height = info[3]->Int32Value();

  glScissor(x, y, width, height);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::StencilFunc) {
  Nan::HandleScope scope;

  GLenum func = info[0]->Int32Value();
  GLint ref = info[1]->Int32Value();
  GLuint mask = info[2]->Int32Value();

  glStencilFunc(func, ref, mask);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::StencilFuncSeparate) {
  Nan::HandleScope scope;

  GLenum face = info[0]->Int32Value();
  GLenum func = info[1]->Int32Value();
  GLint ref = info[2]->Int32Value();
  GLuint mask = info[3]->Int32Value();

  glStencilFuncSeparate(face, func, ref, mask);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::StencilMask) {
  Nan::HandleScope scope;

  GLuint mask = info[0]->Uint32Value();

  glStencilMask(mask);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::StencilMaskSeparate) {
  Nan::HandleScope scope;

  GLenum face = info[0]->Int32Value();
  GLuint mask = info[1]->Uint32Value();

  glStencilMaskSeparate(face, mask);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::StencilOp) {
  Nan::HandleScope scope;

  GLenum fail = info[0]->Int32Value();
  GLenum zfail = info[1]->Int32Value();
  GLenum zpass = info[2]->Int32Value();

  glStencilOp(fail, zfail, zpass);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::StencilOpSeparate) {
  Nan::HandleScope scope;

  GLenum face = info[0]->Int32Value();
  GLenum fail = info[1]->Int32Value();
  GLenum zfail = info[2]->Int32Value();
  GLenum zpass = info[3]->Int32Value();

  glStencilOpSeparate(face, fail, zfail, zpass);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::BindRenderbuffer) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLuint buffer = info[1]->IsNull() ? 0 : info[1]->Int32Value();

  glBindRenderbuffer(target, buffer);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::CreateRenderbuffer) {
  Nan::HandleScope scope;

  GLuint renderbuffers;
  glGenRenderbuffers(1, &renderbuffers);
  /* #ifdef LOGGING
  cout<<"createRenderBuffer "<<renderbuffers<<endl;
  #endif */
  // registerGLObj(GLOBJECT_TYPE_RENDERBUFFER, renderbuffers);

  info.GetReturnValue().Set(Nan::New<Number>(renderbuffers));
}

NAN_METHOD(WebGLRenderingContext::DeleteBuffer) {
  Nan::HandleScope scope;

  GLuint buffer = info[0]->Uint32Value();

  glDeleteBuffers(1, &buffer);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DeleteFramebuffer) {
  Nan::HandleScope scope;

  GLuint buffer = info[0]->Uint32Value();

  glDeleteFramebuffers(1, &buffer);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DeleteProgram) {
  Nan::HandleScope scope;

  GLuint program = info[0]->Uint32Value();

  glDeleteProgram(program);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DeleteRenderbuffer) {
  Nan::HandleScope scope;

  GLuint renderbuffer = info[0]->Uint32Value();

  glDeleteRenderbuffers(1, &renderbuffer);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DeleteShader) {
  Nan::HandleScope scope;

  GLint shaderId = info[0]->ToObject()->Get(JS_STR("id"))->Int32Value();

  glDeleteShader(shaderId);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DeleteTexture) {
  Nan::HandleScope scope;

  GLuint texture = info[0]->Uint32Value();

  glDeleteTextures(1, &texture);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::DetachShader) {
  Nan::HandleScope scope;

  GLuint program = info[0]->Uint32Value();
  GLint shaderId = info[1]->ToObject()->Get(JS_STR("id"))->Int32Value();

  glDetachShader(program, shaderId);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::FramebufferRenderbuffer) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLenum attachment = info[1]->Int32Value();
  GLenum renderbuffertarget = info[2]->Int32Value();
  GLuint renderbuffer = info[3]->Uint32Value();

  glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::GetVertexAttribOffset) {
  Nan::HandleScope scope;

  GLuint index = info[0]->Uint32Value();
  GLenum pname = info[1]->Int32Value();
  void *ret = nullptr;

  glGetVertexAttribPointerv(index, pname, &ret);

  info.GetReturnValue().Set(JS_INT(ToGLuint(ret)));
}

NAN_METHOD(WebGLRenderingContext::IsBuffer) {
  Nan::HandleScope scope;

  GLuint arg = info[0]->Uint32Value();
  bool ret = glIsBuffer(arg) != 0;

  info.GetReturnValue().Set(Nan::New<Boolean>(ret));
}

NAN_METHOD(WebGLRenderingContext::IsFramebuffer) {
  Nan::HandleScope scope;

  GLuint arg = info[0]->Uint32Value();
  bool ret = glIsFramebuffer(arg) != 0;

  info.GetReturnValue().Set(JS_BOOL(ret));
}

NAN_METHOD(WebGLRenderingContext::IsProgram) {
  Nan::HandleScope scope;

  GLuint arg = info[0]->Uint32Value();
  bool ret = glIsProgram(arg) != 0;

  info.GetReturnValue().Set(JS_BOOL(ret));
}

NAN_METHOD(WebGLRenderingContext::IsRenderbuffer) {
  Nan::HandleScope scope;

  GLuint arg = info[0]->Uint32Value();
  bool ret = glIsRenderbuffer(arg) != 0;

  info.GetReturnValue().Set(JS_BOOL(ret));
}

NAN_METHOD(WebGLRenderingContext::IsShader) {
  Nan::HandleScope scope;

  MaybeLocal<Object> arg = Nan::To<Object>(info[0]);
  if (!arg.IsEmpty()) {
    GLint shaderId = arg.ToLocalChecked()->Get(JS_STR("id"))->Int32Value();

    bool ret = glIsShader(shaderId) != 0;

    info.GetReturnValue().Set(JS_BOOL(ret));
  } else {
    info.GetReturnValue().Set(JS_BOOL(false));
  }
}

NAN_METHOD(WebGLRenderingContext::IsTexture) {
  Nan::HandleScope scope;

  GLuint arg = info[0]->Uint32Value();
  bool ret = glIsTexture(arg) != 0;

  info.GetReturnValue().Set(JS_BOOL(ret));
}

NAN_METHOD(WebGLRenderingContext::RenderbufferStorage) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLenum internalformat = info[1]->Int32Value();
  GLsizei width = info[2]->Uint32Value();
  GLsizei height = info[3]->Uint32Value();

  glRenderbufferStorage(target, internalformat, width, height);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::GetShaderSource) {
  Nan::HandleScope scope;

  GLint shaderId = info[0]->ToObject()->Get(JS_STR("id"))->Int32Value();

  GLint len;
  glGetShaderiv(shaderId, GL_SHADER_SOURCE_LENGTH, &len);
  GLchar *source = new GLchar[len];

  glGetShaderSource(shaderId, len, nullptr, source);

  Local<String> str = JS_STR(source, len);
  delete[] source;

  info.GetReturnValue().Set(str);
}

NAN_METHOD(WebGLRenderingContext::ValidateProgram) {
  Nan::HandleScope scope;

  GLint arg = info[0]->Int32Value();
  glValidateProgram(arg);

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::TexSubImage2D) {
  Nan::HandleScope scope;

  GLenum targetV = info[0]->Int32Value();
  GLint levelV = info[1]->Int32Value();
  GLint xoffsetV = info[2]->Int32Value();
  GLint yoffsetV = info[3]->Int32Value();
  GLsizei widthV = info[4]->Int32Value();
  GLsizei heightV = info[5]->Int32Value();
  GLenum formatV = info[6]->Int32Value();
  GLenum typeV = info[7]->Int32Value();
  Local<Value> pixels = info[8];

  // int num;
  char *pixelsV;

  WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());

  if (pixels->IsNull()) {
    glTexSubImage2D(targetV, levelV, xoffsetV, yoffsetV, widthV, heightV, formatV, typeV, nullptr);
  } else if ((pixelsV = (char *)getImageData(pixels)) != nullptr) {
    size_t formatSize = getFormatSize(formatV);
    size_t typeSize = getTypeSize(typeV);
    size_t pixelSize = formatSize * typeSize;
    char *pixelsV2;
    unique_ptr<char[]> pixelsV2Buffer;
    if (formatSize != 4 && !pixels->IsArrayBufferView()) {
      pixelsV2Buffer.reset(new char[widthV * heightV * pixelSize]);
      pixelsV2 = pixelsV2Buffer.get();
      reformatImageData(pixelsV2, pixelsV, formatSize * typeSize, 4 * typeSize, widthV * heightV);
    } else {
      pixelsV2 = pixelsV;
    }

    if (canvas::ImageData::getFlip() && gl->flipY && !pixels->IsArrayBufferView()) {
      unique_ptr<char[]> pixelsV3Buffer(new char[widthV * heightV * pixelSize]);
      flipImageData(pixelsV3Buffer.get(), pixelsV2, widthV, heightV, pixelSize);

      glTexSubImage2D(targetV, levelV, xoffsetV, yoffsetV, widthV, heightV, formatV, typeV, pixelsV3Buffer.get());
    } else {
      glTexSubImage2D(targetV, levelV, xoffsetV, yoffsetV, widthV, heightV, formatV, typeV, pixelsV2);
    }
  } else {
    Nan::ThrowError("Invalid texture argument");
  }

  /* if (pixels != nullptr) {
    int elementSize = num / width / height;
    for (int y = 0; y < height; y++) {
      memcpy(&(texPixels[(height - 1 - y) * width * elementSize]), &pixels[y * width * elementSize], width * elementSize);
    }
  } */
}

NAN_METHOD(WebGLRenderingContext::ReadPixels) {
  Nan::HandleScope scope;

  GLint x = info[0]->Int32Value();
  GLint y = info[1]->Int32Value();
  GLsizei width = info[2]->Int32Value();
  GLsizei height = info[3]->Int32Value();
  GLenum format = info[4]->Int32Value();
  GLenum type = info[5]->Int32Value();
  char *pixels = (char *)getImageData(info[6]);

  if (pixels != nullptr) {
    glReadPixels(x, y, width, height, format, type, pixels);
  } else {
    Nan::ThrowError("Invalid texture argument");
  }

  // info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::GetTexParameter) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLenum pname = info[1]->Int32Value();
  GLint value;

  glGetTexParameteriv(target, pname, &value);

  info.GetReturnValue().Set(Nan::New<Number>(value));
}

NAN_METHOD(WebGLRenderingContext::GetActiveAttrib) {
  Nan::HandleScope scope;

  GLuint program = info[0]->Int32Value();
  GLuint index = info[1]->Int32Value();

  char name[1024];
  GLsizei length = 0;
  GLsizei size;
  GLenum type;

  glGetActiveAttrib(program, index, sizeof(name), &length, &size, &type, name);

  if (length > 0) {
    Local<Object> activeInfo = Nan::New<Object>();
    activeInfo->Set(JS_STR("size"), JS_INT(size));
    activeInfo->Set(JS_STR("type"), JS_INT((int)type));
    activeInfo->Set(JS_STR("name"), JS_STR(name, length));

    info.GetReturnValue().Set(activeInfo);
  } else {
    info.GetReturnValue().Set(Nan::Null());
  }
}

NAN_METHOD(WebGLRenderingContext::GetActiveUniform) {
  Nan::HandleScope scope;

  GLuint program = info[0]->Int32Value();
  GLuint index = info[1]->Int32Value();

  char name[1024];
  GLsizei length = 0;
  GLsizei size;
  GLenum type;

  glGetActiveUniform(program, index, sizeof(name), &length, &size, &type, name);

  if (length > 0) {
    Local<Object> activeInfo = Nan::New<Object>();
    activeInfo->Set(JS_STR("size"), JS_INT(size));
    activeInfo->Set(JS_STR("type"), JS_INT((int)type));
    activeInfo->Set(JS_STR("name"), JS_STR(name, length));

    info.GetReturnValue().Set(activeInfo);
  } else {
    info.GetReturnValue().Set(Nan::Null());
  }
}

NAN_METHOD(WebGLRenderingContext::GetAttachedShaders) {
  Nan::HandleScope scope;

  GLuint program = info[0]->Int32Value();
  GLuint shaders[1024];
  GLsizei count;

  glGetAttachedShaders(program, sizeof(shaders) / sizeof(shaders[0]), &count, shaders);

  Local<Array> shadersArr = Nan::New<Array>(count);
  for(int i = 0; i < count; i++) {
    Local<Object> shaderObject = Nan::New<Object>();
    shaderObject->Set(JS_STR("id"), JS_INT(shaders[i]));
    shadersArr->Set(i, shaderObject);
  }

  info.GetReturnValue().Set(shadersArr);
}

NAN_METHOD(WebGLRenderingContext::GetParameter) {
  Nan::HandleScope scope;

  GLenum name = info[0]->Int32Value();

  switch (name) {
    case GL_BLEND:
    case GL_CULL_FACE:
    case GL_DEPTH_TEST:
    case GL_DEPTH_WRITEMASK:
    case GL_DITHER:
    case GL_POLYGON_OFFSET_FILL:
    case GL_SAMPLE_COVERAGE_INVERT:
    case GL_SCISSOR_TEST:
    case GL_STENCIL_TEST:
    {
      // return a boolean
      GLboolean params;
      glGetBooleanv(name, &params);
      info.GetReturnValue().Set(JS_BOOL(static_cast<bool>(params)));
      break;
    }
    case GL_ACTIVE_TEXTURE:
    case GL_ALPHA_BITS:
    case GL_BLEND_DST_ALPHA:
    case GL_BLEND_DST_RGB:
    case GL_BLEND_EQUATION:
    case GL_BLEND_EQUATION_ALPHA:
    // case GL_BLEND_EQUATION_RGB: // === GL_BLEND_EQUATION
    case GL_BLEND_SRC_ALPHA:
    case GL_BLEND_SRC_RGB:
    case GL_BLUE_BITS:
    case GL_CULL_FACE_MODE:
    case GL_DEPTH_BITS:
    case GL_DEPTH_FUNC:
    case GL_FRONT_FACE:
    case GL_GENERATE_MIPMAP_HINT:
    case GL_GREEN_BITS:
    case GL_IMPLEMENTATION_COLOR_READ_FORMAT:
    case GL_IMPLEMENTATION_COLOR_READ_TYPE:
    case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
    case GL_MAX_CUBE_MAP_TEXTURE_SIZE:
    case GL_MAX_FRAGMENT_UNIFORM_VECTORS:
    case GL_MAX_RENDERBUFFER_SIZE:
    case GL_MAX_TEXTURE_IMAGE_UNITS:
    case GL_MAX_TEXTURE_SIZE:
    case GL_MAX_VARYING_VECTORS:
    case GL_MAX_VERTEX_ATTRIBS:
    case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:
    case GL_MAX_VERTEX_UNIFORM_VECTORS:
    case GL_PACK_ALIGNMENT:
    case GL_RED_BITS:
    case GL_SAMPLE_BUFFERS:
    case GL_SAMPLES:
    case GL_STENCIL_BACK_FAIL:
    case GL_STENCIL_BACK_FUNC:
    case GL_STENCIL_BACK_PASS_DEPTH_FAIL:
    case GL_STENCIL_BACK_PASS_DEPTH_PASS:
    case GL_STENCIL_BACK_REF:
    case GL_STENCIL_BACK_VALUE_MASK:
    case GL_STENCIL_BACK_WRITEMASK:
    case GL_STENCIL_BITS:
    case GL_STENCIL_CLEAR_VALUE:
    case GL_STENCIL_FAIL:
    case GL_STENCIL_FUNC:
    case GL_STENCIL_PASS_DEPTH_FAIL:
    case GL_STENCIL_PASS_DEPTH_PASS:
    case GL_STENCIL_REF:
    case GL_STENCIL_VALUE_MASK:
    case GL_STENCIL_WRITEMASK:
    case GL_SUBPIXEL_BITS:
    case GL_UNPACK_ALIGNMENT:
    case UNPACK_COLORSPACE_CONVERSION_WEBGL:
    {
      // return an int
      GLint param;
      glGetIntegerv(name, &param);
      info.GetReturnValue().Set(JS_INT(param));
      break;
    }
    case GL_DEPTH_CLEAR_VALUE:
    case GL_LINE_WIDTH:
    case GL_POLYGON_OFFSET_FACTOR:
    case GL_POLYGON_OFFSET_UNITS:
    case GL_SAMPLE_COVERAGE_VALUE:
    case GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT:
    {
      // return a float
      GLfloat params;
      glGetFloatv(name, &params);
      info.GetReturnValue().Set(JS_FLOAT(params));
      break;
    }
    case GL_RENDERER:
    case GL_SHADING_LANGUAGE_VERSION:
    case GL_VENDOR:
    case GL_EXTENSIONS:
    {
      // return a string
      char * params = (char *)glGetString(name);

      if (params != NULL) {
        info.GetReturnValue().Set(JS_STR(params));
      } else {
        info.GetReturnValue().Set(Nan::Undefined());
      }

      break;
    }
    case GL_VERSION:
    {
      info.GetReturnValue().Set(JS_STR("WebGL 1"));

      break;
    }
    case GL_MAX_VIEWPORT_DIMS:
    {
      // return a int32[2]
      GLint params[2];
      glGetIntegerv(name, params);

      Local<Array> arr = Nan::New<Array>(2);
      arr->Set(0,JS_INT(params[0]));
      arr->Set(1,JS_INT(params[1]));
      info.GetReturnValue().Set(arr);
      break;
    }
    case GL_SCISSOR_BOX:
    case GL_VIEWPORT:
    {
      // return a int32[4]
      GLint params[4];
      glGetIntegerv(name, params);

      Local<Array> arr = Nan::New<Array>(4);
      arr->Set(0,JS_INT(params[0]));
      arr->Set(1,JS_INT(params[1]));
      arr->Set(2,JS_INT(params[2]));
      arr->Set(3,JS_INT(params[3]));
      info.GetReturnValue().Set(arr);
      break;
    }
    case GL_ALIASED_LINE_WIDTH_RANGE:
    case GL_ALIASED_POINT_SIZE_RANGE:
    case GL_DEPTH_RANGE:
    {
      // return a float[2]
      GLfloat params[2];
      glGetFloatv(name, params);

      Local<Array> arr = Nan::New<Array>(2);
      arr->Set(0,JS_FLOAT(params[0]));
      arr->Set(1,JS_FLOAT(params[1]));
      info.GetReturnValue().Set(arr);
      break;
    }
    case GL_BLEND_COLOR:
    case GL_COLOR_CLEAR_VALUE:
    {
      // return a float[4]
      GLfloat params[4];
      glGetFloatv(name, params);

      Local<Array> arr = Nan::New<Array>(4);
      arr->Set(0,JS_FLOAT(params[0]));
      arr->Set(1,JS_FLOAT(params[1]));
      arr->Set(2,JS_FLOAT(params[2]));
      arr->Set(3,JS_FLOAT(params[3]));
      info.GetReturnValue().Set(arr);
      break;
    }
    case GL_COLOR_WRITEMASK:
    {
      // return a boolean[4]
      GLboolean params[4];
      glGetBooleanv(name, params);

      Local<Array> arr = Nan::New<Array>(4);
      arr->Set(0,JS_BOOL(params[0]==1));
      arr->Set(1,JS_BOOL(params[1]==1));
      arr->Set(2,JS_BOOL(params[2]==1));
      arr->Set(3,JS_BOOL(params[3]==1));
      info.GetReturnValue().Set(arr);
      break;
    }
    case GL_ARRAY_BUFFER_BINDING:
    case GL_CURRENT_PROGRAM:
    case GL_ELEMENT_ARRAY_BUFFER_BINDING:
    case GL_FRAMEBUFFER_BINDING:
    case GL_RENDERBUFFER_BINDING:
    case GL_TEXTURE_BINDING_2D:
    case GL_TEXTURE_BINDING_CUBE_MAP:
    {
      GLint params;
      glGetIntegerv(name, &params);

      info.GetReturnValue().Set(JS_INT(params));
      break;
    }
    case GL_COMPRESSED_TEXTURE_FORMATS:
    {
      GLint numFormats;
      glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numFormats);

      unique_ptr<GLint[]> params(new GLint[numFormats]);
      glGetIntegerv(name, params.get());

      Local<Array> arr = Nan::New<Array>(numFormats);
      for (size_t i = 0; i < numFormats; i++) {
        arr->Set(i, JS_INT(params[i]));
      }
      info.GetReturnValue().Set(arr);
      break;
    }
    case UNPACK_FLIP_Y_WEBGL: {
      WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
      // return a boolean
      GLboolean params;
      glGetBooleanv(name, &params);
      info.GetReturnValue().Set(JS_BOOL(gl->flipY));
      break;
    }
    case UNPACK_PREMULTIPLY_ALPHA_WEBGL: {
      WebGLRenderingContext *gl = ObjectWrap::Unwrap<WebGLRenderingContext>(info.This());
      // return a boolean
      GLboolean params;
      glGetBooleanv(name, &params);
      info.GetReturnValue().Set(JS_BOOL(gl->premultiplyAlpha));
      break;
    }
    default: {
      /* // return a long
      GLint params;
      glGetIntegerv(name, &params);

      info.GetReturnValue().Set(JS_INT(params)); */
      Nan::ThrowError("invalid arguments");
      break;
    }
  }

  //info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::GetBufferParameter) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLenum pname = info[1]->Int32Value();
  GLint params;

  glGetBufferParameteriv(target, pname, &params);

  info.GetReturnValue().Set(JS_INT(params));
}

NAN_METHOD(WebGLRenderingContext::GetFramebufferAttachmentParameter) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLenum attachment = info[1]->Int32Value();
  GLenum pname = info[2]->Int32Value();
  GLint params;

  glGetFramebufferAttachmentParameteriv(target,attachment, pname, &params);

  info.GetReturnValue().Set(JS_INT(params));
}

NAN_METHOD(WebGLRenderingContext::GetProgramInfoLog) {
  Nan::HandleScope scope;

  GLuint program = info[0]->Int32Value();
  char Error[1024];
  int Len;

  glGetProgramInfoLog(program, sizeof(Error), &Len, Error);

  info.GetReturnValue().Set(JS_STR(Error, Len));
}

NAN_METHOD(WebGLRenderingContext::GetRenderbufferParameter) {
  Nan::HandleScope scope;

  int target = info[0]->Int32Value();
  int pname = info[1]->Int32Value();
  int value;

  glGetRenderbufferParameteriv(target, pname, &value);

  info.GetReturnValue().Set(JS_INT(value));
}

NAN_METHOD(WebGLRenderingContext::GetUniform) {
  Nan::HandleScope scope;

  GLuint program = info[0]->Int32Value();
  GLint location = info[1]->Int32Value();
  if (location < 0) info.GetReturnValue().Set(Nan::Undefined());
  float data[16]; // worst case scenario is 16 floats

  glGetUniformfv(program, location, data);

  Local<Array> arr=Nan::New<Array>(16);
  for(int i=0;i<16;i++) {
    arr->Set(i,JS_FLOAT(data[i]));
  }

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(WebGLRenderingContext::GetVertexAttrib) {
  Nan::HandleScope scope;

  GLuint index = info[0]->Int32Value();
  GLuint pname = info[1]->Int32Value();
  GLint value;

  switch (pname) {
    case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
    case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
      glGetVertexAttribiv(index, pname, &value);
      info.GetReturnValue().Set(JS_BOOL(static_cast<bool>(value)));
      break;
    case GL_VERTEX_ATTRIB_ARRAY_SIZE:
    case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
    case GL_VERTEX_ATTRIB_ARRAY_TYPE:
      glGetVertexAttribiv(index, pname, &value);
      info.GetReturnValue().Set(JS_INT(value));
      break;
    case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
      glGetVertexAttribiv(index, pname, &value);
      info.GetReturnValue().Set(JS_INT(value));
      break;
    case GL_CURRENT_VERTEX_ATTRIB: {
      float vextex_attribs[4];
      glGetVertexAttribfv(index, pname, vextex_attribs);
      Local<Array> arr = Nan::New<Array>(4);
      arr->Set(0,JS_FLOAT(vextex_attribs[0]));
      arr->Set(1,JS_FLOAT(vextex_attribs[1]));
      arr->Set(2,JS_FLOAT(vextex_attribs[2]));
      arr->Set(3,JS_FLOAT(vextex_attribs[3]));
      info.GetReturnValue().Set(arr);
      break;
    }
    default:
      Nan::ThrowError("GetVertexAttrib: Invalid Enum");
  }

  //info.GetReturnValue().Set(Nan::Undefined());
}

NAN_METHOD(WebGLRenderingContext::GetSupportedExtensions) {
  Nan::HandleScope scope;

  char *extensions = (char *)glGetString(GL_EXTENSIONS);

  info.GetReturnValue().Set(JS_STR(extensions));
}

// TODO GetExtension(name) return the extension name if found, should be an object...
NAN_METHOD(WebGLRenderingContext::GetExtension) {
  Nan::HandleScope scope;

  String::Utf8Value name(info[0]);
  char *sname = *name;

  if (
    strcmp(sname, "OES_texture_float") == 0 ||
    strcmp(sname, "OES_texture_float_linear") == 0 ||
    strcmp(sname, "OES_texture_half_float") == 0 ||
    strcmp(sname, "OES_texture_half_float_linear") == 0 ||
    strcmp(sname, "OES_element_index_uint") == 0 ||
    strcmp(sname, "OES_standard_derivatives") == 0 ||
    strcmp(sname, "EXT_shader_texture_lod") == 0
  ) {
    info.GetReturnValue().Set(Object::New(Isolate::GetCurrent()));
  } else if (strcmp(sname, "WEBGL_depth_texture") == 0) {
    Local<Object> result = Object::New(Isolate::GetCurrent());
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "UNSIGNED_INT_24_8_WEBGL"), Number::New(Isolate::GetCurrent(), GL_UNSIGNED_INT_24_8_OES));
    info.GetReturnValue().Set(result);
  } else if (strcmp(sname, "EXT_texture_filter_anisotropic") == 0) {
    Local<Object> result = Object::New(Isolate::GetCurrent());
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "MAX_TEXTURE_MAX_ANISOTROPY_EXT"), Number::New(Isolate::GetCurrent(), GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT));
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "TEXTURE_MAX_ANISOTROPY_EXT"), Number::New(Isolate::GetCurrent(), GL_TEXTURE_MAX_ANISOTROPY_EXT));
    info.GetReturnValue().Set(result);
  } else if (strcmp(sname, "WEBGL_compressed_texture_s3tc") == 0) {
    Local<Object> result = Object::New(Isolate::GetCurrent());
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGB_S3TC_DXT1_EXT"), Number::New(Isolate::GetCurrent(), GL_COMPRESSED_RGB_S3TC_DXT1_EXT));
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGBA_S3TC_DXT1_EXT"), Number::New(Isolate::GetCurrent(), GL_COMPRESSED_RGBA_S3TC_DXT1_EXT));
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGBA_S3TC_DXT3_EXT"), Number::New(Isolate::GetCurrent(), GL_COMPRESSED_RGBA_S3TC_DXT3_EXT));
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGBA_S3TC_DXT5_EXT"), Number::New(Isolate::GetCurrent(), GL_COMPRESSED_RGBA_S3TC_DXT5_EXT));
    info.GetReturnValue().Set(result);
  } else if (strcmp(sname, "WEBGL_compressed_texture_pvrtc") == 0) {
    Local<Object> result = Object::New(Isolate::GetCurrent());
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGB_PVRTC_4BPPV1_IMG"), Number::New(Isolate::GetCurrent(), GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG));
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGBA_PVRTC_4BPPV1_IMG"), Number::New(Isolate::GetCurrent(), GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG));
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGB_PVRTC_2BPPV1_IMG"), Number::New(Isolate::GetCurrent(), GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG));
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGBA_PVRTC_2BPPV1_IMG"), Number::New(Isolate::GetCurrent(), GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG));
    info.GetReturnValue().Set(result);
  } else if (strcmp(sname, "WEBGL_compressed_texture_etc1") == 0) {
    Local<Object> result = Object::New(Isolate::GetCurrent());
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "COMPRESSED_RGB_ETC1_WEBGL"), Number::New(Isolate::GetCurrent(), GL_ETC1_RGB8_OES));
    info.GetReturnValue().Set(result);
  } else if (strcmp(sname, "ANGLE_instanced_arrays") == 0) {
    Local<Object> result = Object::New(Isolate::GetCurrent());
    result->Set(String::NewFromUtf8(Isolate::GetCurrent(), "GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE"), Number::New(Isolate::GetCurrent(), GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE));
    Nan::SetMethod(result, "drawArraysInstancedANGLE", DrawArraysInstancedANGLE);
    Nan::SetMethod(result, "drawElementsInstancedANGLE", DrawElementsInstancedANGLE);
    Nan::SetMethod(result, "vertexAttribDivisorANGLE", VertexAttribDivisorANGLE);
    info.GetReturnValue().Set(result);
  } else if (strcmp(sname, "WEBGL_draw_buffers") == 0) {
    Local<Object> result = Object::New(Isolate::GetCurrent());

    Nan::SetMethod(result, "drawBuffersWEBGL", DrawBuffersWEBGL);

    result->Set(JS_STR("COLOR_ATTACHMENT0_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT0));
    result->Set(JS_STR("COLOR_ATTACHMENT1_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT1));
    result->Set(JS_STR("COLOR_ATTACHMENT2_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT2));
    result->Set(JS_STR("COLOR_ATTACHMENT3_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT3));
    result->Set(JS_STR("COLOR_ATTACHMENT4_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT4));
    result->Set(JS_STR("COLOR_ATTACHMENT5_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT5));
    result->Set(JS_STR("COLOR_ATTACHMENT6_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT6));
    result->Set(JS_STR("COLOR_ATTACHMENT7_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT7));
    result->Set(JS_STR("COLOR_ATTACHMENT8_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT8));
    result->Set(JS_STR("COLOR_ATTACHMENT9_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT9));
    result->Set(JS_STR("COLOR_ATTACHMENT10_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT10));
    result->Set(JS_STR("COLOR_ATTACHMENT11_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT11));
    result->Set(JS_STR("COLOR_ATTACHMENT12_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT12));
    result->Set(JS_STR("COLOR_ATTACHMENT13_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT13));
    result->Set(JS_STR("COLOR_ATTACHMENT14_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT14));
    result->Set(JS_STR("COLOR_ATTACHMENT15_WEBGL"), JS_INT(GL_COLOR_ATTACHMENT15));

    result->Set(JS_STR("DRAW_BUFFER0_WEBGL"), JS_INT(GL_DRAW_BUFFER0));
    result->Set(JS_STR("DRAW_BUFFER1_WEBGL"), JS_INT(GL_DRAW_BUFFER1));
    result->Set(JS_STR("DRAW_BUFFER2_WEBGL"), JS_INT(GL_DRAW_BUFFER2));
    result->Set(JS_STR("DRAW_BUFFER3_WEBGL"), JS_INT(GL_DRAW_BUFFER3));
    result->Set(JS_STR("DRAW_BUFFER4_WEBGL"), JS_INT(GL_DRAW_BUFFER4));
    result->Set(JS_STR("DRAW_BUFFER5_WEBGL"), JS_INT(GL_DRAW_BUFFER5));
    result->Set(JS_STR("DRAW_BUFFER6_WEBGL"), JS_INT(GL_DRAW_BUFFER6));
    result->Set(JS_STR("DRAW_BUFFER7_WEBGL"), JS_INT(GL_DRAW_BUFFER7));
    result->Set(JS_STR("DRAW_BUFFER8_WEBGL"), JS_INT(GL_DRAW_BUFFER8));
    result->Set(JS_STR("DRAW_BUFFER9_WEBGL"), JS_INT(GL_DRAW_BUFFER9));
    result->Set(JS_STR("DRAW_BUFFER10_WEBGL"), JS_INT(GL_DRAW_BUFFER10));
    result->Set(JS_STR("DRAW_BUFFER11_WEBGL"), JS_INT(GL_DRAW_BUFFER11));
    result->Set(JS_STR("DRAW_BUFFER12_WEBGL"), JS_INT(GL_DRAW_BUFFER12));
    result->Set(JS_STR("DRAW_BUFFER13_WEBGL"), JS_INT(GL_DRAW_BUFFER13));
    result->Set(JS_STR("DRAW_BUFFER14_WEBGL"), JS_INT(GL_DRAW_BUFFER14));
    result->Set(JS_STR("DRAW_BUFFER15_WEBGL"), JS_INT(GL_DRAW_BUFFER15));

    result->Set(JS_STR("MAX_COLOR_ATTACHMENTS_WEBGL"), JS_INT(GL_MAX_COLOR_ATTACHMENTS));
    result->Set(JS_STR("MAX_DRAW_BUFFERS_WEBGL"), JS_INT(GL_MAX_DRAW_BUFFERS));

    info.GetReturnValue().Set(result);
  } else {
    info.GetReturnValue().Set(Null(Isolate::GetCurrent()));
  }
}

NAN_METHOD(WebGLRenderingContext::CheckFramebufferStatus) {
  Nan::HandleScope scope;

  GLenum target = info[0]->Int32Value();
  GLint ret = glCheckFramebufferStatus(target);

  info.GetReturnValue().Set(JS_INT(ret));
}

/* struct GLObj {
  GLObjectType type;
  GLuint obj;
  GLObj(GLObjectType type, GLuint obj) {
    this->type=type;
    this->obj=obj;
  }
};

vector<GLObj*> globjs;
static bool atExit=false;

void registerGLObj(GLObjectType type, GLuint obj) {
  globjs.push_back(new GLObj(type,obj));
}


void unregisterGLObj(GLuint obj) {
  if(atExit) return;

  vector<GLObj*>::iterator it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *globj=*it;
    if(globj->obj==obj) {
      delete globj;
      globjs.erase(it);
      break;
    }
    ++it;
  }
}

void AtExit() {
  atExit=true;
  //glFinish();

  vector<GLObj*>::iterator it;

  #ifdef LOGGING
  cout<<"WebGL AtExit() called"<<endl;
  cout<<"  # objects allocated: "<<globjs.size()<<endl;
  it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *obj=*it;
    cout<<"[";
    switch(obj->type) {
    case GLOBJECT_TYPE_BUFFER: cout<<"buffer"; break;
    case GLOBJECT_TYPE_FRAMEBUFFER: cout<<"framebuffer"; break;
    case GLOBJECT_TYPE_PROGRAM: cout<<"program"; break;
    case GLOBJECT_TYPE_RENDERBUFFER: cout<<"renderbuffer"; break;
    case GLOBJECT_TYPE_SHADER: cout<<"shader"; break;
    case GLOBJECT_TYPE_TEXTURE: cout<<"texture"; break;
    };
    cout<<": "<<obj->obj<<"] ";
    ++it;
  }
  cout<<endl;
  #endif

  it = globjs.begin();
  while(globjs.size() && it != globjs.end()) {
    GLObj *globj=*it;
    GLuint obj=globj->obj;

    switch(globj->type) {
    case GLOBJECT_TYPE_PROGRAM:
      #ifdef LOGGING
      cout<<"  Destroying GL program "<<obj<<endl;
      #endif
      glDeleteProgram(obj);
      break;
    case GLOBJECT_TYPE_BUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL buffer "<<obj<<endl;
      #endif
      glDeleteBuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_FRAMEBUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL frame buffer "<<obj<<endl;
      #endif
      glDeleteFramebuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_RENDERBUFFER:
      #ifdef LOGGING
      cout<<"  Destroying GL render buffer "<<obj<<endl;
      #endif
      glDeleteRenderbuffers(1,&obj);
      break;
    case GLOBJECT_TYPE_SHADER:
      #ifdef LOGGING
      cout<<"  Destroying GL shader "<<obj<<endl;
      #endif
      glDeleteShader(obj);
      break;
    case GLOBJECT_TYPE_TEXTURE:
      #ifdef LOGGING
      cout<<"  Destroying GL texture "<<obj<<endl;
      #endif
      glDeleteTextures(1,&obj);
      break;
    default:
      #ifdef LOGGING
      cout<<"  Unknown object "<<obj<<endl;
      #endif
      break;
    }
    delete globj;
    ++it;
  }

  globjs.clear();
} */
