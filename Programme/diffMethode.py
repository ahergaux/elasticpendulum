import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation


fig, axs = plt.subplots(1, 2)

tab1 = np.loadtxt("trajEuler1.txt")
tab2 = np.loadtxt("trajRK4_1.txt")

x1 = tab1[:,1]*np.sin(tab1[:,2])
y1 = -tab1[:,1]*np.cos(tab1[:,2])
x2 = tab2[:,1]*np.sin(tab2[:,2])
y2 = -tab2[:,1]*np.cos(tab2[:,2])
    
    
axs[0].plot(x1[:100000],y1[:100000],linestyle='-')
axs[1].plot(x1[-100000:],y1[-100000:],linestyle='-')
axs[0].plot(x2[:100000],y2[:100000],linestyle='-')
axs[1].plot(x2[-100000:],y2[-100000:],linestyle='-')
axs[0].set_title(f"100 000 premiers points")
axs[1].set_title(f"100 000 derniers points")
axs[0].set_xlabel('X')
axs[1].set_xlabel('X')
axs[0].set_ylabel('Y')


fig.suptitle("Différence entre La méthode Euler et RK4")
plt.show()


