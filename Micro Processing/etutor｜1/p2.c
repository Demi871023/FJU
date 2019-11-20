// P2：數字系統轉換

#include <stdio.h>
#include <stdlib.h>

unsigned int output[32];
int count;

// (2進位) 32 bit
void printBinary(unsigned int n)
{
    unsigned int quoient, remainder;
    count = 0;
    while(n != 0)
    {
        quoient = n >> 1;
        remainder = n - (quoient << 1);
        output[count] = remainder;
        count++;
        n = quoient;
    }

    for(int i = 31 ; i >= 0 ; i--)
    {
        printf("%u", output[i]);
    }
    printf("\n");
}

// (8進位) 12 bit
void printOctal(unsigned int n)
{
    unsigned int quoient, remainder;
    count = 0;
    while(n != 0)
    {
        quoient = n >> 3;
        remainder = n - (quoient << 3);
        output[count] = remainder;
        count++;
        n = quoient;
    }

    for(int i = 11 ; i >= 0 ; i--)
    {
        printf("%u", output[i]);
    }
    printf("\n");
}


// (16進位) 0x 8 bit
void printHexidecimal(unsigned int n)
{
    unsigned int quoient, remainder;
    count = 0;
    while(n != 0)
    {
        quoient = n >> 4;
        remainder = n - (quoient << 4);
        output[count] = remainder;
        count++;
        n = quoient;
    }

    printf("0x");

    for(int i = 7 ; i >= 0 ; i--)
    {
        if(output[i] < 10)
        {
            printf("%u", output[i]);
        }
        else
        {
            printf("%c", (char)output[i] - 10 + 65);
        } 
    }
    printf("\n");
}

int main()
{
    unsigned int input;
    int casenumber = 1;
    while(~scanf("%u", &input))
    {
        printf("Case %d: %u\n", casenumber++, input);
        // 初始化
        for(int i = 0 ; i < 32 ; i++)   output[i] = 0;
        printBinary(input);
        for(int i = 0 ; i < 32 ; i++)   output[i] = 0;
        printOctal(input);
        for(int i = 0 ; i < 32 ; i++)   output[i] = 0;
        printHexidecimal(input);
    }
}

