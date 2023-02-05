#include <stdio.h>
#include <stdlib.h>

#define MAXIMO 50

// Ordena os elementos de um vetor, contando a quantidade de inversões para esse fim
unsigned long long intercalaContandoInv(int vetor[], int r, int s, int t) {
    unsigned long long num_inversoes = 0; // inicializa o número de inversos com zero
    int x, y, z, tamanho;
    tamanho = t - r;
    x = r;
    y = s;
    z = 0;
    int* aux = malloc(tamanho * sizeof(int)); // alocação dinâmica de um vetor auxiliar

    // loop para intercalação
    while (x < s && y < t) {
        if (vetor[x] <= vetor[y])
            aux[z++] = vetor[x++];
        else {
            aux[z++] = vetor[y++];
            num_inversoes += s - x;
        }
    }

    // loops para possíveis inversões faltando
    while (y < t) aux[z++] = vetor[y++];
    while (x < s) aux[z++] = vetor[x++];

    // reconstruindo o vetor original com os elementos ordenados
    for (z = 0; z < tamanho; z++)
        vetor[r + z] = aux[z];

    free(aux); // libera~ção de espaço do vetor auxiliar

    return num_inversoes;
}

// conta a quantidade de inversões necessárias para deixar um conjunto de números em ordem crescente
unsigned long long contaNumInversoes(int vetor[], int r, int t) {
    unsigned long long num_inversoes = 0;
    int meio;
    if (t - r > 1) {
        meio = r + (t - r) / 2; // calcula o meio do vetor
        num_inversoes += contaNumInversoes(vetor, r, meio);
        num_inversoes += contaNumInversoes(vetor, meio, t);
        num_inversoes += intercalaContandoInv(vetor, r, meio, t); // auxiliado pelo intercala
    }
    return num_inversoes;
}


int main(int argc, char* argv[])
{
    char nome_arquivo[MAXIMO];
    FILE* arquivo_entrada;
    int num_genes;
    unsigned long long num_inversoes = 0;

    if (argc != 1)
    {
        printf("Parametros Incorretos. Exemplo: .\\nome_arquivo_executavel\n");
        return 0;
    }

    scanf("%s", nome_arquivo); // lendo o nome do arquivo

    // abrindo o arquivo de entrada
    arquivo_entrada = fopen(nome_arquivo, "r");

    if (arquivo_entrada == NULL)
    {
        printf("\nArquivo nao encontrado! Informe o nome da instancia:\n");
        exit(EXIT_FAILURE);
    }

    // leitura do arquivo de entrada
    fscanf(arquivo_entrada, "%d", &num_genes);

    int* vetor = (int*)malloc(num_genes * sizeof(int));

    // inserindo os genes no vetor
    for (int i = 0; i < num_genes; i++)
        fscanf(arquivo_entrada, "%d", &vetor[i]);

    num_inversoes = 0; // inicializando o número de inversões

    // contando a quantidade de inversões para transformar o genoma do indivíduo 2 no do 1
    num_inversoes = contaNumInversoes(vetor, 0, num_genes);

    printf("%llu\n", num_inversoes);

    // fechando o arquivo de entrada
    fclose(arquivo_entrada);

    return 0;
}