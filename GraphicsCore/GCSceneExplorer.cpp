#include "GCSceneExplorer.h"
#include "QToolBar"
#include "shift/sdatabase.h"
#include "3D/GCScene.h"
#include "QTreeView"
#include "QVBoxLayout"
#include "QDebug"

GCSceneExplorer::GCSceneExplorer(GCScene *scene)
    : QWidget(),
      _scene(scene),
      _model(scene->database(), scene->parentEntity(), Shift::DatabaseModel::NoOptions),
      _inputModel(scene->database(),
                  scene,
                  GCRenderable::staticTypeInformation(),
                  GCRenderArray::staticTypeInformation(),
                  GCRenderArray::staticTypeInformation()->childFromName("renderGroup"))
  {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  QToolBar *toolbar = new QToolBar(this);
  layout->addWidget(toolbar);

  toolbar->addAction("Create", this, SLOT(create()));

  QTreeView *view = new QTreeView(this);
  layout->addWidget(view);
  view->setModel(&_inputModel);

  QTreeView *debugView = new QTreeView(this);
  layout->addWidget(debugView);
  debugView->setModel(&_model);
  }

void GCSceneExplorer::create()
  {
  qDebug() << "Create";
  }
