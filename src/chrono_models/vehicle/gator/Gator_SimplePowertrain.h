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
// Simple powertrain model for the Gator vehicle.
// - linear speed-torque curve
// - no torque converter
// - no transmission box (single forward gear, single reverse gear)
//
// =============================================================================

#ifndef GATOR_SIMPLEPOWERTRAIN_H
#define GATOR_SIMPLEPOWERTRAIN_H

#include "chrono_vehicle/ChVehicle.h"
#include "chrono_vehicle/powertrain/ChSimplePowertrain.h"

#include "chrono_models/ChApiModels.h"

namespace chrono {
namespace vehicle {
namespace gator {

/// @addtogroup vehicle_models_gator
/// @{

/// Simple Gator powertrain subsystem (DC motor linear torque-speed characteristic).
class CH_MODELS_API Gator_SimplePowertrain : public ChSimplePowertrain {
  public:
    Gator_SimplePowertrain(const std::string& name);

    ~Gator_SimplePowertrain() {}

    virtual double GetForwardGearRatio() const override { return m_fwd_gear_ratio; }
    virtual double GetReverseGearRatio() const override { return m_rev_gear_ratio; }
    virtual double GetMaxTorque() const override { return m_max_torque; }
    virtual double GetMaxSpeed() const override { return m_max_speed; }

  private:
    static const double m_fwd_gear_ratio;  // forward gear ratio (single gear transmission)
    static const double m_rev_gear_ratio;  // reverse gear ratio
    static const double m_max_torque;      // maximum motor torque
    static const double m_max_speed;       // maximum motor speed
};

/// @} vehicle_models_gator

}  // end namespace gator
}  // end namespace vehicle
}  // end namespace chrono

#endif
