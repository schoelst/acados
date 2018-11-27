#include "acados_cpp/discrete_model.hpp"

namespace acados
{
DiscreteModel::DiscreteModel(const Function& model, const Dict& options) : Simulator(model, options)
{
    // TODO implement this
}

DiscreteModel::~DiscreteModel()
{
    // TODO implement this
}

Dict DiscreteModel::simulate(const Dict& input) const
{
    // TODO implement this
    throw std::runtime_error("not implemented");
    return input;
}

Dict DiscreteModel::settings() const
{
    // TODO implement this
    throw std::runtime_error("not implemented");
    return {};
}

double DiscreteModel::step_size() const
{
    // TODO implement this
    throw std::runtime_error("not implemented");
    return 42;
}

void DiscreteModel::set_step_size(const double step_size)
{
    // TODO implement this
    throw std::runtime_error("not implemented");
}

}  // namespace acados
