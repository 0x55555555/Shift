#ifndef GCMANIPULATABLE_H
#define GCMANIPULATABLE_H

#include "GCGlobal.h"
#include "shift/TypeInformation/sinterface.h"
#include "shift/Properties/sbaseproperties.h"

class GCViewableTransform;
class GCRenderablePointerArray;
class TransformProperty;

class GRAPHICSCORE_EXPORT GCManipulatable : public Shift::InterfaceBase
  {
  S_INTERFACE_TYPE(ManipulatableInterface)
public:

  struct ManipInfo
    {
    ManipInfo() : parentTransform(0), viewTransform(0), displayScale(0)
      {
      }
    const GCViewableTransform *viewTransform;
    const TransformProperty *parentTransform;
    const Shift::FloatProperty *displayScale;
    };

  virtual GCRenderablePointerArray *manipulatableChildren() { return 0; }
  virtual void addManipulators(Shift::Array *parent, const ManipInfo &tr);

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
