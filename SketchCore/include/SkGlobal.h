#ifndef SKGLOBAL_H
#define SKGLOBAL_H

#include "XGlobal"
#include "shift/sglobal.h"
#include "shift/TypeInformation/spropertygroup.h"

#ifdef SKETCHCORE_BUILD
# define SKETCHCORE_EXPORT X_DECL_EXPORT
#else
# define SKETCHCORE_EXPORT X_DECL_IMPORT
#endif


namespace SketchCore
{
void SKETCHCORE_EXPORT initiate();
Shift::PropertyGroup &propertyGroup();
}

#endif // SKGLOBAL_H
