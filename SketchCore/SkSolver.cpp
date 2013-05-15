#include "SkSolver.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"
#include "XTemporaryAllocator"

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

Point *Solver::addPoint()
  {
  auto pt = points.add<Point>();
  return pt;
  }

struct PointSolve
  {
  Point pt;

  enum LockType
    {
    Full,
    Circle,
    Line,
    Free
    } lockType;

  union
    {
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
      Eks::Vector2D position;
      Eks::Vector2D direction;
      } line;
    };
  };

void solvePointSystem(PointSolve &pt, Eks::Vector<PointSolve> &pts, Solver *s)
  {
  Eks::TemporaryAllocator alloc(temporaryAllocator());
  Eks::Vector<Constraint *> constraintsToSolve(&alloc);
  constraintsToSolve.reserve(s->constraints.size());

  pt.lockType = PointSolve::Full;
  }

void Solver::solve()
  {
  Eks::TemporaryAllocator alloc(temporaryAllocator());
  Eks::Vector<PointSolve> pts(&alloc);
  pts.reserve(points.size());

  xForeach(auto pt, points.walker<Point>())
    {
    pts.resize(pts.size()+1);

    PointSolve &sol = pts.back();

    sol.pt = pt;
    sol.lockType = PointSolve::Free;
    }

  while(pts.size())
    {
    auto back = pts.back();
    pts.popBack();
    solvePointSystem(back, pts, this);
    }

  }


