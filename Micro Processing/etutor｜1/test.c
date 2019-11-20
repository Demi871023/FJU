#include <stdio.h>
#include <stdlib.h>


/*unsigned int reverseBits(unsigned int num) 
{ 
    unsigned int reverse = 0, i, temp; 
  
    for (i = 0 ; i < 32 ; i++) 
    {
        printf("~~~%u\n", (1<<i));
        temp = (num & (1 << i));
        if(temp) 
        {
            reverse |= (1 << ((32 - 1) - i));
            printf("%u\n", reverse);
        }
    }
   
    return reverse; 
} */
  



/* Driver function to test above function */
int main() 
{ 
    unsigned int input, reverse, temp;
    unsigned int binaryinput[32];

    for(int i = 0 ; i < 32 ; i++)
    {
        binaryinput[i] = 0;
    }

    scanf("%u", &input);
    temp = input;

    printf("Before bits are reversed:\n%u = ", input);

    unsigned int quoient, remainder;
    int count = 0;
    while(temp != 0)
    {
        quoient = temp >> 1;
        binaryinput[count] = remainder;
        count++;
        temp = quoient;
    }

    int spacecounter = 0;

    for(int i = 31 ; i >= 0 ; i--)
    {
        printf("%u", binaryinput[i]);
        spacecounter++;
        if(spacecounter == 8)
        {
            printf(" ");
            spacecounter = 0;
        }
    }
    printf("\n");


    for(int i = 0 ; i < 32 ; i++)
    {
        int bit = (input & (1 << i));
        if(bit)
        {
            reverse =  reverse | (1 << (32 - 1 - i));
        }
    }

    printf("After bits are reversed:\n%u", reverse);

    //printf("%u", reverseBits(input));

    for(int i = 0 ; i < 32 ; i++)
    {
        if(10 & (1 << (31 - i)))    printf("1");
        else printf("0");
    }
} 