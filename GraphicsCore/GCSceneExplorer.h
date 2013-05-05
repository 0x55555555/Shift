#ifndef GCSCENEEXPLORER_H
#define GCSCENEEXPLORER_H

#include "QtWidgets/QWidget"
#include "GCGlobal.h"
#include "shift/UI/sdatabasemodel.h"

class GCScene;

class GRAPHICSCORE_EXPORT GCSceneExplorer : public QWidget
  {
  Q_OBJECT

public:
  GCSceneExplorer(GCScene *scene);

public slots:
  void create();

private:
  GCScene *_scene;
  Shift::DatabaseModel _model;
  Shift::InputModel _inputModel;
  };

#endif // GCSCENEEXPLORER_H
