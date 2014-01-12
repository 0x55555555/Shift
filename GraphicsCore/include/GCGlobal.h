#ifndef GCGLOBAL_H
#define GCGLOBAL_H

#include "XGlobal.h"
#include "shift/sglobal.h"

#ifdef GRAPHICSCORE_BUILD
# define GRAPHICSCORE_EXPORT X_DECL_EXPORT
#else
# define GRAPHICSCORE_EXPORT X_DECL_IMPORT
#endif

#define GCProfileScope 1090
#define GCProfileFunction XProfileFunctionBase(GCProfileScope)
#define GCProfileFunctionScopedBlock(mess) XProfileScopedBlockBase(GCProfileScope, mess)

S_DEFINE_INTERFACE_TYPE(ManipulatableInterface, 100)

S_MODULE(GRAPHICSCORE_EXPORT, GraphicsCore)

#endif // GCGLOBAL_H
