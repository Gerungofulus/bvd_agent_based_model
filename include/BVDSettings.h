
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



class BVDSettings{
public:
    static BVDSettings* sharedInstance(INIReader* reader);
    StrategyQueue strategies;

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


    class CGuard
	{
	public:
	   ~CGuard();

	};
};

#endif
