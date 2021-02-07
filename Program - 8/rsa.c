#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int isprime(int x)
{
    for(int i=2;i<x/2;i++)
        if(x%i==0) return 0;
    return 1;
}

int gcd(int m,int n)
{
    int r;
    while(n!=0)
    {
        r=m%n;m=n;n=r;
    }
    return m;
}

long encrypt(char ch,long n,long e)
{
    long val = ch;
    for(int i=1;i<e;i++)
        val = (val*ch)%n;
    return val;
}

char decrypt(long ch,long n,long d)
{
    long val = ch;
    for(int i=1;i<d;i++)
        val = (val*ch)%n;
    return val;
}

int main()
{
    long int p,q,n,e,d,phi;
    do
    {
        p=rand()%100;
    } while (!isprime(p));
    do
    {
        q=rand()%100;
    } while (!isprime(q));
    n=p*q;phi=(p-1)*(q-1);
    do
    {
        e=rand()%phi;
    } while (gcd(phi,e)!=1);
    do
    {
        d=rand()%phi;
    } while ((d*e)%phi != 1);
    printf("p:%d,q:%d,n:%d,phi:%d,e:%d,d:%d\n",p,q,n,phi,e,d);    
    char text[50],plain[50];int i,len,cipher[50];
    printf("Enter the text : ");
    scanf("%s",text);
    len=strlen(text);
    for(i=0;i<len;i++)
        cipher[i] = encrypt(text[i],n,e);
    for(i=0;i<len;i++)
        plain[i] = decrypt(cipher[i],n,d);
    
    printf("Cipher text:\n");
    for(i=0;i<len;i++)
        printf("%d",cipher[i]);
    printf("\n");
    printf("Plain text:\n");
    for(i=0;i<len;i++)
        printf("%c",plain[i]);
    printf("\n");
}