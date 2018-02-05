// #include <ostream>
// #include <iostream>
// #include "Simple_One_Herd_Farm.h"
// #include "System.h"
// #include "Herd.h"
// #include "Cow.h"
// #include "Events.h"
// using namespace std;
#include <iostream>
#include "projectImports/Catch/catch.hpp"
#include "projectImports/FakeIt/fakeit.hpp"
#include "Cow.h"
#include "System.h"
#include "projectImports/inih/cpp/INIReader.h"
#include "Farm.h"
#include "Simple_One_Herd_Farm.h"
#include "Events.h"
#include "BVD_Random_Number_Generator.h"
using namespace fakeit;
TEST_CASE("Vaccination tests", "[Cow]"){
  //Set up a system with a single cow in a single farm
  INIReader reader("./iniFiles/unitTestCow.ini");
  System * s = System::getInstance(&reader);
  Farm* f = new Simple_One_Herd_Farm(s);
  f->holdSize();
  Cow::set_system(s);

  //add a new cow for each run. Note that the cow called erna will be a new cow for every single section
  Cow *erna = new Cow( 0.0 , nullptr, true );
  f->push_cow(erna);

  Random_Number_Generator rng = Random_Number_Generator();

  //We mock the random number generator to make sure it returns predictable results
  Mock<Random_Number_Generator> fakeRNG(rng);
  s->rng = &(fakeRNG.get());

  //make sure every calf is female
  When(Method(fakeRNG, is_calf_female)).AlwaysReturn(true);
  //make sure every vaccination works
  When(Method(fakeRNG, vaccinationWorks)).AlwaysReturn(true);

  SECTION("Waiting for the end of MA before vaccinating for the first time"){
    //set up the mother just about to give birth to a calf
    erna->calf_status = Calf_Status::SUSCEPTIBLE;
    //let the mother give birth to a calve at day 500
    s->run_until(499);
    Event *birth = new Event( 500 , Event_Type::BIRTH , erna->id() );
    erna->execute_event(birth);
    //make sure the fake random number generator has been used
    Verify(Method(fakeRNG, is_calf_female)).AtLeastOnce();

    //check if the scheduled first vaccination takes place after the end of MA
    //born at day 500 erna's calve will get out of MA around day 680 so make sure
    //that the vaccination event scheduled is happening after that time
    Event_queue q = s->getEventQueue();
    s->dump_queue();
    std::cout << erna->id() << std::endl;
    while (!q.empty()){//iterate over all events in that queue
      Event* e = q.top();
      if (e->type == Event_Type::VACCINATE && e->id ==  erna->id()+1){//check for the calf, it the first vaccination is scheduled after the approximate end of its MA
        REQUIRE(e->execution_time > 680);
        // return;
      }
      q.pop();
    }

  }
  SECTION("A successful vaccination schedules a vaccination end event and a new vaccination and makes the cow IMMUNE"){

    //since System is a singleton, it will persist the state after the first section so we have to start a day later
    //schedule the vaccination
    Event *vacc = new Event( 500 , Event_Type::VACCINATE , erna->id() );
    s->schedule_event(vacc);
    // run until the vaccination is Done
    s->run_until(501);
    //make sure the fake random number generator has been used
    Verify(Method(fakeRNG, vaccinationWorks)).AtLeastOnce();

    //make sure the cow is immune now
    REQUIRE(erna->infection_status == Infection_Status::IMMUNE);
    Event_queue q = s->getEventQueue();
    //keep track of other events in there
    int numberOfVaccinationEndEvents = 0;
    int numberOfVaccinationEvents = 0;
    while (!q.empty()){//iterate over all events in that queue
      Event* e = q.top();
      if (e->type == Event_Type::END_OF_VACCINATION && e->id ==  erna->id()){//check if a vaccination end has been scheduled: the entry should be exactly one
        numberOfVaccinationEndEvents++;
      }
      if (e->type == Event_Type::VACCINATE && e->id ==  erna->id()){//check if a new vaccination event has been scheduled
        numberOfVaccinationEvents++;
      }
      q.pop();
    }

    //naje sure there is exactly one of each
    REQUIRE(numberOfVaccinationEvents == 1);
    REQUIRE(numberOfVaccinationEndEvents == 1);

  }
  SECTION("If the vaccination failed a new vaccination gets scheduled a year later, no vaccination end is scheduled, the cow is not immune"){
    //make sure this vaccination fails
    fakeRNG.Reset();
    When(Method(fakeRNG, vaccinationWorks)).AlwaysReturn(false);
    REQUIRE(erna->infection_status == Infection_Status::SUSCEPTIBLE);

    Event *vacc = new Event( 502 , Event_Type::VACCINATE , erna->id() );
    s->schedule_event(vacc);
    // run until the vaccination is Done
    s->run_until(503);
    //make sure the fake random number generator has been used
    Verify(Method(fakeRNG, vaccinationWorks)).AtLeastOnce();
    //make sure the cow is not immune now
    REQUIRE(erna->infection_status != Infection_Status::IMMUNE);
    Event_queue q = s->getEventQueue();
    //keep track of other events in there
    int numberOfVaccinationEndEvents = 0;
    int numberOfVaccinationEvents = 0;
    while (!q.empty()){//iterate over all events in that queue
      Event* e = q.top();
      if (e->type == Event_Type::END_OF_VACCINATION && e->id ==  erna->id()){//check if a vaccination end has been scheduled: the entry should be exactly one
        numberOfVaccinationEndEvents++;
      }
      if (e->type == Event_Type::VACCINATE && e->id ==  erna->id()){//check if a new vaccination event has been scheduled
        numberOfVaccinationEvents++;
      }
      q.pop();
    }
    //naje sure there is exactly one of each
    REQUIRE(numberOfVaccinationEvents == 1);
    REQUIRE(numberOfVaccinationEndEvents == 0);
  }
  SECTION("On schedule of a new insemination: Vaccinate a cow 40 days before insemination if it hasn't been vaccinated before."){}
  SECTION("On schedule of a new insemination: If the cow has been vaccinated in the last 200 days, do nothing"){}
  SECTION("On schedule of a new insemination: If the cow has been vaccinated before the last 200 days, invalidate the old vaccination end event, the old next vaccination event and schedule a new vaccination 40 days ahead of insemination"){}
}

// }
