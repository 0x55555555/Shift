#ifndef GCCAMERA_H
#define GCCAMERA_H

#include "GCGlobal.h"
#include "GCTransform.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XCameraCanvasController.h"
#include "XFrame"

namespace Eks
{
class Renderer;
class Plane;
}

class GRAPHICSCORE_EXPORT GCViewableTransform
    : public GCTransform,
    public Eks::CameraCanvasController::CameraInterface
  {
  S_ABSTRACT_ENTITY(GCViewableTransform, GCTransform)

XProperties:
  XProperty(bool, rotateEnabled, setRotateEnabled);

public:
  GCViewableTransform();

  Shift::Vector3DProperty upVector;
  Shift::FloatProperty focalDistance;

  ComplexTransformProperty projection;
  ComplexTransformProperty inverseProjection;

  Shift::UnsignedIntProperty viewportX;
  Shift::UnsignedIntProperty viewportY;
  Shift::UnsignedIntProperty viewportWidth;
  Shift::UnsignedIntProperty viewportHeight;

  float aspectRatio() const { return (float)viewportWidth() / (float)viewportHeight(); };

  GCBoundingBox viewBounds;

  // inverse of transform
  TransformProperty viewTransform;

  Eks::Vector3D lookDirection()
    {
    return transform().matrix().col(2).head<3>();
    }

  Eks::Vector3D upDirection()
    {
    return transform().matrix().col(1).head<3>();
    }

  Eks::Vector3D acrossDirection()
    {
    return transform().matrix().col(0).head<3>();
    }

  Eks::Frame frame()
    {
    return Eks::Frame(lookDirection(),
                      upDirection(),
                      acrossDirection());
    }

  void setPosition(float x, float y, float z) {setPosition(Eks::Vector3D(x, y, z)); }
  void setPosition(const Eks::Vector3D &point);

  void setFocalPoint(float x, float y, float z) {setFocalPoint(Eks::Vector3D(x, y, z)); }
  void setFocalPoint(const Eks::Vector3D &point);
  static Eks::Transform calculateTransform(
    const Eks::Vector3D &camPos,
    const Eks::Vector3D &camAimPos,
    const Eks::Vector3D &upVector);
  Eks::Vector3D focalPoint() const;

  void approximatePixelSizeAtDistance(float distance, float &x, float &y) const;
  Eks::Transform getPixelScaleFacingTransform(const Eks::Vector3D &worldPosition) const;

  bool unitViewportCoordinates(xuint32 x, xuint32 y, float &xUnit, float &yUnit) const;
  bool screenViewportCoordinates(float xUnit, float yUnit, float &x, float &y) const;

  bool screenSpaceFromWorldSpace(const Eks::Vector3D &worldPos, Eks::Vector3D &coord);

  Eks::Vector3D worldSpaceInPlaneFromScreenSpace(xuint32 x, xuint32 y, const Eks::Plane& plane) const;
  Eks::Vector3D worldSpaceFromScreenSpace(xuint32 x, xuint32 y) const;
  Eks::Vector3D worldSpaceFromUnitSpace(const Eks::Vector4D &vpSpace) const;
  virtual Eks::Vector3D worldSpaceAtDepthFromScreenSpace(xuint32 x, xuint32 y, float depth) const = 0;

  void moveToFit(const Eks::BoundingBox &bbox);
  virtual void moveToFit(
      const Eks::Vector3D &centre,
      const Eks::Vector3D &lookDir,
      float upDist,
      float upDistDist) = 0;

  void zoom(float factor, float x, float y);
  void track(float x, float y);
  void dolly(float x, float y);
  void pan(float x, float y);
  void rotateAboutPoint(const Eks::Vector3D &point, float x, float y);
  };

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCViewableTransformPointer, GCViewableTransform)
S_PROPERTY_ABSTRACT_INTERFACE(GCViewableTransform)

class GRAPHICSCORE_EXPORT GCCamera : public GCViewableTransform
  {
  S_ABSTRACT_ENTITY(GCCamera, GCViewableTransform)
  };

S_PROPERTY_ABSTRACT_INTERFACE(GCCamera)

class GRAPHICSCORE_EXPORT GCPerspectiveCamera : public GCCamera
  {
  S_ENTITY(GCPerspectiveCamera, GCCamera)

public:
  Eks::Vector3D worldSpaceAtDepthFromScreenSpace(xuint32 x, xuint32 y, float depth) const;

  void moveToFit(
      const Eks::Vector3D &centre,
      const Eks::Vector3D &lookDir,
      float upDist,
      float upDistDist) X_OVERRIDE;

  Shift::FloatProperty fieldOfView;

  Shift::FloatProperty nearClip;
  Shift::FloatProperty farClip;
  };

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCCameraPointer, GCCamera)

#endif // GCCAMERA_H
