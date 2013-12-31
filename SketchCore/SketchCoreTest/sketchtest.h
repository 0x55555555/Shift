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
  SketchTest()
    {
    Shift::TypeRegistry::initiate(core.defaultAllocator());

    SketchCore::initiate();
    }

  ~SketchTest()
    {
    Shift::TypeRegistry::terminate();
    }

private Q_SLOTS:
  void simpleTest();

private:
  Eks::Core core;
  };

#endif // COMPUTETEST_H
