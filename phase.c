
#include "phase.h"
#include <time.h>

int L_proba[] = {22,15,7,7,21,21,7};

t_move proba(int val, int *LProba){

    t_move L_move[] = {F_10,F_20,F_30,B_10,T_LEFT,T_RIGHT,U_TURN};
    int sum = LProba[0];
    for (int i=0;i<7;i++){
        if (val<sum) {
            LProba[i]-=1;
            return L_move[i];
        }
        else sum+=LProba[i + 1];
    }
}

void tirage(t_move L_move[]){
    int val;
    srand(time(NULL));
    for (int i=0;i<9;i++)
    {
        val = rand() %(100-i);
        L_move[i] = proba(val, L_proba);
    }
}
