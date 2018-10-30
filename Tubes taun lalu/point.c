#include <stdio.h>
#include "boolean.h"
#include "point.h"

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y)
/* Membentuk sebuah POINT dari komponen-komponennya */
{	//Kamus
	POINT P;
	//Algoritma
	Absis(P)=X;
	Ordinat(P)=Y;
	return P;
}

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */                
{	//Algoritma
	printf("(%d,%d)",Absis(P),Ordinat(P));	
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
{	//Algoritma
	return (Absis(P1)==Absis(P2))&&(Ordinat(P1)==Ordinat(P2));
}

boolean NEQ (POINT P1, POINT P2)
/* Mengirimkan true jika P1 tidak sama dengan P2 */
{	//Algoritma
	return !EQ(P1, P2);
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P)
/* Mengirim salinan P dengan absis ditambah satu */
{	//Algoritma
	Absis(P)+=1;
	return P;
}

POINT NextY (POINT P)
/* Mengirim salinan P dengan ordinat ditambah satu */
{	//Algoritma
	Ordinat(P)+=1;
	return P;
}

POINT PlusDelta (POINT P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
{	//Algoritma
	Absis(P)+=deltaX;
	Ordinat(P)+=deltaY;
	return P;
}

int Panjang (POINT P1, POINT P2)
/* Menghitung jarak antara 2 titik yaitu tiik P1 dan titik P2 */
{	//Kamus
	float Jx=Absis(P1)-Absis(P2), Jy=Ordinat(P1)-Ordinat(P2);
	//Algoritma
	return abs(Jx) + abs(Jy);
}

void Geser (POINT *P, int deltaX, int deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{	//Algoritma
	*P = PlusDelta(*P, deltaX, deltaY);
}