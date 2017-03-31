import csv
import numpy as np
import betterStat
import h5py
import matplotlib.pyplot as plt

def h5FileToCsv(filename):

    f = h5py.File(filename)
    for name in f:
        np.savetxt(filename + name + ".csv", h5py.File(filename)[name], '%g', ',')

def getColumn(filename, column):
    results = csv.reader(open(filename), delimiter=";")
    return [result[column] for result in results]

def getCSVValues(fileName):
    x = getColumn(fileName, 0)
    y = getColumn(fileName, 1)
    yr = [float(i) for i in y[1:]]
    xr = [float(i) for i in x[1:]]
    return (yr, xr)

def getCSVValuesYNormalized(fileName):
    yr, xr = getCSVValues(fileName)
    maxy = max(yr)
    miny = min(yr)
    normalizedY = [i/maxy for i in yr]
    return (normalizedY,xr)

def getCSVStatistics(fileName):
    y, x = getCSVValues(fileName)
    yarr = np.array(y[:]).astype(int)
    xarr = np.array(x[:]).astype(int)
    #mu =np.average(xarr, weights=yarr)
    #median = np.median(yarr)
    #sigma = np.std(yarr)
    return betterStat.getHistogrammStatistics(xarr,yarr)#(mu, median,sigma )


def plotCSVFile(fileName, plot = False):
    
    x = getColumn(fileName, 0)
    yr = getColumn(fileName, 1)
    y = [ float(i) for i in yr[1:]]
    if isinstance(x[0], basestring):
        plt.xlabel(x[0])
    if isinstance(yr[0], basestring):
        plt.ylabel(yr[0])
    maxy = max(y)
    miny = min(y)
    normalized = [i/maxy for i in y ]
    plt.plot(x[1:len(x)-1],normalized[0:len(normalized)-1])
    if plot:
        plt.show()

def writeDictOfLists(filename, listdict):
    file = open(filename,'wb')
    wr = csv.writer(file, quoting=csv.QUOTE_ALL)
    
    keys = listdict.keys()
    listlength = len(listdict[keys[0]])
    wr.writerow(keys)
    
        
    for i in range(listlength):
        line = []
        for key in keys:
            line.append(listdict[key][i])
        wr.writerow(line)





        
