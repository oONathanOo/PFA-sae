

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
  if (dt == 0 || (strcmp(quadrature, "left") != 0) && (strcmp(quadrature, "right") != 0) && (strcmp(quadrature, "middle") != 0) && (strcmp(quadrature, "trapezes") != 0) && (strcmp(quadrature, "simpson") != 0) && (strcmp(quadrature, "gauss2") != 0) && (strcmp(quadrature, "gauss3") != 0) || dt < 0.0)
  {
    return false;
  }
  setQuadFormula(&pfaQF, quadrature);
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
  if (x >= 0)
  {
    return 0.5 +integrate_dx(phi, 0, x, pfa_dt, &pfaQF);
  }
  else
  {
    return 0.5 -integrate_dx(phi, x, 0, pfa_dt, &pfaQF);
  }
}

/* =====================================
   Finance function: price of an option 
*/
double z0(Option* option)
{
  return (log(option->K/option->S0)-((option->mu-((option->sig*option->sig)/2))*option->T))/(option->sig*sqrt(option->T));
}
double optionPrice(Option* option)
{
  if (option->type == PUT)
  {
    return option->K*PHI(z0(option))-(option->S0*exp(option->mu*option->T)*PHI(z0(option)-option->sig*sqrt(option->T)));
  }
  else if (option->type == CALL)
  {
    return (option->S0*exp(option->mu*option->T)*PHI(option->sig*sqrt(option->T)-z0(option)))-option->K*PHI(-z0(option));
  }
  else
  {
    return 0.0;
  }
}



/* ===============================================*/
/* Insurance functions */

/* Probability density function (PDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientPDF_X(InsuredClient* client, double x)
{
  if (x <= 0)
  {
    return 0;
  }
  return (1.0/(client->s*x))*phi((log(x)-client->m)/client->s);
}

/* Cumulative distribution function (CDF) of variable X.
   X is the reimbursement in case of a claim from the client.
*/
double clientCDF_X(InsuredClient* client, double x)
{
  if (x <= 0)
  {
    return 0;
  }
  return PHI((log(x)-client->m)/client->s);
}


static InsuredClient* localClient;
static double localX;


/* This function assumes that static variables localClient and localX have been set.
   It can be an argument of integrate_dx (since it has the good signature)
*/
static double localProductPDF(double t)
{
  if (t <=0.0 || t>=localX)
  {
    return 0.0;
  }
  return clientPDF_X(localClient, localX - t) * clientPDF_X(localClient, t);
}

/* Density of X1+X2

   This function assumes that static variable localClient has been set.
   It is called by clientPDF_X1X2
   It can also be an argument of integrate_dx (since it has the good signature)
*/
static double localPDF_X1X2(double x)
{
  if (x <= 0.0)
  {
    return 0.0;
  }
  localX = x;
  return integrate_dx(localProductPDF, 0.0, x, pfa_dt, &pfaQF);
}


/* Probability density function (PDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
double clientPDF_X1X2(InsuredClient* client, double x)
{
  if ( x<=0.0 ) return 0.0;

  localClient = client;
  return localPDF_X1X2(x);
}


/* Cumulative distribution function (CDF) of variable X1+X2.
   X1 and X2 are the reimbursements of the two claims from the client (assuming there are 
   two claims).
*/
double clientCDF_X1X2(InsuredClient* client, double x)
{
  if (x<= 0.0)
  {
    return 0.0;
  }
  localClient = client;
  return integrate_dx(localPDF_X1X2, 0, x, pfa_dt, &pfaQF);
}



/* Cumulative distribution function (CDF) of variable S.
   Variable S is the sum of the reimbursements that the insurance company will pay to client.
*/
double clientCDF_S(InsuredClient* client, double x)
{
  if (x < 0.0)
  {
    return 0.0;
  }
  double p0 = (*client).p[0];
  double p1 = (*client).p[1];
  double p2 = (*client).p[2];
  if (x == 0.0)
  {
    return p0;
  }
  return p0 + p1*(clientCDF_X(client, x))+(p2*clientCDF_X1X2(client, x));

}




