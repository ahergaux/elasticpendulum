import matplotlib.pyplot as plt
import numpy as np
import math as math



euler=np.loadtxt("/Users/g0lil1e/Library/Mobile Documents/com~apple~CloudDocs/ÉTUDES/EIDD/1A/MéthodesNumériques/Projet/Programme/Euler/trajEulermalloc1.txt")
rk4=np.loadtxt("trajRK4malloc1.txt")

x1 = euler[:,1]*np.sin(euler[:,2])
y1 = -euler[:,1]*np.cos(euler[:,2])
x2 = rk4[:,1]*np.sin(rk4[:,2])
y2 = -rk4[:,1]*np.cos(rk4[:,2])

t=euler[:,0]

delta=np.sqrt((x1-x2)**2+(y1-y2)**2)

plt.plot(t,delta,linestyle='dotted')
plt.title("Différence entre les méthodes")
plt.xlabel('Temps')
plt.ylabel('Erreur Relative')
plt.show()

