#include <ostream>
#include <iostream>
#include "Simple_One_Herd_Farm.h"
#include "System.h"
#include "Herd.h"
#include "Cow.h"
#include "Events.h"
using namespace std;




void print_info( Cow::Set& v )
{
  for ( auto c : v )
    {
      cout << "id: " << c->id() << ", Birth time: " << c->birth_time  << " female: " << c->female << endl;
      cout << "    Infection_status:" << (int)c->infection_status << ", last_conception_time: " << c->last_conception_time ;
      cout << " calving_number: " << c-> calving_number << ", Calf_status: " << (int)c->calf_status << endl<<endl;
    }
  (*v.begin())->herd->print_info(cout);
  cout << "--------------------------------------------------------------------------------"<<endl<<endl;
}



int main(int argc, char** argv)
{

  System *s = new System(0);
  s->set_log_interval(0.5);
  Cow::set_system(s);
  
  Farm*   f = new Simple_One_Herd_Farm(s);
  
  Cow *elsa  = new Cow( 0 , NULL ); 
  Cow *Gerda = new Cow( 1 , elsa ); 
  Cow *Trude = new Cow( 2 , elsa ); 
 
      

  elsa->infection_status = Infection_Status::PERSISTENTLY_INFECTED;
  elsa->calf_status      =      Calf_Status::SUSCEPTIBLE;
  Gerda->infection_status = Infection_Status::IMMUNE;
  Gerda->calf_status      =      Calf_Status::SUSCEPTIBLE;
  Gerda->calving_number   = 2;

  f->push_cow(elsa);
  f->push_cow(Gerda);
  f->push_cow(Trude);

  Event *e = new Event ( 1 , Event_Type::END_OF_MA, 2 );
  s->schedule_event( e );

  e = new Event ( 10 , Event_Type::BIRTH , 1 );


  s->schedule_event( e );
  
  s->run_until( 10 );
  exit(0);

  f->print_state(cout);
  s->print_next_event();

  s->execute_next_event();

  f->print_state(cout);
  s->print_next_event();
  
  s->execute_next_event();

  f->print_state(cout);
  s->print_next_event();
  
  s->execute_next_event();

  f->print_state(cout);
  s->print_next_event();
  
  s->execute_next_event();

  f->print_state(cout);
  s->print_next_event();
  
  s->execute_next_event();

  f->print_state(cout);
  s->print_next_event();
  
  s->execute_next_event();

  f->print_state(cout);
  s->print_next_event();
  
  s->execute_next_event();

  f->print_state(cout);
  
  s->dump_queue();
}
