#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 101

// ATEN��O: O c�lculo da complexidade deve incluir todo o cc�digo, inclusive a leitura do arquivo.


char nome_arquivo[50], aux[MAX];								// proibido alterar esta linha
int opcao, tamanho, i, j, n, m, digrafo, matriz_adj[MAX][MAX];  // proibido alterar esta linha
// Declare vari�veis globais a partir daqui.


/* -----------------------------------------------------------------
   executafuncao()
   Tema: CAMINHO MÁXIMO (grafo valorado, vértice origem → vértice destino)
   Saída: “SIM” ou “NÃO”; se SIM, peso e sequência de vértices/arestas
   -----------------------------------------------------------------*/
void executafuncao (){
    /* ---------- declarações locais ---------- */
    int inicio, fim;                               /* vértices escolhidos pelo usuário               */
    int visitado[MAX] = {0};                       /* marcação de vértices visitados                 */
    int pilha_v[MAX], pilha_it[MAX];               /* pilha de DFS: vértice atual e próximo vizinho  */
    int path_best[MAX], tam_best = 0;              /* melhor caminho encontrado                      */
    int peso_best = -1;                            /* peso do melhor caminho                         */
    int peso_atual = 0;                            /* peso acumulado na busca                        */
    int topo = -1, i_local, j_local;               /* controle da pilha                              */

    /* ---------- leitura da origem e destino ---------- */
    printf("Digite o vertice inicial (1 a %d): ", n);
    scanf("%d", &inicio);
    printf("Digite o vertice final   (1 a %d): ", n);
    scanf("%d", &fim);

    if(inicio < 1 || inicio > n || fim < 1 || fim > n){          /* validação */
        printf("Vertices invalidos. Os rotulos devem estar entre 1 e %d.\n", n);
        return;
    }

    /* ---------- inicializa pilha para DFS iterativa ---------- */
    topo++;
    pilha_v[topo]  = inicio;     /* vértice na posição topo       */
    pilha_it[topo] = 1;          /* próximo vizinho a testar      */
    visitado[inicio] = 1;

    /* ---------- busca em profundidade manual (Backtracking) ---------- *
       Complexidade: explora todos os caminhos simples => O(V! ) no pior
       caso em grafos completos, pois cada caminho é percorrido uma vez. */
    while(topo >= 0){
        int v = pilha_v[topo];               /* vértice no topo da pilha  */
        int prox = 0;

        /* procura próximo vizinho não visitado a partir de pilha_it[topo] */
        for(j_local = pilha_it[topo]; j_local <= n; j_local++){
            pilha_it[topo] = j_local + 1;    /* próxima busca começa daqui */
            if(matriz_adj[v][j_local] > 0 && !visitado[j_local]){
                prox = j_local;              /* vizinho encontrado         */
                break;
            }
        }

        if(prox){   /* --- avanço na busca --- */
            /* empilha vizinho */
            topo++;
            pilha_v[topo]  = prox;
            pilha_it[topo] = 1;
            visitado[prox] = 1;
            peso_atual += matriz_adj[v][prox];

            /* se chegou ao destino, verifica se é o melhor caminho */
            if(prox == fim && peso_atual > peso_best){
                peso_best = peso_atual;
                tam_best  = topo + 1;
                for(i_local = 0; i_local <= topo; i_local++)
                    path_best[i_local] = pilha_v[i_local];
            }
        } else {    /* --- retrocesso (backtrack) --- */
            visitado[v] = 0;
            if(topo > 0){
                /* desconta peso da aresta removida do caminho atual */
                peso_atual -= matriz_adj[pilha_v[topo-1]][v];
            }
            topo--; /* desempilha */
        }
    }

    /* ---------- exibição do resultado ---------- */
    if(peso_best == -1){
        printf("NAO\n");                        /* não existe caminho         */
    } else {
        printf("SIM\n");
        printf("Peso do caminho maximo: %d\n", peso_best);

        printf("Sequencia de vertices: ");
        for(i_local = 0; i_local < tam_best; i_local++)
            printf("%d ", path_best[i_local]);
        printf("\nArestas do caminho:   ");
        for(i_local = 0; i_local < tam_best - 1; i_local++)
            printf("(%d,%d) ", path_best[i_local], path_best[i_local+1]);
        printf("\n");
    }
}





int main() {
	opcao = 1;

    while(opcao != 0){
        inicio:
        tamanho = 0;
        m = 0;
        digrafo = 0;
        system("cls"); 
        fflush(stdin); 
        printf("Digite o nome do arquivo (sem o .txt): ");
        gets(nome_arquivo);
        FILE *arquivo; 
        strcat(nome_arquivo,".txt"); 
            
        if((arquivo = fopen(nome_arquivo,"r")) != NULL){
        	while(fgets(aux, MAX, arquivo)) { 
                   char *elemento; 
                   elemento = strtok(aux, " ");
                    while (elemento != NULL){
                        elemento = strtok(NULL, " "); 
                    }
                    tamanho = tamanho + 1; 
                }
                fclose(arquivo);
                
                printf ("\n --------------------------- MATRIZ DE ADJAC�NCIA ---------------------------\n");
                
                if((arquivo = fopen(nome_arquivo,"r")) != NULL){
                    printf("\n");
                    for(int i = 1; i <= tamanho; i++){
                        for(int j = 1; j <= tamanho; j++){
                            fscanf(arquivo, "%d", &matriz_adj[i][j]);
							printf("%3d ", matriz_adj[i][j]); 
                        }
                        printf("\n");
                    }
                }
                fclose(arquivo);
				n = tamanho;
				
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (matriz_adj[i][j] != matriz_adj[j][i]) {
							digrafo = 1;   // � d�grafo
						}
					}
				}
				
                for(int i = 1; i <= tamanho; i++){
                    for(int j = 1; j <= tamanho; j++){
						if (digrafo == 1 && matriz_adj[i][j] != 0) {
							m = m + 1;
						} 
						if (digrafo == 0 && matriz_adj[i][j] != 0 && i <= j) {
							m = m + 1;
						}
					}
				}
				
	          printf ("\nN = %d e M = %d \n \n",n,m);     
            } else {
                printf("\nErro ao abrir o arquivo/Erro ao localizar o arquivo\n\n");
                
            }
        	  
		executafuncao ();       
        printf("\nDigite 0 para sair ou qualquer outra coisa para continuar: ");
		scanf("%d", &opcao);
        
    }
    return 0;
}

