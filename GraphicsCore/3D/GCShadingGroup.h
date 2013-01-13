#ifndef GCSHADINGGROUP_H
#define GCSHADINGGROUP_H

#include "GCGlobal.h"
#include "GCRenderable.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "GCShader.h"
#include "Manipulators/GCManipulator.h"

class GRAPHICSCORE_EXPORT GCShadingGroup : public GCRenderArray, public GCManipulatable
  {
  S_ENTITY(GCShadingGroup, GCRenderArray, 0)

public:
  GCShadingGroup();

  void render(Eks::Renderer *r, const RenderState &) const;

  virtual void addManipulators(Shift::PropertyArray *, const GCTransform *tr=0);

  GCShaderPointer shader;
  };

S_PROPERTY_INTERFACE(GCShadingGroup)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCShadingGroupPointer, GCShadingGroup);

S_TYPED_POINTER_ARRAY_TYPE(GRAPHICSCORE_EXPORT, GCShadingGroupPointerArray, GCShadingGroupPointer);

#endif // GCSHADINGGROUP_H
