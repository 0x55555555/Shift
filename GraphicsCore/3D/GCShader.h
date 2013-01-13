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
  virtual void bindData(Eks::Shader *, const Shift::Property *) const = 0;
  };

class GRAPHICSCORE_EXPORT GCShaderComponent : public Shift::StringProperty
  {
  S_ENTITY(GCShaderComponent, StringProperty, 0)
public:
  };

S_PROPERTY_INTERFACE(GCShaderComponent)

class GRAPHICSCORE_EXPORT GCFragmentShaderComponent : public GCShaderComponent
  {
  S_ENTITY(GCFragmentShaderComponent, GCShaderComponent, 0)
  };

S_PROPERTY_INTERFACE(GCFragmentShaderComponent)

class GRAPHICSCORE_EXPORT GCVertexShaderComponent : public GCShaderComponent
  {
  S_ENTITY(GCVertexShaderComponent, GCShaderComponent, 0)
  };

S_PROPERTY_INTERFACE(GCVertexShaderComponent)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCShaderComponentPointer, GCShaderComponent);

S_TYPED_POINTER_ARRAY_TYPE(GRAPHICSCORE_EXPORT, GCShaderComponentPointerArray, GCShaderComponentPointer);

class GRAPHICSCORE_EXPORT GCShader : public Shift::Entity
  {
  S_ENTITY(GCShader, Shift::Entity, 0)
public:

  void bind(Eks::Renderer *r) const;
  GCRuntimeShaderInstance runtimeShader;

  GCVertexShaderComponent vertex;
  GCFragmentShaderComponent fragment;

protected:
  GCRuntimeShader runtimeShaderCore;

private:
  static void computeShaderRuntime(GCShader *cont);
  static void setupShaderRuntime(GCShader *cont);
  };

S_PROPERTY_INTERFACE(GCShader)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCShaderPointer, GCShader);

#endif // GCSHADER_H
