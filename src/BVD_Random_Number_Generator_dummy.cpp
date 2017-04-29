#include "BVD_Random_Number_Generator.h"
#include "Cow.h"
int rng::ran_unif_int( int hi , int lo )
{
  return lo;
}

bool rng::will_TI_calf_die()
{
  return false;
}

double rng::time_of_death_infected_calf()
{
  return 1.34;
}

Calf_Status rng::calf_outcome_from_infection( double time_of_pregnancy )
{
  return Calf_Status::ABORT;
}

double rng::time_of_abortion_due_to_infection( double time_of_pregnancy )
{
  return 2.4;
}

double rng::time_of_rest_after_calving()
{
  return 60;
}


double rng::time_of_next_infection( double rate )
{
  return 0.5/(rate+0.01);

}
double rng::duration_of_infection()
{
  return 7;
}
int rng::number_of_calvings()
{
  return 4;
}
bool rng::is_calf_female()
{
  return true;
}
double rng::lifetime_PI()
{
  return 100;//days
}
double rng::duration_of_MA()
{
  return 20;
}

double rng::insemination_result(bool first_pregnancy , bool* conception)
{
  *conception = true;
  return 12;
}

bool   rng::is_this_a_deadbirth( double age_of_mother )
{
  return false;
}

double rng::conception_result(double age_of_mother , Infection_Status is_of_mother , bool* birth)
{
  *birth = true;
  return 290;
}

double rng::time_of_death_as_calf()
{
  return -1;
}

double rng::first_insemination_age()
{
  return 400;
}

