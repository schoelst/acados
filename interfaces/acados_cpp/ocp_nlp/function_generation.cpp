
#include "acados_cpp/ocp_nlp/function_generation.hpp"

#include <vector>

namespace acados
{
using std::string;
using std::vector;

casadi_module generate_nls_residual(const casadi::Function& residual, string output_folder)
{
    casadi::SX x = residual.sx_in(0);
    casadi::SX u = residual.sx_in(1);

    vector<casadi::SX> xu{x, u};
    vector<casadi::SX> ux{u, x};

    casadi::SX r_new = casadi::SX::vertcat(residual(xu));
    casadi::SX r_jacT = casadi::SX::jacobian(r_new, casadi::SX::vertcat(ux)).T();

    casadi::Function r_fun(residual.name() + "_nls_res", {casadi::SX::vertcat(ux)},
                           {r_new, r_jacT});

    return casadi_module(r_fun, output_folder);
}


/* IMPLICIT MODEL */
casadi_module generate_impl_ode_fun(const casadi::Function& model, string output_folder)
{
    casadi::SX x = model.sx_in(0);
    casadi::SX xdot = model.sx_in(1);
    casadi::SX u = model.sx_in(2);
    casadi::SX z = model.sx_in(3);

    casadi::SX rhs = casadi::SX::vertcat(model(vector<casadi::SX>({x, xdot, u, z})));

    casadi::Function fun(model.name() + "_impl_ode_fun", {x, xdot, u, z}, {rhs});

    return casadi_module(fun, output_folder);
}

casadi_module generate_impl_ode_fun_jac_x_xdot_z(const casadi::Function& model, string output_folder)
{
    casadi::SX x = model.sx_in(0);
    casadi::SX xdot = model.sx_in(1);
    casadi::SX u = model.sx_in(2);
    casadi::SX z = model.sx_in(3);
    casadi::SX w = casadi::SX::vertcat(vector<casadi::SX>({x, u}));

    casadi::SX rhs = casadi::SX::vertcat(model(vector<casadi::SX>({x, xdot, u, z})));


    casadi::SX jac_x = casadi::SX::jacobian(rhs, x);
    // casadi::SX jac_u = casadi::SX::jacobian(rhs, u);
    casadi::SX jac_z = casadi::SX::jacobian(rhs, z);
    casadi::SX jac_xdot = casadi::SX::jacobian(rhs, xdot);

    casadi::Function fun(model.name() + "_impl_ode_fun_jac_x_xdot_z",
                        {x, xdot, u, z}, {jac_x, jac_xdot, jac_z});

    return casadi_module(fun, output_folder);
}

/* EXPLICIT MODEL */
casadi_module generate_forward_vde(const casadi::Function& model, string output_folder)
{
    casadi::SX x = model.sx_in(0);
    casadi::SX u = model.sx_in(1);

    int_t nx = x.size1();
    int_t nu = u.size1();

    casadi::SX rhs = casadi::SX::vertcat(model(vector<casadi::SX>({x, u})));

    casadi::SX Sx = casadi::SX::sym("Sx", nx, nx);
    casadi::SX Su = casadi::SX::sym("Su", nx, nu);

    casadi::SX vde_x = casadi::SX::jtimes(rhs, x, Sx);
    casadi::SX vde_u = casadi::SX::jacobian(rhs, u) + casadi::SX::jtimes(rhs, x, Su);

    casadi::Function vde_fun(model.name() + "_expl_vde_for", {x, Sx, Su, u}, {rhs, vde_x, vde_u});

    return casadi_module(vde_fun, output_folder);
}


casadi_module generate_expl_ode_fun(const casadi::Function& model, string output_folder)
{
    casadi::SX x = model.sx_in(0);
    casadi::SX u = model.sx_in(1);

    // int_t nx = x.size1();
    // int_t nu = u.size1();

    casadi::SX rhs = casadi::SX::vertcat(model(vector<casadi::SX>({x, u})));

    casadi::Function fun(model.name() + "_expl_ode_fun", {x, u}, {rhs});

    return casadi_module(fun, output_folder);
}


casadi_module generate_expl_vde_adj(const casadi::Function& model, string output_folder)
{
    casadi::SX x = model.sx_in(0);
    casadi::SX u = model.sx_in(1);

    casadi::SX rhs = casadi::SX::vertcat(model(vector<casadi::SX>({x, u})));

    int_t nx = x.size1();

// MATLAB Code:
// adj = jtimes(f_expl,[x;u],lambdaX,true);
// expl_vde_adj = Function([model_name,'_expl_vde_adj'],{x,lambdaX,u},{adj});
    casadi::SX lambdaX = casadi::SX::sym("lambdaX", nx, 1);
    casadi::SX w = casadi::SX::vertcat(vector<casadi::SX>({x, u}));
    casadi::SX adj = casadi::SX::jtimes(rhs, w, lambdaX, true);

    casadi::Function fun(model.name() + "_expl_vde_adj", {x, lambdaX, u}, {adj});

    return casadi_module(fun, output_folder);
}

// TODO(oj): remove this, it is not used in erk
casadi_module generate_ode_jacobian(const casadi::Function& model, string output_folder)
{
    casadi::SX x = model.sx_in(0);
    casadi::SX u = model.sx_in(1);

    int_t nx = x.size1();
    int_t nu = u.size1();

    casadi::SX rhs = casadi::SX::vertcat(model(vector<casadi::SX>({x, u})));

    casadi::SX Sx = casadi::SX::sym("Sx", nx, nx);
    casadi::SX Su = casadi::SX::sym("Su", nx, nu);

    casadi::SX jac_x = casadi::SX::jacobian(rhs, x);
    casadi::Function jac_fun(model.name() + "_expl_ode_jac", {x, Sx, Su, u}, {rhs, jac_x});

    return casadi_module(jac_fun, output_folder);
}

}  // namespace acados
