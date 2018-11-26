
#ifndef INTERFACES_ACADOS_CPP_UTILS_HPP_
#define INTERFACES_ACADOS_CPP_UTILS_HPP_

#include <string>
#include <utility>
#include <vector>

namespace acados
{
std::string to_string(std::pair<int, int> p);

template <typename T>
std::string to_string(std::vector<T> v);

bool match(std::pair<int, int> dims, int nb_elems);

template <typename T>
const T& clamp(const T& lo, const T& hi, const T& val);

/// conversion from column-major matrix representation to standard c++ representation
// TODO(tobi) write tests for this function
template <typename T>
std::vector<std::vector<T>> columnmajor2matrix(std::vector<T> colvec, const size_t n,
                                               const size_t m);

/// conversion from standard c++ matrix representation to column-major representation
// TODO(tobi) write tests for this function
template <typename T>
std::vector<T> matrix2columnmajor(std::vector<std::vector<T>> matrix);
}  // namespace acados

#endif  // INTERFACES_ACADOS_CPP_UTILS_HPP_
