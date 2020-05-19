#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

// common types
using Mxd = Eigen::MatrixXd;
using Mxi = Eigen::Matrix<uint32_t, -1, -1>;
using rand_engine_t = std::mt19937_64;
using Mxd_ref = Eigen::Ref<const Mxd>;
using Mxi_ref = Eigen::Ref<const Mxi>;

// output datatypes
#define outD double
#define outI uint32_t
#define outM Mxd
#define outMi Mxi

// function args
#define declD(arg) const double arg
#define declI(arg) const uint32_t arg // TODO: check 32 or 64 bit? it's "uint_t" in the docs
#define declN(arg) // no arg here
#define declLog(arg) const bool log_form = false
#define declDim(arg) const uint64_t n, const uint64_t k
#define declSeed(arg) const uint64_t seed_val = std::random_device{}()
#define declEng(arg) rand_engine_t& engine
#define declMr(arg) Mxd_ref X // reference to double mat
#define declMir(arg) Mxi_ref X // reference to integer mat

// extra template stuff
#define tempM <Mxd>
#define tempMi <Mxi>
#define tempN // i.e. no <>

// things passed to internal fn
#define eleD(arg) arg
#define eleI(arg) arg
#define eleMr X
#define eleMir X
#define eleSeed(arg) seed_val
#define eleEng(arg) engine
#define eleDim(arg) n, k
#define eleN(arg)
#define eleLog(arg) log_form

// commas
#define commaD ,
#define commaI ,
#define commaSeed ,
#define commaEng ,
#define commaDim ,
#define commaLog ,
#define commaMr ,
#define commaMir ,
#define commaN

// inspired by https://github.com/kaskr/adcomp/blob/master/TMB/inst/include/Vectorize.hpp
#define GRAND(FUN, Ret, Temp, Type1, Type2, Type3, Type4) \
out##Ret fn##FUN ( decl##Type1(arg1) comma##Type2 \
             decl##Type2(arg2) comma##Type3 \
             decl##Type3(arg3) comma##Type4 \
             decl##Type4(arg4) ) \
{ return stats::fn##FUN \
temp##Temp ( ele##Type1(arg1) comma##Type2 \
             ele##Type2(arg2) comma##Type3 \
             ele##Type3(arg3) comma##Type4 \
           ); } \
