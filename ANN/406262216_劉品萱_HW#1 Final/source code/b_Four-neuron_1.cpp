/* 406262216 資工三乙 劉品萱 */
/* 類神經作業 Program 1 */
/* b(1) 2個屬性 4個神經元 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>
#include <cstring>

#define trainingMAXN 10
#define testMAXN 5
#define useProperty 2
#define useNeurons 4     
#define learningRate 1

/*  兩個神經元            四個神經元
    class 1 = {0,0}  →    {1,0,0,0}
    class 2 = {0,1}  →    {0,1,0,0}
    class 3 = {1,0}  →    {0,0,1,0}
    class 4 = {1,1}  →    {0,0,0,1}
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

// 已知的 DataSet1 的訓練資料
int pp1[8] = {1,1,2,2,-1,-2,-1,-2};
int pp2[8] = {1,2,-1,0,2,1,-1,-2};
int tt1[8] = {1,1,0,0,0,0,0,0};
int tt2[8] = {0,0,1,1,0,0,0,0};
int tt3[8] = {0,0,0,0,1,1,0,0};
int tt4[8] = {0,0,0,0,0,0,1,1};

// 已知的 DataSet 1 的測試資料
int ppp1[4] = {5,0,-1,-3};
int ppp2[4] = {2,-2,1,-4};

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

// Transfer Function
int hardlim(double n)
{
    if( n >= 0 )
        return 1;
    else
        return 0;
}

// 確認有無 error，若有error，則回傳 true，進行更新 M 以及 b。
bool testError(int n)
{
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
    int trainNum = 8;
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
        if(passNum == 8)
            allpass = true;
    }
}

// 分類
char testClass()
{
    if(a[0][0] == 1 && a[1][0] == 0 && a[2][0] == 0 && a[3][0] == 0)
        return '1';
    else if(a[0][0] == 0 && a[1][0] == 1 && a[2][0] == 0 && a[3][0] == 0)
        return '2';
    else if(a[0][0] == 0 && a[1][0] == 0 && a[2][0] == 1 && a[3][0] == 0)
        return '3';
    else if(a[0][0] == 0 && a[1][0] == 0 && a[2][0] == 0 && a[3][0] == 1)
        return '4';
    else
        return '?';
}

// 測試
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
    srand(time(NULL)); // 使每一次執行所產生的亂數皆不同
    setup(); // 設置 M 以及 b


    // 輸出 Initial weights
    printf("\nInitial weights:\n");
    for(int i = 0 ; i < useNeurons ; i++)
    {
        for(int j = 0 ; j < useProperty ; j++)
        {
            printf("%lf ", initM[i][j]);
        }
        printf("\n");
    }

    // 輸出 Initial biases
    printf("\nInitial biases:\n");
    for(int i = 0 ; i < useNeurons ; i++)
    {
        printf("%lf\n", initb[i][0]);
    }

    // 設置 DataSet1 的資料
    for(int i = 0 ; i < 8 ; i++)
    {
        trainingP[i].p1 = pp1[i];
        trainingP[i].p2 = pp2[i];
        trainingP[i].t1 = tt1[i];
        trainingP[i].t2 = tt2[i];
        trainingP[i].t3 = tt3[i];
        trainingP[i].t4 = tt4[i];
    }

    // 開始訓練
    training(useNeurons, useProperty);
    
    // 輸出最終花費世代數
    printf("\nEnd epoch number: %d\n", epochCheck);

    // 輸出 Final weight
    printf("\nFinal weight:\n");
    for(int i = 0 ; i < useNeurons ; i++)
    {
        for(int j = 0 ; j < useProperty ; j++)
        {
            printf("%lf ", initM[i][j]);
        }
        printf("\n");
    }

    // 輸出 Final biases
    printf("\nFinal biases:\n");
    for(int i = 0 ; i < useNeurons ; i++)
    {
        printf("%lf\n", initb[i][0]);
    }

    // 開始測試及輸出測試結果
    printf("\nTest data:\n");
    for(int i = 0 ; i < 4 ; i++)
    {
        testP[i].p1 = ppp1[i];
        testP[i].p2 = ppp2[i];
        printf("P%d%c ", i+9, testing(useNeurons, useProperty, i));
    }
}