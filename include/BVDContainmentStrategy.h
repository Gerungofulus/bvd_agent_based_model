#ifndef __containment_strategy_h_
#define __containment_strategy_h_
#include <queue>
struct BVDContainmentStrategy{
    bool usesEartag;
    bool usesVaccination;
    bool usesJungtierFenster;
    double startTime;
    double bloodTestAccuracy;
    double retestingTimeBlood;
    double vaccinationWorkingProbability;
    double vaccinationTimeBeforeInsemination;
    double vaccinationTimeOfDefense;
    double quarantineTime;
    bool applyQuarantineOnBuying;
    bool respectQuarantine;
    double quarantineAfterPositiveTest;
    double jungtierzeit;

};

class BVDContainmentStrategyFactory{
public:
    static BVDContainmentStrategy defaultStrategy;

};
class BVDContainmentStrategySortCriterion
{
 public:
  bool operator() (BVDContainmentStrategy const * const  s1 , BVDContainmentStrategy const * const s2);
};
typedef std::priority_queue< BVDContainmentStrategy* , std::vector< BVDContainmentStrategy*> , BVDContainmentStrategySortCriterion > StrategyQueue;
#endif
