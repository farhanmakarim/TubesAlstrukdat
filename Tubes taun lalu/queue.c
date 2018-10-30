#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

const Kata FPlayer = {" Player.txt", 10};
const Kata ENDPLAYER = {" EndPlayer", 9};

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return ((Head(Q) == 0) && (Tail(Q) == 0));
}
boolean IsFullQueue (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    return ((Head(Q) == 1) && (Tail(Q) == MaxEl(Q)));
}
int NBElmtQueue (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if (IsEmptyQueue(Q)) {
        return 0;
    } else if (Head(Q)>Tail(Q)) {
        return ((MaxEl(Q)-Head(Q)) + 1 + Tail(Q));
    } else {
        return (Tail(Q) - Head(Q) + 1);
    }
}
/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
    (*Q).T = (Player *) malloc ((Max+1) * sizeof(Player));
    if ((*Q).T != NULL) {
        MaxEl(*Q) = Max;
        Head(*Q) = 0;
        Tail(*Q) = 0;
    } else /* alokasi gagal */ {
        MaxEl(*Q) = 0;
    }
}
/* *** Destruktor *** */
void DeAlokasiQueue (Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    MaxEl(*Q) = 0;
    free((*Q).T);
}
/* *** Primitif Add/Delete *** */
void Add (Queue * Q, Player X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
    if (IsEmptyQueue(*Q)) {
        Head(*Q) = 1;
    }
    else if (Tail(*Q) == MaxEl(*Q)) {
        Tail(*Q) = 0;
    }
    Tail(*Q)++;
    Name(InfoTail(*Q)) = Name(X);
    Gold(InfoTail(*Q)) = Gold(X);
    Income(InfoTail(*Q)) = Income(X);
    Upkeep(InfoTail(*Q)) = Upkeep(X);
}

void Del (Queue * Q, Player * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = 0ai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
{
    Name(*X) = Name(InfoHead(*Q));
    Gold(*X) = Gold(InfoHead(*Q));
    Income(*X) = Income(InfoHead(*Q));
    Upkeep(*X) = Upkeep(InfoHead(*Q));

    if (Head(*Q)==Tail(*Q)) {
        Head(*Q)=0;
        Tail(*Q)=0;
    } else {
        Head(*Q)++;
    }
}

void Turn(Queue *Q, Player *X)
{
    Del(Q, X);
    Add(Q, *X);
}

void BacaPlayer(Queue *Q){
    int i = 1;
    CreateEmptyQueue(Q, 100);
    Player P;
    //CreateEmptyList(&(P.village));
    STARTKATA(true, FPlayer);
    while(!EOP){
        if(!IsKataSama(CKata, ENDPLAYER)){
            switch(i){
                case 1 : Name(P) = CKata;
                         break;
                case 2 : Gold(P) = KatatoBilangan(CKata);
                         break;
                case 3 : Income(P) = KatatoBilangan(CKata);
                         break;
                case 4 : Upkeep(P) = KatatoBilangan(CKata);
                         break;
            }
            i++;
        }
        else{
            i = 1;
            Add(Q, P);
        }
        ADVKATA(true);
    }
}

void UpdateAttack(int i, List *L, Unit X, List *LAttack, Unit XAttack, boolean Retaliates, MATRIKS *MAP, boolean KingDEAD[], Queue *PlayerTurn, Player *Selected, boolean miss[]) {
    address P;
    POINT PMAP;
    const Kata King = {" King", 4};

    P = SearchPoint(*LAttack, XAttack.pos);

    if (!miss[1]) {
        InfoList(P).currhealth -= X.atkdmg;        
    }

    if (InfoList(P).currhealth <= 0) {
        miss[2] = true;
        printf("Enemy's ");
        PrintKata(InfoList(P).type);
        if (IsKataSama(InfoList(P).type, King)) {
            KingDEAD[(i%2) + 1] = true;
        }
        printf(" is dead ._.\n");
        PMAP = AksesMatriksUnit(InfoList(P).pos.X, InfoList(P).pos.Y);
        Elmt(*MAP, PMAP.X, PMAP.Y).CC = ' ';
        Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan = 3;
        DelP(LAttack, InfoList(P));
        Add(PlayerTurn, *Selected);
        Del(PlayerTurn, Selected);
        (*Selected).upkeep -= InfoList(P).upkeepcost;
        Add(PlayerTurn, *Selected);
        Del(PlayerTurn, Selected);
    }

    if (Retaliates) {
        P = SearchPoint(*L, X.pos);
        
        if (!miss[2]) {
            InfoList(P).currhealth -= XAttack.atkdmg;
        }

        InfoList(P).canatk = false;
        if (InfoList(P).currhealth <= 0) {
            printf("Your's ");
            PrintKata(InfoList(P).type);
            printf(" is dead :(\n");
            if (IsKataSama(InfoList(P).type, King)) {
                KingDEAD[i] = true;
            }
            PMAP = AksesMatriksUnit(InfoList(P).pos.X, InfoList(P).pos.Y);
            Elmt(*MAP, PMAP.X, PMAP.Y).CC = ' ';

            Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan = 3;
            DelP(L, InfoList(P));
            (*Selected).upkeep -= InfoList(P).upkeepcost;
        }
    }
}