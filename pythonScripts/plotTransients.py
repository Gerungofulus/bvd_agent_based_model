#!/usr/bin/env python
import matplotlib.pyplot as plt
import h5py as h5
import numpy as np
import sys
import os

if len(sys.argv) < 2:
    print("you have to provide a filename")
    sys.exit(1)


filenames = []
path = ""
if sys.argv[1].lower().endswith('.txt'):
    path = os.path.dirname(os.path.abspath(sys.argv[1]))
    with open(sys.argv[1]) as f:
        filenames = f.readlines()
elif sys.argv[1].lower().endswith('.h5'):
    filenames.append(sys.argv[1])
else:
    print("no valid file given")
    sys.exit(1)
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
        h5cows = f[deadCowTableName]
        cows = h5cows[:,:].astype(float)
    except KeyError:
        pass
    if not 'trades' in globals():
        trades = []
        tradeTimes = []
        birthTimes = []
    if 'fileTimes' in globals():
        for time in fileTimes:
            if 'cows' in globals():
                for cow in cows:
                    birthTimes.append(cow[cowBirthTimeIndex])
            
            currTrades = 0
            tradeTimes.append(time)
            dataSetName = "Trades_t" + str(int(time))
            h5Matrix = f[dataSetName]
            tradeMat = np.asmatrix(h5Matrix[:,:].astype(int))
            numOfFarms = len(tradeMat[:])
            currTrades = np.sum(tradeMat)
            trades.append(currTrades)


