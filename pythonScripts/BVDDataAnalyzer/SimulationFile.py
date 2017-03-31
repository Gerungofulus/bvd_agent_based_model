#!/usr/bin/env python
import outputSpecification as outputSpec
import h5py as h5
import os
import numpy as np
import sys
def getFileNames(fileName):
    filenames = []
    path = ""
    if fileName.lower().endswith('.txt'):
        path = os.path.dirname(os.path.abspath(fileName))
        with open(fileName) as f:
            filenames = f.readlines()
        del f
    elif fileName.lower().endswith('.h5'):
        filenames.append(fileName)
    else:
        print("no valid file given")

    return (filenames,path)


class FarmDataManager:
    def __init__(self):
        self.farms = {}
    def getFarm(self,id):
        if id in self.farms:
            return self.farms[id]
        else:
            f = Farm(id)
            self.farms[id] = f
            return f

    def getAllInfectedFarmsAtTime(self,time):
        AllInfectedFarmsAtTime = []
        for id,farm in self.farms.iteritems():
            if time in farm.infectiousTimes:
                AllInfectedFarmsAtTime.append(farm)
        return AllInfectedFarmsAtTime

    def getNumberOfInfectiousFarmsAtTime(self, time):
        return len(self.getAllInfectedFarmsAtTime(time))
        
    def getPrevalenceAtTime(self, time):
        returnDict = {}
        returnDict["time"] = time
        
        for id,f in self.farms.iteritems():
            fdata = f.getDataAtTime(time)
            
            for key, value in fdata.iteritems():
                if not key in returnDict:
                    returnDict[key] = 0
                returnDict[key] = returnDict[key] + value
        return returnDict
        
    def addFarmDataDict(self, time, FarmDataTableDict):
        
        id = FarmDataTableDict.pop("id")
        farm = self.getFarm(id)
        farm.setDataPoint(time, FarmDataTableDict)


class Farm:
    def __init__(self, id):
        self.data = {}
        self.infectiousTimes = []
        self.hasBeenInfected = False
        self.id = id
    def setDataPoint(self, time, dataDict ):
        if(dataDict["ti"] != 0 or dataDict["pi"] != 0):
            self.infectiousTimes.append(time)
            self.hasBeenInfected = True
        dataDict["total"] = 0
        for key, value in dataDict.iteritems():
            if key != "total":
                dataDict["total"] += value
        
        self.data[time] = dataDict
    
    def getDataAtTime(self,time):
        return self.data[time]


class SimulationFile:
    def __init__(self,fileName, printStuff = False):
        self.printStuff = printStuff
        self.files = []
        self.keys = []
        self.keyToFiles = {}
        self.keysForFiles = {}
        self.filenames,self.path = getFileNames(fileName)
        for fileName in self.filenames:
            
            fullpath = os.path.join(self.path, fileName).strip()
            if self.printStuff:
                print "scanning " + fullpath
            try:
                file = h5.File(fullpath, 'r')
                self.files.append(fullpath)
                self.keysForFiles[fullpath] = []
                for key in file.keys():
                    if not key in self.keys:
                        self.keys.append(key)
                        self.keyToFiles[key] = []
                    self.keyToFiles[key].append(fullpath)
                    self.keysForFiles[fullpath].append(key)
            
                file.close()
                pass
            except IOError as ioe:
                print fileName
                print ioe
                pass

    def getFullTable(self, key):
        
        #for fileName in self.retunFilesForKey(key):
        
        return self.getMultipleTables([key])[key]
        
    def getFilesForKey(self, key):
        return self.keyToFiles[key]
    
    def getAllKeys(self):
        return self.keys
    
    def getKeyForFile(self,fileName):
        
        return self.keysForFiles[fileName]
    
    def getMultipleTables(self, keys):
        files = []
        readingKeys = []
        tables = {}
        for key in [key for key in set(keys) if key in self.keys]:
            
            readingKeys.append(key)
            files = files + self.getFilesForKey(key)
        fileset = set(files)
        
        for fileName in fileset:
            file = h5.File(fileName, 'r')
            
            for key in [key for key in self.getKeyForFile(fileName) if key in readingKeys]:
                data = file[key]
                subTable = np.array(data)
                if not key in tables:
                    tables[key] = subTable
                else:
                    fullTable = tables[key]
                    tables[key] = np.concatenate([fullTable, subTable])
            file.close()
        
        return tables
        
    def getBreedingDynamicsData(self):
        data = self.getMultipleTables([outputSpec.deadCowTableName, outputSpec.intermediateCalvingTimesTableName])
        
        return data
        
    def getTestData(self):
        data = self.getFullTable(outputSpec.testsTableName)
        return data
    
    def getIntermediateCalvingTimes(self):
        data = self.getFullTable(outputSpec.intermediateCalvingTimesTableName)
        return data
    
    def getDataDictFromDataPoint(self, rowData, dict):
        dataDict = {}
        for key,value in dict.iteritems():
            dataDict[key] = rowData[value]
        return dataDict
    
    def getAllDataFromSplitUpTables(self, tablePrefix, timeTableName):
        fullRetData = {}
        for fileName in self.files:
            file = h5.File(fileName, 'r')
            try:
                h5times = file[timeTableName]
                times = np.array(h5times[:].astype(int))
                for time in times:
                    
                    dataSetName = tablePrefix + str(time)
                    h5data = file[dataSetName]
                    retData = np.array(h5data)
                    fullRetData[time] = retData
            except KeyError:
                print "error"
                pass
            file.close()
        return fullRetData
    
    
    def getEndemicData(self):
        fdm = FarmDataManager()
        retData = {}
        fullFarmData = self.getAllDataFromSplitUpTables(outputSpec.farmsTablePrefix, outputSpec.farmTimesTableName)
        for time,data in fullFarmData.iteritems():
            for row in data:
                rowData = self.getDataDictFromDataPoint(row, outputSpec.farmTable)
                fdm.addFarmDataDict(time,rowData)
            retData[time] = {}
            retData[time]["prevalenceCows"] = fdm.getPrevalenceAtTime(time)
            
            retData[time]["prevalenceFarms"] = fdm.getAllInfectedFarmsAtTime(time)
        return (len(fdm.farms),retData)
    
    def getTradeData(self):
        fullTradeData = self.getFullTable(outputSpec.tradingTableName)
        trades = np.array( fullTradeData )
        tradingAges = {}
        tradingAges["male"] = []
        tradingAges["female"] = []
        
        for sex in tradingAges:
            cols = trades[:,outputSpec.tradeCowSexIndex] == outputSpec.sexes[sex]
            data = trades[cols,outputSpec.tradeCowAgeIndex]
            tradingAges[sex] = data.reshape(len(data),1)
        tradeData = {}
        tradeData["tradingAges"] = tradingAges
        return tradeData
    
    def getTradeMatrices(self):
        
        fullTradeData = self.getAllDataFromSplitUpTables(outputSpec.tradeTablePrefix, outputSpec.tradeTimesTableName)
        return fullTradeData

    def getStaticTradesPerFarm(self):
        fullTradeData = self.getFullTable(outputSpec.tradingTableName)
        tradeTable = outputSpec.tradeTable
        returnDict = {}
        
        
        trades = np.array( fullTradeData )
        for trade in trades:
            src = trade[tradeTable["srcFarm"]]
            time = trade[tradeTable["date"]]
            dest = trade[tradeTable["destFarm"]]
            #print str(src) + " " + str(dest)
            if not src in returnDict:
                farmDict = {}
                farmDict["id"]=src
                farmDict["in"]={}
                farmDict["out"]={}
                farmDict["times"] = []
            else:
                farmDict = returnDict[src]
            
            if not dest in returnDict:
                destDict = {}
                destDict["id"]=dest
                destDict["in"]={}
                destDict["out"]={}
                destDict["times"] = []
            else:
                destDict = returnDict[dest]
            
            #farmDict["times"].append(time)
            #destDict["times"].append(time)
            
            
            if not dest in farmDict["out"]:
                farmDict["out"][dest] = 1
            else:
                farmDict["out"][dest] += 1
            
            if not src in destDict["in"]:
                destDict["in"][src] = 1
            else:
                destDict["in"][src] += 1
            
            returnDict[src] = farmDict
            returnDict[dest] = destDict
        return returnDict



#    def
