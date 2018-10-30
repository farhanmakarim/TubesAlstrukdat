#include <stdlib.h>
#include <stdio.h>
#include "listsirkuler.h"

const Kata EndUnit = {" ENDUNIT" , 7};
const Kata FUnit = {" Unit.txt", 8};

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyList (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
	return FirstList(L) == Nil;
}


/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyList (List *L)
/* I.S. L sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
	FirstList(*L) = Nil;
}


/****************** Manajemen Memori ******************/
address AlokasiUnit (Unit X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, NextList(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	address P = (address) malloc(sizeof(ElmtList));
	if(P!=Nil){
		InfoList(P) = X;
		NextList(P) = Nil;
	}
	return P;
}

void DealokasiList (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN List ******************/
address SearchPoint (List L, POINT X)
/* Mencari apakah ada elemen List dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
	address P;
	P = FirstList(L);
	while(NextList(P)!=FirstList(L) && !EQ(X,position(InfoList(P)))){
		P = NextList(P);
	}
	if(EQ(X,position(InfoList(P))))
		return P;
	else
		return Nil;
}


/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstList (List *L, Unit X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
	address P = AlokasiUnit(X);
	if(P!=Nil)
		InsertFirstList(L, P);
}

void InsVLastList (List *L, Unit X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen List di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
	address P = AlokasiUnit(X);
	if(P!=Nil)
		InsertLast(L, P);
}


/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstList (List *L, Unit * X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama List dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
	address P;
	DelFirstList(L, &P);
	*X = InfoList(P);
}

void DelVLast (List *L, Unit * X)
/* I.S. List tidak kosong */
/* F.S. Elemen terakhir List dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
	address P;
	DelLast(L, &P);
	*X = InfoList(P);
}


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstList (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
	address Q = FirstList(*L);
	if(IsEmptyList(*L)){
		FirstList(*L) = P;
		NextList(FirstList(*L)) = FirstList(*L);
	}
	else{
		while(NextList(Q) != FirstList(*L)){
			Q = NextList(Q);
		}
		NextList(P) = FirstList(*L);
		FirstList(*L) = P;
		NextList(Q) = FirstList(*L);
	}
	
}

void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
	address Q = FirstList(*L);
	if(IsEmptyList(*L)){
		FirstList(*L) = P;
		NextList(FirstList(*L)) = FirstList(*L);
	}
	else{
		while(NextList(Q) != FirstList(*L)){
			Q = NextList(Q);
		}
		NextList(Q) = P;
		NextList(P) = FirstList(*L);
	}
}

void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen List dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
	NextList(P) = NextList(Prec);
	NextList(Prec) = P;
}


/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstList (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama List sebelum penghapusan */
/*      Elemen List berkurang satu (mungkin menjadi kosong) */
/* FirstList element yg baru adalah suksesor elemen pertama yang lama */
{
	address Q = FirstList(*L);
	*P = Q;
	if(NextList(Q) == FirstList(*L)){
		CreateEmptyList(L);
	}
	else{
		while(NextList(Q) != FirstList(*L)){
			Q = NextList(Q);
		}
		FirstList(*L) = NextList(*P);
		NextList(Q) = FirstList(*L);
	}
}

void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir List sebelum penghapusan  */
/*      Elemen List berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
	address Q = FirstList(*L);
	*P = Q;
	if(NextList(Q) == FirstList(*L)){
		CreateEmptyList(L);
	}
	else{
		while(NextList(NextList(Q)) != FirstList(*L)){
			Q = NextList(Q);
		}
		*P = NextList(Q);
		NextList(Q) = FirstList(*L);
	}
}

void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota List  */
/* F.S. Menghapus NextList(Prec): */
/*      Pdel adalah alamat elemen List yang dihapus  */
{
	*Pdel = NextList(Prec);
	if(NextList(Prec) == FirstList(*L)){
		NextList(Prec) = NextList(FirstList(*L));
		FirstList(*L) = NextList(Prec);
	}
	else{
		NextList(Prec) = NextList(*Pdel);
	}
}

void DelP (List *L, Unit X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen List beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari List dan di-dealokasi */
/* Jika tidak ada elemen List dengan Info(P)=X, maka List tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
	address P= SearchPoint(*L, X.pos);

	if (P != Nil) {
		if (P == FirstList(*L)) {
			DelFirstList(L, &P);
		} else if (NextList(P) == FirstList(*L)) {
			DelLast(L, &P);
		} else {
			address Prec;
			Prec = FirstList(*L);

			while(NextList(Prec) != P) {
				Prec = NextList(Prec);
			}
			P = NextList(Prec);
			NextList(Prec) = NextList(P);
			NextList(P) = Nil;
		}
	}

}

void bacaunit(List *stdunit){
	const Kata King = {" King", 4};

	int i = 1;
	Unit Utemp;
	STARTKATA(true, FUnit);
	while(!EOP){
		if(!IsKataSama(CKata, EndUnit)){
			switch(i){
				case 1 : Utemp.type = CKata;
						 break;
				case 2 : Utemp.maxhealth = KatatoBilangan(CKata);
						 Utemp.currhealth = Utemp.maxhealth;
						 break;
				case 3 : Utemp.atkdmg = KatatoBilangan(CKata);
						 break;
				case 4 : Utemp.maxmove = KatatoBilangan(CKata);
						 if (IsKataSama(Utemp.type, King)) {
						 	Utemp.currmove = Utemp.maxmove;
						 } else {
						 	Utemp.currmove = 0;
						 }	 
						 break;
				case 5 : Utemp.atktype = CKata;
						 break;
				case 6 : Utemp.cost = KatatoBilangan(CKata);
						 break;
				case 7 : Utemp.heal = KatatoBilangan(CKata);
						 break;
				case 8 : Utemp.simbol = CKata.TabKata[1];
						 break;
				case 9 : Utemp.upkeepcost = KatatoBilangan(CKata);
						 break;
				case 10 : Utemp.deff = KatatoBilangan(CKata);
						  break;
				case 11 : Utemp.misschance = KatatoBilangan(CKata);
						  break;
			}
			i++;
		} else{
			Utemp.canatk = true;
			i=1;
			InsVLastList(stdunit, Utemp);
		}
		ADVKATA(true);
	}
}

void UpdateListMove(List *L, Unit *X, POINT PTujuan, boolean InVillage, MATRIKS Jarak) {
	address P;
	POINT PMAP;
	POINT PAwalMap;
	P = SearchPoint(*L, (*X).pos);

	PAwalMap = AksesMatriksUnit((*X).pos.X, (*X).pos.Y);

	if (InVillage) {
		InfoList(P).currmove = 0;
		(*X).currmove = 0;
	} else {
		PMAP = AksesMatriksUnit(PTujuan.X, PTujuan.Y);
		InfoList(P).currmove = InfoList(P).currmove - (abs(Elmt(Jarak, PMAP.X, PMAP.Y).kepemilikan - Elmt(Jarak, PAwalMap.X, PAwalMap.Y).kepemilikan));

		(*X).currmove = InfoList(P).currmove;		
	}

	InfoList(P).pos = PTujuan;
	

	(*X).pos = PTujuan;
}

void TulisListChangeUnit(List L) {
	address P;
	int i = 1;

	P = FirstList(L);

	printf("%d. ", i);
	PrintUnit(InfoList(P));
	printf("\n");

	P = NextList(P);
	i++;

	while(P != FirstList(L)) {
		printf("%d. ", i);
		PrintUnit(InfoList(P));
		printf("\n");
		i++;
		P = NextList(P);
	}
}

void TulisRecruitUnit(List L) {
	int i = 1;

	address P;

	P = FirstList(L);
	P = NextList(P);

	printf("%d.", i);
	PrintUnitRekrut(InfoList(P));
	printf("\n");
	i++;
	P = NextList(P);

	while (P != FirstList(L)) {
		printf("%d.", i);
		PrintUnitRekrut(InfoList(P));
		printf("\n");
		i++;
		P = NextList(P);
	}
}

void UpdateSelectedUnit(List L, int i, Unit *X) {
	address P = FirstList(L);
	int x = 1;

	while(x != i) {
		P = NextList(P);
		x++;
	}

	*X = InfoList(P);
}

void UpdateRecruit(List L, int i, Unit *SelectedUnitRecruit) {
	int x = 1;
	address P = FirstList(L);
	P = NextList(P);

	while(x != i) {
		P = NextList(P);
		x++;
	}

	*SelectedUnitRecruit = InfoList(P);
}

void Reset(List *L) {
	address P;

	P = FirstList(*L);

	while(NextList(P) != FirstList(*L)) {
		InfoList(P).currmove = InfoList(P).maxmove;
		InfoList(P).canatk = true;
		P = NextList(P);
	}
	InfoList(P).currmove = InfoList(P).maxmove;
	InfoList(P).canatk = true;	
}

void UpdateUnitAttack(int i, List L, Unit a, Unit *b, boolean *Retaliates) {
	const Kata Range = {" Range", 5};
	address P;

	if (i == 1) {
		POINT PAttack = a.pos;
		PAttack.X = PAttack.X - 1;
		P = SearchPoint(L, PAttack);

		*b = InfoList(P);
	} else if (i == 2) {
		POINT PAttack = a.pos;
		PAttack.Y = PAttack.Y - 1;
		P = SearchPoint(L, PAttack);

		*b = InfoList(P);
	} else if (i == 3) {
		POINT PAttack = a.pos;
		PAttack.Y = PAttack.Y + 1;
		P = SearchPoint(L, PAttack);

		*b = InfoList(P);
	} else if (i == 4) {
		POINT PAttack = a.pos;
		PAttack.X = PAttack.X + 1;
		P = SearchPoint(L, PAttack);

		*b = InfoList(P);
	}

	if (IsKataSama((*b).atktype, Range)) {
		*Retaliates = true;
	} else {
		if (IsKataSama(a.atktype, (*b).atktype)) {
			*Retaliates = true;
		} else {
			*Retaliates = false;
		}
	}
}

void UpdateUndo(List *L, Stack *S, Unit *X, MATRIKS *MAP, MATRIKS JARAK) {
	POINT PUndo;
	int i;
	int differ;

	if (IsEmptyStack(*S)) {
		printf("There is no Undo\n");
	} else {
		Pop(S, &PUndo);
		address P;
		POINT PMAP;
		POINT PUndoMap;

		PUndoMap = AksesMatriksUnit(PUndo.X, PUndo.Y);
		PMAP = AksesMatriksUnit((*X).pos.X, (*X).pos.Y);

		differ = abs(Elmt(JARAK, PMAP.X, PMAP.Y).kepemilikan - Elmt(JARAK, PUndoMap.X, PUndoMap.Y).kepemilikan);
		(*X).currmove += differ;

		PMAP = AksesMatriksUnit((*X).pos.X, (*X).pos.Y);

		Elmt(*MAP, PMAP.X, PMAP.Y).CC = ' ';
		i = Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan;
		Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan = 3;

		PMAP = AksesMatriksUnit((PUndo).X, (PUndo).Y);
		Elmt(*MAP, PMAP.X, PMAP.Y).CC = (*X).simbol;
		Elmt(*MAP, PMAP.X, PMAP.Y).kepemilikan = i;

		P = SearchPoint(*L, (*X).pos);
		InfoList(P).pos = PUndo;
		InfoList(P).currmove += differ;
		(*X).pos = PUndo; 
	}
}

void UpdateMage(List *L, MATRIKS MAP, int PlayerKe, int BarisR, int KolomR) {
	const Kata Mage = {" WhiteMage", 9};

	address P;
	address SampingMage;
	POINT Po;
	POINT PMAP;

	P = FirstList(*L);

	P = NextList(P);

	while(P != FirstList(*L)) {
		if (IsKataSama(InfoList(P).type, Mage)) {
			if (InfoList(P).pos.X > 0) {
				Po.X = InfoList(P).pos.X-1;
				Po.Y = InfoList(P).pos.Y;

				PMAP = AksesMatriksUnit(Po.X, Po.Y);

				if (Elmt(MAP, PMAP.X, PMAP.Y).kepemilikan == PlayerKe) {
					SampingMage = SearchPoint(*L, Po);
					if (InfoList(P).heal + InfoList(SampingMage).currhealth > InfoList(SampingMage).maxhealth) {
						InfoList(SampingMage).currhealth = InfoList(SampingMage).maxhealth;
					} else {
						InfoList(SampingMage).currhealth += InfoList(P).heal;
					}
				}
			}

			if (InfoList(P).pos.Y > 0) {
				Po.X = InfoList(P).pos.X;
				Po.Y = InfoList(P).pos.Y-1;

				PMAP = AksesMatriksUnit(Po.X, Po.Y);

				if (Elmt(MAP, PMAP.X, PMAP.Y).kepemilikan == PlayerKe) {
					SampingMage = SearchPoint(*L, Po);
					if (InfoList(P).heal + InfoList(SampingMage).currhealth > InfoList(SampingMage).maxhealth) {
						InfoList(SampingMage).currhealth = InfoList(SampingMage).maxhealth;
					} else {
						InfoList(SampingMage).currhealth += InfoList(P).heal;
					}
				}
			}

			if (InfoList(P).pos.X < BarisR - 1) {
				Po.X = InfoList(P).pos.X+1;
				Po.Y = InfoList(P).pos.Y;

				PMAP = AksesMatriksUnit(Po.X, Po.Y);

				if (Elmt(MAP, PMAP.X, PMAP.Y).kepemilikan == PlayerKe) {
					SampingMage = SearchPoint(*L, Po);
					if (InfoList(P).heal + InfoList(SampingMage).currhealth > InfoList(SampingMage).maxhealth) {
						InfoList(SampingMage).currhealth = InfoList(SampingMage).maxhealth;
					} else {
						InfoList(SampingMage).currhealth += InfoList(P).heal;
					}
				}
			}

			if (InfoList(P).pos.Y < KolomR - 1) {
				Po.X = InfoList(P).pos.X;
				Po.Y = InfoList(P).pos.Y+1;

				PMAP = AksesMatriksUnit(Po.X, Po.Y);

				if (Elmt(MAP, PMAP.X, PMAP.Y).kepemilikan == PlayerKe) {
					SampingMage = SearchPoint(*L, Po);
					if (InfoList(P).heal + InfoList(SampingMage).currhealth > InfoList(SampingMage).maxhealth) {
						InfoList(SampingMage).currhealth = InfoList(SampingMage).maxhealth;
					} else {
						InfoList(SampingMage).currhealth += InfoList(P).heal;
					}
				}
			}
		}

		P = NextList(P);
	}
}


void UpdateNextUnit(Unit *S, boolean *F, List L) {
	address P;
	address FindP;

	*F = false;

	P = SearchPoint(L, (*S).pos);

	FindP = NextList(P);

	while(FindP != P && !(*F)) {
		if (InfoList(FindP).currmove > 0 || InfoList(FindP).canatk) {
			*F = true;
			*S  = InfoList(FindP);
		} else {
			FindP = NextList(FindP);
		}
	}
}