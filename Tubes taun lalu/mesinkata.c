#include "mesinkata.h"
#include "mesinkar.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank(boolean bacafile)
{
	while((CC==NEWLINE||CC==BLANK)&&CC!=MARK){
		if(bacafile)
			ADVFILE();
		else
			ADVCLI();
	}
}

void STARTKATA(boolean bacafile, Kata File)
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
	if(bacafile){
		char temp[50];
		KatatoArrChar(File, temp);
		STARTFILE(temp);
	}
	else
		STARTCLI();
	IgnoreBlank(bacafile);
	EndKata = CC==MARK;
	if(!EndKata)
		SalinKata(bacafile);
}

void ADVKATA(boolean bacafile)
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
	IgnoreBlank(bacafile);
	EndKata = CC==MARK;
	if(!EndKata){
		SalinKata(bacafile);
	}
}

void SalinKata(boolean bacafile)
{
	int i;
	for(i=1;i<=NKMax && (CC!=MARK&&CC!=BLANK&&CC!=NEWLINE);i++){
		CKata.TabKata[i]=CC;
		if(bacafile)
			ADVFILE();
		else
			ADVCLI();
	}
	CKata.Length = i-1;
}


boolean IsKataSama(Kata K1, Kata K2){
	int i;
	for(i = 1;i<=K1.Length&&i<=K2.Length;i++){
		if(K1.TabKata[i] != K2.TabKata[i])
			return false;
	}
	return K1.Length == K2.Length;
}

boolean IsBilangan(Kata K){
	int i;
	for(i=1;i<=K.Length;i++){
		if(K.TabKata[i]<'0' || K.TabKata[i]>'9')
			return false;
	}
	return K.Length>0;
}

int KatatoBilangan(Kata K){
	int n=0,i;
	for(i=1;i<=K.Length;i++){
		n=n*10+K.TabKata[i]-'0';
	}
	return n;
}

void PrintKata(Kata K){
	int i;
	for(i=1;i<=K.Length;i++)
		printf("%c",K.TabKata[i]);
}

void InputString(Kata *K) {
	int i = 1;
	char c;

	scanf("%c", &c);

	while(c != '\n') {
		(*K).TabKata[i] = c;
		i++;
		scanf("%c", &c);
	}
	i--;
	(*K).Length = i;
}

void KatatoArrChar(Kata File, char* temp){
	int i=0;
	for(i=0;i<File.Length;i++){
		temp[i] = File.TabKata[i+1];
	}
	temp[i]='\0';
}
