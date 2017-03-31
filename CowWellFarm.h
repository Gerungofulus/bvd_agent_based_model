#ifndef __CowWellFarm_h_
#define __CowWellFarm_h_
#include "Farm.h"
class System;
class CowWellFarm: public Farm{
	public:
		CowWellFarm(System *s);
		~CowWellFarm();
		
		void push_cow(Cow *c);
		void pull_cow(Cow *c);
		int getACowId();
	private:
		
};
#endif

