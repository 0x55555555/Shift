#ifndef GCSHADER_H
#define GCSHADER_H

#include "GCGlobal.h"
#include "sentity.h"
#include "sbaseproperties.h"
#include "sbasepointerproperties.h"
#include "XShader.h"
#include "GCBaseProperties.h"

class GCShaderBindableData : public StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(GCShaderBindableData, GCShaderBindableInterface)
public:
  GCShaderBindableData(bool deleteOnNoReferences) : StaticInterfaceBase(deleteOnNoReferences) { }
  virtual void bindData(XShader *, const Property *) const = 0;
  };

class GRAPHICSCORE_EXPORT GCShaderComponent : public StringProperty
  {
  S_ENTITY(GCShaderComponent, StringProperty, 0)
public:
  GCShaderComponent();
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

class GRAPHICSCORE_EXPORT GCStaticShader : public Entity
  {
  S_ENTITY(GCStaticShader, Entity, 0)
public:

  void bind(XRenderer *r) const;
  GCRuntimeShaderInstance runtimeShader;

protected:
  GCRuntimeShader runtimeShaderCore;

private:
  static void computeShaderRuntime(GCStaticShader *cont);
  static void setupShaderRuntime(GCStaticShader *cont);
  };

class GRAPHICSCORE_EXPORT GCShader : public GCStaticShader
  {
  S_ENTITY(GCShader, GCStaticShader, 0)
public:

  GCShaderComponentPointerArray components;

private:
  static void computeShaderRuntime(GCShader *cont);
  static void setupShaderRuntime(GCShader *cont);
  };

S_PROPERTY_INTERFACE(GCShader)
S_PROPERTY_INTERFACE(GCStaticShader)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCShaderPointer, GCStaticShader);

#endif // GCSHADER_H
