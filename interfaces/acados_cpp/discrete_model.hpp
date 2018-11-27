#pragma once

#include "acados_cpp/simulator.hpp"

namespace acados
{
class DiscreteModel : public Simulator
{
 public:
    DiscreteModel(const Function& model, const Dict& options);
    ~DiscreteModel();

    /// Simulate the model forward for one step.
    Dict simulate(const Dict& input) const;

    /// Returns the current step size.
    inline double step_size() const;

    /// Returns Dict of current settings.
    inline Dict settings() const;

    /// Adjust the step size for simulation
    inline void set_step_size(const double step_size);

 private:
    // member variables

};  // class DiscreteModel

}  // namespace acados
