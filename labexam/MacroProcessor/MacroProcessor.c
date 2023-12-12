// prgram to implement single pass macro processor

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char label[20], opcode[20], operand[20], buffer[20];
FILE *fp1, *fp2, *fp3, *fp4, *fp5;
int isExpanding = 0, deftabIndex = 0;
void processline();  

void getline()
{
    if (isExpanding == 1)
    {
        fp5 = fopen("argtab.txt", "r");
        if (fp5 == NULL) {
            printf("Error opening argtab.txt\n");
            exit(1);
        }
        
        if (operand[0] == '?')
        {
            char indexStr[5];             //as atoi can be called for strings only
            strcpy(indexStr, &operand[1]);
            int index = atoi(indexStr);
            int i = 0;
            while (i++ < index)
            {
                fscanf(fp5, "%s", operand);
            }
        }
        fscanf(fp4, "%s%s%s", label, opcode, operand);
        fclose(fp5);
    }
    else
    {
        fscanf(fp1, "%s%s%s", label, opcode, operand);
    }
}


void define()
{
    int operandIndex = 1;
    char newOperand[20];
    fprintf(fp3, "%s\t%d\n", label, deftabIndex++);
    fprintf(fp4, "%s\t%s\n", label, operand);
    // add operand splitting with , and store to solve the order issue
    while (strcmp(opcode, "MEND") != 0)
    {
        getline();
        if (operand[0] == '&')
        {
            sprintf(newOperand, "?%d", operandIndex++);
            fprintf(fp4, "%s\t%s\t%s\n", label, opcode, newOperand);
        }
        else
        {
            fprintf(fp4, "%s\t%s\t%s\n", label, opcode, operand);
        }
    }
    rewind(fp3);
    //fprintf(fp4, "%s\n", opcode);
}

void expand(int foundline)
{
    isExpanding = 1;
    int currentline = 0;
    fprintf(fp2, ".%s\t%s\t%s\n", label, opcode, operand);
    fp5 = fopen("argtab.txt", "w");
    int length = strlen(operand);
    for (int i = 0; i < length; i++)
    {
        if (operand[i] != ',')
        {
            fprintf(fp5, "%c", operand[i]);
        }
        else
        {
            fprintf(fp5, "\n");
        }
    }
    fclose(fp5);
    // skipping macrodefinition lines
    while (currentline++ < foundline)
    {
        getline();
    }
    while (strcmp(opcode, "MEND") != 0)
    {
        getline();
        processline();
    }
    isExpanding=0;
    getline();
    
}


void processline()
{
    printf("FIRSTLINE\t%s\t%s\t%s\n", label, opcode, operand);
    int foundline = -1,index=0;
    if(fp3==NULL)
        printf("NULL\n");
    while (fscanf(fp3, "%s%d", buffer, &index) != EOF)
    {
        printf("%s\n", buffer);
        printf("%s\n", opcode);
        if (strcmp(opcode, buffer) == 0)
        {
            printf("FOUND\n");
            foundline = index;
            break;
        }
    }
    rewind(fp3); // reset file pointer to start of file
    if (foundline != -1)
    {
        printf("foundline %d\n", foundline);
        expand(index);
    }
    else if (strcmp(opcode, "MACRO") == 0)
        define();
    else
        fprintf(fp2, "%s\t%s\t%s\n", label, opcode, operand);


}



int main()
{
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w+");
    fp3 = fopen("nametab.txt", "w+");
    fp4 = fopen("deftab.txt", "w+");
    while (strcmp(opcode, "END") != 0)
    {
        getline();
        processline();
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}