#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#define STATS_ENABLE_EIGEN_WRAPPERS
#include "stats.hpp"
#include "pystats_internals.hpp"

// define all distributions
#define fnRnorm rnorm
#define fnRbern rbern
#define fnRbeta rbeta
#define fnRbinom rbinom
#define fnRcauchy rcauchy
#define fnRchisq rchisq
#define fnRexp rexp
#define fnRf rf
#define fnRgamma rgamma
#define fnRinvgamma rinvgamma
#define fnRlaplace rlaplace
#define fnRlnorm rlnorm
#define fnRlogis rlogis
#define fnRpois rpois
#define fnRt rt
#define fnRunif runif
#define fnRweibull rweibull
// TODO multivariate distributions

// function, return type, template type, arg1 type, arg2 type, arg3 type, arg4 type (seed or rng)
GRAND(Rnorm, D, N, N, N, N, N) // special case: rnorm can take no args to give standard normal
GRAND(Runif, D, N, N, N, N, N) // special case: runif can take no args to give Unif(0, 1)

// just bernoulli? TODO make sure ints are returned (right now floats)
#define RAND_bern(FUN) \
GRAND(FUN, I, N, D, N, N, N) \
GRAND(FUN, I, N, D, Seed, N, N) \
GRAND(FUN, I, N, D, Eng, N, N) \
GRAND(FUN, Mi, Mi, Dim, D, N, N)

#define RAND1_d(FUN) \
GRAND(FUN, D, N, D, N, N, N) \
GRAND(FUN, D, N, D, Seed, N, N) \
GRAND(FUN, D, N, D, Eng, N, N) \
GRAND(FUN, M, M, Dim, D, N, N)

// just binomial? TODO make sure ints are returned (right now floats)
#define RAND_binom(FUN) \
GRAND(FUN, I, N, I, D, N, N) \
GRAND(FUN, I, N, I, D, Seed, N) \
GRAND(FUN, I, N, I, D, Eng, N) \
GRAND(FUN, Mi, Mi, Dim, I, D, N)

#define RAND2_d(FUN) \
GRAND(FUN, D, N, D, D, N, N) \
GRAND(FUN, D, N, D, D, Seed, N) \
GRAND(FUN, D, N, D, D, Eng, N) \
GRAND(FUN, M, M, Dim, D, D, N)

// final step of C++ bit-- generate all fns
RAND2_d(Rnorm)
RAND_bern(Rbern)
RAND2_d(Rbeta)
RAND_binom(Rbinom)
RAND2_d(Rcauchy)
RAND1_d(Rchisq)
RAND1_d(Rexp)
RAND2_d(Rf)
RAND2_d(Rgamma)
RAND2_d(Rinvgamma)
RAND2_d(Rlaplace)
RAND2_d(Rlnorm)
RAND2_d(Rlogis)
RAND_bern(Rpois)
RAND1_d(Rt)
RAND2_d(Runif)
RAND2_d(Rweibull)
// ----------------
// Python interface
// ----------------

#define Types1d_1 const double
#define Types1d_2 Types1d_1, const uint64_t
#define Types1d_3 Types1d_1, rand_engine_t&
#define Types1d_4 const uint64_t, const uint64_t, Types1d_1

#define Types2d_1 const double, const double
#define Types2d_2 Types2d_1, const uint64_t
#define Types2d_3 Types2d_1, rand_engine_t&
#define Types2d_4 const uint64_t, const uint64_t, Types2d_1

// for binomial
#define Types2i_1 const uint32_t, const double
#define Types2i_2 Types2i_1, const uint64_t
#define Types2i_3 Types2i_1, rand_engine_t&
#define Types2i_4 const uint64_t, const uint64_t, Types2i_1

#define Doc1 "Random numbers from the "
#define Doc2 " distribution."
#define PybindDefs_1d(FUN, funstr, parname1, docstring) \
m.def(funstr, py::overload_cast<Types1d_1>(&fn##FUN), Doc1 docstring Doc2, py::arg(parname1)); \
m.def(funstr, py::overload_cast<Types1d_2>(&fn##FUN), "", py::arg(parname1), "seed_val"_a); \
m.def(funstr, py::overload_cast<Types1d_3>(&fn##FUN), "", py::arg(parname1), "engine"_a); \
m.def(funstr, py::overload_cast<Types1d_4>(&fn##FUN), "", "n"_a, "k"_a, py::arg(parname1));

#define PybindDefs_2d(FUN, funstr, parname1, parname2, docstring) \
m.def(funstr, py::overload_cast<Types2d_1>(&fn##FUN), Doc1 docstring Doc2, py::arg(parname1), py::arg(parname2)); \
m.def(funstr, py::overload_cast<Types2d_2>(&fn##FUN), "", py::arg(parname1), py::arg(parname2), "seed_val"_a); \
m.def(funstr, py::overload_cast<Types2d_3>(&fn##FUN), "", py::arg(parname1), py::arg(parname2), "engine"_a); \
m.def(funstr, py::overload_cast<Types2d_4>(&fn##FUN), "", "n"_a, "k"_a, py::arg(parname1), py::arg(parname2));

#define PybindDefs_2i(FUN, funstr, parname1, parname2, docstring) \
m.def(funstr, py::overload_cast<Types2i_1>(&fn##FUN), Doc1 docstring Doc2, py::arg(parname1), py::arg(parname2)); \
m.def(funstr, py::overload_cast<Types2i_2>(&fn##FUN), "", py::arg(parname1), py::arg(parname2), "seed_val"_a); \
m.def(funstr, py::overload_cast<Types2i_3>(&fn##FUN), "", py::arg(parname1), py::arg(parname2), "engine"_a); \
m.def(funstr, py::overload_cast<Types2i_4>(&fn##FUN), "", "n"_a, "k"_a, py::arg(parname1), py::arg(parname2));

namespace py = pybind11;
using namespace pybind11::literals;

void rand(py::module &m)
{
  m.def("rnorm", py::overload_cast<>(&rnorm), "Random numbers from the Normal (Gaussian) distribution.");
  m.def("runif", py::overload_cast<>(&runif), "Random numbers from the Uniform distribution.");
  PybindDefs_2d(Rnorm, "rnorm", "mu", "sigma", "") // no docstring
  PybindDefs_1d(Rbern, "rbern", "prob", "Bernoulli")
  PybindDefs_2d(Rbeta, "rbeta", "a", "b", "Beta")
  PybindDefs_2i(Rbinom, "rbinom", "n_trials", "prob", "Binomial")
  PybindDefs_2d(Rcauchy, "rcauchy", "mu", "sigma", "Cauchy")
  PybindDefs_1d(Rchisq, "rchisq", "dof", "Chi-squared")
  PybindDefs_1d(Rexp, "rexp", "rate", "Exponential")
  PybindDefs_2d(Rf, "rf", "df1", "df2", "F")
  PybindDefs_2d(Rgamma, "rgamma", "shape", "scale", "Gamma")
  PybindDefs_2d(Rinvgamma, "rinvgamma", "shape", "scale", "Inverse-Gamma")
  PybindDefs_2d(Rlaplace, "rlaplace", "mu", "sigma", "Laplace")
  PybindDefs_2d(Rlnorm, "rlnorm", "mu", "sigma", "Log-Normal")
  PybindDefs_2d(Rlogis, "rlogis", "mu", "sigma", "Logistic")
  PybindDefs_1d(Rpois, "rpois", "rate", "Poisson")
  PybindDefs_1d(Rt, "rt", "dof", "Student's t")
  PybindDefs_2d(Runif, "runif", "a", "b", "")
  PybindDefs_2d(Rweibull, "rweibull", "shape", "scale", "Weibull")

  py::class_<std::mt19937_64>(m, "Engine")
      .def(py::init<int>());
}
