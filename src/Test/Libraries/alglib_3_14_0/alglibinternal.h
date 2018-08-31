/*************************************************************************
ALGLIB 3.14.0 (source code generated 2018-06-16)
Copyright (c) Sergey Bochkanov (ALGLIB project).

>>> SOURCE LICENSE >>>
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation (www.fsf.org); either version 2 of the 
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

A copy of the GNU General Public License is available at
http://www.fsf.org/licensing/licenses
>>> END OF LICENSE >>>
*************************************************************************/
#ifndef _alglibinternal_pkg_h
#define _alglibinternal_pkg_h
#include "ap.h"


/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (DATATYPES)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_SCODES) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_APSERV) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 */
typedef struct
{
    ae_vector ba0; /**< TODO: describe */
    ae_vector ia0; /**< TODO: describe */
    ae_vector ia1; /**< TODO: describe */
    ae_vector ia2; /**< TODO: describe */
    ae_vector ia3; /**< TODO: describe */
    ae_vector ra0; /**< TODO: describe */
    ae_vector ra1; /**< TODO: describe */
    ae_vector ra2; /**< TODO: describe */
    ae_vector ra3; /**< TODO: describe */
    ae_matrix rm0; /**< TODO: describe */
    ae_matrix rm1; /**< TODO: describe */
/**
 * @brief
 *
 */
} apbuffers;
/**
 * @brief
 *
 */
typedef struct
{
    ae_bool val; /**< TODO: describe */
/**
 * @brief
 *
 */
} sboolean;
/**
 * @brief
 *
 */
typedef struct
{
    ae_vector val; /**< TODO: describe */
/**
 * @brief
 *
 */
} sbooleanarray;
/**
 * @brief
 *
 */
typedef struct
{
    ae_int_t val; /**< TODO: describe */
/**
 * @brief
 *
 */
} sinteger;
/**
 * @brief
 *
 */
typedef struct
{
    ae_vector val; /**< TODO: describe */
/**
 * @brief
 *
 */
} sintegerarray;
/**
 * @brief
 *
 */
typedef struct
{
    double val; /**< TODO: describe */
/**
 * @brief
 *
 */
} sreal;
/**
 * @brief
 *
 */
typedef struct
{
    ae_vector val; /**< TODO: describe */
/**
 * @brief
 *
 */
} srealarray;
/**
 * @brief
 *
 */
typedef struct
{
    ae_complex val; /**< TODO: describe */
/**
 * @brief
 *
 */
} scomplex;
/**
 * @brief
 *
 */
typedef struct
{
    ae_vector val; /**< TODO: describe */
/**
 * @brief
 *
 */
} scomplexarray;
#endif
#if defined(AE_COMPILE_TSORT) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_ABLASMKL) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_ABLASF) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_CREFLECTIONS) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_ROTATIONS) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_TRLINSOLVE) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_SAFESOLVE) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_HBLAS) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_SBLAS) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_BLAS) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_LINMIN) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 */
typedef struct
{
    ae_bool brackt; /**< TODO: describe */
    ae_bool stage1; /**< TODO: describe */
    ae_int_t infoc; /**< TODO: describe */
    double dg; /**< TODO: describe */
    double dgm; /**< TODO: describe */
    double dginit; /**< TODO: describe */
    double dgtest; /**< TODO: describe */
    double dgx; /**< TODO: describe */
    double dgxm; /**< TODO: describe */
    double dgy; /**< TODO: describe */
    double dgym; /**< TODO: describe */
    double finit; /**< TODO: describe */
    double ftest1; /**< TODO: describe */
    double fm; /**< TODO: describe */
    double fx; /**< TODO: describe */
    double fxm; /**< TODO: describe */
    double fy; /**< TODO: describe */
    double fym; /**< TODO: describe */
    double stx; /**< TODO: describe */
    double sty; /**< TODO: describe */
    double stmin; /**< TODO: describe */
    double stmax; /**< TODO: describe */
    double width; /**< TODO: describe */
    double width1; /**< TODO: describe */
    double xtrapf; /**< TODO: describe */
/**
 * @brief
 *
 */
} linminstate;
/**
 * @brief
 *
 */
typedef struct
{
    ae_bool needf; /**< TODO: describe */
    ae_vector x; /**< TODO: describe */
    double f; /**< TODO: describe */
    ae_int_t n; /**< TODO: describe */
    ae_vector xbase; /**< TODO: describe */
    ae_vector s; /**< TODO: describe */
    double stplen; /**< TODO: describe */
    double fcur; /**< TODO: describe */
    double stpmax; /**< TODO: describe */
    ae_int_t fmax; /**< TODO: describe */
    ae_int_t nfev; /**< TODO: describe */
    ae_int_t info; /**< TODO: describe */
    rcommstate rstate; /**< TODO: describe */
/**
 * @brief
 *
 */
} armijostate;
#endif
#if defined(AE_COMPILE_XBLAS) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_BASICSTATOPS) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_HPCCORES) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 */
typedef struct
{
    ae_int_t chunksize; /**< TODO: describe */
    ae_int_t ntotal; /**< TODO: describe */
    ae_int_t nin; /**< TODO: describe */
    ae_int_t nout; /**< TODO: describe */
    ae_int_t wcount; /**< TODO: describe */
    ae_vector batch4buf; /**< TODO: describe */
    ae_vector hpcbuf; /**< TODO: describe */
    ae_matrix xy; /**< TODO: describe */
    ae_matrix xy2; /**< TODO: describe */
    ae_vector xyrow; /**< TODO: describe */
    ae_vector x; /**< TODO: describe */
    ae_vector y; /**< TODO: describe */
    ae_vector desiredy; /**< TODO: describe */
    double e; /**< TODO: describe */
    ae_vector g; /**< TODO: describe */
    ae_vector tmp0; /**< TODO: describe */
/**
 * @brief
 *
 */
} mlpbuffers;
#endif
#if defined(AE_COMPILE_NTHEORY) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_FTBASE) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 */
typedef struct
{
    ae_matrix entries; /**< TODO: describe */
    ae_vector buffer; /**< TODO: describe */
    ae_vector precr; /**< TODO: describe */
    ae_vector preci; /**< TODO: describe */
    ae_shared_pool bluesteinpool; /**< TODO: describe */
/**
 * @brief
 *
 */
} fasttransformplan;
#endif
#if defined(AE_COMPILE_NEARUNITYUNIT) || !defined(AE_PARTIAL_BUILD)
#endif
#if defined(AE_COMPILE_ALGLIBBASICS) || !defined(AE_PARTIAL_BUILD)
#endif

}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{


}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS COMPUTATIONAL CORE DECLARATIONS (FUNCTIONS)
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
#if defined(AE_COMPILE_SCODES) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 * @param _state
 * @return ae_int_t
 */
ae_int_t getrdfserializationcode(ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return ae_int_t
 */
ae_int_t getkdtreeserializationcode(ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return ae_int_t
 */
ae_int_t getmlpserializationcode(ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return ae_int_t
 */
ae_int_t getmlpeserializationcode(ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return ae_int_t
 */
ae_int_t getrbfserializationcode(ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return ae_int_t
 */
ae_int_t getspline2dserializationcode(ae_state *_state);
#endif
#if defined(AE_COMPILE_APSERV) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 * @param flag
 * @param val
 * @param refval
 * @param tol
 * @param s
 * @param _state
 */
void seterrorflagdiff(ae_bool* flag,
     double val,
     double refval,
     double tol,
     double s,
     ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return bool
 */
ae_bool alwaysfalse(ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param _state
 */
void touchint(ae_int_t* a, ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param _state
 */
void touchreal(double* a, ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param b
 * @param _state
 * @return double
 */
double coalesce(double a, double b, ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param b
 * @param _state
 * @return ae_int_t
 */
ae_int_t coalescei(ae_int_t a, ae_int_t b, ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param _state
 * @return double
 */
double inttoreal(ae_int_t a, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param _state
 * @return double
 */
double logbase2(double x, ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param b
 * @param tol
 * @param _state
 * @return bool
 */
ae_bool approxequal(double a, double b, double tol, ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param b
 * @param tol
 * @param _state
 * @return bool
 */
ae_bool approxequalrel(double a, double b, double tol, ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param b
 * @param n
 * @param x
 * @param y
 * @param _state
 */
void taskgenint1d(double a,
     double b,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void taskgenint1dequidist(double a,
     double b,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void taskgenint1dcheb1(double a,
     double b,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void taskgenint1dcheb2(double a,
     double b,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     ae_state *_state);
ae_bool aredistinct(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
ae_bool aresameboolean(ae_bool v1, ae_bool v2, ae_state *_state);
void bvectorsetlengthatleast(/* Boolean */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
void ivectorsetlengthatleast(/* Integer */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
void rvectorsetlengthatleast(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
void rmatrixsetlengthatleast(/* Real    */ ae_matrix* x,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
void ivectorgrowto(/* Integer */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
void rmatrixgrowrowsto(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_int_t mincols,
     ae_state *_state);
void rvectorgrowto(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
void ivectorresize(/* Integer */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
void rvectorresize(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
void rmatrixresize(/* Real    */ ae_matrix* x,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
void imatrixresize(/* Integer */ ae_matrix* x,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
void ivectorappend(/* Integer */ ae_vector* x,
     ae_int_t v,
     ae_state *_state);
ae_bool isfinitevector(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_state *_state);
ae_bool isfinitecvector(/* Complex */ ae_vector* z,
     ae_int_t n,
     ae_state *_state);
ae_bool apservisfinitematrix(/* Real    */ ae_matrix* x,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
ae_bool apservisfinitecmatrix(/* Complex */ ae_matrix* x,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
ae_bool isfinitertrmatrix(/* Real    */ ae_matrix* x,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
ae_bool apservisfinitectrmatrix(/* Complex */ ae_matrix* x,
     ae_int_t n,
     ae_bool isupper,
     ae_state *_state);
ae_bool apservisfiniteornanmatrix(/* Real    */ ae_matrix* x,
     ae_int_t m,
     ae_int_t n,
     ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param y
 * @param _state
 * @return double
 */
double safepythag2(double x, double y, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param y
 * @param z
 * @param _state
 * @return double
 */
double safepythag3(double x, double y, double z, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param y
 * @param r
 * @param _state
 * @return ae_int_t
 */
ae_int_t saferdiv(double x, double y, double* r, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param y
 * @param v
 * @param _state
 * @return double
 */
double safeminposrv(double x, double y, double v, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param a
 * @param b
 * @param k
 * @param _state
 */
void apperiodicmap(double* x,
     double a,
     double b,
     double* k,
     ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return double
 */
double randomnormal(ae_state *_state);
void randomunit(ae_int_t n, /* Real    */ ae_vector* x, ae_state *_state);
void swapi(ae_int_t* v0, ae_int_t* v1, ae_state *_state);
void swapr(double* v0, double* v1, ae_state *_state);
void swaprows(/* Real    */ ae_matrix* a,
     ae_int_t i0,
     ae_int_t i1,
     ae_int_t ncols,
     ae_state *_state);
void swapentries(/* Real    */ ae_vector* a,
     ae_int_t i0,
     ae_int_t i1,
     ae_int_t entrywidth,
     ae_state *_state);
void swapelements(/* Real    */ ae_vector* a,
     ae_int_t i0,
     ae_int_t i1,
     ae_state *_state);
void swapelementsi(/* Integer */ ae_vector* a,
     ae_int_t i0,
     ae_int_t i1,
     ae_state *_state);
/**
 * @brief
 *
 * @param v0
 * @param v1
 * @param v2
 * @param _state
 * @return double
 */
double maxreal3(double v0, double v1, double v2, ae_state *_state);
/**
 * @brief
 *
 * @param v
 * @param _state
 */
void inc(ae_int_t* v, ae_state *_state);
/**
 * @brief
 *
 * @param v
 * @param _state
 */
void dec(ae_int_t* v, ae_state *_state);
/**
 * @brief
 *
 * @param v
 * @param _state
 */
void threadunsafeinc(ae_int_t* v, ae_state *_state);
/**
 * @brief
 *
 * @param v
 * @param _state
 */
void countdown(ae_int_t* v, ae_state *_state);
/**
 * @brief
 *
 * @param v0
 * @param v1
 * @param _state
 * @return double
 */
double rmul2(double v0, double v1, ae_state *_state);
/**
 * @brief
 *
 * @param v0
 * @param v1
 * @param v2
 * @param _state
 * @return double
 */
double rmul3(double v0, double v1, double v2, ae_state *_state);
/**
 * @brief
 *
 * @param a
 * @param b
 * @param _state
 * @return ae_int_t
 */
ae_int_t idivup(ae_int_t a, ae_int_t b, ae_state *_state);
/**
 * @brief
 *
 * @param i0
 * @param i1
 * @param _state
 * @return ae_int_t
 */
ae_int_t imin2(ae_int_t i0, ae_int_t i1, ae_state *_state);
/**
 * @brief
 *
 * @param i0
 * @param i1
 * @param i2
 * @param _state
 * @return ae_int_t
 */
ae_int_t imin3(ae_int_t i0, ae_int_t i1, ae_int_t i2, ae_state *_state);
/**
 * @brief
 *
 * @param i0
 * @param i1
 * @param _state
 * @return ae_int_t
 */
ae_int_t imax2(ae_int_t i0, ae_int_t i1, ae_state *_state);
/**
 * @brief
 *
 * @param i0
 * @param i1
 * @param i2
 * @param _state
 * @return ae_int_t
 */
ae_int_t imax3(ae_int_t i0, ae_int_t i1, ae_int_t i2, ae_state *_state);
/**
 * @brief
 *
 * @param r0
 * @param r1
 * @param r2
 * @param _state
 * @return double
 */
double rmax3(double r0, double r1, double r2, ae_state *_state);
/**
 * @brief
 *
 * @param r0
 * @param r1
 * @param r2
 * @param _state
 * @return double
 */
double rmaxabs3(double r0, double r1, double r2, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param b1
 * @param b2
 * @param _state
 * @return double
 */
double boundval(double x, double b1, double b2, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param b1
 * @param b2
 * @param _state
 * @return ae_int_t
 */
ae_int_t iboundval(ae_int_t x, ae_int_t b1, ae_int_t b2, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param b1
 * @param b2
 * @param _state
 * @return double
 */
double rboundval(double x, double b1, double b2, ae_state *_state);
/**
 * @brief
 *
 * @param s
 * @param v
 * @param _state
 */
void alloccomplex(ae_serializer* s, ae_complex v, ae_state *_state);
/**
 * @brief
 *
 * @param s
 * @param v
 * @param _state
 */
void serializecomplex(ae_serializer* s, ae_complex v, ae_state *_state);
/**
 * @brief
 *
 * @param s
 * @param _state
 * @return ae_complex
 */
ae_complex unserializecomplex(ae_serializer* s, ae_state *_state);
/**
 * @brief
 *
 * @param s
 * @param v
 * @param n
 * @param _state
 */
void allocrealarray(ae_serializer* s,
     /* Real    */ ae_vector* v,
     ae_int_t n,
     ae_state *_state);
void serializerealarray(ae_serializer* s,
     /* Real    */ ae_vector* v,
     ae_int_t n,
     ae_state *_state);
void unserializerealarray(ae_serializer* s,
     /* Real    */ ae_vector* v,
     ae_state *_state);
void allocintegerarray(ae_serializer* s,
     /* Integer */ ae_vector* v,
     ae_int_t n,
     ae_state *_state);
void serializeintegerarray(ae_serializer* s,
     /* Integer */ ae_vector* v,
     ae_int_t n,
     ae_state *_state);
void unserializeintegerarray(ae_serializer* s,
     /* Integer */ ae_vector* v,
     ae_state *_state);
void allocrealmatrix(ae_serializer* s,
     /* Real    */ ae_matrix* v,
     ae_int_t n0,
     ae_int_t n1,
     ae_state *_state);
/**
 * @brief
 *
 * @param s
 * @param v
 * @param n0
 * @param n1
 * @param _state
 */
void serializerealmatrix(ae_serializer* s,
     /* Real    */ ae_matrix* v,
     ae_int_t n0,
     ae_int_t n1,
     ae_state *_state);
/**
 * @brief
 *
 * @param s
 * @param v
 * @param _state
 */
void unserializerealmatrix(ae_serializer* s,
     /* Real    */ ae_matrix* v,
     ae_state *_state);
void copyintegerarray(/* Integer */ ae_vector* src,
     /* Integer */ ae_vector* dst,
     ae_state *_state);
void copyrealarray(/* Real    */ ae_vector* src,
     /* Real    */ ae_vector* dst,
     ae_state *_state);
void copyrealmatrix(/* Real    */ ae_matrix* src,
     /* Real    */ ae_matrix* dst,
     ae_state *_state);
void unsetintegerarray(/* Integer */ ae_vector* a, ae_state *_state);
void unsetrealarray(/* Real    */ ae_vector* a, ae_state *_state);
void unsetrealmatrix(/* Real    */ ae_matrix* a, ae_state *_state);
void tiledsplit(ae_int_t tasksize,
     ae_int_t tilesize,
     ae_int_t* task0,
     ae_int_t* task1,
     ae_state *_state);
ae_int_t recsearch(/* Integer */ ae_vector* a,
     ae_int_t nrec,
     ae_int_t nheader,
     ae_int_t i0,
     ae_int_t i1,
     /* Integer */ ae_vector* b,
     ae_state *_state);
void splitlengtheven(ae_int_t tasksize,
     ae_int_t* task0,
     ae_int_t* task1,
     ae_state *_state);
/**
 * @brief
 *
 * @param tasksize
 * @param chunksize
 * @param _state
 * @return ae_int_t
 */
ae_int_t chunkscount(ae_int_t tasksize,
     ae_int_t chunksize,
     ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return ae_int_t
 */
ae_int_t matrixtilesizea(ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return ae_int_t
 */
ae_int_t matrixtilesizeb(ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return double
 */
double smpactivationlevel(ae_state *_state);
/**
 * @brief
 *
 * @param _state
 * @return double
 */
double spawnlevel(ae_state *_state);
/**
 * @brief
 *
 * @param tasksize
 * @param chunksize
 * @param task0
 * @param task1
 * @param _state
 */
void splitlength(ae_int_t tasksize,
     ae_int_t chunksize,
     ae_int_t* task0,
     ae_int_t* task1,
     ae_state *_state);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _apbuffers_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _apbuffers_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _apbuffers_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _apbuffers_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _sboolean_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _sboolean_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _sboolean_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _sboolean_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _sbooleanarray_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _sbooleanarray_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _sbooleanarray_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _sbooleanarray_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _sinteger_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _sinteger_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _sinteger_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _sinteger_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _sintegerarray_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _sintegerarray_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _sintegerarray_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _sintegerarray_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _sreal_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _sreal_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _sreal_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _sreal_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _srealarray_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _srealarray_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _srealarray_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _srealarray_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _scomplex_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _scomplex_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _scomplex_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _scomplex_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _scomplexarray_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _scomplexarray_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _scomplexarray_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _scomplexarray_destroy(void* _p);
#endif
#if defined(AE_COMPILE_TSORT) || !defined(AE_PARTIAL_BUILD)
void tagsort(/* Real    */ ae_vector* a,
     ae_int_t n,
     /* Integer */ ae_vector* p1,
     /* Integer */ ae_vector* p2,
     ae_state *_state);
void tagsortbuf(/* Real    */ ae_vector* a,
     ae_int_t n,
     /* Integer */ ae_vector* p1,
     /* Integer */ ae_vector* p2,
     apbuffers* buf,
     ae_state *_state);
void tagsortfasti(/* Real    */ ae_vector* a,
     /* Integer */ ae_vector* b,
     /* Real    */ ae_vector* bufa,
     /* Integer */ ae_vector* bufb,
     ae_int_t n,
     ae_state *_state);
void tagsortfastr(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     /* Real    */ ae_vector* bufa,
     /* Real    */ ae_vector* bufb,
     ae_int_t n,
     ae_state *_state);
void tagsortfast(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* bufa,
     ae_int_t n,
     ae_state *_state);
void tagsortmiddleir(/* Integer */ ae_vector* a,
     /* Real    */ ae_vector* b,
     ae_int_t offset,
     ae_int_t n,
     ae_state *_state);
void tagheappushi(/* Real    */ ae_vector* a,
     /* Integer */ ae_vector* b,
     ae_int_t* n,
     double va,
     ae_int_t vb,
     ae_state *_state);
void tagheapreplacetopi(/* Real    */ ae_vector* a,
     /* Integer */ ae_vector* b,
     ae_int_t n,
     double va,
     ae_int_t vb,
     ae_state *_state);
void tagheappopi(/* Real    */ ae_vector* a,
     /* Integer */ ae_vector* b,
     ae_int_t* n,
     ae_state *_state);
ae_int_t lowerbound(/* Real    */ ae_vector* a,
     ae_int_t n,
     double t,
     ae_state *_state);
ae_int_t upperbound(/* Real    */ ae_vector* a,
     ae_int_t n,
     double t,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_ABLASMKL) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param ia
 * @param ja
 * @param alpha
 * @param u
 * @param iu
 * @param v
 * @param iv
 * @param _state
 * @return bool
 */
ae_bool rmatrixgermkl(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     double alpha,
     /* Real    */ ae_vector* u,
     ae_int_t iu,
     /* Real    */ ae_vector* v,
     ae_int_t iv,
     ae_state *_state);
ae_bool cmatrixrank1mkl(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Complex */ ae_vector* u,
     ae_int_t iu,
     /* Complex */ ae_vector* v,
     ae_int_t iv,
     ae_state *_state);
ae_bool rmatrixrank1mkl(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_vector* u,
     ae_int_t iu,
     /* Real    */ ae_vector* v,
     ae_int_t iv,
     ae_state *_state);
ae_bool cmatrixmvmkl(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t opa,
     /* Complex */ ae_vector* x,
     ae_int_t ix,
     /* Complex */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state);
ae_bool rmatrixmvmkl(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t opa,
     /* Real    */ ae_vector* x,
     ae_int_t ix,
     /* Real    */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state);
ae_bool rmatrixgemvmkl(ae_int_t m,
     ae_int_t n,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t opa,
     /* Real    */ ae_vector* x,
     ae_int_t ix,
     double beta,
     /* Real    */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state);
ae_bool rmatrixtrsvmkl(ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_vector* x,
     ae_int_t ix,
     ae_state *_state);
ae_bool rmatrixsyrkmkl(ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper,
     ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param optypea
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param isupper
 * @param _state
 * @return bool
 */
ae_bool cmatrixherkmkl(ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     /* Complex */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param optypea
 * @param b
 * @param ib
 * @param jb
 * @param optypeb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 * @return bool
 */
ae_bool rmatrixgemmmkl(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param isupper
 * @param x
 * @param ix
 * @param beta
 * @param y
 * @param iy
 * @param _state
 * @return bool
 */
ae_bool rmatrixsymvmkl(ae_int_t n,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_bool isupper,
     /* Real    */ ae_vector* x,
     ae_int_t ix,
     double beta,
     /* Real    */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state);
ae_bool cmatrixgemmmkl(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     ae_complex alpha,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Complex */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     ae_complex beta,
     /* Complex */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param i1
 * @param j1
 * @param isupper
 * @param isunit
 * @param optype
 * @param x
 * @param i2
 * @param j2
 * @param _state
 * @return bool
 */
ae_bool cmatrixlefttrsmmkl(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Complex */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param i1
 * @param j1
 * @param isupper
 * @param isunit
 * @param optype
 * @param x
 * @param i2
 * @param j2
 * @param _state
 * @return bool
 */
ae_bool cmatrixrighttrsmmkl(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Complex */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param i1
 * @param j1
 * @param isupper
 * @param isunit
 * @param optype
 * @param x
 * @param i2
 * @param j2
 * @param _state
 * @return bool
 */
ae_bool rmatrixlefttrsmmkl(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param i1
 * @param j1
 * @param isupper
 * @param isunit
 * @param optype
 * @param x
 * @param i2
 * @param j2
 * @param _state
 * @return bool
 */
ae_bool rmatrixrighttrsmmkl(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
ae_bool spdmatrixcholeskymkl(/* Real    */ ae_matrix* a,
     ae_int_t offs,
     ae_int_t n,
     ae_bool isupper,
     ae_bool* cholresult,
     ae_state *_state);
ae_bool rmatrixplumkl(/* Real    */ ae_matrix* a,
     ae_int_t offs,
     ae_int_t m,
     ae_int_t n,
     /* Integer */ ae_vector* pivots,
     ae_state *_state);
ae_bool rmatrixbdmkl(/* Real    */ ae_matrix* a,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     /* Real    */ ae_vector* tauq,
     /* Real    */ ae_vector* taup,
     ae_state *_state);
ae_bool rmatrixbdmultiplybymkl(/* Real    */ ae_matrix* qp,
     ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_vector* tauq,
     /* Real    */ ae_vector* taup,
     /* Real    */ ae_matrix* z,
     ae_int_t zrows,
     ae_int_t zcolumns,
     ae_bool byq,
     ae_bool fromtheright,
     ae_bool dotranspose,
     ae_state *_state);
ae_bool rmatrixhessenbergmkl(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_vector* tau,
     ae_state *_state);
ae_bool rmatrixhessenbergunpackqmkl(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_vector* tau,
     /* Real    */ ae_matrix* q,
     ae_state *_state);
ae_bool smatrixtdmkl(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tau,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_state *_state);
ae_bool smatrixtdunpackqmkl(/* Real    */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_vector* tau,
     /* Real    */ ae_matrix* q,
     ae_state *_state);
ae_bool hmatrixtdmkl(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* tau,
     /* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_state *_state);
ae_bool hmatrixtdunpackqmkl(/* Complex */ ae_matrix* a,
     ae_int_t n,
     ae_bool isupper,
     /* Complex */ ae_vector* tau,
     /* Complex */ ae_matrix* q,
     ae_state *_state);
ae_bool rmatrixbdsvdmkl(/* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_int_t n,
     ae_bool isupper,
     /* Real    */ ae_matrix* u,
     ae_int_t nru,
     /* Real    */ ae_matrix* c,
     ae_int_t ncc,
     /* Real    */ ae_matrix* vt,
     ae_int_t ncvt,
     ae_bool* svdresult,
     ae_state *_state);
ae_bool rmatrixinternalschurdecompositionmkl(/* Real    */ ae_matrix* h,
     ae_int_t n,
     ae_int_t tneeded,
     ae_int_t zneeded,
     /* Real    */ ae_vector* wr,
     /* Real    */ ae_vector* wi,
     /* Real    */ ae_matrix* z,
     ae_int_t* info,
     ae_state *_state);
ae_bool rmatrixinternaltrevcmkl(/* Real    */ ae_matrix* t,
     ae_int_t n,
     ae_int_t side,
     ae_int_t howmny,
     /* Real    */ ae_matrix* vl,
     /* Real    */ ae_matrix* vr,
     ae_int_t* m,
     ae_int_t* info,
     ae_state *_state);
ae_bool smatrixtdevdmkl(/* Real    */ ae_vector* d,
     /* Real    */ ae_vector* e,
     ae_int_t n,
     ae_int_t zneeded,
     /* Real    */ ae_matrix* z,
     ae_bool* evdresult,
     ae_state *_state);
ae_bool sparsegemvcrsmkl(ae_int_t opa,
     ae_int_t arows,
     ae_int_t acols,
     double alpha,
     /* Real    */ ae_vector* vals,
     /* Integer */ ae_vector* cidx,
     /* Integer */ ae_vector* ridx,
     /* Real    */ ae_vector* x,
     ae_int_t ix,
     double beta,
     /* Real    */ ae_vector* y,
     ae_int_t iy,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_ABLASF) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param ia
 * @param ja
 * @param ralpha
 * @param u
 * @param iu
 * @param v
 * @param iv
 * @param _state
 * @return bool
 */
ae_bool rmatrixgerf(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     double ralpha,
     /* Real    */ ae_vector* u,
     ae_int_t iu,
     /* Real    */ ae_vector* v,
     ae_int_t iv,
     ae_state *_state);
ae_bool cmatrixrank1f(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Complex */ ae_vector* u,
     ae_int_t iu,
     /* Complex */ ae_vector* v,
     ae_int_t iv,
     ae_state *_state);
ae_bool rmatrixrank1f(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_vector* u,
     ae_int_t iu,
     /* Real    */ ae_vector* v,
     ae_int_t iv,
     ae_state *_state);
ae_bool cmatrixrighttrsmf(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Complex */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param i1
 * @param j1
 * @param isupper
 * @param isunit
 * @param optype
 * @param x
 * @param i2
 * @param j2
 * @param _state
 * @return bool
 */
ae_bool cmatrixlefttrsmf(ae_int_t m,
     ae_int_t n,
     /* Complex */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Complex */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param i1
 * @param j1
 * @param isupper
 * @param isunit
 * @param optype
 * @param x
 * @param i2
 * @param j2
 * @param _state
 * @return bool
 */
ae_bool rmatrixrighttrsmf(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param a
 * @param i1
 * @param j1
 * @param isupper
 * @param isunit
 * @param optype
 * @param x
 * @param i2
 * @param j2
 * @param _state
 * @return bool
 */
ae_bool rmatrixlefttrsmf(ae_int_t m,
     ae_int_t n,
     /* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t j1,
     ae_bool isupper,
     ae_bool isunit,
     ae_int_t optype,
     /* Real    */ ae_matrix* x,
     ae_int_t i2,
     ae_int_t j2,
     ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param optypea
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param isupper
 * @param _state
 * @return bool
 */
ae_bool cmatrixherkf(ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     /* Complex */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper,
     ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param optypea
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param isupper
 * @param _state
 * @return bool
 */
ae_bool rmatrixsyrkf(ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_bool isupper,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param optypea
 * @param b
 * @param ib
 * @param jb
 * @param optypeb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 * @return bool
 */
ae_bool rmatrixgemmf(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param optypea
 * @param b
 * @param ib
 * @param jb
 * @param optypeb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 * @return bool
 */
ae_bool cmatrixgemmf(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     ae_complex alpha,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Complex */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     ae_complex beta,
     /* Complex */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param optypea
 * @param b
 * @param ib
 * @param jb
 * @param optypeb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 */
void cmatrixgemmk(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     ae_complex alpha,
     /* Complex */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Complex */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     ae_complex beta,
     /* Complex */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param optypea
 * @param b
 * @param ib
 * @param jb
 * @param optypeb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 */
void rmatrixgemmk(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     ae_int_t optypea,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     ae_int_t optypeb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param b
 * @param ib
 * @param jb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 */
void rmatrixgemmk44v00(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param b
 * @param ib
 * @param jb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 */
void rmatrixgemmk44v01(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param b
 * @param ib
 * @param jb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 */
void rmatrixgemmk44v10(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
/**
 * @brief
 *
 * @param m
 * @param n
 * @param k
 * @param alpha
 * @param a
 * @param ia
 * @param ja
 * @param b
 * @param ib
 * @param jb
 * @param beta
 * @param c
 * @param ic
 * @param jc
 * @param _state
 */
void rmatrixgemmk44v11(ae_int_t m,
     ae_int_t n,
     ae_int_t k,
     double alpha,
     /* Real    */ ae_matrix* a,
     ae_int_t ia,
     ae_int_t ja,
     /* Real    */ ae_matrix* b,
     ae_int_t ib,
     ae_int_t jb,
     double beta,
     /* Real    */ ae_matrix* c,
     ae_int_t ic,
     ae_int_t jc,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_CREFLECTIONS) || !defined(AE_PARTIAL_BUILD)
void complexgeneratereflection(/* Complex */ ae_vector* x,
     ae_int_t n,
     ae_complex* tau,
     ae_state *_state);
void complexapplyreflectionfromtheleft(/* Complex */ ae_matrix* c,
     ae_complex tau,
     /* Complex */ ae_vector* v,
     ae_int_t m1,
     ae_int_t m2,
     ae_int_t n1,
     ae_int_t n2,
     /* Complex */ ae_vector* work,
     ae_state *_state);
void complexapplyreflectionfromtheright(/* Complex */ ae_matrix* c,
     ae_complex tau,
     /* Complex */ ae_vector* v,
     ae_int_t m1,
     ae_int_t m2,
     ae_int_t n1,
     ae_int_t n2,
     /* Complex */ ae_vector* work,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_ROTATIONS) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 * @param isforward
 * @param m1
 * @param m2
 * @param n1
 * @param n2
 * @param c
 * @param s
 * @param a
 * @param work
 * @param _state
 */
void applyrotationsfromtheleft(ae_bool isforward,
     ae_int_t m1,
     ae_int_t m2,
     ae_int_t n1,
     ae_int_t n2,
     /* Real    */ ae_vector* c,
     /* Real    */ ae_vector* s,
     /* Real    */ ae_matrix* a,
     /* Real    */ ae_vector* work,
     ae_state *_state);
void applyrotationsfromtheright(ae_bool isforward,
     ae_int_t m1,
     ae_int_t m2,
     ae_int_t n1,
     ae_int_t n2,
     /* Real    */ ae_vector* c,
     /* Real    */ ae_vector* s,
     /* Real    */ ae_matrix* a,
     /* Real    */ ae_vector* work,
     ae_state *_state);
void generaterotation(double f,
     double g,
     double* cs,
     double* sn,
     double* r,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_TRLINSOLVE) || !defined(AE_PARTIAL_BUILD)
void rmatrixtrsafesolve(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     double* s,
     ae_bool isupper,
     ae_bool istrans,
     ae_bool isunit,
     ae_state *_state);
void safesolvetriangular(/* Real    */ ae_matrix* a,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     double* s,
     ae_bool isupper,
     ae_bool istrans,
     ae_bool isunit,
     ae_bool normin,
     /* Real    */ ae_vector* cnorm,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_SAFESOLVE) || !defined(AE_PARTIAL_BUILD)
ae_bool rmatrixscaledtrsafesolve(/* Real    */ ae_matrix* a,
     double sa,
     ae_int_t n,
     /* Real    */ ae_vector* x,
     ae_bool isupper,
     ae_int_t trans,
     ae_bool isunit,
     double maxgrowth,
     ae_state *_state);
ae_bool cmatrixscaledtrsafesolve(/* Complex */ ae_matrix* a,
     double sa,
     ae_int_t n,
     /* Complex */ ae_vector* x,
     ae_bool isupper,
     ae_int_t trans,
     ae_bool isunit,
     double maxgrowth,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_HBLAS) || !defined(AE_PARTIAL_BUILD)
void hermitianmatrixvectormultiply(/* Complex */ ae_matrix* a,
     ae_bool isupper,
     ae_int_t i1,
     ae_int_t i2,
     /* Complex */ ae_vector* x,
     ae_complex alpha,
     /* Complex */ ae_vector* y,
     ae_state *_state);
void hermitianrank2update(/* Complex */ ae_matrix* a,
     ae_bool isupper,
     ae_int_t i1,
     ae_int_t i2,
     /* Complex */ ae_vector* x,
     /* Complex */ ae_vector* y,
     /* Complex */ ae_vector* t,
     ae_complex alpha,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_SBLAS) || !defined(AE_PARTIAL_BUILD)
void symmetricmatrixvectormultiply(/* Real    */ ae_matrix* a,
     ae_bool isupper,
     ae_int_t i1,
     ae_int_t i2,
     /* Real    */ ae_vector* x,
     double alpha,
     /* Real    */ ae_vector* y,
     ae_state *_state);
void symmetricrank2update(/* Real    */ ae_matrix* a,
     ae_bool isupper,
     ae_int_t i1,
     ae_int_t i2,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* y,
     /* Real    */ ae_vector* t,
     double alpha,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_BLAS) || !defined(AE_PARTIAL_BUILD)
double vectornorm2(/* Real    */ ae_vector* x,
     ae_int_t i1,
     ae_int_t i2,
     ae_state *_state);
ae_int_t vectoridxabsmax(/* Real    */ ae_vector* x,
     ae_int_t i1,
     ae_int_t i2,
     ae_state *_state);
ae_int_t columnidxabsmax(/* Real    */ ae_matrix* x,
     ae_int_t i1,
     ae_int_t i2,
     ae_int_t j,
     ae_state *_state);
ae_int_t rowidxabsmax(/* Real    */ ae_matrix* x,
     ae_int_t j1,
     ae_int_t j2,
     ae_int_t i,
     ae_state *_state);
double upperhessenberg1norm(/* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t i2,
     ae_int_t j1,
     ae_int_t j2,
     /* Real    */ ae_vector* work,
     ae_state *_state);
void copymatrix(/* Real    */ ae_matrix* a,
     ae_int_t is1,
     ae_int_t is2,
     ae_int_t js1,
     ae_int_t js2,
     /* Real    */ ae_matrix* b,
     ae_int_t id1,
     ae_int_t id2,
     ae_int_t jd1,
     ae_int_t jd2,
     ae_state *_state);
void inplacetranspose(/* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t i2,
     ae_int_t j1,
     ae_int_t j2,
     /* Real    */ ae_vector* work,
     ae_state *_state);
void copyandtranspose(/* Real    */ ae_matrix* a,
     ae_int_t is1,
     ae_int_t is2,
     ae_int_t js1,
     ae_int_t js2,
     /* Real    */ ae_matrix* b,
     ae_int_t id1,
     ae_int_t id2,
     ae_int_t jd1,
     ae_int_t jd2,
     ae_state *_state);
void matrixvectormultiply(/* Real    */ ae_matrix* a,
     ae_int_t i1,
     ae_int_t i2,
     ae_int_t j1,
     ae_int_t j2,
     ae_bool trans,
     /* Real    */ ae_vector* x,
     ae_int_t ix1,
     ae_int_t ix2,
     double alpha,
     /* Real    */ ae_vector* y,
     ae_int_t iy1,
     ae_int_t iy2,
     double beta,
     ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param y
 * @param _state
 * @return double
 */
double pythag2(double x, double y, ae_state *_state);
void matrixmatrixmultiply(/* Real    */ ae_matrix* a,
     ae_int_t ai1,
     ae_int_t ai2,
     ae_int_t aj1,
     ae_int_t aj2,
     ae_bool transa,
     /* Real    */ ae_matrix* b,
     ae_int_t bi1,
     ae_int_t bi2,
     ae_int_t bj1,
     ae_int_t bj2,
     ae_bool transb,
     double alpha,
     /* Real    */ ae_matrix* c,
     ae_int_t ci1,
     ae_int_t ci2,
     ae_int_t cj1,
     ae_int_t cj2,
     double beta,
     /* Real    */ ae_vector* work,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_LINMIN) || !defined(AE_PARTIAL_BUILD)
void linminnormalized(/* Real    */ ae_vector* d,
     double* stp,
     ae_int_t n,
     ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param x
 * @param f
 * @param g
 * @param s
 * @param stp
 * @param stpmax
 * @param gtol
 * @param info
 * @param nfev
 * @param wa
 * @param state
 * @param stage
 * @param _state
 */
void mcsrch(ae_int_t n,
     /* Real    */ ae_vector* x,
     double* f,
     /* Real    */ ae_vector* g,
     /* Real    */ ae_vector* s,
     double* stp,
     double stpmax,
     double gtol,
     ae_int_t* info,
     ae_int_t* nfev,
     /* Real    */ ae_vector* wa,
     linminstate* state,
     ae_int_t* stage,
     ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param x
 * @param f
 * @param s
 * @param stp
 * @param stpmax
 * @param fmax
 * @param state
 * @param _state
 */
void armijocreate(ae_int_t n,
     /* Real    */ ae_vector* x,
     double f,
     /* Real    */ ae_vector* s,
     double stp,
     double stpmax,
     ae_int_t fmax,
     armijostate* state,
     ae_state *_state);
/**
 * @brief
 *
 * @param state
 * @param _state
 * @return bool
 */
ae_bool armijoiteration(armijostate* state, ae_state *_state);
/**
 * @brief
 *
 * @param state
 * @param info
 * @param stp
 * @param f
 * @param _state
 */
void armijoresults(armijostate* state,
     ae_int_t* info,
     double* stp,
     double* f,
     ae_state *_state);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _linminstate_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _linminstate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _linminstate_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _linminstate_destroy(void* _p);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _armijostate_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _armijostate_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _armijostate_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _armijostate_destroy(void* _p);
#endif
#if defined(AE_COMPILE_XBLAS) || !defined(AE_PARTIAL_BUILD)
void xdot(/* Real    */ ae_vector* a,
     /* Real    */ ae_vector* b,
     ae_int_t n,
     /* Real    */ ae_vector* temp,
     double* r,
     double* rerr,
     ae_state *_state);
void xcdot(/* Complex */ ae_vector* a,
     /* Complex */ ae_vector* b,
     ae_int_t n,
     /* Real    */ ae_vector* temp,
     ae_complex* r,
     double* rerr,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_BASICSTATOPS) || !defined(AE_PARTIAL_BUILD)
void rankx(/* Real    */ ae_vector* x,
     ae_int_t n,
     ae_bool iscentered,
     apbuffers* buf,
     ae_state *_state);
void rankxuntied(/* Real    */ ae_vector* x,
     ae_int_t n,
     apbuffers* buf,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_HPCCORES) || !defined(AE_PARTIAL_BUILD)
void hpcpreparechunkedgradient(/* Real    */ ae_vector* weights,
     ae_int_t wcount,
     ae_int_t ntotal,
     ae_int_t nin,
     ae_int_t nout,
     mlpbuffers* buf,
     ae_state *_state);
/**
 * @brief
 *
 * @param buf
 * @param grad
 * @param _state
 */
void hpcfinalizechunkedgradient(mlpbuffers* buf,
     /* Real    */ ae_vector* grad,
     ae_state *_state);
ae_bool hpcchunkedgradient(/* Real    */ ae_vector* weights,
     /* Integer */ ae_vector* structinfo,
     /* Real    */ ae_vector* columnmeans,
     /* Real    */ ae_vector* columnsigmas,
     /* Real    */ ae_matrix* xy,
     ae_int_t cstart,
     ae_int_t csize,
     /* Real    */ ae_vector* batch4buf,
     /* Real    */ ae_vector* hpcbuf,
     double* e,
     ae_bool naturalerrorfunc,
     ae_state *_state);
ae_bool hpcchunkedprocess(/* Real    */ ae_vector* weights,
     /* Integer */ ae_vector* structinfo,
     /* Real    */ ae_vector* columnmeans,
     /* Real    */ ae_vector* columnsigmas,
     /* Real    */ ae_matrix* xy,
     ae_int_t cstart,
     ae_int_t csize,
     /* Real    */ ae_vector* batch4buf,
     /* Real    */ ae_vector* hpcbuf,
     ae_state *_state);
void _mlpbuffers_init(void* _p, ae_state *_state, ae_bool make_automatic);
void _mlpbuffers_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _mlpbuffers_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _mlpbuffers_destroy(void* _p);
#endif
#if defined(AE_COMPILE_NTHEORY) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 * @param n
 * @param proot
 * @param invproot
 * @param _state
 */
void findprimitiverootandinverse(ae_int_t n,
     ae_int_t* proot,
     ae_int_t* invproot,
     ae_state *_state);
#endif
#if defined(AE_COMPILE_FTBASE) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 * @param n
 * @param k
 * @param plan
 * @param _state
 */
void ftcomplexfftplan(ae_int_t n,
     ae_int_t k,
     fasttransformplan* plan,
     ae_state *_state);
/**
 * @brief
 *
 * @param plan
 * @param a
 * @param offsa
 * @param repcnt
 * @param _state
 */
void ftapplyplan(fasttransformplan* plan,
     /* Real    */ ae_vector* a,
     ae_int_t offsa,
     ae_int_t repcnt,
     ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param tasktype
 * @param n1
 * @param n2
 * @param _state
 */
void ftbasefactorize(ae_int_t n,
     ae_int_t tasktype,
     ae_int_t* n1,
     ae_int_t* n2,
     ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param _state
 * @return bool
 */
ae_bool ftbaseissmooth(ae_int_t n, ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param _state
 * @return ae_int_t
 */
ae_int_t ftbasefindsmooth(ae_int_t n, ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param _state
 * @return ae_int_t
 */
ae_int_t ftbasefindsmootheven(ae_int_t n, ae_state *_state);
/**
 * @brief
 *
 * @param n
 * @param _state
 * @return double
 */
double ftbasegetflopestimate(ae_int_t n, ae_state *_state);
/**
 * @brief
 *
 * @param _p
 * @param _state
 * @param make_automatic
 */
void _fasttransformplan_init(void* _p, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _dst
 * @param _src
 * @param _state
 * @param make_automatic
 */
void _fasttransformplan_init_copy(void* _dst, void* _src, ae_state *_state, ae_bool make_automatic);
/**
 * @brief
 *
 * @param _p
 */
void _fasttransformplan_clear(void* _p);
/**
 * @brief
 *
 * @param _p
 */
void _fasttransformplan_destroy(void* _p);
#endif
#if defined(AE_COMPILE_NEARUNITYUNIT) || !defined(AE_PARTIAL_BUILD)
/**
 * @brief
 *
 * @param x
 * @param _state
 * @return double
 */
double nulog1p(double x, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param _state
 * @return double
 */
double nuexpm1(double x, ae_state *_state);
/**
 * @brief
 *
 * @param x
 * @param _state
 * @return double
 */
double nucosm1(double x, ae_state *_state);
#endif
#if defined(AE_COMPILE_ALGLIBBASICS) || !defined(AE_PARTIAL_BUILD)
#endif

}
#endif

