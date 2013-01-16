#include "GCCameraAlignedPlate.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

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
  if(data.registerAttributes)
    {
    auto tr = info->child(&GCCameraAlignedPlate::transform);
    tr->setCompute<computeTransform>();

    auto aff = info->createAffects(data, &tr, 1);

    auto cam = info->add(data, &GCCameraAlignedPlate::cameraTransform, "cameraTransform");
    cam->setAffects(aff, true);

    auto offset = info->add(data, &GCCameraAlignedPlate::offsetTransform, "offsetTransform");
    offset->setAffects(aff, false);

    auto dist = info->add(data, &GCCameraAlignedPlate::distanceFromCamera, "distanceFromCamera");
    dist->setAffects(aff, false);

    auto fov = info->add(data, &GCCameraAlignedPlate::cameraFieldOfView, "cameraFieldOfView");
    fov->setAffects(aff, false);
    }
  }

void GCCameraAlignedPlate::transformPoint(float inX, float inY, float &x, float &y)
  {
  x = inX;
  y = height() - inY;
  }
