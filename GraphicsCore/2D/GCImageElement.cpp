#include "GCImageElement.h"
#include "spropertyinformationhelpers.h"
#include "spropertycontaineriterators.h"

void computeWidth(GCImageElement *e)
  {
  FloatProperty::ComputeLock l(&e->width);

  *l.data() = e->image().width();
  }

void computeHeight(GCImageElement *e)
  {
  FloatProperty::ComputeLock l(&e->height);

  *l.data() = e->image().height();
  }

S_IMPLEMENT_PROPERTY(GCImageElement, GraphicsCore)

void GCImageElement::createTypeInformation(SPropertyInformationTyped<GCImageElement> *info,
                                           const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto width = info->child(&GCRectangle::width);
    width->setCompute<computeWidth>();
    auto height = info->child(&GCRectangle::height);
    height->setCompute<computeHeight>();

    auto im = info->add(&GCImageElement::image, "image");
    const SPropertyInstanceInformation* affects[] = { width, height };
    im->setAffects(affects, X_ARRAY_COUNT(affects));
    }
  }
