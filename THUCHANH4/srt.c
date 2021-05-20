#include <stdio.h> 
#include<stdlib.h>
#include<string.h>
#define FILENAME1 "Input.txt"
#define FILENAME2 "Output.txt"

char* substr(char* des, const char* source,int pos, int len){
	while(len>0){
		*des = *(source + pos);
		des++;
		source++;
		len--;
	}
	*des ='\0';
	return des;
}


int main() 
{ 
     
	int np[10], ari[10], bur[10], bur1[10], total = 0, procs[100], fin[10]; 
	float tavg = 0.0, wavg = 0.0;
	int wt[10], star[10], rr[10];
      
////////////////////////////////////////////////////////////////////////////
	char *line_buf = NULL;
  	ssize_t line_size;
	size_t line_buf_size = 0;
	
	FILE* fp = fopen(FILENAME1,"r");
	
  	line_size = getline(&line_buf, &line_buf_size, fp);
	int n = atoi(line_buf);
  	int i = 0;
  	while (i<n)
  	{
    		line_size = getline(&line_buf, &line_buf_size, fp);
    		int Array[4];
    		int m = 0;
    		char des[10];
    		int D =0;
    		for (int j = 0;j< strlen(line_buf);j++){
    			if(line_buf[j] ==' '|| line_buf[j] == '\n'){
    				int len = j - D;
    				substr(des,line_buf,D,len);
    				Array[m] = atoi(des);
				m++;
    				D = j+1;
    			}
    		}
    		np[i] = Array[0];
    		ari[i] = Array[1];
		bur[i] = Array[2];
    		i++;
  	}
	free(line_buf);
  	line_buf = NULL;
  	fclose(fp);

////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < n; i++) { 
        	total += bur[i]; 
	} 
     	for(int i = 0;i<n;i++){
		bur1[i] = bur[i];
	}
	
	for (int i = 0; i < n; i++) {                  //1
        	for (int j = i + 1; j < n; j++) { 
     
			if (ari[i] > ari[j]){ 
				int temp = ari[i];     
				ari[i] = ari[j];     
				ari[j] = temp;     
				temp = bur[i];      
				bur[i] = bur[j];  
				bur[j] = temp; 
			} 
		} 
	} 
	int k = 0; 
	for (int i = 0; i < total; i++){                //2
        	int small = 10000; 
     
        	for (int j = 0;j < n;j++){ 
			if ((bur[j] != 0) && (ari[j] <= i) && (bur[j] < small)){ 
				small = bur[j]; 
				k = j;
			}     
        	}		 
        	bur[k]--; 
        	procs[i] = k; 
      	} 
	for (int i = 0; i < total; i++){                //3
        	for (int j = 0; j < n; j++){ 	     
          		if (procs[i] == j){ 
            			fin[j] = i;
          		}     
        	} 
      } 
// Nguon tham khao(phan 1,2,3): https://www.quora.com/How-do-I-write-a-C-program-to-implement-a-SRTF-Shortest-Remaining-Time-First-scheduling-algorithm-along-with-displaying-the-Gantt-chart


////////////////////////////////////////////////////////////////////////////
	star[0] = 0;
	rr[0] = 0;
	int check = 0;
    	int D = 1;
    	for (int i = 1; i< total;i++){
    		for(int j = 0; j<n; j++){
    	   		if(procs[i] == rr[j]){
    				check = 1;
    	   		}
    		}
        	if(check == 0){
           		int w = procs[i];
           		rr[D] = w;
           		star[w] = i;
           		D++;
    		}
    		else{ 
    			check = 0;
    		}	
    	}
 
////////////////////////////////////////////////////////////////////////////
        FILE* fptr = fopen(FILENAME2,"w");
      	for (i = 0; i < n; i++){ 
      		int name = np[i];
        	int fis = fin[i] + 1;
        	int tat =(fin[i] - ari[i]) + 1;
        	int wt = ((fin[i] + 1) - bur1[i]) - ari[i];
        	int resp = star[i] - ari[i];
        
        	fprintf(fptr,"%d %d %d %d \n",name, resp, wt, tat);      
        	wavg = wavg + (((fin[i] + 1) - bur1[i]) - ari[i]);      
        	tavg = tavg + ((fin[i] - ari[i]) + 1); 
      	} 
        wavg = wavg/n;
        tavg = tavg/n;
        fprintf(fptr,"%0.2f\n%0.2f\n", wavg,tavg ); 
	fclose(fptr);
      return 0; 
} 

