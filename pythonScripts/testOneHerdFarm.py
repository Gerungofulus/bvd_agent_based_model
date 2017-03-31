#!/usr/bin/env python
import matplotlib.pyplot as plt
import h5py as h5
import numpy as np
import sys
import os
import BVDDataAnalyzer.SimFile as Analyzer
if len(sys.argv) < 2:
    print("you have to provide a filename")
    sys.exit(1)


filenames, path = Analyzer.getFileNames(sys.argv[1])
for file in filenames:
    if not path == "":
        sys.argv[1] = (path+"/"+file).strip()
    else:
        sys.argv[1] = file
    
    
    fileName = sys.argv[1]
    f = h5.File(fileName)
    print(fileName)
    try:
        h5tradeTimes = f['BVD_Trade_Times']
        fileTimes = h5tradeTimes[:].astype(int)
        if not 'trades' in globals():
            trades = []
            tradeTimes = []
            totalTrades = 0
        for time in fileTimes:
            currTrades = 0
            tradeTimes.append(time)
            dataSetName = "Trades_t" + str(int(time))
            h5Matrix = f[dataSetName]
            tradeMat = np.asmatrix(h5Matrix[:,:].astype(int))
            numOfFarms = len(tradeMat[:])
            currTrades = np.sum(tradeMat[:,0]) #all Trades going to that one farm
            totalTrades += currTrades
            trades.append(currTrades)
    except KeyError:
        pass

print totalTrades
plt.figure(1)
plt.plot(tradeTimes, trades, label='Trades')
plt.title('Trades per Time')
plt.ylabel('number of trades')
plt.xlabel('time in days')
#plt.plot(farmTimes, globSum, label='Sum')
plt.legend()
#plt.show()
