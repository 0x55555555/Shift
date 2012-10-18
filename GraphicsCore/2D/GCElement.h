#ifndef GCELEMENT_H
#define GCELEMENT_H

#include "GCGlobal.h"
#include "3D/GCTransform.h"
#include "sbaseproperties.h"
#include "mcsimple.h"
#include "siterator.h"

class XRenderer;
class GCShadingGroup;
class GCElement;

class GCElementCentre : public MCSimple
  {
  S_ENTITY(GCElementCentre, MCSimple, 0)
  };

class GCElementUnCentre : public MCSimple
  {
  S_ENTITY(GCElementUnCentre, MCSimple, 0)
  };

class GRAPHICSCORE_EXPORT GCInteractionHandler : public SPropertyContainer
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCInteractionHandler, SPropertyContainer, 0)

public:
  virtual void onRelease(GCElement *e, int x, int y) = 0;
  };

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCInteractionHandlerPointer, GCInteractionHandler)

class GRAPHICSCORE_EXPORT GCElement : public GCTransform
  {
  S_ENTITY(GCElement, GCTransform, 0)

public:

  BoolProperty visible;

  FloatProperty bottom;
  FloatProperty left;
  FloatProperty width;
  FloatProperty height;

  GCInteractionHandlerPointer interactionHandler;

  const FloatProperty* right();

  const FloatProperty* horizontalCentre();
  const FloatProperty* verticalCentre();

  void setTopInput(const FloatProperty* input);
  void setHorizontalCentreInput(const FloatProperty* input);
  void setVerticalCentreInput(const FloatProperty* input);

  void render(XRenderer *) const X_OVERRIDE;

  virtual bool hitTest(int x, int y) const;
  };

class GRAPHICSCORE_EXPORT GCElementArray : public GCElement
  {
  S_ENTITY(GCElementArray, GCElement, 0)

  template <typename T> GCElement *addChildElement(T **out = 0, GCShadingGroup *material = 0)
    {
    GCElement *el = T::addAsChild(this, material, out);
    return el;
    }

  static GCElement *addAsChild(GCElementArray *parent, GCShadingGroup *material, GCElementArray **arr);

  GCRenderablePointerArray elements;

  void render(XRenderer *) const X_OVERRIDE;
  };



class GRAPHICSCORE_EXPORT GCUnitElement : public GCElement
  {
  S_ENTITY(GCUnitElement, GCElement, 0)

public:
  };

namespace SIterator
{
class GCElementWithUIHandler : public Base<GCElementWithUIHandler, GCElement, NilExtraData>
  {
public:
  typedef Base<GCElementWithUIHandler, GCElement, NilExtraData>::Iterator Iterator;

  inline void first(Iterator &i) const
    {
    SProperty *prop = Base<GCElementWithUIHandler, GCElement, NilExtraData>::property();
    GCElement *el = prop->castTo<GCElement>();
    if(el && el->interactionHandler() != 0)
      {
      i.setProperty(el);
      return;
      }
    i.setProperty(0);
    }

  inline static void next(Iterator &i)
    {
    i.setProperty(0);
    }
  };
}



S_PROPERTY_INTERFACE(GCInteractionHandler)
S_PROPERTY_INTERFACE(GCElement)
S_PROPERTY_INTERFACE(GCElementArray)
S_PROPERTY_INTERFACE(GCUnitElement)
S_PROPERTY_INTERFACE(GCElementCentre)
S_PROPERTY_INTERFACE(GCElementUnCentre)

#endif // GCELEMENT_H
