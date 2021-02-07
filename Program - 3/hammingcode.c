#include<stdio.h>

int main()
{
    int msgs[10],msgr[10];
    printf("Enter the data bitwise : ");
    scanf("%d %d %d %d",&msgs[0],&msgs[1],&msgs[2],&msgs[4]);
    msgs[3]=msgs[0]^msgs[1]^msgs[2];
    msgs[5]=msgs[0]^msgs[1]^msgs[4];
    msgs[6]=msgs[0]^msgs[2]^msgs[4];
    printf("Encoded Data : \n");
    for(int i=0;i<7;i++)
        printf("%d",msgs[i]);
    printf("\n");
    
    printf("Enter the data recieved by reciever : ");
    for(int i=0;i<7;i++)
        scanf("%d",&msgr[i]);
    int c1,c2,c3,c;
    c1 = msgr[6]^msgr[2]^msgr[4]^msgr[0];
    c2 = msgr[5]^msgr[1]^msgr[4]^msgr[0];
    c3 = msgr[3]^msgr[2]^msgr[1]^msgr[0];
    c=c3*4+c2*2+c1;
    if(c==0) printf("No Error");
    else{
        printf("Recieved Data : \n");
        for(int i=0;i<7;i++)
            printf("%d",msgr[i]);
        printf("\n");
        printf("Error at bit %d\nCorrected data : ",8-c);
        msgr[7-c]=(msgr[7-c]==1 ? 0 :1);
        for(int i=0;i<7;i++)
            printf("%d",msgr[i]);
        printf("\n");
    }
    return 0;
}