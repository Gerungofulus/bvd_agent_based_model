#!/usr/bin/env python
from csvTools import getColumn
from csvTools import plotCSVFile
import glob
import numpy as np
import matplotlib.pyplot as plt
import sys
csvdirectoryName = sys.argv[2]
csvFileList = glob.glob(csvdirectoryName +"*.csv")
csvFileList += glob.glob(csvdirectoryName +"*.Csv")
i = 1
print(csvdirectoryName)
print(len(csvFileList))
for myFile in csvFileList:
	plt.figure(i)
	plotCSVFile(myFile,False)
	plt.title(myFile)
	i += 1
	
plt.show()
