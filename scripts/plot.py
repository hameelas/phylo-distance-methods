import matplotlib.pyplot as plt
import numpy as np
import random
import collections


methods = [ "rapidnj", "fastme", "clearcut", "quicktree", "fast-nj"]



buckets = {}

batch_start, batch_end = 1, 751 # total
# batch_start, batch_end = 2, 151 # yule_deep
# batch_start, batch_end = 152, 301 # yule_recent
# batch_start, batch_end = 302, 451 # coalescent_low
# batch_start, batch_end = 452, 601 # coalescent_medium 
# batch_start, batch_end = 602, 751 # coalescent_high



fig = plt.figure()

plt.subplot(2, 1, 1)
ypoints_Max_dict = {}

for method in methods:
    print("Reading the data of %s..." % method)
    with open("results/%s" % method, 'r') as f:
        for raw_data in f.readlines():
            data = raw_data.strip().split()
            index, time = data[0], float(data[1])
            if batch_start > int(index) or int(index) > batch_end:
                continue
            with open("tests/%s.in" % index, 'r') as tf:
                n = int(tf.readline().strip())
                if not n in buckets.keys():
                    buckets[n] = []
                buckets[n].append(time)
    #x = list(map(int,line1.strip().split(' ')))
    #y = list(map(int,line2.strip().split(' ')))
    
    experiments_X = [10, 100, 1000]
    xpoints = np.array(experiments_X)

    experiments_Y_Mean = [ (sum(buckets[n]) / len(buckets[n])) for n in experiments_X ]
    experiments_Y_max = [ (max(buckets[n])) for n in experiments_X ]

    ypoints = np.array(experiments_Y_Mean)
    ypoints_Max = np.array(experiments_Y_max)
    ypoints_Max_dict[method]= ypoints_Max
    print (xpoints, ypoints)
   
    plt.plot(xpoints,ypoints, label= '{i}'.format(i=method))
plt.title('Total')
plt.ylabel('Mean')
plt.xscale("log")
plt.legend(loc='best')



plt.subplot(2, 1, 2)
for method in methods:
    ypoints_Max = ypoints_Max_dict[method]
    print (xpoints, ypoints_Max)
    plt.plot(xpoints,ypoints_Max, label= '{i}'.format(i=method))

plt.ylabel('Max')
plt.xscale("log")
plt.legend(loc='best')

plt.show()
