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
void liberarMemoria(struct Territorio* mapa, char* missaoJogador);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char* corJogador);
void exibirMissao(char* missao);
void encontrarCoresDisponiveis(struct Territorio* mapa, int tamanho, char coresDisponiveis[][10], int* totalCores);

// Vetor de missões pré-definidas
char* missoes[] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas de uma cor inimiga",
    "Conquistar a maioria dos territorios",
    "Destruir completamente um exercito inimigo",
    "Manter 10 tropas em seu territorio principal"
};
int totalMissoes = 5;

int main() {
    int quantidade;
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    
    printf("=== SISTEMA DE CADASTRO E ATAQUE DE TERRITORIOS ===\n\n");
    
    // Solicita a quantidade de territórios
    printf("Digite a quantidade de territorios a serem cadastrados: ");
    scanf("%d", &quantidade);
    
    // Aloca memória dinamicamente para os territórios
    struct Territorio* territorios = cadastrarTerritorios(quantidade);
    
    // Determina a cor do jogador (assumindo que o primeiro território é do jogador)
    char corJogador[10];
    strcpy(corJogador, territorios[0].cor);
    
    // Aloca e atribui missão ao jogador
    char* missaoJogador = (char*)malloc(100 * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para a missao!\n");
        liberarMemoria(territorios, NULL);
        return 1;
    }
    
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("\n=== MISSAO DO JOGADOR ===\n");
    exibirMissao(missaoJogador);
    printf("==========================\n");
    
    // Exibe os territórios cadastrados
    exibirTerritorios(territorios, quantidade);
    
    // Menu de ataques
    int opcao;
    int vitoria = 0;
    do {
        printf("\n=== MENU DE ACOES ===\n");
        printf("1 - Realizar ataque\n");
        printf("2 - Exibir territorios\n");
        printf("3 - Ver minha missao\n");
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
                
                // Verifica se a missão foi cumprida após o ataque
                if (verificarMissao(missaoJogador, territorios, quantidade, corJogador)) {
                    printf("\n🎉 PARABENS! VOCE CUMPRIU SUA MISSAO E VENCEU O JOGO! 🎉\n");
                    vitoria = 1;
                    opcao = 0; // Encerra o jogo
                }
                break;
            }
            case 2:
                exibirTerritorios(territorios, quantidade);
                break;
            case 3:
                exibirMissao(missaoJogador);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
        // Verifica vitória ao final de cada turno
        if (!vitoria && opcao != 0) {
            if (verificarMissao(missaoJogador, territorios, quantidade, corJogador)) {
                printf("\n🎉 PARABENS! VOCE CUMPRIU SUA MISSAO E VENCEU O JOGO! 🎉\n");
                vitoria = 1;
                opcao = 0;
            }
        }
    } while (opcao != 0);
    
    // Libera a memória alocada
    liberarMemoria(territorios, missaoJogador);
    
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
void liberarMemoria(struct Territorio* mapa, char* missaoJogador) {
    free(mapa);
    if (missaoJogador != NULL) {
        free(missaoJogador);
    }
    printf("Memoria liberada com sucesso!\n");
}

// Função para atribuir uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Função para exibir a missão do jogador
void exibirMissao(char* missao) {
    printf("Sua missao: %s\n", missao);
}

// Função para encontrar cores disponíveis no mapa
void encontrarCoresDisponiveis(struct Territorio* mapa, int tamanho, char coresDisponiveis[][10], int* totalCores) {
    *totalCores = 0;
    
    for (int i = 0; i < tamanho; i++) {
        int encontrada = 0;
        
        // Verifica se a cor já foi adicionada
        for (int j = 0; j < *totalCores; j++) {
            if (strcmp(mapa[i].cor, coresDisponiveis[j]) == 0) {
                encontrada = 1;
                break;
            }
        }
        
        // Se não foi encontrada, adiciona ao array
        if (!encontrada) {
            strcpy(coresDisponiveis[*totalCores], mapa[i].cor);
            (*totalCores)++;
        }
    }
}

// Função para verificar se a missão foi cumprida
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char* corJogador) {
    // Encontra todas as cores disponíveis no mapa
    char coresDisponiveis[10][10];
    int totalCores;
    encontrarCoresDisponiveis(mapa, tamanho, coresDisponiveis, &totalCores);
    
    // Lógica de verificação para cada tipo de missão
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        // Verifica se há 3 territórios da mesma cor em sequência
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && 
                strcmp(mapa[i+1].cor, corJogador) == 0 && 
                strcmp(mapa[i+2].cor, corJogador) == 0) {
                return 1;
            }
        }
    }
    else if (strcmp(missao, "Eliminar todas as tropas de uma cor inimiga") == 0) {
        // Verifica se alguma cor inimiga foi eliminada
        for (int i = 0; i < totalCores; i++) {
            if (strcmp(coresDisponiveis[i], corJogador) != 0) {
                int corExiste = 0;
                
                // Verifica se a cor ainda existe no mapa
                for (int j = 0; j < tamanho; j++) {
                    if (strcmp(mapa[j].cor, coresDisponiveis[i]) == 0) {
                        corExiste = 1;
                        break;
                    }
                }
                
                // Se a cor não existe mais, missão cumprida
                if (!corExiste) {
                    return 1;
                }
            }
        }
    }
    else if (strcmp(missao, "Conquistar a maioria dos territorios") == 0) {
        // Verifica se o jogador tem mais da metade dos territórios
        int territoriosJogador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territoriosJogador++;
            }
        }
        return territoriosJogador > tamanho / 2;
    }
    else if (strcmp(missao, "Destruir completamente um exercito inimigo") == 0) {
        // Verifica se algum exercito inimigo foi completamente destruído
        for (int i = 0; i < totalCores; i++) {
            if (strcmp(coresDisponiveis[i], corJogador) != 0) {
                int corExiste = 0;
                
                // Verifica se a cor ainda existe no mapa
                for (int j = 0; j < tamanho; j++) {
                    if (strcmp(mapa[j].cor, coresDisponiveis[i]) == 0) {
                        corExiste = 1;
                        break;
                    }
                }
                
                // Se a cor não existe mais, missão cumprida
                if (!corExiste) {
                    return 1;
                }
            }
        }
    }
    else if (strcmp(missao, "Manter 10 tropas em seu territorio principal") == 0) {
        // Verifica se o primeiro território do jogador tem pelo menos 10 tropas
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                return mapa[i].tropas >= 10;
            }
        }
    }
    
    return 0;
}