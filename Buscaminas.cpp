/*Santiago Echevarria*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
main (){
int i,j,k;
int dim,nbombas,nvisibles,nlibres;
int seguir=1,fi,co;
int A[100][100],VISIBLE[100][100];
cout<<"\n\n\tDimension: ";
cin>>dim;
cout<<"\n\tCantidad de bombas:";
cin>>nbombas;
nlibres=dim*dim-nbombas;
for(i=1;i<=nbombas;i++){
                        j=1+rand()%dim;
                        k=1+rand()%dim;
                        if(A[j][k]==9){i--;};
                        A[j][k]=9;
                        };
for(i=1;i<=dim;i++){
                    for(j=1;j<=dim;j++){
                                        if(A[i][j]!=9){
                                                       if(A[i-1][j-1]==9){A[i][j]++;};
                                                       if(A[i-1][j]  ==9){A[i][j]++;};
                                                       if(A[i-1][j+1]==9){A[i][j]++;};
                                                       if(A[i]  [j-1]==9){A[i][j]++;};
                                                       if(A[i]  [j+1]==9){A[i][j]++;};
                                                       if(A[i+1][j-1]==9){A[i][j]++;};
                                                       if(A[i+1][j]  ==9){A[i][j]++;};
                                                       if(A[i+1][j+1]==9){A[i][j]++;};
                                                       };
                                        };
                    };
while(seguir==1){
                 system("clear");
                 cout<<dim<<"x"<<dim<<" con "<<nbombas<<" bombas\t\tFaltan "<<nlibres-nvisibles<<" / "<<nlibres<<"\n\n\n\n\n\t";
                 k=(dim-(dim%10))/10;
                 for(i=1;i<=k;i++){cout<<"                   "<<i;};
                 cout<<"\n\t";
                 for(i=1;i<=dim;i++){cout<<" "<<i%10;};
                 cout<<endl<<endl;
                 for(i=1;i<=dim;i++){
                                     cout<<i<<"\t";
                                     for(j=1;j<=dim;j++){
                                                         cout<<" ";
                                                         if(VISIBLE[i][j]==1){
                                                                              if(A[i][j]==9){cout<<"*";}
                                                                              else if(A[i][j]==0){cout<<" ";}
                                                                              else{cout<<A[i][j];};
                                                                              }
                                                         else{cout<<"#";};
                                                         };
                                      cout<<endl;
                                      };
                 cout<<"\n\nFila ";
                 cin>>fi;
                 cout<<"Columna ";
                 cin>>co;
                 VISIBLE[fi][co]=1;
                 if(A[fi][co]==9){
                                  system("clear");
                                  cout<<"\n\t\tPERDISTE\n\n";
                                  seguir=0;
                                  };
                 for(k=0;k<=nlibres;k++){
                                         for(i=1;i<=dim;i++){
                                                             for(j=1;j<=dim;j++){
                                                                                 if(VISIBLE[i-1][j-1]==1 && A[i-1][j-1]==0){VISIBLE[i][j]=1;};
                                                                                 if(VISIBLE[i-1][j]  ==1 && A[i-1][j]  ==0){VISIBLE[i][j]=1;};
                                                                                 if(VISIBLE[i-1][j+1]==1 && A[i-1][j+1]==0){VISIBLE[i][j]=1;};
                                                                                 if(VISIBLE[i]  [j-1]==1 && A[i]  [j-1]==0){VISIBLE[i][j]=1;};
                                                                                 if(VISIBLE[i]  [j+1]==1 && A[i]  [j+1]==0){VISIBLE[i][j]=1;};
                                                                                 if(VISIBLE[i+1][j-1]==1 && A[i+1][j-1]==0){VISIBLE[i][j]=1;};
                                                                                 if(VISIBLE[i+1][j]  ==1 && A[i+1][j]  ==0){VISIBLE[i][j]=1;};
                                                                                 if(VISIBLE[i+1][j+1]==1 && A[i+1][j+1]==0){VISIBLE[i][j]=1;};
                                                                                 };
                                                             };
                                          };
                 nvisibles=0;
                 for(i=1;i<=dim;i++){
                                     for(j=1;j<=dim;j++){
                                                         if(VISIBLE[i][j]==1){nvisibles++;};
                                                         };
                                     };
                 if(nvisibles==nlibres){
                                        system("clear");
                                        cout<<"\n\n\n\t\tGANASTE\n\n\n";
                                        for(i=1;i<=dim;i++){
                                                            cout<<"\t";
                                                            for(j=1;j<=dim;j++){
                                                                                if(A[i][j]==9){cout<<"*";}
                                                                                else if(A[i][j]==0){cout<<" ";}
                                                                                else{cout<<A[i][j];};
                                                                                cout<<" ";
                                                                                };
                                                            cout<<endl;
                                                            };

                                        seguir=0;
                                        };
                 };
}



















