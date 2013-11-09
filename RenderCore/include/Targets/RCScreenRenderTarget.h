#ifndef RCRENDERTOSCREEN_H
#define RCRENDERTOSCREEN_H

#include "RCGlobal.h"
#include "RCRenderTarget.h"

class RENDERCORE_EXPORT RCScreenRenderTarget : public RCRenderTarget
  {
  S_ENTITY(RCScreenRenderTarget, RCRenderTarget)

public:
  RCScreenRenderTarget();
  };

#endif // RCRENDERTOSCREEN_H
