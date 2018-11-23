#include "acados_cpp/discrete_model.hpp"

namespace acados
{
discrete_model::discrete_model(const Function& model, const Dict& options)
    : simulator(model, options)
{
    // TODO implement this
}

discrete_model::~discrete_model()
{
    // TODO implement this
}

Dict discrete_model::simulate(const Dict& input) const
{
    // TODO implement this
    throw std::runtime_error("not implemented");
    return input;
}

Dict discrete_model::settings() const
{
    // TODO implement this
    throw std::runtime_error("not implemented");
    return {};
}

double discrete_model::step_size() const
{
    // TODO implement this
    throw std::runtime_error("not implemented");
    return 42;
}

void discrete_model::set_step_size(const double step_size)
{
    // TODO implement this
    throw std::runtime_error("not implemented");
}

}  // namespace acados
