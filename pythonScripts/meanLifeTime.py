#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import csvTools as readCSV
import os
import sys
from BVDDataAnalyzer import outputSpec as outputSpec
import BVDDataAnalyzer

analyzer = BVDDataAnalyzer.Analyzer.SimulationAnalyzer(sys.argv[1])
breedData = analyzer.getBreedingDynamicsStats()
path = analyzer.file.path


times = analyzer.times


femaleAgeHistY = breedData["cows"]["female"]["ages"]["y"]
femaleAgeHistX = breedData["cows"]["female"]["ages"]["x"]
firstCalvingTimeY = breedData["firstCalvingTimes"]["y"]
firstCalvingTimeX = breedData["firstCalvingTimes"]["x"]
maleAgeHistY = breedData["cows"]["male"]["ages"]["y"]
maleAgeHistX = breedData["cows"]["male"]["ages"]["x"]
intermediateCalvingTimesY = breedData["intermediateCalvingTimes"]["all"]["y"]
intermediateCalvingTimesX = breedData["intermediateCalvingTimes"]["all"]["x"]

props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
plotCSV = True
if not len(sys.argv) >= 2:
    plotCSV =  bool(sys.argv[2])



# reading csv values
withCSV = ""
if plotCSV:
    bvdMainPath = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    csvPath = bvdMainPath + "/Statistiken_Cattle/Rinder-Statistiken/"
    csvIntermediateCalvingTimesFileName = "Zwischenkalbezeit.Csv"
    csvFirstCalvingTimesFileName = "Erstkalbealter.Csv"

    intermediateCalvingTimesYCSV, intermediateCalvingTimesXCSV = readCSV.getCSVValuesYNormalized(csvPath+csvIntermediateCalvingTimesFileName)

    firstCalvingTimesYCSV, firstCalvingTimeXCSV = readCSV.getCSVValuesYNormalized(csvPath+csvFirstCalvingTimesFileName)
    withCSV = "withCSV"

    #create csv statistics
    muRealInterm, medianRealInterm, sigmaRealInterm = readCSV.getCSVStatistics(csvPath+csvIntermediateCalvingTimesFileName)
    muRealFirst, medianRealFirst,sigmaRealFirst =readCSV.getCSVStatistics(csvPath+csvFirstCalvingTimesFileName)

# normalizing histogram data
intermediateCalvingTimesYPeak = max(intermediateCalvingTimesY)
normalizedIntermediateCalvingTime = [float(i/intermediateCalvingTimesYPeak) for i in intermediateCalvingTimesY[0:outputSpec.plotMeanCalvingTimeTillAge-1].astype(float)]

firstCalvingTimeYPeak = max(firstCalvingTimeY)
normalizedFirstCalvingTime = [i/firstCalvingTimeYPeak for i in firstCalvingTimeY[0:outputSpec.plotFirstCalvingTimeTillAge-outputSpec.plotFirstCalvingTimeStartingAtAge-1].astype(float)]

maxFemaleAge = max(femaleAgeHistY)
femaleAgeNormal = [i/maxFemaleAge for i in femaleAgeHistY.astype(float)]

#extracting simulation statistics

muFirstInsem = breedData["firstCalvingTimes"]["mu"]
medianFirstInsem = breedData["firstCalvingTimes"]["median"]
sigmaFirstInsem = breedData["firstCalvingTimes"]["sigma"]

muIntermedCalving = breedData["intermediateCalvingTimes"]["all"]["mu"]
medianIntermedCalving = breedData["intermediateCalvingTimes"]["all"]["median"]
sigmaIntermedCalving = breedData["intermediateCalvingTimes"]["all"]["sigma"]

# starting plotting


#plot normaleized age histogram
plt.figure(1)
plt.plot(femaleAgeHistX[0:outputSpec.printTillAge-1],femaleAgeNormal, label="female simulation")

plt.title('normalized age distribution of dead female cows in the simulation')
plt.xlabel('time in days')
plt.ylabel('number of cows')
pltName = "normalizedFemaleAgeHistogram"
plt.savefig(path+"/"+pltName+withCSV+".png")
#plot age distribution
plt.figure(2)
plt.title('age distribution of dead female cows in the simulation')
plt.xlabel('time in days')
plt.ylabel('number of cows')
pltName = "femaleAgeHistogram"
plt.savefig(path+"/"+pltName+withCSV+".png")

plt.plot(times[0:outputSpec.printTillAge-1], np.log10(femaleAgeHistY), label="female simulation")
plt.legend()

#plot of intermediate calving

plt.figure(3)
plt.title('intermediate calving time')
plt.xlabel('time in days')
plt.ylabel('by maximum normalized number of cows')


plt.plot(intermediateCalvingTimesX[0:outputSpec.plotMeanCalvingTimeTillAge-1], normalizedIntermediateCalvingTime, label="simulation")

textstr = '$\mu_\mathrm{sim}=%.2f$\n$\mathrm{median_\mathrm{sim}}=%.2f$\n$\sigma_\mathrm{sim}=%.2f$'%(muIntermedCalving, medianIntermedCalving, sigmaIntermedCalving)
if plotCSV:
    plt.plot(intermediateCalvingTimesXCSV, intermediateCalvingTimesYCSV, label="HI Tier")
    textstr += '\n$\mu_\mathrm{HIT}=%.2f$\n$\mathrm{median_\mathrm{HIT}}=%.2f$\n$\sigma_\mathrm{HIT}=%.2f$'%(muRealInterm, medianRealInterm, sigmaRealInterm)

plt.text(1500., 0.55, textstr, fontsize=12,
         verticalalignment='top', bbox=props)
plt.legend()
pltName = "intermediateCalvingTimes"
plt.savefig(path+"/"+pltName+withCSV+".png")


#plot of male demography
plt.figure(4)
plt.title('age of male cows at point of death')
plt.plot(maleAgeHistX[0:outputSpec.printTillAge-1], maleAgeHistY, label="male")
plt.legend()
pltName = "maleAgeHistogram"
plt.savefig(path+"/"+pltName+withCSV+".png")
#plot of first calving time
plt.figure(5)
plt.title('first calving time')
plt.xlabel('time in days')
plt.ylabel('by maximum normalized number of cows')


plt.plot(firstCalvingTimeX[0:outputSpec.plotFirstCalvingTimeTillAge-outputSpec.plotFirstCalvingTimeStartingAtAge-1], normalizedFirstCalvingTime , label="simulation")

textstr = '$\mu_\mathrm{sim}=%.2f$\n$\mathrm{median_\mathrm{sim}}=%.2f$\n$\sigma_\mathrm{sim}=%.2f$'%(muFirstInsem, medianFirstInsem, sigmaFirstInsem)

if plotCSV:
    plt.plot(firstCalvingTimeXCSV, firstCalvingTimesYCSV, label ="HI Tier" )
    textstr += '\n$\mu_\mathrm{HIT}=%.2f$\n$\mathrm{median_\mathrm{HIT}}=%.2f$\n$\sigma_\mathrm{HIT}=%.2f$'%(muRealFirst, medianRealFirst, sigmaRealFirst)

plt.text(4200., 0.55, textstr,  fontsize=12,
         verticalalignment='top', bbox=props)
plt.legend()
pltName = "firstCalvingTimesNormal"
plt.savefig(path+"/"+pltName+withCSV+".png")


plt.show()
