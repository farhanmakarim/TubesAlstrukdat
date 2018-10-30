/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */
#include "matriks.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
    int i,j;
    for (i = 0; i <= MIn.NBrsEff; i++) {
        for (j = 0; j <= MIn.NKolEff; j++) {
            Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
        }
    }

    NBrsEff(*MHsl) = NBrsEff(MIn);
    NKolEff(*MHsl) = NKolEff(MIn);
}

POINT AksesMatriksUnit(int a, int b) {
    POINT P;

    P.X = 2+(a)*4;
    P.Y = 2+(b)*4;

    return P;
}

void ResetMatriks(MATRIKS *JARAK, int Baris, int Kolom) {
    for(int i = 0; i <= Baris; i++) {
        for(int j = 0; j <= Kolom; j++) {
            Elmt(*JARAK, i, j).kepemilikan = 0;
        }
    }
}