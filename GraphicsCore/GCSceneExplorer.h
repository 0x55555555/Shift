#ifndef GCSCENEEXPLORER_H
#define GCSCENEEXPLORER_H

#include "QWidget"

class GCScene;

class GCSceneExplorer : public QWidget
  {
public:
  GCSceneExplorer(GCScene *scene, QWidget *parent=0);

private:
  GCScene *_scene;
  };

#endif // GCSCENEEXPLORER_H
