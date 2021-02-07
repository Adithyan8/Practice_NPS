#include<stdio.h>
#include<stdlib.h>

int adjmat[10][10],d[10],p[10];

void bf(int s,int n)
{
    int i,u,v;
    for(i=1;i<n;i++)
    {
        for(u=0;u<n;u++)
            for(v=0;v<n;v++)
                if(d[v]>d[u]+adjmat[u][v])
                {
                    d[v]=d[u]+adjmat[u][v];
                    p[v]=u;
                }
    }
    for(u=0;u<n;u++)
        for(v=0;v<n;v++)
            if(d[v]>d[u]+adjmat[u][v])
            {
                printf("Negative Edge exists. Exiting.");
                exit(0);
            }
}

/*
//Keeping all vertices as source and destination for every source
int main()
{
    int n,i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&adjmat[i][j]);
    int source;
    for(source = 0;source<n;source++)
    {
        for(i=0;i<n;i++)
        {
            p[i]=-1;
            d[i]=999;
        }
        d[source]=0;
        bf(source,n);
        printf("Source : %d\n",source);
        for(i=0;i<n;i++)
        {
            printf("Destination : %d\n",i);
            if(i!=source)
            {
                j=i;
                while(p[j]!=-1)
                {
                    printf("%d<-",j);
                    j=p[j];
                }
            }
            printf("%d , Cost:%d\n",source,d[i]);
        }
    }
    return 0;
*/

//For specific source and vertex
int main()
{
    int n,i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&adjmat[i][j]);
    int source,dest;
    scanf("%d %d",&source,&dest);
    for(i=0;i<n;i++)
    {
        p[i]=-1;
        d[i]=999;
    }
    d[source]=0;
    bf(source,n);
    if(dest!=source)
    {
        j=dest;
        while(p[j]!=-1)
        {
            printf("%d<-",j);
            j=p[j];
        }
    }
    printf("%d , Cost:%d\n",source,d[dest]);

    return 0;
}