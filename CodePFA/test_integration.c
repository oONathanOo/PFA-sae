/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods and show your numerical results */

double function(double x)
{
  return 10*(x*x) - 5*x + 7;
}


int main()
{
  double (*f)(double) = function;
  double a = 8.4;
  double b = 42.7;
  int N = 10;
  double dx = 3.8;
  QuadFormula* qf;
  printf("The integral of the function f(x) in between %f and %f using %i subdivisions is:\n", a , b, N);
  setQuadFormula(qf,"left");
  printf("Left : %f\n", integrate(f, a, b, N, qf));
  setQuadFormula(qf,"right");
  printf("Right : %f\n", integrate(f, a, b, N, qf));
  setQuadFormula(qf,"middle");
  printf("Middle : %f\n", integrate(f, a, b, N, qf));
  setQuadFormula(qf,"trapezes");
  printf("Trapezes : %f\n", integrate(f, a, b, N, qf));
  setQuadFormula(qf,"simpson");
  printf("Simpson : %f\n", integrate(f, a, b, N, qf));
  setQuadFormula(qf,"gauss2");
  printf("Gauss2 : %f\n", integrate(f, a, b, N, qf));
  setQuadFormula(qf,"gauss3");
  printf("Gauss3 : %f\n", integrate(f, a, b, N, qf));

  printf("The integral of the function f(x) in between %f and %f using subdivisions of %f length is:\n", a , b, dx);
  setQuadFormula(qf,"left");
  printf("Left : %f\n", integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"right");
  printf("Right : %f\n", integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"middle");
  printf("Middle : %f\n", integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"trapezes");
  printf("Trapezes : %f\n", integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"simpson");
  printf("Simpson : %f\n", integrate_dx(f, a, b,dx, qf));
  setQuadFormula(qf,"gauss2");
  printf("Gauss2 : %f\n", integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"gauss3");
  printf("Gauss3 : %f\n", integrate_dx(f, a, b, dx, qf));
  return 0;
}
