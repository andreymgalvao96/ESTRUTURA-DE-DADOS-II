/*Construa um programa em C com as seguintes funções:
• Uma função que receba um valor n e crie dinamicamente um vetor de n elementos e retorne 
um ponteiro.
• Uma função que receba um ponteiro para um vetor e um valor n e imprima os n elementos 
desse vetor.
• Construa também uma função que receba um ponteiro para um vetor e libere esta área 
de memória.
Ao final, crie uma função principal que leia um valor n e chame a função criada acima. Depois, 
a função principal deve ler os n elementos desse vetor. Então, a função principal deve chamar 
a função de impressão dos n elementos do vetor criado e, finalmente, liberar a memória alocada 
através da função criada para liberação.*/

#include <stdio.h>
#include <stdlib.h>

// Função para criar um vetor dinâmico de n elementos
int* criarVetor(int n) {
	int* vetor = malloc(n * sizeof(int));
	// Verificação de alocação de memória 
	if (vetor == NULL) {
		// Usar fprintf para garantir que a mensagem de erro seja vista
		fprintf(stderr, "Erro: Falha na alocacao de memoria!\n");
		exit(EXIT_FAILURE); // EXIT_FAILURE é mais idiomático que 1
	}
	return vetor;
}

// Função para imprimir os n elementos do vetor
void imprimirVetor(int* vetor, int n) {
	printf("Elementos do vetor:\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", vetor[i]);
	}
	printf("\n");
}

// Função para liberar a memória alocada
void liberarVetor(int* vetor) {
	free(vetor);
}

int main() {
	int n;
	int resultado_scanf;
	
	// --- Leitura do tamanho do vetor (com verificação de entrada) ---
	
	printf("Digite o tamanho do vetor: ");
	
	// Verifica se a leitura foi bem-sucedida e se o número é positivo
	resultado_scanf = scanf("%d", &n);
	
	if (resultado_scanf != 1 || n <= 0) {
		fprintf(stderr, "Erro: Tamanho do vetor invalido. Deve ser um numero inteiro positivo.\n");
		
		// Limpa o buffer de entrada em caso de erro
		while (getchar() != '\n' && !feof(stdin));
		
		return EXIT_FAILURE;
	}
	
	// Criação do vetor dinâmico
	int* vetor = criarVetor(n);
	
	// --- Leitura dos elementos do vetor (com verificação de entrada) ---
	
	printf("Digite os %d elementos do vetor:\n", n);
	for (int i = 0; i < n; i++) {
		printf("Elemento [%d]: ", i);
		resultado_scanf = scanf("%d", &vetor[i]);
		
		if (resultado_scanf != 1) {
			fprintf(stderr, "Erro: Entrada invalida. Encerrando programa.\n");
			
			// Limpa e libera antes de sair em caso de erro
			while (getchar() != '\n' && !feof(stdin));
			liberarVetor(vetor);
			return EXIT_FAILURE;
		}
	}
	
	// Impressão dos elementos do vetor
	imprimirVetor(vetor, n);
	
	// Liberação da memória alocada (essencial!)
	liberarVetor(vetor);
	
	return 0;
}
