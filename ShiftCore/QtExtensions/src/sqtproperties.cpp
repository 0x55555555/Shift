#include "sqtproperties.h"
#include "shift/Properties/sdata.inl"

Eks::String::IStream &operator>>(Eks::String::IStream &str, QUuid &u)
  {
  std::string data;
  str >> data;
  u = QUuid(data.data());
  return str;
  }

namespace Shift
{

IMPLEMENT_POD_PROPERTY(SHIFT_EXPORT, Shift, QUuid, FullData, QUuid)

namespace detail
{

void assignTo(const Attribute *f, Data<QUuid> *to)
  {
  const Data<QUuid> *sProp = f->castTo<Data<QUuid>>();
  if(sProp)
    {
    to->assign(sProp->value());
    return;
    }
  }

void detail::UuidPropertyInstanceInformation::initiateAttribute(
    Attribute *propertyToInitiate,
    AttributeInitialiserHelper *helper) const
  {
  Property::EmbeddedInstanceInformation::initiateAttribute(propertyToInitiate, helper);

  NoUpdateBlock b(propertyToInitiate);

  auto obj = propertyToInitiate->uncheckedCastTo<Data<QUuid>>();
  obj->computeLock() = QUuid::createUuid();
  }
}

TypedSerialisationValue<QUuid>::TypedSerialisationValue(const QUuid *t)
    : _val(t)
  {
  }

Eks::String TypedSerialisationValue<QUuid>::asUtf8(Eks::AllocatorBase *a) const
  {
  Eks::String ret(a);

  ret = _val->toByteArray().constData();
  return ret;
  }

}

std::hash<QUuid>::result_type std::hash<QUuid>::operator()(argument_type const& s) const
  {
  auto h1 = hash<uint>()(s.data1);
  auto h2 = hash<ushort>()(s.data2);
  auto h3 = hash<ushort>()(s.data3);
  auto h41 = hash<uchar>()(s.data4[0]);
  auto h42 = hash<uchar>()(s.data4[1]);
  auto h43 = hash<uchar>()(s.data4[2]);
  auto h44 = hash<uchar>()(s.data4[3]);

  return h1 ^ h2 ^ h3 ^ h41 ^ h42 ^ h43 ^ h44;
  }

