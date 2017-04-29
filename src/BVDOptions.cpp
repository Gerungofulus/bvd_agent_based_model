#include "BVDOptions.h"
#include <iostream>


std::string BVDOptions::iniFilePath = "NONE";
const int BVDOptions::numHelpOptions = 2;
const  std::string BVDOptions::optHelp[2] = {"--help", "-h"}; 
const  std::string BVDOptions::descHelp = "Print this help menu";
const  CommandLineArgument BVDOptions::helpOption = {numHelpOptions, optHelp, descHelp, NULL};

//ini file specification
const  int BVDOptions::numIniOptions = 2;
const std::string BVDOptions::optIni[2] = {"--ini", "-i"};
const  std::string BVDOptions::descIni = "The path to the ini file you want to use";
const  CommandLineArgument BVDOptions::iniOption = {numIniOptions, optIni, descIni,BVDOptions::handleIniOption};

//all options
const  int BVDOptions::overallNumberOfOptions = 2;
const  CommandLineArgument BVDOptions::allOptions[] = {helpOption, iniOption};

BVDOptions::BVDOptions():CommandLineOptions(BVDOptions::overallNumberOfOptions, BVDOptions::allOptions){}


void BVDOptions::handleIniOption(int spot, char* args[]){
	std::cout << "Ini Argument spotted at position " << spot <<". Path: " << args[spot+1] << std::endl;
	BVDOptions::iniFilePath = args[spot+1];
	
	
}

