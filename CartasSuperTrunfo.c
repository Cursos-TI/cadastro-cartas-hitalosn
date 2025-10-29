#include <stdio.h>
#include <string.h>
typedef struct {
    char estado[3];         // Ex: "SP", "RJ"
    char codigo_carta[5];   // Ex: "C-01"
    char nome_cidade[50];
    int populacao;          // População (int)
    float area;             // Área em km² (float)
    float pib;              // PIB em bilhões de R$ (float)
    int pontos_turisticos;
    float densidade_populacional;
    float pib_per_capita;
} Carta;

void calcular_atributos_derivados(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade_populacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0.0;
    }
    if (carta->populacao > 0) {
        carta->pib_per_capita = (carta->pib * 1000000000.0) / (float)carta->populacao;
    } else {
        carta->pib_per_capita = 0.0;
    }
}

// *** VARIÁVEL GLOBAL DE CONTROLE DE COMPARAÇÃO ***
// Esta variável define qual atributo será comparado entre as cartas.
// 1: População (int)
// 2: Área (float)
// 3: PIB (float)
// 4: Densidade Populacional (float) - OBS: MENOR valor vence!
// 5: PIB per capita (float)
const int ATRIBUTO_COMPARACAO = 3; // Escolha inicial: 3 (PIB)
void comparar_cartas(Carta carta1, Carta carta2) {
    float valor1 = 0.0;
    float valor2 = 0.0;
    char nome_atributo[50];
    int menor_valor_vence = 0; // 0 = Maior valor vence (padrão) | 1 = Menor valor vence

    // --- 1. Definir o Atributo a ser Comparado e seus Valores ---
    switch (ATRIBUTO_COMPARACAO) {
        case 1:
            strcpy(nome_atributo, "População");
            valor1 = (float)carta1.populacao;
            valor2 = (float)carta2.populacao;
            break;
        case 2:
            strcpy(nome_atributo, "Área (km²)");
            valor1 = carta1.area;
            valor2 = carta2.area;
            break;
        case 3:
            strcpy(nome_atributo, "PIB (Bilhões R$)");
            valor1 = carta1.pib;
            valor2 = carta2.pib;
            break;
        case 4:
            strcpy(nome_atributo, "Densidade Populacional (hab/km²)");
            valor1 = carta1.densidade_populacional;
            valor2 = carta2.densidade_populacional;
            menor_valor_vence = 1; // REQUISITO: Para Densidade, o menor valor vence.
            break;
        case 5:
            strcpy(nome_atributo, "PIB per Capita (R$)");
            valor1 = carta1.pib_per_capita;
            valor2 = carta2.pib_per_capita;
            break;
        default:
            printf("\nERRO: Atributo de comparação não definido ou inválido.\n");
            return;
    }

    // --- 2. Exibir o Cabeçalho da Comparação ---
    printf("\n--- Comparação de Cartas (Atributo: %s) ---\n", nome_atributo);
    char formato[20] = "%.2f";
    if (ATRIBUTO_COMPARACAO == 1) {
        strcpy(formato, "%.0f"); 
    } else if (ATRIBUTO_COMPARACAO == 5) {
        strcpy(formato, "%.2f");
    }

    printf("Carta 1 - %s (%s): ", carta1.nome_cidade, carta1.estado);
    printf(formato, valor1);
    
    printf("\nCarta 2 - %s (%s): ", carta2.nome_cidade, carta2.estado);
    printf(formato, valor2);
    printf("\n");

    // --- 3. Implementar a Lógica de Decisão (if / if-else) ---

    // Lógica para quando o MAIOR valor vence (População, Área, PIB, PIB per capita)
    if (menor_valor_vence == 0) {
        if (valor1 > valor2) {
            printf("\nResultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
        } else if (valor2 > valor1) {
            printf("\nResultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
        } else {
            // Caso de empate
            printf("\nResultado: Empate! As cartas têm o mesmo valor no atributo %s.\n", nome_atributo);
        }
    } 
    // Lógica para quando o MENOR valor vence (Apenas Densidade Populacional)
    else { // menor_valor_vence == 1
        if (valor1 < valor2) {
            printf("\nResultado: Carta 1 (%s) venceu!\n", carta1.nome_cidade);
        } else if (valor2 < valor1) {
            printf("\nResultado: Carta 2 (%s) venceu!\n", carta2.nome_cidade);
        } else {
            // Caso de empate
            printf("\nResultado: Empate! As cartas têm o mesmo valor no atributo %s.\n", nome_atributo);
        }
    }
    
    printf("---------------------------------------------------\n");
}

int main() {
    // --- 1. Cadastro das Cartas (Reaproveitando o código do desafio anterior) ---

    // Carta 1: Exemplo de uma cidade grande
    Carta carta_sp = {
        .estado = "SP",
        .codigo_carta = "C-01",
        .nome_cidade = "São Paulo",
        .populacao = 12396372,
        .area = 1521.1,
        .pib = 763.8,
        .pontos_turisticos = 50
    };

    // Carta 2: Exemplo de uma capital com menor população e área
    Carta carta_rj = {
        .estado = "RJ",
        .codigo_carta = "C-02",
        .nome_cidade = "Rio de Janeiro",
        .populacao = 6775561,
        .area = 1200.3,
        .pib = 370.0,
        .pontos_turisticos = 45
    };
    
    // --- 2. Cálculo dos Atributos Derivados ---
    calcular_atributos_derivados(&carta_sp);
    calcular_atributos_derivados(&carta_rj);

    // --- 3. Exibir os Dados Completos (Opcional, mas útil para conferência) ---
    printf("--- Dados das Cartas ---\n");
    printf("Carta 1 (%s): %s\n", carta_sp.estado, carta_sp.nome_cidade);
    printf("  População: %d\n", carta_sp.populacao);
    printf("  Área: %.2f km²\n", carta_sp.area);
    printf("  PIB: R$ %.2f Bilhões\n", carta_sp.pib);
    printf("  Densidade Populacional: %.2f hab/km²\n", carta_sp.densidade_populacional);
    printf("  PIB per Capita: R$ %.2f\n", carta_sp.pib_per_capita);
    printf("\n");
    printf("Carta 2 (%s): %s\n", carta_rj.estado, carta_rj.nome_cidade);
    printf("  População: %d\n", carta_rj.populacao);
    printf("  Área: %.2f km²\n", carta_rj.area);
    printf("  PIB: R$ %.2f Bilhões\n", carta_rj.pib);
    printf("  Densidade Populacional: %.2f hab/km²\n", carta_rj.densidade_populacional);
    printf("  PIB per Capita: R$ %.2f\n", carta_rj.pib_per_capita);
    printf("\n");

    // --- 4. Comparação da Carta (Foco do desafio) ---
    // A função comparar_cartas usará o valor da constante ATRIBUTO_COMPARACAO (3: PIB)
    comparar_cartas(carta_sp, carta_rj);

    return 0;
}
