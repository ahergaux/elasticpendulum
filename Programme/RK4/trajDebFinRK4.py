import matplotlib.pyplot as plt
import numpy as np


fig, axs = plt.subplots(1, 2)



for i in range(5):
    a = "trajRK4_" + str(i + 1) + ".txt"
    tab = np.loadtxt(a)

    
    x = tab[:, 1] * np.sin(tab[:, 2])
    y = -tab[:, 1] * np.cos(tab[:, 2])
    
    axs[0].plot(x[:10000],y[:10000],linestyle='-')
    axs[1].plot(x[-10000:],y[-10000:],linestyle='-')
    axs[0].set_title(f"10 000 premiers points")
    axs[1].set_title(f"10 000 derniers points")
    axs[0].set_xlabel('X')
    axs[1].set_xlabel('X')
    axs[0].set_ylabel('Y')


fig.suptitle("Méthode RK4")
plt.show()

