#include "GCGlobal.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/TypeInformation/sinterface.h"
#include "shift/Properties/sbaseproperties.h"

#include "3D/GCTexture.h"
#include "3D/GCShadingGroup.h"
#include "3D/GCShaderDataBindings.h"

namespace GraphicsCore
{
void initiate()
  {
  Shift::TypeRegistry::addPropertyGroup(propertyGroup());

  Shift::Interface::addStaticInterface<Shift::Vector3DProperty, GCShaderDataBindings::Vector3>();
  Shift::Interface::addStaticInterface<Shift::ColourProperty, GCShaderDataBindings::Vector4>();
  Shift::Interface::addStaticInterface<GCTexture2DPointer, GCShaderDataBindings::Texture2DRef>();
  Shift::Interface::addStaticInterface<GCShaderConstantDataPointer, GCShaderDataBindings::DataRef>();

  Shift::Interface::addInheritedInterface<GCShadingGroup, GCManipulatable>();
  }

Shift::PropertyGroup &propertyGroup()
  {
  static Shift::PropertyGroup grp;
  return grp;
  }
}
