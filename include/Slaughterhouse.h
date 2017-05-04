#ifndef __slaughterhouse_h_
#define __slaughterhouse_h_
#include "Farm.h"

class System;
class Cow;

class Slaughterhouse : public Farm
{
 public:
  Slaughterhouse( System *s );
  ~Slaughterhouse();
  void push_cow(Cow *c );
  void pull_cow(Cow *c );
};

#endif
