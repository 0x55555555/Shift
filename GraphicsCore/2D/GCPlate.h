#ifndef GCPLATE_H
#define GCPLATE_H

#include "3D/GCTransform.h"
#include "GCGlobal.h"
#include "GCBaseProperties.h"
#include "GCElement.h"
#include "GCElementContainer.h"

class GRAPHICSCORE_EXPORT GCPlate : public GCTransform
  {
  S_ENTITY(GCPlate, GCTransform, 0)

public:
  virtual void render(XRenderer *) const;

  UnsignedIntProperty viewportWidth;
  UnsignedIntProperty viewportHeight;

  GCElementContainer element;
  };

S_PROPERTY_INTERFACE(GCPlate)

#endif // GCPLATE_H
