#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#define STATS_ENABLE_EIGEN_WRAPPERS
#include "stats.hpp"

using Mxd = Eigen::MatrixXd;
//using MatrixXdR = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

double dnorm(const double x, const double mu, const double sigma, const bool log_form = false)
{
  return stats::dnorm(x, mu, sigma, log_form);
}

Mxd dnorm(Eigen::Ref<const Mxd> X, const double mu, const double sigma, const bool log_form = false)
{
  return stats::dnorm<double, double, double, double, -1, -1>(X, mu, sigma, log_form);
}

namespace py = pybind11;
using namespace pybind11::literals;

void dens(py::module &m)
{
  m.def("dnorm", py::overload_cast<const double, const double, const double, const bool>(&dnorm), 
        "x"_a, "mu"_a, "sigma"_a, "log_form"_a=true);
  m.def("dnorm", py::overload_cast<Eigen::Ref<const Mxd>, const double, const double, const bool>(&dnorm), 
        "X"_a, "mu"_a, "sigma"_a, "log_form"_a=true);
}
