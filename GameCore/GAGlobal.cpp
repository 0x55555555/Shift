#include "GAGlobal.h"
#include "styperegistry.h"

namespace GameCore
{
void initiate()
  {
  STypeRegistry::addPropertyGroup(propertyGroup());
  }

SPropertyGroup &propertyGroup()
  {
  static SPropertyGroup grp;
  return grp;
  }
}
