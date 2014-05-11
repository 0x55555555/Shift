#ifndef GCSCENEEXPLORER_H
#define GCSCENEEXPLORER_H

#if 0

#include "QtWidgets/QWidget"
#include "GCGlobal.h"
#include "shift/QtExtensions/UI/sdatabasemodel.h"
#include "shift/Properties/sattribute.inl"

class RCScene;
class QTreeView;

class GRAPHICSCORE_EXPORT GCSceneExplorer : public QWidget
  {
  Q_OBJECT

public:
  GCSceneExplorer(RCScene *scene);

private Q_SLOTS:
  void onItemAction();

private:
  void frameSelection(const QModelIndexList &lst);
  void updateSelection(const QModelIndexList &lst);
  void onContextMenu(const QPoint& pt, const QModelIndexList &lst);

  RCScene *_scene;
  Shift::InputModel _inputModel;
  };

#endif

#endif // GCSCENEEXPLORER_H
