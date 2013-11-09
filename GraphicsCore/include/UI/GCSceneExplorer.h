#ifndef GCSCENEEXPLORER_H
#define GCSCENEEXPLORER_H

#include "QtWidgets/QWidget"
#include "GCGlobal.h"
#include "shift/UI/sdatabasemodel.h"

class RCScene;
class QTreeView;

class GRAPHICSCORE_EXPORT GCSceneExplorer : public QWidget
  {
  Q_OBJECT

public:
  GCSceneExplorer(RCScene *scene);

private slots:
  void onItemAction();

private:
  void frameSelection(const QModelIndexList &lst);
  void updateSelection(const QModelIndexList &lst);
  void onContextMenu(const QPoint& pt, const QModelIndexList &lst);

  RCScene *_scene;
  Shift::InputModel _inputModel;
  };

#endif // GCSCENEEXPLORER_H
