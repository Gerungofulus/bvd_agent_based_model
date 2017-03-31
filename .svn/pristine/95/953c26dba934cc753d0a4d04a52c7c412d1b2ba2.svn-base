#!/usr/bin/env python

import matplotlib.pyplot as plt
from BVDDataAnalyzer import outputSpec as outputSpec
import BVDDataAnalyzer
import numpy as np
import sys



analyzer = BVDDataAnalyzer.Analyzer.SimulationAnalyzer(sys.argv[1])

times, tradingAgeY,tradingAgeFemaleY,tradingAgeMaleY = analyzer.getTradingAgesStats()

path = analyzer.file.path



#logAges = [log(i, 10) for i in ageYAxis]
plt.figure(1)
plt.plot(times[0:outputSpec.printTillAge-1], tradingAgeY, label="age of cows when traded")
plt.title('age distribution of cows when traded in the simulation')
plt.xlabel('time in days')
plt.ylabel('number of cows')
plt.figure(2)
plt.plot(times[0:outputSpec.printTillAge-1], np.log10(tradingAgeY), label="age of cows when traded")
plt.title('logarithmic plot of the age distribution of cows when traded in the simulation')
plt.xlabel('time in days')
plt.ylabel('number of cows')
plt.show()
