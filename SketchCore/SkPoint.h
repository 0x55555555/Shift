#ifndef SKPOINT_H
#define SKPOINT_H

#include "SkGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XLine.h"

class SKETCHCORE_EXPORT Point : public Shift::Entity
  {
  S_ENTITY(Point, Entity, 0)
public:

    struct Solve
      {
      Solve() : line(Eks::Vector2D::Zero(), Eks::Vector2D::Zero())
        {
        }
      Point *point;

      enum LockType
        {
        Full,
        Circle,
        Line,
        TwoPoint,
        Free
        } lockType;

      struct
        {
        Eks::Vector2D position;
        float radius;
        } circle;

      struct
        {
        Eks::Vector2D position;
        } full;

      struct
        {
        Eks::Vector2D a;
        Eks::Vector2D b;
        } twoPoint;

      Eks::Line2D line;
      };

  typedef Eks::UnorderedMap<Point*, Solve> SolvingMap;

  Shift::Data<float> &x() { return coord[0]; }
  Shift::Data<float> &y() { return coord[1]; }
  const Shift::Data<float> &x() const { return coord[0]; }
  const Shift::Data<float> &y() const { return coord[1]; }

  Shift::Data<float> coord[2];
  Shift::Property constraint;
  };

class SKETCHCORE_EXPORT PointPointer : public Shift::TypedPointer<Point>
  {
  S_PROPERTY(PointPointer, Pointer, 0);
  };

class SKETCHCORE_EXPORT ConstraintPointPointer : public Shift::Pointer
  {
  S_PROPERTY(ConstraintPointPointer, Pointer, 0)

public:
  typedef Point PtrType;
  void setPointed(const Point *p);
  Point *pointed();
  };

S_TYPED_POINTER_ARRAY_TYPE(SKETCHCORE_EXPORT, ConstraintPointPointerArray, ConstraintPointPointer)

S_PROPERTY_INTERFACE(Point)
S_PROPERTY_INTERFACE(PointPointer)
S_PROPERTY_INTERFACE(ConstraintPointPointer)
S_PROPERTY_INTERFACE(ConstraintPointPointerArray)
S_PROPERTY_INTERFACE(Shift::TypedPointerArray<ConstraintPointPointer>)

#endif // SKPOINT_H
