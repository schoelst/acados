#include "gtest/gtest.h"

#include "acados_cpp/integrator.hpp"

namespace acados
{
using std::vector;

// The fixture for testing class Foo.
class IntegratorTest : public ::testing::Test
{
 protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    IntegratorTest()
    {
        // You can do set-up work for each test here.
        options = Dict({{"step_size", 0.1}});
        MX x(1, 1);
        vector<MX> io{x};
        ode_fun = Function("test", io, io, {"x"}, {"xdot"});
    }

    ~IntegratorTest() override
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Foo.
    Function ode_fun;
    Dict options;
};


// TESTS GO HERE

TEST(IntegratorTest, constructor_reject_empty_model)
{
    Dict options({{"step_size", 0.1}});
    Function fun("test");
    ASSERT_THROW(Integrator(fun, options), std::invalid_argument);
}


TEST(IntegratorTest, constructor_rejects_missing_step_size)
{
    acados::MX x(1, 1);
    vector<MX> io{x};
    Function fun("test", io, io, {"x"}, {"xdot"});
    ASSERT_THROW(Integrator(fun, {}), std::invalid_argument);
}


TEST_F(IntegratorTest, construtor_succeeds_for_simple_model)
{
    auto itgr = Integrator(ode_fun, options);
    // itgr.print_settings();
    SUCCEED();
}



}  // namespace acados

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
