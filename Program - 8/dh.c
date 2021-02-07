#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int compute(int g,int x,int p)
{
    int res = pow((g%p),x);
    return res%p;
}

int main()
{
    int p=7,g=3;
    printf("Value of P:%d, G:%d\n",p,g);
    srand(time(0));
    int a = rand()%10+1;
    int A = compute(g,a,p);
    printf("a:%d , A:%d\n",a,A);
    int b;
    do{
        b = rand()%10+1;
    }while(b==a);
    int B = compute(g,b,p);
    printf("b:%d , B:%d\n",b,B);
    int keyA = compute(B,a,p),keyB=compute(A,b,p);
    printf("keyA:%d, keyB:%d\n",keyA,keyB);
}