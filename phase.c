
#include "phase.h"

t_move proba(int val){

    if (val<22) return F_10;
    else if (val<37) return F_20;
    else if (val<44) return F_30;
    else if (val<51) return B_10;
    else if (val<72) return T_LEFT;
    else if (val<93) return T_RIGHT;
    else return U_TURN;

}

void tirage(t_move L_move[]){
    int val;
    srand(time(NULL));
    for (int i=0;i<8;i++)
    {
        val = rand() %100;
        L_move[i] = proba(val);
    }
}
