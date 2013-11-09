#include "UI/GCSceneExplorer.h"
#include "XTemporaryAllocator"
#include "QToolBar"
#include "shift/sdatabase.h"
#include "GCManipulatableScene.h"
#include "QTreeView"
#include "QVBoxLayout"
#include "QMenu"
#include "QDebug"

GCSceneExplorer::GCSceneExplorer(RCScene *scene)
    : QWidget(),
      _scene(scene),
      _inputModel(scene->database(),
                  scene,
                  RCRenderable::staticTypeInformation(),
                  RCRenderArray::staticTypeInformation(),
                  RCRenderArray::staticTypeInformation()->childFromName("renderGroup"))
  {
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);

  QToolBar *toolbar = new QToolBar(this);
  layout->addWidget(toolbar);

  QTreeView *view = new QTreeView(this);
  layout->addWidget(view);
  view->setModel(&_inputModel);
  QItemSelectionModel *sel = view->selectionModel();

  QAction *action = toolbar->addAction("Frame");
  connect(action, &QAction::triggered, [this, sel]()
    {
    frameSelection(sel->selectedIndexes());
    });


  connect(sel, &QItemSelectionModel::selectionChanged, [this, sel]()
    {
    updateSelection(sel->selectedIndexes());
    });

  view->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(view, &QTreeView::customContextMenuRequested, [this, view](const QPoint &pt)
    {
    onContextMenu(view->mapToGlobal(pt), view->selectionModel()->selectedIndexes());
    });
  }

void GCSceneExplorer::frameSelection(const QModelIndexList &lst)
  {
  if(!_scene->activeCamera() || lst.isEmpty())
    {
    return;
    }

  Eks::BoundingBox bbox;

  xForeach(auto item, lst)
    {
    Shift::Attribute *attr = _inputModel.attributeFromIndex(lst[0]);
    xAssert(attr);

    if(RCRenderable *r = attr->castTo<RCRenderable>())
      {
      bbox.unite(r->bounds());
      }
    }

  if(!bbox.isValid())
    {
    return;
    }

  _scene->activeCamera()->moveToFit(bbox);
  }

struct ContextData
  {
  RCRenderable* renderable;
  const XScript::InterfaceBase *ifc;
  xsize function;
  };

Q_DECLARE_METATYPE(ContextData)

void GCSceneExplorer::onContextMenu(const QPoint& pt, const QModelIndexList &lst)
  {
  if(!lst.size() == 1)
    {
    return;
    }

  Shift::Attribute *attr = _inputModel.attributeFromIndex(lst[0]);
  xAssert(attr);

  QMenu m(this);

  if(RCRenderable *r = attr->castTo<RCRenderable>())
    {
    auto api = r->apiInterface();
    while(api)
      {
      for(auto i = 0; i < api->functionCount(); ++i)
        {
        auto fn = api->function(i);
        if (fn.argCount == 0)
          {
          QAction* act = m.addAction(fn.name, this, SLOT(onItemAction()));

          ContextData data = { r, api, i };
          act->setData(QVariant::fromValue(data));
          }
        }
      api = api->parent();
      }
    }
  else if(RCRenderablePointer *r = attr->castTo<RCRenderablePointer>())
    {
    m.addAction("[Remove Null Renderable]");
    }

  m.exec(pt);
  }

void GCSceneExplorer::onItemAction()
  {
  QAction *snd = qobject_cast<QAction*>(sender());
  if(!snd)
    {
    return;
    }

  QVariant v = snd->data();
  if(!v.canConvert<ContextData>())
    {
    return;
    }

  ContextData data = v.value<ContextData>();

  auto fn = data.ifc->function(data.function);
  data.ifc->invoke(fn, data.renderable);
  }

void GCSceneExplorer::updateSelection(const QModelIndexList &lst)
  {
  GCManipulatableScene *manScene = _scene->castTo<GCManipulatableScene>();
  if(!manScene)
    {
    return;
    }

  Eks::TemporaryAllocator alloc(manScene->temporaryAllocator());
  Eks::Vector<RCRenderable*> selection(&alloc);

  Shift::Block b(manScene->handler());
  xForeach(const auto& item, lst)
    {
    Shift::Attribute *attrItem = _inputModel.attributeFromIndex(item);
    xAssert(attrItem);

    if(RCRenderable *r = attrItem->castTo<RCRenderable>())
      {
      selection << r;
      }
    else if(RCRenderablePointer *r = attrItem->castTo<RCRenderablePointer>())
      {
      // null renderable... nothing to select, but useful to allow right click and cleanup.
      }
    else
      {
      xAssertFail();
      }
    }

  manScene->select(selection);
  }
