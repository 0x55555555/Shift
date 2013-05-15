#include "SkLine.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"

S_IMPLEMENT_PROPERTY(Line, SketchCore)

void Line::createTypeInformation(
    Shift::PropertyInformationTyped<Line> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto cb = info->createChildrenBlock(data);

    cb.add(&Line::points, "points");
    }
  }


