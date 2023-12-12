#include <stdio.h>
//FIFO
void fifo(int frames[],int pages[],int nofframes,int nofpages)
{
    int hit=0,miss=0;
    printf("Requests\t\tFrames\n");
    for(int i=0;i<nofpages;i++)
    {
        int flag=0;
        for(int j=0;j<nofframes;j++)
        {
            if(frames[j]==pages[i])
            {
                hit++;
                flag=1;
                break;
            }
        }

        if(flag==0)
        {
            miss++;
            frames[i%nofframes]=pages[i];
        }
        printf("%d\t\t",pages[i]);
        for(int j=0;j<nofframes;j++)
        {
            printf("%d  ",frames[j]);
        }
        printf("\n");
    }
}
//LRU
void lru(int frames[],int pages[],int nofframes,int nofpages)
{
    int hit=0,miss=0;
    printf("Requests\t\tFrames\n");
    for(int i=0;i<nofpages;i++)
    {
        int flag=0;
        for(int j=0;j<nofframes;j++)
        {
            if(frames[j]==pages[i])
            {
                hit++;
                flag=1;
                int temp=frames[j];
                for(int k=j;k>0;k--)
                {
                    frames[k]=frames[k-1];
                }
                frames[0]=temp;
                break;
            }
        }
        if(flag==0)
        {
            miss++;
            for(int j=nofframes;j>0;j--)
            {
                    frames[j]=frames[j-1];
            }
            frames[0]=pages[i];
        }

        printf("%d\t\t",pages[i]);
        for(int j=0;j<nofframes;j++)
        {
            printf("%d  ",frames[j]);
        }
        printf("\n");

    }    

}






int main()
{
    int nofframes,nofpages;
    printf("Enter the number of frames: ");
    scanf("%d",&nofframes);
    printf("Enter the number of pages: ");
    scanf("%d",&nofpages);
    int frames[nofframes],pages[nofpages];
    printf("Enter the pages: ");
    for(int i=0;i<nofpages;i++)
    {
        scanf("%d",&pages[i]);
    }
    for(int i=0;i<nofframes;i++)
    {
        frames[i]=-1;
    }
    lru(frames,pages,nofframes,nofpages);

    
}