#!/usr/bin/env python
import outputSpecification as outputSpec
import numpy as np
import SimulationFile as File

class SimulationAnalyzer:
    def __init__(self,file):
        if isinstance(file,File.SimulationFile):
            self.file=file
        else:
            self.file = File.SimulationFile(file)
        self.times = range(0,outputSpec.printTillAge)
    def getTradingAgesStats(self):
        tradeData = self.file.getTradeData()
        tradingAgesMale = tradeData["tradingAges"]["male"]
        tradingAgesFemale = tradeData["tradingAges"]["female"]
        

        tradingAges = np.concatenate([tradingAgesMale ,tradingAgesFemale],axis=0)
        tradingAgeY , tradingAgeX = np.histogram(tradingAges, bins=self.times)
        tradingAgeFemaleY , tradingAgeFemaleX = np.histogram(tradingAgesFemale, bins=self.times)
        tradingAgeMaleY , tradingAgeMaleX = np.histogram(tradingAgesMale, bins=self.times)

        return (self.times, tradingAgeY,tradingAgeFemaleY,tradingAgeMaleY)

    def getBreedingDynamicsStats(self):
        
        data = self.getBreedingDynamics()
        
        returnDict = self.createHistogramDictForDataDict(data)
    
        return returnDict

    def getBreedingDynamics(self):
        data = self.file.getBreedingDynamicsData()
        cows = {}
        cowData = data[outputSpec.deadCowTableName]
        firstCalvingTimes = []
        allDeathAges = []
        for sex in outputSpec.sexes:
            if not sex in cows:
                cows[sex] = {}
                cows[sex]["individual"] = []
                cows[sex]["ages"] = []
                for event in outputSpec.deathEvents:
                    cows[sex][event] = []
        for cow in cowData:
            for sex in outputSpec.sexes:
                
                if cow[outputSpec.cowSexIndex] == outputSpec.sexes[sex]:
                    age = cow[outputSpec.cowAgeIndex]
                    allDeathAges.append(age)
                    cows[sex]["individual"].append(self.file.getDataDictFromDataPoint(cow,outputSpec.cowTableDict))
                    cows[sex]["ages"].append(age)
                    for event in outputSpec.deathEvents:
                        if(cow[outputSpec.cowCauseOfDeathIndex] == outputSpec.deathEvents[event]):
                            cows[sex][event].append(age)
                    if sex == "female":
                        if cow[outputSpec.cowFirstCalvingTimeIndex] != outputSpec.cowInvalidFirstCalvingTime:
                            firstCalvingTimes.append(cow[outputSpec.cowFirstCalvingTimeIndex])
                    break;
       
        returnDict = {}
        returnDict["intermediateCalvingTimes"] = self.analyzeInterMediateCalvingTimes(data[outputSpec.intermediateCalvingTimesTableName])
        returnDict["cows"] = cows
        returnDict["firstCalvingTimes"] = firstCalvingTimes
        returnDict["allDeathAges"] = allDeathAges
        return returnDict


    def getTestData(self):
        data = self.file.getTradeData()
        testData = data[outputSpec.testsTableName]
        for test in testData:
            print "bla"

    
    def createHistogramDictForDataDict(self,data):
        returnDict = {}
        for key in data:
            
            if isinstance(data[key], list):#plainValues
                
                if data[key] and isinstance(data[key][0],dict):
                    
                    continue
                if not key in returnDict:
                    returnDict[key] = {}
                returnDict[key]["y"], returnDict[key]["x"] = np.histogram(data[key], bins = self.times)
                returnDict[key]["mu"] = np.average(data[key])
                returnDict[key]["median"] = np.median(data[key])
                returnDict[key]["sigma"] = np.std(data[key])
            elif isinstance(data[key],dict):#male and femaleLists
                returnDict[key] = self.createHistogramDictForDataDict(data[key])
        return returnDict
    
    def analyzeInterMediateCalvingTimes(self,data=None):
        if data is None:
            retdata = self.file.getIntermediateCalvingTimes()
            data = data[outputSpec.intermediateCalvingTimesTableName]
        intermediateCalvingTimes = data
    
        allInterCTimes = []
        tiInterCTimes = []
        noInfectCTime = []
        for row in intermediateCalvingTimes:
            time = row[outputSpec.intermediateCalvingTimes["time"]]
            allInterCTimes.append(time)
            if row[outputSpec.intermediateCalvingTimes["healthState"]] == outputSpec.hasBeenIllDuringPregnancy:
                tiInterCTimes.append(time)
            else:
                noInfectCTime.append(time)

        returnDict = {}
        returnDict["nonti"] = noInfectCTime
        returnDict["all"]   = allInterCTimes
        returnDict["ti"]    = tiInterCTimes
        return returnDict

    def getPIData():
        returnDict = {}
        
        return returnDict
