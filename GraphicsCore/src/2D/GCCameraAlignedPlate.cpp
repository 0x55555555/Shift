#include "2D/GCCameraAlignedPlate.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_PROPERTY(GCCameraAlignedPlate, GraphicsCore)

void computeTransform(GCCameraAlignedPlate *plate)
  {
  Eks::Transform tr = plate->cameraTransform();
  tr = tr * plate->offsetTransform();

  const xuint32 width = plate->width();
  const xuint32 height = plate->height();

  const float dist = plate->distanceFromCamera();
  const float fov = plate->cameraFieldOfView();

  tr.translate(Eks::Vector3D(0.0f, 0.0f, -dist));

  float worldHeight = 2.0f * tan(Eks::degreesToRadians(fov * 0.5f)) * dist;
  float scale = worldHeight / height;

  tr.scale(scale);

  tr.translate(Eks::Vector3D(-(int)width/2, -(int)height/2, 0));

  plate->transform = tr;
  }

void GCCameraAlignedPlate::createTypeInformation(Shift::PropertyInformationTyped<GCCameraAlignedPlate> *info,
                                                 const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto tr = childBlock.overrideChild(&GCCameraAlignedPlate::transform);
  tr->setCompute<computeTransform>();

  auto aff = childBlock.createAffects(&tr, 1);

  auto cam = childBlock.add(&GCCameraAlignedPlate::cameraTransform, "cameraTransform");
  cam->setAffects(aff, true);

  auto offset = childBlock.add(&GCCameraAlignedPlate::offsetTransform, "offsetTransform");
  offset->setAffects(aff, false);

  auto dist = childBlock.add(&GCCameraAlignedPlate::distanceFromCamera, "distanceFromCamera");
  dist->setAffects(aff, false);

  auto fov = childBlock.add(&GCCameraAlignedPlate::cameraFieldOfView, "cameraFieldOfView");
  fov->setAffects(aff, false);
  }

void GCCameraAlignedPlate::transformPoint(float inX, float inY, float &x, float &y)
  {
  x = inX;
  y = height() - inY;
  }
