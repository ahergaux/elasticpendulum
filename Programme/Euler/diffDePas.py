import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation



tab = np.loadtxt("trajEuler1.txt")
tab1 = np.loadtxt("trajEulermalloc1.txt")

x = tab[:,1]*np.sin(tab[:,2])
y = -tab[:,1]*np.cos(tab[:,2])
x1 = tab1[:,1]*np.sin(tab1[:,2])
y1 = -tab1[:,1]*np.cos(tab1[:,2])
plt.plot(x,y,linestyle='-',label="100 000 points")
plt.plot(x1,y1,linestyle='-', label="1 000 000 points")
plt.legend()
plt.title("Différence de pas entre 100 000 et 1 000 000 de points")
plt.xlabel('X')
plt.ylabel('Y')
plt.show()
