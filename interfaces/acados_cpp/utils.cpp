
#include "acados_cpp/utils.hpp"

#include <stdexcept>

namespace acados
{
using std::vector;

std::string to_string(std::pair<int, int> p)
{
    return "( " + std::to_string(p.first) + ", " + std::to_string(p.second) + " )";
}

template <typename T>
std::string to_string(std::vector<T> v)
{
    std::string result_string = " vector of length " + std::to_string(v.size()) + ": [\n ";
    for (auto it : v)
    {
        result_string += std::to_string(it) + ", ";
    }
    return result_string + "]\n";
}

bool match(std::pair<int, int> dims, int nb_elems)
{
    int nb_expected_elems = dims.first * dims.second;
    if (nb_expected_elems == 0 || nb_expected_elems == nb_elems) return true;
    return false;
}

template <typename T>
const T& clamp(const T& lo, const T& hi, const T& val)
{
    if (val < lo)
        return lo;
    else if (val > hi)
        return hi;

    return val;
}

template <typename T>
vector<T> matrix2columnmajor(vector<vector<T>> matrix)
{
    vector<T> colvec;
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

template <typename T>
vector<vector<T>> columnmajor2matrix(vector<T> colvec, const size_t n, const size_t m)
{
    vector<vector<T>> matrix;
    if (colvec.size() == 0) return matrix;

    if (colvec.size() != n * m) throw std::length_error("colvec has inconsistent size");


    matrix.reserve(n);
    auto start = colvec.begin();
    while (start != colvec.end())
    {
        matrix.push_back(vector<T>(start, start + m));
        start = start + m + 1;  // element after end
    }
    if (matrix.size() != n)
        throw std::length_error("conversion failed: output matrix as wrong dimensions");

    return matrix;
}

}  // namespace acados
