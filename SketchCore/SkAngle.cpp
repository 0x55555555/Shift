#include "SkAngle.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"

S_IMPLEMENT_PROPERTY(Angle, SketchCore)

void Angle::createTypeInformation(
    Shift::PropertyInformationTyped<Angle> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto cb = info->createChildrenBlock(data);
    }
  }
