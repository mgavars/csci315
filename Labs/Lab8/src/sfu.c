/* ------------------------------------------------------------------------- */
/* These are C lang routines which can be used to evaluate some of the       */
/* 'special' functions which arrise in the modeling and analysis of various  */
/* statistical distributions.                                                */
/*                                                                           */
/* Name            : SFU.C                                                   */
/* Purpose         : Special Function Routines                               */
/* Author          : Steve Park                                              */
/* Language        : Turbo Pascal, 5.0                                       */
/* Latest Revision : 09-19-90                                                */
/* Reference       : Lecture Notes on Simulation, by Steve Park              */
/* Converted to C  : David W. Geyer  09-02-91                                */
/* ------------------------------------------------------------------------- */
/* include files */
#include <math.h>                          /* for log(), exp(), abs() */

//#define ABS(a) ( (a > 0) ? a : -(a) )

typedef enum {false, true} boolean;

/* ========================================================================= */
/*                             double Ln_Gamma()                             */
/* ========================================================================= */
/* Ln_Gamma returns the natural log of the gamma function.                   */
/* NOTE: use a > 0.0                                                         */
/*                                                                           */
/* The algorithm used to evaluate the natural log of the gamma function is   */
/* based on an approximation by C. Lanczos, SIAM J. Numerical Analysis, B,   */
/* vol 1, 1964.  The constants have been selected to yield a relative error  */
/* which is less than 2.0e-10 for all positive values of the parameter a.    */
/* ========================================================================= */
double Ln_Gamma(a)
double a;
{ double c = 2.506628274631;                     /* Sqrt(2 * pi) */
  double s[6], sum, temp;
  int    i;

  s[0] =  76.180091729406 / a;
  s[1] = -86.505320327112 / (a + 1);
  s[2] =  24.014098222230 / (a + 2);
  s[3] =  -1.231739516140 / (a + 3);
  s[4] =   0.001208580030 / (a + 4);
  s[5] =  -0.000005363820 / (a + 5);
  sum  =   1.000000000178;
  for (i=0;i < 6;i++)
    sum += s[i];
  temp = (a - 0.5) * log(a + 4.5) - (a + 4.5) + log(c * sum);
  return(temp);
}  /* Ln_Gamma */

/* ========================================================================= */
/*                         double Ln_Factorial()                             */
/* ========================================================================= */
/* Ln_Factorial(n) returns the natural log of n!                             */
/* NOTE: use n >= 0                                                          */
/*                                                                           */
/* The algorithm used to evaluate the natural log of n! is based on a        */
/* simple equation which relates the gamma and factorial functions.          */
/* ========================================================================= */
double Ln_Factorial(n)
long n;
{ double Ln_Gamma();

  return(Ln_Gamma((double)n + (double)1.0));
}  /* Ln_Factorial */

/* ========================================================================= */
/*                            double Ln_Beta()                               */
/* ========================================================================= */
/* Ln_Beta returns the natural log of the beta function.                     */
/* NOTE: use a > 0.0 and b > 0.0                                             */
/*                                                                           */
/* The algorithm used to evaluate the natural log of the beta function is    */
/* based on a simple equation which relates the gamma and beta functions.    */
/* ========================================================================= */
double Ln_Beta(a, b)
double a, b;
{ double temp, Ln_Gamma();

  temp    = Ln_Gamma(a) + Ln_Gamma(b) - Ln_Gamma(a + b);

  // printf("Ln_Beta(%lf, %lf) = %lf\n", a, b, temp);

  return(temp);
}  /* Ln_Beta */

/* ========================================================================= */
/*                            double Ln_Choose()                             */
/* ========================================================================= */
/* Ln_Choose returns the natural log of the binomial coefficient C(n,m).     */
/* NOTE: use 0 <= m <= n                                                     */
/*                                                                           */
/* The algorithm used to evaluate the natural log of a binomial coefficient  */
/* is based on a simple equation which relates the beta function to a        */
/* binomial coefficient.                                                     */
/* ========================================================================= */
double Ln_Choose(n, m)
long n, m;
{ double Ln_Beta();

  if (m > 0)
    return(- Ln_Beta((double)m, (double)(n - m + 1)) - log((double)m));
  else
    return((double) 0.0);
}  /* Ln_Choose */

/* ========================================================================= */
/*                     double Incomplete_Gamma()                             */
/* ========================================================================= */
/* Evaluates the incomplete gamma function.                                  */
/* NOTE: use a > 0.0 and x >= 0.0                                            */
/*                                                                           */
/* The algorithm used to evaluate the incomplete gamma function is based on  */
/* Algorithm AS 32, J. Applied Statistics, 1970, by G. P. Bhattacharjee.     */
/* See also equations 6.5.29 and 6.5.31 in the Handbook of Mathematical      */
/* Functions, Abramowitz and Stegum (editors).  The absolute error is less   */
/* than 1e-10 for all non-negative values of x.                              */
/* ========================================================================= */
double Incomplete_Gamma(a, x)
double a, x;
{ double tiny = 1.0e-10;                      /* convergence parameter */
  double t, sum, term, factor, f, g, c[2], p[3], q[3];
  double Ln_Gamma();
  long   n;

  if (x > 0.0)
    factor = exp(-x + a * log(x) - Ln_Gamma(a));
  else
    factor = 0.0;
  if (x < a + 1.0) {                 /* evaluate as an infinite series - */
      t    = a;                      /* A & S equation 6.5.29            */
      term = 1.0 / a;
      sum  = term;
      do {                           /* sum until 'term' is small */
        t++;
        term *= x / t;
        sum  += term;
      } while (term >= tiny * sum);
      return(factor * sum);
  }

  else  {                            /* evaluate as a continued fraction - */
    p[0]  = 0.0;                     /* A & S eqn 6.5.31 with the extended */
    q[0]  = 1.0;                     /* pattern 2-a, 2, 3-a, 3, 4-a, 4,... */
    p[1]  = 1.0;                     /* - see also A & S sec 3.10, eqn (3) */
    q[1]  = x;
    f     = p[1] / q[1];
    n     = 0;
    do {                             /* recursively generate the continued */
      g  = f;                        /* fraction 'f' until two consecutive */
      n++;                           /* values are small                   */
      if ((n%2) > 0) {
        c[0] = ((double)(n + 1) / 2) - a;
        c[1] = 1.0;
      }
      else  {
        c[0] = (double)(n / 2);
        c[1] = x;
      }
      p[2] = c[1] * p[1] + c[0] * p[0];
      q[2] = c[1] * q[1] + c[0] * q[0];
      if (q[2] != 0.0)  {             /* rescale to avoid overflow */
          p[0] = p[1] / q[2];
          q[0] = q[1] / q[2];
          p[1] = p[2] / q[2];
          q[1] = 1.0;
          f    = p[1];
      }
    } while ((fabs(f - g) >= tiny) || (q[1] != 1.0));
    return((double)1.0 - factor * f);
  }
}  /* Incomplete_Gamma */

/* ========================================================================= */
/*                     double Incomplete_Beta()                              */
/* ========================================================================= */
/* Evaluates the incomplete beta function.                                   */
/* NOTE: use a > 0.0, b > 0.0 and 0.0 <= x <= 1.0                            */
/*                                                                           */
/* The algorithm used to evaluate the incomplete beta function is based on   */
/* equation 26.5.8 in the Handbook of Mathematical Functions, Abramowitz     */
/* and Stegum (editors).  The absolute error is less than 1e-10 for all x    */
/* between 0 and 1.                                                          */
/* ========================================================================= */
double Incomplete_Beta(a, b, x)
double a, b, x;
{ double tiny = 1.0e-10;                      /* convergence parameter */
  double t, factor, f, g, c, p[3], q[3], Ln_Beta();
  boolean swap;
  long   n;

  if (x > (a + 1) / (a + b + 1)) {   /* to accelerate convergence   */
    swap = true;                     /* complement x and swap a & b */
    x    = 1 - x;
    t    = a;
    a    = b;
    b    = t;
  }
  else                                /* do nothing */
    swap = false;
  if (x > 0)
    factor = exp(a * log(x) + b * log(1 - x) - Ln_Beta(a,b)) / a;
  else
    factor = 0;
  p[0] = 0;
  q[0] = 1;
  p[1] = 1;
  q[1] = 1;
  f    = p[1] / q[1];
  n    = 0;
  do {                               /* recursively generate the continued */
    g = f;                           /* fraction 'f' until two consecutive */
    n++;                             /* values are small                   */
    if ((n%2) > 0)  {
      t = (n - 1) / 2;
      c = -(a + t) * (a + b + t) * x / ((a + n - 1) * (a + n));
    }
    else  {
      t = n / 2;
      c = t * (b - t) * x / ((a + n - 1) * (a + n));
    }
    p[2] = p[1] + c * p[0];
    q[2] = q[1] + c * q[0];
    if (q[2] != 0)  {                /* rescale to avoid overflow */
      p[0] = p[1] / q[2];
      q[0] = q[1] / q[2];
      p[1] = p[2] / q[2];
      q[1] = 1.0;
      f    = p[1];
    }
  } while ((fabs(f - g) >= tiny) || (q[1] != 1));
  if (swap)
    return(1.0 - factor * f);
  else
    return(factor * f);
}  /* Incomplete_Beta */
