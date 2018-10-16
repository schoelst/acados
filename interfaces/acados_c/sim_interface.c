/*
 *    This file is part of acados.
 *
 *    acados is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    acados is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with acados; if not, write to the Free Software Foundation,
 *    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "acados/sim/sim_common.h"
#include "acados/sim/sim_erk_integrator.h"
#include "acados/sim/sim_gnsf.h"
#include "acados/sim/sim_irk_integrator.h"
#include "acados/sim/sim_lifted_irk_integrator.h"
#include "acados/sim/sim_new_lifted_irk_integrator.h"

#include "acados_c/sim_interface.h"

// external
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "acados/utils/mem.h"



/* config */

sim_solver_config *sim_config_create(sim_solver_plan plan)
{
    int bytes = sim_solver_config_calculate_size();
    void *ptr = calloc(1, bytes);
    sim_solver_config *solver_config = sim_solver_config_assign(ptr);

    sim_solver_t solver_name = plan.sim_solver;

    // TODO(dimitris): cath error if solver not compiled
    // printf("\n\nSpecified solver interface not compiled with acados!\n\n");
    switch (solver_name)
    {
        case ERK:
            sim_erk_config_initialize_default(solver_config);
            break;
        case LIFTED_IRK:
            sim_lifted_irk_config_initialize_default(solver_config);
            break;
        case IRK:
            sim_irk_config_initialize_default(solver_config);
            break;
        case GNSF:
            sim_gnsf_config_initialize_default(solver_config);
            break;
        case NEW_LIFTED_IRK:
            sim_new_lifted_irk_config_initialize_default(solver_config);
            break;
    }
    return solver_config;
}



void sim_config_free(void *config)
{
	free(config);
}



/* dims */

void *sim_dims_create(void *config_)
{
    sim_solver_config *config = (sim_solver_config *) config_;
    int bytes = config->dims_calculate_size(config_);

    void *ptr = calloc(1, bytes);

    void *dims = config->dims_assign(config_, ptr);

    return dims;
}



void sim_dims_free(void *dims)
{
	free(dims);
}



void sim_dims_set_nx(sim_solver_config *config, void *dims, int nx)
{
	config->set_nx(dims, nx);
}



void sim_dims_set_nu(sim_solver_config *config, void *dims, int nu)
{
	config->set_nu(dims, nu);
}



/* in */

sim_in *sim_in_create(sim_solver_config *config, void *dims)
{
    int bytes = sim_in_calculate_size(config, dims);

    void *ptr = calloc(1, bytes);

    sim_in *in = sim_in_assign(config, dims, ptr);

    return in;
}



void sim_in_free(void *in)
{
	free(in);
}



int sim_set_model(sim_solver_config *config, sim_in *in, const char *fun_type, void *fun_ptr)
{
    int status = sim_set_model_internal(config, in->model, fun_type, fun_ptr);

    return status;
}



// NOTE(dimitris) not exposed to user, used by NLP interface too
int sim_set_model_internal(sim_solver_config *config, void *model, const char *fun_type,
                           void *fun_ptr)
{
    int status = ACADOS_SUCCESS;
        /* explicit model */
    if (!strcmp(fun_type, "expl_ode_fun"))
        status = config->model_set_function(model, EXPL_ODE_FUN, fun_ptr);
    else if (!strcmp(fun_type, "expl_ode_jac"))
        status = config->model_set_function(model, EXPL_ODE_JAC, fun_ptr);
    else if (!strcmp(fun_type, "expl_ode_hes"))     // TODO(FreyJo): more consistent naming: hess
        status = config->model_set_function(model, EXPL_ODE_HES, fun_ptr);
    else if (!strcmp(fun_type, "expl_ode_hess"))
        status = config->model_set_function(model, EXPL_ODE_HES, fun_ptr);
    else if (!strcmp(fun_type, "expl_vde_for"))
        status = config->model_set_function(model, EXPL_VDE_FOR, fun_ptr);
    else if (!strcmp(fun_type, "expl_vde_adj"))
        status = config->model_set_function(model, EXPL_VDE_ADJ, fun_ptr);
        /* implicit model */
    else if (!strcmp(fun_type, "impl_ode_fun"))
        status = config->model_set_function(model, IMPL_ODE_FUN, fun_ptr);
    else if (!strcmp(fun_type, "impl_ode_fun_jac_x_xdot")) // TODO update with z !!!
        status = config->model_set_function(model, IMPL_ODE_FUN_JAC_X_XDOT, fun_ptr);
    else if (!strcmp(fun_type, "impl_ode_jac_x_xdot_u")) // TODO update with z !!!
        status = config->model_set_function(model, IMPL_ODE_JAC_X_XDOT_U, fun_ptr);
    else if (!strcmp(fun_type, "impl_ode_fun_jac_x_xdot_u"))
        status = config->model_set_function(model, IMPL_ODE_FUN_JAC_X_XDOT_U, fun_ptr);
    else if (!strcmp(fun_type, "impl_ode_hess"))
        status = config->model_set_function(model, IMPL_ODE_HESS, fun_ptr);
        /* GNSF model */
    else if (!strcmp(fun_type, "phi_fun"))
        status = config->model_set_function(model, PHI_FUN, fun_ptr);
    else if (!strcmp(fun_type, "phi_fun_jac_y"))
        status = config->model_set_function(model, PHI_FUN_JAC_Y, fun_ptr);
    else if (!strcmp(fun_type, "phi_jac_y_uhat"))
        status = config->model_set_function(model, PHI_JAC_Y_UHAT, fun_ptr);
    else if (!strcmp(fun_type, "f_lo_jac_x1_x1dot_u_z"))
        status = config->model_set_function(model, LO_FUN, fun_ptr);
    else
        return ACADOS_FAILURE;

    return status;
}



void sim_in_set_T(sim_solver_config *config, double T, sim_in *in)
{
	in->T = T;
	return;
}



void sim_in_set_x(sim_solver_config *config, void *dims, double *x, sim_in *in)
{
	int nx;
	config->get_nx(dims, &nx);
	int ii;
	for (ii=0; ii<nx; ii++)
		in->x[ii] = x[ii];
	return;
}



void sim_in_set_xdot(sim_solver_config *config, void *dims, double *xdot, sim_in *in)
{
	int nx;
	config->get_nx(dims, &nx);
	int ii;
	for (ii=0; ii<nx; ii++)
		in->xdot[ii] = xdot[ii];
	return;
}



void sim_in_set_u(sim_solver_config *config, void *dims, double *u, sim_in *in)
{
	int nu;
	config->get_nu(dims, &nu);
	int ii;
	for (ii=0; ii<nu; ii++)
		in->u[ii] = u[ii];
	return;
}



void sim_in_set_Sx(sim_solver_config *config, void *dims, double *Sx, sim_in *in)
{
	int nx;
	config->get_nx(dims, &nx);
	int ii;
	for (ii=0; ii<nx*nx; ii++)
		in->S_forw[ii] = Sx[ii];
	return;
}



void sim_in_set_Su(sim_solver_config *config, void *dims, double *Su, sim_in *in)
{
	int nx, nu;
	config->get_nx(dims, &nx);
	config->get_nu(dims, &nu);
	int ii;
	for (ii=0; ii<nx*nu; ii++)
		in->S_forw[nx*nx+ii] = Su[ii];
	return;
}



sim_out *sim_out_create(sim_solver_config *config, void *dims)
{
    int bytes = sim_out_calculate_size(config, dims);

    void *ptr = calloc(1, bytes);

    sim_out *out = sim_out_assign(config, dims, ptr);

    return out;
}



void sim_out_free(void *out)
{
	free(out);
}



void sim_out_get_xn(sim_solver_config *config, void *dims, sim_out *out, double *xn)
{
	int nx;
	config->get_nx(dims, &nx);
	int ii;
	for (ii=0; ii<nx; ii++)
		xn[ii] = out->xn[ii];
	return;
}



void sim_out_get_Sxn(sim_solver_config *config, void *dims, sim_out *out, double *Sxn)
{
	int nx;
	config->get_nx(dims, &nx);
	int ii;
	for (ii=0; ii<nx*nx; ii++)
		Sxn[ii] = out->S_forw[ii];
	return;
}



void sim_out_get_Sun(sim_solver_config *config, void *dims, sim_out *out, double *Sun)
{
	int nx, nu;
	config->get_nx(dims, &nx);
	config->get_nu(dims, &nu);
	int ii;
	for (ii=0; ii<nx*nu; ii++)
		Sun[ii] = out->S_forw[nx*nx+ii];
	return;
}



void *sim_opts_create(sim_solver_config *config, void *dims)
{
    int bytes = config->opts_calculate_size(config, dims);

    void *ptr = calloc(1, bytes);

    void *opts = config->opts_assign(config, dims, ptr);

    config->opts_initialize_default(config, dims, opts);

    return opts;
}



void sim_opts_free(void *opts)
{
	free(opts);
}



void sim_opts_set_sens_forw(sim_rk_opts *opts, bool value)
{

	opts->sens_forw = value;
	return;

}



int sim_calculate_size(sim_solver_config *config, void *dims, void *opts_)
{
    int bytes = sizeof(sim_solver);

    bytes += config->memory_calculate_size(config, dims, opts_);
    bytes += config->workspace_calculate_size(config, dims, opts_);

    return bytes;
}



sim_solver *sim_assign(sim_solver_config *config, void *dims, void *opts_, void *raw_memory)
{
    char *c_ptr = (char *) raw_memory;

    sim_solver *solver = (sim_solver *) c_ptr;
    c_ptr += sizeof(sim_solver);

    solver->config = config;
    solver->dims = dims;
    solver->opts = opts_;

    // TODO(dimitris): CHECK ALIGNMENT!

    solver->mem = config->memory_assign(config, dims, opts_, c_ptr);
    c_ptr += config->memory_calculate_size(config, dims, opts_);

    solver->work = (void *) c_ptr;
    c_ptr += config->workspace_calculate_size(config, dims, opts_);

    assert((char *) raw_memory + sim_calculate_size(config, dims, opts_) == c_ptr);

    return solver;
}



sim_solver *sim_create(sim_solver_config *config, void *dims, void *opts_)
{
    // update Butcher tableau (needed if the user changed ns)
    config->opts_update(config, dims, opts_);
    int bytes = sim_calculate_size(config, dims, opts_);

    void *ptr = calloc(1, bytes);

    sim_solver *solver = sim_assign(config, dims, opts_, ptr);

    return solver;
}



void sim_free(void *solver)
{
	free(solver);
}



int sim_solve(sim_solver *solver, sim_in *in, sim_out *out)
{
    int flag =  solver->config->evaluate(solver->config, in, out, solver->opts, solver->mem,
                                    solver->work);
	return flag;
}
