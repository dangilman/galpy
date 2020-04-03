#include <math.h>
// Constants not defined in MSVC's math.h
#ifndef M_SQRT1_2
#define M_SQRT1_2 0.70710678118654746172
#endif
#ifndef M_2_SQRTPI
#define M_2_SQRTPI 1.12837916709551255856
#endif
#include <gsl/gsl_spline.h>
#include <galpy_potentials.h>
// ChandrasekharDynamicalFrictionForce: 8 arguments: amp,ms,rhm,gamma^2,
// lnLambda, minr^2, ro, rf
double ChandrasekharDynamicalFrictionForceRforce(double R,double z, double phi,
						 double t,
						 struct potentialArg * potentialArgs,
						 double vR,double vT,
						 double vz){
  double sr,X,Xfactor,d_ind;
  double * args= potentialArgs->args;
  //Get args
  double amp= *args;
  double ms= *(args+1);
  double rhm= *(args+2);
  double gamma2= *(args+3);
  double lnLambda= *(args+4);
  double ro= *(args+6);
  double rf= *(args+7);
  double GMvs;
  double r2=  R * R + z * z;
  if ( r2 < *(args+5) )  // r < minr
    return 0.;
  double r= sqrt( r2 );
  double v2=  vR * vR + vT * vT + vz * vz;
  double v= sqrt( v2 );
  // Constant or variable Lambda
  if ( lnLambda < 0 ) {
    GMvs= ms/v/v;
    if ( GMvs < rhm )
      lnLambda= 0.5 * log ( 1. + r2 / gamma2 / rhm / rhm );
    else
      lnLambda= 0.5 * log ( 1. + r2 / gamma2 / GMvs / GMvs );
  }
  d_ind= (r-ro)/(rf-ro);
  d_ind= d_ind <  0 ? 0. : ( d_ind > 1 ? 1. : d_ind);
  sr= gsl_spline_eval(*potentialArgs->spline1d,d_ind,*potentialArgs->acc1d);
  X= M_SQRT1_2 * v / sr;
  Xfactor= erf ( X ) - M_2_SQRTPI * X * exp ( - X * X );
  return - amp * Xfactor * lnLambda * vR / v2 / v \
    * calcDensity(R,z,phi,t,potentialArgs->nwrapped,
		  potentialArgs->wrappedPotentialArg);
}
double ChandrasekharDynamicalFrictionForcezforce(double R,double z, double phi,
						 double t,
						 struct potentialArg * potentialArgs,
						 double vR,double vT,
						 double vz){
  double sr,X,Xfactor,d_ind;
  double * args= potentialArgs->args;
  //Get args
  double amp= *args;
  double ms= *(args+1);
  double rhm= *(args+2);
  double gamma2= *(args+3);
  double lnLambda= *(args+4);
  double ro= *(args+6);
  double rf= *(args+7);
  double GMvs;
  double r2=  R * R + z * z;
  if ( r2 < *(args+5) )  // r < minr
    return 0.;
  double r= sqrt( r2 );
  double v2=  vR * vR + vT * vT + vz * vz;
  double v= sqrt( v2 );
  // Constant or variable Lambda
  if ( lnLambda < 0 ) {
    GMvs= ms/v/v;
    if ( GMvs < rhm )
      lnLambda= 0.5 * log ( 1. + r2 / gamma2 / rhm / rhm );
    else
      lnLambda= 0.5 * log ( 1. + r2 / gamma2 / GMvs / GMvs );
  }
  d_ind= (r-ro)/(rf-ro);
  d_ind= d_ind <  0 ? 0. : ( d_ind > 1 ? 1. : d_ind);
  sr= gsl_spline_eval(*potentialArgs->spline1d,d_ind,*potentialArgs->acc1d);
  X= M_SQRT1_2 * v / sr;
  Xfactor= erf ( X ) - M_2_SQRTPI * X * exp ( - X * X );
  return - amp * Xfactor * lnLambda * vz / v2 / v \
    * calcDensity(R,z,phi,t,potentialArgs->nwrapped,
		  potentialArgs->wrappedPotentialArg);
}
double ChandrasekharDynamicalFrictionForcephiforce(double R,double z,
						   double phi,double t,
						   struct potentialArg * potentialArgs,
						   double vR,double vT,
						   double vz){
  double sr,X,Xfactor,d_ind;
  double * args= potentialArgs->args;
  //Get args
  double amp= *args;
  double ms= *(args+1);
  double rhm= *(args+2);
  double gamma2= *(args+3);
  double lnLambda= *(args+4);
  double ro= *(args+6);
  double rf= *(args+7);
  double GMvs;
  double r2=  R * R + z * z;
  if ( r2 < *(args+5) )  // r < minr
    return 0.;
  double r= sqrt( r2 );
  double v2=  vR * vR + vT * vT + vz * vz;
  double v= sqrt( v2 );
  // Constant or variable Lambda
  if ( lnLambda < 0 ) {
    GMvs= ms/v/v;
    if ( GMvs < rhm )
      lnLambda= 0.5 * log ( 1. + r2 / gamma2 / rhm / rhm );
    else
      lnLambda= 0.5 * log ( 1. + r2 / gamma2 / GMvs / GMvs );
  }
  d_ind= (r-ro)/(rf-ro);
  d_ind= d_ind <  0 ? 0. : ( d_ind > 1 ? 1. : d_ind);
  sr= gsl_spline_eval(*potentialArgs->spline1d,d_ind,*potentialArgs->acc1d);
  X= M_SQRT1_2 * v / sr;
  Xfactor= erf ( X ) - M_2_SQRTPI * X * exp ( - X * X );
  return - amp * Xfactor * lnLambda * vT * R / v2 / v \
    * calcDensity(R,z,phi,t,potentialArgs->nwrapped,
		  potentialArgs->wrappedPotentialArg);
}

