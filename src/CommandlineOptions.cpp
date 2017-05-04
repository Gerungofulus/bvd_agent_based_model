#include "CommandlineOptions.h"
#include <iostream>
#include <cstring>
CommandLineOptions::CommandLineOptions(int numOfOptions,const CommandLineArgument *allOptions):overallNumberOfOptions(numOfOptions){
	this->allOptions = allOptions;
}

void CommandLineOptions::printCommandLineArguments(const int num,const std::string args[],const std::string description){
		std::cout << "\t\t";
		for(int i=0; i < num; i++){
			std::cout << args[i] << "\t\t\t" ;
		}
		std::cout << description << std::endl;
}

void CommandLineOptions::printCommandLineArguments(const CommandLineArgument& option){
		printCommandLineArguments(option.numberOfOptions, option.options, option.description);
	}
void CommandLineOptions::printHelpMenu(){
	std::cout << "This is a simulation programm that simulates the endemic behaviour of bovine viral diarrhea. " << std::endl;
	std::cout << "Command line arguments " << std::endl;
	for(int i = 0; i < overallNumberOfOptions; i++){
		printCommandLineArguments(allOptions[i]);
	}
	exit(0);
}
void CommandLineOptions::handleCommandLineArguments(int num, char *args[]){
		
	for(int i = 1; i < num; i++){
		if( strcmp(args[i], "--help") == 0 ||  strcmp(args[i], "-h") == 0 ){
			printHelpMenu();	  
		}
		for(int j = 0; j < overallNumberOfOptions; j++){

			for(int k = 0; k < allOptions[j].numberOfOptions; k++){

			  if(strcmp(args[i],allOptions[j].options[k].c_str()) == 0 && allOptions[j].func != NULL){

				  allOptions[j].func(i,args);
				  break;
			  }
			}
		 }
	}
}

