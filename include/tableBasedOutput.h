#ifndef __table_output_h_
#define __table_output_h_

#include "FileHandler.h"
#include "BVDSettings.h"
class Trade_Event;
class Event;
class Cow;
class Farm;

struct TradeDataPoint{
	double date;
	double srcFarmID;
	double destFarmID;
	double cowID;
	double cowAge;
	double cowSex;

	double operator[] (int i);
	operator const double*();
	operator double*();
	static const int size;
};

struct FarmDataPoint{
	int id;
	int numberS;
	int numberTI;
	int numberPI;
	int numberR;
	int operator[] (int i);
	operator int*();
	static const int size;
};

struct CowDataPoint{
	double id;
	double lastConceptionTime;
	double female;
	double age;
	double numberOfCalves;
	double causeOfDeath;
	double firstCalvingTime;
	double birthTime;
	double knownState;
	double numberOfVaccinations;
	double firstTestTime;
	double lastTestTime;
	double operator[] (int i);
	operator double*();
	static const int size;
};

struct TestDataPoint{
	double id;
	double date;
	double age;
	double testType;
	double sex;
	double result;
	double infectiousState;
	double knownState;
	double operator[] (int i);
	operator double*();
	operator const double*();
	static const int size;
};

struct InfectionResultDataPoint{
	int id;
	int resultType;
	int calfStatus;
	int operator[] (int i);
	operator int*();
	static const int size;
};
struct intermediateCalvingTimePoint{
	double id;
	double intermediateCalvingTime;
	double healthState;
	double operator[] (int i);
	operator double*();
	operator const double*();
	static const int size;
};



class TableBasedOutput : public FileHandler{
private:

public:
    TableBasedOutput();
    ~TableBasedOutput();
    void logFarms(const double time,const std::vector< Farm* >*farms);
    void logEvent(const Event *e);
    void logBirth(const Cow *c);
    void logResultingEventOfInfection(const Event* e);
    void logTest(const Event *e, const Cow *c);



protected:
    typedef std::vector<TradeDataPoint> TradeDataSave;
    typedef std::vector<FarmDataPoint> FarmDataSave;
    typedef std::vector<FarmDataSave *> FarmData;
    typedef std::vector<CowDataPoint> CowDataSave;
    typedef std::vector<CowDataSave* > CowDataSaveStorage;
    typedef std::vector<TestDataPoint> TestDataSave;
    typedef std::vector<intermediateCalvingTimePoint> intermediateCalvingTimeSave;
    typedef std::vector<InfectionResultDataPoint> infectionResultDataSave;


    void logTrade(const Trade_Event* event);
    void logDyingCow(const Event* event,const Cow* cow);
    void logInfection(const Event* event,const Cow* cow,const bool didLooseCalf=false);
    void logInfectionRateChangeEvent(const Event* event);

    TestDataPoint testEventToDataPoint(const Event*, const Cow* c);
    CowDataPoint createCowDataPointForCow(const Event* event,const Cow* cow);
    void createIntermediateCalvingTimePoints(Cow*c);

    void writeCowToSave(const Event* event,const Cow* cow, CowDataSave* save);
    void flushStorages();

    template<typename T>
    void clearMySave(std::vector<T>* save, bool clearThis = true);
    template<typename T>
    void clearMyStorage(std::vector<T>* storage);






    std::vector<double>* farmDataTimes;
    intermediateCalvingTimeSave* intermediateCalvingTimes;
    FarmData* farmData;
    TradeDataSave* trades;
    CowDataSave* CowData;
    CowDataSave* InfectionData;
    CowDataSave* PIDeathSave;
    CowDataSaveStorage* piStorage;
    TestDataSave* testStorage;
    infectionResultDataSave *infectionResultSave;

    int farmNum;

    fileMode mode;

};

#endif
