#ifndef __output_h_
#define __output_h_

#include "hdf5.h"
#include "hdf5_hl.h"
#include <string>
#include <array>
#include <vector>
class Output
{
 public:
  Output( std::string filename , bool overwrite=false);
  
  ~Output();
  typedef std::vector< std::array< int , 4 >* > Datapoint;
  void log_datapoint( double time , Datapoint * d );
  void write_to_file();
  void set_number_of_farms(unsigned int N);
  
  
 private:
  unsigned int T ; //number of timepoints so far
  unsigned int N ; //number of farms.
  std::vector<double> out_times;
  hid_t open_file( std::string filename , bool overwrite );
  std::string _filename;
  std::vector< int > data ; //complete data stored here. Old school.. [i][j][k] -> [ i*N*4 + j*4 + k ]
  //[time_idx][farm_idx][infection_state_index] 
    
};
#endif
