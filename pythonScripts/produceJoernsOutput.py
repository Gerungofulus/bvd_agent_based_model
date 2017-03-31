#!/usr/bin/env python

from BVDDataAnalyzer import outputSpec as outputSpec
import BVDDataAnalyzer
import sys
import csvTools

analyzer = BVDDataAnalyzer.Analyzer.SimulationAnalyzer(sys.argv[1])

numberOfFarms, allIneed = analyzer.file.getEndemicData()
path = analyzer.file.path

times = sorted(allIneed.keys())


csvFarmDataDict = {}
tonetime = times[0]
for key in allIneed[tonetime]["prevalenceCows"]:
    csvFarmDataDict[key] = []
csvFarmDataDict["numberOfInfectedFarms"] = []
for time in times:
    thisData = allIneed[time]
    
    for key in thisData["prevalenceCows"]:
        csvFarmDataDict[key].append(thisData["prevalenceCows"][key])

    csvFarmDataDict["numberOfInfectedFarms"].append(len(thisData["prevalenceFarms"]))

csvTools.writeDictOfLists(path+"/farm_data.csv",csvFarmDataDict)


csvFarmDataDict = {}


