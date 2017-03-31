#!/usr/bin/env python
import matplotlib.pyplot as plt
import h5py as h5
import numpy as np
import sys
import BVDDataAnalyzer




def doThePlot(filename):
    file = BVDDataAnalyzer.SimFile.SimulationFile(filename)
    filenames = file.filenames
    path = file.path

    allTradeMatrices = file.getTradeMatrices()

    times = allTradeMatrices.keys()
    del file
    tradeTimes = sorted(times)
    trades = []
    sellingIndex = 0
    buyinIndex = 1
    numBuyinFarms = []
    numSellinFarms = []
    for time in tradeTimes:

        currTrades = 0
        
        tradeMat = allTradeMatrices[time]
        nozeroes = np.transpose(tradeMat.nonzero())
        buyinFarms = {}
        sellingFarms = {}
        
        for tupel in nozeroes:
            if tupel[sellingIndex] in sellingFarms:
                sellingFarms[tupel[sellingIndex]] += 1
            else:
                sellingFarms[tupel[sellingIndex]] = 1
            if tupel[buyinIndex] in buyinFarms:
                buyinFarms[tupel[buyinIndex]] += 1
            else:
                buyinFarms[tupel[buyinIndex]] = 1

        numBuyinFarms.append(len(buyinFarms))
        numSellinFarms.append(len(sellingFarms))
        #print tradeMat[nozeroes]
        
        
        numOfFarms = len(tradeMat[:])
        currTrades = np.sum(tradeMat)
        trades.append(currTrades)

    fig, ax1 = plt.subplots()

    ax1.plot(tradeTimes, trades, label='Trades')

    plt.title('Trading Activity')
    ax1.set_ylabel('number of trades')
    ax1.set_xlabel('time in days')
    #plt.plot(farmTimes, globSum, label='Sum')
    ax2 = ax1.twinx()
    ax2.set_ylabel('number of active farms')
    plt.plot(tradeTimes, numSellinFarms, label='Selling Farms', color='r')
    plt.plot(tradeTimes, numBuyinFarms, label='Buying Farms', color='g')

    ax1.legend(loc="upper left")
    ax2.legend()

    plt.savefig(path + "/tradingPlot.png" )
    plt.clf()
    #plt.show()

if len(sys.argv) < 2:
    print("you have to provide a filename")
    sys.exit(1)
doThePlot(sys.argv[1])
