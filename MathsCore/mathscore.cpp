#include "MCGlobal.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertygroup.h"

namespace MathsCore
{
void initiate()
  {
  Shift::TypeRegistry::addPropertyGroup(propertyGroup());
  }

Shift::PropertyGroup &propertyGroup()
  {
  static Shift::PropertyGroup grp;
  return grp;
  }
}
