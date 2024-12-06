import matplotlib.pyplot as plt
import numpy as np


for i in range(#nbre de fichier texte crée en C  pour montrer le charactère chaotique
4):
    a="trajRK4_"+str(i+1)+".txt"
    tab = np.loadtxt(a)

    x = tab[:, 1] * np.sin(tab[:, 2])
    y = -tab[:, 1] * np.cos(tab[:, 2])
    plt.xlim(xmin=-50, xmax=50)
    plt.ylim(ymin=-50, ymax=50)
    plt.plot(x,y,linestyle='-')
plt.title("Méthode RK4")
plt.xlabel('X')
plt.ylabel('Y')
plt.show()
