#include "GCShaderDataBindings.h"
#include "GCTexture.h"

namespace GCShaderDataBindings
{

void Vector3::bindData(DataBlock *data, ResourceBlock *, const Shift::Property *p) const
  {
  const Shift::Vector3DProperty *c = p->uncheckedCastTo<Shift::Vector3DProperty>();

  data->resizeAndCopy(sizeof(Eks::Vector3D), (xuint8*)c->value().data());
  }

void Vector4::bindData(DataBlock *data, ResourceBlock *, const Shift::Property *p) const
  {
  const Shift::ColourProperty *c = p->uncheckedCastTo<Shift::ColourProperty>();

  data->resizeAndCopy(sizeof(Eks::Colour), (xuint8*)c->value().data());
  }

void Texture2DRef::bindData(DataBlock *, ResourceBlock *resources, const Shift::Property *p) const
  {
  const GCTexture2DPointer *c = p->uncheckedCastTo<GCTexture2DPointer>();

  if(c->input())
    {
    const Eks::Texture2D* newValue = &(c->pointed()->value());

    resources->pushBack(newValue);
    }
  }

}
