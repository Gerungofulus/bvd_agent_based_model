#!/usr/bin/env python
#import plotGlobalEndemicBehaviour
import matplotlib.pyplot as plt
from BVDDataAnalyzer import outputSpec as outputSpec
import BVDDataAnalyzer
import numpy as np
import sys
import os


analyzer = BVDDataAnalyzer.Analyzer.SimulationAnalyzer(sys.argv[1])
breedData = analyzer.getBreedingDynamicsStats()
times, tradingAgeY,tradingAgeFemaleY,tradingAgeMaleY = analyzer.getTradingAgesStats()

path = analyzer.file.path

plt.figure(1)
plt.title("Breeding and trading dynamics of female cows in dependence of their age")
plt.xlabel("Age in days")
plt.ylabel("log(number of cows)")

print breedData

plt.semilogy(times[0:outputSpec.printTillAge-1], (breedData["cows"]["female"]["DEATH"]["y"]), label="age of female cows with natural death")
plt.semilogy(times[0:outputSpec.printTillAge-1], (breedData["cows"]["female"]["SLAUGHTER"]["y"]), label="age of female cows when slaughtered")

plt.semilogy(times[0:outputSpec.printTillAge-1], (tradingAgeFemaleY), label="age of female cows when traded")
plt.legend()
if not 'thisScen' in globals():
    thisScen = os.path.basename(path)

figureName = thisScen +"femaleDemography"
plt.yticks([10**i for i in range(6)],[10**i for i in range(6)])
plt.xticks([i*365 for i in range(21)])
plt.xlim([0, 15*365])
for label in plt.gca().get_xmajorticklabels():
    label.set_rotation(30)
    label.set_horizontalalignment("right")
plt.savefig(path+"/" + figureName+".png")


plt.figure(2)
plt.title("Breeding and trading dynamics of male cows in dependence of their age")
plt.xlabel("Age in days")
plt.ylabel("log(number of cows)")

plt.semilogy(times[0:outputSpec.printTillAge-1], (breedData["cows"]["male"]["DEATH"]["y"]), label="age of male cows with natural death")
plt.semilogy(times[0:outputSpec.printTillAge-1], (breedData["cows"]["female"]["SLAUGHTER"]["y"]), label="age of male cows when slaughtered")

plt.semilogy(times[0:outputSpec.printTillAge-1], (tradingAgeMaleY), label="age of male cows when traded")
plt.legend()
plt.legend()
plt.yticks([10**i for i in range(6)],[10**i for i in range(6)])
#plt.xticks([i*365 for i in range(21)],[str(i) + "a" for i in range(21)])
plt.xticks([i*365 for i in range(21)])
plt.xlim([0, 15*365])

figureName = thisScen +"maleDemography"

for label in plt.gca().get_xmajorticklabels():
    label.set_rotation(30)
    label.set_horizontalalignment("right")
plt.savefig(path+"/"+figureName+".png")

plt.show()

del analyzer
del tradingAgeMaleY
del tradingAgeFemaleY
del tradingAgeY
del times


