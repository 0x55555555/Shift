#if 0

#include "mcimage.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "QImage"

void MCImage::computeImageOutput(MCImage *image)
  {
  QImage imInput(image->filename().toQString());

  MCMathsOperation::ComputeLock l(&image->output);
  if(imInput.isNull())
    {
    l.data()->load(XMathsOperation::None, 0, 0, 0, 0, 0, Eks::VectorI2D::Zero());
    }

  Eks::VectorI2D transform = Eks::VectorI2D::Zero();

  xsize channels = 3;
  if(imInput.hasAlphaChannel())
    {
    channels = 4;
    if(image->premultiply())
      {
      imInput.convertToFormat(QImage::Format_ARGB32_Premultiplied);
      }
    else
      {
      imInput.convertToFormat(QImage::Format_ARGB32);
      }
    }
  else
    {
    if(image->premultiply())
      {
      imInput.convertToFormat(QImage::Format_ARGB32_Premultiplied);
      }
    else
      {
      imInput.convertToFormat(QImage::Format_RGB32);
      }
    }

  const uchar *bits = imInput.bits();

  if(bits)
    {
    xsize stride = imInput.bytesPerLine()/imInput.width();

    image->_preOperation.load(XMathsOperation::Byte, (void*)bits, stride, imInput.width(), imInput.height(), channels, transform);
    }
  else
    {
    image->_preOperation.load(XMathsOperation::None, 0, 0, 0, 0, channels, transform);
    }

  xuint32 shuffleMask = XMathsOperation::shuffleMask(2, 1, 0, 3);
  l.data()->shuffle(image->_preOperation, shuffleMask);
  }

S_IMPLEMENT_PROPERTY(MCImage, MathsCore)

void MCImage::createTypeInformation(Shift::PropertyInformationTyped<MCImage> *info,
                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outputInst = info->child(&MCImage::output);
    outputInst->setCompute<computeImageOutput>();

    auto preMultInst = info->add(data, &MCImage::premultiply, "premultiply");
    preMultInst->setAffects(data, outputInst);

    auto filenameInst = info->add(data, &MCImage::filename, "filename");
    filenameInst->setAffects(data, outputInst);
    }
  }

#endif
