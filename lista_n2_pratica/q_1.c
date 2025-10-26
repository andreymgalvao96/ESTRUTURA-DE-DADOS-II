/*Em uma agenda telefônica os contatos são cadastrados com os seguintes dados:
• Nome – nome do contato (máximo 40 caracteres);
• Telefone – cadeia de caracteres com o número do telefone do contato (máximo 15
caracteres);
• Celular – cadeia de caracteres com o número do celular do contato (máximo 15
caracteres);
• Email – cadeia de caracteres com o email do contato (máximo 40 caracteres);
• DataAniversario – data de aniversário do contato (contendo dia e mês);
Essas informações podem ser representadas em dois tipos estruturados: Data e
Contato.Utilizando listas encadeadas simples, escreva um programa que permita o
cadastro, edição, remoção, busca e impressão de contatos desta agenda telefônica. Os
elementos da lista encadeada para armazenar contatos são representados pela seguinte
estrutura:O seu programa deve implementar as seguintes funções:
cria_agenda – cria uma lista encadeada retornando um ponteiro para NULL;
insere_contato – insere um novo contato na lista encadeada no final;
lista_contatos – exibe na tela todos os dados dos contatos existentes na agenda;
busca_contato – busca um contato na agenda com base em um determinado nome
informado pelo usuário. A função retorna o endereço de memória do elemento encontrado
ou NULL caso o contato não seja encontrado;
remove_contato – deleta um determinado contato existente na agenda. A função deve
permitir ao usuário buscar por um contato na agenda (utilizando a função busca_contato
previamente criada) e em seguida remover da lista o contato. Se o contato buscado não for
encontrado, o programa deve exibir uma mensagem informando o usuário sobre esse fato;
atualiza_contato – modifica os dados de um contato já existente na agenda. A função deve
permitir ao usuário buscar por um contato na agenda (utilizando a função
busca_contatopreviamente criada) e em seguida alterar os dados do contato encontrado
com base nas novas informações fornecidas pelo usuário. Se o contato buscado não for
encontrado, o programa deve exibir uma mensagem informando o usuário sobre esse fato;
Em seguida, você deve implementar a função principal do programa que permita ao usuário
realizar todas as operações da agenda: cadastro, impressão, edição, remoção, busca e
remover duplicados.
O programa deve exibir um menu para o usuário escolher as operações desejadas.
1. Inserir Contato
2. Listar Contatos
3. Buscar Contato4. Editar Contato
5. Remover Contato
6. Sair
O programa deve permitir que o usuário realize operações na agenda de contatos até o
momento que ele desejar sair do programa (escolhendo a opção 6).*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar o tipo bool e melhorar a validação

#define MAX_NOME 40
#define MAX_SOBRENOME 40
#define MAX_CELULAR 15
#define MAX_EMAIL 40
// #define MAX_DATA 3 // Esta macro não era usada de forma eficaz e foi removida.

typedef struct {
	int dia;
	int mes;
} Data;

typedef struct Contato {
	char nome[MAX_NOME];
	char sobrenome[MAX_SOBRENOME];
	char celular[MAX_CELULAR];
	char email[MAX_EMAIL];
	Data dataAniversario;
	struct Contato* prox;
} Contato;
// Função simples para verificar se a data é razoável (apenas dia/mes)
bool valida_data(int dia, int mes) {
	if (mes < 1 || mes > 12) {
		return false;
	}
	if (dia < 1) {
		return false;
	}
	
	// Dias máximos por mês
	if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
		if (dia > 30) return false;
	} else if (mes == 2) {
		// Considerando apenas 29 dias no maximo para evitar complexidade com ano bissexto
		if (dia > 29) return false; 
	} else {
		if (dia > 31) return false;
	}
	
	return true;
}

Contato* cria_agenda() {
	return NULL;
}

Contato* insere_contato(Contato* agenda, Contato novoContato) {
	Contato* novo = (Contato*)malloc(sizeof(Contato));
	
	// Copia a estrutura (o seu método original, que funciona bem)
	*novo = novoContato;
	novo->prox = NULL;

	if (agenda == NULL) {
		return novo;
	}

	Contato* atual = agenda;
	while (atual->prox != NULL) {
		atual = atual->prox;
	}
	atual->prox = novo;
	return agenda;
}

void lista_contatos(Contato* agenda) {
	if (agenda == NULL) {
		printf("A agenda esta vazia.\n");
		return;
	}
	Contato* atual = agenda;
	while (atual != NULL) {
		printf("----------------------------\n");
		printf("Nome: %s\n", atual->nome);
		printf("Sobrenome: %s\n", atual->sobrenome);
		printf("Celular: %s\n", atual->celular);
		printf("Email: %s\n", atual->email);
		printf("Data de Aniversario: %02d/%02d\n", atual->dataAniversario.dia, atual->dataAniversario.mes);
		atual = atual->prox;
	}
	printf("----------------------------\n");
}

Contato* busca_contato(Contato* agenda, const char* nome) {
	Contato* atual = agenda;
	while (atual != NULL) {
		if (strcmp(atual->nome, nome) == 0) {
			return atual;
		}
		atual = atual->prox;
	}
	return NULL;
}

Contato* remove_contato(Contato* agenda, const char* nome) {
	Contato* atual = agenda;
	Contato* anterior = NULL;  
	while (atual != NULL) {
		if (strcmp(atual->nome, nome) == 0) {
			if (anterior == NULL) {
				// O contato a ser removido é a cabeça da lista
				Contato* temp = atual->prox;
				free(atual);
				printf("Contato '%s' removido com sucesso.\n", nome);
				return temp;  // A nova cabeça
			} else {
				// O contato está no meio ou fim
				anterior->prox = atual->prox;
				free(atual);
				printf("Contato '%s' removido com sucesso.\n", nome);
				return agenda;  // A cabeça da lista não mudou
			}
		}
		anterior = atual;
		atual = atual->prox;
	}
	printf("Contato nao encontrado.\n");
	return agenda;
}

// Adicionada validação e limpeza do buffer de entrada (getchar)
void atualiza_contato(Contato* contato) {
	int dia, mes;
	
	printf("Atualizando contato: %s\n", contato->nome);
	
	printf("Novo nome (atual: %s): ", contato->nome);
	fgets(contato->nome, MAX_NOME, stdin);
	contato->nome[strcspn(contato->nome, "\n")] = 0;
	
	printf("Novo sobrenome (atual: %s): ", contato->sobrenome);
	fgets(contato->sobrenome, MAX_SOBRENOME, stdin);
	contato->sobrenome[strcspn(contato->sobrenome, "\n")] = 0;
	
	printf("Novo celular (atual: %s): ", contato->celular);
	fgets(contato->celular, MAX_CELULAR, stdin);
	contato->celular[strcspn(contato->celular, "\n")] = 0;
	
	printf("Novo email (atual: %s): ", contato->email);
	fgets(contato->email, MAX_EMAIL, stdin);
	contato->email[strcspn(contato->email, "\n")] = 0;
	
	// Nova leitura e validação da data
	do {
		printf("Novo dia de aniversario (atual: %02d): ", contato->dataAniversario.dia);
		if (scanf("%d", &dia) != 1) {
			printf("Entrada invalida. Tente novamente.\n");
			while (getchar() != '\n'); // Limpa buffer em caso de erro de leitura
			dia = 0; // Força nova iteração
		} else {
			printf("Novo mes de aniversario (atual: %02d): ", contato->dataAniversario.mes);
			if (scanf("%d", &mes) != 1) {
				printf("Entrada invalida. Tente novamente.\n");
				while (getchar() != '\n'); 
				dia = 0; // Força nova iteração
			} else {
				if (!valida_data(dia, mes)) {
					printf("Data invalida (dia/mes). Tente novamente.\n");
					dia = 0; // Força nova iteração
				}
			}
		}
		getchar(); // Limpa o \n restante do último scanf
	} while (dia == 0 || mes == 0); 
	
	contato->dataAniversario.dia = dia;
	contato->dataAniversario.mes = mes;
	
	printf("Contato atualizado com sucesso!\n");
}

int main() {
	Contato* agenda = cria_agenda();
	int opcao;
	int dia, mes; // Variáveis temporárias para a data

	// Loop principal do menu
	do {
		printf("\n===== AGENDA DE CONTATOS =====\n");
		printf("1. Inserir Contato\n");
		printf("2. Listar Contatos\n");
		printf("3. Buscar Contato\n");
		printf("4. Editar Contato\n");
		printf("5. Remover Contato\n");
		printf("6. Sair\n");
		printf("Escolha uma opcao: ");

		// CORREÇÃO: Verifica se a leitura da opção foi bem sucedida
		if (scanf("%d", &opcao) != 1) {
			printf("Opcao invalida. Tente novamente.\n");
			while (getchar() != '\n'); // Limpa o buffer em caso de erro
			opcao = 0; // Força a repetição do loop
		} else {
			getchar(); // Limpa o \n restante do scanf
		}

		if (opcao == 1) {
			Contato novoContato;
			
			printf("\n--- NOVO CONTATO ---\n");
			printf("Nome: ");
			fgets(novoContato.nome, MAX_NOME, stdin);
			novoContato.nome[strcspn(novoContato.nome, "\n")] = 0; 
			
			printf("Sobrenome: ");
			fgets(novoContato.sobrenome, MAX_SOBRENOME, stdin);
			novoContato.sobrenome[strcspn(novoContato.sobrenome, "\n")] = 0; 
			
			printf("Celular: ");
			fgets(novoContato.celular, MAX_CELULAR, stdin);
			novoContato.celular[strcspn(novoContato.celular, "\n")] = 0; 
			
			printf("Email: ");
			fgets(novoContato.email, MAX_EMAIL, stdin);
			novoContato.email[strcspn(novoContato.email, "\n")] = 0; 
			
			// Validação da data no cadastro
			do {
				printf("Dia de aniversario (1-31): ");
				if (scanf("%d", &dia) != 1) {
					printf("Entrada invalida. Tente novamente.\n");
					while (getchar() != '\n');
					dia = 0;
				} else {
					printf("Mes de aniversario (1-12): ");
					if (scanf("%d", &mes) != 1) {
						printf("Entrada invalida. Tente novamente.\n");
						while (getchar() != '\n'); 
						dia = 0;
					} else {
						if (!valida_data(dia, mes)) {
							printf("Data invalida (dia/mes). Tente novamente.\n");
							dia = 0;
						}
					}
				}
				getchar(); // Limpa o \n restante do ultimo scanf
			} while (dia == 0 || mes == 0);

			novoContato.dataAniversario.dia = dia;
			novoContato.dataAniversario.mes = mes;

			agenda = insere_contato(agenda, novoContato);
			printf("Contato inserido com sucesso!\n");

		} else if (opcao == 2) {
			printf("\n--- LISTA DE CONTATOS ---\n");
			lista_contatos(agenda);
			
		} else if (opcao == 3) {
			char nomeBusca[MAX_NOME];
			printf("\n--- BUSCAR CONTATO ---\n");
			printf("Digite o nome do contato para buscar: ");
			fgets(nomeBusca, MAX_NOME, stdin);
			nomeBusca[strcspn(nomeBusca, "\n")] = 0; 

			Contato* contatoEncontrado = busca_contato(agenda, nomeBusca);
			if (contatoEncontrado != NULL) {
				printf("--- CONTATO ENCONTRADO ---\n");
				printf("Nome: %s\n", contatoEncontrado->nome);
				printf("Sobrenome: %s\n", contatoEncontrado->sobrenome);
				printf("Celular: %s\n", contatoEncontrado->celular);
				printf("Email: %s\n", contatoEncontrado->email);
				printf("Data de Aniversario: %02d/%02d\n", contatoEncontrado->dataAniversario.dia, contatoEncontrado->dataAniversario.mes);
				printf("--------------------------\n");
			} else {
				printf("Contato nao encontrado.\n");
			}
		} else if (opcao == 4) {
			char nomeEditar[MAX_NOME];
			printf("\n--- EDITAR CONTATO ---\n");
			printf("Digite o nome do contato para editar: ");
			fgets(nomeEditar, MAX_NOME, stdin);
			nomeEditar[strcspn(nomeEditar, "\n")] = 0;
			
			Contato* contatoParaEditar = busca_contato(agenda, nomeEditar);
			if (contatoParaEditar != NULL) {
				atualiza_contato(contatoParaEditar);
			} else {
				printf("Contato nao encontrado.\n");
			}
		} else if (opcao == 5) {
			char nomeRemover[MAX_NOME];
			printf("\n--- REMOVER CONTATO ---\n");
			printf("Digite o nome do contato para remover: ");
			fgets(nomeRemover, MAX_NOME, stdin);
			nomeRemover[strcspn(nomeRemover, "\n")] = 0;
			agenda = remove_contato(agenda, nomeRemover);
		} else if (opcao == 6) {
			printf("Saindo do programa. Liberando memoria...\n");
		} else if (opcao != 0) {
			printf("Opcao invalida. Por favor, escolha uma opcao entre 1 e 6.\n");
		}
	} while (opcao != 6);
	
	// Limpeza de memória antes de sair
	Contato* atual = agenda;
	while (atual != NULL) {
		Contato* temp = atual;
		atual = atual->prox;
		free(temp);
	}
	
	return 0;
}