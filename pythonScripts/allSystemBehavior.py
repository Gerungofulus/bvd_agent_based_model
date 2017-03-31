#!/usr/bin/env python
import sys
import os
import plotGlobalEndemicBehaviour as analysisFile

thisDir = os.path.dirname(os.path.abspath(__file__))

filenames = []
thepath = "/Users/pascal/Coding/uni/Masterarbeit/Tests/results/finalcont/"
scen = "scen"
thisScen = scen
listfile = "/comp3.txt" #"/testing_list.txt"
scenariotext = " of scenario "
for i in range(5,7):
    thisScen = scen +str(i)
    filename = thepath + thisScen + listfile
    analysisFile.doThePlot(filename,scenariotext+str(i))


for i in range(5,7):
   thisScen = scen +str(i) + "b"
   filename = thepath + thisScen + listfile
   analysisFile.doThePlot(filename,scenariotext+str(i)+"b")


