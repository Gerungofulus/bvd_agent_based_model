#!/usr/bin/env python
import numpy as np

def getHistogrammStatistics(xvals,yvals):
    rawData = []
    if len(xvals) != len(yvals):
        raise ValueError("both arrays given should have the same length")
    
    for i in range(len(xvals)):
        for j in range(yvals[i]):
            rawData.append(xvals[i])
    rawDatArr = np.array(rawData)
    mu = np.mean(rawDatArr)
    median = np.median(rawDatArr)
    sigma = np.std(rawDatArr)
    return (mu, median, sigma)
