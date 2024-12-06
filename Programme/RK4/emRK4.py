import matplotlib.pyplot as plt
import numpy as np


for i in range(#nbre de fichier texte crée en C  pour montrer le charactère chaotique
4):
    a="trajRK4_"+str(i+1)+".txt"
    tab = np.loadtxt(a)

    x = tab[:,0]
    y = tab[:,3]+tab[:,4]
    y1 = tab[:,3]
    y2 = tab[:,4]
    plt.plot(x,y,linestyle='-',label='Energie méchanique')
    #plt.plot(x,y1,linestyle='-',label='Energie potentielle')
    #plt.plot(x,y2,linestyle='-',label='Energie cinétique')

plt.title("Energie mécanique")
plt.xlabel('temps')
plt.ylabel('Energie')
plt.show()

