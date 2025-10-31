#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura para representar uma sala (nó da árvore)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// Função para construir o mapa da mansão
Sala* construirMansao() {
    // Criar todas as salas
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* quartoPrincipal = criarSala("Quarto Principal");
    Sala* escritorio = criarSala("Escritorio");
    Sala* jardim = criarSala("Jardim");
    Sala* porao = criarSala("Porao");
    Sala* quartoVisitantes = criarSala("Quarto de Visitantes");
    Sala* banheiro = criarSala("Banheiro");
    Sala* lavanderia = criarSala("Lavanderia");
    Sala* despensa = criarSala("Despensa");
    
    // Montar a árvore conforme o layout da mansão
    // Hall de Entrada -> Sala de Estar (esq) e Cozinha (dir)
    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;
    
    // Sala de Estar -> Biblioteca (esq) e Quarto Principal (dir)
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = quartoPrincipal;
    
    // Cozinha -> Escritorio (esq) e Jardim (dir)
    cozinha->esquerda = escritorio;
    cozinha->direita = jardim;
    
    // Biblioteca -> Porao (esq) e NULL (dir - fim do caminho)
    biblioteca->esquerda = porao;
    biblioteca->direita = NULL;
    
    // Quarto Principal -> Quarto Visitantes (esq) e Banheiro (dir)
    quartoPrincipal->esquerda = quartoVisitantes;
    quartoPrincipal->direita = banheiro;
    
    // Escritorio -> NULL (esq - fim) e NULL (dir - fim)
    escritorio->esquerda = NULL;
    escritorio->direita = NULL;
    
    // Jardim -> Lavanderia (esq) e Despensa (dir)
    jardim->esquerda = lavanderia;
    jardim->direita = despensa;
    
    // Porao, QuartoVisitantes, Banheiro, Lavanderia, Despensa são folhas
    porao->esquerda = NULL;
    porao->direita = NULL;
    
    quartoVisitantes->esquerda = NULL;
    quartoVisitantes->direita = NULL;
    
    banheiro->esquerda = NULL;
    banheiro->direita = NULL;
    
    lavanderia->esquerda = NULL;
    lavanderia->direita = NULL;
    
    despensa->esquerda = NULL;
    despensa->direita = NULL;
    
    return hallEntrada;
}

// Função para explorar as salas
void explorarSalas(Sala* raiz) {
    Sala* salaAtual = raiz;
    char opcao;
    
    printf("=== DETECTIVE QUEST - EXPLORACAO DA MANSAO ===\n\n");
    
    while (salaAtual != NULL) {
        printf("Voce esta no/a: %s\n\n", salaAtual->nome);
        
        // Verificar se é uma sala sem saída (folha)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("*** Fim do caminho! Esta sala nao tem saidas. ***\n");
            printf("Voltando ao Hall de Entrada...\n\n");
            salaAtual = raiz; // Volta ao início
            continue;
        }
        
        // Mostrar opções disponíveis
        printf("Opcoes de exploracao:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  [E] - Ir para esquerda (%s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [D] - Ir para direita (%s)\n", salaAtual->direita->nome);
        }
        printf("  [S] - Sair da exploracao\n");
        
        printf("\nEscolha uma opcao: ");
        scanf(" %c", &opcao);
        opcao = tolower(opcao);
        
        switch (opcao) {
            case 'e':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("\n*** Nao ha sala a esquerda! Escolha outra direcao. ***\n\n");
                }
                break;
                
            case 'd':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("\n*** Nao ha sala a direita! Escolha outra direcao. ***\n\n");
                }
                break;
                
            case 's':
                printf("\nSaindo da exploracao...\n");
                return;
                
            default:
                printf("\n*** Opcao invalida! Use E, D ou S. ***\n\n");
                break;
        }
        printf("\n");
    }
}

// Função para liberar a memória da árvore
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) return;
    
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// Função para mostrar o mapa da mansão (em ordem)
void mostrarMapa(Sala* raiz, int nivel) {
    if (raiz == NULL) return;
    
    mostrarMapa(raiz->direita, nivel + 1);
    
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("%s\n", raiz->nome);
    
    mostrarMapa(raiz->esquerda, nivel + 1);
}

int main() {
    // Construir o mapa da mansão
    Sala* mansao = construirMansao();
    
    int opcao;
    
    do {
        printf("=========================================\n");
        printf("      DETECTIVE QUEST - NIVEL NOVATO     \n");
        printf("=========================================\n");
        printf("1. Explorar Mansao\n");
        printf("2. Ver Mapa da Mansao\n");
        printf("3. Sair do Jogo\n");
        printf("=========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                explorarSalas(mansao);
                break;
                
            case 2:
                printf("\n=== MAPA DA MANSAO ===\n");
                printf("(Visualizacao lateral - raiz a esquerda)\n\n");
                mostrarMapa(mansao, 0);
                printf("\nPressione Enter para continuar...");
                getchar(); // Limpar buffer
                getchar(); // Esperar Enter
                break;
                
            case 3:
                printf("Obrigado por jogar Detective Quest!\n");
                break;
                
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
        printf("\n");
        
    } while (opcao != 3);
    
    // Liberar memória
    liberarArvore(mansao);
    
    return 0;
}