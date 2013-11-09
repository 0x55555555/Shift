#include "SkAngle.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_PROPERTY(Angle, SketchCore)

void Angle::createTypeInformation(
    Shift::PropertyInformationTyped<Angle> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto cb = info->createChildrenBlock(data);

    cb.add(&Angle::origin, "origin");
    cb.add(&Angle::a, "a");
    cb.add(&Angle::b, "b");

    cb.add(&Angle::angle, "angle");
    }
  }

void Angle::gatherPoints(Eks::Vector<Point *> &p)
  {
  p << origin.pointed();
  p << a.pointed();
  p << b.pointed();
  }

Angle::Solution Angle::apply(Point::SolvingMap &m)
  {
  (void)m;
  return UnderConstrained;
  }
