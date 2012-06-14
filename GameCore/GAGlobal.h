#ifndef GAGLOBAL_H
#define GAGLOBAL_H

#include "XGlobal"
#include "sglobal.h"
#include "spropertygroup.h"

#ifdef SHIFTGAMECORE_BUILD
# define GAMECORE_EXPORT X_DECL_EXPORT
#else
# define GAMECORE_EXPORT X_DECL_IMPORT
#endif


namespace GameCore
{
void GAMECORE_EXPORT initiate();
SPropertyGroup &propertyGroup();
}

#endif // GAGLOBAL_H
