
#ifndef INTERFACES_ACADOS_CPP_UTILS_HPP_
#define INTERFACES_ACADOS_CPP_UTILS_HPP_

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace acados
{
std::string to_string(std::pair<int, int> p);

template <typename T>
std::string to_string(std::vector<T> v);

bool match(std::pair<int, int> dims, int nb_elems);

// TEMPLATE FUNCTIONS

// TODO: what is it, is it used somewhere?
template <typename T>
const T& clamp(const T& lo, const T& hi, const T& val);

/// conversion from column-major matrix representation to standard c++ representation
// TODO(tobi) write tests for this function
template <typename T>
std::vector<std::vector<T>> columnmajor2matrix(std::vector<T> colvec, const size_t n,
                                               const size_t m)
{
    std::vector<std::vector<T>> matrix;
    if (colvec.size() == 0) return matrix;

    if (colvec.size() != n * m) throw std::length_error("colvec has inconsistent size");


    matrix.reserve(n);
    auto start = colvec.begin();
    while (start != colvec.end())
    {
        matrix.push_back(std::vector<T>(start, start + m));
        start = start + m + 1;  // element after end
    }
    if (matrix.size() != n)
        throw std::length_error("conversion failed: output matrix as wrong dimensions");

    return matrix;
}

/// conversion from standard c++ matrix representation to column-major representation
// TODO(tobi) write tests for this function
template <typename T>
std::vector<T> matrix2columnmajor(std::vector<std::vector<T>> matrix)
{
    std::vector<T> colvec;
    if (matrix.size() == 0) return colvec;

    const size_t n = matrix.size();
    const size_t m = matrix[0].size();
    colvec.reserve(n * m);
    for (auto const& row : matrix)
    {
        if (row.size() != m) throw std::length_error("matrix has inconsistent dimensions");
        colvec.insert(colvec.end(), row.begin(), row.end());
    }
    return colvec;
}

}  // namespace acados

#endif  // INTERFACES_ACADOS_CPP_UTILS_HPP_
