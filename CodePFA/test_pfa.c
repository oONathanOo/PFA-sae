/******************************************************/
/* Program to run and test the integration functions. */
/* Creation date: 31 July, 2025                       */
/******************************************************/

#include "pfa.h"

/* Code here anything you want to test your pfa functions and to show your numerical results */
int main()
{


  Option *option = malloc(sizeof(Option));
  InsuredClient *client = malloc(sizeof(InsuredClient));
  option->type = 0;
  option -> S0 = 100;
  option ->T = 2;
  option -> mu = 0.05;
  option -> K = 115;
  option -> sig = 0.02;
  client->m = 1;
  client->s = 1;
  client->p = malloc(sizeof(double)*3);
  client->p[0]=0.9;
  client->p[1]=0.05;
  client->p[2]=0.05;
  
  init_integration("gauss3", 0.1);
  printf("%f\n", PHI(1.0));
  double a = optionPrice(option);
  printf("%f\n", clientCDF_S(client, 1));
  printf("%lf\n",a);
  free(client->p);
  free(client);
  free (option);
  return 0;
}
