#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"extsort.h"
#include"sort.h"



int getmin(char **arr,int it){
	int i = 0 ;
	int j = 0;
	int count;
	for(i = 0 ; i < it; i++){
		count = 0;
		for(j = i + 1; j < it ;j++){
			if( strcmp(arr[i],arr[j]) < 0) count++;
		}
		if(count == it - i - 1) return i;
		else continue;
	}
	return 0;
}

int getminnum(char **arr,int it){
	int i = 0 ;
	int j = 0;
	int count;
	for(i = 0 ; i < it; i++){
		count = 0;
		for(j = i + 1; j < it ;j++){
			if( numcmp(arr[i],arr[j]) < 0) count++;
		}
		if(count == it - i - 1) return i;
		else continue;
	}
	return 0;
}

int getminb(char **arr,int it){
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
	
	int i = 0 ;
	int j = 0;
	int count;
	char *tmp1;
   	char *tmp2;
	for(i = 0 ; i < it; i++){
		tmp1 = (char *)malloc(strlen(arr[i]) + 2);
		strcpy(tmp1,arr[i]);
		trim(tmp1);
		count = 0;
		for(j = i + 1; j < it ;j++){
			tmp2 = (char *)malloc(strlen(arr[j]) + 2 );
			strcpy(tmp2,arr[j]);
			trim(tmp2);
			if( strcmp(tmp1,tmp2) < 0) count++;
		}
		if(count == it - i - 1) return i;
		else continue;
	}
	return 0;
}

int getmind(char **arr,int it){
	void trim(char * str)
				{
				    int top, i, j;
				    top = 0;
				    while((str[top] > 32 && str[top] <=47) || (str[top] >= 123 && str[top] <  126 ) )
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
					   }
					} 

	
	int i = 0 ;
	int j = 0;
	int count;
	char *tmp1;
   	char *tmp2;
	for(i = 0 ; i < it; i++){
		tmp1 = (char *)malloc(strlen(arr[i]));
		strcpy(tmp1,arr[i]);
		trim(tmp1);
		count = 0;
		for(j = i + 1; j < it ;j++){
			tmp2 = (char *)malloc(strlen(arr[j]));
			strcpy(tmp2,arr[j]);
			trim(tmp2);
			if( strcmp(tmp1,tmp2) < 0) count++;
		}
		if(count == it - i - 1) return i;
		else continue;
	}
	return 0;
}

int getmax(char **arr,int it){
	int i = 0 ;
	int j = 0;
	int count;
	for(i = 0 ; i < it; i++){
		count = 0;
		for(j = i + 1; j < it ;j++){
			if( strcmp(arr[i],arr[j]) > 0) count++;
		}
		if(count == it - i - 1) return i;
		else continue;
	}
	return it;
}
void filecopy(FILE *f1, FILE *f2){
	char str[1024];
	while(fgets(str,1024,f1) != NULL){
		fprintf(f2,"%s",str);
	}
}

void extsort(int it,char *f){
		
	FILE *fp[it +1];
	char *op[it + 1];
	char *temp[it + 1];
	FILE *out = fopen("output.txt","w+");
	if(out == NULL) printf("Unable to open");
	FILE *ft = fopen("temp_file.txt","r+");
	if(ft == NULL) printf("error");
	int i = 0;
	for(i = 0 ; i < it ;i++){
		if(strcmp(f,"-m") == 0){
			temp[i] = (char *)malloc(20);
			op[i] = (char *)malloc(20);
			fgets(temp[i],100,ft);
			strncpy(op[i],temp[i],strlen(temp[i]) - 1);
			free(temp[i]);
		}
		
		else{
		op[i] = (char *)malloc(20);
		fgets(op[i],100,ft);
		}
		
	}
	fclose(ft);
	i = 0;
	while(i < it){
		fp[i] = fopen(op[i],"r");
		i++;
	}
	if(it == 1) {
		filecopy(fp[0],out);
		fclose(out);
		if(strcmp(f,"-m") != 0) remove(op[0]);
		remove("temp_file.txt");
		return;
	}
	char *arr[it + 1];
	char *str = (char *)malloc(1024);
	i = 0;
	while(i < it){
		fgets(str,1024,fp[i]);
		arr[i] = (char *)malloc(1024);
		strcpy(arr[i],str);
		i++;
	}
	

	int count = 0;
	int k;
	i = 0;
	while(count < it - 1){
	while(1){
		if(strcmp(f,"--") == 0 || strcmp(f,"-m") == 0)
			k = getmin(arr,it);
		else if(strcmp(f,"-n") == 0)
			k = getminnum(arr,it);
		else if(strcmp(f,"-r") == 0)
			k = getmax(arr,it);
		else if(strcmp(f,"-b") == 0)
			k = getminb(arr,it);
		else if(strcmp(f,"-d") == 0)
			k = getmind(arr,it);				
		
		if(!feof(fp[k])){ 
			fprintf(out,"%s",arr[k]);
			fgets(str,1024,fp[k]);
			strcpy(arr[k],str);
			}	
		else{
			if(strcmp(f,"-r") == 0) arr[k] = "\0";
			else arr[k] = "~";
			count++;
			break;
		}
	}
	}
	
	if(strcmp(f,"-r") == 0){
	for(i = 0 ; i < it ;i++){
		if(strcmp(arr[i],"\0") != 0){
			k = i;
			break;
		}
	}
	fprintf(out,"%s",arr[k]);
	}
	else
	{
	for(i = 0 ; i < it ;i++){
		if(strcmp(arr[i],"~") != 0){
			k = i;
			break;
		}
	}
	fprintf(out,"%s",arr[k]);
	}	
	
	while(1){
		fgets(str,1024,fp[k]);
		if(feof(fp[k])) break;
		fprintf(out,"%s",str);
	}
		free(str);
	//if(feof(fp[k])) arr[k] = "~";
	 
	k = 0;
	while(k < it){
		if(strcmp(f,"-m") != 0)
		remove(op[k]);
		k++;
	}
	remove("temp_file.txt");
	fclose(out); 
	}


