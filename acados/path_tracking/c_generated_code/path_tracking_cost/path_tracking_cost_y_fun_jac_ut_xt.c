/* This file was automatically generated by CasADi.
   The CasADi copyright holders make no ownership claim of its contents. */
#ifdef __cplusplus
extern "C" {
#endif

/* How to prefix internal symbols */
#ifdef CASADI_CODEGEN_PREFIX
  #define CASADI_NAMESPACE_CONCAT(NS, ID) _CASADI_NAMESPACE_CONCAT(NS, ID)
  #define _CASADI_NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) CASADI_NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else
  #define CASADI_PREFIX(ID) path_tracking_cost_y_fun_jac_ut_xt_ ## ID
#endif

#include <math.h>

#ifndef casadi_real
#define casadi_real double
#endif

#ifndef casadi_int
#define casadi_int int
#endif

/* Add prefix to internal symbols */
#define casadi_f0 CASADI_PREFIX(f0)
#define casadi_s0 CASADI_PREFIX(s0)
#define casadi_s1 CASADI_PREFIX(s1)
#define casadi_s2 CASADI_PREFIX(s2)
#define casadi_s3 CASADI_PREFIX(s3)
#define casadi_sq CASADI_PREFIX(sq)

/* Symbol visibility in DLLs */
#ifndef CASADI_SYMBOL_EXPORT
  #if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
    #if defined(STATIC_LINKED)
      #define CASADI_SYMBOL_EXPORT
    #else
      #define CASADI_SYMBOL_EXPORT __declspec(dllexport)
    #endif
  #elif defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
    #define CASADI_SYMBOL_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define CASADI_SYMBOL_EXPORT
  #endif
#endif

casadi_real casadi_sq(casadi_real x) { return x*x;}

static const casadi_int casadi_s0[10] = {6, 1, 0, 6, 0, 1, 2, 3, 4, 5};
static const casadi_int casadi_s1[6] = {2, 1, 0, 2, 0, 1};
static const casadi_int casadi_s2[11] = {7, 1, 0, 7, 0, 1, 2, 3, 4, 5, 6};
static const casadi_int casadi_s3[19] = {8, 7, 0, 2, 4, 5, 6, 7, 8, 9, 2, 3, 2, 4, 5, 6, 7, 0, 1};

/* path_tracking_cost_y_fun_jac_ut_xt:(i0[6],i1[2],i2[6])->(o0[7],o1[8x7,9nz]) */
static int casadi_f0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real a0, a1, a10, a2, a3, a4, a5, a6, a7, a8, a9;
  a0=arg[2]? arg[2][3] : 0;
  a1=arg[0]? arg[0][0] : 0;
  a2=casadi_sq(a1);
  a3=(a1*a2);
  a3=(a0*a3);
  a4=arg[2]? arg[2][2] : 0;
  a5=casadi_sq(a1);
  a5=(a4*a5);
  a3=(a3+a5);
  a5=arg[2]? arg[2][1] : 0;
  a6=(a5*a1);
  a3=(a3+a6);
  a6=arg[2]? arg[2][0] : 0;
  a3=(a3+a6);
  a6=arg[0]? arg[0][1] : 0;
  a3=(a3-a6);
  if (res[0]!=0) res[0][0]=a3;
  a3=arg[0]? arg[0][2] : 0;
  a6=3.;
  a6=(a6*a0);
  a7=(a6*a1);
  a8=(a7*a1);
  a9=2.;
  a9=(a9*a4);
  a10=(a9*a1);
  a8=(a8+a10);
  a8=(a8+a5);
  a10=atan(a8);
  a3=(a3-a10);
  if (res[0]!=0) res[0][1]=a3;
  a3=arg[0]? arg[0][3] : 0;
  a10=arg[2]? arg[2][5] : 0;
  a3=(a3-a10);
  if (res[0]!=0) res[0][2]=a3;
  a3=arg[0]? arg[0][4] : 0;
  if (res[0]!=0) res[0][3]=a3;
  a3=arg[0]? arg[0][5] : 0;
  if (res[0]!=0) res[0][4]=a3;
  a3=arg[1]? arg[1][0] : 0;
  if (res[0]!=0) res[0][5]=a3;
  a3=arg[1]? arg[1][1] : 0;
  if (res[0]!=0) res[0][6]=a3;
  a3=(a1+a1);
  a3=(a1*a3);
  a2=(a2+a3);
  a0=(a0*a2);
  a2=(a1+a1);
  a4=(a4*a2);
  a0=(a0+a4);
  a0=(a0+a5);
  if (res[1]!=0) res[1][0]=a0;
  a0=-1.;
  if (res[1]!=0) res[1][1]=a0;
  a1=(a1*a6);
  a1=(a1+a7);
  a1=(a1+a9);
  a9=1.;
  a8=casadi_sq(a8);
  a8=(a9+a8);
  a1=(a1/a8);
  a1=(-a1);
  if (res[1]!=0) res[1][2]=a1;
  if (res[1]!=0) res[1][3]=a9;
  if (res[1]!=0) res[1][4]=a9;
  if (res[1]!=0) res[1][5]=a9;
  if (res[1]!=0) res[1][6]=a9;
  if (res[1]!=0) res[1][7]=a9;
  if (res[1]!=0) res[1][8]=a9;
  return 0;
}

CASADI_SYMBOL_EXPORT int path_tracking_cost_y_fun_jac_ut_xt(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f0(arg, res, iw, w, mem);
}

CASADI_SYMBOL_EXPORT int path_tracking_cost_y_fun_jac_ut_xt_alloc_mem(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT int path_tracking_cost_y_fun_jac_ut_xt_init_mem(int mem) {
  return 0;
}

CASADI_SYMBOL_EXPORT void path_tracking_cost_y_fun_jac_ut_xt_free_mem(int mem) {
}

CASADI_SYMBOL_EXPORT int path_tracking_cost_y_fun_jac_ut_xt_checkout(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT void path_tracking_cost_y_fun_jac_ut_xt_release(int mem) {
}

CASADI_SYMBOL_EXPORT void path_tracking_cost_y_fun_jac_ut_xt_incref(void) {
}

CASADI_SYMBOL_EXPORT void path_tracking_cost_y_fun_jac_ut_xt_decref(void) {
}

CASADI_SYMBOL_EXPORT casadi_int path_tracking_cost_y_fun_jac_ut_xt_n_in(void) { return 3;}

CASADI_SYMBOL_EXPORT casadi_int path_tracking_cost_y_fun_jac_ut_xt_n_out(void) { return 2;}

CASADI_SYMBOL_EXPORT casadi_real path_tracking_cost_y_fun_jac_ut_xt_default_in(casadi_int i){
  switch (i) {
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* path_tracking_cost_y_fun_jac_ut_xt_name_in(casadi_int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* path_tracking_cost_y_fun_jac_ut_xt_name_out(casadi_int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* path_tracking_cost_y_fun_jac_ut_xt_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s1;
    case 2: return casadi_s0;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* path_tracking_cost_y_fun_jac_ut_xt_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s2;
    case 1: return casadi_s3;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int path_tracking_cost_y_fun_jac_ut_xt_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 3;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 0;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
