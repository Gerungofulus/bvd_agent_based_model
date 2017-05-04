#ifndef __HDF5Handler_h_
#define __HDF5Handler_h_
#include "FileHandler.h"
#include <vector>
#include "hdf5.h"
#include "hdf5_hl.h"
#include <fstream>

enum fileMode{
	single_file = 0,
	multi_file = 1
};

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

class HDF5FileHandler: public FileHandler{
	public:
		HDF5FileHandler(INIReader& reader);
		~HDF5FileHandler();
		
		
		
		void logFarms(const double time,const std::vector< Farm* >*farms);
		void logEvent(const Event *e);
		void logBirth(const Cow *c);
		void logTest(const Event *e, const Cow *c);
		void logResultingEventOfInfection(const Event* e);
		void write_to_file(const double time);
	private:
		void logInfection(const Event* event,const Cow* cow,const bool didLooseCalf=false);
		void logInfectionRateChangeEvent(const Event* event);
		void logTrade(const Trade_Event* event);
		hid_t open_file(const std::string filename ,const bool overwrite);
		void writeTradeData(const hid_t& file);
		void writeFarmData(const hid_t& file);
		void writeCowData(const hid_t& file);
		void writeTestData(const hid_t& file);
		void writeInfectionResultData(const hid_t& file);
		
		
		
		typedef std::vector<TradeDataPoint> TradeDataSave;
		typedef std::vector<FarmDataPoint> FarmDataSave;
		typedef std::vector<FarmDataSave *> FarmData;
		typedef std::vector<CowDataPoint> CowDataSave;
		typedef std::vector<CowDataSave* > CowDataSaveStorage;
		typedef std::vector<TestDataPoint> TestDataSave;
		typedef std::vector<intermediateCalvingTimePoint> intermediateCalvingTimeSave;
		typedef std::vector<InfectionResultDataPoint> infectionResultDataSave;
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
		void flushStorages();
		void writeCowToSave(const Event* event,const Cow* cow, CowDataSave* save);
		void writeSaveToFile(const hid_t& file, CowDataSave* save,const std::string tableName);
		CowDataPoint createCowDataPointForCow(const Event* event,const Cow* cow);
		void writeLivingPIsToFile(const hid_t& file);
		bool deleteList;
		static fileMode iniInputToFileMode(std::string& fileMode,bool shallExit=true);
		void logDyingCow(const Event* event,const Cow* cow);
		fileMode mode;
		std::string fileExtension;
		TestDataPoint testEventToDataPoint(const Event*, const Cow* c);
		template<typename T>
		void clearMyStorage(std::vector<T>* storage);
		
		template<typename T>
		void clearMySave(std::vector<T>* save, bool clearThis = true);
		//TODO refactoring
		template<typename T, typename returnType>
		void createWritableData(std::vector<T>* save, returnType** data);
		template<typename T> 
		void writeTemplateSaveToFile(const hid_t& file, std::vector<T>* save,const std::string tableName);
		void createIntermediateCalvingTimePoints(Cow*c);
		
		
		static const std::string intermediateCalvingTimeTableName;
		static const std::string infectionResultTabelName;
		static const std::string testsTableName;
};


#endif
