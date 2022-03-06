// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2022 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban
// =============================================================================

#include "chrono/assets/ChVisualModel.h"

namespace chrono {

void ChVisualModel::AddShape(std::shared_ptr<ChVisualShape> shape, const ChFrame<>& frame) {
    //// RADU - obsolete this
    shape->Pos = frame.GetPos();
    shape->Rot = frame.GetA();
    ////
    m_shapes.push_back({shape, frame});
}

void ChVisualModel::Clear() {
    m_shapes.clear();
}

void ChVisualModel::Erase(std::shared_ptr<ChVisualShape> shape) {
    auto it = std::find_if(m_shapes.begin(), m_shapes.end(),
                           [&shape](const ShapeInstance& element) { return element.first == shape; });
    if (it != m_shapes.end())
        m_shapes.erase(it);
}

void ChVisualModel::Update(ChPhysicsItem* owner, const ChFrame<>& frame) {
    for (auto& shape : m_shapes) {
        auto xform = frame >> shape.second;
        shape.first->Update(owner, xform);
    }
}

// -----------------------------------------------------------------------------

ChVisualModelInstance::ChVisualModelInstance(std::shared_ptr<ChVisualModel> model) : m_model(model), m_owner(nullptr) {}

void ChVisualModelInstance::Update(const ChFrame<>& frame) {
    m_model->Update(m_owner, frame);
}

}  // namespace chrono
