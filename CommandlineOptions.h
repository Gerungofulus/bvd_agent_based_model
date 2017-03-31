#ifndef __commandlineoptions_h_
#define __commandlineoptions_h_
//command line arguments
#include <string>
struct CommandLineArgument{
	const int numberOfOptions;
	const std::string *options;
	const std::string description;
	void (*func)(int spot, char* args[]);//the function that should be called when the option is found. It gets all arguments given to the main handling function
};
class CommandLineOptions{
	//neat printing
	public:
	CommandLineOptions(int numOfOptions,const CommandLineArgument *allOptions);
	void printCommandLineArguments(const int num,const std::string args[],const std::string description);
	
	void printCommandLineArguments(const CommandLineArgument& option);
	
	void printHelpMenu();
	
	//handling all command line arguments and calls corrosponding functions
	void handleCommandLineArguments(int num, char *args[]);
	private:
		const CommandLineArgument *allOptions;
		int overallNumberOfOptions;
};
#endif
