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
/*typedef int ElType{} 
typedef struct { 
	ElType Mem[BrsMax+1][KolMax+1]{}
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
boolean IsIdxValid (int i, int j){
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
boolean IsIdxEff (MATRIKS M, indeks i, indeks j){
	return ( ( i>= BrsMin) && (i <= NBrsEff(M)) && (j >= KolMin) && (j<= NKolEff(M)) );
}
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
ElType GetElmtDiagonal (MATRIKS M, indeks i){
	return Elmt(M,i,i);
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
			Elmt(*MHsl,i,j) = Elmt(MIn,i,j);
		}
	}
}
/* Melakukan assignment MHsl  MIn */

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK){
	//KAMUS LOKAL
	int i,j;
	ElType temp;
	
	//ALGORTIMA
	MakeMATRIKS(NB,NK,&(*M));
	for (i=BrsMin;i<=NBrsEff(*M);i++)
	{
		for(j=KolMin;j<=NKolEff(*M);j++)
		{
			scanf("%d", &temp);
			Elmt(*M,i,j) = temp;
		}
	}
}
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
void TulisMATRIKS (MATRIKS M){
	indeks i, j;
     for (i = BrsMin; i <= NBrsEff(M); i++){
        for (j = KolMin; j <= NKolEff(M); j++){
            printf("%d",Elmt(M, i, j));

            if (j < NKolEff(M)) {
                printf(" ");
            }
            else if ((j = NKolEff(M)) && (i != NBrsEff(M)) ) {
                printf("\n");
            }
        }
    }
}
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2){
	//KAMUS LOKAL
	MATRIKS MHsl;
	int i,j;
	
	//ALGORITMA
	MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&MHsl);
	for (i=BrsMin;i<=NBrsEff(M1);i++)
	{
		for(j=KolMin;j<=NKolEff(M1);j++)
		{
			Elmt(MHsl,i,j) = Elmt(M1,i,j) + Elmt(M2,i,j);
		}		
	}
	return MHsl;
}
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */ 
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2){
	//KAMUS LOKAL
	MATRIKS MHsl;
	int i,j;
	
	//ALGORITMA
	MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&MHsl);
	for (i=BrsMin;i<=NBrsEff(M1);i++)
	{
		for(j=KolMin;j<=NKolEff(M1);j++)
		{
			Elmt(MHsl,i,j) = Elmt(M1,i,j) - Elmt(M2,i,j);
		}		
	}
	return MHsl;
}
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */ 
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2){
	//KAMUS LOKAL
	/*MATRIKS MHsl;
	int i,j,k;
	ElType sum;
	//while(true){}
	//ALGORITMA
	MakeMATRIKS(NBrsEff(M1),NKolEff(M2),&MHsl);
	for (i=BrsMin;i<=NBrsEff(MHsl);i++)
	{
		for(j=KolMin;j<=NKolEff(MHsl);j++)
		{
			sum = 0;
			for(k = KolMin;k<=NKolEff(M1);k++);
			{
				sum = sum + Elmt(M1,i,k)*Elmt(M2,k,j);
			}
			Elmt(MHsl,i,j) = sum;
		}		
	}
	return MHsl; */
	
	indeks i, j, k;
    ElType sum;
    MATRIKS MHsl;

    MakeMATRIKS(NBrsEff(M1), NKolEff(M2), &MHsl);

    for (i = BrsMin; i <= NBrsEff(MHsl); i++){
        for (j = KolMin; j <= NKolEff(MHsl); j++){

            sum = 0;
            for (k = KolMin; k <= NKolEff(M1) ; k++){
                sum += Elmt(M1,i,k) * Elmt(M2,k, j);
            }
            Elmt(MHsl, i, j) = sum;
        }
    }

    return MHsl;
}
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
MATRIKS KaliKons (MATRIKS M, ElType X){
	//KAMUS LOKAL
	MATRIKS MHsl;
	int i,j;
	
	//ALGORITMA
	MakeMATRIKS(NBrsEff(M),NKolEff(M),&MHsl);
	for (i=BrsMin;i<=NBrsEff(M);i++)
	{
		for(j=KolMin;j<=NKolEff(M);j++)
		{
			Elmt(MHsl,i,j) = Elmt(M,i,j) * X;
		}		
	}
	return MHsl;
}
/* Mengirim hasil perkalian setiap elemen M dengan X */
void PKaliKons (MATRIKS * M, ElType K){
	//KAMUS LOKAL
	int i,j;
	
	//ALGORITMA
	for (i=BrsMin;i<=NBrsEff(*M);i++)
	{
		for(j=KolMin;j<=NKolEff(*M);j++)
		{
			Elmt(*M,i,j) = Elmt(*M,i,j) * K;
		}		
	}
}
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2){
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

                if ( Elmt(M1, i, j) != Elmt(M2, i, j) ){
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
boolean NEQ (MATRIKS M1, MATRIKS M2){
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
                if (Elmt(M, i, j) != Elmt(M, j, i)){
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
                    if (Elmt(M, i, j) != 1 ){
                        return false;
                    }
                }
                else{
                    if (Elmt(M, i, j) != 0 ){
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
                if (Elmt(M, i, j) != 0){
                    counter += 1;
                }
            }
        }
    return (counter <= limit);
}
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */ 
MATRIKS Inverse1 (MATRIKS M){
	return KaliKons(M, -1);
}
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
float Determinan (MATRIKS M){
	int brsneff = NBrsEff(M);
    int kolneff = NKolEff(M);
    float Mcopy[brsneff+1][kolneff+1];

    indeks i, j;
    float det = 1;

    void swap_rows(float M[brsneff+1][kolneff+1], int a, int b, float * det){
    /* a dan b adalah baris yang akan ditukar */
        float Temp;
        indeks i;

        for (i = KolMin; i <= kolneff; i++){
            Temp = M[a][i];
            M[a][i] = M[b][i];
            M[b][i] = Temp;
        }

        *det = -(*det); /* setelah 2 baris ditukar, determinan menjadi -determinan */
    }

    void make_one(float M[brsneff+1][kolneff+1], int a, float * det){
    /* a,a adalah index element diagonal yang akan dibuat 1 */

        indeks i;
        int z = 1;

        float divider = M[a][a] ;

        /* tukar baris jika elemen diagonal determinannya sudah 0  */
        while ((divider == 0) && (a+z <= kolneff)){
            swap_rows(M, a, a+z, det);
            divider = M[a][a];
            z += 1;
        }

        if ((divider == 0) && (a+z > kolneff)){ /* matriks unsolvable */
            *det = 0;
            return;
        }

        for (i = a; i <= kolneff; i++){
            M[a][i]  = M[a][i]  / divider;
        }
        *det = *det * divider;
    }

    void make_zero(float M[brsneff+1][kolneff+1], int a){
    /* reduce column a to 0 */
        indeks i,j ;

        for (i = a+1; i <= brsneff; i++){
            for (j = kolneff; j >= a; j--){
                M[i][j] -= (M[i][a] * M[a][j] / M[a][a]);
            }
        }
    }



    /* copy matriks M ke matriks Mcopy */
    for (i = BrsMin; i <= brsneff; i++){
        for (j = KolMin; j <= kolneff; j++){
            Mcopy[i][j] = Elmt(M, i, j);
        }
    }

    /* untuk setiap kolom, lakukan operasi baris elementer */
    for (i = KolMin; i <= kolneff; i++){
        make_one(Mcopy,i, &det);  /* bagi Mcopy[i,i] sehingga menjadi 1 */


        if (det == 0){
            return 0.000000;
        }

        /*
        printf("\n\n");
        for (k = BrsMin; k <= brsneff; k++){
            for (j = KolMin; j <= kolneff; j++){
                printf("%.2f ",Mcopy[k][j]);
            }
            printf("\n");
        }*/

        make_zero(Mcopy,i); /* kurangi baris sisasnya hingga menjadi 0 */

        /*
        printf("\n\n");
        for (k = BrsMin; k <= brsneff; k++){
            for (j = KolMin; j <= kolneff; j++){
                printf("%.2f ",Mcopy[k][j]);
            }
            printf("\n");
        }
        */

    }
    return det;
}
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
void PInverse1 (MATRIKS * M){
	return PKaliKons(M, -1);
}
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
void Transpose (MATRIKS * M){
	ElType temp;
    indeks i,j;

    for (i = BrsMin; i <= NBrsEff(*M); i++){
		for (j = i; j <= NKolEff(*M); j++){
			temp = Elmt(*M, i, j);
			Elmt(*M, i, j) = Elmt(*M, j, i);
			Elmt(*M, j, i) = temp;
		}
	}
}
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */