#ifndef RCSHADER_H
#define RCSHADER_H

#include "RCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "shift/TypeInformation/sinterface.h"
#include "XShader.h"
#include "Utilities/RCBaseProperties.h"

class RCShader;

class RCShaderInterface : public Shift::StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(RCShaderInterface, RCShaderInterface)

public:
  struct Shader
    {
    Eks::Shader *shader;
    Eks::ShaderFragmentComponent *fragment;
    Eks::ShaderVertexComponent *vertex;
    Eks::ShaderVertexLayout *layout;
    };

  virtual bool initShader(
    RCShader *,
    Eks::Renderer *,
    Shader *) const
    { return false; }
  };

class RCShaderBindableResource : public Shift::StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(RCShaderBindableResource, RCShaderBindableResource)
public:

  enum
    {
    ResourceCount = 4
    };
  typedef Eks::Vector<const Eks::Resource *, ResourceCount> ResourceBlock;
  typedef Eks::Vector<const Eks::ShaderConstantData *, ResourceCount> DataBlock;

  virtual void bindResource(DataBlock *data, ResourceBlock *resources, const Shift::Attribute *) const = 0;
  };

class RCShaderBindableData : public Shift::StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(RCShaderBindableData, RCShaderBindableData)
public:

  typedef Eks::Vector<xuint8> DataBlock;

  virtual void bindData(DataBlock *data, const Shift::Attribute *) const = 0;
  virtual void getDescription(
      Eks::ShaderConstantDataDescription &desc,
      const Shift::Attribute *) const = 0;
  };

class RENDERCORE_EXPORT RCShaderConstantData : public Shift::Container
  {
  S_PROPERTY_CONTAINER(RCShaderConstantData, Shift::Container)

public:
  enum
    {
    StaticChildMode = Shift::NamedChildren
    };

  RCRenderer renderer;
  RCShaderRuntimeConstantData runtimeData;
  };

S_TYPED_POINTER_TYPE(RENDERCORE_EXPORT, RCShaderConstantDataPointer, RCShaderConstantData);


class RENDERCORE_EXPORT RCShader : public Shift::Entity
  {
  S_ENTITY(RCShader, Shift::Entity)
public:

  void bind(Eks::Renderer *r) const;
  RCRuntimeShaderInstance runtimeShader;

  RCRenderer renderer;

  RCRuntimeShader runtimeShaderCore;

  const Eks::ShaderVertexLayout *layout() { return &_layout; }

protected:
  Eks::ShaderVertexLayout _layout;

  RCShaderBindableResource::DataBlock constantDatas;
  RCShaderBindableResource::ResourceBlock resources;

private:
  static void setupShaderRuntime(RCShader *cont);
  };

class RENDERCORE_EXPORT RCStaticShader : public RCShader
  {
  S_ABSTRACT_ENTITY(RCStaticShader, RCShader)

private:
  Eks::ShaderFragmentComponent fragment;
  Eks::ShaderVertexComponent vertex;

  static void computeShaderRuntime(RCStaticShader *cont);
  };


S_TYPED_POINTER_TYPE(RENDERCORE_EXPORT, RCShaderPointer, RCShader);

#endif // RCSHADER_H
