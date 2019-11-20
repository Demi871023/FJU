// P6 : Reversing the Order of an Integer's Bi

#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int input, reverse = 0;
    scanf("%u", &input);

    printf("Before bits are reversed:\n%u = ", input);
    int spacecounter = 0;

    //10進位制轉2進位制
    for(int i = 0 ; i < 32 ; i++)
    {
        if(input & (1 << (31 - i)))   printf("1");
        else printf("0");
        spacecounter++;
        if(spacecounter == 8)
        {
            printf(" ");
            spacecounter = 0;
        }
    printf("\n\n");

    for(int i = 0 ; i < 32 ; i++)
    {
        int bit = input & (1 << i);
        if(bit)
        {
            reverse = reverse | (1 << (31 - i));
        }
    }

    printf("After bits are reversed:\n%u = ", reverse);
    for(int i = 0 ; i < 32 ; i++)
    {
        if(reverse & (1 << (31 - i)))   printf("1");
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