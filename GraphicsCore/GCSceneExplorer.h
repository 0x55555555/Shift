#ifndef GCSCENEEXPLORER_H
#define GCSCENEEXPLORER_H

#include "QtWidgets/QWidget"
#include "GCGlobal.h"
#include "shift/UI/sdatabasemodel.h"

class GCScene;
class QTreeView;

class GRAPHICSCORE_EXPORT GCSceneExplorer : public QWidget
  {
  Q_OBJECT

public:
  GCSceneExplorer(GCScene *scene);

public slots:
  void create();

private:
  void updateSelection(const QModelIndexList &lst);
  void onContextMenu(const QPoint& pt, const QModelIndexList &lst);

  GCScene *_scene;
  Shift::InputModel _inputModel;
  };

#endif // GCSCENEEXPLORER_H
