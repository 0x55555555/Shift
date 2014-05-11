#include "Shader/RCShader.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XRenderer.h"
#include "shift/Properties/sdata.inl"
#include "shift/Changes/shandler.inl"

void computeData(RCShaderConstantData *d)
  {
  Eks::Renderer *r = d->renderer.value();
  if(!r)
    {
    return;
    }

  auto walker = d->walkerFrom(&d->runtimeData);
  auto it = ++walker.begin();
  auto end = walker.end();

  Eks::TemporaryAllocator alloc(d->temporaryAllocator());
  RCShaderBindableData::DataBlock data(&alloc);

  for(; it != end; ++it)
    {
    auto p = *it;
    const RCShaderBindableData *binder = p->findInterface<RCShaderBindableData>();

    xAssert(binder);
    binder->bindData(&data, p);
    }

  auto lock = d->runtimeData.computeLock();

  if(!lock->isValid())
    {
    Eks::Vector<Eks::ShaderConstantDataDescription> descs(&alloc);

    it = ++walker.begin();
    for(; it != end; ++it)
      {
      auto p = *it;
      const RCShaderBindableData *binder = p->findInterface<RCShaderBindableData>();

      descs.resize(descs.size()+1);
      binder->getDescription(descs.back(), p);
      }

    Eks::ShaderConstantData::delayedCreate(*lock.data(), r, descs.data(), descs.size(), data.data());
    }
  else
    {
    lock->update(data.data());
    }
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(RCShaderConstantDataPointer, RenderCore)

S_IMPLEMENT_PROPERTY(RCShaderConstantData, RenderCore)

void RCShaderConstantData::createTypeInformation(
    Shift::PropertyInformationTyped<RCShaderConstantData> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto rend = childBlock.add(&RCShaderConstantData::renderer, "renderer");

  auto rtInfo = childBlock.add(&RCShaderConstantData::runtimeData, "runtimeData");

  rtInfo->setCompute<computeData>();
  rend->setAffects(data, rtInfo);
  }


S_IMPLEMENT_PROPERTY(RCShader, RenderCore)

void RCShader::createTypeInformation(Shift::PropertyInformationTyped<RCShader> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto rtInfo = childBlock.add(&RCShader::runtimeShader, "runtimeShader");
  rtInfo->setCompute<setupShaderRuntime>();

  auto rtInfoCore = childBlock.add(&RCShader::runtimeShaderCore, "runtimeShaderCore");
  rtInfoCore->setAffects(data, rtInfo);

  auto r = childBlock.add(&RCShader::renderer, "renderer");
  r->setAffects(data, rtInfoCore);
  }

void RCShader::setupShaderRuntime(RCShader *shader)
  {
  RCRuntimeShaderInstance::ComputeLock lock(&shader->runtimeShader);

  Eks::Renderer *r = shader->renderer.value();
  if(!r)
    {
    return;
    }

  shader->resources.clear();
  shader->constantDatas.clear();

  lock.data()->instance = (Eks::Shader*)&shader->runtimeShaderCore();
  xForeach(auto p, shader->walkerFrom((Property*)&shader->runtimeShaderCore))
    {
    const RCShaderBindableResource *binder = p->findInterface<RCShaderBindableResource>();
    if(binder)
      {
      binder->bindResource(&shader->constantDatas, &shader->resources, p);
      }
    }
  }

void RCShader::bind(Eks::Renderer *r) const
  {
  Eks::Shader *s = runtimeShader().instance;
  r->setShader(s, &_layout);

  s->setShaderConstantDatas(0, constantDatas.size(), constantDatas.data());
  s->setShaderResources(0, resources.size(), resources.data());
  }


S_IMPLEMENT_ABSTRACT_PROPERTY(RCStaticShader, RenderCore)

void RCStaticShader::createTypeInformation(Shift::PropertyInformationTyped<RCStaticShader> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto rtInfoCore = childBlock.overrideChild(&RCShader::runtimeShaderCore);
  rtInfoCore->setCompute<computeShaderRuntime>();
  }

void RCStaticShader::computeShaderRuntime(RCStaticShader *shader)
  {
  RCRuntimeShader::ComputeLock lock(&shader->runtimeShaderCore);

  Eks::Renderer *r = shader->renderer.value();
  if(!r)
    {
    return;
    }

  RCShaderInterface::Shader shaderStruct =
    {
    lock.data(),
    &shader->fragment,
    &shader->vertex,
    &shader->_layout
    };

  RCShaderInterface *ifc = shader->findInterface<RCShaderInterface>();
  xAssert(ifc);
  if(!ifc->initShader(
       shader,
       r,
       &shaderStruct))
    {
    xAssertFail();
    return;
    }
  }

S_IMPLEMENT_TYPED_POINTER_TYPE(RCShaderPointer, RenderCore)
