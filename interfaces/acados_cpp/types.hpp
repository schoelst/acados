#pragma once

#include "acados_c/sim_interface.h"
#include "casadi/casadi.hpp"

namespace acados
{
// copy some casadi types to acados namespace
typedef casadi::Dict Dict;
typedef casadi::Function Function;
typedef casadi::SX SX;
typedef casadi::MX MX;

typedef enum
{
    EXPLICIT = 0,
    IMPLICIT,
    GNSF_MODEL
} model_t;

typedef sim_solver_t integrator_t;

}  // namespace acados
