#include "GCShader.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XRenderer.h"
#include "shift/Changes/shandler.inl"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderComponentPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_TYPE(GCShaderPointer, GraphicsCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(GCShaderComponentPointerArray, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCShaderComponent, GraphicsCore)

void GCShaderComponent::createTypeInformation(Shift::PropertyInformationTyped<GCShaderComponent> *,
                                              const Shift::PropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCFragmentShaderComponent, GraphicsCore)

void GCFragmentShaderComponent::createTypeInformation(Shift::PropertyInformationTyped<GCFragmentShaderComponent> *,
                                                      const Shift::PropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCVertexShaderComponent, GraphicsCore)

void GCVertexShaderComponent::createTypeInformation(Shift::PropertyInformationTyped<GCVertexShaderComponent> *,
                                                    const Shift::PropertyInformationCreateData &)
  {
  }

S_IMPLEMENT_PROPERTY(GCShader, GraphicsCore)

void GCShader::createTypeInformation(Shift::PropertyInformationTyped<GCShader> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto rtInfoCore = info->add(&GCShader::runtimeShaderCore, "runtimeShaderCore");
    rtInfoCore->setCompute<computeShaderRuntime>();

    info->add(&GCShader::vertex, "vertex");
    info->add(&GCShader::fragment, "fragment");

    auto rtInfo = info->add(&GCShader::runtimeShader, "runtimeShader");
    rtInfo->setCompute<setupShaderRuntime>();
    }
  }

void GCShader::computeShaderRuntime(GCShader *shader)
  {
  GCRuntimeShader::ComputeLock lock(&shader->runtimeShaderCore);

  lock.data()->~Shader();
  new(lock.data()) Eks::Shader(renderer, &vertex(), &fragment());
  }

void GCShader::setupShaderRuntime(GCShader *shader)
  {
  GCRuntimeShaderInstance::ComputeLock lock(&shader->runtimeShader);

  lock.data()->instance = (Eks::Shader*)&shader->runtimeShaderCore();
  xForeach(auto p, shader->walkerFrom((Property*)&shader->runtimeShaderCore))
    {
    const GCShaderBindableData *binder = p->interface<GCShaderBindableData>();
    if(binder)
      {
      binder->bindData(lock.data()->instance, p);
      }
    }
  }

void GCShader::bind(XRenderer *r) const
  {
  r->setShader(runtimeShader().instance);
  }
