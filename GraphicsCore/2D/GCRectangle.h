#ifndef GCRECTANGLE_H
#define GCRECTANGLE_H

#include "GCElement.h"

class GRAPHICSCORE_EXPORT GCRectangle : public GCElement
  {
  S_ENTITY(GCRectangle, GCElement, 0)

public:
  void render(XRenderer *) const;
  };

S_PROPERTY_INTERFACE(GCRectangle)

#endif // GCRECTANGLE_H
