#include "SkPoint.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_TYPED_POINTER_TYPE(PointPointer, SketchCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(ConstraintPointPointerArray, SketchCore)

S_IMPLEMENT_PROPERTY(ConstraintPointPointer, SketchCore)

void ConstraintPointPointer::createTypeInformation(
    Shift::PropertyInformationTyped<ConstraintPointPointer> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  auto cb = info->createChildrenBlock(data);
  }

S_IMPLEMENT_PROPERTY(Point, SketchCore)

void Point::createTypeInformation(
    Shift::PropertyInformationTyped<Point> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  auto cb = info->createChildrenBlock(data);

  cb.addArray(&Point::coord, "coord");

  cb.add(&Point::constraint, "constraint");
  }

void ConstraintPointPointer::setPointed(const Point *p)
  {
  Pointer::setPointed(&p->constraint);
  }

Point *ConstraintPointPointer::pointed()
  {
  auto p = Pointer::pointed();
  if(!p)
    {
    return 0;
    }

  auto c = p->parent();
  if(!c)
    {
    xAssertFail();
    return 0;
    }

  return c->castTo<Point>();
  }
