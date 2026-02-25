

// #define GRAPHIC

#define PFA_C

#include "pfa.h"
#include "integration.h"

QuadFormula pfaQF;
double pfa_dt;


/* Initialize the integration variables.
   Arguments :
   - quadrature : name of the quadrature formula that will be used. It can be "left", "right", 
     "middle", "trapezes", "simpson", "gauss2" or "gauss3".
   - dt : a positive value, which will be used to decide the number of subdivisions of an 
          interval [a,b], when computing the integration.
          The number of subdivisions will be N such that (b-a)/N ~ dt
*/
bool init_integration(char* quadrature, double dt)
{ 
  if ((strcmp(name, "left") != 0) && (strcmp(name, "right") != 0) && (strcmp(name, "middle") != 0) && (strcmp(name, "trapezes") != 0) && (strcmp(name, "simpson") != 0) && (strcmp(name, "gauss2") != 0) && (strcmp(name, "gauss3") != 0) || dt < 0.0)
  {
    return false
  }
  setQuadFormula(pfaQF, quadrature);
  pfa_dt = dt;
  return true;
}



/* Density of the normal distribution */
double phi(double x)
{
  return 0.398942280401433 * exp( -x*x/2 );
}


/* Cumulative distribution function of the normal distribution */
double PHI(double x)
{
  return 0.5*integrate_dx(phi(x), 0, x, pfa_dt, (*pfaQF).formula);
}

/* =====================================
   Finance function: price of an option 
*/
double z0(Option* option)
{
  return (ln(option.K/option.S0)-((option.mu-((option.sig*option.sig)/2))*option.T))/(option.sig*sqrt(option.T));
}
double optionPrice(Option* option)
{
  if (option.type == PUT)
  {
    return option.K*PHI(z0(option))-(option.S0*exp(option.mu*option.T)*PHI(z0(option)-option.sig*sqrt(T)));
  }
  else if (option.type == CALL)
  {
    return (option.S0*exp(option.mu*option.T)*PHI(option.sig*sqrt(T)-z0(option)))-option.K*PHI(-z0(option));
  }
  else
  {
    return 0.0
  }
}



/* ===============================================*/
/* Insurance functions */

/* Probability density function (PDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientPDF_X(InsuredClient* client, double x)
{
  return 0.0;
}


/* Cumulative distribution function (CDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientCDF_X(InsuredClient* client, double x)
{
  return 0.0;
}


/* Probability density function (PDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
double clientPDF_X1X2(InsuredClient* client, double x)
{
  return 0.0;
}


/* Cumulative distribution function (CDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
double clientCDF_X1X2(InsuredClient* client, double x)
{
  return 0.0;
}



/* Cumulative distribution function (CDF) of variable S.
   Variable S is the sum of the reimbursements that the insurance company will pay to client.
*/
double clientCDF_S(InsuredClient* client, double x)
{
  return 0.0;
}




