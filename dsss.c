#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char data [3];
char xnorValue [11];
char pattern [11] = {'1', '0', '1', '1', '0', '1', '1', '1', '0', '0', '0'};
char res [33];
char resReceiver[33];
int ptr = 0;
int ptrReceiver = 0;
char chunk [11];
int start=0;
int end = 10;

void xnorfunction(char bit,char pattern[]){

    for (int k = 0; k < 11; k++)
    {
        xnorValue[k] = bit;
    }

    for (int  j= 0; j < 11; j++)
    {
        res[ptr] = ((xnorValue[j] == pattern[j] ? '1' : '0'));
        ptr++;
    }   
}

void xnorfunctionForReceiver(char arr[],char pattern[]){

    for (int  j= 0; j < 11; j++)
    {
        resReceiver[ptrReceiver] = ((arr[j] == pattern[j] ? '1' : '0'));
        ptrReceiver++;
    }
    
}

void makeChunks(char res[]){
    
    for (int w = start; w <= end; w++)
    {
       chunk[w-start] = res[w];
    }
    start += 11;
    end += 11;
}

void xnoresult(char arr[]){
    for (int q = 0; q < 33; q++)
    {
        printf("%c",arr[q]);
    }
    printf("\n");
}

int main(){
    printf("Enter data to be sent :");
    scanf("%s",data);

    for(int i = 0 ; i<3 ;i++){
        xnorfunction(data[i],pattern);
    }

    printf("Data converted to 33 bit :");

    for (int l = 0; l < 33; l++)
    {
        printf("%c",res[l]);
    }

    printf("\n");


    start=0;
    end =10;

    for(int p = 0 ; p < 3;p++){          //instead of 3 write : res length / 3;
        //0-10 11-21 22-32
        makeChunks(res);
        xnorfunctionForReceiver(chunk,pattern);
    }

    printf("Received data:");
    xnoresult(resReceiver);
    
    printf("Extracting original data from receiverd data : ");
    for(int g = 0 ; g<33;g++){
        if(g%11 == 0){
            printf("%c",resReceiver[g]);
        }
    }
    
    return 0;
}