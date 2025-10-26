#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Estrutura para um nó da pilha
typedef struct Node {
	double value;
	struct Node* next;
} Node;

// Estrutura para controle da pilha
typedef struct Stack {
	Node* top;
} Stack;

// Função para criar uma nova pilha vazia
Stack* createStack() {
	// Boa Prática: usar sizeof *ptr e evitar cast em C
	Stack* stack = malloc(sizeof *stack);
	if (stack == NULL) {
		// Usar fprintf(stderr, ...) para mensagens de erro
		fprintf(stderr, "Erro: Falha na alocacao de memoria para Stack.\n");
		exit(EXIT_FAILURE); // Usar EXIT_FAILURE
	}
	stack->top = NULL;
	return stack;
}

// Função para verificar se a pilha está vazia
int isEmpty(Stack* stack) {
	return stack->top == NULL;
}

// Função para adicionar um valor ao topo da pilha
void push(Stack* stack, double value) {
	/* Boa prática: usar sizeof *ptr e evitar cast em C */
	Node* newNode = malloc(sizeof *newNode);
	if (newNode == NULL) {
		fprintf(stderr, "Erro: Falha na alocacao de memoria para novo no.\n");
		/* NOTA: Em um programa maior, você poderia tentar recuperar em vez de sair. */
		exit(EXIT_FAILURE);
	}
	newNode->value = value;
	newNode->next = stack->top;
	stack->top = newNode;
}

// Função para remover e retornar o valor do topo da pilha
double pop(Stack* stack) {
	if (isEmpty(stack)) {
		// Aqui, em vez de sair, poderíamos retornar um valor sentinela (NaN ou ERRO),
		// mas como evaluateRPN já verifica antes de pop, podemos manter o exit para
		// tratar erros internos ou expressões malformadas não detectadas.
		fprintf(stderr, "Erro: Tentativa de remover elemento de pilha vazia (erro interno).\n");
		exit(EXIT_FAILURE);
	}
	Node* temp = stack->top;
	double value = temp->value;
	stack->top = temp->next;
	free(temp);
	return value;
}

// Função para liberar toda a memória alocada para a pilha
void freeStack(Stack* stack) {
	if (stack == NULL) return; // Verificação de segurança

	Node* current = stack->top;
	Node* next;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	free(stack);
}

// Função para avaliar a expressão RPN
double evaluateRPN(char* expression) {
	Stack* stack = createStack();
	// NOTA: strtok modifica o string de entrada (expression). 
	// Isso é aceitável, pois argv[1] é uma cópia modificável pelo sistema.
	char* token = strtok(expression, " ");
	double result = 0.0; // Inicializa com 0.0

	while (token != NULL) {
		// Se for um operador: verifica se é um char e se tem apenas um char
		if (strlen(token) == 1 && strchr("+-*/", token[0]) != NULL) {

			// Valida se há operandos suficientes (dois)
			if (isEmpty(stack)) {
				fprintf(stderr, "Erro: Expressao malformada (operando 2 insuficiente para '%c').\n", token[0]);
				freeStack(stack);
				exit(EXIT_FAILURE);
			}
			double val2 = pop(stack);

			if (isEmpty(stack)) {
				// Se a pilha estiver vazia aqui, val2 foi o único elemento.
				fprintf(stderr, "Erro: Expressao malformada (operando 1 insuficiente para '%c').\n", token[0]);
				push(stack, val2); // Empurra val2 de volta para freeStack não quebrar
				freeStack(stack);
				exit(EXIT_FAILURE);
			}
			double val1 = pop(stack);

			// Realiza a operação
			switch (token[0]) {
				case '+':
					result = val1 + val2;
					break;
				case '-':
					result = val1 - val2;
					break;
				case '*':
					result = val1 * val2;
					break;
				case '/':
					if (val2 == 0.0) { // Comparar double com 0.0 é ok neste contexto
						fprintf(stderr, "Erro: Tentativa de divisao por zero.\n");
						freeStack(stack);
						exit(EXIT_FAILURE);
					}
					result = val1 / val2;
					break;
				default:
					// Este caso não deve ocorrer devido à verificação inicial
					fprintf(stderr, "Erro: Operador desconhecido '%s'.\n", token);
					freeStack(stack);
					exit(EXIT_FAILURE);
			}
			push(stack, result);
		}
		// Se for um número
		else {
			char* endptr;
			// Converte a string para double. strtod é mais seguro que atof.
			double value = strtod(token, &endptr);

			// Se *endptr não for '\0', significa que houve caracteres não numéricos após o número.
			if (*endptr != '\0') {
				fprintf(stderr, "Erro: Token invalido '%s'.\n", token);
				freeStack(stack);
				exit(EXIT_FAILURE);
			}
			push(stack, value);
		}
		token = strtok(NULL, " ");
	}

	// --- Verificação Final ---
	if (isEmpty(stack)) {
		fprintf(stderr, "Erro: Expressao vazia ou malformada.\n");
		freeStack(stack);
		exit(EXIT_FAILURE);
	}

	result = pop(stack);

	if (!isEmpty(stack)) {
		fprintf(stderr, "Erro: Expressao malformada (operandos em excesso).\n");
		freeStack(stack);
		exit(EXIT_FAILURE);
	}

	freeStack(stack); // Libera toda a memória alocada para a pilha
	return result;
}

int main(int argc, char* argv[]) {
	// Verifica se foi fornecido um argumento
	if (argc != 2) {
		printf("Uso: %s \"expressao RPN\"\n", argv[0]);
		printf("Exemplo: %s \"10 5 + 2 *\"\n", argv[0]);
		return EXIT_FAILURE; // Usar EXIT_FAILURE
	}

	// Avalia a expressão e imprime o resultado
	double result = evaluateRPN(argv[1]);
	printf("Resultado: %.2f\n", result);

	return EXIT_SUCCESS; // Usar EXIT_SUCCESS (0)
}