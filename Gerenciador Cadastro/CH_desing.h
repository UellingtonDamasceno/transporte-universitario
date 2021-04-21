#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include "CH_enum.h"

void barra_sup(int tamanho_x, int pula_linha);
void barra_inf(int tamanho_x, int pula_linha);
void novo_menu_item(int tamanho_x, char item[], int peso_item, int pula_linha);
void separa_itens(int tamanho_x, int pula_linha);
void menu_titulo(int tamanho_x, char titulo[], int pula_linha);
void pula_espaco(int tamanho_x, int pula_linha);
void op_ler();
void gotoxy(int x, int y);
void desenha_menu_turno(int pos_x, int pos_y, int menu_tamanho, int dia_semana);
void desenha_barras();
void set_cursor_visible(int visible);

void barra_sup(int tamanho_x, int pula_linha){
	setlocale(LC_ALL, "C");
	int i = 0;
	printf("\xC9");//Serve para desenhar um canto superior esquero.
	for(i = 0; i < tamanho_x+2; i++){
		printf("\xCD");
	}
	printf("\xBB");
	if(pula_linha == True)
		printf("\n");
}
//================================================================================================================================================================
void barra_inf(int tamanho_x, int pula_linha){
	setlocale(LC_ALL, "C");
	int i = 0;
	
	printf("\xC8");
	for(i = 0; i < tamanho_x+2; i++)
		printf("\xCD");
	printf("\xBC");
	if(pula_linha == True)
		printf("\n");
}

//==============================================================================================================================================================
void novo_menu_item(int tamanho_x, char item[], int peso_item, int pula_linha){
	int i, qtd_letras = 0;
	qtd_letras = strlen(item);

	if(peso_item >= 1000){
		printf("\n\nERRO - Peso do item '%s' esta muito alto!\n\nRECOMENDACAO: Faca alguns Sub-menus\n", item);
		getch();
	}
	else{
		printf("\xBA ");
		printf("%s", item);
		if(peso_item < 100){
			while(qtd_letras < tamanho_x - 4){
				printf("_");
				qtd_letras++;
			}
			if(peso_item < 0)
				printf("(__)");
			else if(peso_item < 10)
				printf("(0%d)", peso_item);
			else
				printf("(%d)", peso_item);
		}
		else if(peso_item >= 100 && peso_item < 1000){
			while(qtd_letras < tamanho_x - 5){
				printf("_");
				qtd_letras++;
			}
			printf("(%d)", peso_item);
		}
	}
	printf(" \xBA");
	if(pula_linha == True)
		printf("\n");
}
//==============================================================================================================================================================
void separa_itens(int tamanho_x, int pula_linha){
	int i = 0;
	printf("\xCC");
		for(i = 0; i < tamanho_x+2; i++){
			printf("\xCD");
		}
	printf("\xB9");
	if(pula_linha == True)
		printf("\n");
}
//============================================================================================================================================================
void menu_titulo(int tamanho_x, char titulo[], int pula_linha){
	int i = 0;
	int tamanho_titulo = strlen(titulo);
	int tamanho_x_novo = tamanho_x - tamanho_titulo;
	int metade_x_novo = tamanho_x_novo / 2;
	
	printf("\xBA ");
	for(i = 0; i < metade_x_novo; i++)
		printf(" ");
	printf("%s", titulo);
	for(i = 0; i < metade_x_novo; i++)
		printf(" ");
	printf(" \xBA");
	if(pula_linha == True)
		printf("\n");
}
//===========================================================================================================================================================
void pula_espaco(int tamanho_x, int pula_linha){//Função responsabel por fazer dois traços separado. EX: "|            |"
	setlocale(LC_ALL, "C");
	int i = 0;
	printf("\xBA ");
	for (i = 0; i < tamanho_x; i++)
		printf(" ");
	printf(" \xBA");
	if(pula_linha == True)
		printf("\n");
}
//===========================================================================================================================================================
void op_ler(int tamanho_x, char conteudo[], int pos_x, int pos_y){
	int i = 0;
	barra_sup(tamanho_x, True);
	printf("\xBA ");
	printf("%s", conteudo);
	for(i = strlen(conteudo); i < tamanho_x; i++)
		printf(" ");
	printf(" \xBA\n");
	barra_inf(tamanho_x, True);
	gotoxy(pos_x, pos_y);
}
//===========================================================================================================================================================
void gotoxy(int x, int y){//Função utilizada para selecionar o lugar que o cursor deve ficar no terminal com base na posição X e Y.
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//==========================================================================================================================================================
void desenha_menu_turno(int pos_x, int pos_y, int tamanho_menu, int dia_semana){
	gotoxy(pos_x, pos_y);
	barra_sup(tamanho_menu, False);
	gotoxy(pos_x, pos_y+=1);
	switch(dia_semana){
		case 0:{
			menu_titulo(tamanho_menu, "Segunda Feira", False);
			break;
		}
		case 1:{
			menu_titulo(tamanho_menu, " Terca Feira ", False);
			break;
		}
		case 2:{
			menu_titulo(tamanho_menu, " Quarta Feira", False);
			break;
		}
		case 3:{
			menu_titulo(tamanho_menu, " Quinta Feira", False);
			break;
		}
		case 4:{
			menu_titulo(tamanho_menu, " Sexta Feira ", False);
			break;
		}		
		case 5:{
			menu_titulo(tamanho_menu, "Sabado ", False);
			break;
		}	
	}
	gotoxy(pos_x, pos_y+=1);
	separa_itens(tamanho_menu, False);
	gotoxy(pos_x, pos_y+=1);
	novo_menu_item(tamanho_menu, "Manha <-> Manha", -1, False);
	gotoxy(pos_x, pos_y+=1);
	novo_menu_item(tamanho_menu, "Tarde <-> Tarde", -1, False);
	gotoxy(pos_x, pos_y+=1);
	novo_menu_item(tamanho_menu, "Noite <-> Noite", -1, False);
	gotoxy(pos_x, pos_y+=1);
	novo_menu_item(tamanho_menu, "Manha <-> Tarde", -1, False);
	gotoxy(pos_x, pos_y+=1);
	novo_menu_item(tamanho_menu, "Nao Vai", -1, False);
	gotoxy(pos_x, pos_y+=1);
	separa_itens(tamanho_menu, False);
	gotoxy(pos_x, pos_y+=1);
	novo_menu_item(tamanho_menu, "Voltar", -1, False);
	gotoxy(pos_x, pos_y+=1);
	barra_inf(tamanho_menu, False);
}
//=========================================================================================================================================================
void desenha_barras(){
	int x = 4, y, terminou;
	for(x = 4; terminou < 2; x += 114){
		for(y = 4; y < 30; y++){
			gotoxy(x, y);
			printf("\xBA");
		}
		terminou++;
	};
}
//==========================================================================================================================================================
void set_cursor_visible(int visible){
  CONSOLE_CURSOR_INFO cursor = {visible, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

int deve_sair(){//Função responsavel por gerar uma mensagem de saida.
	setlocale(LC_ALL, "C");

	int resposta = 0;
	do{
		system("cls");
		barra_sup(30, True);
		pula_espaco(30, True);
		printf("\xBA    DESEJA REALMENTE SAIR?     \xBA\n");
		printf("\xBA    SIM___(01) | NAO___(02)    \xBA\n");
		pula_espaco(30, True);
		barra_inf(31, True);
		scanf("%d", &resposta);
		fflush(stdin);
		if (resposta == 1){
			return True;
		}
		else if(resposta == 2){
			return False;
		}
		else{
			printf("\nESCOLHA INVALIDA! TENTE NOVAMENTE!\n");
		}
	}while(resposta < 1 || resposta > 2);
}
//=====================================================================================================================================================================================
 void saindo(){
	int  i = 0;
	setlocale(LC_ALL, "C");
	system("cls");
	for (i = 0; i < 14; i++)//desce 14 linhas
		printf("\n");
	for (i = 0; i < 5; i++)//centraliza o texto
		printf("\t");
	barra_sup(28, True);
	for (i = 0; i < 5; i++)//centraliza o texto
		printf("\t");
	menu_titulo(28, "Saindo", True);
	for (i = 0; i < 5 ; i++)
		printf("\t");
	barra_inf(28, True);
	for (i = 0; i < 14; i++)
		printf("\n");
	system("exit");
}
