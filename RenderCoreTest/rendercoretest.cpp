#include "rendercoretest.h"
#include "QGLWidget"
#include "shift/TypeInformation/spropertygroup.h"
#include "X3DCanvas.h"
#include "XRenderer.h"
#include "XFramebuffer.h"
#include "../examples/Simple3DExample.h"

TestCanvas::TestCanvas()
  {
  widget = Eks::Canvas3D::createBest(nullptr, &canvas);

  outPath = "./";

  init = [](Eks::Renderer *) { };
  paint = [](Eks::Renderer *, Eks::FrameBuffer *) { };
  resize = [](Eks::Renderer *, xuint32, xuint32) { };

  connect(widget, SIGNAL(initialise3D(Eks::Renderer *)), this, SLOT(initialise3D(Eks::Renderer*)));
  connect(widget, SIGNAL(paint3D(Eks::Renderer*,Eks::FrameBuffer*)), this, SLOT(paint3D(Eks::Renderer*,Eks::FrameBuffer*)));
  connect(widget, SIGNAL(resize3D(Eks::Renderer*,xuint32,xuint32)), this, SLOT(resize3D(Eks::Renderer*,xuint32,xuint32)));

  widget->resize(640, 480);
  }

TestCanvas::~TestCanvas()
  {
  delete widget;
  }

void TestCanvas::initialise3D(Eks::Renderer *r)
  {
  init(r);
  }

void TestCanvas::paint3D(Eks::Renderer *r, Eks::FrameBuffer *buffer)
  {
  paint(r, buffer);
  }

void TestCanvas::resize3D(Eks::Renderer *r, xuint32 w, xuint32 h)
  {
  resize(r, w, h);
  }

#define SAVE_IMAGES
QImage TestCanvas::grab(
    const char *
#ifdef SAVE_IMAGES
    id
#endif
    )
  {
  auto glWidget = qobject_cast<QGLWidget*>(widget);
  if (glWidget)
    {
    glWidget->show();

    glWidget->updateGL();

    auto scale = widget->devicePixelRatio();
    QImage img = glWidget->grabFrameBuffer();

#ifdef Q_OS_OSX
#define IMAGE_WAIT
#endif

#ifdef IMAGE_WAIT
    sleep(1);
#endif
    glWidget->hide();

    QCOMPARE_FN(img.width() / scale, 640);
    QCOMPARE_FN(img.height() / scale, 480);

  #ifdef SAVE_IMAGES
    QString path = outPath + id + ".png";
    QVERIFY_FN(img.save(path));
  #endif

    return img.convertToFormat(QImage::Format_ARGB32);
    }

  xAssertFail();
  return QImage();
  }

void TestCanvas::grabSequence(xsize count)
  {
  auto glWidget = qobject_cast<QGLWidget*>(widget);
  if (glWidget)
    {
    glWidget->show();

    for(xsize i = 0; i < count; ++i)
      {
      glWidget->updateGL();
      }

    glWidget->hide();
    return;
    }

  xAssertFail();
  return;
  }

QSize TestCanvas::canvasSize()
  {
  auto scale = widget->devicePixelRatio();
  return QSize(widget->width() * scale,
               widget->height() * scale);
  }

QImage::Format TestCanvas::canvasFormat()
  {
  return QImage::Format_ARGB32;
  }

void RenderCoreTest::basicRender()
  {
  TestCanvas test;

  Eks::Colour clearColour;
  test.paint = [&clearColour](Eks::Renderer *r, Eks::FrameBuffer *fb)
    {
    r->setClearColour(clearColour);
    Eks::FrameBufferRenderFrame frame(r, fb);
    };

  try
    {
    QImage testImg(test.canvasSize(), test.canvasFormat());

    clearColour = Eks::Colour(0.0f, 0.0f, 0.0f);
    testImg.fill(Qt::black);
    QCOMPARE(test.grab("blank"), testImg);

    clearColour = Eks::Colour(1.0f, 0.0f, 0.0f);
    testImg.fill(Qt::red);
    QCOMPARE(test.grab("blank_red"), testImg);

    clearColour = Eks::Colour(1.0f, 0.0f, 1.0f);
    testImg.fill(Qt::magenta);
    QCOMPARE(test.grab("blank_purple"), testImg);
    }
  catch(...)
    {
    return;
    }
  }

void RenderCoreTest::simpleExample()
  {
  TestCanvas test;

  Eks::Demo::Simple3DExample example;

  test.init = [&example](Eks::Renderer *r)
    {
    float data[] =
      {
      0,  0,  0,    1, 0, 0,
      0,  10, 0,    0, 1, 0,
      10, 0,  0,    0, 0, 1,
      };

    example.intialise(r, data, X_ARRAY_COUNT(data));
    r->setClearColour(Eks::Colour(0.2, 0.2, 0));
    };

  test.paint = [&example](Eks::Renderer *r, Eks::FrameBuffer *fb)
    {
    Eks::FrameBufferRenderFrame frame(r, fb);

    example.render(r);
    };

  test.resize = [&example](Eks::Renderer *r, xuint32 w, xuint32 h)
    {
    example.resize(r, w, h);
    };

  try
    {
    QImage testImg(":/images/triangletest.png");
    testImg = testImg.convertToFormat(test.canvasFormat());
    testImg = testImg.scaled(test.canvasSize());

    QCOMPARE(test.grab("triangletest"), testImg);
    }
  catch(...)
    {
    return;
    }
  }

S_IMPLEMENT_TEST
QTEST_MAIN(RenderCoreTest)
