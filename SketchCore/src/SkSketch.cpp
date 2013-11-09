#include "SkSketch.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"

S_IMPLEMENT_PROPERTY(Sketch, SketchCore)

void Sketch::createTypeInformation(
    Shift::PropertyInformationTyped<Sketch> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto cb = info->createChildrenBlock(data);
    }
  }
