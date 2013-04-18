#ifndef GCELEMENT_H
#define GCELEMENT_H

#include "GCGlobal.h"
#include "3D/GCTransform.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Utilities/siterator.h"
#include "mcsimple.h"

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

class GRAPHICSCORE_EXPORT GCInteractionHandler : public Shift::Container
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCInteractionHandler, Shift::Container, 0)

public:
  virtual void onRelease(GCElement *e, int x, int y) = 0;
  };

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCInteractionHandlerPointer, GCInteractionHandler)

class GRAPHICSCORE_EXPORT GCElement : public GCTransform
  {
  S_ENTITY(GCElement, GCTransform, 0)

public:

  Shift::BoolProperty visible;

  Shift::FloatProperty bottom;
  Shift::FloatProperty left;
  Shift::FloatProperty width;
  Shift::FloatProperty height;

  GCInteractionHandlerPointer interactionHandler;

  const Shift::FloatProperty* right();

  const Shift::FloatProperty* horizontalCentre();
  const Shift::FloatProperty* verticalCentre();

  void setTopInput(const Shift::FloatProperty* input);
  void setHorizontalCentreInput(const Shift::FloatProperty* input);
  void setVerticalCentreInput(const Shift::FloatProperty* input);

  void render(Eks::Renderer *, const RenderState &state) const X_OVERRIDE;

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

  void render(Eks::Renderer *, const RenderState &state) const X_OVERRIDE;
  };



class GRAPHICSCORE_EXPORT GCUnitElement : public GCElement
  {
  S_ENTITY(GCUnitElement, GCElement, 0)

public:
  };

namespace Shift
{
namespace Iterator
{
class GCElementWithUIHandler : public Base<GCElementWithUIHandler, GCElement, NilExtraData>
  {
public:
  typedef Base<GCElementWithUIHandler, GCElement, NilExtraData>::Iterator Iterator;

  inline void first(Iterator &i) const
    {
    Attribute *prop = Base<GCElementWithUIHandler, GCElement, NilExtraData>::attribute();
    GCElement *el = prop->castTo<GCElement>();
    if(el && el->interactionHandler() != 0)
      {
      i.setAttribute(el);
      return;
      }
    i.setAttribute(0);
    }

  inline static void next(Iterator &i)
    {
    i.setAttribute(0);
    }
  };
}
}



S_PROPERTY_INTERFACE(GCInteractionHandler)
S_PROPERTY_INTERFACE(GCElement)
S_PROPERTY_INTERFACE(GCElementArray)
S_PROPERTY_INTERFACE(GCUnitElement)
S_PROPERTY_INTERFACE(GCElementCentre)
S_PROPERTY_INTERFACE(GCElementUnCentre)

#endif // GCELEMENT_H
