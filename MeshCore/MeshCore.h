#ifndef MESHCORE_H
#define MESHCORE_H

#include "XGlobal"
#include "shift/sglobal.h"

#ifdef SHIFTMESHCORE_BUILD
# define MESHCORE_EXPORT X_DECL_EXPORT
#else
# define MESHCORE_EXPORT X_DECL_IMPORT
#endif


class Shift::PropertyGroup;
namespace MeshCore
{
void MESHCORE_EXPORT initiate();
Shift::PropertyGroup &propertyGroup();
}

#endif // GRAPHICSCORE_H
