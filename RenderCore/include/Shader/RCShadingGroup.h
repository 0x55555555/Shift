#ifndef RCSHADINGGROUP_H
#define RCSHADINGGROUP_H

#include "RCGlobal.h"
#include "RCRenderable.h"
#include "Shader/RCShader.h"
#include "shift/Properties/sbasepointerproperties.h"

class RENDERCORE_EXPORT RCShadingGroup : public RCRenderArray
  {
  S_ENTITY(RCShadingGroup, RCRenderArray)

public:
  RCShadingGroup();

  void render(Eks::Renderer *r, const RenderState &) const;

  RCRenderablePointerArray *manipulatableChildren() { return &renderGroup; }

  RCShaderPointer shader;
  };

S_TYPED_POINTER_TYPE(RENDERCORE_EXPORT, RCShadingGroupPointer, RCShadingGroup);

S_TYPED_POINTER_ARRAY_TYPE(RENDERCORE_EXPORT, RCShadingGroupPointerArray, RCShadingGroupPointer);

S_PROPERTY_INTERFACE(RCShadingGroup)
S_PROPERTY_INTERFACE(Shift::TypedPointerArray<RCShadingGroupPointer>)
S_PROPERTY_INTERFACE(RCShadingGroupPointerArray)

#endif // RCSHADINGGROUP_H
