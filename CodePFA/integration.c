
#define INTEGRATION_C

#include "integration.h"

(*qf).name = right
(*qf).formula = 

double left(double (*f)(double), double b, double a)
{
  return (b-a)*f(a);
}

double right(double (*f)(double), double b, double a)
{
  return (b-a)*f(b);
}

double middle(double (*f)(double), double b, double a)
{
  return (b-a)*f((a+b)/2);
}

double trapezes(double (*f)(double), double b, double a)
{
  return (b-a)*(0.5*f(a)+0.5*f(b));
}

double simpson(double (*f)(double), double b, double a)
{
  return (b-a)*((1/6)*f(a)+(2/3)*f((a+b)/2)+(1/6)*f(b));
}
/*
double gauss2(double (*f)(double), double b, double a)
{
  return;
}
*/

bool setQuadFormula(QuadFormula* qf, char* name)
{
  (*qf).name = name;
  if (name == "left")
  {
    (*qf).formula = double (*left)(double, double, double);
  }
  else if (name == "right")
  {
    (*qf).formula = double (*right)(double, double, double);
  }
  else if (name == "middle")
  {
    (*qf).formula = double (*middle)(double, double, double);
  }
  else if (name == "trapezes")
  {
    (*qf).formula = double (trapezes)(double, double, double);
  }
  else if (name == "simpson")
  {

  }
  else if (name == "gauss2")
  {
    
  }
  else if (name == "gauss3")
  {
    
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
  double length = (a+b)/N;
  double end = a + length
  double res = 0
  while (end <= b)
  {
    //res = res + callfunc with ai = start and bi = end//
    start = end
    end += length;
  }
  return res;
}

double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
  int N = (b-a)/dx
  double temp = res;
  if (((b-a)/dx) > temp+0.5)
  {
    res += 1;
  }
  return integrate(f,a,b,N,qf);
}


