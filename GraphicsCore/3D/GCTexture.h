#ifndef GCTEXTURE_H
#define GCTEXTURE_H

#include "GCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XTexture.h"

typedef Shift::Data<Eks::Texture2D, Shift::ComputedData> GCTexture2D;

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCTexture2DPointer, GCTexture2D);

#endif // GCTEXTURE_H
