// P4：Packing Characters into an Integer
// ASCII 32 ' '

#include <stdio.h>
#include <stdlib.h>
void displayBits(int value)
{
    int spacecounter = 0;
    for(int i = 0 ; i < 32 ; i++)
    {
        if(value & (1 << (31 - i)))   printf("1");
        else printf("0");
        spacecounter++;
        if(spacecounter == 8 && i != 31)
        {
            printf(" ");
            spacecounter = 0;
        }
    }
    printf("\n");
}

unsigned int packCharacters(char a, char b)
{
    printf("%c:\n%d = ", a, (a - ' ' + 32));
    displayBits((int)(a - ' ') + 32);
    printf("%c:\n%d = ", b, (b - ' ' + 32));
    displayBits((int)(b - ' ') + 32);
    return ((a - ' ' + 32) << 8) + (b - ' ' + 32);
}

int main()
{
    char c1, c2, c3, c4;
    scanf("%c %c %c %c", &c1, &c2, &c3, &c4);

    unsigned int temp1 = packCharacters(c1, c2);
    unsigned int temp2 = packCharacters(c3, c4);

    printf("'%c' and '%c' and '%c' and '%c' packed in an unsigned int:\n", c1, c2, c3, c4);
    unsigned Integer = (temp1 << 16) + temp2;
    printf("%u = ", Integer);
    int spacecounter = 0;
    for(int i = 0 ; i < 32 ; i++)
    {
        if(Integer & (1 << (31 - i)))   printf("1");
        else printf("0");
        spacecounter++;
        if(spacecounter == 8 && i != 31)
        {
            printf(" ");
            spacecounter = 0;
        }
    }
    printf("\n");
}