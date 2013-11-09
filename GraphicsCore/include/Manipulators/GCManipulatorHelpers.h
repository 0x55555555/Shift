#ifndef GCMANIPULATORHELPER_H
#define GCMANIPULATORHELPER_H

#include "shift/TypeInformation/spropertyinformationhelpers.h"

template <typename Parent, typename Child, typename Fn>
static void embedChildManipulator(
    Shift::PropertyInformationTyped<Parent> *parentInfo,
    const Shift::PropertyInformationCreateData &data,
    Shift::PropertyInformationChildrenCreatorTyped<Parent> &parentBlock,
    Shift::PropertyInstanceInformationTyped<Parent, Child> *inst,
    const Fn &extraInit)
  {
  auto iInfo = parentInfo->extendContainedProperty(data, inst);
  auto block = iInfo->createChildrenBlock(data);

  auto rt = parentBlock.child(&GCVisualManipulator::worldTransform);
  auto sm = parentBlock.child(&GCVisualManipulator::scaleMode);
  auto ds = parentBlock.child(&GCVisualManipulator::displayScale);

  auto iPt = block.overrideChild(&GCVisualManipulator::parentTransform);
  iPt->setDefaultInput(rt);

  auto iSm = block.overrideChild(&GCVisualManipulator::scaleMode);
  iSm->setDefaultInput(sm);

  auto iDs = block.overrideChild(&GCVisualManipulator::displayScale);
  iDs->setDefaultInput(ds);

  extraInit(block);
  }

template <typename Parent, typename Child>
static void embedChildManipulator(
    Shift::PropertyInformationTyped<Parent> *info,
    const Shift::PropertyInformationCreateData &data,
    Shift::PropertyInformationChildrenCreatorTyped<Parent> &parentBlock,
    Shift::PropertyInstanceInformationTyped<Parent, Child> *inst)
  {
  embedChildManipulator(
    info,
    data,
    parentBlock,
    inst,
    [](Shift::PropertyInformationChildrenCreatorTyped<Child> &) { }
    );
  }

#endif // GCMANIPULATORHELPER_H
