#include "MCGlobal.h"
#include "styperegistry.h"
#include "spropertygroup.h"

namespace MathsCore
{
void initiate()
  {
  TypeRegistry::addPropertyGroup(propertyGroup());
  }

PropertyGroup &propertyGroup()
  {
  static PropertyGroup grp;
  return grp;
  }
}
