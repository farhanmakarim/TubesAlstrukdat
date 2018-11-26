/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#include "mesinkata.h"

boolean EndKata;
Kata CKata;

void IgnoreBlank(){
	//ALGORITMA
	while((CC!=MARK) && (CC== BLANK))
	{
		ADV();
	}
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA(const char *filename){
	EndKata = false;
	START(filename);
	IgnoreBlank();
	ADVKATA();
}
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK{} 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA(){
	IgnoreBlank();
	if (CC == MARK)
	{
		EndKata = true;
	}
	else
	{
		SalinKata();
	}
}
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata(){
	int i = 0;
	
	while((CC!=BLANK)&&(CC!=MARK)&&(i<NMax)) {
		CKata.TabKata[i] = CC;
		
		ADV();
		++i;
		
	}
	CKata.TabKata[i] = '\0';
	
	CKata.Length = i;
}
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi{} 
          CC = BLANK atau CC = MARK{} 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
