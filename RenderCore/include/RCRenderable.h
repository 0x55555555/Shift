#ifndef RCRENDERABLE_H
#define RCRENDERABLE_H

#include "RCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "Utilities/RCBaseProperties.h"

namespace Eks
{
class Renderer;
class Line;
class Frustum;
}

class RENDERCORE_EXPORT RCRenderable : public Shift::Entity
  {
  S_ABSTRACT_ENTITY(RCRenderable, Entity)

public:
  RCRenderable();

  RCBoundingBox bounds;

  class RenderState
    {
  public:
    Eks::FrameBuffer *framebuffer;
    Eks::Transform transform;
    };

  virtual void render(Eks::Renderer *r, const RenderState &state) const = 0;

  class Selector
    {
  public:
    virtual void onHit(const Eks::Vector3D &point, const Eks::Vector3D& normal, RCRenderable *renderable) = 0;
    };

  virtual void intersect(const Eks::Line &line, Selector *);
  virtual void intersect(const Eks::Frustum &frus, Selector *);
  };

S_TYPED_POINTER_TYPE(RENDERCORE_EXPORT, RCRenderablePointer, RCRenderable)
S_TYPED_POINTER_ARRAY_TYPE(RENDERCORE_EXPORT, RCRenderablePointerArray, RCRenderablePointer)

class RENDERCORE_EXPORT RCRenderArray : public RCRenderable
  {
  S_ENTITY(RCRenderArray, RCRenderable)

public:
  RCRenderablePointerArray renderGroup;

  virtual void render(Eks::Renderer *, const RenderState &state) const;

  virtual void intersect(const Eks::Line &line, Selector *);
  virtual void intersect(const Eks::Frustum &frus, Selector *);
  };

S_PROPERTY_INTERFACE(RCRenderable)
S_PROPERTY_INTERFACE(RCRenderablePointerArray)
S_PROPERTY_INTERFACE(Shift::TypedPointerArray<RCRenderablePointer>)
S_TYPED_POINTER_TYPE(RENDERCORE_EXPORT, RCRenderArrayPointer, RCRenderArray)

#endif // RCRENDERABLE_H
