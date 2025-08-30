#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração do vetor para armazenar 5 territórios
    struct Territorio territorios[5];
    
    printf("=== SISTEMA DE CADASTRO DE TERRITORIOS ===\n\n");
    
    // Loop para cadastrar os 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do territorio %d:\n", i + 1);
        
        // Entrada do nome
        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);
        
        // Entrada da cor
        printf("Digite a cor do exercito, (Ex.AZUL): ");
        scanf("%s", territorios[i].cor);
        
        // Entrada do número de tropas
        printf("Digite a quantidade de tropas, (Ex.7): ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n"); // Linha em branco para melhor organização
    }
    
    // Exibição dos dados cadastrados
    printf("=== DADOS DOS TERRITORIOS CADASTRADOS ===\n\n");
    
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
        printf("----------------------------\n");
    }
    
    return 0;
}
