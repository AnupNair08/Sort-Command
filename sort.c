#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sort.h"
#include"extsort.h"

//Functions for implementing numeric sort
int isDigit(char a){
	if(a >= '0' && a <= '9') return 1;
	else return 0;
}

int numcmp(char *str, char *str2){
	int i = 0;
	long long num = 0;
	if(str[0] >= '0' && str[0] <= '9'){
		while(isDigit(str[i])){
			num = num * 10 + str[i] - '0';
			i++;
		}
	}
	else{
		return strcmp(str,str2);
	}
	int num2 = 0;
	i = 0;
	if(str2[0] >= '0' && str2[0] <= '9'){
		while(isDigit(str2[i])){
			num2 = num2 * 10 + str2[i] - '0';
			i++;
		}
	}
	else{
		return strcmp(str,str2);
	}
	if(num > num2) return 1;
	else if(num < num2) return -1;
	else return 0;
	
}



//Merge sort for sorting lines
void Merge(char* arr[],int low,int mid,int high,int it,char *f) 
{
    int nL= mid-low+1;
    int nR= high-mid;
    char*L[nL];
    char*R[nR];
    int i;
    for(i=0;i<nL;i++)
    {
        L[i] = arr[low+i];
    }
    for(i=0;i<nR;i++)
    {
	R[i] = arr[mid+i+1];
    }
    int j=0,k;
    i = 0;
    k = low;
    
    if(strcmp(f,"-f") == 0){
    while(i<nL && j<nR)
    {
        if(strcasecmp(L[i],R[j]) < 0) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
    }
    while(i<nL){
    	arr[k++] = L[i++];
    	}
    while(j<nR){
    	arr[k++] = R[j++];
	}
    }
    
    
    else if (strcmp(f,"-i") == 0){
    void trim(char * str)
				{
				    int top, i, j;
				    top = 0;
				    while(str[top] >= 0 && str[top] <= 31 )
				    {
					top++;
				    }
				    if(top != 0)
				    {
					i = 0;
					while(str[i + top] != '\0')
					{
					    str[i] = str[i + top];
					    i++;
					}
					str[i] = '\0';
				     }
				}


    
    
    i = 0 ; j = 0;
    k=low;
    char *tmp1 = (char *)malloc(1024);
    char *tmp2 = (char *)malloc(1024);
    while(i<nL && j<nR)
    {
    	strcpy(tmp1,L[i]);
    	strcpy(tmp2,R[j]);
    	trim(tmp1);
    	trim(tmp2);	
        if(strcmp(tmp1,tmp2) < 0) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
    }
    free(tmp1);
    free(tmp2);
    while(i<nL){
    	arr[k++] = L[i++];
    	}
    while(j<nR){
    	arr[k++] = R[j++];
	}
    }
    else if(strcmp(f,"1") == 0 || strcmp(f,"2") == 0 || strcmp(f,"3") == 0 || strcmp(f,"4") == 0 || strcmp(f,"5") == 0){
    	i = 0; j = 0; k=low;
    	int n = 1;
    	char *tmp1 = (char *) malloc(1024);
    	char *tmp2 = (char *) malloc(1024);
    	char *tok1 = (char *)malloc(1024); 
    	char *tok2 = (char *)malloc(1024);
    	while(i<nL && j<nR)
    	{
    	strcpy(tmp1,L[i]);
    	strcpy(tmp2,R[j]);
    	int p,q,spc = 0;
    	int x = atoi(f);
    	for(p = 0 ; p < strlen(tmp1); p++){if(tmp1[p] == ' ') spc++;};
    	if(atoi(f) > spc + 1) x = spc + 1;   
    	tok1 = strtok(tmp1," ");
    	while(n < x) {tok1 = strtok(NULL," "); n++;}
    	n = 1;
    	tok2 = strtok(tmp2," ");
	while(n < x)  {tok2 = strtok(NULL," "); n++;};
    	
        if(strcmp(tok1,tok2) < 0) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
    }
    while(i<nL){
    	arr[k++] = L[i++];
    	}
    while(j<nR){
    	arr[k++] = R[j++];
	}
    
    }
    
    else{
    while(i<nL && j<nR)
    {
        if(strcmp(L[i],R[j]) < 0) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
    }
    while(i<nL){
    	arr[k++] = L[i++];
    	}
    while(j<nR){
    	arr[k++] = R[j++];
	}
    
    }
    
    
}



void MergeSort(char* arr[],int low,int high,int it,char *f) 
{
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSort(arr,low,mid,it,f);
        MergeSort(arr,mid+1,high,it,f);
        Merge(arr,low,mid,high,it,f);
    }
}



//Merge sort for sorting in reverse order
void Merger(char* arr[],int low,int mid,int high,int it) 
{
    	
    int nL= mid-low+1;
    int nR= high-mid;
    char*L[nL];
    char*R[nR];
    int i;
    for(i=0;i<nL;i++)
    {
        L[i] = arr[low+i];
    }
    for(i=0;i<nR;i++)
    {
	R[i] = arr[mid+i+1];
	}
    int j=0,k;
    i=0;
    k=low;
    while(i<nL&&j<nR)
    {
        if(strcmp(L[i],R[j])>0) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
    }
    while(i<nL){
    	arr[k++] = L[i++];
    	}
    while(j<nR){
    	arr[k++] = R[j++];
	}
}







void MergeSortr(char* arr[],int low,int high,int it) 
{
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSortr(arr,low,mid,it);
        MergeSortr(arr,mid+1,high,it);
        Merger(arr,low,mid,high,it);
    }
}




//Merge Sort for numeric sort
void Mergen(char* arr[],int low,int mid,int high,int it,char *f) 
{
    	
    int nL= mid-low+1;
    int nR= high-mid;
    char*L[nL];
    char*R[nR];
    int i;
    for(i=0;i<nL;i++)
    {
        L[i] = arr[low+i];
    }
    for(i=0;i<nR;i++)
    {
	R[i] = arr[mid+i+1];
	}
    int j=0,k;
    i=0;
    k=low;
    if(strcmp(f,"-n") == 0){
    while(i<nL&&j<nR)
    {
        if(numcmp(L[i],R[j]) < 0 ) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
        	
        
        
    }
    }
    else{
    while(i<nL&&j<nR)
    {
        if(numcmp(L[i],R[j]) > 0 ) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
        	
        
        
    }
    
    
    
    
    }
    while(i<nL){
    	arr[k++] = L[i++];
    	}
    while(j<nR){
    	arr[k++] = R[j++];
	}
}







void MergeSortn(char* arr[],int low,int high,int it,char *f) 
{
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSortn(arr,low,mid,it,f);
        MergeSortn(arr,mid+1,high,it,f);
        Mergen(arr,low,mid,high,it,f);
    }
}



void Mergeb(char* arr[],int low,int mid,int high,int it) 
{
	void trim(char * str)
				{
				    int top, i, j;
				    top = 0;
				    while(str[top] == ' ' || str[top] == '\t' )
				    {
					top++;
				    }
				    if(top != 0)
				    {
					i = 0;
					while(str[i + top] != '\0')
					{
					    str[i] = str[i + top];
					    i++;
					}
					str[i] = '\0';
				     }
				}


    int nL= mid-low+1;
    int nR= high-mid;
    char* L[nL];
    char* R[nR];
    int i;
    for(i=0;i<nL;i++)
    {
        L[i] = arr[low+i];
    }
    for(i=0;i<nR;i++)
    {
	R[i] = arr[mid+i+1];
	}
    int j=0,k;
    i=0;
    k=low;
    char *tmp1 = (char *)malloc(1024);
    char *tmp2 = (char *)malloc(1024);
    while(i<nL && j<nR)

    {
	strcpy(tmp1,L[i]);
	strcpy(tmp2,R[j]);
    	trim(tmp1);
    	trim(tmp2);
        if(strcmp(tmp1,tmp2) < 0) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
    
    }
    free(tmp1);
    free(tmp2);
    while(i<nL){
    	arr[k++] = L[i++];
    	}
    while(j<nR){
    	arr[k++] = R[j++];
	}
}


void MergeSortb(char* arr[],int low,int high,int it) 
{
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSortb(arr,low,mid,it);
        MergeSortb(arr,mid+1,high,it);
        Mergeb(arr,low,mid,high,it);
    }
}








void Merged(char* arr[],int low,int mid,int high,int it) 
{
	void trim(char * str)
				{
				    int top, i, j;
				    top = 0;
				    while(str[top] == '\t'  || (str[top] > 32 && str[top] <=47) || (str[top] >= 123 && str[top] < 126 ) )
				    {
					top++;
				    }
				    if(top != 0)
				    {
					i = 0;
					while(str[i + top] != '\0')
					{
					    str[i] = str[i + top];
					    i++;
					}
					str[i] = '\0'; 				    }
				}


    int nL= mid-low+1;
    int nR= high-mid;
    char *L[nL];
    char *R[nR];
    int i;
    for(i=0;i<nL;i++)
    {
        L[i] = arr[low+i];
    }
    for(i=0;i<nR;i++)
    {
	R[i] = arr[mid+i+1];
	}
    int j=0,k;
    i=0;
    k=low;
    char *tmp1 = (char *)malloc(1024);
    char *tmp2 = (char *)malloc(1024);
    while(i<nL && j<nR)
    {
    	strcpy(tmp1,L[i]);
    	strcpy(tmp2,R[j]);
    	if (strlen(tmp1) != 1) trim(tmp1);
    	if (strlen(tmp2) != 1) trim(tmp2);
        if(strcmp(tmp1,tmp2) < 0) {
        	arr[k++] = L[i++];
        	}
        else {
        	arr[k++] = R[j++];
        	}
    }
    free(tmp1);
    free(tmp2);
    while(i<nL){
    	arr[k++] = L[i++];
    	}
    while(j<nR){
    	arr[k++] = R[j++];
	}
}


void MergeSortd(char* arr[],int low,int high,int it) 
{
    if(low<high)
    {
        int mid=(low+high)/2;
        MergeSortd(arr,low,mid,it);
        MergeSortd(arr,mid+1,high,it);
        Merged(arr,low,mid,high,it);
    }
}

