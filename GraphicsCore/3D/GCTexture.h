#ifndef GCTEXTURE_H
#define GCTEXTURE_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XTexture.h"

class GRAPHICSCORE_EXPORT GCTexture2D
    : public Shift::PODPropertyBase<Eks::Texture2D,
      GCTexture2D>
  {
  S_PROPERTY(GCTexture2D, Property, 0)
  };

S_PROPERTY_INTERFACE(GCTexture2D)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCTexture2DPointer, GCTexture2D);

#endif // GCTEXTURE_H
