#include "matriks.h"
#include "pcolor.h"
#include "point.h"
#include "listsirkuler.h"
#include "queuepoint.h"

#ifndef MAP_H
#define MAP_H

void CreateMap(int m, int n, MATRIKS* M);
/* Untuk membuat map Awal */

void PrintMap(int m, int n, MATRIKS M);
/* Untuk Mencetak Map */

void convertIndex (int *m, int *n);
/* Untuk mengkonvert indeks */

void RecruitMap(int m, int n, MATRIKS *M, int x);

void UpdateMoveMAP(MATRIKS *MAP, MATRIKS *JARAK, Unit X, int player, int BarisR, int KolomR);

void CopyMap(MATRIKS Min, MATRIKS *Mout);

void PrintAttack(int i, List L, Unit X, MATRIKS MAP, int PosAttack[], boolean *CanAttack, int BarisR, int KolomR);

#endif
