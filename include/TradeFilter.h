#ifndef __trade_filter_h_
#define __trade_filter_h_

class Trade_Event;
class TradingFilter{
	public:
		TradingFilter();
		virtual ~TradingFilter();
		bool operator()(const Trade_Event* event);
		virtual bool check(const Trade_Event* event)=0;
};

class WellSlaughterhouseFilter: public TradingFilter{
	public:
		WellSlaughterhouseFilter();
		~WellSlaughterhouseFilter();
		bool check(const Trade_Event* event);
};

class SameFarmFilter: public TradingFilter{
	public:
		bool check(const Trade_Event* event);
};
#endif
