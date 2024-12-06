/*Ce programme simule un pendule élastique en utilisant la méthode RK4*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<math.h>

const int nEch=5;            //Nombre d'échantillon

//CONDITIONS INITILAES//

//Parametre du pendule
double l = 21.0;             //Longueur de départ
double l0 = 20.0;            //Longueur à vide
double teta =M_PI/2.0;        //Angle de départ en radians
double lptn = 0.0;           //Vitesse initiale de la masse sur Ur
double tetaptn = 0.0;        //Vitesse angulaire initiale sur Uteta
double g=9.81;               //Constante de gravitation
double m=6;                  //Masse du pendule
double k=2.0;                //Constante de raideur du ressort

//Parametres de temps

const double t0=0.0;          //Début de la simulation
const double tmax=100.0;     //Fin de la simulation
const int n=1000000.0;        //Nombre de points
const double dt=(tmax-t0)/n;  //Intervalle de temps
const int pas=100000;         //Intervalle de points

//Parametres de changement des conditions initiales par itérations

const double lDelta=0;     //Différence entre chaque simulation pour la longueur
const double tetaDelta=0.1;  //Différence entre chaque simulation pour l'angle
const double lptnDelta=0.0;     //Différence entre chaque simulation pour la vitesse de la masse sur Ur
const double tetaptnDelta=0.000;  //Différence entre chaque simulation la vitesse angulaire
const double kDelta=0;        //Différence entre chaque simulation pour la raideur

//CONDITIONS INITIALES//



//Fonction utile ||  Débogage//
void afficheTab2D(int n,int d,double tab[d][n]){
    
    printf("[");
    for(int i=0;i<n;i++){
        printf("[");
        for(int j=0;j<d;j++){
            printf("%e",tab[j][i]);
            if(i<n-1){
                printf(",");
            }
        }
        printf("]\n");
    }
    printf("]\n");
}
//Fonction utile ||  Débogage//



//PROGRAMME //

// fonction Y' qui donne la dérivé de Y
void f(double y[4], double dy[4]){
    dy[0]=y[1]*pow(y[2],2)+g*cos(y[3])-k/m*(y[1]-l0);
    dy[1]=y[0];
    dy[2]=-g*sin(y[3])/y[1]-2*y[0]*y[2]/y[1];
    dy[3]=y[2];
}


//RK4 adapté pour une matrice de 4 valeurs
void rk4(int nt,double t[nt],double y0[4],double** y) {
    y[0][0]=y0[0];
    y[0][1]=y0[1];
    y[0][2]=y0[2];
    y[0][3]=y0[3];
    
    double dt;
    double yp[4];
    double ytemp[4];

    for(int i=1;i<nt;i++){
        dt=t[i]-t[i-1];

        for(int j=0;j<4;j++){
            ytemp[j]=y[i-1][j];
            double k1,k2,k3,k4;

            f(ytemp,yp);
            k1=dt*yp[j];

            ytemp[j]=y[i-1][j]+k1/2.0;
            f(ytemp,yp);
            k2=dt*yp[j];

            ytemp[j]=y[i-1][j]+k2/2.0;
            f(ytemp,yp);
            k3=dt*yp[j];

            ytemp[j]=y[i-1][j]+k3;
            f(ytemp,yp);
            k4=dt*yp[j];

            y[i][j]=y[i-1][j]+(k1+2*k2+2*k3+k4)/6.0;
        }
    }
}


//Création d'un tableau de temps
void timeTab(int n,double t[n],int j){
    for(int i=0;i<n;i++){
        t[i]=i*dt+j*pas*dt+t0;
    }
}


//Fonction de création de nom de fichier
void nameCre(char c[][21], int n){
    for(int i=0; i<n; i++){
        sprintf(c[i], "trajRK4_%d.txt", i+1);
    }
}



int main(){
    
    char c[nEch][21];                   //Tableaux de mots
    nameCre(c,nEch);                    //Création des noms de fichier

    for(int i=0;i<nEch;i++){            //Boucle pour créer le nombre d'echantillon suffisant
        
        l+=lDelta;teta+=tetaDelta;lptn+=lptnDelta;tetaptn+=tetaptnDelta;k+=kDelta;
        
        FILE* ff=fopen(c[i],"w");       //Creation d'un fichier ou on ecrira les valeurs
        if (ff == NULL) {
            printf("Erreur d'ouverture du fichier\n");
            return 1;
        }
        
        int a=n/pas;                    //Répartition du nombre de points
        int r=n%pas;                    //printf("a=%i et r=%i\n",a,r);//DEBUG
       
        
        double y0[4]={lptn,l,tetaptn,teta};
        for(int i=0;i<a;i++){
            
            double* t=malloc(pas*sizeof(double));//Déclaration d'un tableau dynamique de temps
            timeTab(pas,t,i);
            
            double** y=(double**)malloc(pas*sizeof(double*));// Déclaration d'un tableau dynamique pour les valeurs
            for(int j=0;j<pas;j++){
                y[j]=(double*)malloc(4*sizeof(double));
            }
            
            
            rk4(pas,t,y0,y);
            
            for(int i=0;i<pas;i++){
                fprintf(ff,"%e\t\t%e\t\t%e\t\t%e\t\t%e\n",t[i],y[i][1],y[i][3],-m*g*y[i][1]*cos(y[i][3])+0.5*k*pow(y[i][1]-l0,2),0.5*m*(pow(y[i][0],2)+pow(y[i][1]*y[i][2],2)));
                /*if(y[i][1]>10e4 || y[i][3]>10e4){
                    printf("Erreur calcul");
                    return 0;
                }*/
            }
            y0[0]=y[pas-1][0];y0[1]=y[pas-1][1];y0[2]=y[pas-1][2];y0[3]=y[pas-1][3];
            
            for(int i=0;i<pas;i++){  //
                free(y[i]);          //
            }                        //Libération de la mémoire
            free(y);                 //
            free(t);                 //
        }
        
        if(r!=0){
            double* t=malloc(r*sizeof(double));             //Déclaration d'un tableau dynamique de temps
            timeTab(r,t,a);
            
            double** y=(double**)malloc(r*sizeof(double*)); // Déclaration d'un tableau dynamique pour les valeurs
            for(int j=0;j<r;j++){
                y[j]=(double*)malloc(4*sizeof(double));
            }
            
            rk4(r,t,y0,y);
            for(int i=0;i<r;i++){
                /*if(y[i][1]>10e4 || y[i][3]>10e4){
                    printf("Erreur calcul");
                    return 0;
                }*/
            }
            for(int i=0;i<pas;i++){  //
                free(y[i]);          //
            }                        //Libération de la mémoire
            free(y);                 //
            free(t);                 //
        }
        fclose(ff);
    }
}

