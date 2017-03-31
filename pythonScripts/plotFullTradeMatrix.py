#!/usr/bin/env python
import networkx as nx
import os
import sys
from matplotlib import pyplot, patches
import h5py as h5
import numpy as np
def draw_adjacency_matrix(G, node_order=None, partitions=[], colors=[]):
    """
        - G is a netorkx graph
        - node_order (optional) is a list of nodes, where each node in G
        appears exactly once
        - partitions is a list of node lists, where each node in G appears
        in exactly one node list
        - colors is a list of strings indicating what color each
        partition should be
        If partitions is specified, the same number of colors needs to be
        specified.
        """
    adjacency_matrix = nx.to_numpy_matrix(G, dtype=np.bool, nodelist=node_order)
    
    #Plot adjacency matrix in toned-down black and white
    fig = pyplot.figure(figsize=(5, 5)) # in inches
    pyplot.imshow(adjacency_matrix,
      cmap="Greys",
      interpolation="none")

      # The rest is just if you have sorted nodes by a partition and want to
      # highlight the module boundaries
    assert len(partitions) == len(colors)
    ax = pyplot.gca()
    for partition, color in zip(partitions, colors):
      current_idx = 0
      for module in partition:
          ax.add_patch(patches.Rectangle((current_idx, current_idx),
                                         len(module), # Width
                                         len(module), # Height
                                         facecolor="none",
                                         edgecolor=color,
                                         linewidth="1"))
          current_idx += len(module)

filenames = []
path = ""
listFile = '/Users/pascal/Coding/uni/Masterarbeit/testing_list.txt'
path = os.path.dirname(os.path.abspath(listFile))
with open(listFile) as f:
    filenames = f.readlines()
tradeMatriceList = []
ivar =  0
alltradeTimes = []
graphs = []
for h5file in filenames:
    f = h5.File((path+"/"+h5file).strip())
    ivar += 1
    try:
        h5tradeTimes = f['BVD_Trade_Times']
        tradeTimes = h5tradeTimes[:].astype(int)
        for time in tradeTimes:
            alltradeTimes.append(time)
            dataSetName = "Trades_t" + str(time)
            h5Matrix = f[dataSetName]
            intMatrix = np.matrix(h5Matrix[:,:].astype(int))
            
            if ivar % 2:
                tradeMatriceList.append(intMatrix)
        
        
#           img = pyplot.imshow(intMatrix, interpolation='nearest')
            #img.set_cmap('hot')
#pyplot.savefig(path + "/trading_"+str(time)+".png", bbox_inches='tight')
    except KeyError:
        pass
    f.close()


matArr = np.array(tradeMatriceList)

matsum = np.sum(matArr, axis=0)
fullGraph = nx.from_numpy_matrix(matsum)
draw_adjacency_matrix(fullGraph)
plt.show()




