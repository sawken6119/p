
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

t_move tirage(){
    int val;
    t_move L_move[8];
    for (int i=0;i<8;i++)
    {
        val = rand() %100;
        printf("%d ", val);
        L_move[i] = proba(val);
        afficher_move(L_move[i]);
    }
    return *L_move;
}