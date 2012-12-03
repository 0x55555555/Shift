#ifndef GCSHADERDATABINDINGS_H
#define GCSHADERDATABINDINGS_H

#include "GCShader.h"

namespace GCShaderDataBindings
{
class Vector3 : public GCShaderBindableData
  {
public:
  Vector3();
  virtual void bindData(XShader *, const Property *) const;
  };

class Vector4 : public GCShaderBindableData
  {
public:
  Vector4();
  virtual void bindData(XShader *, const Property *) const;
  };

class TextureRef : public GCShaderBindableData
  {
public:
  TextureRef();
  virtual void bindData(XShader *, const Property *) const;
  };
}

#endif // GCSHADERDATABINDINGS_H
