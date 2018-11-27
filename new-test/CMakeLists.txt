cmake_policy(SET CMP0057 NEW)
include(GoogleTest)

# from: https://cliutils.gitlab.io/modern-cmake/chapters/testing/googletest.html
macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main acados dl)
    #gtest_add_tests(TARGET ${TESTNAME})
    gtest_discover_tests(${TESTNAME})
    add_test(${TESTNAME} ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(tests tests.cpp)
#include_directories("${CASADIPATH}/casadi/include")
#include_directories("~/code/acados/external/googletest/googletest/include")
#include_directories("~/code/acados/interfaces")
#add_executable(tests tests.cpp)
#gtest_discover_tests(tests)
# gtest_add_tests(TARGET      tests
#                 TEST_SUFFIX .noArgs
#                 TEST_LIST   noArgsTests
# )
#target_link_libraries(tests acados gtest)
#add_test(NAME unit-tests COMMAND tests)
