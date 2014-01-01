#ifndef RENDERTEST_H
#define RENDERTEST_H

#include <QtTest>
#include <functional>
#include "XCore.h"
#include "Memory/XGlobalAllocator.h"
#include "../ShiftCoreTest/shifttestcommon.h"
#include "shift/sentity.h"
#include "shift/Properties/sarray.h"
#include "shift/Properties/sbaseproperties.h"

namespace Eks
{
class Renderer;
class FrameBuffer;
class AbstractCanvas;
}

class RenderCoreTest : public QObject
  {
  Q_OBJECT

public:
  RenderCoreTest()
    {
    Shift::TypeRegistry::initiate(core.defaultAllocator());

    Shift::TypeRegistry::addPropertyGroup(Test::propertyGroup());
    }

  ~RenderCoreTest()
    {
    Shift::TypeRegistry::terminate();
    }

private Q_SLOTS:
  void basicRender();
  void simpleExample();

private:
  Eks::Core core;
  };

class TestCanvas : public QObject
  {
  Q_OBJECT
public:
  TestCanvas();
  ~TestCanvas();

  QImage grab(const char *id);
  void grabSequence(xsize count);

  QSize canvasSize();
  QImage::Format canvasFormat();

public slots:
  void initialise3D(Eks::Renderer *r);
  void paint3D(Eks::Renderer *r, Eks::FrameBuffer *buffer);
  void resize3D(Eks::Renderer *r, xuint32 w, xuint32 h);

public:
  QString outPath;
  QWidget *widget;
  Eks::AbstractCanvas *canvas;

  std::function<void (Eks::Renderer *)> init;
  std::function<void (Eks::Renderer *, Eks::FrameBuffer *)> paint;
  std::function<void (Eks::Renderer *, xuint32, xuint32)> resize;
  };

#endif // RENDERTEST_H
