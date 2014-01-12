#include "rendercoretest.h"
#include "QGLWidget"
#include "Utilities/RCBaseProperties.h"
#include "shift/Properties/sdata.inl"
#include "X3DCanvas.h"
#include "XRenderer.h"
#include "XFramebuffer.h"
#include "RCViewport.h"
#include "RCScene.h"
#include "RCTransform.h"
#include "RCGeometry.h"
#include "Shader/RCShader.h"
#include "Shader/RCShadingGroup.h"
#include "XModeller.h"
#include "../examples/Simple3DExample.h"

#ifdef Q_OS_OSX
# define IMAGE_WAIT
# include <unistd.h>
#endif

class TestRenderable : public RCRenderable
  {
  S_ENTITY(TestRenderable, RCRenderable)

public:
  RCGeometry geometry;
  RCRenderer renderer;

  void render(Eks::Renderer *r, const RenderState &) const X_OVERRIDE
    {
    r->drawTriangles(&geometry.runtimeGeometry());
    }
  };

S_IMPLEMENT_PROPERTY(TestRenderable, Test)

void TestRenderable::createTypeInformation(
    Shift::PropertyInformationTyped<TestRenderable> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto geo = childBlock.add(&TestRenderable::geometry, "geometry");
    geo->setCompute([](TestRenderable *r)
      {
      Eks::Renderer *renderer = r->renderer();

      auto lock = r->geometry.runtimeGeometry.computeLock();

      Eks::Modeller m(Eks::Core::globalAllocator(), 100);
      m.drawCube();

      lock->~Geometry();
      new(lock.data()) Eks::Geometry();

      Eks::ShaderVertexLayoutDescription::Semantic semantics[] =
        {
        Eks::ShaderVertexLayoutDescription::Position,
        Eks::ShaderVertexLayoutDescription::Normal
        };

      m.bakeVertices(renderer, semantics, X_ARRAY_COUNT(semantics), lock.data());
      });

    auto renderer = childBlock.add(&TestRenderable::renderer, "renderer");
    renderer->setAffects(data, geo);
    }
  }


class TestShader : public RCShader, public RCShaderInterface
  {
  S_ENTITY(TestShader, RCShader)

public:
  bool initShader(
      RCShader *,
      Eks::Renderer *,
      Shader *) const X_OVERRIDE
    {
    xAssertFail();
    return false;
    }
  };

S_IMPLEMENT_PROPERTY(TestShader, Test)

void TestShader::createTypeInformation(
    Shift::PropertyInformationTyped<TestShader> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    data.module.addInheritedInterface<TestShader, RCShaderInterface>();
    }
  }

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

QImage TestCanvas::getTestImage(const char *name)
  {
  QImage img(name);
  img = img.convertToFormat(canvasFormat());
  img = img.scaled(canvasSize());
  return img;
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
#if 0
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
    QImage testImg = test.getTestImage(":/images/triangletest.png");

    QCOMPARE(test.grab("triangletest"), testImg);
    }
  catch(...)
    {
    return;
    }
  }

void RenderCoreTest::renderCoreSimple()
  {
  TestCanvas test;
  TestDatabase db;

  try
    {
    auto renderer = db.addChild<RCRenderer>();
    auto viewport = db.addChild<RCViewport>();

    auto scene = db.addChild<RCScene>();
    scene->renderer.setInput(renderer);
    viewport->source.setInput(scene);

    test.init = [renderer](Eks::Renderer *r)
      {
      renderer->computeLock() = r;
      };

    test.paint = [scene](Eks::Renderer *r, Eks::FrameBuffer *fb)
      {
      Eks::FrameBufferRenderFrame frame(r, fb);

      RCScene::RenderState state;
      state.framebuffer = nullptr;
      state.transform = Eks::Transform::Identity();

      scene->render(r, state);
      };

    test.resize = [viewport](Eks::Renderer *, xuint32 w, xuint32 h)
      {
      viewport->width = w;
      viewport->height = h;
      };

    auto shadingGroup = db.addChild<RCShadingGroup>();
    scene->renderGroup.addPointer(shadingGroup);

    auto shader = db.addChild<RCShader>();
    shader->renderer.setInput(renderer);
    shadingGroup->shader.setInput(shader);

    auto transform = db.addChild<RCTransform>();
    shadingGroup->renderGroup.addPointer(transform);

    transform->transform = Eks::Transform::Identity();

    auto cube = db.addChild<TestRenderable>();
    cube->renderer.setInput(renderer);
    transform->renderGroup.addPointer(cube);

    QCOMPARE(test.grab("triangletest"), test.getTestImage("rendercoresimple"));
    }
  catch(...)
    {
    return;
    }
#endif
  }

S_IMPLEMENT_TEST
QTEST_MAIN(RenderCoreTest)
