#ifndef SKGLOBAL_H
#define SKGLOBAL_H

#include "XGlobal.h"
#include "shift/sglobal.h"

#ifdef SKETCHCORE_BUILD
# define SKETCHCORE_EXPORT X_DECL_EXPORT
#else
# define SKETCHCORE_EXPORT X_DECL_IMPORT
#endif


S_MODULE(SKETCHCORE_EXPORT, SketchCore)

#endif // SKGLOBAL_H
