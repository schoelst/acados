#ifndef INTERFACES_ACADOS_CPP_INTEGRATOR_HPP_
#define INTERFACES_ACADOS_CPP_INTEGRATOR_HPP_

#include <map>
#include <string>
#include <vector>

#include "acados_c/sim_interface.h"

#include "acados_cpp/ocp_nlp/casadi_module.hpp"
#include "acados_cpp/simulator.hpp"
#include "acados_cpp/types.hpp"

namespace acados
{
class Integrator : public Simulator
{
 public:
    /**
     *
     * model: a CasADi function that contains the system's ODE.
     *
     * options:
     *   MANDATORY ARGUMENTS:
     *     'step_size': integrator step size, double
     *   OPTIONAL ARGUMENTS:
     *     'model_type': type of provided model, model_t default EXPLICIT
     *                   available: [EXPLICIT, IMPLICIT, GNSF_MODEL]
     *     'integrator': integrator type, integrator_t, default ERK
     *                   available: [ERK, IRK, GNSF, LIFTED_IRK]
     *     'use_MX': use MX symbolics, bool, default false
     *     'num_stages': number of stages, size_t, default depends on integrator type
     *     'num_steps': number of steps, size_t, default 1
     *     'newton_iter': number of newton iterations, size_t, default 3
     *     'output_z': output value of algebraic variables, bool, default depends on integrator type
     *     'sens_forw': propagate forward sensitivities, bool, default false
     *     'sens_adj': propagate adjoint sensitivities, bool, default false
     *     'sens_hess': propagate second order sensitivities, bool, default false
     *     'sens_algebraic': propagate sensitivities of algebraic variables, bool, default false
     *     'jac_reuse': jacobians are reused during newton iterations.
     *                  For sensitivity propagation new jacobian evaluations are used.
     *
     *
     */
    Integrator(const Function& model, const Dict& options);
    // Integrator(const Integrator& other);

    ~Integrator();

    std::vector<double> integrate(std::vector<double> x, std::vector<double> u = {}) const;
    Dict integrate(const Dict& input = {}) const;
    Dict simulate(const Dict& input) const { return integrate(input); }

    Dict settings() const;

    void set_step_size(const double step_size);

    int num_stages() const { return opts_->ns; }
    double step_size() const { return in_->T; }


 private:
    void set_model(const Function& model, const Dict& options = {});

    casadi::Function explicit2implicit(const casadi::Function& model);

    sim_solver_config* config_;
    sim_rk_opts* opts_;
    sim_in* in_;
    sim_out* out_;
    sim_solver* solver_;
    sim_solver_plan sim_plan_;

    void* dims_;

    size_t nx_;
    size_t nu_;
    size_t nz_;

    model_t model_type_;
    bool use_MX_;
};

}  // namespace acados

#endif  // INTERFACES_ACADOS_CPP_INTEGRATOR_HPP_
