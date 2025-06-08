#include <stdio.h>
#include <stdlib.h>

#define TAM 27

typedef struct Aresta {
    int destino;
    double peso;
    struct Aresta* prox;
} Aresta;

typedef struct Vertice {
    Aresta* inicio;
} Vertice;

const char* estados[TAM] = {
    "Amazonas", "Amapa", "Acre", "Para", "Roraima", "Rondonia", "Tocantins",         // 0-6 Norte
    "Bahia", "Piaui", "Alagoas", "Sergipe", "Ceara", "Maranhao", "Pernambuco", "Paraiba", // 7-14 Nordeste
    "Distrito Federal", "Goias", "Mato Grosso", "Mato Grosso do Sul",                // 15-18 Centro-Oeste
    "Espirito Santo", "Rio de Janeiro", "Minas Gerais", "Rio Grande do Norte", "Sao Paulo", // 19-23 Sudeste
    "Parana", "Rio Grande do Sul", "Santa Catarina"                                   // 24-26 Sul
};

int regiaoDe[TAM] = {
    0,0,0,0,0,0,0,   // Norte
    1,1,1,1,1,1,1,1, // Nordeste
    2,2,2,2,         // Centro-Oeste
    3,3,3,1,3,       // Sudeste (RN em lugar incomum)
    4,4,4            // Sul
};

const char* regioes[5] = {"Norte", "Nordeste", "Centro-Oeste", "Sudeste", "Sul"};

// Mostra tabela de estados
void exibirTabelaEstados() {
    printf("\n=== Tabela de Estados ===\n");
    for(int i = 0; i < TAM; i++) {
        printf("%2d - %s\n", i + 1, estados[i]);
    }
    printf("=========================\n\n");
}

void adicionarAresta(Vertice grafo[], int origem, int destino, double peso) {
    Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
    nova->destino = destino;
    nova->peso = peso;
    nova->prox = grafo[origem].inicio;
    grafo[origem].inicio = nova;
}

void exibirGrafo(Vertice grafo[]) {
    printf("\n=== Grafo de Trocas Monetárias ===\n");
    for(int i = 0; i < TAM; i++) {
        printf("%s troca com:\n", estados[i]);
        Aresta* temp = grafo[i].inicio;
        while(temp != NULL) {
            printf("  -> %s, Valor: R$ %.2f\n", estados[temp->destino], temp->peso);
            temp = temp->prox;
        }
        printf("\n");
    }
}

void relatorioPorRegiao(Vertice grafo[]) {
    double soma[5] = {0.0};

    for(int i = 0; i < TAM; i++) {
        int regiao = regiaoDe[i];
        Aresta* temp = grafo[i].inicio;
        while(temp != NULL) {
            soma[regiao] += temp->peso;
            temp = temp->prox;
        }
    }

    printf("\n=== Relatório por Região (Total de Saídas) ===\n");
    for(int i = 0; i < 5; i++) {
        printf("%s: R$ %.2f\n", regioes[i], soma[i]);
    }
}

void relatorioPorEstado(Vertice grafo[]) {
    double saiu[TAM] = {0.0};
    double entrou[TAM] = {0.0};

    for(int i = 0; i < TAM; i++) {
        Aresta* temp = grafo[i].inicio;
        while(temp != NULL) {
            saiu[i] += temp->peso;
            entrou[temp->destino] += temp->peso;
            temp = temp->prox;
        }
    }

    printf("\n=== Relatório por Estado ===\n");
    for(int i = 0; i < TAM; i++) {
        printf("%-20s | Saiu: R$ %.2f | Entrou: R$ %.2f\n", estados[i], saiu[i], entrou[i]);
    }
}

int main() {
    Vertice grafo[TAM];
    for(int i = 0; i < TAM; i++) grafo[i].inicio = NULL;

    int origem, destino, numTrocas;
    double valor;

    printf("Digite o número de trocas (arestas): ");
    scanf("%d", &numTrocas);

    for(int i = 0; i < numTrocas; i++) {
        printf("\nTroca %d:\n", i + 1);
        exibirTabelaEstados();

        printf("Origem (1 a 27): ");
        scanf("%d", &origem);

        printf("Destino (1 a 27): ");
        scanf("%d", &destino);

        printf("Valor monetário: ");
        scanf("%lf", &valor);

        adicionarAresta(grafo, origem - 1, destino - 1, valor);
    }

    exibirGrafo(grafo);
    relatorioPorRegiao(grafo);
    relatorioPorEstado(grafo);

    return 0;
}
