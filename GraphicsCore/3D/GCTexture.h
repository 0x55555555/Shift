#ifndef GCTEXTURE_H
#define GCTEXTURE_H

#include "GCGlobal.h"
#include "sentity.h"
#include "sbaseproperties.h"
#include "sbasepointerproperties.h"
#include "XTexture.h"

class GRAPHICSCORE_EXPORT GCTexture : public PODPropertyBase<XTexture, GCTexture>
  {
  S_PROPERTY(GCTexture, Property, 0)

public:
  GCTexture();

  static void assignProperty(const Property *, Property *)
    {
    xAssertFail();
    }
  };

S_PROPERTY_INTERFACE(GCTexture)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCTexturePointer, GCTexture);

#endif // GCTEXTURE_H
