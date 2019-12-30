#include <cstdio>
#include <cstdlib>
#include <random>
#include <ctime>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

#define TrainingMax 125
#define TestingMax 35
#define EpochMax 500000             // 最大世代數
#define LearningRate 1
#define e 2.71828182846
#define tao 0.1                     // 最大 ERMSE 數值

#define useProperty 4               // 訓練及測試資料所使用屬性個數（題目所定）
#define OutputLayerNeuron 3         // 輸出層使用的神經元個數（題目所定）
#define HiddenLayerNeuron 20        // 隱藏層使用的神經元個數（自訂，最多 5 個）

double ErrorTotoalCount = 0;

// 隱藏層及輸出層的 Matrix 及 Biases
double Layer_1_Matrix[HiddenLayerNeuron][useProperty];
double Layer_2_Matrix[OutputLayerNeuron][HiddenLayerNeuron];
double Layer_1_Biases[HiddenLayerNeuron][1];
double Layer_2_Biases[OutputLayerNeuron][1];

// 暫存隱藏層及輸出層的 Matrix 及 Biases，用於測試不同 Matrix 與 Biases 初始值影響所用
double Layer_1_Matrix_Tmp[HiddenLayerNeuron][useProperty];
double Layer_2_Matrix_Tmp[OutputLayerNeuron][HiddenLayerNeuron];
double Layer_1_Biases_Tmp[HiddenLayerNeuron][1];
double Layer_2_Biases_Tmp[OutputLayerNeuron][1];

// 隱藏層輸出與輸出層輸出
double ah[HiddenLayerNeuron][1];
double a[OutputLayerNeuron][1];

// 隱藏層 error 與輸出層 error
double deltah[HiddenLayerNeuron][1];
double delta[OutputLayerNeuron][1];

double ErrorTotal[OutputLayerNeuron][1];

int epochNum;
bool Wrong = true;

struct Training_Point
{
    double feature1, feature2, feature3, feature4;
    char tname[15];
    string tanswer; // 目標類別
    string tclass;  // 測驗判斷類別
    double t1, t2, t3;
};

struct Testing_Point
{
    double feature1, feature2, feature3, feature4;
    char tans[15];  // txt檔案讀入類別
    string tanswer; // 目標類別
    string tclass;  // 測驗判斷類別
    double t1, t2, t3;
};

Training_Point TrainingP[TrainingMax];
Testing_Point TestingP[TestingMax];


// 產生亂數
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// active function
double sigmoid(double power)
{
    double tmp = 1 + pow(e, -power);
    return (1 / tmp);
}

// 以亂數產生 M 以及 b
void setup()
{
    // Layer 1 Martix
    for(int i = 0 ; i < HiddenLayerNeuron ; i++)
        for(int j = 0 ; j < useProperty ; j++)
            Layer_1_Matrix[i][j] = fRand(0,1);

    for(int i = 0 ; i < HiddenLayerNeuron ; i++)
        for(int j = 0 ; j < useProperty ; j++)
            Layer_1_Matrix_Tmp[i][j] = Layer_1_Matrix[i][j];

    // Layer 1 Biases
    for(int i = 0 ; i < HiddenLayerNeuron ; i++)
        Layer_1_Biases[i][0] = fRand(0,1);

    for(int i = 0 ; i < HiddenLayerNeuron ; i++)
        Layer_1_Biases_Tmp[i][0] = Layer_1_Biases[i][0];

    // Layer 2 Martix
    for(int i = 0 ; i < OutputLayerNeuron ; i++)
        for(int j = 0 ; j < HiddenLayerNeuron ; j++)
            Layer_2_Matrix[i][j] = fRand(0,1);
    
    for(int i = 0 ; i < OutputLayerNeuron ; i++)
        for(int j = 0 ; j < HiddenLayerNeuron ; j++)
            Layer_2_Matrix_Tmp[i][j] = Layer_2_Matrix[i][j];

    // Layer 2 Biases  
    for(int i = 0 ; i < OutputLayerNeuron ; i++)
        Layer_2_Biases[i][0] = fRand(0,1);

    for(int i = 0 ; i < OutputLayerNeuron ; i++)
        Layer_2_Biases_Tmp[i][0] = Layer_2_Biases[i][0];
}

// 判斷所有 Error 的平方總和除以個數後再開根號是否有小於所設定的最大 ERMSE 數值
void ErrorTest()
{
    // 若小於，則給予 Wrong false，即訓練完畢
    if(sqrt(ErrorTotoalCount / 120) < tao)
        Wrong = false;
}

// 計算一個世代中所有 Error 的平方總和
void ErrorCount(int n)
{
    // 計算一個世代的所有error總和（tn - an)^2
    ErrorTotoalCount = ErrorTotoalCount + pow((TrainingP[n].t1 - a[0][0]),2) + pow((TrainingP[n].t2 - a[1][0]),2) + pow((TrainingP[n].t3 - a[2][0]),2);
}

// 更新 Matrix 與 Biases。傳入第幾個 node 的 n 及隱藏層使用的神經元個數
void Update(int n, int un)
{
    // Layer 1 Weight
    for(int i = 0 ; i < un ; i++)
    {
        for(int j = 0 ; j < useProperty ; j++)
        {
            if(j == 0)
                Layer_1_Matrix[i][j] = Layer_1_Matrix[i][j] + (LearningRate * deltah[i][0] * TrainingP[n].feature1);
            if(j == 1)
                Layer_1_Matrix[i][j] = Layer_1_Matrix[i][j] + (LearningRate * deltah[i][0] * TrainingP[n].feature2);
            if(j == 2)
                Layer_1_Matrix[i][j] = Layer_1_Matrix[i][j] + (LearningRate * deltah[i][0] * TrainingP[n].feature3);
            if(j == 4)
                Layer_1_Matrix[i][j] = Layer_1_Matrix[i][j] + (LearningRate * deltah[i][0] * TrainingP[n].feature4);
        }
    }
    // Layer 1 Biases
    for(int i = 0 ; i < un ; i++)
    {
        Layer_1_Biases[i][0] = Layer_1_Biases[i][0] + LearningRate * deltah[i][0];
    }
    // Layer 2 Martix
    for(int i = 0 ; i < OutputLayerNeuron ; i++)
    {
        for(int j = 0 ; j < un ; j++)
        {
            Layer_2_Matrix[i][j] = Layer_2_Matrix[i][j] + (LearningRate * delta[i][0] * ah[j][0]);
        }
    }
    // Layer 2 Basies
    for(int i = 0 ; i < OutputLayerNeuron ; i++)
    {
        Layer_2_Biases[i][0] = Layer_2_Biases[i][0] + (LearningRate * delta[i][0]);
    }
}

// 訓練，傳入的是此次訓練隱藏層所使用的神經元個數
void Training(int HiddenN)
{
    epochNum = 0;
    
    while(1)
    {
        // 如果超過最大世代數 或 Error 小於所設立的值
        if(epochNum >= EpochMax || !Wrong)
            break;
        memset(ErrorTotal, 0, sizeof(ErrorTotal));
        ErrorTotoalCount = 0;
        for(int n = 0 ; n < 120 ; n++)
        {
            memset(a, 0, sizeof(a));
            memset(ah, 0, sizeof(ah));
            // Lyaer 1：Hidden Layer
            for(int i = 0 ; i < HiddenN ; i ++)
            {
                double netinput = 0;
                for(int j = 0 ; j < useProperty ; j++)
                {
                    if(j == 0)
                        netinput = netinput + (Layer_1_Matrix[i][j] * TrainingP[n].feature1);
                    if(j == 1)
                        netinput = netinput + (Layer_1_Matrix[i][j] * TrainingP[n].feature2);
                    if(j == 2)
                        netinput = netinput + (Layer_1_Matrix[i][j] * TrainingP[n].feature3);
                    if(j == 3)
                        netinput = netinput + (Layer_1_Matrix[i][j] * TrainingP[n].feature4);
                }
                netinput = netinput + Layer_1_Biases[i][0];
                ah[i][0] = sigmoid(netinput);
            }

            // Layer 2：Output Layer
            for(int i = 0 ; i < OutputLayerNeuron ; i++)
            {
                double netinput = 0;
                for(int j = 0 ; j < HiddenN ; j++)
                {
                    // netinput 加總幾次決定於 Hidden Layer 使用幾個神經元
                    netinput = netinput + (Layer_2_Matrix[i][j] * ah[j][0]);
                }
                netinput = netinput + Layer_2_Biases[i][0];
                a[i][0] = sigmoid(netinput);
            }

            memset(delta, 0, sizeof(delta));
            memset(deltah, 0, sizeof(deltah));

            // 計算輸出層的 Error Delta
            for(int i = 0 ; i < OutputLayerNeuron ; i++)
            {
                if(i == 0)
                    delta[i][0] = (TrainingP[n].t1 - a[i][0])*(a[i][0] * (1 - a[i][0]));
                if(i == 1)
                    delta[i][0] = (TrainingP[n].t2 - a[i][0])*(a[i][0] * (1 - a[i][0]));
                if(i == 2)
                    delta[i][0] = (TrainingP[n].t3 - a[i][0])*(a[i][0] * (1 - a[i][0]));
            }

            // 計算隱藏層的 Error Delta
            for(int i = 0 ; i < HiddenN ; i++)
            {
                deltah[i][0] = ((delta[0][0] * Layer_2_Matrix[0][i]) + (delta[1][0] * Layer_2_Matrix[1][i]) + (delta[2][0] * Layer_2_Matrix[2][i])) * (ah[i][0] * (1 - ah[i][0]));
            }
            Update(n, HiddenN);
            ErrorCount(n);   
        }
        ErrorTest();
        epochNum++;
    }   
}

// 為讀入的 Training Data 設置所屬類別的目標值
void setTarget(int n)
{
    // versicolor
    if(TrainingP[n].tanswer == "versicolor")
    {
        TrainingP[n].t1 = 0.9;
        TrainingP[n].t2 = 0.1;
        TrainingP[n].t3 = 0.1;
    }
    // virginica
    if(TrainingP[n].tanswer == "virginica")
    {
        TrainingP[n].t1 = 0.1;
        TrainingP[n].t2 = 0.9;
        TrainingP[n].t3 = 0.1;
    }
    // setosa
    if(TrainingP[n].tanswer == "setosa")
    {
        TrainingP[n].t1 = 0.1;
        TrainingP[n].t2 = 0.1; 
        TrainingP[n].t3 = 0.9;
    }
}

// 分類
void TestClass(int n, int c)
{
    // Training Data Use
    if(c == 0)
    {
        if(a[0][0] > a[1][0] && a[0][0] > a[2][0])
            TrainingP[n].tclass = "versicolor";
        if(a[1][0] > a[0][0] && a[1][0] > a[2][0])
            TrainingP[n].tclass = "virginica";
        if(a[2][0] > a[0][0] && a[2][0] > a[1][0])
            TrainingP[n].tclass = "setosa";
    }
    // Testing Data Use
    if(c == 1)
    {
        if(a[0][0] > a[1][0] && a[0][0] > a[2][0])
            TestingP[n].tclass = "versicolor";
        if(a[1][0] > a[0][0] && a[1][0] > a[2][0])
            TestingP[n].tclass = "virginica";
        if(a[2][0] > a[0][0] && a[2][0] > a[1][0])
            TestingP[n].tclass = "setosa";
    }
}

// Testing Data 測試
void Testing(int HiddenN)
{
    for(int n = 0 ; n < 30 ; n++)
    {
        memset(a, 0, sizeof(a));
        memset(ah, 0, sizeof(ah));

        // Layer 1
        for(int i = 0 ; i < HiddenN ; i++)
        {
            double netinput = 0;
            for(int j = 0 ; j < useProperty ; j++)
            {
                if(j == 0)
                    netinput = netinput + (Layer_1_Matrix[i][j] * TestingP[n].feature1);
                if(j == 1)
                    netinput = netinput + (Layer_1_Matrix[i][j] * TestingP[n].feature2);
                if(j == 2)
                    netinput = netinput + (Layer_1_Matrix[i][j] * TestingP[n].feature3);
                if(j == 3)
                    netinput = netinput + (Layer_1_Matrix[i][j] * TestingP[n].feature4);
            }
            netinput = netinput + Layer_1_Biases[i][0];
            ah[i][0] = sigmoid(netinput);
        }

        // Layer 2
        for(int i = 0 ; i < OutputLayerNeuron ; i++)
        {
            double netinput = 0;
            for(int j = 0 ; j < HiddenN ; j++)
            {
                netinput = netinput + (Layer_2_Matrix[i][j] * ah[j][0]);
            }
            netinput = netinput + Layer_2_Biases[i][0];
            a[i][0] = sigmoid(netinput);
        }
        TestClass(n, 1);
    }
}

// Training Data 測試
void TrainingDataTesting(int HiddenN)
{
    for(int n = 0 ; n < 120 ; n++)
    {
        memset(a, 0, sizeof(a));
        memset(ah, 0, sizeof(ah));
        // Layer 1
        for(int i = 0 ; i < HiddenN ; i++)
        {
            double netinput = 0;
            for(int j = 0 ; j < useProperty ; j++)
            {
                if(j == 0)
                    netinput = netinput + (Layer_1_Matrix[i][j] * TrainingP[n].feature1);
                if(j == 1)
                    netinput = netinput + (Layer_1_Matrix[i][j] * TrainingP[n].feature2);
                if(j == 2)
                    netinput = netinput + (Layer_1_Matrix[i][j] * TrainingP[n].feature3);
                if(j == 3)
                    netinput = netinput + (Layer_1_Matrix[i][j] * TrainingP[n].feature4);
            }
            netinput = netinput + Layer_1_Biases[i][0];
            ah[i][0] = sigmoid(netinput);
        }

        // Layer 2
        for(int i = 0 ; i < OutputLayerNeuron ; i++)
        {
            double netinput = 0;
            for(int j = 0 ; j < HiddenN ; j++)
            {
                netinput = netinput + (Layer_2_Matrix[i][j] * ah[j][0]);
            }
            netinput = netinput + Layer_2_Biases[i][0];
            a[i][0] = sigmoid(netinput);
        }
        TestClass(n, 0);
    }
}

// 計算 Training accuracies
int TrainingAccuracies()
{
    int TraingingCorrectNum = 0;
    for(int i = 0 ; i < 120 ; i++)
    {
        if(TrainingP[i].tanswer == TrainingP[i].tclass)
            TraingingCorrectNum++;
    }
    return (TraingingCorrectNum * 100 / 120);
}

// 計算 Testing accuracies
int TestingAccuracies()
{
    int TestingCorrectNum = 0;
    for(int i = 0 ; i < 30 ; i++)
    {
        if(TestingP[i].tanswer == TestingP[i].tclass)
            TestingCorrectNum++;
    }
    return (TestingCorrectNum * 100 / 30);
}

// 回覆初始的 Matrix 與 Biases，此函式用於測試 Matrix 與 Biases 初始值不同時的影響
void Reset()
{
    for(int i = 0 ; i < HiddenLayerNeuron ; i++)
        for(int j = 0 ; j < useProperty ; j++)
            Layer_1_Matrix[i][j] = Layer_1_Matrix_Tmp[i][j];

    for(int i = 0 ; i < HiddenLayerNeuron ; i++)
        Layer_1_Biases[i][0] = Layer_1_Biases_Tmp[i][0];
    
    for(int i = 0 ; i < OutputLayerNeuron ; i++)
        for(int j = 0 ; j < HiddenLayerNeuron ; j++)
            Layer_2_Matrix[i][j] = Layer_2_Matrix_Tmp[i][j];

    for(int i = 0 ; i < OutputLayerNeuron ; i++)
        Layer_2_Biases[i][0] = Layer_2_Biases_Tmp[i][0];
}

int main()
{
    // 使每一次產生的亂數皆為不同的值
    srand(time(NULL));      

    // 讀入訓練的資料
    freopen("iris_training_data.txt", "r", stdin);
    for(int i = 0 ; i < 120 ; i++)
    {
        scanf("%lf %lf %lf %lf", &TrainingP[i].feature1, &TrainingP[i].feature2, &TrainingP[i].feature3, &TrainingP[i].feature4);
        cin >> TrainingP[i].tanswer;
        setTarget(i);
    }

    // 讀入測試的資料
    freopen("iris_testing_data.txt", "r", stdin);
    for(int i = 0 ; i < 30 ; i++)
    {
        scanf("%lf %lf %lf %lf %s", &TestingP[i].feature1, &TestingP[i].feature2, &TestingP[i].feature3, &TestingP[i].feature4, TestingP[i].tans);
        if(TestingP[i].tans[0] == 'v' && TestingP[i].tans[1] == 'e')
            TestingP[i].tanswer = "versicolor";
        if(TestingP[i].tans[0] == 'v' && TestingP[i].tans[1] == 'i')
            TestingP[i].tanswer = "virginica";
        if(TestingP[i].tans[0] == 's' && TestingP[i].tans[1] == 'e')
            TestingP[i].tanswer = "setosa";
    }
    
    // 從一個神經元個數開始，跑至所設定的最大神經元個數
    for(int i = 1 ; i <= HiddenLayerNeuron ; i++)
    {
        Wrong = true;
        setup(); 
        printf("\n---------------------------------------------\n");
        printf("Number of hidden neurons = %d\n", i);
        printf("Learning rates = %d\n", LearningRate);
        Training(i);
        printf("Epoch: %d\n", epochNum);
        TrainingDataTesting(i);
        printf("training accuracies = %d%%\n", TrainingAccuracies());
        Testing(i);
        printf("testing accuracies = %d%%\n", TestingAccuracies());
    }
    return 0;
}