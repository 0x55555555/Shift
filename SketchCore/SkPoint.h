#ifndef SKPOINT_H
#define SKPOINT_H

#include "SkGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"

class SKETCHCORE_EXPORT Point : public Shift::Entity
  {
  S_ENTITY(Point, Entity, 0)
public:

  Shift::Data<float> &x() { return coord[0]; }
  Shift::Data<float> &y() { return coord[1]; }
  const Shift::Data<float> &x() const { return coord[0]; }
  const Shift::Data<float> &y() const { return coord[1]; }

  Shift::Data<float> coord[2];
  };

class SKETCHCORE_EXPORT PointPointer : public Shift::TypedPointer<Point>
  {
  S_PROPERTY(PointPointer, Pointer, 0);
  };

S_TYPED_POINTER_ARRAY_TYPE(SKETCHCORE_EXPORT, PointPointerArray, PointPointer)

S_PROPERTY_INTERFACE(Point)
S_PROPERTY_INTERFACE(PointPointer)
S_PROPERTY_INTERFACE(PointPointerArray)
S_PROPERTY_INTERFACE(Shift::TypedPointerArray<PointPointer>)

#endif // SKPOINT_H
