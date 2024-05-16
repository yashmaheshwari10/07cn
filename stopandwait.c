#include <stdio.h>
#include <stdlib.h>

int numofPacket;
float tp;
float tt;
float time = 0;
int i, j, k;

void sender();
void receiver();

void sender(){
    printf("\nEnter number of packets :");
    scanf("%d", &numofPacket);
    
    int packet[numofPacket];

    printf("\nEnter packets : ");
    for(i = 0; i < numofPacket; i++){
        scanf("\n%d", &packet[i]);
    }

    printf("\nEnter transmission time in ms : ");
    scanf("%f", &tt);

    printf("\nEnter propagation time in ms : ");
    scanf("%f", &tp);

    printf("\nTheoretically time taken to transmit %d number of packets should be %.2f", numofPacket, numofPacket*2*(tt+tp));
    printf("\n");
    
    for(i = 0; i < numofPacket; i++){
        time += tt;
        printf("\nFor %d : \n",packet[i]);
        printf("\nBuffer time is %.2f",time);
        receiver();
    }
    printf("\n");
    printf("\nTotal time taken is %.2f", time);
    printf("\n");
}

void receiver(){
    time += tp;
    printf("\nPacket received at %.2f", time);
    time += tt;
    printf("\nAcknowledgement sent at %.2f", time);
    time += tp;
    printf("\nAcknowledgement received at %.2f", time);
    printf("\n-----------------------");

    printf("\n");
}

int main(){
    sender();
    return 0;
}