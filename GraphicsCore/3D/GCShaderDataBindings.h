#ifndef GCSHADERDATABINDINGS_H
#define GCSHADERDATABINDINGS_H

#include "GCShader.h"

namespace GCShaderDataBindings
{
class Vector3 : public GCShaderBindableData
  {
public:
  void bindData(DataBlock *data, const Shift::Attribute *) const X_OVERRIDE;
  void getDescription(Eks::ShaderConstantDataDescription &desc, const Shift::Attribute *) const X_OVERRIDE;
  };

class Vector4 : public GCShaderBindableData
  {
public:
  void bindData(DataBlock *data, const Shift::Attribute *) const X_OVERRIDE;
  void getDescription(Eks::ShaderConstantDataDescription &desc, const Shift::Attribute *) const X_OVERRIDE;
  };

class Texture2DRef : public GCShaderBindableResource
  {
public:
  void bindResource(DataBlock *data, ResourceBlock *resources, const Shift::Attribute *) const X_OVERRIDE;
  };

class DataRef : public GCShaderBindableResource
  {
public:
  void bindResource(DataBlock *data, ResourceBlock *resources, const Shift::Attribute *) const X_OVERRIDE;
  };
}

#endif // GCSHADERDATABINDINGS_H
