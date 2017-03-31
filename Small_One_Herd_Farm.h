#include "Farm.h"
#ifndef __small_one_herd_farm_h_
#define __small_one_herd_farm_h_
class Herd;

class Small_One_Herd_Farm : public Farm
{
 public:
  Small_One_Herd_Farm( System *s );
  ~Small_One_Herd_Farm();
  void push_cow( Cow* c);
  void pull_cow( Cow* c);

};

#endif
