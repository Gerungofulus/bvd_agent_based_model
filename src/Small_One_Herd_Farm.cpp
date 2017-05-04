#include "Small_One_Herd_Farm.h"
#include "Herd.h"
#include "SmallFarmManager.h"

Small_One_Herd_Farm::Small_One_Herd_Farm( System * s ) :  Farm( s )
{
	#ifdef _SIMPLE_HERD_DEBUG_
		std::cout << "creating one herd farm" << std::endl;
	#endif
  my_herds.push_back(new Herd( this ) );
  
  this->manager = new SmallFarmManager(this,s);
  #ifdef _SIMPLE_HERD_DEBUG_
		std::cout << "created manager, setting type" << std::endl;
	#endif
  this->myType = SMALL_FARM;
  #ifdef _SIMPLE_HERD_DEBUG_
		std::cout << "finished creating one herd farm" << std::endl;
	#endif
}

Small_One_Herd_Farm::~Small_One_Herd_Farm()
{
  for (auto h : my_herds )
    delete h;
}

void Small_One_Herd_Farm::push_cow( Cow * c )
{
	
  my_herds.front()->push_cow( c );
}

void Small_One_Herd_Farm::pull_cow( Cow *c )
{
  my_herds.front()->pull_cow( c );
}
