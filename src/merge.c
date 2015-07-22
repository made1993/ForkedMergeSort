#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int forkedMergeSort(int * tabla,int ini, int fin){
	int medio, i;
	printf("forkedMergeSort ini=%d fin= %d \n",ini, fin);
	if (tabla ==NULL)
		return 0;
	if (fin - ini<2)
		return 1;
	medio = (ini+fin)/2;
	forkedMergeSort(tabla, ini, medio);
	forkedMergeSort(tabla, medio+1, fin);
	merge(tabla,ini,fin,medio);
	printf("\n");
	for(i=0;i<10;i++){
		printf("%d ", tabla[i]);
	}
	printf("\n");
	return 1;
}
int merge(int *tabla, int ini, int fin, int medio){
	printf("merge ini=%d fin= %d medio=%d\n",ini, fin,medio);
	int i= ini,j=medio+1, k=0;
	int * auxTabla=NULL;
	auxTabla= malloc(sizeof(int)*fin-ini +1);
	if(ini==fin)
		return 1;
	while(i<=medio && j<=fin){
		if(tabla[i]<tabla[j]){
			auxTabla[k]=tabla[i];
			i++;
		}
		else{
			auxTabla[k]=tabla[j];
			j++;
		}
		k++;
	}
	for(;i<=medio;i++, k++){
		auxTabla[k]=tabla[i];
	}
	for(;j<=medio;j++, k++){
		auxTabla[k]=tabla[j];
	}
	for(i=ini,j=0;j<k;i++,j++){
		tabla[i]=auxTabla[j];
	}
	free(auxTabla);
	return 1;
}

int main(){
	int* tabla = NULL;
	int i=0, j=10;
	tabla = malloc(sizeof(int)*10);
	for(i=0,j=10;i<10;j--,i++){
		tabla[i]=j;
	}
	for(i=0;i<10;i++){
		printf("%d ", tabla[i]);
	}
	printf("\n");
	printf("%d\n",forkedMergeSort(tabla,0,9));
	

	for(i=0;i<10;i++){
		printf("%d ", tabla[i]);
	}
	printf("\n");
}