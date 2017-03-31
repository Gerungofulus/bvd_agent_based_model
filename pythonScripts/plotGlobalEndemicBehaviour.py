#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import sys
import BVDDataAnalyzer
def doThePlot(filename, scenariotext=""):
    analyzer = BVDDataAnalyzer.Analyzer.SimulationAnalyzer(filename)
    file = analyzer.file
    numberOfFarms, allIneed = file.getEndemicData()
    path = file.path
    if path == "":
        return
    del file
    plotPIOnly = True
    
    globR = []
    globS = []
    globTI = []
    globPI = []
    globSum = []
    globs = []
    globti = []
    globpi = []
    globr = []
    farmTimes = []
    times = allIneed.keys()

    for time in sorted(times):
        
        data = allIneed[time]
        
        
        
        
        #print(intMatrix[0,1])
        globSCurr = 0
        globTICurr = 0
        globPICurr = 0
        globRCurr = 0
        globSumCurr = 0
        
        for key,dat in data.iteritems():
            
            if key == "prevalenceCows":
                farmTimes.append(dat["time"])
                
                globSCurr = globSCurr + dat["s"]
                globTICurr = globTICurr + dat["ti"]
                globPICurr = globPICurr + dat["pi"]
                globRCurr = globRCurr + dat["r"]
                globSumCurr = globSumCurr + dat["total"]
                if globSumCurr != 0:
                    
                    globr.append(float(globRCurr)/float(globSumCurr))
                    globs.append(float(globSCurr)/float(globSumCurr))
                    globti.append(float(globTICurr)/float(globSumCurr))
                    globpi.append(float(globPICurr)/float(globSumCurr))
                else:
                    print str(time)
                    print "shit"
                    globr.append(0.0)
                    globs.append(0.0)
                    globti.append(0.0)
                    globpi.append(0.0)
                
                
                globR.append(globRCurr)
                globS.append(globSCurr)
                globTI.append(globTICurr)
                globPI.append(globPICurr)
                globSum.append(globSumCurr)


    plt.figure(1)
    
    if not plotPIOnly:
        plt.plot(farmTimes, globs, label='S'+scenariotext)
    
    plt.plot(farmTimes, globti, label='TI'+scenariotext)
    plt.plot(farmTimes, globpi, label='PI'+scenariotext)
    if not plotPIOnly:
        plt.plot(farmTimes, globr, label='R'+scenariotext)
    plt.title('Global Endemic Behavior')
    plt.ylabel('fraction of each infection state')
    plt.xlabel('time in days')
    #plt.plot(farmTimes, globSum, label='Sum')
    plt.legend()
    figureName = "endemicFractions"
    
    #create a subplot showing the PI, TI prevalence
    if True and not plotPIOnly:
        plt.axes([0.3, 0.2,0.5,0.5])
        plt.plot(farmTimes, globti, 'g-'+scenariotext)
        plt.plot(farmTimes,globpi, 'r-'+scenariotext)

    plt.savefig(path+"/"+figureName+".png")
    #plt.clf()
    plt.figure(2)
    if not plotPIOnly:
        plt.plot(farmTimes, globS, label='S'+scenariotext)

    plt.plot(farmTimes, globTI, label='TI'+scenariotext)
    plt.plot(farmTimes, globPI, label='PI'+scenariotext)
    if not plotPIOnly:
        plt.plot(farmTimes, globR, label='R'+scenariotext)
        plt.plot(farmTimes, globSum, label='Sum'+scenariotext)
    plt.ylabel('absolute number of cows for each infection state')
    plt.xlabel('time in days')
    plt.legend()
    figureName = "totalEndemicNumbers"



    plt.savefig(path+"/"+figureName+".png")
    #   plt.show()
#plt.clf()
if len(sys.argv) < 2:
	print("you have to provide a filename")
	sys.exit(1)
filename = sys.argv[1]
doThePlot(filename)
