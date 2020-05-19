#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "stats.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

void dens(py::module &m)
{
    m.def("dnorm", py::vectorize(&stats::dnorm<double, double, double>), 
          "x"_a, "mu"_a=0, "sigma"_a=1, "log_form"_a=true);
}