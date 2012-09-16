#ifndef GCELEMENT_H
#define GCELEMENT_H

#include "GCGlobal.h"
#include "3D/GCTransform.h"
#include "sbaseproperties.h"
#include "mcsimple.h"

class XRenderer;

class GCElementCentre : public MCSimple
  {
  S_ENTITY(GCElementCentre, MCSimple, 0)
  };

class GCElementUnCentre : public MCSimple
  {
  S_ENTITY(GCElementUnCentre, MCSimple, 0)
  };

class GRAPHICSCORE_EXPORT GCElement : public GCTransform
  {
  S_ENTITY(GCElement, GCTransform, 0)

public:

  FloatProperty bottom;
  FloatProperty left;
  FloatProperty width;
  FloatProperty height;

  FloatProperty* right();

  FloatProperty* horizontalCentre();
  FloatProperty* verticalCentre();

  void setHorizontalCentreInput(FloatProperty* input);
  void setVerticalCentreInput(FloatProperty* input);
  };



class GRAPHICSCORE_EXPORT GCUnitElement : public GCElement
  {
  S_ENTITY(GCUnitElement, GCElement, 0)

public:
  };



S_PROPERTY_INTERFACE(GCElement)
S_PROPERTY_INTERFACE(GCUnitElement)
S_PROPERTY_INTERFACE(GCElementCentre)
S_PROPERTY_INTERFACE(GCElementUnCentre)

#endif // GCELEMENT_H
