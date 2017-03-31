#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import sys
import BVDDataAnalyzer

def doThePlot(filename):
    analyzer = BVDDataAnalyzer.Analyzer.SimulationAnalyzer(filename)
    file = analyzer.file
    path = file.path
    farms = file.getStaticTradesPerFarm()
    interEventTimes = []
    indeg = []
    outdeg = []
    farmID = []
    cummweights = []
    cummdeg = []
    farmids = farms.keys()
    for id in farmids:
        farm = farms[id]
        times = farm["times"].sort()
        
        lastTime = -1
        if not times == None:
            for time in times:
                if not lastTime == -1:
                    diff = time - lastTime
                    interEventTimes.append(diff)
                lastTime = time
        farmID.append(id)

        indeg.append(len(farm["in"]))
        outdeg.append(len(farm["out"]))
        myweight = 0
        mydeg = 0
        for src in farm["in"]:
            myweight += farm["in"][src]
            mydeg +=1
        for dest in farm["out"]:
            myweight += farm["out"][dest]
            mydeg += 1
        cummdeg.append(mydeg)
        cummweights.append(myweight)
    #degrees, weights = sorted(zip(cummdeg,cummweights))
    cummdeg = np.array(cummdeg)
    cummweights = np.array(cummweights)
    indizes = cummdeg.argsort()
    degrees = cummdeg[indizes]
    weights = cummweights[indizes]
    plt.semilogy(farmID,outdeg,label="Outdegrees")
    
    plt.semilogy(farmID,indeg,label="Indegrees")
    plt.xlabel("Farm ID")
    plt.ylabel("Degree")
    plt.legend()
    figureName = "degreeDistri"
    plt.savefig(path+"/"+figureName+".png")
    plt.figure(2)
    plt.loglog(degrees,weights,'o')
    plt.xlabel("Cummulative Degree")
    plt.ylabel("Weight")
    figureName = "weightDegreeDistri"
    plt.savefig(path+"/"+figureName+".png")
    plt.show()


if len(sys.argv) < 2:
    print("you have to provide a filename")
    sys.exit(1)
filename = sys.argv[1]
doThePlot(filename)
