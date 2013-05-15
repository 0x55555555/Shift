#include "SkPoint.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_TYPED_POINTER_TYPE(PointPointer, SketchCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(PointPointerArray, SketchCore)

S_IMPLEMENT_PROPERTY(Point, SketchCore)

void Point::createTypeInformation(
    Shift::PropertyInformationTyped<Point> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto cb = info->createChildrenBlock(data);

    cb.addArray(&Point::coord, "coord");
    }
  }
