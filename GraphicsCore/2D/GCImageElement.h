#ifndef GCIMAGEELEMENT_H
#define GCIMAGEELEMENT_H

#include "GCRectangle.h"
#include "GCBaseProperties.h"

class GRAPHICSCORE_EXPORT GCImageElement : public GCRectangle
  {
  S_ENTITY(GCImageElement, GCElement, 0);

public:

  GCQImage image;
  };

S_PROPERTY_INTERFACE(GCImageElement)

#endif // GCIMAGEELEMENT_H
