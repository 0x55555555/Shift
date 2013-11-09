#ifndef RCSCENE_H
#define RCSCENE_H

#include "Shader/RCShadingGroup.h"
#include "RCRenderable.h"
#include "RCCamera.h"
#include "XFrustum.h"

class RCViewableTransform;

class RENDERCORE_EXPORT RCScene : public RCRenderArray, public Eks::CameraCanvasController
  {
  S_ENTITY(RCScene, RCRenderArray);

public:
  RCScene();

  RCCameraPointer activeCamera;
  ComplexTransformProperty cameraProjection;
  TransformProperty cameraTransform;

  void render(Eks::Renderer *, const RenderState &state) const;

  void setCamera(RCViewableTransform *e);
  virtual CameraInterface *camera();

  RCRenderer renderer;

private:
  static void computeRasteriser(RCScene *s);
  RCRuntimeRasteriserState _rasteriserState;
  };

S_PROPERTY_INTERFACE(RCScene)

#endif // RCSCENE_H
