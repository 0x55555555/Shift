#ifndef GCGLOBAL_H
#define GCGLOBAL_H

#include "XGlobal.h"
#include "shift/sglobal.h"
#include "shift/TypeInformation/spropertygroup.h"

#ifdef GRAPHICSCORE_BUILD
# define GRAPHICSCORE_EXPORT X_DECL_EXPORT
#else
# define GRAPHICSCORE_EXPORT X_DECL_IMPORT
#endif

#define GCProfileScope 1090
#define GCProfileFunction XProfileFunctionBase(GCProfileScope)
#define GCProfileFunctionScopedBlock(mess) XProfileScopedBlockBase(GCProfileScope, mess)

S_DEFINE_INTERFACE_TYPE(ManipulatableInterface, 52)

namespace GraphicsCore
{
void GRAPHICSCORE_EXPORT initiate();
Shift::PropertyGroup &propertyGroup();
}

#endif // GCGLOBAL_H
