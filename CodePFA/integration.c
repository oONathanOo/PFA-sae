
#define INTEGRATION_C
#include <string.h>
#include "integration.h"


double left(double (*f)(double), double a, double b)
{
  return (b-a)*f(a);
}

double right(double (*f)(double), double a, double b)
{
  return (b-a)*f(b);
}

double middle(double (*f)(double), double a, double b)
{
  return (b-a)*f((a+b)/2.0);
}

double trapezes(double (*f)(double), double a, double b)
{
  return (b-a)*(0.5*f(a)+0.5*f(b));
}

double simpson(double (*f)(double), double a, double b)
{
  return (b-a)*((1.0/6.0)*f(a)+(2.0/3.0)*f((a+b)/2.0)+(1.0/6.0)*f(b));
}
double gauss2(double (*f)(double), double a, double b)
{
  return (1.0/2.0)*f((1.0 - 1.0/sqrt(3.0))/2.0) + (1.0/2.0)*f((1.0+(1.0)/sqrt(3.0))/2.0);
}
double gauss3(double (*f)(double), double a, double b)
{
  return (5.0/18.0)*f((1.0/2.0)*(1.0 - sqrt(3.0/5.0))) + (4.0/9.0)*f(1.0/2.0) +(5.0/18.0)*f((1.0/2.0)*(1.0 + sqrt(3.0/5.0)));
}

bool setQuadFormula(QuadFormula* qf, char *name)
{

  if (!qf || !name) return false;

  strncpy(qf->name, name, sizeof(qf->name) - 1);
  qf->name[sizeof(qf->name) - 1] = '\0';

  if (strcmp(name, "left") == 0)
  {
    (*qf).formula = left;
  }
  else if (strcmp(name, "right") == 0)
  {
    (*qf).formula = right;
  }
  else if (strcmp(name, "middle") == 0)
  {
    (*qf).formula = middle;
  }
  else if (strcmp(name, "trapezes") == 0)
  {
    (*qf).formula = trapezes;
  }
  else if (strcmp(name, "simpson") == 0)
  {
    (*qf).formula = simpson;
  }
  else if (strcmp(name, "gauss2") == 0)
  {
    (*qf).formula = gauss2;
  }
  else if (strcmp(name, "gauss3") == 0)
  {
    (*qf).formula = gauss3;
  }
  else
  {

    return false;
  }

  return true;
}

/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}


/* Approximate the integral of function f from a to b.
   - f is a pointer to a function pointer
   - a and b are the integration bounds
   - Interval [a,b] is split in N subdivisions [ai,bi]
   - Integral of f on each subdivision [ai,bi] is approximated by the quadrature formula qf.
*/
double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
  double start = a;
  double length = (b-a)/(double)N;
  double end = a + length;
  double res = 0.0;

  for (int i = 0; i < N; i++)
  {

    res += (*qf).formula(f, start, end);

    start = end;
    end += length;
  }

  return res;
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  int N = (fabs((b-a))/dx)+0.5;
  if (N < 1)
  {
    N = 1;
  }
  return integrate(f,a,b,N,qf);
}


