/* This file was automatically generated by CasADi.
   The CasADi copyright holders make no ownership claim of its contents. */
#ifdef __cplusplus
extern "C" {
#endif

/* How to prefix internal symbols */
#ifdef CODEGEN_PREFIX
  #define NAMESPACE_CONCAT(NS, ID) _NAMESPACE_CONCAT(NS, ID)
  #define _NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else
  #define CASADI_PREFIX(ID) impl_ode_fun_jac_x_xdot_ ## ID
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

static const casadi_int casadi_s0[8] = {4, 1, 0, 4, 0, 1, 2, 3};
static const casadi_int casadi_s1[5] = {1, 1, 0, 1, 0};
static const casadi_int casadi_s2[48] = {4, 9, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};

casadi_real casadi_sq(casadi_real x) { return x*x;}

/* casadi_impl_ode_fun_jac_x_xdot:(i0[4],i1[4],i2)->(o0[4x9]) */
static int casadi_f0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem) {
  casadi_real a0, a1, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a2, a20, a21, a22, a23, a3, a4, a5, a6, a7, a8, a9;
  a0=arg[1] ? arg[1][0] : 0;
  a1=arg[0] ? arg[0][2] : 0;
  a0=(a0-a1);
  if (res[0]!=0) res[0][0]=a0;
  a0=arg[1] ? arg[1][1] : 0;
  a1=arg[0] ? arg[0][3] : 0;
  a0=(a0-a1);
  if (res[0]!=0) res[0][1]=a0;
  a0=arg[1] ? arg[1][2] : 0;
  a2=-8.0000000000000016e-02;
  a3=arg[0] ? arg[0][1] : 0;
  a4=sin(a3);
  a4=(a2*a4);
  a5=casadi_sq(a1);
  a6=(a4*a5);
  a7=arg[2] ? arg[2][0] : 0;
  a6=(a6+a7);
  a8=9.8100000000000009e-01;
  a9=cos(a3);
  a9=(a8*a9);
  a10=sin(a3);
  a11=(a9*a10);
  a6=(a6+a11);
  a11=1.1000000000000001e+00;
  a12=1.0000000000000001e-01;
  a13=cos(a3);
  a14=casadi_sq(a13);
  a14=(a12*a14);
  a14=(a11-a14);
  a6=(a6/a14);
  a0=(a0-a6);
  if (res[0]!=0) res[0][2]=a0;
  a0=arg[1] ? arg[1][3] : 0;
  a15=cos(a3);
  a15=(a2*a15);
  a16=sin(a3);
  a17=(a15*a16);
  a18=casadi_sq(a1);
  a19=(a17*a18);
  a20=cos(a3);
  a20=(a7*a20);
  a19=(a19+a20);
  a20=sin(a3);
  a20=(a8*a20);
  a19=(a19+a20);
  a20=9.8100000000000005e+00;
  a21=sin(a3);
  a21=(a20*a21);
  a19=(a19+a21);
  a21=8.0000000000000004e-01;
  a22=cos(a3);
  a23=casadi_sq(a22);
  a23=(a12*a23);
  a11=(a11-a23);
  a11=(a21*a11);
  a19=(a19/a11);
  a0=(a0-a19);
  if (res[0]!=0) res[0][3]=a0;
  a0=0.;
  if (res[0]!=0) res[0][4]=a0;
  if (res[0]!=0) res[0][5]=a0;
  if (res[0]!=0) res[0][6]=a0;
  if (res[0]!=0) res[0][7]=a0;
  if (res[0]!=0) res[0][8]=a0;
  if (res[0]!=0) res[0][9]=a0;
  a23=cos(a3);
  a23=(a2*a23);
  a5=(a5*a23);
  a23=cos(a3);
  a9=(a9*a23);
  a23=sin(a3);
  a23=(a8*a23);
  a10=(a10*a23);
  a9=(a9-a10);
  a5=(a5+a9);
  a5=(a5/a14);
  a6=(a6/a14);
  a13=(a13+a13);
  a9=sin(a3);
  a13=(a13*a9);
  a13=(a12*a13);
  a6=(a6*a13);
  a5=(a5-a6);
  a5=(-a5);
  if (res[0]!=0) res[0][10]=a5;
  a5=cos(a3);
  a15=(a15*a5);
  a5=sin(a3);
  a2=(a2*a5);
  a16=(a16*a2);
  a15=(a15-a16);
  a18=(a18*a15);
  a15=sin(a3);
  a7=(a7*a15);
  a18=(a18-a7);
  a7=cos(a3);
  a8=(a8*a7);
  a18=(a18+a8);
  a8=cos(a3);
  a20=(a20*a8);
  a18=(a18+a20);
  a18=(a18/a11);
  a19=(a19/a11);
  a22=(a22+a22);
  a3=sin(a3);
  a22=(a22*a3);
  a12=(a12*a22);
  a21=(a21*a12);
  a19=(a19*a21);
  a18=(a18-a19);
  a18=(-a18);
  if (res[0]!=0) res[0][11]=a18;
  a18=-1.;
  if (res[0]!=0) res[0][12]=a18;
  if (res[0]!=0) res[0][13]=a0;
  if (res[0]!=0) res[0][14]=a0;
  if (res[0]!=0) res[0][15]=a0;
  if (res[0]!=0) res[0][16]=a0;
  if (res[0]!=0) res[0][17]=a18;
  a18=(a1+a1);
  a4=(a4*a18);
  a4=(a4/a14);
  a4=(-a4);
  if (res[0]!=0) res[0][18]=a4;
  a1=(a1+a1);
  a17=(a17*a1);
  a17=(a17/a11);
  a17=(-a17);
  if (res[0]!=0) res[0][19]=a17;
  a17=1.;
  if (res[0]!=0) res[0][20]=a17;
  if (res[0]!=0) res[0][21]=a0;
  if (res[0]!=0) res[0][22]=a0;
  if (res[0]!=0) res[0][23]=a0;
  if (res[0]!=0) res[0][24]=a0;
  if (res[0]!=0) res[0][25]=a17;
  if (res[0]!=0) res[0][26]=a0;
  if (res[0]!=0) res[0][27]=a0;
  if (res[0]!=0) res[0][28]=a0;
  if (res[0]!=0) res[0][29]=a0;
  if (res[0]!=0) res[0][30]=a17;
  if (res[0]!=0) res[0][31]=a0;
  if (res[0]!=0) res[0][32]=a0;
  if (res[0]!=0) res[0][33]=a0;
  if (res[0]!=0) res[0][34]=a0;
  if (res[0]!=0) res[0][35]=a17;
  return 0;
}

CASADI_SYMBOL_EXPORT int casadi_impl_ode_fun_jac_x_xdot(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, void* mem){
  return casadi_f0(arg, res, iw, w, mem);
}

CASADI_SYMBOL_EXPORT void casadi_impl_ode_fun_jac_x_xdot_incref(void) {
}

CASADI_SYMBOL_EXPORT void casadi_impl_ode_fun_jac_x_xdot_decref(void) {
}

CASADI_SYMBOL_EXPORT casadi_int casadi_impl_ode_fun_jac_x_xdot_n_in(void) { return 3;}

CASADI_SYMBOL_EXPORT casadi_int casadi_impl_ode_fun_jac_x_xdot_n_out(void) { return 1;}

CASADI_SYMBOL_EXPORT const char* casadi_impl_ode_fun_jac_x_xdot_name_in(casadi_int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* casadi_impl_ode_fun_jac_x_xdot_name_out(casadi_int i){
  switch (i) {
    case 0: return "o0";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* casadi_impl_ode_fun_jac_x_xdot_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s0;
    case 2: return casadi_s1;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* casadi_impl_ode_fun_jac_x_xdot_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s2;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int casadi_impl_ode_fun_jac_x_xdot_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 3;
  if (sz_res) *sz_res = 1;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 0;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
