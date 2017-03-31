#!/usr/bin/env python
printTillAge = 7300
plotMeanCalvingTimeTillAge = 1000
plotFirstCalvingTimeStartingAtAge = 400
plotFirstCalvingTimeTillAge = 1400

deadCowTableName = "BVD_Dead_Cows"
cowIDIndex = 0
cowMeanCalvingTimeIndex = 1
cowSexIndex = 2
cowAgeIndex = 3
cowNumberOfCalvesIndex = 4
cowCauseOfDeathIndex = 5
cowFirstCalvingTimeIndex = 6



tradingTableName = "BVD_Trades"
tradeDateIndex = 0
tradeSRCFarmIDIndex = 1
tradeDestFarmIDIndex = 2
tradeCowIDIndex = 3
tradeCowAgeIndex = 4
tradeCowSexIndex = 5

farmTimesTableName = "BVD_Farm_Times"
tradeTimesTableName = "BVD_Trade_Times"
intermediateCalvingTimesTableName = "BVD_intermediate_calving_times"

tradeTablePrefix = "Trades_t"
farmsTablePrefix = "Farms_t"


farmIDIndex = 0
farmSIndex = 1
farmTIIndex = 2
farmPIIndex = 3
farmRIndex = 4

cowFemale = 1.0
cowDeathReasonNatural = 105.0
cowDeathReasonSlaughter = 201.0
cowInvalidFirstCalvingTime = -1.0
cowInfectionEvent = 107
