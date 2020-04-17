#ifndef _Pragma // MSVC
#define _Pragma __pragma
#endif
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#define STATS_ENABLE_EIGEN_WRAPPERS
#include "stats.hpp"

using Mxd = Eigen::MatrixXd;

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

void rand(py::module&);
void dens(py::module&);

PYBIND11_MODULE(statslib, m)
{
  m.doc() = "pybind11 wrapper for kthohr/statslib";
  dens(m);
  rand(m);
}
