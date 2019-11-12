#include <stdio.h>
#include <math.h>

/* ------------------------------------------------------------------------- */
/* These are C lang routines which can be used to evaluate the probability   */
/* density functions (pdf's), cumulative distribution functions (cdf's), and */
/* inverse distribution functions (idf's) for a variety of discrete and      */
/* continuous random variables.                                              */
/*                                                                           */
/* The following notational conventions are used -                           */
/*                 x : possible value of the random variable                 */
/*                 u : real variable (probability) between 0 and 1           */
/*  a, b, n, p, m, s : distribution specific parameters                      */
/*                                                                           */
/* There are pdf's, cdf's and idf's for 6 discrete random variables:         */
/*                                                                           */
/*      Random Variable    Range (x)  Mean         Variance                  */
/*                                                                           */
/*      Bernoulli(p)       0..1       p            p*(1-p)                   */
/*      Binomial(n, p)     0..n       n*p          n*p*(1-p)                 */
/*      Equilikely(a, b)   a..b       (a+b)/2      ((b-a+1)*(b-a+1)-1)/12    */
/*      Geometric(p)       0...       p/(1-p)      p/((1-p)*(1-p))           */
/*      Pascal(n, p)       0...       n*p/(1-p)    n*p/((1-p)*(1-p))         */
/*      Poisson(m)         0...       m            m                         */
/*                                                                           */
/* and for 8 continuous random variables:                                    */
/*                                                                           */
/*      Random Variable    Range (x)  Mean         Variance                  */
/*                                                                           */
/*      Uniform(a, b)      a < x < b  (a+b)/2      (b-a)*(b-a)/12            */
/*      Exponential(m)     x > 0      m            m*m                       */
/*      Erlang(n, b)       x > 0      n*b          n*b*b                     */
/*      Normal             all x      0            1                         */
/*      Gauss(m, s)        all x      m            s*s                       */
/*      Lognormal(a, b)    x > 0         see below                           */
/*      Chisquare(n)       x > 0      n            2*n                       */
/*      Student(n)         all x      0  (n > 1)   n/(n-2)   (n > 2)         */
/*                                                                           */
/* For the Lognormal(a, b), the mean and variance are:                       */
/*                                                                           */
/*                        mean = Exp(a + 0.5*b*b)                            */
/*                    variance = (Exp(b*b) - 1)*Exp(2*a + b*b)               */
/*                                                                           */
/* Name            : DFU.C                                                   */
/* Purpose         : Distribution/Density Function Routines                  */
/* Author          : Steve Park                                              */
/* Language        : Turbo Pascal, 5.0                                       */
/* Latest Revision : 09-19-90                                                */
/* Reference       : Lecture Notes on Simulation, by Steve Park              */
/* Converted to C  : David W. Geyer  09-02-91                                */
/* ------------------------------------------------------------------------- */
/* NOTE - must link with routine sfu.obj */

/* include files */
#include <math.h>                          /* for log(), exp(), abs() */
//#define ABS(a) ( (a > 0) ? a : -(a) )

/* ========================================================================= */
/*                         double Bernoulli_pdf()                            */
/*                         double Bernoulli_cdf()                            */
/*                          long  Bernoulli_idf()                            */
/*                                                                           */
/* NOTE: use 0 < p < 1, 0 <= x <= 1 and 0 < u < 1                            */
/* ========================================================================= */
double Bernoulli_pdf(p, x)
double p;
long x;
{
  if (x == 0)
    return((double)1.0 - p);
  else
    return(p);
}  /* Bernoulli_pdf */

double Bernoulli_cdf(p, x)
double p;
long x;
{
  if (x == 0)
    return((double)1.0 - p);
  else
    return((double)1.0);
}  /* Bernoulli_cdf */

long Bernoulli_idf(p, u)
double p, u;
{
  if (u < ((double)1.0 - p))
    return((double)0.0);
  else
    return((double)1.0);
}  /* Bernoulli_idf */

/* ========================================================================= */
/*                        double Equilikely_pdf()                            */
/*                        double Equilikely_cdf()                            */
/*                         long  Equilikely_idf()                            */
/*                                                                           */
/* NOTE: use a <= x <= b and 0 < u < 1                                       */
/* ========================================================================= */
double Equilikely_pdf(a, b, x)
long a, b, x;
{
  return( (double)1.0 / ((double)b - (double)a + (double)1.0) );
}  /* Equilikely_pdf */

double Equilikely_cdf(a, b, x)
long a; 
long b;
long x;
{
  return( ((double)x - (double)a + (double)1.0) /
          ((double)b - (double)a + (double)1.0)  );
}  /* Equilikely_cdf */

long Equilikely_idf(a, b, u)
long   a, b;
double u;
{
  return(a + (long)(u * (b - a + 1)) );
}  /* Equilikely_idf */

/* ========================================================================= */
/*                          double Binomial_pdf()                            */
/*                          double Binomial_cdf()                            */
/*                           long  Binomial_idf()                            */
/*                                                                           */
/* NOTE: use 0 <= x <= n, 0 < p < 1 and 0 < u < 1                            */
/* ========================================================================= */
double Binomial_pdf(n, p, x)
long n; 
double p; 
long x;
{ double s, t, Ln_Choose();

  s = Ln_Choose(n, x);                   /* break this calculation        */
  t = x * log(p) + (n - x) * log(1 - p); /* into two parts                */
  return(exp(s + t));                    /* to avoid 80x87 stack overflow */
}  /* Binomial_pdf */

double Binomial_cdf(n, p, x)
long n; 
double p; 
long x;
{ double Incomplete_Beta();

  if (x < n)
    return((double)1.0 - Incomplete_Beta((double)(x+1), (double)(n-x), p));
  else
    return((double)1.0);
}  /* Binomial_cdf */

long Binomial_idf(n, p, u)
long n; 
double p; 
double u;
{ long  x;
  double Binomial_cdf();

  x = (long)(n * p);                         /* start searching at the mean */
  if (Binomial_cdf(n, p, x) <= u)
    while (Binomial_cdf(n, p, x) <= u)  {
      x++;
    }
  else if (Binomial_cdf(n, p, 0) <= u)
    while (Binomial_cdf(n, p, x - 1) > u)  {
      x--;
    }
  else
    x = 0;
  return(x);
}  /* Binomial_idf */

/* ========================================================================= */
/*                         double Geometric_pdf()                            */
/*                         double Geometric_cdf()                            */
/*                          long  Geometric_idf()                            */
/*                                                                           */
/* NOTE: use 0 < p < 1, x >= 0 and 0 < u < 1                                 */
/* ========================================================================= */
double Geometric_pdf(p, x)
double p; 
long x;
{
  return( (1.0 - p) * exp(x * log(p)) );
}  /* Geometric_pdf */

double Geometric_cdf(p, x)
double p; 
long x;
{
  return( 1.0 - exp((x + 1) * log(p)) );
}  /* Geometric_cdf */

long Geometric_idf(p, u)
double p;
double u;
{
  return( (long)(log(1.0 - u) / log(p)) );
}  /* Geometric_idf */

/* ========================================================================= */
/*                            double Pascal_pdf()                            */
/*                            double Pascal_cdf()                            */
/*                             long  Pascal_idf()                            */
/*                                                                           */
/* NOTE: use n >= 1, 0 < p < 1, x >= 0 and 0 < u < 1                         */
/* ========================================================================= */
double Pascal_pdf(n, p, x)
long n; 
double p; 
long x;
{ double  s, t, Ln_Choose();

  s = Ln_Choose(n + x - 1, x);            /* break this calculation        */
  t = x * log(p) + n * log(1.0 - p);      /* into two parts                */
  return(exp(s + t));                     /* to avoid 80x87 stack overflow */
}  /* Pascal_pdf */

double Pascal_cdf(n, p, x)
long n; 
double p; 
long x;
{ double  Incomplete_Beta();

  return(1.0 - Incomplete_Beta(x + 1, n, p));
}  /* Pascal_cdf */

long Pascal_idf(n, p, u)
long n;
double p;
double u;
{ long  x;

  x = (long)(n * p / (1.0 - p));            /* start searching at the mean */
  if (Pascal_cdf(n, p, x) <= u)
    while (Pascal_cdf(n, p, x) <= u)  {
      x++;
    }
  else if (Pascal_cdf(n, p, 0) <= u)
    while (Pascal_cdf(n, p, x - 1) > u)  {
      x--;
    }
  else
    x = 0;
  return(x);
}  /* Pascal_idf */

/* ========================================================================= */
/*                          double Poisson_pdf()                             */
/*                          double Poisson_cdf()                             */
/*                           long  Poisson_idf()                             */
/*                                                                           */
/* NOTE: use m > 0, x >= 0 and 0 < u < 1                                     */
/* ========================================================================= */
double Poisson_pdf(m, x)
double m;
long x;
{ double t, Ln_Factorial();

  t = - m + x * log(m) - Ln_Factorial(x);
  return(exp(t));
}  /* Poisson_pdf */

double Poisson_cdf(m, x)
double m;
long x;
{ double Incomplete_Gamma();

  return((double)1.0 - Incomplete_Gamma((double)x + 1.0, m));
}  /* Poisson_cdf */

long Poisson_idf(m, u)
double m;
double u;
{ long x;
  double Poisson_cdf();

  x = (long)m;                            /* start searching at the mean */
  if (Poisson_cdf(m, x) <= u)
    while (Poisson_cdf(m, x) <= u)  {
      x++;
    }
  else if (Poisson_cdf(m, 0) <= u)
    while (Poisson_cdf(m, x - 1) > u)  {
      x--;
    }
  else
    x = 0;
  return(x);
}  /* Poisson_idf */

/* ========================================================================= */
/*                          double Uniform_pdf()                             */
/*                          double Uniform_cdf()                             */
/*                          double Uniform_idf()                             */
/*                                                                           */
/* NOTE: use a < x < b and 0 < u < 1                                         */
/* ========================================================================= */
double Uniform_pdf(a, b, x)
double a;
double b;
double x;
{
  return(1.0 / (b - a));
}  /* Uniform_pdf */

double Uniform_cdf(a, b, x)
double a;
double b;
double x;
{
  return((x - a) / (b - a));
}  /* Uniform_cdf */

double Uniform_idf(a, b, u)
double a;
double b;
double u;
{
  return(a + (b - a) * u);
}  /* Uniform_idf */

/* ========================================================================= */
/*                        double Exponential_pdf()                           */
/*                        double Exponential_cdf()                           */
/*                        double Exponential_idf()                           */
/*                                                                           */
/* NOTE: use m > 0, x > 0 and 0 < u < 1                                      */
/* ========================================================================= */
double Exponential_pdf(m, x)
double m;
double x;
{
  return((1.0 / m) * exp(- x / m));
}  /* Exponential_pdf */

double Exponential_cdf(m, x)
double m;
double x;
{
  return(1.0 - exp(- x / m));
}  /* Exponential_cdf */

double Exponential_idf(m, u)
double m;
double u;
{
  return(- m * log(1 - u));
}  /* Exponential_idf */

/* ========================================================================= */
/*                          double Erlang_pdf()                              */
/*                          double Erlang_cdf()                              */
/*                          double Erlang_idf()                              */
/*                                                                           */
/* NOTE: use n >= 1, b > 0, x > 0 and 0 < u < 1                              */
/* ========================================================================= */
double Erlang_pdf(n, b, x)
long n;
double b;
double x;
{ double t, Ln_Gamma();

  t = (double)(n - 1) * log(x / b) - (x / b) - log(b) - Ln_Gamma((double)n);
  return(exp(t));
}  /* Erlang_pdf */

double Erlang_cdf(n, b, x)
long n;
double b; 
double x;
{ double Incomplete_Gamma();

  return(Incomplete_Gamma((double)n, x / b));
}  /* Erlang_cdf */

double Erlang_idf(n, b, u)
long n;
double b;
double u;
{ double tiny = 1.0e-10, t, x, Erlang_cdf(), Erlang_pdf();

  x = (double)n * b;                 /* initialize to the mean, then - */
  do {                               /* use Newton-Raphson iteration   */
    t = x;
    x = t + (u - Erlang_cdf(n, b, t)) / Erlang_pdf(n, b, t);
    if (x <= 0.0)
      x = 0.5 * t;
  } while (fabs(x - t) >= tiny);
  return(x);
}  /* Erlang_idf */

/* ========================================================================= */
/*                          double Normal_pdf()                              */
/*                          double Normal_cdf()                              */
/*                          double Normal_idf()                              */
/*                                                                           */
/* NOTE: x can be any value, but 0 < u < 1                                   */
/* ========================================================================= */
double Normal_pdf (x)
double x;
{ double c = 0.3989422804;                          /* 1 / Sqrt(2 * pi) */

  return(c * exp(-0.5 * x * x));
}  /* Normal_pdf */

double Normal_cdf (x)
double x;
{ double t, Incomplete_Gamma();

  t = Incomplete_Gamma(0.5, 0.5 * x * x);
  if (x < 0.0)
    return(0.5 * (1.0 - t));
  else
    return(0.5 * (1.0 + t));
}  /* Normal_cdf */

double Normal_idf (u)
double u;
{ double tiny = 1.0e-10, t, x, Normal_cdf(), Normal_pdf();

  x = 0.0;                           /* initialize to the mean, then - */
  do {                               /* use Newton-Raphson iteration   */
    t = x;
    x = t + (u - Normal_cdf(t)) / Normal_pdf(t);
  } while (fabs(x - t) >= tiny);
  return(x);
}  /* Normal_idf */

/* ========================================================================= */
/*                           double Gauss_pdf()                              */
/*                           double Gauss_cdf()                              */
/*                           double Gauss_idf()                              */
/*                                                                           */
/* NOTE: x and m can be any value, but s > 0 and 0 < u < 1                   */
/* ========================================================================= */
double Gauss_pdf(m, s, x)
double m;
double s;
double x;
{ double t, Normal_pdf();

  t = (x - m) / s;
  return(Normal_pdf(t) / s);
}  /* Gauss_pdf */

double Gauss_cdf(m, s, x)
double m;
double s;
double x;
{ double t, Normal_cdf();

  t = (x - m) / s;
  return(Normal_cdf(t));
}  /* Gauss_cdf */

double Gauss_idf(m, s, u)
double m;
double s;
double u;
{ double Normal_idf();

  return(m + s * Normal_idf(u));
}  /* Gauss_idf */

/* ========================================================================= */
/*                          double Lognormal_pdf()                           */
/*                          double Lognormal_cdf()                           */
/*                          double Lognormal_idf()                           */
/*                                                                           */
/* NOTE: a can have any value, but b > 0, x > 0 and 0 < u < 1                */
/* ========================================================================= */
double Lognormal_pdf(a, b, x)
double a;
double b;
double x;
{ double t, Normal_pdf();

  t = (log(x) - a) / b;
  return(Normal_pdf(t) / (b * x));
}  /* Lognormal_pdf */

double Lognormal_cdf(a, b, x)
double a;
double b;
double x;
{ double t, Normal_cdf();

  t = (log(x) - a) / b;
  return(Normal_cdf(t));
}  /* Lognormal_cdf */

double Lognormal_idf(a, b, u)
double a;
double b;
double u;
{ double t, Normal_idf();

  t = a + b * Normal_idf(u);
  return(exp(t));
}  /* Lognormal_idf */

/* ========================================================================= */
/*                          double Chisquare_pdf()                           */
/*                          double Chisquare_cdf()                           */
/*                          double Chisquare_idf()                           */
/*                                                                           */
/* NOTE: use n >= 1, x > 0 and 0 < u < 1                                     */
/* ========================================================================= */
double Chisquare_pdf(n, x)
long n;
double x;
{ double t, Ln_Gamma();

  t = (n / 2 - 1) * log(x / 2) - (x / 2) - log(2) - Ln_Gamma(n / 2);
  return(exp(t));
}  /* Chisquare_pdf */

double Chisquare_cdf(n, x)
long n;
double x;
{ double Incomplete_Gamma();

  return(Incomplete_Gamma(n / 2, x / 2));
}  /* Chisquare_cdf */

double Chisquare_idf(n, u)
long n;
double u;
{ double tiny = 1.0e-10, t, x, Chisquare_cdf(), Chisquare_pdf();

  x = n;                               /* initialize to the mean, then - */
  do {                                 /* use Newton-Raphson iteration   */
    t = x;
    x = t + (u - Chisquare_cdf(n, t)) / Chisquare_pdf(n, t);
    if (x <= 0)
      x = 0.5 * t;
  } while (fabs(x - t) >= tiny);
  return(x);
}  /* Chisquare_idf */

/* ========================================================================= */
/*                           double Student_pdf()                            */
/*                           double Student_cdf()                            */
/*                           double Student_idf()                            */
/*                                                                           */
/* NOTE: use n >= 1, x > 0 and 0 < u < 1                                     */
/* ========================================================================= */
double Student_pdf(n, x)
long n;
double x;
{ double t, Ln_Beta();

  t = -0.5 * (n + 1) * log(1 + ((x * x) / (double)n))
                                     - Ln_Beta(0.5, (double)n / 2.0);
  return(exp(t) / sqrt((double)n));
}  /* Student_pdf */

double Student_cdf(n, x)
long n;
double x;
{ double s, t, Incomplete_Beta();

  t = (x * x) / (n + x * x);
  s = Incomplete_Beta(0.5, (double)n / 2.0, t);
  if (x >= 0)
    return(0.5 * (1.0 + s));
  else
    return(0.5 * (1.0 - s));
}  /* Student_cdf */

double Student_idf(n, u)
long n;
double u;
{ double tiny = 1.0e-10, t, x, Student_cdf(), Student_pdf();

  x = 0;                              /* initialize to the mean, then - */
  do {                                /* use Newton-Raphson iteration   */
    t = x;

    //printf("Student_cdf(%ld, %lf) = %lf\n",n,u,Student_cdf(n, t)); 
    //printf("Student_pdf(%ld, %lf) = %lf\n",n,u,Student_pdf(n, t)); 

    x = t + (u - Student_cdf(n, t)) / Student_pdf(n, t);

    //printf("x = %lf\n", x);
    //printf("difference = %lf\n\n\n", fabs(x-t));

  } while (fabs(x - t) >= tiny);
  return(x);
}  /* Student_idf */
