// P3：檢查數字特定位元

#include <cstdio>
#include <cstdlib>
#include <algorithm>


int confirmbit[35];

int main()
{
    int bit, n = 0;
    while(scanf("%d", &bit))
    {
        if(bit == -1)   break;
        else
        {
            confirmbit[n] = bit;
            n++;
        }
    }

    sort(confirmbit, confirmbit+n);

    for(int i = 0 ; i < n ; i++)
    {
        if(confirmbit[i] == confirmbit[i+1])    continue;
        else printf("%d ", confirmbit[i]);
    }
    printf("\n");

    unsigned int input, quoient, remainder;
    unsigned int output[32];
    int casenumber = 1;

    while(~scanf("%u", &input))
    {
        printf("Case %d: %u\n", casenumber++, input);

        //初始化
        for(int i = 0 ; i < 32 ; i++)
        {
            output[i] = 0;
        }

        int count = 0;
        while(input != 0)
        {
            quoient = input >> 1;
            remainder = input - (quoient << 1);
            output[count] = remainder;
            count++;
            input = quoient;
        }

        bool exit = false;
        int all = 0;

        for(int i = 0 ; i < n ; i++)
        {
            int confirm = confirmbit[i];
            if(output[confirm] == 1)
            {
                exit = true;
                all++;
            }
        }

        if(n == all)    printf("true(all bits 1)\n");
        else    printf("false(all bits 1)\n");

        if(exit)    printf("true(exist bits 1)\n");
        else    printf("false(exist bits 1)\n");


    }
}