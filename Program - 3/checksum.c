#include<stdio.h>

unsigned checksum()
{
    unsigned sum=0;
    printf("Enter the data in 16 bit words : ");
    for(int i=0;i<9;i++)
    {
        unsigned field;
        scanf("%x",&field);
        sum+=field;
        while(sum>>16)
            sum = (sum & 0xFFFF) + (sum>>16);
    }
    return (unsigned short)~sum;
}

int main()
{
    int i1,i2;
    i1=checksum();
    i2=checksum();
    printf("Checksum at sender:%x\nChecksum at reciever:%x\n",i1,i2);
    if(i1==i2)
        printf("No Error\n");
    else
        printf("Error\n");
    return 0;
}