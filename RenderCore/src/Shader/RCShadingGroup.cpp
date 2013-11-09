#include "Shader/RCShadingGroup.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XGeometry.h"
#include "XModeller.h"
#include "XRenderer.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(RCShadingGroupPointer, RenderCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(RCShadingGroupPointerArray, RenderCore)

S_IMPLEMENT_PROPERTY(RCShadingGroup, RenderCore)

void RCShadingGroup::createTypeInformation(Shift::PropertyInformationTyped<RCShadingGroup> *info,
                                           const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&RCShadingGroup::shader, "shader");
    }
  }

RCShadingGroup::RCShadingGroup()
  {
  }

void RCShadingGroup::render(Eks::Renderer *r, const RenderState &state) const
  {
  const RCShader *s = shader.pointed();
  if(s)
    {
    s->bind(r);
    }

  RCRenderArray::render(r, state);
  }
