#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "map.h"
#include "player.h"
#include "listsirkuler.h"
#include "stackpoint.h"
#include "math.h"

int Baris, Kolom, BarisR, KolomR;
Queue TurnPlayer;
int pilihanawal;
Queue PlayerTurn;
Player SelectedPlayer;
Unit SelectedUnit[3];
int PlayerKe = 1;
List ListUnitAwal;
List ListUnitPlayer[3];
Stack MoveUndo;
int banyakvillage;
int villageX;
int villageY;
boolean KingDEAD[3] = {false};
POINT Pvillage;
boolean FindNextUnit = false;
MATRIKS MAPASLI;
MATRIKS MAPCOPY;
MATRIKS JARAK;
int missatk;
boolean miss[3];

const Kata Recruit = {" RECRUIT", 7};
const Kata Change_Unit = {" CHANGE_UNIT", 11};
const Kata Info = {" INFO", 4};
const Kata Attack = {" ATTACK", 6};
const Kata Map = {" MAP", 3};
const Kata Next_Unit = {" NEXT_UNIT", 9};
const Kata Kosong = {" ", 0};
const Kata Move = {" MOVE", 4};
const Kata Undo = {" UNDO", 4};
const Kata EndT = {" ENDTURN", 7};
const Kata Exit = {" EXIT", 4};
const Kata Help = {" HELP", 4};

int main()
{
	printf("Masukkan Baris dan Kolom pada MAP : ");
	scanf("%d %d", &Baris, &Kolom);
	BarisR = Baris, KolomR = Kolom;
	MAPASLI.NBrsEff = BarisR;
	MAPASLI.NKolEff = KolomR;
	convertIndex(&Baris, &Kolom);
	CreateMap(Baris, Kolom, &MAPASLI);

	banyakvillage = ceil((float) BarisR/10) * ceil((float) KolomR/10);

	if (banyakvillage < 2) {
		banyakvillage = 2;
	}

	int getvillage = 0;

	while(getvillage != banyakvillage) {
		villageX = rand()%(BarisR-3) + 1;
		villageY = rand()%(KolomR/2) + 1;

		Pvillage = AksesMatriksUnit(villageX, villageY);

		if (Elmt(MAPASLI, Pvillage.X-1, Pvillage.Y).CC == ' ') {
			Elmt(MAPASLI, Pvillage.X-1, Pvillage.Y).CC = 'V';
			Elmt(MAPASLI, Pvillage.X-1, Pvillage.Y).kepemilikan = 3;
			getvillage++;
		}
	}

	getvillage = 0;

	while(getvillage != banyakvillage) {
		villageX = rand()%(BarisR-3) + 3;
		villageY = rand()%(KolomR/2) + KolomR/2 + 1;

		Pvillage = AksesMatriksUnit(villageX, villageY);

		if (Elmt(MAPASLI, Pvillage.X-1, Pvillage.Y).CC == ' ') {
			Elmt(MAPASLI, Pvillage.X-1, Pvillage.Y).CC = 'V';
			Elmt(MAPASLI, Pvillage.X-1, Pvillage.Y).kepemilikan = 3;
			getvillage++;
		}			
	}

	PrintMap(Baris, Kolom, MAPASLI);

	bacaunit(&ListUnitAwal);
	for(int i = 1; i <= 2; i++) {
		CreateEmptyList(&ListUnitPlayer[i]);
		InsVFirstList(&ListUnitPlayer[i], InfoList(FirstList(ListUnitAwal)));
	}

	InfoList(FirstList(ListUnitPlayer[1])).pos.X = BarisR-2;
	InfoList(FirstList(ListUnitPlayer[1])).pos.Y = 1;

	InfoList(FirstList(ListUnitPlayer[2])).pos.X = 1;
	InfoList(FirstList(ListUnitPlayer[2])).pos.Y = KolomR - 2;

	CreateEmptyStack(&MoveUndo);
	BacaPlayer(&PlayerTurn);
	boolean Main = true;
	boolean EndTurn = false;
	while(Main) {
		EndTurn = false;
		Del(&PlayerTurn, &SelectedPlayer);

		UpdateMage(&ListUnitPlayer[PlayerKe], MAPASLI, PlayerKe, BarisR, KolomR);

		for(int i = 1; i <= 2; i++) {
			SelectedUnit[i] = InfoList(FirstList(ListUnitPlayer[i]));
		}
		
		SelectedPlayer.gold += SelectedPlayer.income;
		SelectedPlayer.gold -= SelectedPlayer.upkeep;

		CreateEmptyStack(&MoveUndo);
		ResetMatriks(&JARAK, Baris, Kolom);

		while(!EndTurn) {
			PrintPlayer(SelectedPlayer);
			
			POINT PSelected;
			
			PrintMove(SelectedUnit[PlayerKe]);
			PSelected = AksesMatriksUnit(SelectedUnit[PlayerKe].pos.X, SelectedUnit[PlayerKe].pos.Y);

			Elmt(MAPASLI, PSelected.X, PSelected.Y).kepemilikan = 4;
			printf("\n");

			Kata pilihan;
			printf("Your Input : ");
			STARTKATA(false, Kosong);
			pilihan = CKata;

			if (!IsKataSama(pilihan, EndT)) {
				if (IsKataSama(pilihan, Move)) {
					CopyMap(MAPASLI, &MAPCOPY);
					UpdateMoveMAP(&MAPCOPY, &JARAK, SelectedUnit[PlayerKe], PlayerKe, BarisR, KolomR);

					int TujuanX, TujuanY;
					POINT PTujuan, PAsal;
					boolean InVillage = false;

					if (SelectedUnit[PlayerKe].currmove <= 0) {
						printf("Your ");
						PrintKata(SelectedUnit[PlayerKe].type);
						printf("'s cannot move\n");
					} else {
						PAsal.X = SelectedUnit[PlayerKe].pos.X;
						PAsal.Y = SelectedUnit[PlayerKe].pos.Y;
						PrintMap(Baris, Kolom, MAPCOPY);
						Push(&MoveUndo, PAsal);
						printf("Please enter cell's coordinate x y :");
						scanf("%d %d", &TujuanX, &TujuanY);
						PTujuan = AksesMatriksUnit(TujuanX, TujuanY);
						PAsal = AksesMatriksUnit(SelectedUnit[PlayerKe].pos.X, SelectedUnit[PlayerKe].pos.Y);
						
						while(Elmt(MAPCOPY, PTujuan.X, PTujuan.Y).CC != '?') {
							printf("You can't move there\n");
							printf("Please enter cell's coordinate x y :");
							scanf("%d %d", &TujuanX, &TujuanY);
							PTujuan = AksesMatriksUnit(TujuanX, TujuanY);
						}
							
						Elmt(MAPASLI, PTujuan.X, PTujuan.Y).CC = SelectedUnit[PlayerKe].simbol;
						Elmt(MAPASLI, PTujuan.X, PTujuan.Y).kepemilikan = PlayerKe;
						Elmt(MAPASLI, PAsal.X, PAsal.Y).CC = ' ';
						Elmt(MAPASLI, PAsal.X, PAsal.Y).kepemilikan = 3;
						
						if (Elmt(MAPASLI, PTujuan.X - 1, PTujuan.Y).CC == 'V' && Elmt(MAPASLI, PTujuan.X-1, PTujuan.Y).kepemilikan != PlayerKe) {
							if (Elmt(MAPASLI, PTujuan.X-1, PTujuan.Y).kepemilikan != 3) {
								Add(&PlayerTurn, SelectedPlayer);
								Del(&PlayerTurn, &SelectedPlayer);
								SelectedPlayer.income -= 10;
								Add(&PlayerTurn, SelectedPlayer);
								Del(&PlayerTurn, &SelectedPlayer);
							}
							CreateEmptyStack(&MoveUndo);
							ResetMatriks(&JARAK, Baris, Kolom);
							Elmt(MAPASLI, PTujuan.X-1, PTujuan.Y).kepemilikan = PlayerKe;
							SelectedPlayer.income += 10;
							InVillage = true;
						}

						PTujuan.X = TujuanX;
						PTujuan.Y = TujuanY;

						UpdateListMove(&ListUnitPlayer[PlayerKe], &SelectedUnit[PlayerKe], PTujuan, InVillage, JARAK);
						
						printf("\n");						
					}			
				} else if (IsKataSama(pilihan, Map)) {
					PrintMap(Baris, Kolom, MAPASLI);
					printf("\n");
				} else if (IsKataSama(pilihan, Change_Unit)) {
					int SelectChange;

					if (PlayerKe == 1) {
						Elmt(MAPASLI, PSelected.X, PSelected.Y).kepemilikan = 1;
					} else {
						Elmt(MAPASLI, PSelected.X, PSelected.Y).kepemilikan = 2;
					}

					printf("\n== List of Units ==\n");
					TulisListChangeUnit(ListUnitPlayer[PlayerKe]);
					printf("Please enter the no. of unit you want to select : ");
					scanf("%d", &SelectChange);
					UpdateSelectedUnit(ListUnitPlayer[PlayerKe], SelectChange, &SelectedUnit[PlayerKe]);

					printf("You are now selected ");
					PrintKata(SelectedUnit[PlayerKe].type);
					CreateEmptyStack(&MoveUndo);
					ResetMatriks(&JARAK, Baris, Kolom);
					printf("\n");
					printf("\n");
				} else if (IsKataSama(pilihan, Recruit)) {
					POINT SelectRecruit;
					POINT SelectRecruitMAP;
					Unit SelectedUnitRecruit;
					int SelectRecruitX;
					int SelectRecruitY;
					int NoRecruit;

					if (SelectedUnit[PlayerKe].simbol != 'K') {
						printf("\nYou're not choose King\n");	
					} else if (Elmt(MAPASLI, AksesMatriksUnit(SelectedUnit[PlayerKe].pos.X, SelectedUnit[PlayerKe].pos.Y).X-1, AksesMatriksUnit(SelectedUnit[PlayerKe].pos.X, SelectedUnit[PlayerKe].pos.Y).Y).CC != 'T'){
						printf("\nYour King is not in the tower\n");
						printf("\n");
					} else {
						printf("\nEnter coordinate of empty castle : ");
						scanf("%d %d", &SelectRecruitX, &SelectRecruitY);

						SelectRecruit = MakePOINT(SelectRecruitX, SelectRecruitY);
						SelectRecruitMAP = AksesMatriksUnit(SelectRecruit.X, SelectRecruit.Y);
						
						while(Elmt(MAPASLI, SelectRecruitMAP.X, SelectRecruitMAP.Y).CC != ' ' || Elmt(MAPASLI, SelectRecruitMAP.X-1, SelectRecruitMAP.Y).CC != 'C' || Elmt(MAPASLI, SelectRecruitMAP.X - 1, SelectRecruitMAP.Y).kepemilikan != PlayerKe) {
							printf("WRONG INPUT MAP\n");
							printf("\n");
							
							printf("Enter coordinate of empty castle : ");
							scanf("%d %d", &SelectRecruitX, &SelectRecruitY);

							SelectRecruit = MakePOINT(SelectRecruitX, SelectRecruitY);
							SelectRecruitMAP = AksesMatriksUnit(SelectRecruit.X, SelectRecruit.Y);
						}

						printf("\n== List of Recruits ==\n");
						TulisRecruitUnit(ListUnitAwal);

						printf("Enter no. of unit you want recruit: ");
						scanf("%d", &NoRecruit);

						UpdateRecruit(ListUnitAwal, NoRecruit, &SelectedUnitRecruit);

						if (SelectedPlayer.gold < SelectedUnitRecruit.cost) {
							printf("You dont have money\n");
						} else {
							SelectedUnitRecruit.pos.X = SelectRecruit.X;
							SelectedUnitRecruit.pos.Y = SelectRecruit.Y;

							InsVLastList(&ListUnitPlayer[PlayerKe], SelectedUnitRecruit);
							SelectedPlayer.gold -= SelectedUnitRecruit.cost;
							SelectedPlayer.upkeep += SelectedUnitRecruit.upkeepcost;

							Elmt(MAPASLI, SelectRecruitMAP.X, SelectRecruitMAP.Y).CC = SelectedUnitRecruit.simbol;
							Elmt(MAPASLI, SelectRecruitMAP.X, SelectRecruitMAP.Y).kepemilikan = PlayerKe;
							printf("You have recruited an ");
							PrintKata(SelectedUnitRecruit.type);
							printf("\n");
							printf("\n");	
						}					
					}		
				} else if (IsKataSama(pilihan, Info)) {
					POINT SelectedInfoMap;	
					POINT SelectedInfo;

					printf("Enter the coordinate of the cell : ");
					scanf("%d %d", &(SelectedInfo.X), &(SelectedInfo.Y));

					SelectedInfoMap = AksesMatriksUnit(SelectedInfo.X, SelectedInfo.Y);
					printf("== Cell Info ==\n");
					if (Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).CC == 'T') {
						printf("Tower\n");
						printf("Owned by Player %d\n", Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).kepemilikan);
						printf("\n");
					} else if (Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).CC == 'C') {
						printf("Castle\n");
						printf("Owned by Player %d\n", Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).kepemilikan);
						printf("\n");
					} else if (Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).CC == 'V') {
						printf("Village\n");
						if (Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).kepemilikan == 3) {
							printf("Don't Owned by Anyone\n");
						} else if (Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).kepemilikan == 2) {
							printf("Owned by Player %d\n", Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).kepemilikan);
						} else {
							printf("Owned by Player %d\n", Elmt(MAPASLI, SelectedInfoMap.X-1, SelectedInfoMap.Y).kepemilikan);
						}
						printf("\n");
					} else {
						printf("Normal\n");
					}

					printf("== Unit Info == \n");
					if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).CC == ' ') {
						printf("There's no Unit here\n");
					} else if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).CC == 'A') {
						printf("Archer\n");
						if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).kepemilikan != 4) {
							printf("Owned by Player %d\n", Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).kepemilikan);
						} else {
							printf("Owned by Player %d\n", PlayerKe);
						}
					} else if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).CC == 'K') {
						printf("King\n");
						if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).kepemilikan != 4) {
							printf("Owned by Player %d\n", Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).kepemilikan);
						} else {
							printf("Owned by Player %d\n", PlayerKe);
						}
					} else if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).CC == 'S') {
						printf("Swordsman\n");
						if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).kepemilikan != 4) {
							printf("Owned by Player %d\n", Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).kepemilikan);
						} else {
							printf("Owned by Player %d\n", PlayerKe);
						}
					} else if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).CC == 'W') {
						printf("White Mage\n");
						if (Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).kepemilikan != 4) {
							printf("Owned by Player %d\n", Elmt(MAPASLI, SelectedInfoMap.X, SelectedInfoMap.Y).kepemilikan);
						} else {
							printf("Owned by Player %d\n", PlayerKe);
						}
					}
					printf("\n");
				} else if (IsKataSama(pilihan, Attack)) {
					int pilihanAttack;
					int PosAttack[5];
					Unit SelectedUnitAttack;
					boolean Retaliates;
					boolean CantAttack = false;

					if (SelectedUnit[PlayerKe].canatk == false) {
						printf("Your ");
						PrintKata(SelectedUnit[PlayerKe].type);
						printf("'s cannot attack\n");
					} else {
						miss[1] = false;
						miss[2] = false;

						PrintAttack(PlayerKe, ListUnitPlayer[(PlayerKe%2)+1], SelectedUnit[PlayerKe], MAPASLI, PosAttack, &CantAttack, BarisR, KolomR);

						if (!CantAttack) {
							printf("Select enemy you want to attack : ");
							scanf("%d", &pilihanAttack);

							UpdateUnitAttack(PosAttack[pilihanAttack], ListUnitPlayer[(PlayerKe%2)+1], SelectedUnit[PlayerKe], &SelectedUnitAttack, &Retaliates);

							missatk = rand()%100;
							if (missatk <= SelectedUnitAttack.misschance) {
								printf("Your's ");
								PrintKata(SelectedUnit[PlayerKe].type);
								printf(" miss the attack\n");
								miss[1] = true;
							} else {
								printf("Enemy's ");
								PrintKata(SelectedUnitAttack.type);
								printf(" is damaged by ");
								printf("%d.\n", SelectedUnit[PlayerKe].atkdmg);
							}

							
							if (Retaliates) {
								missatk = rand()%100;
								printf("Enemy's ");
								PrintKata(SelectedUnitAttack.type);
								printf(" retaliates.\n");
								if (missatk <= SelectedUnit[PlayerKe].misschance) {
									printf("Enemy's ");
									PrintKata(SelectedUnit[PlayerKe].type);
									printf(" miss the attack\n");
									miss[2] = true;
								} else {				
									printf("Your ");
									PrintKata(SelectedUnit[PlayerKe].type);
									printf(" is damaged by ");
									printf("%d.\n", SelectedUnitAttack.atkdmg);	
								}
							}
							UpdateAttack(PlayerKe, &ListUnitPlayer[PlayerKe], SelectedUnit[PlayerKe], &ListUnitPlayer[(PlayerKe%2)+1], SelectedUnitAttack, Retaliates, &MAPASLI, KingDEAD, &PlayerTurn, &SelectedPlayer, miss);

							if (KingDEAD[PlayerKe]) {
								printf("\n");

								PrintKata(SelectedPlayer.name);
								printf("'s King is Dead\n");
								Main = false;
								EndTurn = true;

								Add(&PlayerTurn, SelectedPlayer);
								Del(&PlayerTurn, &SelectedPlayer);
								puts("");
								printf("Congratulation ");
								PrintKata(SelectedPlayer.name);
								printf("\n");	
							} else if (KingDEAD[PlayerKe%2 + 1]) {
								printf("\n");
								Add(&PlayerTurn, SelectedPlayer);
								Del(&PlayerTurn, &SelectedPlayer);
								PrintKata(SelectedPlayer.name);
								printf("'s King is Dead\n");
								Main = false;
								EndTurn = true;

								printf("\n");

								Add(&PlayerTurn, SelectedPlayer);
								Del(&PlayerTurn, &SelectedPlayer);
								printf("Congratulation ");
								PrintKata(SelectedPlayer.name);
								printf("\n");
							}	

							SelectedUnit[PlayerKe].canatk = false;
							CreateEmptyStack(&MoveUndo);
							ResetMatriks(&JARAK, Baris, Kolom);
						}							
					} 		
				} else if (IsKataSama(pilihan, Exit)) {
					Main = false;
					EndTurn = true;
				} else if (IsKataSama(pilihan, Undo)) {
					UpdateUndo(&ListUnitPlayer[PlayerKe],  &MoveUndo, &SelectedUnit[PlayerKe], &MAPASLI, JARAK);
					printf("\n");
				} else if (IsKataSama(pilihan, Help)) {
					puts("");
					puts("Command : ");
					puts("HELP : Untuk melihat command apa saja yang dapat dilakukan");
					puts("MOVE : Untuk Memindahkan Unit yang telah dipilih");
					puts("RECRUIT : Untuk membeli unit baru");
					puts("CHANGE_UNIT : Untuk merubah Unit yang mau dipilih");
					puts("ATTACK : Untuk menyerang unit lawan disekitarnya");
					puts("INFO : Untuk melihat info village dan unit di suatu petak");
					puts("ENDTURN : Untuk berhenti turn player");
					puts("UNDO : Untuk mengembalikan unit di posisi sebelumnya");
					puts("MAP : Untuk melihat kondisi map");
					puts("");					
				} else if (IsKataSama(pilihan, Next_Unit)) {
					UpdateNextUnit(&SelectedUnit[PlayerKe], &FindNextUnit, ListUnitPlayer[PlayerKe]);
					if (!FindNextUnit) {
						printf("There is no Unit with Movement Point or Can Attack\n");
					}
				} else {
					printf("\n");
					printf("MASUKAN SALAH\n");
					printf("\n");
				} 
			} else {
				Add(&PlayerTurn, SelectedPlayer);
				Reset(&ListUnitPlayer[PlayerKe]);
				if (PlayerKe == 1) {
					Elmt(MAPASLI, PSelected.X, PSelected.Y).kepemilikan = 1;
					PlayerKe = 2;
				} else {
					Elmt(MAPASLI, PSelected.X, PSelected.Y).kepemilikan = 2;
					PlayerKe = 1;
				}
				EndTurn = true;
			}
		}
	}
}
