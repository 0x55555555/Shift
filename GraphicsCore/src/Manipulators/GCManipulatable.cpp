#include "Manipulators/GCManipulatable.h"
#include "shift/Properties/sattribute.inl"
#include "RCRenderable.h"

void GCManipulatable::addManipulators(
    RCRenderable* renderable,
    Shift::Array *arr,
    const ManipInfo &info)
  {
  RCRenderablePointerArray *children = manipulatableChildren(renderable);
  if(!children)
    {
    return;
    }

  xForeach(auto prop, children->walker<RCRenderablePointer>())
    {
    RCRenderable *geo = prop->pointed();
    if(geo)
      {
      GCManipulatable *manip = geo->findInterface<GCManipulatable>();

      if(manip)
        {
        manip->addManipulators(renderable, arr, info);
        }
      }
    }
  }
