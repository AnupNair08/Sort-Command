/*
DSA Project
MIS : 111811052 
Title : Sort Command
This is an implementation of the UNIX sort command using external sort algorithm
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<ctype.h>
#include"sort.h"
#include"extsort.h"

static int it = 0;

int main(int argc, char *argv[]){
	if(argc == 1){
		printf("Invalid number of arguments\n");
		return 1;
	}
	//version history
	if(strcmp(argv[1],"--version") == 0  ){
		printf("The current version is 1.50\nDated : 9 Nov 2019\nAuthor : Anup Nair\n") ;
		printf(":)\n");
		return 0;
	}
	
	
	
     	//help panel	
	else if(strcmp(argv[1],"--help") == 0){
		printf("This is an implementation of the Linux sort command that works on the external sorting algorithm\nCurrently supported options with this program include\n1.Sorting large files\n2.Reverse sorting\n3.Sorting with ignore of leading blank spaces\n4.Sorting with dictionary order\n5.Numeric Sort\n6.Merge sorted files without sort\n7.Unique sorted lines.\n8.Numeric reverse sort.\n9.Sorting by ignoring non printable characters\n10.Sort by folding lower and upper cases\n11.Sort by . delimiter\n12.Sort by cloumn number\n13.Describe and sort\n");
		return 0;
	}
	
	FILE *fd;
	FILE *f[argc -2];
	long long i = 0;
	if(argc < 2 || argc > 10){
		perror("Bad number of arguments");
		return errno;
	} 
	if(argc == 2){
		fd = fopen(argv[1],"r");
		if(fd == NULL){
			perror("File not found");
			return errno;
		}
	}
	else if(argc == 3){
		fd = fopen(argv[2],"r");
		if(fd == NULL){
			perror("File not found");
			return errno;
		}
		
	}
	else if(argc > 3){
		
		int i = 0; 
		for(i = 2; i < argc ;i++){
			f[i] = fopen(argv[i],"r");
			if(f[i] == NULL) {
				printf("File not found");
				return errno;
			}
		}
	
	
	}
	
      //Sort if no options are given or if output is specified(normally sort the file)
      if(argc == 2 || (argc == 3 && strcmp(argv[1],"-o") == 0 || (argc == 3 && strcmp(argv[1],"-f") == 0))){
		int f_size = 0;
		while(fgetc(fd) != EOF) f_size++;
		rewind(fd);
		
		int buf = f_size/(2048*255);
		int size = f_size/10;
		if(buf == 0) buf = f_size/size;		
		
		FILE *fp[buf+1];
		char *on[buf+1];
		
		FILE *ft = fopen("temp_file.txt","w+");
			if(ft == NULL) return -1;
			for(i =0 ; i <= buf ;i++){
				fprintf(ft,"f%lld.txt\n",i);
			}
		rewind(ft);
			for(i = 0 ; i <= buf ;i++){
				on[i] = (char *)malloc(20);
				fgets(on[i],20,ft);
			}
		fclose(ft);
		char *str[2048*255];
		while(1){
					if(feof(fd)) break;
					i = 0;
					while(i < 2048*255){ 	 
							str[i] = (char *)malloc(1024);
							fgets(str[i],1024,fd);
							if(feof(fd)) break;
							i++;
					}
					//printf("Number of lines is %d\n\n",i);
					MergeSort(str,0,i - 1,it,argv[1]);
					fp[it] = fopen(on[it],"w");
					free(on[it]);
					int k;
					for(k = 0 ; k < i ;k++){
						fprintf(fp[it],"%s",str[k]);
						free(str[k]);
					}
					fclose(fp[it]);
					it++;	
			}
			free(on[it]);
			extsort(it,"--");
			remove("temp_file.txt");
			system("cat output.txt");
			//if(argc == 2)
			//remove("output.txt");	
						

	}
	
	
	//Reverse sort the input
	else if(strcmp(argv[1],"-r") == 0){
		long long f_size = 0;
		while(fgetc(fd) != EOF) f_size++;
		rewind(fd);
		
		int buf = f_size/(2048*255);
		int size = f_size/10;
		if(buf == 0) buf = f_size/size;
		
		FILE *fp[buf + 1];
		char *on[buf + 1];
		FILE *ft = fopen("temp_file.txt","w+");
			if(ft == NULL) return -1;
			for(i =0 ; i <= buf ;i++){
				fprintf(ft,"f%lld.txt\n",i);
			}
		rewind(ft);
			on[0] = (char *)malloc(20);
			for(i = 0 ; i <= buf ;i++){
				on[i] = (char *)malloc(20);
				fgets(on[i],20,ft);
			}
		fclose(ft);
		int r = 0;
		char *str[2048*255];
		while(1){
					
					i = 0;
					while(i < 2048*255){ 	 
							str[i] = (char *)malloc(1024);
							fgets(str[i],1024,fd);
							if(feof(fd)) { r = 1; break;}
							i++;
					}
					
					//printf("Number of lines is %d\n\n",i);
					MergeSortr(str,0,i - 1,it);
					fp[it] = fopen(on[it],"w");
					free(on[it]);
					int k;
					for(k = 0 ; k < i ;k++){
						fprintf(fp[it],"%s",str[k]);
						free(str[k]);
					}
					fclose(fp[it]);
					it++;
					if(r == 1) { break; }
						
					
				}
			free(on[it]);
			extsort(it,argv[1]);
			system("cat output.txt");
				//remove("output.txt");			
		
	}
		
	//Ignore leading blanks	
	else if(strcmp(argv[1],"-b") == 0){
		int f_size = 0;
		while(fgetc(fd) != EOF) f_size++;
		rewind(fd);
		
		int buf = f_size/(2048*250);
		int size = (f_size)/10;
		if(buf == 0) buf = f_size/size;
		
		FILE *fp[buf + 1];
		char *on[buf + 1];
		
		FILE *ft = fopen("temp_file.txt","w+");
		if(ft == NULL) return -1;
			for(i =0 ; i <= buf ;i++){
				fprintf(ft,"f%lld.txt\n",i);
			}
		rewind(ft);
			on[0] = (char *)malloc(20);
			for(i = 0 ; i <= buf ;i++){
				on[i] = (char *)malloc(20);
				fgets(on[i],20,ft);
			}
		fclose(ft);
			
		int r = 0;
		char *str[2048*250];
		while(1){
					i = 0;
					str[0] = (char *)malloc(1024);
					while(i < 2048*250){ 	 
							fgets(str[i],1024,fd);
							if(feof(fd)) { r = 1 ; break;}
							i++;
							str[i] = (char *)malloc(1024);
					}
					//printf("Number of lines is %d\n\n",i);
					MergeSortb(str,0,i - 1,it);
					
					fp[it] = fopen(on[it],"w");
					free(on[it]);
					int k;
					for(k = 0 ; k < i ;k++){
						fprintf(fp[it],"%s",str[k]);
						free(str[k]);
					}
					free(str[k]);
					fclose(fp[it]);
					it++;
					if(r == 1) break;	
				}
				free(on[it]);
				extsort(it,"-b");
				system("cat output.txt");	
		
		}
	
	//Merge the non sorted files.
		else if(strcmp(argv[1],"-m") == 0){
				FILE *ft = fopen("temp_file.txt","w+");
					if(ft == NULL){
						printf("Error");
						return -1;
					}
				int i;
					for(i = 2 ; i < argc ;i++){
						fprintf(ft,"%s\n",argv[i]);
						it++;
					}
				fclose(ft);
				extsort(it,"-m");
				system("cat output.txt");
				remove("output.txt");			
		}
		
		
	else if(strcmp(argv[1],"-n") == 0 || strcmp(argv[1],"-nr") == 0 || strcmp(argv[1],"-dd") == 0){
		int f_size = 0;
		while(fgetc(fd) != EOF) f_size++;
		rewind(fd);
		
		int buf = f_size/(2048*250);
		int size = f_size/10;
		if(buf == 0) buf = f_size/10;
		
		FILE *fp[buf + 1];
		char *on[buf + 1];
		
		FILE *ft = fopen("temp_file.txt","w+");
			if(ft == NULL) return -1;
			for(i =0 ; i <= buf ;i++){
				fprintf(ft,"f%lld.txt\n",i);
			}
		rewind(ft);
			for(i = 0 ; i <= buf ;i++){
				on[i] = (char *)malloc(100);
				fgets(on[i],100,ft);
			}
		fclose(ft);
		int r = 0;
		char *str[2048*250];
		while(1){
					 
					i = 0;
					str[0] = (char *)malloc(1024);
					while(i < 2048*250){ 	
							fgets(str[i],1024,fd); 
							if(feof(fd)) { r = 1; break;}
							i++;
							str[i] = (char *)malloc(1024);
					}
					//printf("Number of lines is %d\n\n",i);
					MergeSortn(str,0,i - 1,it,argv[1]);
					fp[it] = fopen(on[it],"w");
					for(int k = 0 ; k < i ;k++){
						fprintf(fp[it],"%s",str[k]);
						free(str[k]);
					}
					fclose(fp[it]);
					it++;	
					if(r == 1) break;
				}
				extsort(it,argv[1]);
				if(strcmp(argv[1],"-dd") == 0){
					char **eptr;
					FILE *out = fopen("output.txt","r");
					char *str = (char *)malloc(1024);
					long long avg = 0;
					int line = 0;
					while(fgets(str,1024,out)){
						line++;
						avg = avg + strtoll(str,eptr,10);
					}
					float new;
					new = (float)avg/line;
					printf("Average is %f\n",new);
					rewind(out);
					long long max = 0;
					long long min;
					int n = 0;
					while(fgets(str,1024,out)){
						avg = strtoll(str,eptr,10);
						if(n == 0){
							min = avg;
							n++;
						}
						if(avg > max) max = avg;
						if(avg < min) min = avg;
					}
					printf("Maximum is %lld\n",max);
					printf("Minimum is %lld\n",min);
					printf("Frequency is %d\n",line);
					fclose(out);
				}
				else
				system("cat output.txt");
		
		}
		
		
		
	else if(strcmp(argv[1],"-d") == 0){
		int f_size = 0;
		while(fgetc(fd) != EOF) f_size++;
		rewind(fd);
		
		int buf = f_size/(2048*250);
		int size = f_size/10;
		if(buf == 0) buf = f_size/10;
		
		FILE *fp[buf + 1];
		char *on[buf + 1];
		
		FILE *ft = fopen("temp_file.txt","w+");
			if(ft == NULL) return -1;
			for(i =0 ; i <= buf ;i++){
				fprintf(ft,"f%lld.txt\n",i);
			}
		rewind(ft);
			for(i = 0 ; i <= buf ;i++){
				on[i] = (char *)malloc(100);
				fgets(on[i],100,ft);
			}
		fclose(ft);
		int r = 0;
		char *str[2048*250];
		while(1){
					i = 0;
					str[0] = (char *)malloc(1024);
					while(i < 2048*250){ 	 
							fgets(str[i],1024,fd);
							if(feof(fd)) { r = 1 ; break;}
							i++;
							str[i] = (char *)malloc(1024);
					}
					//printf("Number of lines is %lld\n\n",i);
					MergeSortd(str,0,i - 1,it);
					fp[it] = fopen(on[it],"w");
					free(on[it]);
					for(int k = 0 ; k < i ;k++){
						fprintf(fp[it],"%s",str[k]);
						free(str[k]);
					}
					fclose(fp[it]);
					it++;
					if(r == 1) break;	
			 }
			free(on[it]); 
			extsort(it,"-d");
			system("cat output.txt");
			//remove("output.txt");
		}
		
		
		else if(strcmp(argv[1],"-u") == 0){
		int f_size = 0;
		while(fgetc(fd) != EOF) f_size++;
		rewind(fd);
		
		int buf = f_size/(2048*250);
		int size = f_size/10;
		if(buf == 0) buf = f_size/10;
		
		FILE *fp[buf + 1];
		char *on[buf + 1];
		FILE *ft = fopen("temp_file.txt","w+");
			if(ft == NULL) return -1;
			for(i =0 ; i <= buf ;i++){
				fprintf(ft,"f%lld.txt\n",i);
			}
			rewind(ft);
			on[0] = (char *)malloc(100);
			for(i = 0 ; i <= buf ;i++){
				on[i] = (char *)malloc(100);
				fgets(on[i],100,ft);
			}
			fclose(ft);
			char *str[2048*250];
			while(1){
					if(feof(fd)) break;
					i = 0;
					str[0] = (char *)malloc(1024);
					while(i < 2048*250){ 	 
							fgets(str[i],1024,fd);
							if(feof(fd)) break;
							i++;
							str[i] = (char *)malloc(1024);
					}
					//printf("Number of lines is %lld\n\n",i);
					MergeSort(str,0,i - 1,it,argv[1]);
					fp[it] = fopen(on[it],"w");
					free(on[it]);
					for(int k = 0 ; k < i ;k++){
						fprintf(fp[it],"%s",str[k]);
						free(str[k]);
					}
					fclose(fp[it]);
					it++;	
				}
				free(on[it]);
				extsort(it,"--");
				system("uniq  output.txt");
				//remove("output.txt");
		}
		
		
		else if(strcmp(argv[1],"-i") == 0){
		int f_size = 0;
		while(fgetc(fd) != EOF) f_size++;
		rewind(fd);
		
		int buf = f_size/(2048);
		int size = f_size/10;
		if(buf == 0) buf = f_size/size;
		
		FILE *fp[buf + 1];
		char *on[buf + 1];
		
		FILE *ft = fopen("temp_file.txt","w+");
			if(ft == NULL) return -1;
			for(i =0 ; i <= buf ;i++){
				fprintf(ft,"f%lld.txt\n",i);
			}
		rewind(ft);
			for(i = 0 ; i <= buf ;i++){
				on[i] = (char *)malloc(100);
				fgets(on[i],100,ft);
			}
		fclose(ft);
		
		char *str[2048*250];
		while(1){
					if(feof(fd)) break;
					
					i = 0;
					str[0] = (char *)malloc(1024);
					while(i < 2048*250){ 	 
							fgets(str[i],1024,fd);
							if(feof(fd)) break;
							i++;
							str[i] = (char *)malloc(1024);
					}
					//printf("Number of lines is %lld\n\n",i);
					MergeSort(str,0,i - 1,it,"-i");
					fp[it] = fopen(on[it],"w");
					free(on[it]);
					for(int k = 0 ; k < i ;k++){
						fprintf(fp[it],"%s",str[k]);
						free(str[k]);
					}
					free(on[it]);
					fclose(fp[it]);
					it++;	
				}
				extsort(it,"--");
				system("cat output.txt");
				//remove("output.txt");
		}
		
		else if(strcmp(argv[1],"-t") == 0 && strcmp(argv[2],".") == 0 ){
			char ch;
			int fd = open(argv[3],O_RDONLY);
			if(fd == -1) printf("Cannot open");
			int f_size = 0;
			while(read(fd,&ch,1)) f_size++;
			lseek(fd,0,SEEK_SET);
			int buf = f_size/(20480);
			FILE *out = fopen("output.txt","w");
		
				
				
				
				int p;
				int chk = 0;
				
				int no_of_lines = 0;
				while(1){
				if(chk > f_size - 1) break;
				char *str = (char *)calloc(1024 * 1024,sizeof(char));
				p = 0;
				i = 0;
				
				while(read(fd,&ch,1) && p < 20480){ 	 
							str[i] = ch;
							i++;
						if(ch == argv[2][0]) {
							p++;
							no_of_lines++;
						}
						chk++;
				}
				lseek(fd,-1,SEEK_CUR);
				char *tok[no_of_lines + 2];
				char *token;
				i = 0;
				token = strtok(str,argv[2]);
				while(token != NULL){
					tok[i] = token;
					i++;
					token = strtok(NULL,argv[2]); 	
				}
				
				//printf("Number of lines is %d\n\n",no_of_lines);
				MergeSort(tok,0,no_of_lines - 1,it,"-t");
				int k;
				for(k = 0; k < no_of_lines;k++)
				fprintf(out,"%s\n",tok[k]);
				free(str);
				it++;	
				}
				fclose(out);
				system("cat output.txt");						
				remove("output.txt");
		}
		
		
		
		else if(strcmp(argv[1],"-k") == 0 ){
		int k_val;
		printf("Enter column number\n");
		scanf("%d",&k_val);
		char s[3];
		sprintf(s,"%d",k_val);
		int f_size = 0;
		while(fgetc(fd) != EOF) f_size++;
		rewind(fd);
		
		int buf = f_size/(2048*250);
		int size = f_size/10;
		if(buf == 0) buf = f_size/10;
		
		FILE *fp[buf + 1];
		char *on[buf + 1];
		FILE *ft = fopen("temp_file.txt","w+");
			if(ft == NULL) return -1;
			for(i =0 ; i <= buf ;i++){
				fprintf(ft,"f%lld.txt\n",i);
			}
			rewind(ft);
			on[0] = (char *)malloc(100);
			for(i = 0 ; i <= buf ;i++){
				on[i] = (char *)malloc(100);
				fgets(on[i],100,ft);
			}
			fclose(ft);
			char *str[2048*250];
			while(1){
					if(feof(fd)) break;
					i = 0;
					str[0] = (char *)malloc(1024);
					while(i < 2048*250){ 	 
							fgets(str[i],1024,fd);
							if(feof(fd)) break;
							i++;
							str[i] = (char *)malloc(1024);
					}
					//printf("Number of lines is %lld\n\n",i);
					MergeSort(str,0,i - 1,it,s);
					fp[it] = fopen(on[it],"w");
					free(on[it]);
					for(int k = 0 ; k < i ;k++){
						fprintf(fp[it],"%s",str[k]);
						free(str[k]);
					}
					fclose(fp[it]);
					it++;	
				}
				free(on[it]);
				extsort(it,"--");
				system("cat output.txt");
				remove("output.txt");
		
		}
		
		
		
		
		
		
    
	
	else{
		printf("Sort: Invalid option\n");
		return 1;
	}
	
	

	
	
	
		
	if(argc == 2) fclose(fd);
	else if(argc == 3) fclose(fd);
	else {
		int i;
		for(i = 2; i < argc ;i++){
			fclose(f[i]);
		}
	}
	return 0;
}
