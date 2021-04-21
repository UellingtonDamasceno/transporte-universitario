
enum var_controle{False = 0, True, Voltar, Continue, Proximo, Erro, Outro};

enum Escolhas_menu_principal{
	novo_cadastro = 10,
	localizar_aluno,
	carregar_arquivo,
	exibir_relatorio,
	configuracoes,
	sobre,
	sair
};
enum Escolhas_menu_sexo{
	masculino = 20,
	femenino
};
enum Escolhas_menu_instituicao{
	faculdade = 30,
	universidade,
	curso_tecnico_op
};
enum Escolhas_menu_faculdade{
	FAN = 40,
	FAT,
	FTC,
	PITAGORAS,
	UNIASSELVI
};
enum Escolhas_menu_universidade{
	UEFS = 50,
	UFRB,
	UNEF
};
enum Escolhas_menu_curso_tecnico{
	CEBRAC = 60,
	CEEP,
	IFBA,
	SENAI
};
enum Escolhas_menu_tipo_curso{
	humanas = 70,
	exatas,
	letras,
	engenharia,
	tecnicos,
	saude
};
enum Escolhas_curso_humanas{
	biologia = 80,
	biomedicina,
	educacao_fisica,
	historia,
	quimica
};
enum Escolhas_curso_engenharia{
	alimentos = 90,
	ambiental,
	civel,
	computacao,
	eletrica,
	mecanica,
	producao
};
enum Escolhas_curso_exatas{
	administracao = 100,
	ciencias_contabeis,
	fisica,
	matematica
};
enum Escolhas_menu_turno{
	matutino = 110,
	vespertino,
	noturno,
	diurno
};
enum Escolhas_curso_letras{
	espanhol = 120,
	frances,
	ingles,
	portugues,
	vernaculas
};
enum Escolhas_curso_saude{
	enfermagem = 130,
	farmacia,
	fisioterapia,
	medicina,
	veterinaria,
	nutricao,
	odontologia,
	psicologia,
	radiologia
};
enum Escolhas_curso_tecnico{
	analises_clinicas = 140,
	edificacoes,
	eletromecanica,
	eletrotecnica,
	enfermagem_ct,
	logistica,
	mecanica_ct,
	rotina_adm,
	seguranca_do_trabalho
};
enum Escolhas_menu_confirmacao{
	alterar_cadastro_op = 150,
	menu_principal_op
};
enum Escolhas_menu_alterar_aluno{
	nome_op = 160,
	sexo_op,
	instituicao_op,
	turno_dominante_op,
	curso_op,
	semestre_op,
	matricula_op
};
enum Escolhas_menu_busca{
	pelo_nome = 170,
	pelo_semestre,
	pela_matricula,
	listar,
	pelo_protocolo
};
enum Escolhas_menu_listagem{
	pelo_turno = 180,
	pelo_sexo,
	pela_instituicao,
	listar_todos
};

