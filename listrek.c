#include <stdio.h>
#include <stdlib.h>
#include "listrek.h"
#include "boolean.h"

/* *** Manajemen Memori *** */
treeaddress Alokasi (treeinfotype X){
    treeaddress P=(treeaddress) malloc(sizeof(ElmtList));
	if(P!=TreeNil){
		Info(P)=X;
		Next(P)=TreeNil;
	}
	return P;
}
/* Mengirimkan treeaddress hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka treeaddress tidak TreeNil, dan misalnya menghasilkan P, 
  maka Info(P) = X, Next(P) = TreeNil */
/* Jika alokasi gagal, mengirimkan TreeNil */
void Dealokasi (treeaddress P){
    free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian treeaddress P */

/* *** Primitif-primitif yang harus direalisasikan *** */

/* Pemeriksaan Kondisi ListRek */
int ListRekIsEmpty(ListRek L){
    return (L == TreeNil);
}
/* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */
int IsOneElmt(ListRek L){
    return (NbElmtList(L) == 1);
}
/* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */

/* *** Selektor *** */
treeinfotype FirstElmt (ListRek L){
    return (Info(L));
}
/* Mengirimkan elemen pertama sebuah ListRek L yang tidak kosong */
ListRek ListRekTail(ListRek L){
    return (Next(L));
}
/* Mengirimkan ListRek L tanpa elemen pertamanya, mungkin menjadi ListRek kosong */

/* *** Konstruktor *** */
ListRek Konso(treeinfotype e, ListRek L){
    treeaddress P=Alokasi(e);
	if(P!=TreeNil){
		Next(P)=L;
		return P;
	} else {
		return L;
	}
}
/* Mengirimkan ListRek L dengan tambahan e sebagai elemen pertamanya. 
e dialokasi terlebih dahulu. Jika alokasi gagal, mengirimkan L. */
ListRek KonsB(ListRek L, treeinfotype e){
    treeaddress P=Alokasi(e),Pt=L;
	if(P!=TreeNil){
		if(Pt==TreeNil){
			return P;
		} else {
			while(Next(Pt)!=TreeNil){
				Pt=Next(Pt);
			}
			Next(Pt)=P;
		}
	}
	return L;		
}
/* Mengirimkan ListRek L dengan tambahan e sebagai elemen pertamanya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan L */ 

/* *** Operasi Lain *** */
ListRek Copy (ListRek L){
    if(ListRekIsEmpty(L)){
		return TreeNil;
	} else {
		return Konso(FirstElmt(L),Copy(ListRekTail(L)));
	}
}
/* Mengirimkan salinan ListRek L (menjadi ListRek baru) */
/* Jika ada alokasi gagal, mengirimkan L */ 
void MCopy (ListRek Lin, ListRek *Lout){
    ListRek LTemp;
	if(ListRekIsEmpty(Lin)){
		*Lout=TreeNil;
	} else {
		MCopy(ListRekTail(Lin),&LTemp);
		*Lout=Konso(FirstElmt(Lin),LTemp);
	}

}
/* I.S. Lin terdefinisi */
/* F.S. Lout berisi salinan dari Lin */
/* Proses : menyalin Lin ke Lout */
ListRek Concat (ListRek L1, ListRek L2){
    if (ListRekIsEmpty(L1)){
		return Copy(L2);
	} else {
		return Konso(FirstElmt(L1),Concat(ListRekTail(L1),L2));
	}
}
/* Mengirimkan salinan hasil konkatenasi ListRek L1 dan L2 (menjadi ListRek baru) */
/* Jika ada alokasi gagal, menghasilkan TreeNil */
void MConcat (ListRek L1, ListRek L2, ListRek *LHsl){
    ListRek LTemp;
	if(ListRekIsEmpty(L1)){
		*LHsl=Copy(L2);
	} else {
		MConcat(ListRekTail(L1),L2,&LTemp);
		*LHsl=Konso(FirstElmt(L1),LTemp);
	}
}
/* I.S. L1, L2 terdefinisi */
/* F.S. LHsl adalah hasil melakukan konkatenasi L1 dan L2 dengan cara "disalin" */
/* Proses : Menghasilkan salinan hasil konkatenasi ListRek L1 dan L2 */
void PrintList (ListRek L){
    /*if(!ListRekIsEmpty(L)){
		printf("%d\n", FirstElmt(L));
		PrintList(ListRekTail(L));
	}*/
}
/* I.S. L terdefinisi. */
/* F.S. Setiap elemen ListRek dicetak. */
int NbElmtList (ListRek L){
    if(ListRekIsEmpty(L)){
		return 0;
	} else {
		return 1+NbElmtList(ListRekTail(L));
	}
}
/* Mengirimkan banyaknya elemen ListRek L, Nol jika L kosong */
boolean Search (ListRek L, treeinfotype X){
    /*if(ListRekIsEmpty(L)){
		return false;
	} else {
		if(Info(L)==X){
			return true;
		} else {
			return Search(ListRekTail(L),X);
		}
	}*/
}
/* Mengirim true jika X adalah anggota ListRek, false jika tidak */