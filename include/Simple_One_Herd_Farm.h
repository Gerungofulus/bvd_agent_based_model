#include "Farm.h"

class Herd;

class Simple_One_Herd_Farm : public Farm
{
 public:
  Simple_One_Herd_Farm( System *s );
  ~Simple_One_Herd_Farm();
  void push_cow( Cow* c);
  void pull_cow( Cow* c);

};
