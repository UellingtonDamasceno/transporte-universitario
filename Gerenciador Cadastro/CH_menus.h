#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <pthread.h>
#include "CH_desing.h"
#define ENTER 13
#define UP 72
#define DOWN 80
#define SPACE 32
//================= DECLARAÇÃO DE ESTRUTURAS=============
typedef struct aluno {
	char nome[100];//Nome do aluno.
	char sexo[100];//sexo.
	char instituicao[100];//Nome da faculdade.
	int turno_dominante[6]; //horario que vai a faculdade.
	char curso[100];
	int semestre; //Semestre que entrou.
	int matricula; //Numero da matricula da faculdade.
	int protocolo; //Numero usado para identificar cada aluno.
	int status_de_cadastro; //Pendente, Cadastrado ou Precisa recadastrar.
	struct aluno* proximo;
} Aluno;

typedef struct cabeca {
 	int numero_de_homens;//Contabiliza o numero de homens
	int numero_de_mulheres;//Contabilida o numero de mulheres
 	int numero_de_novos_cadastrados;//Numero de novos cadastrados por semestre.
	int id_aluno_antigo;//identificação dos 10 alunos mais antigos.
	int id_aluno_novo;//identificação dos 10 alunos mais recentes.
	int qtd_univer;//quantidade de alunos que vai para universidade.
	int qtd_facul;//quantidade de alunos que vai para faculdade.
	int qtd_curso_tec;//quantidade de alunos que vai para cursos tecnicos.
	int qtd_pendentes;//com vase no status de cadastro indica o numero de usarios pendentes.
	int qtd_atualizados;//com base no status de cadastro indica o numero de usario devidamente cadastrado.
	int qtd_manha;//contabiliza a quantidade de alunos que vai e volta pela manha.
	int qtd_tarde;//contabiliza a quantidade de alunos que vai e volta pela tarde.
	int qtd_noite;
	int qtd_manha_tarde;//contabilza a quantidade de alunos que vai pela manha e volta pela tarde.
	int tamanho_lista;//indica o tamanho da lista.

	struct aluno* proximo;
} Head;
//=================ASSINATURA DAS FUNCÕES===============
void menu_turno(int tamanho_menu);
void imprime_turno(int dia_horas);
int get_navegacao(Aluno* novo_aluno, int x, int y);
int used_coord(Aluno* novo_aluno, int* x, int* y, int *i);
//-----------------Relacionada aos menus----------------
int menu_principal();       /**/	int menu_sexo();
int menu_instituicao();     /**/    int menu_universidade();
int menu_faculdades();      /**/    int menu_curso_tecnico();
int menu_tipo_curso();
int menu_de_confirmacao();  /**/    int menu_busca();
void menu_sobre();
//------------Relacionadas ao cursos disponiveis-------
int curso_humanas();        /**/    int curso_tecnico();
int curso_engenharia();		/**/    int curso_exatas();
int curso_letras();         /**/
//======================================================
void imprime_aluno(Aluno* novo){
	int i;
	setlocale(LC_ALL, "Portuguese");
	printf("Nome: %s\n", novo->nome);
	printf("Matricula: %d\n", novo->matricula);
	printf("Universidade: %s\n", novo->instituicao);
	printf("Curso: %s\n", novo->curso);
	printf("Sexo: %s\n", novo->sexo);
	printf("Turno dominante: \n");
	for(i = 0; i < 6; i++)
		imprime_turno(novo->turno_dominante[i]);
	printf("\nSemestre: %d\n", novo->semestre);
	printf("Protocolo: %d\n", novo->protocolo);
	printf("===============================================================\n\n");
}
void menu_turno(int tamanho_menu){
	int resposta = 0;
	int i = 0;
	int repetir_menu_turno = False;
	int x = 9, y = 4;
	do{
		system("cls");
		repetir_menu_turno = False;
		printf("   ");
		barra_sup(111, False);
		printf("\n   ");
		menu_titulo(111, "TURNO DOMINANTE PELO QUAL O ALUNO VAI E VOLTA EM DETERMINADO DIA NA SEMANA ", False);
		printf("\n   ");
		separa_itens(111, False);
		for(i = 0; i < 6; i++){
			if(i != 3)
				desenha_menu_turno(x, y, tamanho_menu, i);
			if(i == 3){
				x = 9;
				y = 18;
				desenha_menu_turno(x, y, tamanho_menu, i);
				x+=40;
			}
			else{
				x+=40;
			}
		}
		desenha_barras();
		printf("\n   ");
		barra_inf(111, False);
	}while(repetir_menu_turno == True);
	return;
}
int get_navegacao(Aluno* novo_aluno, int x, int y){
	int i = 0;
	set_cursor_visible(True);
	int repetir_navegacao = True;
	char ch;
	int xa = x, ya = y;
	do{
		repetir_navegacao = True;
		ya = y, xa = x;
		gotoxy(x, y);
		printf("><");
		ch = getch();
		switch(ch){
			case UP:{
				if(y == 7){
					y = 13;
				}
				else if(y == 21){
					y = 27;
				}
				else if(y == 13 || y == 27){
					y -= 2;
				}
				else{
					y--;
				}
				break;
			}
			case DOWN:{
				if(y == 13){
					y = 7;
				}
				else if(y == 27){
					y == 21;
				}
				else if(y == 11 || y == 25){
					y += 2;
				}
				else{
					y++;
				}
				break;
			}
			case ENTER:{
				switch(used_coord(novo_aluno, &x, &y, &i)){
					case Voltar:{
						return Voltar;
						break;
					}
					case Continue:{
						return Continue;
						break;
					}
				}
				break;
			}
			default:{
				repetir_navegacao = True;
				break;
			}
		}
		gotoxy(xa, ya);
		printf("__");
	}while(repetir_navegacao == True);
}
int used_coord(Aluno* o, int* x, int* y, int *i){
	if((*y >= 7 && *y < 13)){
		if(*x == 109){
			o->turno_dominante[*i] = *x+*y;
			(*i)++;
			*x = 29;
			*y = 21;
		}
		else{
			o->turno_dominante[*i] = *x+*y;
			*x += 40;
			while(*y > 7)
				(*y)--;
			gotoxy(*x, *y);
			(*i)++;
		}
	}
	else if(*y >= 21 && *y < 27){
		if(*x == 109){
			o->turno_dominante[*i] = *x+*y;
			return Continue;
		}
		else{
			o->turno_dominante[*i] = *x+*y;
			*x+=40;
			while(*y > 21)
				(*y)--;
			gotoxy(*x, *y);
			(*i)++;
		}	
	}
	else{
		if(*y == 13 && *x == 29){
			return Voltar;
		}
		else if(*y == 13 && *x == 69){
			*x = 29, *y = 7;
		}
		else if(*y == 13 && *x == 109){
			*x = 69, *y = 7;
		}
		else if(*y == 27 && *x == 29){
			*x = 109, *y = 7;
		}
		else if(*y == 27 && *x == 69){
			*x = 29, *y = 21;
		}
		else{
			*x = 69, *y = 21;
		}
		(*i)--;
	}
}
void imprime_turno(int dia_horas){
	if(dia_horas >= 36 && dia_horas <= 40){
		printf("Segunda\t");
		printf("Terca\t");
		printf("Quarta\t");
		printf("Quinta\t");
		printf("Sexta\t");
		printf("Sabado\n");
	}
	if(dia_horas == 36 || dia_horas == 76 || dia_horas == 116 || dia_horas == 50 || dia_horas == 90 || dia_horas == 130)
		printf("  MM\t");
	else if(dia_horas == 37 || dia_horas == 77 || dia_horas == 117 || dia_horas == 51 || dia_horas == 91 || dia_horas == 131)
		printf("  TT\t");
	else if(dia_horas == 38 || dia_horas == 78 || dia_horas == 118 || dia_horas == 52 || dia_horas == 92 || dia_horas == 132)
		printf("  NN\t");
	else if(dia_horas == 39 || dia_horas == 79 || dia_horas == 119 || dia_horas == 53 || dia_horas == 93 || dia_horas == 133)
		printf("  MT\t");
	else 
		printf("  NV\t");
}

int menu_principal(int tamanho_menu) {
	int resposta = 0;
	system("cls");
	barra_sup(tamanho_menu, True);
	menu_titulo(tamanho_menu, "MENU PRINCIPAL", True);
	separa_itens(tamanho_menu, True);
	pula_espaco(tamanho_menu, True);
	novo_menu_item(tamanho_menu, "Cadastrar Aluno", 1, True);
	novo_menu_item(tamanho_menu, "Localizar Aluno", 2, True);
	novo_menu_item(tamanho_menu, "Carregar_arquivo", 3, True);
	novo_menu_item(tamanho_menu, "Exibir Relatorio", 4, True);
	novo_menu_item(tamanho_menu, "Configuracoes", 5, True);
	novo_menu_item(tamanho_menu, "Sobre", 6, True);
	pula_espaco(tamanho_menu, True);
	separa_itens(tamanho_menu, True);
	novo_menu_item(tamanho_menu, "Sair", 7, True);
	barra_inf(tamanho_menu, True);
	scanf("%d", &resposta);
	fflush(stdin);
	switch(resposta){
		case 1:{
			return novo_cadastro;
			break;
		}
		case 2:{
			return localizar_aluno;
			break;
		}
		case 3:{
			return carregar_arquivo;
			break;
		}
		case 4:{
			return exibir_relatorio;
			break;
		}
		case 5:{
			return configuracoes;
			break;
		}
		case 6:{
			return sobre;
			break;
		}
		case 7:{
			return sair;
			break;
		}
	}
	return resposta;
}
//====================================================================================================================================================================================
int menu_sexo(int tamanho_menu){
	int resposta = 0;
	int repetir_menu_sexo = False;
	do{
		system("cls");
		repetir_menu_sexo = False;
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Sexo", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Masculino", 1, True);
		novo_menu_item(tamanho_menu, "Femenino", 2, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 3, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return masculino;
				break;
			}
			case 2:{
				return femenino;
				break;
			}
			case 3:{
				return Voltar;
				break;
			}
			default:{
				printf("ESCOLHA INVALIDA TENTE NOVAMENTE\n");
				repetir_menu_sexo = True;
				break;
			}
		}
	}while(repetir_menu_sexo == True);
	return Continue;
}
//====================================================================================================================================================================================
int menu_busca(int tamanho_menu){
	int resposta = 0;
	int repetir_menu_busca = False;
	do{
		system("cls");
		repetir_menu_busca = False;
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Menu de Busca", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Nome", 1, True);
		novo_menu_item(tamanho_menu, "Semestre", 2, True);
		novo_menu_item(tamanho_menu, "Matricula", 3, True);
		novo_menu_item(tamanho_menu, "Protocolo", 4, True);
		novo_menu_item(tamanho_menu, "Listar Alunos por...", 5, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 6, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return pelo_nome;
				break;
			}
			case 2:{
				return pelo_semestre;
				break;
			}
			case 3:{
				return pela_matricula;
				break;
			}
			case 4:{
				return pelo_protocolo;
				break;
			}
			case 5:{
				return listar;
				break;
			}
			case 6:{
				return Voltar;
				break;
			}
			default:{
				printf("Escolha invalida tente novamente\n");
				repetir_menu_busca = True;
				break;
			}
		}
	}while(repetir_menu_busca == True);
}
//====================================================================================================================================================================================

//====================================================================================================================================================================================
int menu_instituicao(int tamanho_menu){
	int resposta = 0;
	int repetir_menu_instituicao = False;
	do{
		repetir_menu_instituicao = False;
		system("cls");
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Instituicao", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Faculdade", 1, True);
		novo_menu_item(tamanho_menu, "Universidade", 2, True);
		novo_menu_item(tamanho_menu, "Curso Tecnico", 3, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 4, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return faculdade;
				break;
			}
			case 2:{
				return universidade;
				break;
			}
			case 3:{
				return curso_tecnico_op;
			}
			case 4:{
				return Voltar;
				break;
			}
			default:{
				repetir_menu_instituicao = True;
				break;
			}
		}
	}while(repetir_menu_instituicao == True);
}
//====================================================================================================================================================================================
int menu_faculdades(int tamanho_menu){
	int resposta = 0;
	int repetir_menu_faculdade = False;
	do{
		system("cls");
		repetir_menu_faculdade = False;
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Faculdades", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "FAN", 1, True);
		novo_menu_item(tamanho_menu, "FAT", 2, True);
		novo_menu_item(tamanho_menu, "FTC", 3, True);
		novo_menu_item(tamanho_menu, "PITAGORAS", 4, True);
		novo_menu_item(tamanho_menu, "UNIASSELVI", 5, True);
		novo_menu_item(tamanho_menu, "Outra", 6, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 7, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1: {
				return FAN;
				break;
			}
			case 2: {
				return FAT;
				break;
			}
			case 3: {
				return FTC;
				break;
			}
			case 4: {
				return PITAGORAS;
				break;
			}
			case 5: {
				return UNIASSELVI;
				break;
			}
			case 6:{
				return Outro;
				break;
			}
			case 7: {
				return Voltar;
				break;
			}
			default: {
				printf("ESCOLHA INVALIDA TENTE NOVAMENTE\n");
				repetir_menu_faculdade = True;
				break;
			}
		}
	}while(repetir_menu_faculdade == True);
	return Continue;
}
//====================================================================================================================================================================================
int menu_universidade(int tamanho_menu){
	int resposta = 0;
	int repetir_menu_universidade = False;
	do{
		system("cls");
		repetir_menu_universidade = False;
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Universidade", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "UEFS", 1, True);
		novo_menu_item(tamanho_menu, "UFRB", 2, True);
		novo_menu_item(tamanho_menu, "UNEF", 3, True);
		novo_menu_item(tamanho_menu, "Outra", 4, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "VOLTAR", 5, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1: {
				return UEFS;
				break;
			}
			case 2: {
				return UFRB;
				break;
			}
			case 3: {
				return UNEF;
				break;
			}
			case 4:{
				return Outro;
				break;
			}
			case 5: {
				return Voltar;
				break;
			}
			default: {
				printf("ESCOLHA INVALIDA TENTE NOVAMENTE\n");
				repetir_menu_universidade = True;
				break;
			}
		}
	}while(repetir_menu_universidade == True);
	return Continue;
}
//====================================================================================================================================================================================
int menu_tipo_curso(int tamanho_menu){
	int resposta = 0;
	int repetir_tipo_curso = False;
	do{
		system("cls");
		repetir_tipo_curso = False;
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Tipo de Curso ", True);
		separa_itens(tamanho_menu, True);
		pula_espaco(tamanho_menu, True);
		novo_menu_item((tamanho_menu/2)-3, "Engenharia", 1, False);
		printf("\t");
		novo_menu_item((tamanho_menu/2)-3, "Exatas", 2, True);
		novo_menu_item((tamanho_menu/2)-3, "Humanas", 3, False);
		printf("\t");
		novo_menu_item((tamanho_menu/2)-3, "Linguisticas", 4, True);
		novo_menu_item((tamanho_menu/2)-3, "Saude", 5, False);
		printf("\t");
		novo_menu_item((tamanho_menu/2)-3, "Tecnicos", 6, True);
		pula_espaco(tamanho_menu, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Nao encontrei o curso", 7, True);
		novo_menu_item(tamanho_menu, "Voltar", 8, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return engenharia;
				break;
			}
			case 2:{
				return exatas;
				break;
			}
			case 3:{
				return humanas;
				break;
			}
			case 4:{
				return letras;
				break;
			}
			case 5:{
				return saude;
				break;
			}
			case 6:{
				return curso_tecnico_op;
				break;
			}
			case 8:{
				return Voltar;
				break;
			}
			default:{
				repetir_tipo_curso = True;
				break;
			}
		}
	}while(repetir_tipo_curso == True);
}
//====================================================================================================================================================================================
int menu_curso_tecnico(int tamanho_menu){
	int resposta = 0;
	int repetir_menu_curso_tecnico = False;
	do{
		system("cls");
		repetir_menu_curso_tecnico = False;
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Cursos Tecnico", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "CEBRAC", 1, True);
		novo_menu_item(tamanho_menu, "CEEP", 2, True);
		novo_menu_item(tamanho_menu, "IFBA", 3, True);
		novo_menu_item(tamanho_menu, "SENAI", 4, True);
		novo_menu_item(tamanho_menu, "Outro", 5, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 6, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return CEBRAC;
				break;
			}
			case 2:{
				return CEEP;
				break;
			}
			case 3:{
				return IFBA;
				break;
			}
			case 4:{
				return SENAI;
				break;
			}
			case 5:{
				return Outro;
				break;
			}
			case 6:{
				return Voltar;
				break;
			}
			default:{
				printf("ESCOLHA INVALIDA TENTE NOVAMENTE\n");
				repetir_menu_curso_tecnico = True;
				break;
			}
		}
	}while(repetir_menu_curso_tecnico == True);
	return Continue;
}
//====================================================================================================================================================================================
//====================================================================================================================================================================================
int menu_de_confirmacao(Aluno *novo, int tamanho_menu){
	int resposta = 0;
	int repetir_menu_de_confirmacao = False;
	do{
		repetir_menu_de_confirmacao = False;
		system("cls");
		imprime_aluno(novo);
		printf("\n\n");
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Confimacao De Cadastro", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Novo Cadastro", 1, True);
		novo_menu_item(tamanho_menu, "Alterar Ultimo Cadastro", 2, True);
		novo_menu_item(tamanho_menu, "Menu Principal", 3, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Sair", 4, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return novo_cadastro;
				break;
			}
			case 2:{
				return alterar_cadastro_op;
				break;
			}
			case 3:{
				return menu_principal_op;
				break;
			}
			case 4:{
				return sair;
				break;
			}
			default:{
				repetir_menu_de_confirmacao = True;
				break;
			}
		}
	}while(repetir_menu_de_confirmacao == True);
}
//====================================================================================================================================================================================
int menu_alterar_aluno(int tamanho_menu, Aluno *o_aluno){
	int resposta = 0;
	int repetir_menu_alterar_aluno = False;
	do{
		system("cls");
		repetir_menu_alterar_aluno = False;
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Alterar aluno", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Nome", 1, True);
		novo_menu_item(tamanho_menu, "Sexo", 2, True);
		novo_menu_item(tamanho_menu, "Instituicacao", 3, True);
		novo_menu_item(tamanho_menu, "Turno dominante", 4, True);
		novo_menu_item(tamanho_menu, "Curso", 5, True);
		novo_menu_item(tamanho_menu, "Semestre", 6, True);
		novo_menu_item(tamanho_menu, "Matricula", 7, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 8, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return nome_op;
				break;
			}
			case 2:{
				return sexo_op;
				break;
			}
			case 3:{
				return instituicao_op;
				break;
			}
			case 4:{
				return turno_dominante_op;
				break;
			}
			case 5:{
				return curso_op;
				break;
			}
			case 6:{
				return semestre_op;
				break;
			}
			case 7:{
				return matricula_op;
				break;
			}
			case 8:{
				return Voltar;
				break;
			}
			default:{
				repetir_menu_alterar_aluno = True;
				break;
			}
		}
	}while(repetir_menu_alterar_aluno == True);
}
//====================================================================================================================================================================================
int menu_de_listagem(int tamanho_menu){
	int resposta = 0;
	int repetir_menu_de_listagem = False;
	do{
		system("cls");
		repetir_menu_de_listagem = False;
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Menu de Busca", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Turno", 1, True);
		novo_menu_item(tamanho_menu, "Sexo", 2, True);
		novo_menu_item(tamanho_menu, "Instituicao", 3, True);
		novo_menu_item(tamanho_menu, "Listar Todos", 4, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 5, True);
		barra_inf(tamanho_menu, True);;
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return pelo_turno;
				break;
			}
			case 2:{
				return pelo_sexo;
				break;
			}
			case 3:{
				return pela_instituicao;
				break;
			}
			case 4:{
				return listar_todos;
				break;
			}
			case 5:{
				return Voltar;
				break;
			}
		}
	}while(repetir_menu_de_listagem == True);
}
//====================================================================================================================================================================================
int curso_humanas(int tamanho_menu){
	int repetir_curso_humanas = False;
	int resposta = 0;
	do{
		repetir_curso_humanas = False;
		system("cls");
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Curso De Humanas", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Biologia", 1, True);
		novo_menu_item(tamanho_menu, "Biomedicina", 2, True);
		novo_menu_item(tamanho_menu, "Educacao Fisca", 3, True);
		novo_menu_item(tamanho_menu, "Historia", 4, True);
		novo_menu_item(tamanho_menu, "Quimica", 5, True);
		novo_menu_item(tamanho_menu, "Outro", 6, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 7, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return biologia;
				break;
			}
			case 2:{
				return biomedicina;
				break;
			}
			case 3:{
				return educacao_fisica;
				break;
			}
			case 4:{
				return historia;
				break;
			}
			case 5:{
				return quimica;
				break;
			}
			case 6:{
				return Outro;
				break;
			}
			case 7:{
				return Voltar;
				break;
			}
			default:{
				repetir_curso_humanas = True;
				break;
			}
		}
	}while(repetir_curso_humanas == True);
	return Continue;
}
//====================================================================================================================================================================================
int curso_exatas(int tamanho_menu){
	int resposta = 0;
	int repetir_curso_exatas = False;
	do{
		repetir_curso_exatas = False;
		system("cls");
		
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Curso De Exatas ", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Administracao", 1, True);
		novo_menu_item(tamanho_menu, "Ciencias Contabeis", 2, True);
		novo_menu_item(tamanho_menu, "Fisca", 3, True);
		novo_menu_item(tamanho_menu, "Matematica", 4, True);
		novo_menu_item(tamanho_menu, "Outro", 5, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 6, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return administracao;
				break;
			}
			case 2:{
				return ciencias_contabeis;
				break;
			}
			case 3:{
				return fisica;
				break;
			}
			case 4:{
				return matematica;
				break;
			}
			case 5:{
				return Outro;
				break;
			}
			case 6:{
				return Voltar;
				break;
			}
			default:{
				repetir_curso_exatas = True;
				break;
			}
		}
	}while(repetir_curso_exatas == True);
	return Continue;
}
//====================================================================================================================================================================================
int curso_engenharia(int tamanho_menu){
	int resposta = 0;
	int repetir_curso_engenharia = False;
	do{
		repetir_curso_engenharia = False;
		system("cls");
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Curso de engenharia ", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu,"E.Alimentos", 1, True);
		novo_menu_item(tamanho_menu, "E.Ambiental", 2, True);
		novo_menu_item(tamanho_menu, "E.Civel", 3, True);
		novo_menu_item(tamanho_menu, "E.Computacao", 4, True);
		novo_menu_item(tamanho_menu, "E.Eletrica", 5, True);
		novo_menu_item(tamanho_menu, "E.Mecanica", 6, True);
		novo_menu_item(tamanho_menu, "E.Producao", 7, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 8, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return alimentos;
				break;
			}
			case 2:{
				return ambiental;
				break;
			}
			case 3:{
				return civel;
				break;
			}
			case 4:{
				return computacao;
				break;
			}
			case 5:{
				return eletrica;
				break;
			}
			case 6:{
				return mecanica;
				break;
			}
			case 7:{
				return producao;
				break;
			}
			case 8:{
				return Voltar;
				break;
			}
			default:{
				repetir_curso_engenharia = True;
				break;
			}
		}
	}while(repetir_curso_engenharia == True);
	return Continue;
}
//====================================================================================================================================================================================
int curso_saude(int tamanho_menu){
	int resposta = 0;
	int repetir_curso_saude = False;
	do{
		repetir_curso_saude = False;
		system("cls");
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Saude ", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item((tamanho_menu/2)-3, "Enfermagem", 1, False);
		printf("\t ");
		novo_menu_item((tamanho_menu/2)-3, "Farmacia", 2, True);
		novo_menu_item((tamanho_menu/2)-3, "Fisioterapia", 3, False);
		printf("\t ");
		novo_menu_item((tamanho_menu/2)-3, "Medicina", 4, True);
		novo_menu_item((tamanho_menu/2)-3, "M. Veterinaria", 5, False);
		printf("\t ");
		novo_menu_item((tamanho_menu/2)-3, "Nutricao", 6, True);
		novo_menu_item((tamanho_menu/2)-3, "Odontologia", 7, False);
		printf("\t ");
		novo_menu_item((tamanho_menu/2)-3, "Psicologia", 8, True);
		novo_menu_item(tamanho_menu, "Radiologia", 9, True);;
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 10, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return enfermagem;
				break;
			}
			case 2:{
				return farmacia;
				break;
			}
			case 3:{
				return fisioterapia;
				break;
			}
			case 4:{
				return medicina;
				break;
			}
			case 5:{
				return veterinaria;
				break;
			}
			case 6:{
				return nutricao;
				break;
			}
			case 7:{
				return odontologia;
				break;
			}
			case 8:{
				return psicologia;
				break;
			}
			case 9:{
				return radiologia;
				break;
			}
			case 10:{
				return Voltar;
				break;
			}
			default:{
				repetir_curso_saude = True;
				break;
			}
		}
	}while(repetir_curso_saude == True);
	return Continue;
}
//====================================================================================================================================================================================
int curso_tecnico(int tamanho_menu){
	int resposta = 0;
	int repetir_curso_tecnico = False;
	do{
		repetir_curso_tecnico = False;
		system("cls");
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, " Curso Tecnico", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item((tamanho_menu/2)-3, "Analises Clinicas", 1, False);
		printf("\t ");
		novo_menu_item((tamanho_menu/2)-3, "Edificacoes", 2, True);
		novo_menu_item((tamanho_menu/2)-3, "Eletromecanica", 3, False);
		printf("\t ");
		novo_menu_item((tamanho_menu/2)-3, "Eletrotecnica", 4, True);
		novo_menu_item((tamanho_menu/2)-3, "Enfermagem", 5, False);
		printf("\t ");
		novo_menu_item((tamanho_menu/2)-3, "Logistica", 6, True);
		novo_menu_item((tamanho_menu/2)-3, "Mecanica", 7, False);
		printf("\t ");
		novo_menu_item((tamanho_menu/2)-3, "Rotina ADM", 8, True);
		novo_menu_item(tamanho_menu, "Seguranca do Trab", 9, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 10, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return analises_clinicas;
				break;
			}
			case 2:{
				return edificacoes;
				break;
			}
			case 3:{
				return eletromecanica;

				break;
			}
			case 4:{
				return eletrotecnica;
				break;
			}
			case 5:{
				return enfermagem_ct;
				break;
			}
			case 6:{
				return logistica;
				break;
			}
			case 7:{
				return mecanica_ct;
				break;
			}
			case 8:{
				return rotina_adm;
				break;
			}
			case 9:{
				return seguranca_do_trabalho;
				break;
			}
			case 10:{
				return Voltar;
				break;
			}
			default:{
				repetir_curso_tecnico = True;
				break;
			}
		}
	}while(repetir_curso_tecnico == True);
	return Continue;
}
//====================================================================================================================================================================================
int curso_letras(int tamanho_menu){
	int resposta = 0;
	int repetir_curso_letras = False;
	do{
		repetir_curso_letras = False;
		system("cls");
		barra_sup(tamanho_menu, True);
		menu_titulo(tamanho_menu, "Letras", True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "L.Com Espanhol", 1, True);
		novo_menu_item(tamanho_menu, "L.Com Frances", 2, True);
		novo_menu_item(tamanho_menu, "L.Com Ingles", 3, True);
		novo_menu_item(tamanho_menu, "L.Com Portugues", 4, True);
		novo_menu_item(tamanho_menu, "L.com Vernaculas", 5, True);
		separa_itens(tamanho_menu, True);
		novo_menu_item(tamanho_menu, "Voltar", 6, True);
		barra_inf(tamanho_menu, True);
		scanf("%d", &resposta);
		fflush(stdin);
		switch(resposta){
			case 1:{
				return espanhol;
				break;
			}
			case 2:{
				return frances;
				break;
			}
			case 3:{
				return ingles;
				break;
			}
			case 4:{
				return portugues;
				break;
			}
			case 5:{
				return vernaculas;
				break;
			}
			case 6:{
				return Voltar;
				break;
			}
			default:{
				repetir_curso_letras = True;
				break;
			}
		}
	}while(repetir_curso_letras == True);
	return Continue;
}
void menu_sobre(){
	system("cls");
	printf("'+=+=+=+=+=+=+= #Sobre# =+=+=+=+=+=+=+=+=+\n");
	printf("| DESENVOLVEDOR: Uellington Damasceno    |\n");
	printf("| DATA DO INICIO: 02/09/2017  |||||||    |\n");
	printf("| VERSAO: 1.0                ª| @  @|    |\n");
	printf("| TIPO: Gerenciador           |   > |    |\n");
	printf("| Orientador: Sem orientador  |_---_|    |\n");
	printf("| Ultima altercao 11/09/2017 as 21:16 PM |\n");
	printf("'+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+\n");
	system("pause");
}
int ler_matricula(Aluno* a){
	char ch;
	int repetir_digitacao = False;
	int i = 0;
	system("cls");
	op_ler(35, "Digite a Matricula: ", 23, 2);
	i = ler_apenas_numero(&a->matricula, 9);
	return i;
}
//====================================================================================================================================================================================
int ler_nome(Aluno* o){

	system("cls");
	op_ler(60, "Nome do aluno(a): ", 21, 2);
	if(ler_apenas_letras(o->nome) == Continue)
		return Continue;
	else
		return Voltar;
}
//====================================================================================================================================================================================
int ler_semestre(Aluno *o){
	char semestre[5];
	int repetir_digitacao = False;
	system("cls");
	op_ler(26, "Digite o Semeste: ", 21, 2);
	int x = ler_apenas_numero(&o->semestre, 5);
	return x;
}
