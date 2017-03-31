#!/usr/bin/env python

import numpy as np
import csv
import csvTools
import sys
import matplotlib.pyplot as plt

from datetime import datetime

filename = './Statistiken_Cattle/Rinder-Statistiken/VerbleibdauerPI.csv'

results = csv.DictReader(open(filename),delimiter=";")
statidict = {}

def getDate(dateString):
    return  datetime.strptime(dateString, '%d.%m.%Y')

totalNumber = 0
statidict["unknown"] = []
for pi in results:
    status = pi['BVD_ERG']
    if not status in statidict:
        
        statidict[status] = []
    
    datDict = {}
    totalNumber += 1
    sex = pi['GESCHL']
    datDict["sex"] =  'male' if (sex == 'M') else 'female'
    try:
        
        birthdate = getDate(pi['GEB_DATR'])
        changedate = getDate(pi['BVD_BDAT'])
        endDate = getDate(pi['DAT_END'])



        timeBeforeTest = (changedate-birthdate).days
        timeBeforeRemoval = (endDate-changedate).days
        
        
        datDict["timeBeforeTest"] = timeBeforeTest
        datDict["timeBeforeRemoval"] = timeBeforeRemoval
        
        
        
        
    except ValueError:
        status = "unknown"

    statidict[status].append(datDict) #data that is basically irrelevant



for status in statidict:
    timesBeforeTest = []
    timesBeforeRemoval = []
    print "Status " + str(status) +":\t" + str(len(statidict[status])) + " / " + str(totalNumber)
    if status == "unknown":
        continue
    for piData in statidict[status]:
        timesBeforeTest.append(piData["timeBeforeTest"])
        timesBeforeRemoval.append(piData["timeBeforeRemoval"])
    #timesBeforeTest = statidict[status][:]["timeBeforeTest"]
    #timesBeforeRemoval = statidict[status][:]
    timesBeforeTestY, timesBeforeTestX = np.histogram(timesBeforeTest,bins=range(400))
    timesBeforeRemovalY, timesBeforeRemovalX = np.histogram(timesBeforeRemoval, bins=range(400))

    plt.figure(1)
    plt.plot(timesBeforeRemovalX[:len(timesBeforeRemovalX)-1],timesBeforeRemovalY, label="status "+ str(status))
    plt.title("Time between removal and last positive test")
    plt.xlabel("time in days")
    plt.ylabel("number of cows")
    plt.legend()

    plt.figure(2)
    plt.title("Time between last positive test and birth")
    plt.plot(timesBeforeTestX[:len(timesBeforeTestX)-1],timesBeforeTestY, label="status "+ str(status))
    plt.legend()
    plt.xlabel("time in days")
    plt.ylabel("number of cows")
plt.show()
