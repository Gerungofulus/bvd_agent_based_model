
#ifndef __bvdsettings_h_
#define __bvdsettings_h_
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include "BVDContainmentStrategy.h"
class INIReader;
struct BVDContainmentStrategy;

enum fileMode{
	single_file = 0,
	multi_file = 1
};
struct OutputSettings{
    bool overwrite;
    std::string fileExtension;
    std::string fullFilePath;
    std::string fileprefix;
    std::string path;
    fileMode mode;

	bool writeAllDeadCows;
	bool writeDeadPIS;
	bool writeTradeAdjacencyMatrix;
	std::string postFileWriteCall;
};
class BVDSettings{
public:
    static BVDSettings* sharedInstance(INIReader* reader = nullptr);
    StrategyQueue strategies;
    OutputSettings outputSettings;
private:
    INIReader* reader;
    BVDSettings(INIReader* reader);
    ~BVDSettings();
    BVDSettings(const BVDSettings&);

    static BVDSettings* _instance;



    double bloodTestAccuracy;
    double retestTimeMax;
    double vaccinationWorkingProb;


    //strategies


    void initializeStrategies();

    void initializeStrategy(const std::string& name);

    void initializeOutputSettings();
    static fileMode iniInputToFileMode(std::string& fileMode,bool shallExit=true);
    class CGuard
	{
	public:
	   ~CGuard();

	};

};



#endif
