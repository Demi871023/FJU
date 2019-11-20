// P1：數字半位元組分割

#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int input, quoient, remainder;
    unsigned int output[8];

    int casenumber = 1;

    while(~scanf("%u", &input))
    {

        printf("Case %d: %u\n", casenumber++, input);

        // 初始化
        for(int i = 0 ; i < 8 ; i++)
        {
            output[i] = 0;
        }

        int count = 0;

        // input >> 4 的結果相當於 input / 16
        while(input != 0)
        {
            quoient = input >> 4;
            remainder = input - (quoient << 4);
            output[count] = remainder;
            count++;
            input = quoient;
        }

        for(int i = 7 ; i >= 0 ; i--)
        {
            if(output[i] < 10)
            {
                printf("%u ", output[i]);
            }
            else
            {
                printf("%c ", (char)output[i] - 10 + 65);
            }      
        }
        printf("\n");
    }

}