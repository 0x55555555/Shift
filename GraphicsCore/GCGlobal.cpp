#include "GCGlobal.h"
#include "styperegistry.h"

#include "sbaseproperties.h"
#include "3D/GCTexture.h"
#include "3D/GCShadingGroup.h"
#include "3D/GCShaderDataBindings.h"
#include "spropertyinformationhelpers.h"

namespace GraphicsCore
{
void initiate()
  {
  TypeRegistry::addPropertyGroup(propertyGroup());

  PropertyInformation *colInfo = const_cast<PropertyInformation *>(ColourProperty::staticTypeInformation());
  colInfo->addStaticInterface(new GCShaderDataBindings::Vector4);

  PropertyInformation *vec3Info = const_cast<PropertyInformation *>(Vector3DProperty::staticTypeInformation());
  vec3Info->addStaticInterface(new GCShaderDataBindings::Vector3);

  PropertyInformation *texInfo = const_cast<PropertyInformation *>(GCTexturePointer::staticTypeInformation());
  texInfo->addStaticInterface(new GCShaderDataBindings::TextureRef);

  Interface::addInheritedInterface<GCShadingGroup, GCManipulatable>();
  }

PropertyGroup &propertyGroup()
  {
  static PropertyGroup grp;
  return grp;
  }
}
