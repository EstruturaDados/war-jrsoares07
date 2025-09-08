#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Protótipos das funções
struct Territorio* cadastrarTerritorios(int quantidade);
void exibirTerritorios(struct Territorio* territorios, int quantidade);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);

int main() {
    int quantidade;
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    printf("=== SISTEMA DE CADASTRO E ATAQUE DE TERRITORIOS ===\n\n");
    
    // Solicita a quantidade de territórios
    printf("Digite a quantidade de territorios a serem cadastrados: ");
    scanf("%d", &quantidade);
    
    // Aloca memória dinamicamente para os territórios
    struct Territorio* territorios = cadastrarTerritorios(quantidade);
    
    // Exibe os territórios cadastrados
    exibirTerritorios(territorios, quantidade);
    
    // Menu de ataques
    int opcao;
    do {
        printf("\n=== MENU DE ACOES ===\n");
        printf("1 - Realizar ataque\n");
        printf("2 - Exibir territorios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: {
                int indiceAtacante, indiceDefensor;
                
                // Exibe os territórios para seleção
                exibirTerritorios(territorios, quantidade);
                
                // Solicita o território atacante
                printf("Digite o numero do territorio ATACANTE: ");
                scanf("%d", &indiceAtacante);
                indiceAtacante--; // Ajusta para índice do vetor
                
                // Solicita o território defensor
                printf("Digite o numero do territorio DEFENSOR: ");
                scanf("%d", &indiceDefensor);
                indiceDefensor--; // Ajusta para índice do vetor
                
                // Valida as escolhas
                if (indiceAtacante < 0 || indiceAtacante >= quantidade || 
                    indiceDefensor < 0 || indiceDefensor >= quantidade) {
                    printf("Erro: Indices invalidos!\n");
                    break;
                }
                
                if (indiceAtacante == indiceDefensor) {
                    printf("Erro: Um territorio nao pode atacar a si mesmo!\n");
                    break;
                }
                
                if (strcmp(territorios[indiceAtacante].cor, territorios[indiceDefensor].cor) == 0) {
                    printf("Erro: Nao pode atacar um territorio da mesma cor!\n");
                    break;
                }
                
                // Realiza o ataque
                printf("\n=== INICIANDO ATAQUE ===\n");
                printf("%s (%s) ataca %s (%s)\n", 
                       territorios[indiceAtacante].nome, territorios[indiceAtacante].cor,
                       territorios[indiceDefensor].nome, territorios[indiceDefensor].cor);
                
                atacar(&territorios[indiceAtacante], &territorios[indiceDefensor]);
                
                // Exibe os territórios após o ataque
                printf("\n=== SITUACAO POS-ATAQUE ===\n");
                exibirTerritorios(territorios, quantidade);
                break;
            }
            case 2:
                exibirTerritorios(territorios, quantidade);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
    // Libera a memória alocada
    liberarMemoria(territorios);
    
    return 0;
}

// Função para cadastrar territórios
struct Territorio* cadastrarTerritorios(int quantidade) {
    // Aloca memória dinamicamente para o vetor de territórios
    struct Territorio* territorios = (struct Territorio*)calloc(quantidade, sizeof(struct Territorio));
    
    if (territorios == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        exit(1);
    }
    
    // Preenche os dados dos territórios
    for (int i = 0; i < quantidade; i++) {
        printf("\nCadastro do territorio %d:\n", i + 1);
        
        // Entrada do nome
        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);
        
        // Entrada da cor
        printf("Digite a cor do exercito (Ex. AZUL): ");
        scanf("%s", territorios[i].cor);
        
        // Entrada do número de tropas
        printf("Digite a quantidade de tropas (Ex. 7): ");
        scanf("%d", &territorios[i].tropas);
    }
    
    return territorios;
}

// Função para exibir os territórios
void exibirTerritorios(struct Territorio* territorios, int quantidade) {
    printf("\n=== DADOS DOS TERRITORIOS ===\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n", 
               i + 1, 
               territorios[i].nome, 
               territorios[i].cor, 
               territorios[i].tropas);
    }
    printf("----------------------------\n");
}

// Função para simular um ataque entre territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Simula a rolagem de dados para atacante e defensor
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);
    
    // Determina o resultado do ataque
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("O atacante venceu a batalha!\n");
        
        // O defensor perde metade de suas tropas
        int tropasPerdidas = defensor->tropas / 2;
        defensor->tropas -= tropasPerdidas;
        
        // Atacante ganha metade das tropas do defensor
        atacante->tropas += tropasPerdidas;
        
        // O território muda de dono (cor)
        printf("O territorio %s agora pertence ao exercito %s!\n", defensor->nome, atacante->cor);
        strcpy(defensor->cor, atacante->cor);
        
    } else if (dadoAtacante < dadoDefensor) {
        // Defensor vence
        printf("O defensor venceu a batalha!\n");
        
        // Atacante perde uma tropa
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa!\n");
        } else {
            printf("O atacante nao tem tropas suficientes para perder!\n");
        }
        
    } else {
        // Empate
        printf("A batalha terminou em empate! Nada mudou.\n");
    }
}

// Função para liberar a memória alocada
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
    printf("Memoria liberada com sucesso!\n");
}