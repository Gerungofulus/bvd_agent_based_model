#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <time.h>

int und (int ranLRmax)			//uniform number distribution
{

	const gsl_rng_type * T;
  	gsl_rng * r;

  	int i, n = 10;

	T = gsl_rng_default;

 	r = gsl_rng_alloc (T);

 	gsl_rng_env_setup();  
 	//set a random seed
 	unsigned int seed = (time(NULL)  + random());   
    gsl_rng_set (r,seed);

  
    int ranLR;
  ranLR = gsl_rng_uniform_int(r, ranLRmax);
  //printf("A random long from U[ranLRmin,%d-1): %d\n", ranLRmax, ranLR);

  gsl_rng_free (r);

  return ranLR;
}



double time_of_abortion_due_to_infection( double time_of_pregnancy )
{
	int index = und(101);
	printf("%d\n", index );
	if (time_of_pregnancy <= 70)
	{
		if (index <10)
		{
		return (time_of_pregnancy + und(14));
		}
	}
	if (time_of_pregnancy > 70 && time_of_pregnancy <=120)
	{
		if (index >10 && index<=25)
		{
		return (time_of_pregnancy + und(14));
		}
	}
	if (time_of_pregnancy > 121 && time_of_pregnancy <=180)
	{
		if (index >25 && index<=45)
		{
		return (time_of_pregnancy + und(14));
		}
	}
	if (time_of_pregnancy > 180)
	{
		if (index >45 && index<=50)
		{
		return (time_of_pregnancy + und(14));
		}
	}
	else
	{
		return 0;
	}
}

int main()
{
	printf("%f\n", time_of_abortion_due_to_infection(123) );
}
