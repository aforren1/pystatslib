#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "stats.hpp"

namespace py = pybind11;
using namespace pybind11::literals;
using engine_t = stats::rand_engine_t;
using llint_t = stats::llint_t;

template <auto Func, typename T1, typename T2, typename S>
struct Vectorize2
{
      auto operator()(const T1 a, const T2 b, const S size,
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

template <auto Func, typename T1, typename S>
struct Vectorize1
{
      auto operator()(const T1 a, const S size, stats::rand_engine_t &engine)
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
Vectorize2<rnorm, double, double, std::vector<size_t>&> vrnorm;
Vectorize2<rnorm, double, double, size_t> srnorm;

const auto rbern = py::overload_cast<double, engine_t &>(&stats::rbern<double>);
Vectorize1<rbern, double, std::vector<size_t>&> vrbern;
Vectorize1<rbern, double, size_t> srbern;

const auto rbeta = py::overload_cast<double, double, engine_t &>(&stats::rbeta<double, double>);
Vectorize2<rbeta, double, double, std::vector<size_t>&> vrbeta;
Vectorize2<rbeta, double, double, size_t> srbeta;

const auto rbinom = py::overload_cast<llint_t, double, engine_t &>(&stats::rbinom<double>);
Vectorize2<rbinom, llint_t, double, std::vector<size_t>&> vrbinom;
Vectorize2<rbinom, llint_t, double, size_t> srbinom;

const auto rcauchy = py::overload_cast<double, double, engine_t &>(&stats::rcauchy<double, double>);
Vectorize2<rcauchy, double, double, std::vector<size_t>&> vrcauchy;
Vectorize2<rcauchy, double, double, size_t> srcauchy;

const auto rchisq = py::overload_cast<double, engine_t &>(&stats::rchisq<double>);
Vectorize1<rchisq, double, std::vector<size_t>&> vrchisq;
Vectorize1<rchisq, double, size_t> srchisq;

const auto rexp = py::overload_cast<double, engine_t &>(&stats::rexp<double>);
Vectorize1<rexp, double, std::vector<size_t>&> vrexp;
Vectorize1<rexp, double, size_t> srexp;

const auto rf = py::overload_cast<double, double, engine_t &>(&stats::rf<double, double>);
Vectorize2<rf, double, double, std::vector<size_t>&> vrf;
Vectorize2<rf, double, double, size_t> srf;

const auto rgamma = py::overload_cast<double, double, engine_t &>(&stats::rgamma<double, double>);
Vectorize2<rgamma, double, double, std::vector<size_t>&> vrgamma;
Vectorize2<rgamma, double, double, size_t> srgamma;

const auto rinvgamma = py::overload_cast<double, double, engine_t &>(&stats::rinvgamma<double, double>);
Vectorize2<rinvgamma, double, double, std::vector<size_t>&> vrinvgamma;
Vectorize2<rinvgamma, double, double, size_t> srinvgamma;

const auto rlaplace = py::overload_cast<double, double, engine_t &>(&stats::rlaplace<double, double>);
Vectorize2<rlaplace, double, double, std::vector<size_t>&> vrlaplace;
Vectorize2<rlaplace, double, double, size_t> srlaplace;

const auto rlnorm = py::overload_cast<double, double, engine_t &>(&stats::rlnorm<double, double>);
Vectorize2<rlnorm, double, double, std::vector<size_t>&> vrlnorm;
Vectorize2<rlnorm, double, double, size_t> srlnorm;

const auto rlogis = py::overload_cast<double, double, engine_t &>(&stats::rlogis<double, double>);
Vectorize2<rlogis, double, double, std::vector<size_t>&> vrlogis;
Vectorize2<rlogis, double, double, size_t> srlogis;

const auto rpois = py::overload_cast<double, engine_t &>(&stats::rpois<double>);
Vectorize1<rpois, double, std::vector<size_t>&> vrpois;
Vectorize1<rpois, double, size_t> srpois;

const auto rt = py::overload_cast<double, engine_t &>(&stats::rt<double>);
Vectorize1<rt, double, std::vector<size_t>&> vrt;
Vectorize1<rt, double, size_t> srt;

const auto runif = py::overload_cast<double, double, engine_t &>(&stats::runif<double, double>);
Vectorize2<runif, double, double, std::vector<size_t>&> vrunif;
Vectorize2<runif, double, double, size_t> srunif;

const auto rweibull = py::overload_cast<double, double, engine_t &>(&stats::rweibull<double, double>);
Vectorize2<rweibull, double, double, std::vector<size_t>&> vrweibull;
Vectorize2<rweibull, double, double, size_t> srweibull;

void rand(py::module &m)
{
      py::class_<engine_t>(m, "Engine").def(py::init<int>());
      py::object engine = m.attr("Engine")(1); // default engine

      m.def("rnorm", rnorm, "mu"_a = 0, "sigma"_a = 1, "engine"_a = engine);
      m.def("rnorm", vrnorm, "mu"_a = 0, "sigma"_a = 1, "dims"_a, "engine"_a = engine);
      m.def("rnorm", srnorm, "mu"_a = 0, "sigma"_a = 1, "dims"_a, "engine"_a = engine);
      m.def("rbern", rbern, "prob"_a, "engine"_a = engine);
      m.def("rbern", vrbern, "prob"_a, "dims"_a, "engine"_a = engine);
      m.def("rbern", srbern, "prob"_a, "dims"_a, "engine"_a = engine);
      m.def("rbeta", rbeta, "a"_a, "b"_a, "engine"_a = engine);
      m.def("rbeta", vrbeta, "a"_a, "b"_a, "dims"_a, "engine"_a = engine);
      m.def("rbeta", srbeta, "a"_a, "b"_a, "dims"_a, "engine"_a = engine);
      m.def("rbinom", rbinom, "n_trials"_a, "prob"_a, "engine"_a = engine);
      m.def("rbinom", vrbinom, "n_trials"_a, "prob"_a, "dims"_a, "engine"_a = engine);
      m.def("rbinom", srbinom, "n_trials"_a, "prob"_a, "dims"_a, "engine"_a = engine);
      m.def("rcauchy", rcauchy, "mu"_a, "sigma"_a, "engine"_a = engine);
      m.def("rcauchy", vrcauchy, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rcauchy", srcauchy, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rchisq", rchisq, "dof"_a, "engine"_a = engine);
      m.def("rchisq", vrchisq, "dof"_a, "dims"_a, "engine"_a = engine);
      m.def("rchisq", srchisq, "dof"_a, "dims"_a, "engine"_a = engine);
      m.def("rexp", rexp, "rate"_a, "engine"_a = engine);
      m.def("rexp", vrexp, "rate"_a, "dims"_a, "engine"_a = engine);
      m.def("rexp", srexp, "rate"_a, "dims"_a, "engine"_a = engine);
      m.def("rf", rf, "df1"_a, "df2"_a, "engine"_a = engine);
      m.def("rf", vrf, "df1"_a, "df2"_a, "dims"_a, "engine"_a = engine);
      m.def("rf", srf, "df1"_a, "df2"_a, "dims"_a, "engine"_a = engine);
      m.def("rgamma", rgamma, "shape"_a, "scale"_a, "engine"_a = engine);
      m.def("rgamma", vrgamma, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
      m.def("rgamma", srgamma, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
      m.def("rinvgamma", rinvgamma, "shape"_a, "scale"_a, "engine"_a = engine);
      m.def("rinvgamma", vrinvgamma, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
      m.def("rinvgamma", srinvgamma, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
      m.def("rlaplace", rlaplace, "mu"_a, "sigma"_a, "engine"_a = engine);
      m.def("rlaplace", vrlaplace, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rlaplace", srlaplace, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rlnorm", rlnorm, "mu"_a, "sigma"_a, "engine"_a = engine);
      m.def("rlnorm", vrlnorm, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rlnorm", srlnorm, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rlogis", rlogis, "mu"_a, "sigma"_a, "engine"_a = engine);
      m.def("rlogis", vrlogis, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rlogis", srlogis, "mu"_a, "sigma"_a, "dims"_a, "engine"_a = engine);
      m.def("rpois", rpois, "rate"_a, "engine"_a = engine);
      m.def("rpois", vrpois, "rate"_a, "dims"_a, "engine"_a = engine);
      m.def("rpois", srpois, "rate"_a, "dims"_a, "engine"_a = engine);
      m.def("rt", rt, "dof"_a, "engine"_a = engine);
      m.def("rt", vrt, "dof"_a, "dims"_a, "engine"_a = engine);
      m.def("rt", srt, "dof"_a, "dims"_a, "engine"_a = engine);
      m.def("runif", runif, "a"_a, "b"_a, "engine"_a = engine);
      m.def("runif", vrunif, "a"_a, "b"_a, "dims"_a, "engine"_a = engine);
      m.def("runif", srunif, "a"_a, "b"_a, "dims"_a, "engine"_a = engine);
      m.def("rweibull", rweibull, "shape"_a, "scale"_a, "engine"_a = engine);
      m.def("rweibull", vrweibull, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
      m.def("rweibull", srweibull, "shape"_a, "scale"_a, "dims"_a, "engine"_a = engine);
}
