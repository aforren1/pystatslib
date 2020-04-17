#ifndef _Pragma // MSVC
#define _Pragma __pragma
#endif
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#define STATS_ENABLE_EIGEN_WRAPPERS
#include "stats.hpp"

using Mxd = Eigen::MatrixXd;
using rand_engine_t = std::mt19937_64;
//using MatrixXdR = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

double dnorm(const double x, const double mu, const double sigma, const bool log_form = false)
{
  return stats::dnorm(x, mu, sigma, log_form);
}

Mxd dnorm(Eigen::Ref<const Mxd> X, const double mu, const double sigma, const bool log_form = false)
{
  return stats::dnorm<double, double, double, double, -1, -1>(X, mu, sigma, log_form);
}

// scalar
double rnorm() { return stats::rnorm(); }
double rnorm(const double mu, const double sigma)
{
  return stats::rnorm(mu, sigma);
}
double rnorm(const double mu, const double sigma, const uint64_t seed_val = std::random_device{}()) 
{ 
  return stats::rnorm(mu, sigma, seed_val); 
}

double rnorm(const double mu, const double sigma, rand_engine_t& engine)
{
  return stats::rnorm(mu, sigma, engine);
}

Mxd rnorm(const uint64_t n, const uint64_t k, const double mu, const double sigma)
{
  return stats::rnorm<Mxd>(n, k, mu, sigma);
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(statslib, m)
{
  m.doc() = "pybind11 wrapper for kthohr/statslib";
  m.def("dnorm", py::overload_cast<const double, const double, const double, const bool>(&dnorm), 
        "x"_a, "mu"_a, "sigma"_a, "log_form"_a=true);
  m.def("dnorm", py::overload_cast<Eigen::Ref<const Mxd>, const double, const double, const bool>(&dnorm), 
        "X"_a, "mu"_a, "sigma"_a, "log_form"_a=true);
  m.def("rnorm", py::overload_cast<void>(&rnorm));
  m.def("rnorm", py::overload_cast<const double, const double>(&rnorm));
  m.def("rnorm", py::overload_cast<const double, const double, const uint64_t>(&rnorm));
  m.def("rnorm", py::overload_cast<const double, const double, rand_engine_t&>(&rnorm));
  m.def("rnorm", py::overload_cast<const uint64_t, const uint64_t, const double, const double>(&rnorm));

  py::class_<std::mt19937_64>(m, "Engine")
      .def(py::init<int>());
}
