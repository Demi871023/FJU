#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>
#include <cstring>

#define trainingMAXN 1005
#define testMAXN 45
#define useProperty 3
#define useNeurons 2
#define learningRate 1

/*   兩個神經元              四個神經元
  class W = {1,1}  ｜   class W = {1,0,0,0}
  class O = {0,1}  ｜   class O = {0,1,0,0}
  class P = {0,0}  ｜   class P = {0,0,1,0}
  class B = {1,0}  ｜   class B = {0,0,0,1}
*/

struct Training_Point
{
    double p1, p2, p3;
    char fruit;
    int t1, t2, t3, t4;
};

struct Testing_Point
{
    double p1, p2, p3;
    int t1, t2, t3, t4;
};

double initM[useNeurons][useProperty];
double initb[useNeurons][1];

int error[useNeurons][1];
int a[useNeurons][1];

int epochCheck;

Training_Point trainingP[trainingMAXN];
Testing_Point testP[testMAXN];

// 產生亂數
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// 以亂數產生 M 以及 b
void setup()
{
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            initM[i][j] = fRand(-10, 10);
        }
    }
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 3 ; j++)
        {
            initb[i][j] = fRand(-10, 10);
        }
    }
}

// 設定相對應目標值
void setupTarget(char c, int i)
{
    if(useNeurons == 2)
    {
        if(c == 'W')
        {
            trainingP[i].t1 = 1;
            trainingP[i].t2 = 1;
        }
        else if(c == 'O')
        {
            trainingP[i].t1 = 0;
            trainingP[i].t2 = 1;
        }
        else if(c == 'P')
        {
            trainingP[i].t1 = 0;
            trainingP[i].t2 = 0;
        }
        else if(c == 'B')
        {
            trainingP[i].t1 = 1;
            trainingP[i].t2 = 0;
        }
    }
    if(useNeurons == 4)
    {
        if(c == 'W')
        {
            trainingP[i].t1 = 1; 
            trainingP[i].t2 = 0; 
            trainingP[i].t3 = 0; 
            trainingP[i].t4 = 0;
        }
        else if(c == 'O')
        {
            trainingP[i].t1 = 0; 
            trainingP[i].t2 = 1; 
            trainingP[i].t3 = 0; 
            trainingP[i].t4 = 0;
        }
        else if(c == 'P')
        {
            trainingP[i].t1 = 0; 
            trainingP[i].t2 = 0; 
            trainingP[i].t3 = 1; 
            trainingP[i].t4 = 0;
        }
        else if(c == 'B')
        {
            trainingP[i].t1 = 0; 
            trainingP[i].t2 = 0; 
            trainingP[i].t3 = 0; 
            trainingP[i].t4 = 1;
        }
    }
}

// Transfer Function
int hardlim(double n)
{
    if( n >= 0 )
        return 1;
    else
        return 0;
}

// 確認有無 error
// 若有error，則回傳 true，更新 M 以及 b。
// 若皆為 0，則回傳 false，無須更新。
bool testError(int n)
{
    // 初始化 error array
    memset(error, 0, sizeof(error));
    bool change = false;
    for(int i = 0 ; i < useNeurons ; i++)
    {
        if(i == 0)
            error[i][0] = trainingP[n].t1 - a[i][0];
        else if(i == 1)
            error[i][0] = trainingP[n].t2 - a[i][0];
        else if(i == 2)
            error[i][0] = trainingP[n].t3 - a[i][0];
        else if(i == 3)
            error[i][0] = trainingP[n].t4 - a[i][0];
        
        if(error[i][0] != 0)
            change = true;
    }
    return change;
}

// 更新 M 以及 b
void change(int n)
{
    for(int i = 0 ; i < useNeurons ; i++)
    {
        for(int j = 0 ; j < useProperty ; j++)
        {
            if(j == 0)
                initM[i][j] = initM[i][j] + learningRate * (error[i][0] * trainingP[n].p1);
            else if(j == 1)
                initM[i][j] = initM[i][j] + learningRate * (error[i][0] * trainingP[n].p2);
            else if(j == 2)
                initM[i][j] = initM[i][j] + learningRate * (error[i][0] * trainingP[n].p3);  
        }
    }
    for(int i = 0 ; i < useNeurons ; i++)
    {
        initb[i][0] = initb[i][0] + learningRate * error[i][0];
    }
}

// 訓練
void training(int un, int up)
{
    int trainNum = 1000;
    bool allpass = false;
    int epochMAX = 10000;
    epochCheck = 0;

    while(1)
    {
        int passNum = 0;
        // 當所有 p 的 a 和 t 都相同，或訓練已超過定好的最大世代數，則訓練完成  
        if(allpass || epochCheck > epochMAX)
            break;
        epochCheck++;
        for(int n = 0 ; n < trainNum ; n++)
        {                      
            memset(a, 0, sizeof(a));
            for(int i = 0 ; i < un ; i++)
            {
                double netinput = 0;
                for(int j = 0 ; j < up ; j++)
                {
                    if(j == 0)
                        netinput = netinput + (initM[i][j] * trainingP[n].p1);
                    else if(j == 1)
                        netinput = netinput + (initM[i][j] * trainingP[n].p2);
                    else if(j == 2)
                        netinput = netinput + (initM[i][j] * trainingP[n].p3);
                }
                netinput = netinput + initb[i][0];
                a[i][0] = hardlim(netinput);
            }
            if(testError(n))
                change(n);     
            else
                passNum++;
        }
        if(passNum == 1000)
            allpass = true;
    }
}

char testClass()
{

    if(useNeurons == 2)
    {
        if(a[0][0] == 1 && a[1][0] == 1)
            return 'W';
        else if(a[0][0] == 0 && a[1][0] == 1)
            return 'O';
        else if(a[0][0] == 0 && a[1][0] == 0)
            return 'P';
        else if(a[0][0] == 1 && a[1][0] == 0)
            return 'B';
        else
            return '?';
    }
    if(useNeurons == 4)
    {
        if(a[0][0] == 1 && a[1][0] == 0 && a[2][0] == 0 && a[3][0] == 0)
            return 'W';
        else if(a[0][0] == 0 && a[1][0] == 1 && a[2][0] == 0 && a[3][0] == 0)
            return 'O';
        else if(a[0][0] == 0 && a[1][0] == 0 && a[2][0] == 1 && a[3][0] == 0)
            return 'P';
        else if(a[0][0] == 0 && a[1][0] == 0 && a[2][0] == 0 && a[3][0] == 1)
            return 'B';
        else
            return '?';
    }
    
}

char testing(int un, int up, int n)
{
    memset(a, 0, sizeof(a));
    for(int i = 0 ; i < un ; i++)
    {
        double netinput = 0;
        for(int j = 0 ; j < up ; j++)
        {
            if(j == 0)
                netinput = netinput + (initM[i][j] * testP[n].p1);
            else if(j == 1)
                netinput = netinput + (initM[i][j] * testP[n].p2);
            else if(j == 2)
                netinput = netinput + (initM[i][j] * testP[n].p3);
        }
        netinput = netinput + initb[i][0];
        a[i][0] = hardlim(netinput);
    }
    return testClass();
}

int main()
{
    srand(time(NULL));
    setup();

    // Initial Weight
    printf("\nInitial weights:\n");
    for(int i = 0 ; i < useNeurons ; i++)
    {
        for(int j = 0 ; j < useProperty ; j++)
        {
            printf("%lf ", initM[i][j]);
        }
        printf("\n");
    }

    // Initial biases
    printf("\nInitial biases:\n");
    for(int i = 0 ; i < useNeurons ; i++)
    {
        printf("%lf\n", initb[i][0]);
    }

    // Read data from training_data.txt file
    freopen("training_data.txt", "r", stdin);

    for(int i = 0 ; i < 1000 ; i++)
    {
        scanf("%lf %lf %lf %c", &trainingP[i].p1, &trainingP[i].p2, &trainingP[i].p3, &trainingP[i].fruit);
        setupTarget(trainingP[i].fruit, i);
    }

    // 開始訓練
    training(useNeurons, useProperty);
    
    // 最後停止世代數
    printf("\nEnd epoch number: %d\n", epochCheck);

    // Final Weight
    printf("\nFinal weight:\n");
    for(int i = 0 ; i < useNeurons ; i++)
    {
        for(int j = 0 ; j < useProperty ; j++)
        {
            printf("%lf ", initM[i][j]);
        }
        printf("\n");
    }

    // Final biases
    printf("\nFinal biases:\n");
    for(int i = 0 ; i < useNeurons ; i++)
    {
        printf("%lf\n", initb[i][0]);
    }

    // Read data from testing_data.txt file
    freopen("testing_data.txt", "r", stdin);
    
    // 開始測試
    printf("\nTest data:\n");
    for(int i = 0 ; i < 40 ; i++)
    {
        scanf("%lf %lf %lf", &testP[i].p1, &testP[i].p2, &testP[i].p3);
        printf("%d%c ", i+1, testing(useNeurons, useProperty, i));
    }
    
}
