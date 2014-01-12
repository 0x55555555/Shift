#ifndef GCMANIPULATABLE_H
#define GCMANIPULATABLE_H

#include "GCGlobal.h"
#include "shift/TypeInformation/sinterface.h"
#include "shift/Properties/sbaseproperties.h"
#include "Utilities/RCBaseProperties.h"

class RCRenderable;
class RCViewableTransform;
class RCRenderablePointerArray;

class GRAPHICSCORE_EXPORT GCManipulatable : public Shift::StaticInterfaceBase
  {
  S_STATIC_INTERFACE_TYPE(GCManipulatable, ManipulatableInterface)
public:

  struct ManipInfo
    {
    ManipInfo() : viewTransform(0), parentTransform(0), displayScale(0)
      {
      }
    const RCViewableTransform *viewTransform;
    const TransformProperty *parentTransform;
    const Shift::FloatProperty *displayScale;
    };

  virtual RCRenderablePointerArray *manipulatableChildren(RCRenderable *) { return 0; }
  virtual void addManipulators(
    RCRenderable* renderable,
    Shift::Array *parent,
    const ManipInfo &tr);

protected:
  template <typename T, typename X> static T *createManipulator(
      Shift::Array *parent,
      X *x,
      const GCManipulatable::ManipInfo &info,
      TransformProperty *localTransform)
    {
    T *manip = parent->add<T>();

    if(info.parentTransform)
      {
      manip->parentTransform.setInput(info.parentTransform);
      }

    if(info.displayScale)
      {
      manip->displayScale.setInput(info.displayScale);
      }

    if(localTransform)
      {
      manip->localTransform.setInput(localTransform);
      }

    manip->addDriven(x);

    manip->setDriver(x);
    return manip;
    }
  };


#endif // GCMANIPULATABLE_H
