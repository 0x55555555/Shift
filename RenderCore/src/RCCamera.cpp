#include "RCCamera.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/Properties/sdata.inl"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "XRenderer.h"
#include "XPlane.h"
#include "Math/Eigen/Geometry"
#include "XLine.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(RCViewableTransformPointer, RenderCore)
S_IMPLEMENT_TYPED_POINTER_TYPE(RCCameraPointer, RenderCore)

S_IMPLEMENT_ABSTRACT_PROPERTY(RCViewableTransform, RenderCore)

void computeView(RCViewableTransform *tr)
  {
  Eks::Transform inv;

  bool invertible = false;
  tr->transform().matrix().computeInverseWithCheck(inv.matrix(),invertible);
  xAssert(invertible);

  tr->viewTransform.computeLock() = inv;
  }

void computeInverseProjection(RCViewableTransform *tr)
  {
  Eks::ComplexTransform inv;

  bool invertible = false;
  tr->projection().matrix().computeInverseWithCheck(inv.matrix(),invertible);
  xAssert(invertible);

  tr->inverseProjection.computeLock() = inv;
  }

void computeViewBounds(RCViewableTransform *tr)
  {
  auto cb = tr->viewBounds.computeLock();

  cb->clear();
  cb->unite(tr->worldSpaceFromUnitSpace(Eks::Vector4D(-1.0f, -1.0f, -1.0f, 1.0f)));
  cb->unite(tr->worldSpaceFromUnitSpace(Eks::Vector4D( 1.0f, -1.0f, -1.0f, 1.0f)));
  cb->unite(tr->worldSpaceFromUnitSpace(Eks::Vector4D(-1.0f,  1.0f, -1.0f, 1.0f)));
  cb->unite(tr->worldSpaceFromUnitSpace(Eks::Vector4D( 1.0f,  1.0f, -1.0f, 1.0f)));
  cb->unite(tr->worldSpaceFromUnitSpace(Eks::Vector4D(-1.0f, -1.0f,  1.0f, 1.0f)));
  cb->unite(tr->worldSpaceFromUnitSpace(Eks::Vector4D( 1.0f, -1.0f,  1.0f, 1.0f)));
  cb->unite(tr->worldSpaceFromUnitSpace(Eks::Vector4D(-1.0f,  1.0f,  1.0f, 1.0f)));
  cb->unite(tr->worldSpaceFromUnitSpace(Eks::Vector4D( 1.0f,  1.0f,  1.0f, 1.0f)));
  }

void RCViewableTransform::createTypeInformation(
    Shift::PropertyInformationTyped<RCViewableTransform> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto upInfo = childBlock.add(&RCViewableTransform::upVector, "upVector");
    upInfo->setDefault(Eks::Vector3D(0.0f, 1.0f, 0.0f));

    auto focalInfo = childBlock.add(&RCViewableTransform::focalDistance, "focalDistance");
    focalInfo->setDefault(1.0f);

    auto bnds = childBlock.add(&RCViewableTransform::viewBounds, "viewBounds");
    bnds->setCompute<computeViewBounds>();

    auto invProjInfo = childBlock.add(&RCViewableTransform::inverseProjection, "inverseProjection");
    invProjInfo->setCompute<computeInverseProjection>();
    invProjInfo->setAffects(data, bnds);

    auto projInfo = childBlock.add(&RCViewableTransform::projection, "projection");
    projInfo->setAffects(data, invProjInfo);

    childBlock.add(&RCViewableTransform::viewportX, "viewportX");
    childBlock.add(&RCViewableTransform::viewportY, "viewportY");
    childBlock.add(&RCViewableTransform::viewportWidth, "viewportWidth");
    childBlock.add(&RCViewableTransform::viewportHeight, "viewportHeight");


    auto viewInfo = childBlock.add(&RCViewableTransform::viewTransform, "viewTransform");
    viewInfo->setCompute<computeView>();

    const Shift::EmbeddedPropertyInstanceInformation *affects[] =
      {
      childBlock.child(&RCViewableTransform::bounds),
      viewInfo,
      bnds
      };

    auto transformInfo = childBlock.overrideChild(&RCViewableTransform::transform);
    transformInfo->setAffects(data, affects, X_ARRAY_COUNT(affects));
    }

  if(data.registerInterfaces)
    {
    XScript::InterfaceBase *ifc = info->apiInterface();

    typedef XScript::MethodToInCa<RCViewableTransform,
                                  void(float, float, float),
                                  &RCViewableTransform::setFocalPoint> FocalPointType;
    typedef XScript::MethodToInCa<RCViewableTransform,
                                  void(float, float, float),
                                  &RCViewableTransform::setPosition> PositionType;

    static XScript::ClassDef<0,0,2> cls = {
      {
      ifc->method<FocalPointType>("setFocalPoint"),
      ifc->method<PositionType>("setPosition"),
      }
    };

    ifc->buildInterface(cls);
    }
  }

RCViewableTransform::RCViewableTransform() : _rotateEnabled(true)
  {
  }

void RCViewableTransform::setPosition(const Eks::Vector3D &point)
  {
  Eks::Transform t = transform();
  t.translation() = point;
  transform = t;
  }

void RCViewableTransform::setFocalPoint(const Eks::Vector3D &aim)
  {
  Eks::Transform t = transform();

  transform = calculateTransform(t.translation(), aim, upVector());

  focalDistance = (aim - t.translation()).norm();
  transform = t;
  }

Eks::Transform RCViewableTransform::calculateTransform(const Eks::Vector3D &camPos, const Eks::Vector3D &camAimPos, const Eks::Vector3D &upVector)
  {
  Eks::Transform t = Eks::Transform::Identity();

  Eks::Vector3D forward = (camAimPos - camPos).normalized();
  Eks::Vector3D side = forward.cross(upVector).normalized();
  Eks::Vector3D up = side.cross(forward);

  t.matrix().col(0).head<3>() = side;
  t.matrix().col(1).head<3>() = up;
  t.matrix().col(2).head<3>() = -forward;

  t.translation() = camPos;

  return t;
  }

Eks::Vector3D RCViewableTransform::focalPoint() const
  {
  return transform().translation() - (transform().matrix().col(2).head<3>() * focalDistance());
  }

void RCViewableTransform::approximatePixelSizeAtDistance(float distanceFromCamera, float &xScale, float &yScale) const
  {
  xuint32 x = viewportX() + ((float)viewportWidth()/2.0f);
  xuint32 y = viewportY() + ((float)viewportHeight()/2.0f);

  Eks::Vector3D a = worldSpaceAtDepthFromScreenSpace(x, y, distanceFromCamera);
  Eks::Vector3D b = worldSpaceAtDepthFromScreenSpace(x+1, y, distanceFromCamera);
  Eks::Vector3D c = worldSpaceAtDepthFromScreenSpace(x, y+1, distanceFromCamera);

  xScale = (a - b).norm();
  yScale = (a - c).norm();
  }


Eks::Transform RCViewableTransform::getPixelScaleFacingTransform(const Eks::Vector3D &worldPosition) const
  {
  Eks::Transform t;

  t = transform();

  float pixelSizeX;
  float pixelSizeY;
  approximatePixelSizeAtDistance((worldPosition - t.translation()).norm(), pixelSizeX, pixelSizeY);

  t.scale(pixelSizeX);

  t.translation() = worldPosition;

  return t;
  }

bool RCViewableTransform::unitViewportCoordinates(xuint32 x, xuint32 y, float &xUnit, float &yUnit) const
  {
  xint32 adjX = x - viewportX();
  xint32 adjY = y - viewportY();
  if(adjX < 0 || adjY < 0 || adjX > (xint32)viewportWidth() || adjY > (xint32)viewportHeight())
    {
    xUnit = 0.0f;
    yUnit = 0.0f;
    return false;
    }

  xUnit = (float)adjX/viewportWidth();
  yUnit = (float)adjY/viewportHeight();

  xUnit *= 2.0f;
  yUnit *= 2.0f;

  xUnit -= 1.0f;
  yUnit -= 1.0f;

  // viewport units are in positive down, flip to posisitve up
  yUnit *= -1.0f;

  return true;
  }

bool RCViewableTransform::screenViewportCoordinates(float xUnit, float yUnit, float &x, float &y) const
  {
  xUnit += 1.0f;
  yUnit += 1.0f;

  xUnit /= 2.0f;
  yUnit /= -2.0f;

  xUnit *= viewportWidth();
  yUnit *= viewportHeight();

  x = viewportX() + xUnit;
  y = viewportY() + yUnit;

  return true;
  }

Eks::Vector3D RCViewableTransform::worldSpaceInPlaneFromScreenSpace(
    xuint32 x,
    xuint32 y,
    const Eks::Plane& plane) const
  {
  const Eks::Vector3D &camPos = transform().translation();
  Eks::Vector3D pos = worldSpaceFromScreenSpace(x, y);

  Eks::Line l(camPos, pos);
  float t = plane.intersection(l);
  return l.sample(t);
  }

Eks::Vector3D RCViewableTransform::worldSpaceFromUnitSpace(const Eks::Vector4D &vpSpace) const
  {
  auto downZAxisWorld = inverseProjection() * vpSpace;
  auto world = transform() * (downZAxisWorld.head<3>() / downZAxisWorld(3));
  return world;
  }

Eks::Vector3D RCViewableTransform::worldSpaceFromScreenSpace(xuint32 x, xuint32 y) const
  {
  Eks::Vector4D vpSpace(0.0f, 0.0f, 1.0f, 1.0f);
  unitViewportCoordinates(x, y, vpSpace(0), vpSpace(1));
  return worldSpaceFromUnitSpace(vpSpace);
  }

bool RCViewableTransform::screenSpaceFromWorldSpace(const Eks::Vector3D &worldPos, Eks::Vector3D &posOut)
  {
  auto eye = viewTransform() * worldPos;

  if(eye.z() > 0.0f)
    {
    return false;
    }

  Eks::Vector4D eyeH;
  eyeH.head<3>() = eye;
  eyeH(3) = 1.0f;

  Eks::Vector4D projected = projection() * eyeH;
  float w = projected.w();

  float x, y;
  screenViewportCoordinates(projected.x() / w, projected.y() / w, x, y);

  posOut = Eks::Vector3D(x, y, projected.z());
  return true;
  }

void RCViewableTransform::zoom(float factor, float, float)
  {
  Eks::Transform t = transform();

  float moveDist = focalDistance() * -0.5f * (factor - 1.0f);
  focalDistance = focalDistance() - moveDist;

  // flip axes because input x and y are in a top left coordinate system
  Eks::Vector3D look = upVector().cross(Eks::Vector3D(1.0f, 0.0f, 0.0f)) * moveDist;

  t.translate(look);

  transform = t;
  }

void RCViewableTransform::moveToFit(const Eks::BoundingBox &bnds)
  {
  Eks::Vector3D pos = bnds.centre();

  Eks::AxisAlignedBoundingBox bbox(Eks::Frame::XYZ(), bnds);

  Eks::Vector3D across = acrossDirection().normalized();
  Eks::Vector3D up = upDirection().normalized();
  Eks::Vector3D look = lookDirection().normalized();

  float minX, maxX;
  bbox.maximumExtents(across, minX, maxX);

  float minY, maxY;
  bbox.maximumExtents(up, minY, maxY);

  float minZ, maxZ;
  bbox.maximumExtents(look, minZ, maxZ);

  float centreX = pos.dot(across);
  float centreY = pos.dot(up);
  float centreZ = pos.dot(look);

  float axisX = xMax(centreX - minX, maxX - centreX) / aspectRatio();
  float axisY = xMax(centreY - minY, maxY - centreY);
  float minDist = centreZ - minZ;

  moveToFit(pos, lookDirection(), xMax(axisX, axisY), minDist);
  }

void RCViewableTransform::track(float x, float y)
  {
  Eks::Transform t = transform();

  float xScale;
  float yScale;
  approximatePixelSizeAtDistance(focalDistance(), xScale, yScale);

  // flip axes because input x and y are in a top left coordinate system
  Eks::Vector3D across = Eks::Vector3D(1.0f, 0.0f, 0.0f) * xScale;
  Eks::Vector3D up = upVector() * yScale;

  x *= -1.0f;

  t.translate(x * across + y * up);

  transform = t;
  }

void RCViewableTransform::dolly(float x, float y)
  {
  rotateAboutPoint(focalPoint(), x, y);
  }

void RCViewableTransform::pan(float x, float y)
  {
  rotateAboutPoint(transform().translation(), x, y);
  }

void RCViewableTransform::rotateAboutPoint(const Eks::Vector3D &point, float x, float y)
  {
  if(_rotateEnabled)
    {
    Eks::Transform t = transform();

    // old translation vector
    float length = (t.translation() - point).norm();

    Eigen::AngleAxisf xRot(x * -0.005f, upVector());
    t.prerotate(xRot);

    Eigen::AngleAxisf yRot(y * -0.005f, Eks::Vector3D(1.0f, 0.0f, 0.0f));
    t.rotate(yRot);


    Eks::Vector3D newLook = t.matrix().col(2).head<3>();
    t.translation() = point + (newLook * length);

    transform = t;
    }
  }

S_IMPLEMENT_ABSTRACT_PROPERTY(RCCamera, RenderCore)

void RCCamera::createTypeInformation(Shift::PropertyInformationTyped<RCCamera> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->createChildrenBlock(data);
    }
  }

S_IMPLEMENT_PROPERTY(RCPerspectiveCamera, RenderCore)

void RCPerspectiveCamera::createTypeInformation(Shift::PropertyInformationTyped<RCPerspectiveCamera> *info,
                                                const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto proj = childBlock.overrideChild(&RCCamera::projection);
    proj->setCompute([](RCPerspectiveCamera *c)
      {
      c->projection.computeLock() = Eks::TransformUtilities::perspective(
        c->fieldOfView(),
        c->aspectRatio(),
        c->nearClip(),
        c->farClip());
      });

    auto affectsProj = childBlock.createAffects(&proj, 1);

    auto width = childBlock.overrideChild(&RCCamera::viewportWidth);
    width->setAffects(affectsProj, true);

    auto height = childBlock.overrideChild(&RCCamera::viewportHeight);
    height->setAffects(affectsProj, false);

    auto fov = childBlock.add(&RCPerspectiveCamera::fieldOfView, "fieldOfView");
    fov->setDefault(Eks::degreesToRadians(45.0f));
    fov->setAffects(affectsProj, false);

    auto nC = childBlock.add(&RCPerspectiveCamera::nearClip, "nearClip");
    nC->setDefault(0.1f);
    nC->setAffects(affectsProj, false);

    auto fC = childBlock.add(&RCPerspectiveCamera::farClip, "farClip");
    fC->setDefault(100.0f);
    fC->setAffects(affectsProj, false);
    }
  }

Eks::Vector3D RCPerspectiveCamera::worldSpaceAtDepthFromScreenSpace(xuint32 x, xuint32 y, float depth) const
  {
  Eks::Vector3D wsFSS(worldSpaceFromScreenSpace(x,y));
  const Eks::Vector3D &camPos = transform().translation();

  Eks::Vector3D camToPoint = wsFSS - camPos;

  return camPos + (camToPoint.normalized() * depth);
  }

void RCPerspectiveCamera::moveToFit(
    const Eks::Vector3D &pos,
    const Eks::Vector3D &lookDir,
    float upDist,
    float upDistDist)
  {
  const float distFromCamera = upDist * tanf(fieldOfView());

  const Eks::Vector3D cameraPos = pos + (lookDir * (distFromCamera + upDistDist));

  setPosition(cameraPos);
  setFocalPoint(pos);
  }
