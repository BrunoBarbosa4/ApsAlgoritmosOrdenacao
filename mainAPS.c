#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <sys/time.h>

//#include "time.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct{
	char nome[20];
	float tempoExecucao;
}algoritmo;

#define TAMANHO_BALDE 10
typedef struct{
	int qtdItens;
	int* itens;
}balde;

int tamanhoVetor;
*numeros = NULL;

//Diferen�a em milissegundos
float diferenca(struct timeval inicio, struct timeval fim){
    return (fim.tv_sec - inicio.tv_sec) * 1000.0 + (fim.tv_usec - inicio.tv_usec) / 1000.0;
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	
	struct timeval inicio;
	struct timeval fim;
	
	int escolha = -1;
	
	system("color 0a");//Deixa a cor da fonte verde
	
	// Escolhendo se o usu�rio que ir� digitar os n�meros ou ser�o gerados aleatoriamente.
	while (escolha < 0 || escolha > 1) {
		printf("Para come�ar voc� deve escolher se os n�meros ser�o aleat�rios, ou voc� que ir� digit�-los: (Obs: Escolha 0 ou 1)");
		printf("\n(0) - N�meros aleat�rios");
		printf("\n(1) - N�meros digitados\n");
		
		scanf("%d", &escolha);
	}
	
	switch ( escolha ) {
		
	case 0 :
    geraNumeros();
    break;	
		
    case 1 :
    recebendoNumeros();
    break;
    
    default :
    printf ("Erro inesperado: Valor invalido!\n");
  }	
  
  	escolha = -1;
	
	// Escolhendo o m�todo de ordena��o
	while (escolha < 1 || escolha > 9) {
		printf("\nEscolha uma op��o de algoritmo para  realizar a ordena��o: (Obs: 1 � 9)");
		printf("\n(1) - M�todo BubbleSort");
		printf("\n(2) - M�todo QuickSort ");
		printf("\n(3) - M�todo InsertionSort");
		printf("\n(4) - M�todo BinaryInsertionSort");
		printf("\n(5) - M�todo SelectionSort");
		printf("\n(6) - M�todo HeapSort");
		printf("\n(7) - M�todo MergeSort ");
		printf("\n(8) - M�todo BucketSort");
		printf("\n(9) - Todos (verificar a performance)\n");
		
		scanf("%d", &escolha);
	}
	
	gettimeofday(&inicio, 0);
	
	switch ( escolha ) {
	
	    case 1 :
		    printf ("\nM�todo BubbleSort\n");
		    bubbleSort();
		    break;
	    
	    case 2 :
		    printf ("\nM�todo QuickSort\n");
		    quickSort(numeros, 0, tamanhoVetor - 1); //Seleciono o primeiro elemento do vetor at� o �ltimo
		    break;
	    
	    case 3 :
		    printf ("\nM�todo InsertionSort\n");
		    insertionSort(numeros, tamanhoVetor);
		    break;
	    
	    case 4 :
		    printf ("\nM�todo BinaryInsertionSort\n");
		    binaryInsertionSort();
		    break;
	    
	    case 5 :
		    printf ("\nM�todo SelectionSort\n");
		    selectionSort();
		    break;
	    
	    case 6 :
		    printf ("\nM�todo HeapSort\n");
		    heapSort(numeros, tamanhoVetor);
		    break;
	    
	    case 7 :
		    printf ("\nM�todo MergeSort\n");
		    mergeSort(numeros, 0, tamanhoVetor - 1);
		    break;
	    
	    case 8 :
		    printf ("\nM�todo BucketSort\n");
		    bucketSort(numeros, tamanhoVetor);
		    break;
	    
	    case 9:
	    	executarTodos();
	    	break;
	    
	    default :
	    printf ("Erro inesperado: Valor invalido!\n");
	}
	
	if(escolha != 9){
		gettimeofday(&fim, 0);
		listarNumeros();
		printf("\n\nTempo de execu��o: %f milissegundos (sem a parte de printar)\n", diferenca(inicio, fim));
	}
	
	return 0;
}

// Fun��es de gerar n�meros aleat�rios e de receber n�meros do usu�rio
int geraNumeros() {
	printf("Quantos n�meros deseja que sejam gerados?\n");
	scanf("%d", &tamanhoVetor);
	
	numeros = (int *)malloc(tamanhoVetor * sizeof(int));
	
	srand(314159976);//srand(time(NULL));//srand(314159976);
	int valorMaximo = 1000;//Os n�meros aleat�rios ser�o gerados de 0 at� 100
	for (int i = 0; i < tamanhoVetor; i++){
		numeros[i] = rand() % valorMaximo + 1;
	}
	listarNumeros();
	printf("\n");
	
	return 0;
}

int recebendoNumeros() {
	printf("Quantos n�meros deseja escrever?\n");
	scanf("%d", &tamanhoVetor);
	
	numeros = (int *)malloc(tamanhoVetor * sizeof(int));
	
	for (int i = 0; i < tamanhoVetor; i++){
		printf("Digite um n�mero para o vetor: ");
		scanf("%d", &numeros[i]);
	}
	listarNumeros();
	printf("\n");
	
	return 0;
}

void listarNumeros(){
	printf("\nN�meros do vetor:\n");
	for(int i = 0;i < tamanhoVetor;i++){
		printf("%d", numeros[i]);
		
		if(i+1 < tamanhoVetor){    // if para impedir que fique uma v�rgula depois de j� ter mostrado todos os n�meros
			printf(", ");
		}
		
	}
	
}

void bubbleSort(){
	bool ordenada;
	
	do{
		ordenada = true; //est� ordenada at� que se prove o contr�rio
		
		for(int i = 0; i < tamanhoVetor - 1; i++){
			
			if(numeros[i] > numeros[i + 1]){
				trocar(i, i + 1);
				ordenada = false;
			}
			
		}
		
	}while(!ordenada);
}

void quickSort(int *numeros, int comeco, int fim) {
     
    int contEsquerda = comeco;
    int contDireita = fim;
    int pivo = numeros[(comeco + fim) / 2];  //Defini o piv� sendo o n�mero do meio do vetor
     
    while(contEsquerda <= contDireita) {
        while(numeros[contEsquerda] < pivo && contEsquerda < fim) {  //Enquanto n�o houver um n�mero maior ou igual ao piv�, o contador da esquerda vai aumentando
            contEsquerda++;
        }
        while(numeros[contDireita] > pivo && contDireita > comeco) { //Enquanto n�o houver um n�mero menor ou igual ao piv�, o contador da direita vai diminuindo
            contDireita--;
        }
        if(contEsquerda <= contDireita) { 
            trocar(contEsquerda, contDireita);
            contEsquerda++;
            contDireita--;
        }
    }
     
    if(contDireita > comeco) {
        quickSort(numeros, comeco, contDireita);
    }
    if(contEsquerda < fim) {
        quickSort(numeros, contEsquerda, fim);
    }
}

void insertionSort(int *vetor, int tamanhoVetor){
	int j;
	int atual;
	for(int i = 0;i < tamanhoVetor; i++){
		atual = vetor[i];
		j = i - 1;
		
		while(atual < vetor[j]){
			if(j < 0){
				break;
			}
			
			vetor[j + 1] = vetor[j];
			j--;
		}
		vetor[j + 1] = atual;
	}
}


void binaryInsertionSort(){
	
	
	
}

void selectionSort(){
	
	for(int i = 0; i < tamanhoVetor - 1; i++){
		
		int posMenor = i;
		for(int j = i + 1; j < tamanhoVetor; j++){
			
			if(numeros[j] < numeros[posMenor]){
				posMenor = j;
			}
			
		}
		trocar(i, posMenor);
	}
}

void heapSort(int *numeros, int tamanhoVetor){
	int i = tamanhoVetor / 2;
	int aux;
	
   while(true) {
      if (i > 0) {
          i--;
          aux = numeros[i];
      } else {
          tamanhoVetor--;
          if (tamanhoVetor <= 0) return;
          aux = numeros[tamanhoVetor];
          numeros[tamanhoVetor] = numeros[0];
      }
      
      int posicaoPai = i;
      int posicaoFilho = i * 2 + 1;
      while (posicaoFilho < tamanhoVetor) {
      	
          if ((posicaoFilho + 1 < tamanhoVetor)  &&  (numeros[posicaoFilho + 1] > numeros[posicaoFilho]))//Compara qual dos filhos � o maior
              posicaoFilho++;
              
          if (numeros[posicaoFilho] > aux) {//Compara se o maior dos filhos � maior que o pai
          	
             numeros[posicaoPai] = numeros[posicaoFilho];
             posicaoPai = posicaoFilho;
             posicaoFilho = posicaoPai * 2 + 1;
             
          } else {
             break;
          }
      }
      
      numeros[posicaoPai] = aux;
   }
	
}

void mergeSort(int *numeros, int inicio, int final){
	if (inicio < final) {
        int meio = (final + inicio) / 2;

        mergeSort(numeros, inicio, meio);
        mergeSort(numeros, meio + 1, final);
        merge(numeros, inicio, meio, final);
    }
	
}

void merge(int *numeros, int inicio, int meio, int final) {
	int tamanho = final - inicio + 1;
    int indiceParte1 = inicio;
	int indiceParte2 = meio + 1;
	int indiceAuxiliar = 0;
    int *vetorAuxiliar;
    vetorAuxiliar = (int*)malloc(tamanho * sizeof(int));

    while((indiceParte1 <= meio) && (indiceParte2 <= final)){//Roda enquanto o in�cio1 e o in�cio2 estiverem dentro dos limites, meio e final respectivamente
        if(numeros[indiceParte1] < numeros[indiceParte2]) {//Compara qual dos dois n�meros (numeros[indiceParte1] e numeros[indiceParte2]) � o menor
            vetorAuxiliar[indiceAuxiliar] = numeros[indiceParte1];//Se o numeros[indiceParte1] for menor, ent�o ele � colocado no vetor auxiliar
            indiceParte1++;//incrementa para que, na pr�xima compara��o ele comparar com o pr�ximo da parte do indiceParte1 (in�cio para o meio)
        }
		else {
            vetorAuxiliar[indiceAuxiliar] = numeros[indiceParte2];//Se o numeros[indiceParte2] for menor, ent�o ele � colocado no vetor auxiliar
            indiceParte2++;//incrementa para que, na pr�xima compara��o ele comparar com o pr�ximo da parte do indiceParte2 (meio para o fim)
        }
        indiceAuxiliar++;
    }

    while(indiceParte1 <= meio){//Verifica se a parte1 (in�cio para o meio) ainda tem elementos 
        vetorAuxiliar[indiceAuxiliar] = numeros[indiceParte1];
        indiceAuxiliar++;
        indiceParte1++;
    }

    while(indiceParte2 <= final) {//Verifica se a parte2 (meio para o fim) ainda tem elementos 
        vetorAuxiliar[indiceAuxiliar] = numeros[indiceParte2];
        indiceAuxiliar++;
        indiceParte2++;
    }

	//Copia os elementos j� organizados do vetor auxiliar para o vetor numeros
    for(indiceAuxiliar = inicio; indiceAuxiliar <= final; indiceAuxiliar++){
        numeros[indiceAuxiliar] = vetorAuxiliar[indiceAuxiliar - inicio];
    }
    
    free(vetorAuxiliar);//Libera o vetor auxiliar
}

void bucketSort(int *numeros, int tamanhoVetor){
	
	if(tamanhoVetor < 1)
		return;
	
	int maior = numeros[0];
	
	for(int i = 0; i < tamanhoVetor; i++){//Procra pelo maior e menor valores do vetor
		int atual = numeros[i];
		
		if(atual > maior)
			maior = atual;
	}
	
	//Declarando os baldes
	int qtdBaldes = 10;
	balde baldes[qtdBaldes];
	for(int i = 0; i < qtdBaldes; i++){
		baldes[i].itens = (int*)malloc(sizeof(int) * tamanhoVetor);//os baldes tem a capacidade do tamanho do vetor
		baldes[i].qtdItens = 0;//colocando a quantidade de itens do balde como 0
	}
	
	//Separa nos baldes
	int posicaoBalde;
	for(int i = 0; i < tamanhoVetor; i++){
		
		int posicaoBalde = (qtdBaldes) - 1;
		while(posicaoBalde >= 0){
			
			if(numeros[posicaoBalde] >= posicaoBalde * (maior / qtdBaldes)){
				baldes[posicaoBalde].itens[baldes[posicaoBalde].qtdItens] = numeros[i];
				baldes[posicaoBalde].qtdItens++;//Aumenta a quantidade de itens para poder colcoar o pr�ximo no local correto
				break;
			}
			
			posicaoBalde--;
		}
		
	}
	
	//Ordena os itens em cada balde e coloca os baldes no vetor;
	posicaoBalde = 0;
	for(int i = 0; i < qtdBaldes; i++){
		
		insertionSort(baldes[i].itens, baldes[i].qtdItens);
		
		for(int j = 0; j < baldes[i].qtdItens; j++){//Coloca cada item do balde no vetor
			numeros[posicaoBalde] = baldes[i].itens[j];
			posicaoBalde++;
		}
		
		//free(baldes[i].itens);
	}
	
}

void executarTodos(){
	struct timeval inicio;
	struct timeval fim;
	
	int qtdAlgoritmos = 8;
	algoritmo algs[qtdAlgoritmos];
	
	int copia = (int *)malloc(tamanhoVetor * sizeof(int));
	copiaNumeros(numeros, copia, tamanhoVetor);
	
	//BubbleSort
	gettimeofday(&inicio, NULL);
	bubbleSort();
	gettimeofday(&fim, NULL);
	strcpy(algs[0].nome, "BubbleSort\t");
	algs[0].tempoExecucao = diferenca(inicio, fim);
	
	copiaNumeros(copia, numeros, tamanhoVetor);//Recolocando os n�meros da mesma forma que estavam
	
	//QuickSort
	gettimeofday(&inicio, NULL);
	quickSort(numeros, 0, tamanhoVetor - 1);
	gettimeofday(&fim, NULL);
	strcpy(algs[1].nome, "QuickSort\t");
	algs[1].tempoExecucao = diferenca(inicio, fim);
	
	copiaNumeros(copia, numeros, tamanhoVetor);//Recolocando os n�meros da mesma forma que estavam
	
	//InsertionSort
	gettimeofday(&inicio, NULL);
	insertionSort(numeros, tamanhoVetor);
	gettimeofday(&fim, NULL);
	strcpy(algs[2].nome, "InsertionSort");
	algs[2].tempoExecucao = diferenca(inicio, fim);
	
	copiaNumeros(copia, numeros, tamanhoVetor);//Recolocando os n�meros da mesma forma que estavam
	
	//BinaryInsertionSort
	gettimeofday(&inicio, NULL);
	binaryInsertionSort();
	gettimeofday(&fim, NULL);
	strcpy(algs[3].nome, "BinaryInsertionSort");
	algs[3].tempoExecucao = diferenca(inicio, fim);
	
	copiaNumeros(copia, numeros, tamanhoVetor);//Recolocando os n�meros da mesma forma que estavam
	
	//SelectionSort
	gettimeofday(&inicio, NULL);
	selectionSort();
	gettimeofday(&fim, NULL);
	strcpy(algs[4].nome, "SelectionSort");
	algs[4].tempoExecucao = diferenca(inicio, fim);
	
	copiaNumeros(copia, numeros, tamanhoVetor);//Recolocando os n�meros da mesma forma que estavam
	
	//HeapSort
	gettimeofday(&inicio, NULL);
	heapSort(numeros, tamanhoVetor);
	gettimeofday(&fim, NULL);
	strcpy(algs[5].nome, "HeapSort\t");
	algs[5].tempoExecucao = diferenca(inicio, fim);
	
	copiaNumeros(copia, numeros, tamanhoVetor);//Recolocando os n�meros da mesma forma que estavam
	
	//MergeSort
	gettimeofday(&inicio, NULL);
	mergeSort(numeros, 0, tamanhoVetor - 1);
	gettimeofday(&fim, NULL);
	strcpy(algs[6].nome, "MergeSort\t");
	algs[6].tempoExecucao = diferenca(inicio, fim);
	
	copiaNumeros(copia, numeros, tamanhoVetor);//Recolocando os n�meros da mesma forma que estavam
	
	//BucketSort
	gettimeofday(&inicio, NULL);
	bucketSort(numeros, tamanhoVetor);
	gettimeofday(&fim, NULL);
	strcpy(algs[7].nome, "BucketSort\t");
	algs[7].tempoExecucao = diferenca(inicio, fim);
	
	listarNumeros();
	ordenarAlgoritmos(algs, qtdAlgoritmos);
	listarAlgoritmos(algs, qtdAlgoritmos);
}

void listarAlgoritmos(algoritmo *algs, int qtdAlgoritmos){
	printf("\n\nAlgoritmos ordenados pelo tempo de execu��o: \n");
	printf("\n\t| Posi��o | \tAlgoritmo\t |   tempo\t   |\n");//
	printf("\t|-----------------------------------------------|\n");
	for(int i = 0; i < qtdAlgoritmos; i++){
		//printf(" %d Algoritmo: %s\t tempo: %.2f ms.\n", (i + 1), algs[i].nome, algs[i].tempoExecucao);
		printf("\t|    %d    | %s\t | %f ms.        |\n", (i + 1), algs[i].nome, algs[i].tempoExecucao);
	}
}

//Usando o algoritmo de insertionSort
void ordenarAlgoritmos(algoritmo *algs, int qtdAlgoritmos){
	int j;
	algoritmo atual;
	for(int i = 0;i < qtdAlgoritmos; i++){
		atual = algs[i];
		j = i - 1;
		
		while(atual.tempoExecucao < algs[j].tempoExecucao){
			if(j < 0){
				break;
			}
			
			algs[j + 1] = algs[j];
			j--;
		}
		algs[j + 1] = atual;
	}
}

bool estaOrdenado(){
	for(int i = 0;i < tamanhoVetor - 1; i++){
		if(numeros[i] > numeros[i + 1]){
			return false;
		}
	}
	
	return true;
}

void trocar(int posicao1, int posicao2){
	if((posicao1 < 0) || (posicao1 > tamanhoVetor - 1) || (posicao2 < 0) || (posicao2 > tamanhoVetor - 1)){
		return;//Verifica se as posi��o est�o dentro do vetor
	}
	
	int aux = numeros[posicao1];
	numeros[posicao1] = numeros[posicao2];
	numeros[posicao2] = aux;
}

void copiaNumeros(int *vetorFonte, int *vetorDestino, int tamanhoVetores){
	for(int i = 0; i < tamanhoVetores; i++){
		vetorDestino[i] = vetorFonte[i];
	}
}

