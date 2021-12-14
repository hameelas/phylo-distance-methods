import matplotlib.pyplot as plt
import numpy as np
import random

cnt = 0
while True:
    cnt += 1
    line1 = input()
    if not line1:
        break
    line2 = input()

    x = list(map(int,line1.strip().split(' ')))
    y = list(map(int,line2.strip().split(' ')))

    xpoints = np.array(x)
    ypoints = np.array(y)

    plt.plot(xpoints,ypoints, color = random.choice(['r','g','b']))
print (cnt)
plt.show()
