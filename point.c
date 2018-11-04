/* File: point.h */
/* Tanggal: 28 Agustus 2016 */
/* *** Definisi ABSTRACT DATA TYPE POINT *** */
#include "point.h"
#include <stdio.h>
#include <stdlib.h>

/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y){
/* Membentuk sebuah POINT dari komponen-komponennya */
	POINT P;
	Absis(P)=X;
	Ordinat(P)=Y;
	return P;
}


/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2){
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
	return (Absis(P1)==Absis(P2)) && (Ordinat(P1)==Ordinat(P2));
}
boolean NEQ (POINT P1, POINT P2){
/* Mengirimkan true jika P1 tidak sama dengan P2 */
	return (!EQ(P1,P2));
}

/* *** Kelompok menentukan di mana P berada *** */
boolean IsOrigin (POINT P){
/* Menghasilkan true jika P adalah titik origin */
	return EQ(P,MakePOINT(0,0));
}
boolean IsOnSbX (POINT P){
/* Menghasilkan true jika P terletak Pada sumbu X */
	return (Ordinat(P)==0);
}
boolean IsOnSbY (POINT P){
/* Menghasilkan true jika P terletak pada sumbu Y */
	return (Absis(P)==0);
}
int Kuadran (POINT P){
/* Menghasilkan kuadran dari P: 1, 2, 3, atau 4 */
/* Prekondisi : P bukan titik origin, */
/*              dan P tidak terletak di salah satu sumbu */
	if ((Absis(P)>0) && (Ordinat(P)>0)) {
		return 1;
	} else if ((Absis(P)<0) && (Ordinat(P)>0)) {
		return 2;
	} else if ((Absis(P)<0) && (Ordinat(P)<0)) {
		return 3;
	} else if ((Absis(P)>0) && (Ordinat(P)<0)) {
		return 4;
	} else {
		return 0;
	}
}
/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
POINT NextX (POINT P){
/* Mengirim salinan P dengan absis ditambah satu */              
	return MakePOINT(Absis(P)+1,Ordinat(P));
}
POINT NextY (POINT P){
/* Mengirim salinan P dengan ordinat ditambah satu */
	return MakePOINT(Absis(P),Ordinat(P)+1);	
}
POINT PlusDelta (POINT P, int deltaX, int deltaY){
/* Mengirim salinan P yang absisnya adalah Absis(P) + deltaX dan ordinatnya adalah Ordinat(P) + deltaY */
	return MakePOINT(Absis(P)+deltaX,Ordinat(P)+deltaY);
}
POINT MirrorOf (POINT P, boolean SbX){
/* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
/* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
/* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
	if (SbX) {
            if (Ordinat(P)!=0){
		return MakePOINT(Absis(P),Ordinat(P)*(-1));
            } else {
                return MakePOINT(Absis(P),Ordinat(P));
            }
	} else {
            if (Absis(P)!=0){
		return MakePOINT(Absis(P)*(-1),Ordinat(P));
            } else {
                return MakePOINT(Absis(P),Ordinat(P));
            }
	}
}

void Geser (POINT *P, int deltaX, int deltaY){
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
	*P = PlusDelta(*P,deltaX,deltaY);
}
void GeserKeSbX (POINT *P){
/* I.S. P terdefinisi */
/* F.S. P berada pada sumbu X dengan absis sama dengan absis semula. */
/* Proses : P digeser ke sumbu X. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (9,0) */
	*P = MakePOINT(Absis(*P),0);
}
void GeserKeSbY (POINT *P){
/* I.S. P terdefinisi*/
/* F.S. P berada pada sumbu Y dengan ordinat yang sama dengan semula. */
/* Proses : P digeser ke sumbu Y. */
/* Contoh : Jika koordinat semula (9,9), maka menjadi (0,9) */
	*P = MakePOINT(0,Ordinat(*P));
}
void Mirror (POINT *P, boolean SbX){
/* I.S. P terdefinisi */
/* F.S. P dicerminkan tergantung nilai SbX atau SbY */
/* Jika SbX true maka dicerminkan terhadap sumbu X */
/* Jika SbX false maka dicerminkan terhadap sumbu Y */
	*P = MirrorOf(*P,SbX);
}

