import matplotlib.pyplot as plt
import numpy as np
from matplotlib.animation import FuncAnimation


for i in range(#nbre de fichier texte crée en C  pour montrer le charactère chaotique
5):
    a="trajEuler"+str(i+1)+".txt"
    tab = np.loadtxt(a)

    x = tab[:, 1] * np.sin(tab[:, 2])
    y = -tab[:, 1] * np.cos(tab[:, 2])
    plt.plot(x,y,linestyle='-')
plt.title("Méthode Euler")
plt.xlabel('X')
plt.ylabel('Y')
plt.show()

