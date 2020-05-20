#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "stats.hpp"

namespace py = pybind11;
using namespace pybind11::literals;

// want <function, args..., tuple> and return py::array of dimension tuple and size matching mul(tuple)
template<typename A, typename B>
py::array_t<A>
rnorm(const A x, const B y, const std::vector<size_t> &size, stats::rand_engine_t& engine)
{
    auto out_array = py::array_t<A, py::array::c_style>(size);
    const auto info = out_array.request();
    A* r = static_cast<A*>(info.ptr);
    for (int i = 0; i < info.size; i++)
    {
        r[i] = stats::rnorm(x, y, engine);
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
    m.def("rnorm", py::overload_cast<double, double, const std::vector<size_t>&, stats::rand_engine_t&>(&rnorm<double, double>),
          "mu"_a=0, "sigma"_a=1, "dims"_a, "engine"_a=engine);
}