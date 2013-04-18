#include "GCManipulatable.h"
#include "GCRenderable.h"

void GCManipulatable::addManipulators(
    Shift::Array *arr,
    const ManipInfo &info)
  {
  GCRenderablePointerArray *children = manipulatableChildren();
  if(!children)
    {
    return;
    }

  xForeach(auto prop, children->walker<GCRenderablePointer>())
    {
    GCRenderable *geo = prop->pointed();
    if(geo)
      {
      GCManipulatable *manip = geo->findInterface<GCManipulatable>();

      if(manip)
        {
        manip->addManipulators(arr, info);
        }
      }
    }
  }
