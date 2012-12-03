#include "GCCameraAlignedPlate.h"
#include "spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCCameraAlignedPlate, GraphicsCore)

void computeTransform(GCCameraAlignedPlate *plate)
  {
  XTransform tr = plate->cameraTransform();
  tr = tr * plate->offsetTransform();

  const xuint32 width = plate->width();
  const xuint32 height = plate->height();

  const float dist = plate->distanceFromCamera();
  const float fov = plate->cameraFieldOfView();

  tr.translate(XVector3D(0.0f, 0.0f, -dist));

  float worldHeight = 2.0f * tan(X_DEGTORAD(fov * 0.5f)) * dist;
  float scale = worldHeight / height;

  tr.scale(scale);

  tr.translate(XVector3D(-(int)width/2, -(int)height/2, 0));

  plate->transform = tr;
  }

void GCCameraAlignedPlate::createTypeInformation(PropertyInformationTyped<GCCameraAlignedPlate> *info,
                                                 const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto tr = info->child(&GCCameraAlignedPlate::transform);
    tr->setCompute<computeTransform>();

    auto cam = info->add(&GCCameraAlignedPlate::cameraTransform, "cameraTransform");
    cam->setAffects(tr);

    auto offset = info->add(&GCCameraAlignedPlate::offsetTransform, "offsetTransform");
    offset->setAffects(tr);

    auto dist = info->add(&GCCameraAlignedPlate::distanceFromCamera, "distanceFromCamera");
    dist->setAffects(tr);

    auto fov = info->add(&GCCameraAlignedPlate::cameraFieldOfView, "cameraFieldOfView");
    fov->setAffects(tr);
    }
  }

void GCCameraAlignedPlate::transformPoint(float inX, float inY, float &x, float &y)
  {
  x = inX;
  y = height() - inY;
  }
