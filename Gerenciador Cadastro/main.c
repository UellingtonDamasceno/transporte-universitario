#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "CH_lista.h"
#include "CH_menus.h"
#include "CH_preencher.h"
#include "CH_gerador.h"
#include <locale.h>

//================= DECLARAÇÃO DE ESTRUTURAS=============

//=================ASSINATURA DAS FUNCÕES===============
//------------------Relacionadas a Cabeça---------------
Head* carregar_head();         /**/     Head* insere_ordenado();
//-----------------Relacionadas ao aluno---------------
Aluno * iniciar_estrutura_aluno();/**/

//----------Utilzadas para preencher a estrutura-------
int listar_sexo();
//-------------PROCEDIMENTOS ACOPLADOS-----------------
void imprime_info();		/**/	void zerar_vetor_char();
int ler_apenas_letras();	/**/	void gotoxy();
void impede_fechar();		/**/	int deve_sair();
void saindo();              /**/    void imprimir_lista();

//======================================================

int main(int argc, char *argv[]) {
//===========Sessão de funções de pré-processamento==========
	setlocale(LC_ALL, "Portuguese");
	SetConsoleTitle("SISTEMA DE RECADASTRO E GERENCIAMENTEO - TRANSPORTE UNIVERSITARIO");
	impede_fechar();

//===========Sessão de Declaração de Variaveis==============
	Head* inicio = NULL;
	Aluno* novo_aluno = NULL;
	int resposta = 0;

	int repetir_menu_principal = False;
	int repetir_cadastro = False;
	int repetir_menu_instituicao = False;
	int repetir_menu_sexo = False;
	int repetir_menu_turno = False;
	int repetir_matricula = False;
	int repetir_semestre = False;
	int repetir_menu_tipo_curso = False;
	int repetir_confirmacao_matricula = False;
	int repetir_menu_de_confirmacao = False;
	int repetir_menu_alterar_aluno = False;
	int repetir_menu_curso_tecnico = False;
	int repetir_menu_faculdade = False;
	int repetir_menu_universidade = False;
	int repetir_menu_busca = False;

	int continuar_questionario = True;
	int criar_novo_aluno = False;
//====================Inicio do Algoritmo===================

	FILE* arquivo = fopen("Head.txt", "r");//abre o arquivo da cabeça.
	if(verifica_se_vazio(arquivo) == True)//verifica se o arquivo da cabeça esta vazio.
		inicio = carregar_head(inicio, arquivo);//se não estiver vazio o conteudo vai ser carregado na estrutura da cabeça.
	else {
		FILE* cria_um_arq;//se não existir um arquivo de cabeça vai ser criado.
		cria_um_arq = fopen("Head.txt", "w+");
	}
	fclose(arquivo);

	do {
		repetir_menu_principal = False;
		switch(menu_principal(30)) {
			case novo_cadastro: {
				criar_novo_aluno = True;
				do {
					repetir_cadastro = False;//Impede que o laço para repetir cadastro entre em loop infinito.
					if(criar_novo_aluno == True){
						novo_aluno = (Aluno*) malloc(sizeof(Aluno));
						novo_aluno = iniciar_estrutura_aluno(novo_aluno);//inicializa a esturtura novo aluno zerando todos os seus resultados
					}
					resposta = ler_nome(novo_aluno);//aluno recebe nome do aluno e retorna se o usario quer voltar ao menu principal.
					if(resposta == Voltar){//caso o usario digite um numero o cadastro sera cancelado e voltará para o menu anterior.
						printf("CADASTRO CANCELADO!\n");
						repetir_menu_principal = True;
						getch();
						free(novo_aluno);//apaga a estrutura aluno.
					}
					else{
						do{
							continuar_questionario = True;
							repetir_menu_sexo = False;
							switch(preencher_sexo(menu_sexo(26), novo_aluno)){
								case Continue:{
									continuar_questionario = True;
									break;
								}
								case Voltar:{
									continuar_questionario = False;
									repetir_cadastro = True;
									break;
								}
							}
							if(continuar_questionario == True){
								do {
									continuar_questionario = True;
									repetir_menu_instituicao = False;
									resposta = menu_instituicao(25);
									switch(resposta){
										case faculdade:{
											do{
												repetir_menu_faculdade = False;
												switch(preencher_faculdade(menu_faculdades(26), novo_aluno)){
													case Voltar:{
														repetir_menu_instituicao = True;
														continuar_questionario = False;
														break;
													}
													case Outro:{
														switch(outra_instituicao(1, novo_aluno)){
															case Voltar:{
																repetir_menu_faculdade = True;
																break;
															}
															case Continue:{
																continuar_questionario = True;
																break;
																}
															}
															break;
														}
													case Continue:{
														continuar_questionario = True;
														break;
													}
												}
											}while(repetir_menu_faculdade == True);
											break;
										}
										case universidade:{
											do{
												repetir_menu_universidade = False;
												switch(preencher_universidade(menu_universidade(26), novo_aluno)){
													case Voltar:{
														repetir_menu_instituicao = True;
														continuar_questionario = False;
														break;
													}
													case Outro:{
														switch(outra_instituicao(2, novo_aluno)){
															case Voltar:{
																repetir_menu_universidade = True;
																break;
															}
															case Continue:{
																continuar_questionario = True;
																break;
															}
														}
														break;
													}
													case Continue:{
														continuar_questionario = True;
														break;
													}
												}
											}while(repetir_menu_universidade == True);
											break;
										}
										case curso_tecnico_op:{
											do{
												repetir_menu_curso_tecnico = False;
												switch (preencher_CT(menu_curso_tecnico(26), novo_aluno)){
													case Voltar:{
														repetir_menu_instituicao = True;
														continuar_questionario = False;
														break;
													}
													case Outro:{
														switch(outra_instituicao(3, novo_aluno)){
															case Voltar:{
																repetir_menu_curso_tecnico = True;
																break;
															}
															case Continue:{
																continuar_questionario = True;
																break;
															}
														}
														break;
													}
													case Continue:{
														continuar_questionario = True;
														break;
													}
												}
											}while(repetir_menu_curso_tecnico == True);
											break;
										}
										case Voltar:{
											repetir_menu_sexo = True;
											continuar_questionario = False;
											break;
										}
									}
									if(continuar_questionario == True){
										do{
											continuar_questionario = False;
											repetir_menu_tipo_curso = False;
											switch(menu_tipo_curso(58)){
												case engenharia:{
													switch(preencher_engenharia(curso_engenharia(26), novo_aluno)){
														case Continue:{
															continuar_questionario = True;
															break;
														}
														case Voltar:{
															repetir_menu_tipo_curso = True;
															continuar_questionario = False;
															break;
														}
													}
													break;
												}
												case exatas:{
													switch(preencher_exatas(curso_exatas(26), novo_aluno)){
														case Continue:{
															continuar_questionario = True;
															break;
														}
														case Voltar:{
															repetir_menu_tipo_curso = True;
															continuar_questionario = False;
															break;
														}
													}
													break;
												}
												case letras:{
													switch(preencher_letras(curso_letras(26), novo_aluno)){
														case Voltar:{
															repetir_menu_tipo_curso = True;
															continuar_questionario = False;
															break;
														}
														case Continue:{
															continuar_questionario = True;
															break;
														}
													}
													break;
												}
												case humanas:{
													switch(preencher_humanas(curso_humanas(26), novo_aluno)){
														case Voltar:{
															repetir_menu_tipo_curso = True;
															continuar_questionario = False;
															break;
														}
														case Continue:{
															continuar_questionario = True;
															break;
														}
													}
													break;
												}
												case saude:{
													switch(preencher_saude(curso_saude(60), novo_aluno)){
														case Voltar:{
															repetir_menu_tipo_curso = True;
															continuar_questionario = False;
															break;
														}
														case Continue:{
															continuar_questionario = True;
															break;
														}
													}
													break;
												}
												case curso_tecnico_op:{
													switch(preencher_curso_tec(curso_tecnico(60), novo_aluno)){
														case Voltar:{
															repetir_menu_tipo_curso = True;
															continuar_questionario = False;
															break;
														}
														case Continue:{
															continuar_questionario = True;
															break;
														}
													}
													break;
												}
												case Continue:{
													continuar_questionario = True;
													break;
												}
												case Voltar:{
													repetir_menu_instituicao = True;
													continuar_questionario = False;
													break;
												}
											}
											if(continuar_questionario == True){
												do{
													continuar_questionario = False;
													repetir_matricula = False;
													switch(ler_matricula(novo_aluno)){
														case Voltar:{
															repetir_menu_tipo_curso = True;
															break;
														}
														case Continue:{
															do{
																repetir_confirmacao_matricula = False;
																switch(confirma_matricula(novo_aluno)){
																	case Voltar:{
																			repetir_matricula = True;
																		break;
																	}
																	case Continue:{
																			do{
																				repetir_semestre = False;
																				switch(ler_semestre(novo_aluno)){
																					case Voltar:{
																						repetir_confirmacao_matricula = True;
																						break;
																					}
																					case Continue:{
																						do{
																							repetir_menu_turno = False;
																							menu_turno(21);
																							switch(get_navegacao(novo_aluno, 29, 7)){
																								case Continue:{
																									set_cursor_visible(False);
																									continuar_questionario = True;
																									break;
																								}
																								case Voltar:{
																									continuar_questionario = False;
																									repetir_semestre = True;
																									break;
																								}
																							}
																							if(continuar_questionario == True){
																								do{
																									repetir_menu_de_confirmacao = False;
																									switch(menu_de_confirmacao(novo_aluno, 28)){
																										case novo_cadastro:{
																											repetir_cadastro = True;
																											inicio = insere_ordenado(inicio, novo_aluno, novo_aluno->nome);
																											break;
																										}
																										case alterar_cadastro_op:{
																											do{
																												repetir_menu_alterar_aluno = False;
																												switch(menu_alterar_aluno(25, novo_aluno)){
																													case nome_op:{
																														switch(ler_nome(novo_aluno)){
																															case Voltar:{
																																repetir_menu_alterar_aluno = True;
																																break;
																															}
																															case Continue:{
																																repetir_menu_de_confirmacao = True;
																																break;
																															}
																														}
																														break;
  																													}
  																													case sexo_op:{
  																														switch(preencher_sexo(menu_sexo(26), novo_aluno)){
																															case Voltar:{
																																repetir_menu_alterar_aluno = True;
																																break;
																															}
																															case Continue:{
																																repetir_menu_de_confirmacao = True;
																																break;
																															}
																														}
																														break;
																													  }
																													case instituicao_op:{
																														do{
																															repetir_menu_instituicao = False;
																															switch(menu_instituicao(27)){
																																case faculdade:{
																																	do{
																																		repetir_menu_faculdade = False;
																																		switch(preencher_faculdade(menu_faculdades(26), novo_aluno)){
																																			case Voltar:{
																																				repetir_menu_instituicao = True;
																																				break;
																																			}
																																			case Outro:{
																																				switch(outra_instituicao(1, novo_aluno)){
																																					case Voltar:{
																																						repetir_menu_faculdade = True;
																																						break;
																																					}
																																					case Continue:{
																																						repetir_menu_de_confirmacao = True;
																																						break;
																																					}
																																				}
																																				break;
																																			}
																																			case Continue:{
																																			repetir_menu_de_confirmacao = True;
																																				break;
																																			}
																																		}
																																	}while(repetir_menu_faculdade == True);
																																	break;
																																}
																																case universidade:{
																																	do{
																																		repetir_menu_universidade = False;
																																		switch(preencher_universidade(menu_universidade(26), novo_aluno)){
																																			case Voltar:{
																																				repetir_menu_instituicao = True;
																																				break;
																																			}
																																			case Outro:{
																																				switch(outra_instituicao(2, novo_aluno)){
																																					case Voltar:{
																																						repetir_menu_universidade = True;
																																						break;
																																					}
																																					case Continue:{
																																						repetir_menu_de_confirmacao = True;
																																						break;
																																					}
																																				}
																																				break;
																																			}
																																			case Continue:{
																																				repetir_menu_de_confirmacao = True;
																																				break;
																																			}
																																		}
																																	}while(repetir_menu_universidade == True);
																																	break;
																																}
																																case curso_tecnico_op:{
																																	do{
																																		repetir_menu_curso_tecnico = False;
																																		switch (preencher_CT(menu_curso_tecnico(26), novo_aluno)){
																																			case Voltar:{
																																				repetir_menu_instituicao = True;
																																				break;
																																			}
																																			case Outro:{
																																				switch(outra_instituicao(3, novo_aluno)){
																																					case Voltar:{
																																						repetir_menu_curso_tecnico = True;
																																						break;
																																					}
																																					case Continue:{
																																						repetir_menu_de_confirmacao = True;
																																						break;
																																					}
																																				}
																																				break;
																																			}
																																			case Continue:{
																																				repetir_menu_de_confirmacao = True;
																																				break;
																																			}
																																		}
																																	}while(repetir_menu_curso_tecnico == True);
																																	break;
																																}
																																case Voltar:{
																																	repetir_menu_alterar_aluno = True;
																																	break;
																																}
																																case Continue:{
																																	repetir_menu_de_confirmacao = True;
																																	break;
																																}
																															}
																														}while(repetir_menu_instituicao == True);
																														break;
																													}
																													case turno_dominante_op:{
																														menu_turno(21);
																														switch(get_navegacao(novo_aluno, 29, 7)){
																															case Voltar:{
																																repetir_menu_alterar_aluno = True;
																																break;
																															}
																															case Continue:{
																																repetir_menu_de_confirmacao = True;
																																break;
																															}
																														}
																														break;
																													}
																													case curso_op:{
																														int repetir_menu_tipo_curso_op = False;
																														do{
																															repetir_menu_tipo_curso_op = False;
																															switch(menu_tipo_curso(58)){
																																case engenharia:{
																																	switch(preencher_engenharia(curso_engenharia(26), novo_aluno)){
																																		case Continue:{
																																			repetir_menu_de_confirmacao = True;
																																			break;
																																		}
																																		case Voltar:{
																																			repetir_menu_tipo_curso = True;
																																			break;
																																		}
																																	}
																																	break;
																																}
																																case exatas:{
																																	switch(preencher_exatas(curso_exatas(26), novo_aluno)){
																																		case Continue:{
																																			repetir_menu_de_confirmacao = True;
																																			break;
																																		}
																																		case Voltar:{
																																			repetir_menu_tipo_curso = True;
																																			break;
																																		}
																																	}
																																	break;
																																}
																																case letras:{
																																	switch(preencher_letras(curso_letras(26), novo_aluno)){
																																		case Voltar:{
																																			repetir_menu_tipo_curso = True;
																																			continuar_questionario = False;
																																			break;
																																		}
																																		case Continue:{
																																			repetir_menu_de_confirmacao = True;
																																			break;
																																		}
																																	}
																																	break;
																																}
																																case humanas:{
																																	switch(preencher_humanas(curso_humanas(26), novo_aluno)){
																																		case Voltar:{
																																			repetir_menu_tipo_curso = True;
																																			continuar_questionario = False;
																																			break;
																																		}
																																		case Continue:{
																																			repetir_menu_de_confirmacao = True;
																																			break;
																																		}
																																	}
																																	break;
																																}
																																case saude:{
																																	switch(preencher_saude(curso_saude(50), novo_aluno)){
																																		case Voltar:{
																																			repetir_menu_tipo_curso = True;
																																			continuar_questionario = False;
																																			break;
																																		}
																																		case Continue:{
																																			repetir_menu_de_confirmacao = True;
																																			break;
																																		}
																																	}
																																	break;
																																}
																																case curso_tecnico_op:{
																																	switch(preencher_curso_tec(curso_tecnico(60), novo_aluno)){
																																		case Voltar:{
																																			repetir_menu_tipo_curso = True;
																																			continuar_questionario = False;
																																			break;
																																		}
																																		case Continue:{
																																			repetir_menu_de_confirmacao = True;
																																			break;
																																		}
																																	}
																																	break;
																																}
																																case Continue:{
																																	repetir_menu_de_confirmacao = True;
																																	break;
																																}
																																case Voltar:{
																																	repetir_menu_instituicao = True;
																																	break;
																																}
																															}
																														}while(repetir_menu_tipo_curso_op == True);
																														break;
																													}
																													case semestre_op:{
																														switch(ler_semestre(novo_aluno)){
																															case Voltar:{
																																repetir_menu_alterar_aluno = True;
																																break;
																															}
																															case Continue:{
																																repetir_menu_de_confirmacao = True;
																																break;
																															}
																														}
																														break;
																													}
																													case matricula_op:{
																														switch(ler_matricula(novo_aluno)){
																															case Voltar:{
																																repetir_menu_alterar_aluno = True;
																																break;
																															}
																															case Continue:{
																																repetir_menu_de_confirmacao = True;
																																break;
																															}
																														}
																														break;
																													}
																													case Voltar:{
																														repetir_menu_de_confirmacao = True;
																														break;
																													}
																												}
																											}while(repetir_menu_alterar_aluno == True);
																											break;
																										}
																										case menu_principal_op:{
																											repetir_menu_principal = True;
																											inicio = insere_ordenado(inicio, novo_aluno);
																											break;
																										}
																										case sair:{
																											if(deve_sair() == True)
																												saindo();
																											else
																												repetir_menu_de_confirmacao = True;
																											break;
																										}
																									}
																								}while(repetir_menu_de_confirmacao == True);
																								system("pause");
																								break;
																							}
																						}while(repetir_menu_turno == True);
																						break;
																					}
																				}
																			}while(repetir_semestre == True);
																		break;
																	}
																}
															}while(repetir_confirmacao_matricula == True);
															break;
														}
													}
												}while(repetir_matricula == True);
											}
										}while(repetir_menu_tipo_curso == True);
									}
								}while(repetir_menu_instituicao == True);
							}
						}while(repetir_menu_sexo == True);
					}
				} while(repetir_cadastro == True);
				break;
			}
			case localizar_aluno:{
				do{
					repetir_menu_busca = False;
					system("cls");
					switch(menu_busca(25)){
						case pelo_nome:{
							printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
							repetir_menu_busca = True;
							getch();
							break;
						}
						case pelo_semestre:{
							printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
							repetir_menu_busca = True;
							getch();
							break;
						}
						case pela_matricula:{
							printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
							repetir_menu_busca = True;
							getch();
							break;
						}
						case pelo_protocolo:{
							printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
							repetir_menu_busca = True;
							getch();
							break;
						}
						case listar:{
							int repetir_menu_listar = True;
							do{
								repetir_menu_listar = False;
								switch(menu_de_listagem(23)){
									case pelo_sexo:{
										int repetir_listagem_por_sexo = False;
										do{
											repetir_listagem_por_sexo = False;
											switch(menu_sexo(26)){
												case masculino:{
													listar_sexo(inicio, "Masculino");
													repetir_listagem_por_sexo = True;
													break;
												}
												case femenino:{
													listar_sexo(inicio, "Femenino");
													repetir_listagem_por_sexo = True;
													break;
												}
												case Voltar:{
													repetir_menu_listar = True;
													break;
												}
											}
										}while(repetir_listagem_por_sexo == True);
										break;
									}
									case pelo_turno:{
										printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
										repetir_menu_listar = True;
										getch();
										break;
									}
									case pela_instituicao:{
										printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
										repetir_menu_listar = True;
										getch();
										break;
									}
									case listar_todos:{
										imprimir_lista(inicio);
										getch();
										repetir_menu_listar = True;
										break;
									}
									case Voltar:{
										repetir_menu_busca = True;
										break;
									}
								}
							}while(repetir_menu_listar == True);
							break;
						}
						case Voltar:{
							repetir_menu_principal = True;
							break;
						}
					}
				}while(repetir_menu_busca == True);
				break;
			}
			case carregar_arquivo:{
				printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
				getch();
				repetir_menu_principal = True;
				break;
			}
			case exibir_relatorio:{
				printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
				repetir_menu_principal = True;
				getch();
				system("pause");
				repetir_menu_principal = True;
				break;
			}
			case configuracoes:{
				printf("EM DESENVOLVIMENTO\nAPERTE QUALQUER TECLA PARA VOLTAR AO MENU ANTERIOR...\n");
				getch();
				repetir_menu_principal = True;
				break;
			}
			case sobre:{
				menu_sobre();
				repetir_menu_principal = True;;
				break;
			}
			case sair:{
				if(deve_sair() == True)
					saindo();
				else
					repetir_menu_principal = True;
				break;
			}
			default:{
				printf("ESCOLHA INVALIDA TENTE NOVAMENTE\n");
				repetir_menu_principal = True;
				system("pause");
				break;
			}
		}
	} while(repetir_menu_principal == True);
	return 0;
}
int listar_sexo(Head* inicio, char sexo_escolhido[]){
	Aluno* o = NULL;
	o = inicio->proximo;
	int num_encontrado = 0;
	if(o == NULL){
		printf("Nenhuem Aluno foi cadastrado\n\n");
		getch();
	}
	else{
		while(o != NULL){
			if(strcmp(o->sexo, sexo_escolhido) == 0){
				imprime_aluno(o);
				o = o->proximo;
				num_encontrado++;
				getch();
			}
			else
				o = o->proximo;
		}
		if(num_encontrado == 0){
			printf("Nenhum aluno foi encontrado\n");
			getch();
		}
		else
			return 0;
	}
	return 0;
}

int ler_apenas_numero(int *valor, int tamanho){
	char ch;
	char digitado[20];
	int i = 0;
	int repetir_digitacao = True;
	do{
		repetir_digitacao = True;
		fflush(stdin);
		ch = getch();
		if(i >= tamanho && ch != 13 && ch != 8)
			getch();
		else{
			if(isalpha(ch))
				return Voltar;
			else if(isdigit(ch)){
				digitado[i] = ch;
				printf("%c", ch);
				i++;
			}
			else if(ch == 8 && i > 0){
				printf("\b \b");
				digitado[i] = '\0';
				i--;
			}
			else{
				if(i == tamanho)
					repetir_digitacao = False;
				else
	   				repetir_digitacao = True;
			}
		}
	}while(repetir_digitacao == True);
	digitado[i] = '\0';
	*valor = atoi(digitado);
	return Continue;
}
//====================================================================================================================================================================================
int confirma_matricula(Aluno *a){
	int resposta = 0;
	do{
		system("cls");
		printf("A matricula: %d\nEsta correta?\n", a->matricula);
		printf("Sim____(01)     Nao_____(02)\n");
		scanf("%d", &resposta);
		fflush(stdin);
		if(resposta == 1)
			return Continue;
 		else if(resposta == 2)
			return Voltar;
		else{
			printf("Escolha invalida, Tente novamente!\n");
			system("pause");
		}
	}while(resposta < 1 || resposta > 2);
}
//====================================================================================================================================================================================
int ler_apenas_letras(char *nome){
	char c, ca = '\0';
	int i = 0;
	int para_digitacao = False;
	setlocale(LC_ALL, "portuguese");
	do{
		c = getch();
		if(isdigit(c)){
			if(i != 0){
				while(i != 0){
					printf("\b \b");
					i--;
				}
				return Voltar;
			}
			else
				return Voltar;
		}
		else if(isalpha(c) || c == 32){
			if(islower(c) && (nome[i-1] == ' ' || i == 0)){
				nome[i] = toupper(c);
				printf("%c", toupper(c));
			}
			else{
				nome[i] = c;
				printf("%c", c);
			}
			i++;
			ca = c;
		}
		else if(c == 8 && i > 0){
			nome[i] = '\0';
			printf("\b \b");
			i--;
			ca = c;
		}
		else if((c == 13 && i > 0) && ca != '\0'){
			if(ca == ' '){
				nome[i-1] = '\0'; 
			}
			else{
				nome[i] = '\0';
			}
			para_digitacao = True;
		}
	}while(para_digitacao == False);
	return Continue;
}
//====================================================================================================================================================================================
int outra_instituicao(int titulo, Aluno* a){
	int i = 0;
	system("cls");
	switch(titulo){
		case 1:{
			op_ler(60, "Digite o Nome da Faculdade: ", 30, 2);
			return ler_apenas_letras(a->instituicao);
			break;
		}
		case 2:{
			op_ler(60, "Digite o Nome da Universidade: ", 33, 2);
			return ler_apenas_letras(a->instituicao);
			break;
		}
		case 3:{
			op_ler(60, "Digite o Nome do Curso Tecnico: ", 33, 2);
			return ler_apenas_letras(a->instituicao);
			break;
		}
		default:{
			op_ler(60, "Digite o Nome da Instituição: ", 28, 1);
			return ler_apenas_letras(a->instituicao);
			break;
		}
	}
}
//====================================================================================================================================================================================
Head* carregar_head(Head* o, FILE* pegar_no_arq) {
	o = (Head*) malloc(sizeof(Head));
	fscanf(pegar_no_arq, "%d\n", &o->numero_de_homens);
 	fscanf(pegar_no_arq, "%d\n", &o->numero_de_mulheres);
	fscanf(pegar_no_arq, "%d\n", &o->id_aluno_antigo);
	fscanf(pegar_no_arq, "%d\n", &o->id_aluno_novo);
	fscanf(pegar_no_arq, "%d\n", &o->numero_de_novos_cadastrados);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_facul);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_univer);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_curso_tec);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_pendentes);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_atualizados);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_manha);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_tarde);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_noite);
	fscanf(pegar_no_arq, "%d\n", &o->qtd_manha_tarde);
	o->tamanho_lista = o->numero_de_homens + o->numero_de_mulheres;
	return o;
}
//====================================================================================================================================================================================
Aluno* iniciar_estrutura_aluno(Aluno* o) {
	int i;
	zerar_vetor_char(o->nome, 100);
	zerar_vetor_char(o->sexo, 100);
	for(i = 0; i < 6; i++)
		o->turno_dominante[i] = 0;
	zerar_vetor_char(o->instituicao, 100);
	o->matricula = 0;
	o->semestre = 0;
	o->protocolo = 0;
	o->status_de_cadastro = 0;
	return o;
}
//====================================================================================================================================================================================
int verifica_se_vazio(FILE* arquivo) {
	if(arquivo)
		return True;
	else
		return False;
}
//====================================================================================================================================================================================
Head* insere_ordenado(Head* inicio, Aluno* o_novo){
	if(inicio->proximo == NULL){//verifica se a lista esta vazia;
		inicio->proximo = o_novo;
		o_novo->proximo = NULL;
		return inicio;
	}
	else{
		if(strcmp(o_novo->nome, inicio->proximo->nome) <= 0){
			o_novo->proximo = inicio->proximo;
			inicio->proximo = o_novo;
			return inicio;
		}
		Aluno* atual = inicio->proximo;
		Aluno* anterior = inicio->proximo;
		while(atual != NULL){
			if (strcmp(atual->nome, o_novo->nome) >= 0)
				break;
			anterior = atual;
			atual = atual->proximo;
		}
		o_novo->proximo = atual;
		anterior->proximo = o_novo;
	}
	return inicio;
}
//====================================================================================================================================================================================
void imprime_info(Head* o) {
	if(o->tamanho_lista == 0 )
		printf("Não existe nenhum cadastrado\n");
	else{
		if(o->tamanho_lista == 1 && o->numero_de_homens == 1){
			printf("Apenas um homem foi cadasatrado\n");
			if(o->qtd_facul > 0)
				printf("Ele Foi Cadastrado como Estudante de uma Faculdade\n");
			else if(o->qtd_univer > 0)
				printf("Ele Foi Cadastrado como Estudante de uma Universidade\n");
			else
				printf("Ele foi Cadastrado como Estudante de um Curso Tecnico\n");
		}
		else if(o->tamanho_lista == 1 && o->numero_de_mulheres == 1){
			printf("Apenas uma Mulher foi cadastrada\n");
			if(o->qtd_facul > 0)
				printf("Ela Foi Cadastrada como Estudante de uma Faculdade\n");
			else if(o->qtd_univer > 0)
				printf("Ela Foi Cadastrada como Estudante de uma Universidade\n");
			else
				printf("Ela foi Cadastrada como Estudante de um Curso Tecnico\n");
		}
		else{
			printf("No total foram cadastrados %d pessoas\n", o->tamanho_lista);
			printf("=================GENERO================\n");
			printf("sendo: %d Homens\n", o->numero_de_homens);
			printf("E: %d Mulheres\n", o->numero_de_mulheres);
			printf("==============INSTITUIÇÃO===============\n");
			printf("%d Alunos foram cadastrados como estudante de Faculdade\n", o->qtd_facul);
			printf("%d Alunos foram cadastrados como estudante de Universidade\n", o->qtd_univer);
			printf("E: %d Alunos foram cadastrados como estudante de Curso tecnico\n", o->qtd_curso_tec);
			printf("=================TURNO=================\n");
			printf("%d Alunos vai e volta pelo turno da manhã\n", o->qtd_manha);
			printf("%d Alunos vai e volta pelo turno da tarde\n", o->qtd_tarde);
			printf("%d Alunos vai pela manhã e volta pela tarde\n", o->qtd_manha_tarde);
			printf("%d Alunos vai e volta pelo turno da noite\n", o->qtd_noite);
			printf("=============STATUS DE CADASTRO=======\n");
			printf("%d Alunos foram cadastrado nesse semestre\n", o->numero_de_novos_cadastrados);
			printf("%d Alunos estão com a situação irregular\n", o->qtd_pendentes);
			printf("%d Alunos já efetuaram o recadastro\n", o->qtd_atualizados);

		}
	}
}
void imprimir_lista(Head* inicio){
	Aluno *pnt = NULL;
	pnt = inicio->proximo;
	if(pnt == NULL)
		printf("Nenhum Usuario Cadastrado\n");
	else
		while(pnt != NULL){
			imprime_aluno(pnt);
			pnt = pnt->proximo;
		}
	system("pause");
}
void zerar_vetor_char(char vetor[], int tamanho){
	int i = 0;
	for(i = 0; i < tamanho ; i++)
		vetor[i] = '\0';
}
//=====================================================================================================================================================================================
void impede_fechar(){//Fução repsonsavel por impedir que o terminal seja finalizado pelo "X";
	HWND hnd;
    HMENU menu;
    int i, j, cont;
    LPTSTR buffer;
    hnd = GetConsoleWindow();
    menu = GetSystemMenu(hnd, 0);
    cont = GetMenuItemCount(menu);
    j = -1;
    buffer = (TCHAR*) malloc (256 *sizeof(TCHAR));
    for (i=0; i<cont; i++) {
        GetMenuString(menu, i, buffer, 255, MF_BYPOSITION);
        if (!strcmp(buffer, "&Fechar")) {
            j = i;
            break;
        }
    }
    if (j >= 0)
        RemoveMenu(menu, j, MF_BYPOSITION);
}

