#include "GCProject3D.h"
#include "spropertyinformationhelpers.h"

#include "XOptional"

void computeAlignTransform(GCProject3D *el)
  {
  SPointerComputeLock cLock(&el->camera);
  GCCamera *c = el->camera();
  const XVector3D &pos = el->targetTransform().translation();

  if(!c)
    {
    el->xPosition = 0.0f;
    el->yPosition = 0.0f;
    el->validPosition = false;
    return;
    }

  XVector3D screenPosition;
  if(!c->screenSpaceFromWorldSpace(pos, screenPosition))
    {
    el->xPosition = 0.0f;
    el->yPosition = 0.0f;
    el->validPosition = false;
    return;
    }

  el->xPosition = screenPosition.x();
  el->yPosition = -screenPosition.y();
  el->validPosition = true;
  }

S_IMPLEMENT_PROPERTY(GCProject3D, GraphicsCore)

void GCProject3D::createTypeInformation(PropertyInformationTyped<GCProject3D> *info,
                                    const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto x = info->add(&GCProject3D::xPosition, "xPosition");
    x->setCompute<computeAlignTransform>();

    auto y = info->add(&GCProject3D::yPosition, "yPosition");
    y->setCompute<computeAlignTransform>();

    auto v = info->add(&GCProject3D::validPosition, "validPosition");
    v->setCompute<computeAlignTransform>();

    const EmbeddedPropertyInstanceInformation *aff[] = { x, y };

    auto cam = info->add(&GCProject3D::camera, "camera");
    cam->setAffects(aff, X_ARRAY_COUNT(aff));
    auto taTr = info->add(&GCProject3D::targetTransform, "targetTransform");
    taTr->setAffects(aff, X_ARRAY_COUNT(aff));
    }
  }
