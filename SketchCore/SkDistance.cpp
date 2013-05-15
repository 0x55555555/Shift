#include "SkDistance.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_PROPERTY(Distance, SketchCore)

void Distance::createTypeInformation(
    Shift::PropertyInformationTyped<Distance> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto cb = info->createChildrenBlock(data);

    cb.add(&Distance::a, "a");
    cb.add(&Distance::b, "b");

    cb.add(&Distance::distance, "distance");
    }
  }


