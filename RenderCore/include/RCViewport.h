#ifndef RCVIEWPORT_H
#define RCVIEWPORT_H

#include "RCGlobal.h"
#include "shift/Properties/sbaseproperties.h"
#include "Targets/RCScreenRenderTarget.h"

class RENDERCORE_EXPORT RCViewport : public RCScreenRenderTarget
  {
  S_ENTITY(RCViewport, RCScreenRenderTarget)

public:
  Shift::UnsignedIntProperty x;
  Shift::UnsignedIntProperty y;
  };

#endif // RCVIEWPORT_H
