#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#define STATS_ENABLE_EIGEN_WRAPPERS
#include "stats.hpp"

using Mxd = Eigen::MatrixXd;
using rand_engine_t = std::mt19937_64;

#define outD double
#define outM Mxd
#define declD(arg) const double arg
#define declN(arg)
#define declDim(arg) const uint64_t n, const uint64_t k
#define declSeed(arg) const uint64_t seed_val = std::random_device{}()
#define declEng(arg) rand_engine_t& engine

#define tempM <Mxd>
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

#define TEST(FUN, Ret, Temp, Type1, Type2, Type3, Type4) \
out##Ret FUN ( decl##Type1(arg1) comma##Type2 \
             decl##Type2(arg2) comma##Type3 \
             decl##Type3(arg3) comma##Type4 \
             decl##Type4(arg4) ) \
{ return stats::FUN \
temp##Temp ( ele##Type1(arg1) comma##Type2 \
                    ele##Type2(arg2) comma##Type3 \
                    ele##Type3(arg3) comma##Type4 \
                    ); } \


double rnorm() { return stats::rnorm(); }
// function, return type, arg1 type, arg2 type, arg3 type, arg4 type (seed or rng), template type
TEST(rnorm, D, N, D, D, N, N)
TEST(rnorm, D, N, D, D, Seed, N)
TEST(rnorm, D, N, D, D, Eng, N)
TEST(rnorm, M, M, Dim, D, D, N)

// ----------------
// Python interface
// ----------------

namespace py = pybind11;
using namespace pybind11::literals;

void rand(py::module &m)
{
  m.def("rnorm", py::overload_cast<>(&rnorm));
  m.def("rnorm", py::overload_cast<const double, const double>(&rnorm));
  m.def("rnorm", py::overload_cast<const double, const double, const uint64_t>(&rnorm));
  m.def("rnorm", py::overload_cast<const double, const double, rand_engine_t&>(&rnorm));
  m.def("rnorm", py::overload_cast<const uint64_t, const uint64_t, const double, const double>(&rnorm));

  py::class_<std::mt19937_64>(m, "Engine")
      .def(py::init<int>());
}
