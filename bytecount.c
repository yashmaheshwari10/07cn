#include<stdio.h>
#include<string.h>
char data [8];
char datawithLen[9];
void sender(){
    printf("\nSender\n-------------------------------------");

    printf("\nEnter data :");
    scanf("%s",data);

    int len = strlen(data);
    datawithLen[0] = (len+1) + '0'; // char to int => add '0' to char
 
    for(int i = 0 ; i < len ; i++){
        datawithLen[i+1] = data[i];
    }

    datawithLen[len+1] ='\0';
    printf("\nData to send : ");
    for(int i = 0 ; i <= len ; i++){
        printf("%c ",datawithLen[i]);
    }
}

void receiver(char datawithLen[]){
    printf("\n\nReceiver\n-------------------------------------");
    int lenofDataReceived = datawithLen[0] - '0'; // char to integer => subtract '0' from char
    printf("\nOriginal Data : ");
    for(int i = 1 ; i <= lenofDataReceived ; i++){
        printf("%c ",datawithLen[i]);
    }
}
int main(){
    sender();
    receiver(datawithLen);
}