#include "GCShader.h"
#include "spropertyinformationhelpers.h"
#include "XRenderer.h"
#include "sprocessmanager.h"
#include "shandlerimpl.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderComponentPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(GCShaderComponentPointerArray, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCShaderComponent, GraphicsCore)

void GCShaderComponent::createTypeInformation(SPropertyInformationTyped<GCShaderComponent> *,
                                              const SPropertyInformationCreateData &)
  {
  }

GCShaderComponent::GCShaderComponent()
  {
  }

S_IMPLEMENT_PROPERTY(GCFragmentShaderComponent, GraphicsCore)

void GCFragmentShaderComponent::createTypeInformation(SPropertyInformationTyped<GCFragmentShaderComponent> *,
                                                      const SPropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCVertexShaderComponent, GraphicsCore)

void GCVertexShaderComponent::createTypeInformation(SPropertyInformationTyped<GCVertexShaderComponent> *,
                                                    const SPropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCStaticShader, GraphicsCore)

void GCStaticShader::computeShaderRuntime(GCStaticShader *shader)
  {
  xAssert(SProcessManager::isMainThread());

  GCRuntimeShader::ComputeLock lock(&shader->runtimeShaderCore);

  lock.data()->clear();

  xForeach(auto cmp, shader->walker<GCShaderComponent>())
    {
    XAbstractShader::ComponentType t;
    if(cmp->castTo<GCFragmentShaderComponent>())
      {
      t = XAbstractShader::Fragment;
      }
    else if(cmp->castTo<GCVertexShaderComponent>())
      {
      t = XAbstractShader::Vertex;
      }
    else
      {
      xAssertFail();
      }
    lock.data()->addComponent(t, cmp->value());
    }
  }

void GCStaticShader::setupShaderRuntime(GCStaticShader *shader)
  {
  GCRuntimeShaderInstance::ComputeLock lock(&shader->runtimeShader);

  lock.data()->instance = (XShader*)&shader->runtimeShaderCore();
  xForeach(auto p, shader->walkerFrom((SProperty*)&shader->runtimeShaderCore))
    {
    const GCShaderBindableData *binder = p->interface<GCShaderBindableData>();
    if(binder)
      {
      binder->bindData(lock.data()->instance, p);
      }
    }
  }

void GCStaticShader::createTypeInformation(SPropertyInformationTyped<GCStaticShader> *info,
                                     const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto rtInfoCore = info->add(&GCStaticShader::runtimeShaderCore, "runtimeShaderCore");
    rtInfoCore->setCompute<computeShaderRuntime>();
    rtInfoCore->setComputeLockedToMainThread(true);

    auto rtInfo = info->add(&GCStaticShader::runtimeShader, "runtimeShader");
    rtInfo->setCompute<setupShaderRuntime>();
    rtInfo->setComputeLockedToMainThread(true);
    }
  }

void GCStaticShader::bind(XRenderer *r) const
  {
  r->setShader(runtimeShader().instance);
  }


S_IMPLEMENT_PROPERTY(GCShader, GraphicsCore)

void GCShader::computeShaderRuntime(GCShader *shader)
  {
  xAssert(SProcessManager::isMainThread());

  GCRuntimeShader::ComputeLock lock(&shader->runtimeShaderCore);

  lock.data()->clear();

  xForeach(auto cmpPtr, shader->components.walker<GCShaderComponentPointer>())
    {
    const GCShaderComponent* cmp = cmpPtr->pointed();
    if(cmp)
      {
      XAbstractShader::ComponentType t;
      if(cmp->castTo<GCFragmentShaderComponent>())
        {
        t = XAbstractShader::Fragment;
        }
      else if(cmp->castTo<GCVertexShaderComponent>())
        {
        t = XAbstractShader::Vertex;
        }
      else
        {
        xAssertFail();
        }
      lock.data()->addComponent(t, cmp->value());
      }
    }
  }

void GCShader::setupShaderRuntime(GCShader *shader)
  {
  GCRuntimeShaderInstance::ComputeLock lock(&shader->runtimeShader);

  lock.data()->instance = (XShader*)&shader->runtimeShaderCore();
  xForeach(auto p, shader->walkerFrom((SProperty*)&shader->components))
    {
    const GCShaderBindableData *binder = p->interface<GCShaderBindableData>();
    if(binder)
      {
      binder->bindData(lock.data()->instance, p);
      }
    }
  }


void GCShader::createTypeInformation(SPropertyInformationTyped<GCShader> *info,
                                     const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto rtInfoCore = info->child(&GCShader::runtimeShaderCore);
    rtInfoCore->setCompute<computeShaderRuntime>();

    auto rtInfo = info->child(&GCShader::runtimeShader);
    rtInfo->setCompute<setupShaderRuntime>();

    auto comInfo = info->add(&GCShader::components, "components");
    comInfo->setAffects(rtInfo);
    }
  }
