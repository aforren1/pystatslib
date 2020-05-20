#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "stats.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

// want <function, args..., tuple> and return py::array of dimension tuple and size matching mul(tuple)
py::array_t<double>
rnorm(const double x, const double y, stats::rand_engine_t& z, const std::vector<size_t> &dims)
{
    size_t out_size = 1;
    for (const auto& e: dims)
    {
        out_size *= e;
    }
    py::array_t<double, py::array::c_style> out_array({out_size});
    auto r = out_array.mutable_unchecked<1>();
    for (int i = 0; i < out_size; i++)
    {
        r(i) = stats::rnorm(x, y, z);
    }
    return out_array;
}


void rand(py::module &m)
{
    py::class_<stats::rand_engine_t>(m, "Engine")
        .def(py::init<int>());
    py::object engine = m.attr("Engine")(1); // default engine
    m.def("rnorm", py::overload_cast<double, double, stats::rand_engine_t&>(&stats::rnorm<double, double>),
          "mu"_a=0, "sigma"_a=1, "engine"_a=engine);
    m.def("rnorm", py::overload_cast<double, double, stats::rand_engine_t&, const std::vector<int>&>(rnorm),
          "mu"_a=0, "sigma"_a=1, "engine"_a=engine);
}