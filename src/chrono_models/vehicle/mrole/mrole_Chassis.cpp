// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Radu Serban
// =============================================================================
//
// mrole chassis subsystem.
//
// =============================================================================

#include "chrono/assets/ChTriangleMeshShape.h"
#include "chrono/utils/ChUtilsInputOutput.h"

#include "chrono_vehicle/ChVehicleModelData.h"

#include "chrono_models/vehicle/mrole/mrole_Chassis.h"

namespace chrono {
namespace vehicle {
namespace mrole {

// -----------------------------------------------------------------------------
// Static variables
// -----------------------------------------------------------------------------
const double mrole_Chassis::m_mass = 31200.0;
const ChVector<> mrole_Chassis::m_inertiaXX(32786, 175786, 189800);
const ChVector<> mrole_Chassis::m_inertiaXY(0, 0, 0);
const ChVector<> mrole_Chassis::m_COM_loc(-2.5, 0, 0.213);
const ChVector<> mrole_Chassis::m_connector_rear_loc(-5.5, 0, 0.0);
const ChCoordsys<> mrole_Chassis::m_driverCsys(ChVector<>(0.87, 0.27, 1.05), ChQuaternion<>(1, 0, 0, 0));

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
mrole_Chassis::mrole_Chassis(const std::string& name, bool fixed, CollisionType chassis_collision_type)
    : ChRigidChassis(name, fixed) {
    m_inertia(0, 0) = m_inertiaXX.x();
    m_inertia(1, 1) = m_inertiaXX.y();
    m_inertia(2, 2) = m_inertiaXX.z();

    m_inertia(0, 1) = m_inertiaXY.x();
    m_inertia(0, 2) = m_inertiaXY.y();
    m_inertia(1, 2) = m_inertiaXY.z();
    m_inertia(1, 0) = m_inertiaXY.x();
    m_inertia(2, 0) = m_inertiaXY.y();
    m_inertia(2, 1) = m_inertiaXY.z();

    //// TODO:
    //// A more appropriate contact shape from primitives
    // ChVehicleGeometry::BoxShape box1(ChVector<>(0.0, 0.0, 0.1), ChQuaternion<>(1, 0, 0, 0), ChVector<>(2.0, 1.0,
    // 0.2)); ChVehicleGeometry::BoxShape box2(ChVector<>(0.0, 0.0, 0.3), ChQuaternion<>(1, 0, 0, 0), ChVector<>(1.0,
    // 0.5, 0.2));

    m_geometry.m_has_primitives = true;
    // m_geometry.m_vis_boxes.push_back(box1);
    // m_geometry.m_vis_boxes.push_back(box2);

    m_geometry.m_has_mesh = false;
    m_geometry.m_vis_mesh_file = "hmmwv/hmmwv_chassis.obj";

    m_geometry.m_has_collision = (chassis_collision_type != CollisionType::NONE);
    switch (chassis_collision_type) {
        case CollisionType::PRIMITIVES:
            // box1.m_matID = 0;
            // m_geometry.m_coll_boxes.push_back(box1);
            break;
        case CollisionType::HULLS: {
            ChVehicleGeometry::ConvexHullsShape hull("hmmwv/hmmwv_chassis_simple.obj", 0);
            m_geometry.m_coll_hulls.push_back(hull);
            break;
        }
        default:
            break;
    }
}

void mrole_Chassis::CreateContactMaterials(ChContactMethod contact_method) {
    // Create the contact materials.
    // In this model, we use a single material with default properties.
    MaterialInfo minfo;
    m_geometry.m_materials.push_back(minfo.CreateMaterial(contact_method));
}

}  // namespace mrole
}  // end namespace vehicle
}  // end namespace chrono
