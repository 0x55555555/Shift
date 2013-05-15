#include "sketchtest.h"
#include "SkSketch.h"
#include "SkPoint.h"
#include "SkLine.h"
#include "SkDistance.h"
#include "SkAngle.h"
#include "SkSolver.h"
#include "shift/Properties/sdata.inl"

void SketchTest::simpleTest()
  {
  TestDatabase db;

  auto sk = db.addChild<Sketch>();

  auto solver = sk->addChild<Solver>();
  auto a = solver->addPoint();
  auto b = solver->addPoint();
  auto c = solver->addPoint();

  auto l = sk->addChild<Line>();
  l->points.addPointer(a);
  l->points.addPointer(b);
  l->points.addPointer(c);

  auto d = sk->addChild<Distance>();
  d->a.setPointed(a);
  d->b.setPointed(b);
  d->distance = 50.0f;

  auto d2 = sk->addChild<Distance>();
  d->a.setPointed(c);
  d->b.setPointed(b);
  d->distance = -25.0f;

  solver->constraints.addPointer(l);
  solver->constraints.addPointer(d);
  solver->constraints.addPointer(d2);

  a->x().value();
  a->y().value();
  b->x().value();
  b->y().value();
  c->x().value();
  c->y().value();
  }

S_IMPLEMENT_TEST
QTEST_APPLESS_MAIN(SketchTest)
