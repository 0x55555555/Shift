#ifndef RCRENDERTARGET_H
#define RCRENDERTARGET_H

#include "RCGlobal.h"
#include "shift/sentity.h"
#include "RCRenderable.h"

class RENDERCORE_EXPORT RCRenderTarget : public Shift::Entity
  {
  S_ENTITY(RCRenderTarget, Entity)

public:
  RCRenderablePointer source;

  Shift::UnsignedIntProperty width;
  Shift::UnsignedIntProperty height;

  Shift::FloatProperty aspectRatio;
  };


#endif // RCRENDERTARGET_H
