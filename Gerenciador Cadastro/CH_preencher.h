
int preencher_faculdade();          /**/    int preencher_universidade();
int preencher_sexo();               /**/    int preencher_curso_CT();
int preencher_humanas();            /**/    int preencher_exatas();
int preencher_engenharia();         /**/    int ler_nome();
int preencher_saude();              /**/    int preencher_curso_tec();
int preencher_letras();

int preencher_exatas(int escolha_curso, Aluno* o){
	switch(escolha_curso){
		case administracao:{
			strcpy(o->curso, "Adminstra��o");
			break;
		}
		case ciencias_contabeis:{
			strcpy(o->curso, "Ci�ncias Contabeis");
			break;
		}
		case fisica:{
			strcpy(o->curso, "F�sica");
			break;
		}
		case matematica:{
			strcpy(o->curso, "Matem�tica");
			break;
		}
		case Outro:{
			return Outro;
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_humanas(int curso, Aluno* o){
	switch(curso){
		case biologia:{
			strcpy(o->curso, "Biologia");
			break;
		}
		case biomedicina:{
			strcpy(o->curso, "Biomedicina");
			break;
		}
		case educacao_fisica:{
			strcpy(o->curso, "Educa��o Fisica");
			break;
		}
		case historia:{
			strcpy(o->curso, "Historia");
			break;
		}
		case quimica:{
			strcpy(o->curso, "Quimica");
			break;
		}
		case Outro:{
			return Outro;
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_CT(int escolha_curso, Aluno* novo_aluno){
	switch(escolha_curso){
		case CEBRAC:{
			strcpy(novo_aluno->instituicao, "CEBRAC - CENTRO DE ENSINO BRASILEIRO E FORMA��O PROFISSIONAL");
			break;
		}
		case CEEP:{
			strcpy(novo_aluno->instituicao, "CEEP - CENTRO ESTADUAL DE EDUCA��O PROFISSIONAL");
			break;
		}
		case IFBA:{
			strcpy(novo_aluno->instituicao, "IFBA - INSTITUITO FEDERAL DA BAIHA");
			break;
		}
		case SENAI:{
			strcpy(novo_aluno->instituicao, "SENAI - SERVI�O NACIONAL DE APRENDIZAGEM INDUSTRIAL");
			break;
		}
		case Outro:{
			return Outro;
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_sexo(int escolha_sexo, Aluno* novo_aluno){
	switch(escolha_sexo){
		case masculino:{
			strcpy(novo_aluno->sexo, "Masculino");
			break;
		}
		case femenino:{
			strcpy(novo_aluno->sexo, "Femenino");
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_faculdade(int escolha_faculdade, Aluno* novo_aluno){
	switch(escolha_faculdade){
		case FAN:{
			strcpy(novo_aluno->instituicao, "FAN - FACULDADE NOBRE");
			break;
		}
		case FAT:{
			strcpy(novo_aluno->instituicao, "FAT - FACULDADE ANISO TEXEIRA");
			break;
		}
		case FTC:{
			strcpy(novo_aluno->instituicao, "FTC - FACULDADE DE TECNOLOGIA E CIENCIA");
			break;
		}
		case PITAGORAS:{
			strcpy(novo_aluno->instituicao, "PITAGORAS - FACULDADE PITAGORAS");
			break;
		}
		case UNIASSELVI:{
			strcpy(novo_aluno->instituicao, "UNIASSELVI");
			break;
		}
		case Outro:{
			return Outro;
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_universidade(int escolha_universidade, Aluno* novo_aluno){
	switch(escolha_universidade){
		case UEFS:{
			strcpy(novo_aluno->instituicao, "UEFS - UNIVERSIDADE ESTAUDAL DE FEIRA DE SANTANA");
			break;
		}
		case UFRB:{
			strcpy(novo_aluno->instituicao, "UFRB - UNIVERSIDADE FEDERAL DO RECONCAVO DA BAIHA");
			break;
		}
		case UNEF:{
			strcpy(novo_aluno->instituicao, "UNEF - UNIDADE DE ENSINO SUPERIOR DE FEIRA DE SANTANA");
			break;
		}
		case Outro:{
			return Outro;
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_engenharia(int escolha_curso, Aluno* o){
	switch(escolha_curso){
		case alimentos:{
			strcpy(o->curso, "Engenharia De Alimentos");
			break;
		}
		case ambiental:{
			strcpy(o->curso, "Engenharia Ambiental");
			break;
		}
		case civel:{
			strcpy(o->curso, "Engenharia Civil");
			break;
		}
		case computacao:{
			strcpy(o->curso, "Engenharia Da Computa��o");
			break;
		}
		case eletrica:{
			strcpy(o->curso, "Engenharia Eletrica");
			break;
		}
		case mecanica:{
			strcpy(o->curso, "Engenharia Mec�nica");
			break;
		}
		case producao:{
			strcpy(o->curso, "Engenharia De Produ��o");
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_letras(int escolha_curso, Aluno* o){
	switch(escolha_curso){
		case espanhol:{
			strcpy(o->curso, "Espanhol");
			break;
		}
		case frances:{
			strcpy(o->curso, "Letras Com Franc�s");
			break;
		}
		case ingles:{
			strcpy(o->curso, "Ingl�s");
			break;
		}
		case portugues:{
			strcpy(o->curso, "Ligua Portuguesa");
			break;
		}
		case vernaculas:{
			strcpy(o->curso, "Letras Com Vernaculas");
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_saude(int escolha_curso, Aluno *o){
	switch(escolha_curso){
		case enfermagem:{
			strcpy(o->curso, "Enfermagem");
			break;
		}
		case farmacia:{
			strcpy(o->curso, "F�rmacia");
			break;
		}
		case fisioterapia:{
			strcpy(o->curso, "Fisoterapia");
			break;
		}
		case medicina:{
			strcpy(o->curso, "Medicina");
			break;
		}
		case veterinaria:{
			strcpy(o->curso, "Medicina Veterinaria");
			break;
		}
		case nutricao:{
			strcpy(o->curso, "Nutric�o");
			break;
		}
		case odontologia:{
			strcpy(o->curso, "Odontologia");
			break;
		}
		case psicologia:{
			strcpy(o->curso, "Psicologia");
			break;
		}
		case radiologia:{
			strcpy(o->curso, "Radiologia");
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}
//====================================================================================================================================================================================
int preencher_curso_tec(int escolha_curso, Aluno* o){
	strcpy(o->curso, "T�cnico em ");
	switch(escolha_curso){
		case analises_clinicas:{
			strcat(o->curso, "Analises Clinicas");
			break;
		}
		case edificacoes:{
			strcat(o->curso, "Edifica��es");
			break;
		}
		case eletromecanica:{
			strcat(o->curso, "Eletromec�nica");
			break;
		}
		case eletrotecnica:{
			strcat(o->curso, "Eletrotecnico");
			break;
		}
		case enfermagem_ct:{
			strcat(o->curso, "Enfremagem");
			break;
		}
		case logistica:{
			strcat(o->curso, "Logistica");
			break;
		}
		case mecanica_ct:{
			strcat(o->curso, "Mec�nica");
			break;
		}
		case rotina_adm:{
			strcat(o->curso, "Rotina Administrativa");
			break;
		}
		case seguranca_do_trabalho:{
				strcat(o->curso, "Seguran�a do Trabalho");
			break;
		}
		case Voltar:{
			return Voltar;
			break;
		}
	}
	return Continue;
}


