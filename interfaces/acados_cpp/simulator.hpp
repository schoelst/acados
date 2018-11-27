#pragma once

#include "acados_cpp/types.hpp"

namespace acados
{
class Simulator
{
 public:
    /// Constructor. Takes a model, which is an acados::Function
    /// and a acados::Dict of options.
    /// Simulator is the common base class of integrator and discrete_model
    Simulator(const Function& model, const Dict& options) {}

    /// Destructor.
    virtual ~Simulator() {}

    /// Simulate the model forward for one step.
    virtual Dict simulate(const Dict& input) const = 0;

    /// Returns the current step size.
    virtual inline double step_size() const = 0;

    /// Returns Dict of current settings.
    virtual inline Dict settings() const { return {}; }

    /// Adjust the step size for simulation
    virtual inline void set_step_size(const double step_size) = 0;
    /// Print settings to std::out.
    virtual inline void print_settings() const
    {
        for (auto const& s : settings())
        {
            std::cout << s.first << "\t : " << s.second << std::endl;
        }
    }


 protected:
    // member variables


};  // class Simulator

}  // namespace acados
