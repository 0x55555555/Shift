#ifndef GCSCENE_H
#define GCSCENE_H

#include "GCShadingGroup.h"
#include "GCRenderable.h"
#include "GCCamera.h"
#include "XFrustum.h"

class GCViewableTransform;

class GRAPHICSCORE_EXPORT GCScene : public GCRenderArray, public Eks::CameraCanvasController
  {
  S_ENTITY(GCScene, GCRenderArray, 0);

public:
  GCScene();

  GCCameraPointer activeCamera;
  ComplexTransformProperty cameraProjection;
  TransformProperty cameraTransform;

  void render(Eks::Renderer *, const RenderState &state) const;

  void setCamera(GCViewableTransform *e);
  virtual CameraInterface *camera();

  GCRenderer renderer;

private:
  static void computeRasteriser(GCScene *s);
  GCRuntimeRasteriserState _rasteriserState;
  };

S_PROPERTY_INTERFACE(GCScene)

class GRAPHICSCORE_EXPORT GCManipulatableScene : public GCScene
  {
  S_ENTITY(GCManipulatableScene, GCScene, 0);

XProperties:
  XROProperty(GCVisualManipulator *, currentManipulator);

public:
  GCManipulatableScene();

  Shift::Array manipulators;

  Shift::FloatProperty manipulatorDisplayScale;

  void initialise();

  void render(Eks::Renderer *, const RenderState &state) const;

  void clearSelection();
  void select(GCRenderable* r);
  void select(const Eks::Vector<GCRenderable*> &r);

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
    GCRenderable *object;
    };

  GCRenderablePointerArray selection;

  void clearManipulators();
  void refreshManipulators();

  Eks::Geometry _bounds;
  Eks::IndexGeometry _boundIndices;
  Eks::Shader *_shader;
  const Eks::ShaderVertexLayout *_shaderLayout;
  };

S_PROPERTY_INTERFACE(GCManipulatableScene)

#endif // GCSCENE_H
