#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#define STATS_ENABLE_EIGEN_WRAPPERS
#include "stats.hpp"

using Mxd = Eigen::MatrixXd;
using Mxi = Eigen::Matrix<uint32_t, -1, -1>;
using rand_engine_t = std::mt19937_64;

#define declD(arg) const double arg
#define declI(arg) const uint32_t arg // TODO: check 32 or 64 bit? it's "uint_t" in the docs
#define declN(arg)
#define declDim(arg) const uint64_t n, const uint64_t k
#define declSeed(arg) const uint64_t seed_val = std::random_device{}()
#define declEng(arg) rand_engine_t& engine

#define tempM <Mxd>
#define tempMi <Mxi>
#define tempN
#define eleD(arg) arg
#define eleSeed(arg) seed_val
#define eleEng(arg) engine
#define eleDim(arg) n, k
#define eleN(arg)

#define commaD ,
#define commaSeed ,
#define commaEng ,
#define commaDim ,
#define commaN

#define fnRnorm rnorm
#define fnRbern rbern
#define fnRbeta rbeta
#define fnRbinom rbinom

// inspired by https://github.com/kaskr/adcomp/blob/master/TMB/inst/include/Vectorize.hpp
#define GRAND(FUN, Temp, Type1, Type2, Type3, Type4) \
auto fn##FUN ( decl##Type1(arg1) comma##Type2 \
             decl##Type2(arg2) comma##Type3 \
             decl##Type3(arg3) comma##Type4 \
             decl##Type4(arg4) ) \
{ return stats::fn##FUN \
temp##Temp ( ele##Type1(arg1) comma##Type2 \
             ele##Type2(arg2) comma##Type3 \
             ele##Type3(arg3) comma##Type4 \
           ); } \

// function, return type, template type, arg1 type, arg2 type, arg3 type, arg4 type (seed or rng)
GRAND(Rnorm, N, N, N, N, N) // special case: rnorm can take no args to give standard normal

// just bernoulli?
#define RAND_bern(FUN) \
GRAND(FUN, N, D, N, N, N) \
GRAND(FUN, N, D, Seed, N, N) \
GRAND(FUN, N, D, Eng, N, N) \
GRAND(FUN, Mi, Dim, D, N, N)

#define RAND1_d(FUN) \
GRAND(FUN, N, D, N, N, N) \
GRAND(FUN, N, D, Seed, N, N) \
GRAND(FUN, N, D, Eng, N, N) \
GRAND(FUN, M, Dim, D, N, N)

// just binomial?
#define RAND_binom(FUN) \
GRAND(FUN, N, I, D, N, N) \
GRAND(FUN, N, I, D, Seed, N) \
GRAND(FUN, N, I, D, Eng, N) \
GRAND(FUN, Mi, Dim, D, D, N)

#define RAND2_d(FUN) \
GRAND(FUN, N, D, D, N, N) \
GRAND(FUN, N, D, D, Seed, N) \
GRAND(FUN, N, D, D, Eng, N) \
GRAND(FUN, M, Dim, D, D, N)

RAND2_d(Rnorm)
RAND_bern(Rbern)
RAND2_d(Rbeta)

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

#define PybindDefs_1d(FUN, funstr, parname1, docstring) \
m.def(funstr, py::overload_cast<Types1d_1>(&fn##FUN), docstring, py::arg(parname1)); \
m.def(funstr, py::overload_cast<Types1d_2>(&fn##FUN), "", py::arg(parname1), "seed_val"_a); \
m.def(funstr, py::overload_cast<Types1d_3>(&fn##FUN), "", py::arg(parname1), "engine"_a); \
m.def(funstr, py::overload_cast<Types1d_4>(&fn##FUN), "", "n"_a, "k"_a, py::arg(parname1));

#define PybindDefs_2d(FUN, funstr, parname1, parname2, docstring) \
m.def(funstr, py::overload_cast<Types2d_1>(&fn##FUN), docstring, py::arg(parname1), py::arg(parname2)); \
m.def(funstr, py::overload_cast<Types2d_2>(&fn##FUN), "", py::arg(parname1), py::arg(parname2), "seed_val"_a); \
m.def(funstr, py::overload_cast<Types2d_3>(&fn##FUN), "", py::arg(parname1), py::arg(parname2), "engine"_a); \
m.def(funstr, py::overload_cast<Types2d_4>(&fn##FUN), "", "n"_a, "k"_a, py::arg(parname1), py::arg(parname2));

namespace py = pybind11;
using namespace pybind11::literals;

void rand(py::module &m)
{
  m.def("rnorm", py::overload_cast<>(&rnorm), "Random numbers the Normal (Gaussian) distribution.");
  PybindDefs_2d(Rnorm, "rnorm", "mu", "sigma", "") // no docstring
  PybindDefs_1d(Rbern, "rbern", "p", "Random numbers from the Bernoulli distribution.")

  py::class_<std::mt19937_64>(m, "Engine")
      .def(py::init<int>());
}
