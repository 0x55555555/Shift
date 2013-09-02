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
  S_ENTITY(GCElementCentre, MCSimple)
  };

class GCElementUnCentre : public MCSimple
  {
  S_ENTITY(GCElementUnCentre, MCSimple)
  };

class GRAPHICSCORE_EXPORT GCInteractionHandler : public Shift::Container
  {
  S_ABSTRACT_PROPERTY_CONTAINER(GCInteractionHandler, Shift::Container)

public:
  virtual void onRelease(GCElement *e, int x, int y) = 0;
  };

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCInteractionHandlerPointer, GCInteractionHandler)

class GRAPHICSCORE_EXPORT GCElement : public GCTransform
  {
  S_ENTITY(GCElement, GCTransform)

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
  S_ENTITY(GCElementArray, GCElement)

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
  S_ENTITY(GCUnitElement, GCElement)

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


#endif // GCELEMENT_H
