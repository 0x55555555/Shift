#ifndef GCVIEWPORT_H
#define GCVIEWPORT_H

#include "GCGlobal.h"
#include "shift/Properties/sbaseproperties.h"
#include "GCScreenRenderTarget.h"

class GRAPHICSCORE_EXPORT GCViewport : public GCScreenRenderTarget
  {
  S_ENTITY(GCViewport, GCScreenRenderTarget, 0)

public:
  Shift::UnsignedIntProperty x;
  Shift::UnsignedIntProperty y;
  };

S_PROPERTY_INTERFACE(GCViewport)

#endif // GCVIEWPORT_H
