#ifndef GCPLATE_H
#define GCPLATE_H

#include "GCRenderable.h"
#include "GCGlobal.h"

class GRAPHICSCORE_EXPORT GCPlate : public GCRenderable
  {
  S_ENTITY(GCPlate, GCRenderable, 0)

public:
  GCPlate();

  virtual void render(XRenderer *) const;
  };

S_PROPERTY_INTERFACE(GCPlate)

#endif // GCPLATE_H
