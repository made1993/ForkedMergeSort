#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#
typedef struct str_thdata{
	int * tabla;
	int ini;
	int fin;
}MergeData;
int MergeSort(int * tabla,int ini, int fin){
	int medio, i;
	if (tabla ==NULL)
		return 0;
	if (fin == ini)
		return 1;
	medio = (ini+fin)/2;
	MergeSort(tabla, ini, medio);
	MergeSort(tabla, medio+1, fin);
	merge(tabla,ini,fin,medio);
	return 1;
}

int threadMergeSort(void * arg){

	int medio, i;
	MergeData data1, data2, *data;
	data= (MergeData*)arg;
	pthread_t thread1,thread2;
	if (data->tabla ==NULL)
		return 0;
	if (data->fin == data->ini)
		return 1;
	medio = (data->ini+data->fin)/2;
	data1.tabla=data->tabla;
	data1.ini=data->ini;
	data1.fin=medio;

	data2.tabla=data->tabla;
	data2.ini=medio+1;
	data2.fin=data->fin;
	pthread_create(&thread1, NULL,(void *)&threadMergeSort, (void *) &data1);
	pthread_create(&thread2, NULL,(void *)&threadMergeSort, (void *) &data2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	merge(data->tabla,data->ini,data->fin,medio);
	return 1;
}
int ClusterMergeSort(int puerto){
	int socket;
	char * buffer;
	socket = abrirSocketUDP();
	abrirBind(socket, puerto);
	recibir(socket,buffer);
	return 1;
}
int ServerMergeSort(int puerto){
	int socket;
	char * buffer;
	socket = abrirSocketUDP();
	abrirBind(socket, puerto);
	recibir(socket,buffer);
	return 1;
}

int merge(int *tabla, int ini, int fin, int medio){
	int i= ini,j=medio+1, k=0;
	int * auxTabla=NULL;
	auxTabla= (int*)malloc(sizeof(int)*fin-ini +1);
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



int main(int argc, char ** argv){
	int* tabla = NULL;
	int i=0, j=10, size;
	if(argc<3)
		return 0;
	size= atoi(argv[1]);
	tabla = malloc(sizeof(int)*size);
	for(i=0,j=size;i<size;j--,i++){
		tabla[i]=j;
	}
	
	if(strcmp(argv[2],"t")==0){
		MergeData data;
		data.tabla=tabla;
		data.ini=0;
		data.fin=size-1;
		threadMergeSort((void*) &data);
	}else if(strcmp(argv[2],"n")==0){
		MergeSort(tabla,0,size-1);
	}else if(strcmp(argv[2],"c")==0){
		ClusterMergeSort();
	}else if(strcmp(argv[2],"s")==0){
		ServerMergeSort();
	}
	for(i=0,j=size;i<size;j--,i++){
		printf("%d ",tabla[i]);
	}
	printf("\n");
	free(tabla);
}