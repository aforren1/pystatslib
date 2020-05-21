#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "stats.hpp"

namespace py = pybind11;
using namespace pybind11::literals;
using engine_t = stats::rand_engine_t;
using llint_t = stats::llint_t;

void rand(py::module &m)
{
    py::class_<engine_t>(m, "Engine").def(py::init<int>());
    py::object engine = m.attr("Engine")(1); // default engine

    m.def("rnorm", py::overload_cast<double, double, engine_t&>(&stats::rnorm<double, double>),
          "mu"_a=0, "sigma"_a=1, "engine"_a=engine);
    m.def("rbern", py::overload_cast<double, engine_t&>(&stats::rbern<double>),
          "prob"_a,  "engine"_a=engine);
    m.def("rbeta", py::overload_cast<double, double, engine_t&>(&stats::rbeta<double, double>),
          "a"_a, "b"_a, "engine"_a=engine);
    m.def("rbinom", py::overload_cast<llint_t, double, engine_t&>(&stats::rbinom<double>),
          "n_trials"_a, "prob"_a, "engine"_a=engine);
    m.def("rcauchy", py::overload_cast<double, double, engine_t&>(&stats::rcauchy<double, double>),
          "mu"_a, "sigma"_a, "engine"_a=engine);
    m.def("rchisq", py::overload_cast<double, engine_t&>(&stats::rchisq<double>),
          "dof"_a, "engine"_a=engine);
    m.def("rexp", py::overload_cast<double, engine_t&>(&stats::rexp<double>),
          "rate"_a, "engine"_a=engine);
    m.def("rf", py::overload_cast<double, double, engine_t&>(&stats::rf<double, double>),
          "df1"_a, "df2"_a, "engine"_a=engine);
    m.def("rgamma", py::overload_cast<double, double, engine_t&>(&stats::rgamma<double, double>),
          "shape"_a, "scale"_a, "engine"_a=engine);
    m.def("rinvgamma", py::overload_cast<double, double, engine_t&>(&stats::rinvgamma<double, double>),
          "shape"_a, "scale"_a, "engine"_a=engine);
    m.def("rlaplace", py::overload_cast<double, double, engine_t&>(&stats::rlaplace<double, double>), 
          "mu"_a, "sigma"_a, "engine"_a=engine);
    m.def("rlnorm", py::overload_cast<double, double, engine_t&>(&stats::rlnorm<double, double>), 
          "mu"_a, "sigma"_a, "engine"_a=engine);
    m.def("rlogis", py::overload_cast<double, double, engine_t&>(&stats::rlogis<double, double>), 
          "mu"_a, "sigma"_a, "engine"_a=engine);
    m.def("rpois", py::overload_cast<double, engine_t&>(&stats::rpois<double>),
          "rate"_a, "engine"_a=engine);
    m.def("rt", py::overload_cast<double, engine_t&>(&stats::rt<double>),
          "dof"_a, "engine"_a=engine);
    m.def("runif", py::overload_cast<double, double, engine_t&>(&stats::runif<double, double>),
          "a"_a, "b"_a, "engine"_a=engine);
    m.def("rweibull", py::overload_cast<double, double, engine_t&>(&stats::rweibull<double, double>),
          "shape"_a, "scale"_a, "engine"_a=engine);
}
