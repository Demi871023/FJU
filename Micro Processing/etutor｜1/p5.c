// P5: Unpacking Characters from an Integer
#include <stdio.h>
#include <stdlib.h>

void toBinary(unsigned int num)
{
    int spacecounter = 0;
    for(int i = 0 ; i < 32 ; i++)
    {
        if(num & (1 << (31 - i))) printf("1");
        else printf("0");
        spacecounter++;
        if(spacecounter == 8)
        {
            printf(" ");
            spacecounter = 0;
        }
    }
    printf("\n");
}

int main()
{
    unsigned int input;
    scanf("%u", &input);

    printf("The packed character representation is:\n%u = ", input);

    toBinary(input);
    printf("\n");

    unsigned int temp1, temp2, temp3, temp4;

    temp1 = input & 0xFF000000;
    temp1 = temp1 >> 24;
    temp2 = input & 0xFF0000;
    temp2 = temp2 >> 16;
    temp3 = input & 0xFF00;
    temp3 = temp3 >> 8;
    temp4 = input & 0xFF;

    //printf("The unpacked characters are '%c' and '%c' and '%c' and '%c'\n", (char)temp1, (char)temp2, (char)temp3, (char)temp4);
    printf("%u = ", temp1);
    toBinary(temp1);
    printf("%u = ", temp2);
    toBinary(temp2);
    printf("%u = ", temp3);
    toBinary(temp3);
    printf("%u = ", temp4);
    toBinary(temp4);

}