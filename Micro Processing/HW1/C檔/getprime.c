#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number[101]; // index 0~100

    //初始化

    int i;
    for(i = 0 ; i < 101 ; i++)
    {
        number[i] = 0;
    }

    //從最小的質數2開始
    printf(" Prime Generator < 100:\n");

    int test = 2, temp;
    int counter = 0;
    while(test < 101)
    {
    	if(number[test] == 0)
    	{
    		printf("%d ", test);
    		counter++;
    	}
    	if(counter == 10)
    	{
    		printf("\n");
    		counter = 0;
    	}

        int multiple = 1;
        temp = test * multiple;

        while(temp < 101)
        {
            number[temp] = 1;
            multiple++;
            temp = test * multiple;
        }
        test++;
    }
}
