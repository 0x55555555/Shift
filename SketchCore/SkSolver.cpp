#include "SkSolver.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"
#include "XTemporaryAllocator"
#include <map>

S_IMPLEMENT_PROPERTY(Solver, SketchCore)

void Solver::createTypeInformation(
    Shift::PropertyInformationTyped<Solver> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto cb = info->createChildrenBlock(data);

    auto pts = cb.add(&Solver::points, "points");
    pts->setCompute([](Solver *s) { s->solve(); } );

    auto constrs = cb.add(&Solver::constraints, "constraints");
    auto affects = cb.createAffects(&pts, 1);
    constrs->setAffects(affects, true);
    }
  }

struct ConstraintSolve
  {
  Constraint *constraint;
  Eks::Vector<Point::Solve*> points;
  bool solved;
  };

typedef std::multimap<Point *, ConstraintSolve*, std::less<Point *>,
  Eks::TypedAllocator<std::pair<const Point*, ConstraintSolve*> > > PointMap;

Constraint::Solution solvePointSystem(
    Point::Solve &pt,
    Point::SolvingMap &pts,
    const PointMap &ptMap,
    Solver *s)
  {
  if(pt.lockType == Point::Solve::Full)
    {
    return Constraint::UnderConstrained;
    }

  Eks::TemporaryAllocator alloc(s->temporaryAllocator());
  Eks::Vector<Point::Solve *> pointsToSolve(&alloc);
  pointsToSolve.reserve(pts.size());
  Eks::UnorderedMap<Point::Solve*, bool> visited(&alloc);

  auto solution = Constraint::UnderConstrained;

  pt.lockType = Point::Solve::Full;
  pt.full.position = Eks::Vector2D::Zero();
  pointsToSolve << &pt;

  while(pointsToSolve.size())
    {
    auto pt = pointsToSolve.back();
    pointsToSolve.popBack();

    if(visited[pt] == true)
      {
      continue;
      }
    visited[pt] = true;

    qDebug() << pt->point << pt->point->path();
    auto it = ptMap.lower_bound(pt->point);
    auto end = ptMap.upper_bound(pt->point);
    for(; it != end; ++it)
      {
      auto constraint = it->second;
      if(!constraint->solved)
        {
        constraint->solved = true;

        // apply constraint
        auto newSol = constraint->constraint->apply(pts);
        if(newSol == Constraint::OverConstrained)
          {
          return newSol;
          }

        // append points for constraint.
        if(pt->lockType != Point::Solve::Full)
          {
          xForeach(auto pt, constraint->points)
            {
            pointsToSolve << pt;
            }
          }

        solution = xMax(solution, newSol);
        }
      }
    }
  return solution;
  }

void Solver::solve()
  {
  Eks::TemporaryAllocator alloc(temporaryAllocator());
  Eks::UnorderedMap<Point *, Point::Solve> pts(&alloc);
  Eks::Vector<ConstraintSolve> allConstraints(&alloc);
  PointMap pointMap(&alloc);
  pts.reserve((int)points.size());
  allConstraints.reserve(constraints.size());

  Eks::Vector<Point*> tmpPoints(&alloc);

  xForeach(auto ct, constraints.walker<ConstraintPointer>())
    {
    allConstraints.resize(allConstraints.size()+1);

    auto ptd = ct->pointed();
    if(!ptd)
      {
      continue;
      }

    ConstraintSolve &sol = allConstraints.back();

    sol.constraint = ptd;
    sol.solved = false;
    sol.points.allocator() = &alloc;

    tmpPoints.clear();
    ptd->gatherPoints(tmpPoints);
    xForeach(auto pt, tmpPoints)
      {
      sol.points << &pts[pt];
      if(pt)
        {
        qDebug() << pt << pt->path();
        pointMap.insert(std::pair<Point*, ConstraintSolve*>(pt, &sol));
        }
      }
    }

  xForeach(auto pt, points.walker<Point>())
    {
    Point::Solve &sol = pts[pt];

    qDebug() << pt << pt->path();

    sol.point = pt;
    sol.lockType = Point::Solve::Free;
    }

  auto it = pts.begin();
  auto end = pts.end();
  for(; it != end; ++it)
    {
    auto pt = it.value();
    solvePointSystem(pt, pts, pointMap, this);
    }

  }


