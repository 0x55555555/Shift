#ifndef GCSHADER_H
#define GCSHADER_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XShader.h"
#include "GCBaseProperties.h"

class GCShaderBindableData : public Shift::StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(GCShaderBindableData, GCShaderBindableInterface)
public:

  enum
    {
    DataSize = 128,
    ResourceCount = 4
    };
  typedef Eks::Vector<xuint8, DataSize> DataBlock;
  typedef Eks::Vector<const Eks::Resource *, ResourceCount> ResourceBlock;

  virtual void bindData(DataBlock *data, ResourceBlock *resources, const Shift::Property *) const = 0;
  };

class GRAPHICSCORE_EXPORT GCShader : public Shift::Entity
  {
  S_ENTITY(GCShader, Shift::Entity, 0)
public:

  void bind(Eks::Renderer *r) const;
  GCRuntimeShaderInstance runtimeShader;

  GCRendererPointer renderer;
  GCVertexLayoutPointer layoutDescription;

  GCRuntimeShader runtimeShaderCore;

protected:
  Eks::ShaderVertexLayout layout;

  Eks::ShaderConstantData constantData;
  GCShaderBindableData::ResourceBlock resources;

private:
  static void setupShaderRuntime(GCShader *cont);
  };

class GRAPHICSCORE_EXPORT GCStaticShader : public GCShader
  {
public:
  class EmbeddedInstanceInformation : public GCShader::EmbeddedInstanceInformation
    {
  XProperties:
    XByRefProperty(Eks::String, vertexData, setVertexData);
    XByRefProperty(Eks::String, fragmentData, setFragmentData);
    };

  S_ENTITY(GCStaticShader, Shift::Entity, 0)

private:
  Eks::ShaderFragmentComponent fragment;
  Eks::ShaderVertexComponent vertex;

  static void computeShaderRuntime(GCStaticShader *cont);
  };

S_PROPERTY_INTERFACE(GCShader)
S_PROPERTY_INTERFACE(GCStaticShader)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCShaderPointer, GCShader);

#endif // GCSHADER_H
