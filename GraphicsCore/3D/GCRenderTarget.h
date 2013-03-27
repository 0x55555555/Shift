#ifndef GCRENDERTARGET_H
#define GCRENDERTARGET_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "GCRenderable.h"

class GRAPHICSCORE_EXPORT GCRenderTarget : public Shift::Entity
  {
  S_ENTITY(GCRenderTarget, Entity, 0)

public:
  GCRenderablePointer source;

  Shift::UnsignedIntProperty width;
  Shift::UnsignedIntProperty height;

  Shift::FloatProperty aspectRatio;

  void render(Eks::Renderer *);
  };

S_PROPERTY_INTERFACE(GCRenderTarget)

#endif // GCRENDERTARGET_H
