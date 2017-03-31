#include "Output.h"
#include <string>
#include <array>
#include <iostream>


Output::Output( std::string filename , bool overwrite)
{
  auto hasEnding =[this] (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
  };
  if (!(hasEnding(filename,".h5") || hasEnding(filename,".hdf5")))
    filename += ".h5";
  hid_t file_id = open_file( filename , overwrite );
  H5Fclose( file_id );
  T=0;
  N=1;
  _filename=filename;
}
void Output::set_number_of_farms( unsigned int number_of_farms )
{
  if ( number_of_farms == 0 )
    std::cerr << "Error: Trying to set the number of Farms for output to 0. Quitting."<<std::endl;
  N = number_of_farms;
}

void Output::log_datapoint( double time , Datapoint * d )
{
  // (1) Check validity (correct number of farms)
  if (d->size() != N)
    {
      std::cerr << " Error while logging datapoint at time t=" <<time<<". Expected values for "<<N<<" farms, got values for "<<d->size()<<". Exiting."<<std::endl;
      exit(1);
    }
  // (2) append to time
  // (3) append to data
  out_times.push_back(time);
  for ( auto farm : *d ){
    for( auto const val : *farm )
      data.push_back( val );
  	delete farm;
  }
  T++;
}

hid_t Output::open_file( std::string filename , bool overwrite)
{

  hid_t file_id              = H5Fcreate( filename.c_str() ,
					  overwrite ? H5F_ACC_TRUNC : H5F_ACC_EXCL ,
					  H5P_DEFAULT,
					  H5P_DEFAULT);
  if (file_id < 0 )
    {
      std::cerr << "Error while setting up output file with name " << filename << " . . Possible reason: File already exists." << std::endl;
      exit(1);
    }
  return file_id;
}

void Output::write_to_file()
{
  hid_t file_id = open_file( _filename , true );
  const int rank       = 3; // time,farm,infection_status
  unsigned int num_time_points = T;
  
  hsize_t   dims[rank] = {num_time_points , N , 4}; // 4 because S,TI,PI,R => 4 different infection states.
  hsize_t   t_dims[1]  = {num_time_points};
  
  
  int success = H5LTmake_dataset_int( file_id ,
				      "/BVD_Data",
				      rank,
				      dims,
				      &data[0] );
  success = H5LTmake_dataset_double( file_id ,
				     "/times",
				     1,
				     t_dims,
				     &out_times[0] );

  if (success < 0 )
    std::cerr << "Fehler beim Schreiben der Daten." << std::endl;
  H5Fclose( file_id );

				      
  
}

Output::~Output()
{
  write_to_file();
}


