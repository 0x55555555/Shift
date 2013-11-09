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

void Distance::gatherPoints(Eks::Vector<Point *> &p)
  {
  p << a.pointed();
  p << b.pointed();
  }

Distance::Solution Distance::apply(Point::SolvingMap &m)
  {
  auto f = a.pointed();
  auto l = b.pointed();

  if(!f || !l)
    {
    return UnderConstrained;
    }

  auto fixed = &m[f];
  xAssert(fixed->point == f);

  auto loose = &m[l];
  xAssert(loose->point == l);

  if(loose->lockType == Point::Solve::Full)
    {
    std::swap(fixed, loose);
    }

  float dist = distance();

  if(loose->lockType == Point::Solve::Full)
    {
    // check distance correct
    float lDist = (loose->full.position - fixed->full.position).norm();
    return qFuzzyCompare(lDist, dist) ? Constrained : OverConstrained;
    }
  else if(loose->lockType == Point::Solve::Line)
    {
    // two points
    loose->lockType = Point::Solve::TwoPoint;
    loose->twoPoint.a = loose->line.pointAtDistance(dist).head<2>();
    loose->twoPoint.b = loose->line.pointAtDistance(-dist).head<2>();
    }
  else if(loose->lockType == Point::Solve::Circle)
    {
    float lDist = (loose->circle.position - fixed->full.position).norm();
    if(qFuzzyCompare(lDist, loose->circle.radius + dist))
      {
      // point.
      }
    else if (lDist > loose->circle.radius + dist)
      {
      return OverConstrained;
      }
    else
      {
      // http://paulbourke.net/geometry/circlesphere/
      xAssertFail(); // check this...
      // two points
      loose->lockType = Point::Solve::TwoPoint;

      float aRad = loose->circle.radius;
      float bRad = dist;

      float distToLine = (aRad*aRad - bRad*bRad + lDist*lDist) / (2 * lDist);
      float distFromLineToPoint = aRad*aRad - distToLine*distToLine;

      Eks::Vector2D aToB = fixed->full.position - loose->circle.position;

      Eks::Vector2D intermediatePoint = loose->circle.position + (distToLine * aToB / lDist);

      Eks::Vector2D offset = (distFromLineToPoint * aToB) / lDist;

      loose->twoPoint.a = intermediatePoint + offset;
      loose->twoPoint.b = intermediatePoint - offset;
      }
    }
  else if(loose->lockType == Point::Solve::TwoPoint)
    {
    float distA = (loose->twoPoint.a - fixed->full.position).norm();
    float distB = (loose->twoPoint.b - fixed->full.position).norm();

    if(qFuzzyCompare(distA, dist))
      {
      loose->lockType = Point::Solve::Full;
      loose->full.position = loose->twoPoint.a;
      return Constrained;
      }
    else if(qFuzzyCompare(distB, dist))
      {
      loose->lockType = Point::Solve::Full;
      loose->full.position = loose->twoPoint.b;
      return Constrained;
      }

    return OverConstrained;
    }
  else if(loose->lockType == Point::Solve::Free)
    {
    loose->lockType = Point::Solve::Circle;
    loose->circle.position = fixed->full.position;
    loose->circle.radius = dist;
    }
  else
    {
    xAssertFail();
    }

  return UnderConstrained;
  }


