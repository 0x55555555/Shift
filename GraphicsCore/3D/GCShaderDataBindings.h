#ifndef GCSHADERDATABINDINGS_H
#define GCSHADERDATABINDINGS_H

#include "GCShader.h"

namespace GCShaderDataBindings
{
class Vector3 : public GCShaderBindableData
  {
public:
  virtual void bindData(DataBlock *data, ResourceBlock *resources, const Shift::Property *) const;
  };

class Vector4 : public GCShaderBindableData
  {
public:
  virtual void bindData(DataBlock *data, ResourceBlock *resources, const Shift::Property *) const;
  };

class Texture2DRef : public GCShaderBindableData
  {
public:
  virtual void bindData(DataBlock *data, ResourceBlock *resources, const Shift::Property *) const;
  };
}

#endif // GCSHADERDATABINDINGS_H
