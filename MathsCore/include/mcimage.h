#ifndef MCIMAGE_H
#define MCIMAGE_H

#if 0

#include "mcsource.h"
#include "shift/Properties/sbaseproperties.h"

class MATHSCORE_EXPORT MCImage : public MCSource
  {
  S_ENTITY(MCImage, MCSource, 0);

public:
  Shift::BoolProperty premultiply;
  Shift::StringProperty filename;

private:
  static void computeImageOutput(MCImage *image);
  XMathsOperation _preOperation;
  };

#endif

#endif // MCIMAGE_H
