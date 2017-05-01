
#ifndef __bvdsettings_h_
#define __bvdsettings_h_
class INIReader;

class BVDSettings{
    static const BVDSettings* sharedInstance(const INIReader& reader);


private:
    const INIReader* reader;
    BVDSettings(const INIReader& reader);
    ~BVDSettings();
    BVDSettings(const BVDSettings&);

    static BVDSettings* _instance;

    class CGuard
	{
	public:
	   ~CGuard();

	};

    double bloodTestAccuracy;
    double retestTimeMax;
    double vaccinationWorkingProb;
};
#endif
