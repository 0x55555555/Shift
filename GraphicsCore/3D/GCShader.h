#ifndef GCSHADER_H
#define GCSHADER_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "shift/TypeInformation/sinterface.h"
#include "XShader.h"
#include "GCBaseProperties.h"

class GCShader;

class GCShaderInterface : public Shift::StaticInterfaceBase
  {
public:
  struct Shader
    {
    Eks::Shader *shader;
    Eks::ShaderFragmentComponent *fragment;
    Eks::ShaderVertexComponent *vertex;
    Eks::ShaderVertexLayout *layout;
    };

  virtual bool initShader(
    GCShader *,
    Eks::Renderer *,
    Shader *) const
    { return false; }
  };

class GCShaderBindableResource : public Shift::StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(GCShaderBindableResource, GCShaderBindableResource)
public:

  enum
    {
    ResourceCount = 4
    };
  typedef Eks::Vector<const Eks::Resource *, ResourceCount> ResourceBlock;
  typedef Eks::Vector<const Eks::ShaderConstantData *, ResourceCount> DataBlock;

  virtual void bindResource(DataBlock *data, ResourceBlock *resources, const Shift::Property *) const = 0;
  };

class GCShaderBindableData : public Shift::StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(GCShaderBindableData, GCShaderBindableData)
public:

  typedef Eks::Vector<xuint8> DataBlock;

  virtual void bindData(DataBlock *data, const Shift::Property *) const = 0;
  virtual void getDescription(
      Eks::ShaderConstantDataDescription &desc,
      const Shift::Property *) const = 0;
  };

class GRAPHICSCORE_EXPORT GCShaderConstantData : public Shift::PropertyContainer
  {
  S_PROPERTY_CONTAINER(GCShaderConstantData, Shift::PropertyContainer, 0)

public:
  GCRenderer renderer;
  GCShaderRuntimeConstantData runtimeData;
  };

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCShaderConstantDataPointer, GCShaderConstantData);


class GRAPHICSCORE_EXPORT GCShader : public Shift::Entity
  {
  S_ENTITY(GCShader, Shift::Entity, 0)
public:

  void bind(Eks::Renderer *r) const;
  GCRuntimeShaderInstance runtimeShader;

  GCRenderer renderer;

  GCRuntimeShader runtimeShaderCore;

protected:
  Eks::ShaderVertexLayout layout;

  GCShaderBindableResource::DataBlock constantDatas;
  GCShaderBindableResource::ResourceBlock resources;

private:
  static void setupShaderRuntime(GCShader *cont);
  };

class GRAPHICSCORE_EXPORT GCStaticShader : public GCShader
  {
  S_ABSTRACT_ENTITY(GCStaticShader, GCShader, 0)

private:
  Eks::ShaderFragmentComponent fragment;
  Eks::ShaderVertexComponent vertex;

  static void computeShaderRuntime(GCStaticShader *cont);
  };

S_PROPERTY_INTERFACE(GCShader)
S_PROPERTY_INTERFACE(GCStaticShader)
S_PROPERTY_INTERFACE(GCShaderConstantData)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCShaderPointer, GCShader);

#endif // GCSHADER_H
