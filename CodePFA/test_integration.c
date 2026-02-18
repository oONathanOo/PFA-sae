/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "integration.h"

/* Code here everything you need to test the integration methods and show your numericzal results */

int main()
{
  double (*f)(double) =;
  double a =;
  double b =;
  int N =;
  double dx =;
  QuadFormula* qf;
  printf("The integral of the function f(x) in between %d and %d using %i subdivisions is:\n", a , b, N);
  setQuadFormula(qf,"left")
  printf("Left : %d\n",double integrate(f, a, b, N, qf));
  setQuadFormula(qf,"right")
  printf("Right : %d\n",double integrate(f, a, b, N, qf));
  setQuadFormula(qf,"middle")
  printf("Middle : %d\n",double integrate(f, a, b, N, qf));
  setQuadFormula(qf,"trapezes")
  printf("Trapezes : %d\n",double integrate(f, a, b, N, qf));
  setQuadFormula(qf,"simpson")
  printf("Simpson : %d\n",double integrate(f, a, b, N, qf));
  setQuadFormula(qf,"gauss2")
  printf("Gauss2 : %d\n",double integrate(f, a, b, N, qf));
  setQuadFormula(qf,"gauss3")
  printf("Gauss3 : %d\n",double integrate(f, a, b, N, qf));

  printf("The integral of the function f(x) in between %d and %d using subdivisions of %d length is:\n", a , b, dx);
  setQuadFormula(qf,"left")
  printf("Left : %d\n",double integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"right")
  printf("Right : %d\n",double integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"middle")
  printf("Middle : %d\n",double integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"trapezes")
  printf("Trapezes : %d\n",double integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"simpson")
  printf("Simpson : %d\n",double integrate_dx(f, a, b,dx, qf));
  setQuadFormula(qf,"gauss2")
  printf("Gauss2 : %d\n",double integrate_dx(f, a, b, dx, qf));
  setQuadFormula(qf,"gauss3")
  printf("Gauss3 : %d\n",double integrate_dx(f, a, b, dx, qf));
  return 0;
}
