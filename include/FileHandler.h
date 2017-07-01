#ifndef __FileHandler_h_
#define __FileHandler_h_
#include <string>
#include <vector>
#include <iostream>

class INIReader;
class Cow;
class Event;
class Farm;

class FileHandler{

	public:
	FileHandler();
	virtual ~FileHandler();
	virtual void logEvent(const Event *event)=0;

	virtual void logFarms(const double time,const std::vector< Farm* >*farms)=0;
	virtual void logBirth(const Cow *c)=0;
	//virtual void logDyingCow(const Event* event,const Cow* cow)=0;
	//virtual void logInfection(const Event* event,const Cow* cow,const bool didLooseCalf)=0;
	virtual void write_to_file(const double time=0.0)=0;
	virtual void logResultingEventOfInfection(const Event* e)=0;

	protected:
		bool overwrite;
		std::string fileExtension;
		std::string fullFilePath;
		std::string fileprefix;
		std::string path;
		void setPath();

};

#endif
