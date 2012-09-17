#ifndef GCELEMENT_H
#define GCELEMENT_H

#include "GCGlobal.h"
#include "3D/GCTransform.h"
#include "sbaseproperties.h"
#include "mcsimple.h"

class XRenderer;
class GCShadingGroup;

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

class GRAPHICSCORE_EXPORT GCElementArray : public GCElement
  {
  S_ENTITY(GCElementArray, GCElement, 0)

  template <typename T> typename GCElement *addChildElement(T **out = 0, GCShadingGroup *material = 0)
    {
    GCElement *el = T::addAsChild(this, material, out);
    return el;
    }

  GCRenderablePointerArray elements;

  void render(XRenderer *) const X_OVERRIDE;
  };



class GRAPHICSCORE_EXPORT GCUnitElement : public GCElement
  {
  S_ENTITY(GCUnitElement, GCElement, 0)

public:
  };



S_PROPERTY_INTERFACE(GCElement)
S_PROPERTY_INTERFACE(GCElementArray)
S_PROPERTY_INTERFACE(GCUnitElement)
S_PROPERTY_INTERFACE(GCElementCentre)
S_PROPERTY_INTERFACE(GCElementUnCentre)

#endif // GCELEMENT_H
