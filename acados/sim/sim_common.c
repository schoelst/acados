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

// standard
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// acados
#include "acados/sim/sim_common.h"
#include "acados/utils/mem.h"
#include "acados/utils/print.h"

/************************************************
 * config
 ************************************************/

int sim_solver_config_calculate_size()
{
    int size = 0;

    size += sizeof(sim_solver_config);

    return size;
}

sim_solver_config *sim_solver_config_assign(void *raw_memory)
{
    char *c_ptr = raw_memory;

    sim_solver_config *config = (sim_solver_config *) c_ptr;
    c_ptr += sizeof(sim_solver_config);

    assert((char *) raw_memory + sim_solver_config_calculate_size() >= c_ptr);

    return config;
}

/************************************************
 * in
 ************************************************/

int sim_in_calculate_size(void *config_, void *dims)
{
    sim_solver_config *config = config_;

    int size = sizeof(sim_in);

    int nx, nu, nz;

    config->get_nx(dims, &nx);
    config->get_nu(dims, &nu);
    config->get_nz(dims, &nz);

    size += 2 * nx * sizeof(double);          // x, xdot
    size += nu * sizeof(double);              // u
    size += nz * sizeof(double);              // z
    size += nx * (nx + nu) * sizeof(double);  // S_forw (max dimension)
    size += (nx + nu) * sizeof(double);       // S_adj

    size += config->model_calculate_size(config, dims);

    make_int_multiple_of(8, &size);
    size += 1 * 8;

    return size;
}

sim_in *sim_in_assign(void *config_, void *dims, void *raw_memory)
{
    sim_solver_config *config = config_;

    char *c_ptr = (char *) raw_memory;

    sim_in *in = (sim_in *) c_ptr;
    c_ptr += sizeof(sim_in);

    in->dims = dims;

    int nx, nu, nz;
    config->get_nx(dims, &nx);
    config->get_nu(dims, &nu);
    config->get_nz(dims, &nz);

    int NF = nx + nu;

    align_char_to(8, &c_ptr);

    assign_and_advance_double(nx, &in->x, &c_ptr);
    assign_and_advance_double(nu, &in->u, &c_ptr);
    assign_and_advance_double(nz, &in->z, &c_ptr);
    assign_and_advance_double(nx, &in->xdot, &c_ptr);

    // initialization of xdot, z is 0 if not changed
    for (int ii = 0; ii < nx; ii++)
        in->xdot[ii] = 0;
    for (int ii = 0; ii < nz; ii++)
        in->z[ii] = 0;

    assign_and_advance_double(nx * NF, &in->S_forw, &c_ptr);
    assign_and_advance_double(NF, &in->S_adj, &c_ptr);

    in->model = config->model_assign(config, dims, c_ptr);
    c_ptr += config->model_calculate_size(config, dims);

    assert((char *) raw_memory + sim_in_calculate_size(config_, dims) >= c_ptr);

    return in;
}

/************************************************
 * out
 ************************************************/

int sim_out_calculate_size(void *config_, void *dims)
{
    sim_solver_config *config = config_;

    int size = sizeof(sim_out);

    int nx, nu, nz;
    config->get_nx(dims, &nx);
    config->get_nu(dims, &nu);
    config->get_nz(dims, &nz);

    int NF = nx + nu;
    size += sizeof(sim_info);

    size += nx * sizeof(double);                // xn
    size += nx * NF * sizeof(double);           // S_forw
    size += (nx + nu) * sizeof(double);         // S_adj
    size += (NF * NF) * sizeof(double);         // S_hess

    size += nz * sizeof(double);                //  zn
    size += nz * NF * sizeof(double);           // S_algebraic

    size += NF * sizeof(double);                // grad

    make_int_multiple_of(8, &size);
    size += 1 * 8;

    return size;
}

sim_out *sim_out_assign(void *config_, void *dims, void *raw_memory)
{
    sim_solver_config *config = config_;

    char *c_ptr = (char *) raw_memory;

    int nx, nu, nz;
    config->get_nx(dims, &nx);
    config->get_nu(dims, &nu);
    config->get_nz(dims, &nz);

    int NF = nx + nu;

    sim_out *out = (sim_out *) c_ptr;
    c_ptr += sizeof(sim_out);

    out->info = (sim_info *) c_ptr;
    c_ptr += sizeof(sim_info);

    align_char_to(8, &c_ptr);

    assign_and_advance_double(nx, &out->xn, &c_ptr);
    assign_and_advance_double(nx * NF, &out->S_forw, &c_ptr);
    assign_and_advance_double(nx + nu, &out->S_adj, &c_ptr);
    assign_and_advance_double(NF * NF, &out->S_hess, &c_ptr);
    assign_and_advance_double(NF, &out->grad, &c_ptr);

    assign_and_advance_double(nz, &out->zn, &c_ptr);
    assign_and_advance_double(nz * NF, &out->S_algebraic, &c_ptr);

    assert((char *) raw_memory + sim_out_calculate_size(config_, dims) >= c_ptr);

    return out;
}
