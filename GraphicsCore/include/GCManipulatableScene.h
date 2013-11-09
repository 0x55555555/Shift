#ifndef RCMANIPULATABLESCENE_H
#define RCMANIPULATABLESCENE_H

#include "GCGlobal.h"
#include "RCScene.h"

class GCVisualManipulator;

class GRAPHICSCORE_EXPORT GCManipulatableScene : public RCScene
  {
  S_ENTITY(GCManipulatableScene, RCScene);

XProperties:
  XROProperty(GCVisualManipulator *, currentManipulator);

public:
  GCManipulatableScene();

  Shift::Array manipulators;

  Shift::FloatProperty manipulatorDisplayScale;

  void initialise();

  void render(Eks::Renderer *, const RenderState &state) const;

  void clearSelection();
  void select(RCRenderable* r);
  void select(const Eks::Vector<RCRenderable*> &r);

  void beginMouseSelection(const Eks::Vector3D &sel);
  void moveMouseSelection(const Eks::Vector3D &sel);
  void endMouseSelection(const Eks::Vector3D &sel);
  bool isMouseSelecting() const;

  void raySelect(const Eks::Vector3D &sel);
  void marqueeSelect(const Eks::Frustum &frus);

  virtual UsedFlags mouseEvent(const MouseEvent &);
  virtual UsedFlags wheelEvent(const WheelEvent &);

private:
  bool _mouseSelecting;
  bool _hasMouseMoved;
  Eks::Vector3D _initialRay;
  Eks::Vector3D _finalRay;

  struct Hit
    {
    Eks::Vector3D position;
    Eks::Vector3D normal;
    RCRenderable *object;
    };

  RCRenderablePointerArray selection;

  void clearManipulators();
  void refreshManipulators();

  Eks::Geometry _bounds;
  Eks::IndexGeometry _boundIndices;
  Eks::Shader *_shader;
  Eks::ShaderConstantData _shaderData;
  const Eks::ShaderVertexLayout *_shaderLayout;
  };

S_PROPERTY_INTERFACE(GCManipulatableScene)

#endif // RCMANIPULATABLESCENE_H
