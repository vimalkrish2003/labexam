#include <stdio.h>
int main()
{
    int p, r;
    printf("Enter the number of processes and resources :");
    scanf("%d %d", &p, &r);

    int allocation[p][r], max[p][r], need[p][r], available[r], finish[p],sequence[p];
    for (int i = 0; i < p; i++)
    {
        printf("enter the max resources for P%d :",i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    for (int i = 0; i < p; i++)
    {
        printf("enter the allocated resources for P%d :",i);
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter the available resources :");
    for (int i = 0; i < r; i++)
    {
        scanf("%d", &available[i]);
    }
    printf("The need matrix is :\n");
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
            printf(" %d ", need[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < p; i++)
    {
        finish[i] = 0;
    }
    // bankers
    int y=0;
    for (int k = 0; k < p; k++)
    {
        for (int i = 0; i < p; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < r; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag==0)
                {
                    for(int j=0;j<r;j++)
                    {
                        available[j]=available[j]+allocation[i][j];
                    }
                    sequence[y++]=i;
                    finish[i]=1;

                }
            }
        }
    }

    int issafe=1;
    for(int i=0;i<p;i++)
    {
        if(finish[i]==0)
        {
            printf("The system is not in safe state\n");
            issafe=0;
            break;
        }
    }
    if(issafe==1)
    {
        printf("The system is in safe state\n the safe sequence is\n");
        for(int i=0;i<y;i++)
        {
            printf("%d => ",sequence[i]);
        }
    }
    return 0;
} 