#ifndef GCELEMENT_H
#define GCELEMENT_H

#include "GCGlobal.h"
#include "sentity.h"
#include "sbaseproperties.h"

class XRenderer;

class GRAPHICSCORE_EXPORT GCElement : public SEntity
  {
  S_ENTITY(GCElement, SEntity, 0)

public:

  FloatProperty top;
  FloatProperty left;

  FloatProperty width;
  FloatProperty height;

  virtual void render(XRenderer *) const;
  };

S_PROPERTY_INTERFACE(GCElement)

#endif // GCELEMENT_H
