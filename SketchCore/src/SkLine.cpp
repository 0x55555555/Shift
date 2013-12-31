#include "SkLine.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"
#include "shift/Properties/sdata.inl"
#include "shift/Properties/scontainer.inl"
#include "XPlane.h"

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

void Line::gatherPoints(Eks::Vector<Point *> &l)
  {
  xForeach(auto p, points.walker<ConstraintPointPointer>())
    {
    l << p->pointed();
    }
  }

Line::Solution Line::apply(Point::SolvingMap &m)
  {
  Point::Solve *s = 0;
  xForeach(auto p, points.walker<ConstraintPointPointer>())
    {
    auto &&ptd = m[p->pointed()];
    xAssert(ptd.point == p->pointed());

    if(ptd.lockType == Point::Solve::Full)
      {
      s = &ptd;
      break;
      }
    }

  if(!s)
    {
    xAssertFail();
    return OverConstrained;
    }

  xAssertFail();
  /*auto &&dir = direction();

  xForeach(auto p, points.walker<ConstraintPointPointer>())
    {
    auto &&ptd = m[p->pointed()];
    xAssert(ptd.point == p->pointed());
    if(&ptd != s)
      {
      if(ptd.lockType == Point::Solve::Full)
        {
        // check on line.
        Eks::Line2D l(s->full.position, dir, Eks::Line2D::PointAndDirection);
        float closestT = l.closestPointTo(ptd.full.position);
        Eks::Vector2D pt = l.sample(closestT);

        float dot = (pt-l.position()).normalized().dot(l.direction());
        if(dot < 0.995f)
          {
          return OverConstrained;
          }
        return Constrained;
        }
      else if(ptd.lockType == Point::Solve::Line)
        {
        // point or line
        if(ptd.line.direction().normalized().isApprox(s->line.direction().normalized()))
          {
          if(ptd.line.position().isApprox(s->line.position()))
            {
            return Constrained;
            }
          return OverConstrained;
          }
        else
          {
          Eks::Vector2D pt = s->line.sample(s->line.closestPointOn(ptd.line));
          ptd.lockType = Point::Solve::Full;
          ptd.full.position = pt;
          return Constrained;
          }
        }
      else if(ptd.lockType == Point::Solve::Circle)
        {
        // two points
        Eks::Line2D l(s->full.position, dir, Eks::Line2D::PointAndDirection);
        Eks::Vector2D closestPt = l.sample(l.closestPointTo(ptd.circle.position));

        Eks::Vector2D circleToLine = closestPt - ptd.circle.position;
        float circLineLen = circleToLine.norm();

        if(circLineLen > ptd.circle.radius)
          {
          return OverConstrained;
          }
        else if(qFuzzyCompare(circLineLen, ptd.circle.radius))
          {
          ptd.lockType = Point::Solve::Full;
          ptd.full.position = closestPt;
          return Constrained;
          }

        float distAlongLine = sqrtf(ptd.circle.radius*ptd.circle.radius - circLineLen*circLineLen);

        Eks::Vector2D dirNorm = l.direction().normalized();

        ptd.lockType = Point::Solve::TwoPoint;
        ptd.twoPoint.a = closestPt + dirNorm * distAlongLine;
        ptd.twoPoint.b = closestPt - dirNorm * distAlongLine;

        }
      else if(ptd.lockType == Point::Solve::TwoPoint)
        {
        // one point
        bool aMatch = s->line.sample(s->line.closestPointTo(ptd.twoPoint.a)).isApprox(ptd.twoPoint.a);
        bool bMatch = s->line.sample(s->line.closestPointTo(ptd.twoPoint.b)).isApprox(ptd.twoPoint.b);

        if(aMatch && !bMatch)
          {
          ptd.lockType = Point::Solve::Full;
          ptd.full.position = ptd.twoPoint.a;
          return Constrained;
          }
        else if(!aMatch && bMatch)
          {
          ptd.lockType = Point::Solve::Full;
          ptd.full.position = ptd.twoPoint.b;
          return Constrained;
          }
        else if(!aMatch && !bMatch)
          {
          return OverConstrained;
          }
        return Constrained;
        }
      else if(ptd.lockType == Point::Solve::Free)
        {
        ptd.lockType = Point::Solve::Line;
        ptd.line.setPosition(s->full.position);
        ptd.line.setDirection(dir);
        }
      else
        {
        xAssertFail();
        }
      }
    }*/


  return UnderConstrained;
  }


