#include "BVDSettings.h"
#include "projectImports/inih/cpp/INIReader.h"
BVDSettings* BVDSettings::_instance = 0;
const BVDSettings* BVDSettings::sharedInstance(const INIReader& reader){
   static CGuard g;   // Speicherbereinigung
   if (!BVDSettings::_instance)
      BVDSettings::_instance = new BVDSettings (reader);
   return _instance;
}

BVDSettings::BVDSettings(const INIReader& reader){
    this->reader = &reader;
    bloodTestAccuracy = this->reader->GetReal("containment", "bloodTestAccuracy", 0.98);
	retestTimeMax = this->reader->GetReal("containment", "retestingTimeBlood", 40);
	vaccinationWorkingProb = this->reader->GetReal("containment", "vaccinationWorkingProbability", 0.985);
}
BVDSettings::BVDSettings(const BVDSettings&){}
BVDSettings::~BVDSettings(){}

BVDSettings::CGuard::~CGuard(){
	if(BVDSettings::_instance != nullptr){
		delete BVDSettings::_instance;
		BVDSettings::_instance = nullptr;
	}
}
