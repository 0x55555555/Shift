#ifndef COMPUTETEST_H
#define COMPUTETEST_H

#include <QtTest>
#include "XCore.h"
#include "Memory/XGlobalAllocator.h"
#include "SkGlobal.h"
#include "shifttestcommon.h"
#include "shift/TypeInformation/styperegistry.h"


class SketchTest : public QObject
  {
  Q_OBJECT

public:
  SketchTest() : registry(core.defaultAllocator())
    {
    registry.installModule(SketchCore::shiftModule());
    }

  ~SketchTest()
    {
    }

private Q_SLOTS:
  void simpleTest();

private:
  Eks::Core core;
  Shift::TypeRegistry registry;
  };

#endif // COMPUTETEST_H
