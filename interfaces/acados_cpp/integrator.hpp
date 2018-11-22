#ifndef INTERFACES_ACADOS_CPP_INTEGRATOR_HPP_
#define INTERFACES_ACADOS_CPP_INTEGRATOR_HPP_

#include <map>
#include <string>
#include <vector>


#include "acados/utils/types.h"
#include "acados_c/sim_interface.h"


#include "acados_cpp/ocp_nlp/casadi_module.hpp"
#include "acados_cpp/simulator.hpp"
#include "acados_cpp/types.hpp"

// TODO(oj): try to only use C interface, i.e. remove line above and use void pointers
// @tobi: or what do u think?
namespace acados
{
class integrator : public simulator
{
 public:
    // TODO default value of options invalid! Either provide step or make step mandatory argument
    integrator(const Function& model, Dict options = {});

    ~integrator();

    std::vector<double> integrate(std::vector<double> x, std::vector<double> u = {}) const;
    Dict integrate(const Dict& in = {}) const { return in; }
    // std::map<std::string, std::vector<double>> integrate(std::map<std::string,
    // std::vector<double>> in = {}) {return in;}

    void print_settings() const;

    void set_step_size(const double step_size);

    int num_stages() const { return opts_->ns; }
    double step_size() const { return in_->T; }


 private:
    void set_model(const Function& model, const Dict& options = {});

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

    std::map<std::string, casadi_module> module_;
};

}  // namespace acados

#endif  // INTERFACES_ACADOS_CPP_INTEGRATOR_HPP_
