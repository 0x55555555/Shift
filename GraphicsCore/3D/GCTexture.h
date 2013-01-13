#ifndef GCTEXTURE_H
#define GCTEXTURE_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XTexture.h"

class GRAPHICSCORE_EXPORT GCTexture : public Shift::PODPropertyBase<XTexture, GCTexture>
  {
  S_PROPERTY(GCTexture, Property, 0)

public:
  GCTexture();

  static void assignProperty(const Shift::Property *, Shift::Property *)
    {
    xAssertFail();
    }
  };

S_PROPERTY_INTERFACE(GCTexture)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCTexturePointer, GCTexture);

#endif // GCTEXTURE_H
