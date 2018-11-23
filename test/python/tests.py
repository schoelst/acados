
import unittest

from acados import *
from models import pendulum_model, chen_model


class TestIntegrator(unittest.TestCase):

    def setUp(self):
        # available options
        self.test_opts = {
            # MANDATORY ARGUMENTS
            'step_size': [0.01, 0.1, 1, 42],  # step width
            # OPTIONAL ARGUMENTS
            # type of provided model
            'model_type': [EXPLICIT, IMPLICIT, GNSF_MODEL],
            'integrator': [ERK, IRK, GNSF, LIFTED_IRK],  # integrator type
            'use_MX': [True, False],  # use MX symbolics
            'ns': [1, 2, 4],  # number of stages
            'num_steps': [1, 2, 4],  # number of steps
            'newton_iter': [2, 3],  # number of newton iterations
            'output_z': [True, False],  # output value of algebraic variables
            'sens_forw': [True, False],  # propagate forward sensitivities
            'sens_adj': [True, False],  # propagate adjoint sensitivities
            'sens_hess': [True, False],  # propagate second order sensitivities
            # propagate sensitivities of algebraic variables
            'sens_algebraic': [True, False],
            # jacobians are reused during newton iterations.
            # For sensitivity propagation new jacobian evaluations are used.
            'jac_reuse': [True, False],
        }

        ode_fun, nx, nu, impl_ode_fun = pendulum_model()
        self.model = ode_fun
        self.impl_model = impl_ode_fun

    def test_constructor(self):
        itgr = integrator(self.model, {'step_size': 42})
        self.assertIsInstance(itgr, integrator)
        impl_itgr = integrator(self.impl_model, {'step_size': 42})
        self.assertIsInstance(impl_itgr, integrator)


if __name__ == '__main__':
    unittest.main()
