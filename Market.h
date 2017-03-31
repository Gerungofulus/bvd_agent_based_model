#ifndef __market_h_
#define __market_h_
#include <set>
#include "Cow.h"

class System;
class Farm;
class TradingFilter;
class CowWellFarm;
class Slaughterhouse;
class Offer
{
	public:	
		Offer(Cow::UnorderedSet* cows, Farm* src);
		~Offer();
		Cow::UnorderedSet* getCows();
	
	
		Cow::UnorderedSet* cows; 
		Farm* src;
};
class Demand
{
	public:
	Demand(Cow_Trade_Criteria criteria, int number, Farm* source);
	~Demand();
	
	Cow_Trade_Criteria crit;
	int numberOfDemandedCows;
	Farm* src;
};

class Market
{
 public:
  Market( System* system);
  ~Market();
  void register_offer( Offer * offer);
  void register_demand( Demand *demand);
	void flushQueues();
  
  void registerSourceFarm(CowWellFarm* f);
  void registerSlaughterHouse(Slaughterhouse* sl);
  void sellDirectlyToSlaughterHouse(const Cow* cow);
  
  void setFarms(std::vector<Farm*>* newfarms);
  void registerFarm(Farm *f);
  private:
	int lastID;
  	typedef std::queue<Cow*> cowqueue;
  	typedef std::queue<Demand*>  demandqueue;
  	typedef std::vector<cowqueue* > cowQvec;
  	typedef std::vector<demandqueue*> cowDvec;
  	
  	void matchTradingPartners(cowqueue* offerQueue, demandqueue* demandQueue);
  	void matchDemandToOfferQueue(Demand* demand, cowqueue* offerQueue); 
  	const std::pair<cowqueue*, demandqueue*> getRelevantQueues(const Cow_Trade_Criteria crit);
  	bool doTheTrading(Cow* cow, Demand* d);
  	bool scheduleTrade(Trade_Event* event);
  	System *s;
  	
  	cowQvec* cowQs;
  	cowDvec* demandQs;
  	
  	bool dump;
  	std::vector<Slaughterhouse*>* slaughterHouses;
  	std::vector<CowWellFarm*>* sources;
  	std::vector<Farm*>* farms;
  	std::vector<TradingFilter*>* filters;
  	bool ignoreTypeOfDemand;
  	std::vector<Cow_Trade_Criteria> *buyingQueueTradeCriteriaPriorities;
  	
  	void scheduleTradeToSlaughterHouse(Cow* c);
  	template<typename T>
  	void cleanUpBufferQueue(std::queue<T>* trueQ, std::queue<T>* bufferQ);

};


#endif
