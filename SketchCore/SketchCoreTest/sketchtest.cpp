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
  
  QCOMPARE(solver->constraints.isDirty(), true);
  QCOMPARE(solver->points.isDirty(), true);
  auto a = solver->points.add<Point>();

  QCOMPARE(solver->constraints.isDirty(), false);
  QCOMPARE(solver->points.isDirty(), false);
  a->preGet();
  
  QCOMPARE(a->isDirty(), false);
  QCOMPARE(solver->constraints.isDirty(), false);
  QCOMPARE(solver->points.isDirty(), false);
  auto b = solver->points.add<Point>();
  auto c = solver->points.add<Point>();
  
  QCOMPARE(a->isDirty(), true);

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
  d->distance = 25.0f;
  
  QCOMPARE(solver->constraints.isDirty(), false);
  QCOMPARE(solver->points.isDirty(), false);

  solver->constraints.addPointer(l);
  solver->constraints.addPointer(d);
  solver->constraints.addPointer(d2);
  
  QCOMPARE(a->isDirty(), true);
  
  QCOMPARE(solver->constraints.isDirty(), false);
  QCOMPARE(solver->points.isDirty(), true);

  a->x().value();
  a->y().value();
  b->x().value();
  b->y().value();
  c->x().value();
  c->y().value();
  }

S_IMPLEMENT_TEST
QTEST_APPLESS_MAIN(SketchTest)
