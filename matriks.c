/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */
/*
#ifndef MATRIKS_H
#define MATRIKS_H

#include "boolean.h"

/* Ukuran minimum dan maksimum baris dan kolom */
/*
#define BrsMin 1
#define BrsMax 100
#define KolMin 1
#define KolMax 100

typedef int indeks{} /* indeks baris, kolom */
/*typedef int MatrixElType{} 
typedef struct { 
	MatrixElType Mem[BrsMax+1][KolMax+1]{}
    int NBrsEff{} /* banyaknya/ukuran baris yg terdefinisi */
//	int NKolEff{} /* banyaknya/ukuran kolom yg terdefinisi */
//} MATRIKS{} */
/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

#include <stdio.h>
#include "matriks.h"


/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
} 
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor "DUNIA MATRIKS" *** */
boolean MatrixIsIdxValid (int i, int j){
	return ((i >= BrsMin && i <= BrsMax) && (j >= KolMin && j <= KolMax));
}
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M){
	return BrsMin;
}
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (MATRIKS M){
	return KolMin;
}
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (MATRIKS M){
	return NBrsEff(M);
}
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (MATRIKS M){
	return NKolEff(M);
}
/* Mengirimkan indeks kolom terbesar M */
boolean MatrixIsIdxEff (MATRIKS M, indeks i, indeks j){
	return ( ( i>= BrsMin) && (i <= NBrsEff(M)) && (j >= KolMin) && (j<= NKolEff(M)) );
}
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
MatrixElType GetElmtDiagonal (MATRIKS M, indeks i){
	return MatrixElmt(M,i,i);
}
/* Mengirimkan elemen M(i,i) */

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl){
	//KAMUS LOKAL
	int i, j;
	
	//ALGORITMA
	MakeMATRIKS(NBrsEff(MIn),NKolEff(MIn),&(*MHsl));
	for (i=BrsMin;i<=NBrsEff(MIn);i++)
	{
		for(j=KolMin;j<=NKolEff(MIn);j++)
		{
			MatrixElmt(*MHsl,i,j) = MatrixElmt(MIn,i,j);
		}
	}
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQMATRIKS (MATRIKS M1, MATRIKS M2){
	//KAMUS LOKAL
	int i,j;
	boolean found = false;
	
	//ALGORITMA
	if ( (NBrsEff(M1) != NBrsEff(M2)) || (NKolEff(M1) != NKolEff(M2)) ){
        return false;
     }
     else if ( (GetFirstIdxBrs(M1) != GetFirstIdxBrs(M2)) || (GetLastIdxKol(M1) != GetLastIdxKol(M2)) ){
        return false;
     }
     else{
        for (i = BrsMin; i <= NBrsEff(M1); i++){
            for (j = KolMin; j <= NKolEff(M1); j++){

                if ( MatrixElmt(M1, i, j) != MatrixElmt(M2, i, j) ){
                    return false;
                }
            }
        }
     }

     return true;
}
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
boolean NEQMATRIKS (MATRIKS M1, MATRIKS M2){
	return !(EQ(M1,M2));
}
/* Mengirimkan true jika M1 tidak sama dengan M2 */
boolean EQSize (MATRIKS M1, MATRIKS M2){
	return ( (NBrsEff(M1) == NBrsEff (M2)) && (NKolEff (M1) == NKolEff (M2)) );
}
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M){
	return (NBrsEff(M)*NKolEff(M));
}
/* Mengirimkan banyaknya elemen M */

/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M){
	return (NBrsEff(M) == NKolEff(M));
}
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
boolean IsSimetri (MATRIKS M){
	indeks i, j;

    if (!(IsBujurSangkar(M))){
        return false;
    }
    else {
        for (i = BrsMin; i <= NBrsEff(M); i++){
            for (j = KolMin; j <= NKolEff(M); j++){
                if (MatrixElmt(M, i, j) != MatrixElmt(M, j, i)){
                    return false;
                }
            }
        }
    }
    return true;
}
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
boolean IsSatuan (MATRIKS M){
	indeks i, j;

    if (!(IsBujurSangkar(M))){
        return false;
    }
    else {
        for (i = BrsMin; i <= NBrsEff(M); i++){
            for (j = KolMin; j <= NKolEff(M); j++){
                if (i == j){
                    if (MatrixElmt(M, i, j) != 1 ){
                        return false;
                    }
                }
                else{
                    if (MatrixElmt(M, i, j) != 0 ){
                        return false;
                    }
                }

            }
        }
    }

    return true;
}
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */ 
boolean IsSparse (MATRIKS M){
	indeks i,j;
    int counter = 0;
    int limit = NBrsEff(M) * NKolEff(M) * 0.05;

    for (i = BrsMin; i <= NBrsEff(M); i++){
            for (j = KolMin; j <= NKolEff(M); j++){
                if (MatrixElmt(M, i, j) != 0){
                    counter += 1;
                }
            }
        }
    return (counter <= limit);
}

/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
void Transpose (MATRIKS * M){
	MatrixElType temp;
    indeks i,j;

    for (i = BrsMin; i <= NBrsEff(*M); i++){
		for (j = i; j <= NKolEff(*M); j++){
			temp = MatrixElmt(*M, i, j);
			MatrixElmt(*M, i, j) = MatrixElmt(*M, j, i);
			MatrixElmt(*M, j, i) = temp;
		}
	}
}
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
