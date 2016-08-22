/**
 * spaint: SmoothingComponent.cpp
 * Copyright (c) Torr Vision Group, University of Oxford, 2016. All rights reserved.
 */

#include "pipelinecomponents/SmoothingComponent.h"

#include "smoothing/LabelSmootherFactory.h"

namespace spaint {

//#################### CONSTRUCTORS ####################

SmoothingComponent::SmoothingComponent(const SmoothingContext_Ptr& context, size_t maxLabelCount, const Settings_CPtr& settings)
: m_context(context)
{
  m_labelSmoother = LabelSmootherFactory::make_label_smoother(maxLabelCount, settings->deviceType);
}

//#################### PUBLIC MEMBER FUNCTIONS ####################

void SmoothingComponent::run(const RenderState_CPtr& renderState)
{
  m_labelSmoother->smooth_labels(renderState->raycastResult, m_context->get_scene().get());
}

}
