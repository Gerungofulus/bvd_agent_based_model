#!/usr/bin/env python
import matplotlib.pyplot as plt

import numpy as np
import sys
import csvTools


if len(sys.argv) < 2:
	print("you have to provide a filename")
	sys.exit(1)


fileName = sys.argv[1]

    
y, x = csvTools.getCSVValuesYNormalized(fileName)
plt.plot(x,y)
plt.show()
