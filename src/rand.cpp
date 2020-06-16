#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "stats.hpp"

namespace py = pybind11;
using namespace pybind11::literals;
using engine_t = stats::rand_engine_t;
using llint_t = stats::llint_t;

template <auto Func, typename T1, typename T2>
struct Vectorize2
{
      auto operator()(const T1 a, const T2 b,
                      const std::vector<size_t> &size,
                      stats::rand_engine_t &engine)
      {
            auto out_array = py::array_t<T2, py::array::c_style>(size);
            const auto info = out_array.request();
            T2 *r = static_cast<T2 *>(info.ptr);
            for (int i = 0; i < info.size; i++)
            {
                  r[i] = Func(a, b, engine);
            }
            return out_array;
      }
};

template <auto Func, typename T1>
struct Vectorize1
{
      auto operator()(const T1 a, const std::vector<size_t> &size,
                      stats::rand_engine_t &engine)
      {
            auto out_array = py::array_t<T1, py::array::c_style>(size);
            const auto info = out_array.request();
            T1 *r = static_cast<T1 *>(info.ptr);
            for (int i = 0; i < info.size; i++)
            {
                  r[i] = Func(a, engine);
            }
            return out_array;
      }
};

const auto rnorm = py::overload_cast<double, double, engine_t &>(&stats::rnorm<double, double>);
Vectorize2<rnorm, double, double> vrnorm;

const auto rbern = py::overload_cast<double, engine_t &>(&stats::rbern<double>);
Vectorize1<rbern, double> vrbern;

const auto rbeta = py::overload_cast<double, double, engine_t &>(&stats::rbeta<double, double>);
Vectorize2<rbeta, double, double> vrbeta;

const auto rbinom = py::overload_cast<llint_t, double, engine_t &>(&stats::rbinom<double>);
Vectorize2<rbinom, llint_t, double> vrbinom;

const auto rcauchy = py::overload_cast<double, double, engine_t &>(&stats::rcauchy<double, double>);
Vectorize2<rcauchy, double, double> vrcauchy;

const auto rchisq = py::overload_cast<double, engine_t &>(&stats::rchisq<double>);
Vectorize1<rchisq, double> vrchisq;

const auto rexp = py::overload_cast<double, engine_t &>(&stats::rexp<double>);
Vectorize1<rexp, double> vrexp;

const auto rf = py::overload_cast<double, double, engine_t &>(&stats::rf<double, double>);
Vectorize2<rf, double, double> vrf;

const auto rgamma = py::overload_cast<double, double, engine_t &>(&stats::rgamma<double, double>);
Vectorize2<rgamma, double, double> vrgamma;

const auto rinvgamma = py::overload_cast<double, double, engine_t &>(&stats::rinvgamma<double, double>);
Vectorize2<rinvgamma, double, double> vrinvgamma;

const auto rlaplace = py::overload_cast<double, double, engine_t &>(&stats::rlaplace<double, double>);
Vectorize2<rlaplace, double, double> vrlaplace;

const auto rlnorm = py::overload_cast<double, double, engine_t &>(&stats::rlnorm<double, double>);
Vectorize2<rlnorm, double, double> vrlnorm;

const auto rlogis = py::overload_cast<double, double, engine_t &>(&stats::rlogis<double, double>);
Vectorize2<rlogis, double, double> vrlogis;

const auto rpois = py::overload_cast<double, engine_t &>(&stats::rpois<double>);
Vectorize1<rpois, double> vrpois;

const auto rt = py::overload_cast<double, engine_t &>(&stats::rt<double>);
Vectorize1<rt, double> vrt;

const auto runif = py::overload_cast<double, double, engine_t &>(&stats::runif<double, double>);
Vectorize2<runif, double, double> vrunif;

const auto rweibull = py::overload_cast<double, double, engine_t &>(&stats::rweibull<double, double>);
Vectorize2<rweibull, double, double> vrweibull;

void rand(py::module &m)
{
      py::class_<engine_t>(m, "Engine").def(py::init<int>());
      py::object engine = m.attr("Engine")(1); // default engine

      m.def("rnorm", rnorm, "mu"_a = 0, "sigma"_a = 1, "engine"_a = engine);
      m.def("rnorm", vrnorm, "mu"_a = 0, "sigma"_a = 1, "dims"_a, "engine"_a = engine);
      m.def("rbern", rbern, "prob"_a, "engine"_a = engine);
      m.def("rbern", vrbern, "prob"_a, "dims"_a, "engine"_a = engine);
      m.def("rbeta", rbeta, "a"_a, "b"_a, "engine"_a = engine);
      m.def("rbeta", vrbeta, "a"_a, "b"_a, "dims"_a, "engine"_a = engine);
      m.def("rbinom", rbinom, "n_trials"_a, "prob"_a, "engine"_a = engine);
      m.def("rbinom", vrbinom, "n_trials"_a, "prob"_a, "dims"_a, "engine"_a = engine);
      m.def("rcauchy", rcauchy, "mu"_a, "sigma"_a, "engine"_a = engine);
      m.def("rcauchy", vrcauchy, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rchisq", rchisq, "dof"_a, "engine"_a = engine);
      m.def("rchisq", vrchisq, "dof"_a, "dims"_a, "engine"_a = engine);
      m.def("rexp", rexp, "rate"_a, "engine"_a = engine);
      m.def("rexp", vrexp, "rate"_a, "dims"_a, "engine"_a = engine);
      m.def("rf", rf, "df1"_a, "df2"_a, "engine"_a = engine);
      m.def("rf", vrf, "df1"_a, "df2"_a, "dims"_a, "engine"_a = engine);
      m.def("rgamma", rgamma, "shape"_a, "scale"_a, "engine"_a = engine);
      m.def("rgamma", vrgamma, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
      m.def("rinvgamma", rinvgamma, "shape"_a, "scale"_a, "engine"_a = engine);
      m.def("rinvgamma", vrinvgamma, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
      m.def("rlaplace", rlaplace, "mu"_a, "sigma"_a, "engine"_a = engine);
      m.def("rlaplace", vrlaplace, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rlnorm", rlnorm, "mu"_a, "sigma"_a, "engine"_a = engine);
      m.def("rlnorm", vrlnorm, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rlogis", rlogis, "mu"_a, "sigma"_a, "engine"_a = engine);
      m.def("rlogis", vrlogis, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rpois", rpois, "rate"_a, "engine"_a = engine);
      m.def("rpois", vrpois, "rate"_a, "dims"_a, "engine"_a = engine);
      m.def("rt", rt, "dof"_a, "engine"_a = engine);
      m.def("rt", vrt, "dof"_a, "dims"_a, "engine"_a = engine);
      m.def("runif", runif, "a"_a, "b"_a, "engine"_a = engine);
      m.def("runif", vrunif, "a"_a, "b"_a, "dims"_a, "engine"_a = engine);
      m.def("rweibull", rweibull, "shape"_a, "scale"_a, "engine"_a = engine);
      m.def("rweibull", vrweibull, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
}
