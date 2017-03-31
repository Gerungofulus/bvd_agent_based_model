
#include "CommandlineOptions.h"





class BVDOptions: public CommandLineOptions{
	public:
	BVDOptions();
	static std::string iniFilePath;
	static void handleIniOption(int spot, char* args[]);
	private:
	/*Command line arguments and handling */
	static const int numHelpOptions;
	static const std::string optHelp[2]; 
	static const std::string descHelp;
	static const CommandLineArgument helpOption;
	
	//ini file specification
	static const int numIniOptions;
	static const std::string optIni[2];
	static const std::string descIni;
	static const CommandLineArgument iniOption;
	
	//all options
	static const int overallNumberOfOptions;
	static const CommandLineArgument allOptions[];
};

