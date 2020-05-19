#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "stats.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

void rand(py::module &m)
{
    
    py::class_<stats::rand_engine_t>(m, "Engine")
        .def(py::init<int>());
    py::object engine = m.attr("Engine")(1);
    m.def("rnorm", py::overload_cast<double, double, const gcem::ullint_t>(&stats::rnorm<double, double>),
          "mu"_a=0, "sigma"_a=1, "seed_val"_a);
    m.def("rnorm", py::overload_cast<double, double, stats::rand_engine_t&>(&stats::rnorm<double, double>),
          "mu"_a=0, "sigma"_a=1, "engine"_a=engine);
    //m.def("rnorm", py::overload_cast<uint64_t, uint64_t, double, double)

}