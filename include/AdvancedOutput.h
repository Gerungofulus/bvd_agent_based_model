#ifndef __output_h_
#define __output_h_

#include <vector>
#include <string>


class INIReader;

class Farm;
class Event;
class Cow;
class FileHandler;

enum fileType{
	HDF5,
	SQLITE	
};

class AdvancedOutput{
	public:
	
		
		AdvancedOutput(INIReader& reader);
		
		~AdvancedOutput();
		void logEvent(const Event *event);
		void logInfectionRateChangeEvent(const Event* event);
		void logFarms(const double time,const std::vector< Farm* >*farms);
		
		
		void write_to_file(double time=0.0);
		void logBirth(const Cow *c);
		void logResultingEventOfInfection(const Event* e);
	private:

		
		
		
		fileType type;
		
		
		FileHandler* handler;
		static std::string fileTypeToExtension(fileType type);
		static fileType iniInputToFileType(std::string& fileType,bool shallExit=true);
		
						
};

#endif
