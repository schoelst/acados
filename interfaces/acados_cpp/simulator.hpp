#pragma once

#include "acados_cpp/types.hpp"

namespace acados
{
class simulator
{
 public:
    /// Constructor. Takes a model, which is an acados::Function
    /// and a acados::Dict of options.
    simulator(const Function& model, const Dict& options) {}

    /// Destructor.
    ~simulator() {}

    /// Simulate the model forward for one step.
    virtual Dict simulate(const Dict& in) const = 0;

    /// Print settings to std::out.
    virtual inline void print_settings() const
    {
        for (auto const& s : settings())
        {
            std::cout << s.first << "\t : " << s.second << std::endl;
        }
    }

    /// Returns the current step size.
    virtual inline double step_size() const = 0;

    /// Returns Dict of current settings.
    virtual inline Dict settings() const { return {}; }

    /// Adjust the step size for simulation
    virtual inline void set_step_size(const double step_size) = 0;

 protected:
    // member variables


};  // class simulator

class discrete_model : private simulator
{
 public:
    discrete_model(const Function& model, const Dict& options);
    ~discrete_model();

    /// Simulate the model forward for one step.
    Dict simulate(const Dict& in) const;

    /// Returns the current step size.
    inline double step_size() const;

    /// Returns Dict of current settings.
    inline Dict settings() const;

    /// Adjust the step size for simulation
    inline void set_step_size(const double step_size);

 private:
    // member variables

};  // class discrete_model

}  // namespace acados
