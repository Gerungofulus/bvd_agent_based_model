#ifndef __utilities_h_
#define __utilities_h_
#include "Cow.h"
#include "Events.h"
#include <ostream>

class Utilities
{
 public:
  static const std::map< Infection_Status , std::string > IS_tostr;
  static const std::map< Calf_Status , std::string > CS_tostr;
  static const std::map< Event_Type  , std::string > Event_tostr;
  static void pretty_print( Cow* c   , std::ostream& out );
  static void pretty_print(const Event* c , std::ostream& out );
  static void printStackTrace(int number=10);
};

#endif
