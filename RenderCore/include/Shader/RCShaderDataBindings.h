#ifndef RCSHADERDATABINDINGS_H
#define RCSHADERDATABINDINGS_H

#include "RCShader.h"

namespace RCShaderDataBindings
{
class RENDERCORE_EXPORT Vector3 : public RCShaderBindableData
  {
public:
  void bindData(DataBlock *data, const Shift::Attribute *) const X_OVERRIDE;
  void getDescription(Eks::ShaderConstantDataDescription &desc, const Shift::Attribute *) const X_OVERRIDE;
  };

class RENDERCORE_EXPORT Vector4 : public RCShaderBindableData
  {
public:
  void bindData(DataBlock *data, const Shift::Attribute *) const X_OVERRIDE;
  void getDescription(Eks::ShaderConstantDataDescription &desc, const Shift::Attribute *) const X_OVERRIDE;
  };

class RENDERCORE_EXPORT Texture2DRef : public RCShaderBindableResource
  {
public:
  void bindResource(DataBlock *data, ResourceBlock *resources, const Shift::Attribute *) const X_OVERRIDE;
  };

class RENDERCORE_EXPORT DataRef : public RCShaderBindableResource
  {
public:
  void bindResource(DataBlock *data, ResourceBlock *resources, const Shift::Attribute *) const X_OVERRIDE;
  };
}

#endif // RCSHADERDATABINDINGS_H
