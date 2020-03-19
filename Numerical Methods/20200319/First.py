import array
import math
import random
import matplotlib.pyplot as plt

FxPicX = []
FxPicY = []

# Bisection Method
BisectionCP = []
BisectionValue = []
# False Position Method
FalsePositionCP = []
FalsePositionValue = []
# Newtons Method
NewtonsCP = []
NewtonsValue = []

# 計算 F(x) 微分後在 X 點的數值
def FxDerAnswer(x):
    return(math.exp(x) + math.cos(2 * x) - 2 * x * math.sin(2 * x))
# 計算 F(x) 微分後在 X 點的數值
def FxAnswer(x):
    return(math.exp(x) + x * math.cos(2 * x) + 3)    

# 二分法
def BisectionMethod():
    counter = 0
    a = -7
    b = -6
    while(abs(a - b) >= 2 * 1e-8):
        counter = counter + 1
        c = (a + b) / 2
        BisectionCP.append(c)
        BisectionValue.append(FxAnswer(c))
        # 若 FxAnswer(a) * FxAnswer(c) < 0，即代表 a 和 c 之間有解
        if(FxAnswer(a) * FxAnswer(c) < 0):
            b = c
        else:
            a = c
    # 繪製出找每一次抓取的位置圖
    plt.grid(True)
    plt.plot(FxPicX, FxPicY, '-', color='g', alpha = 0.5)
    plt.plot(BisectionCP, BisectionValue, '-o', color='b', alpha = 0.2, lw=0.5)
    plt.title('Bisection Method')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.savefig('BisectionMethod.png')
    # 輸出找到的最後解相近值
    print("Bisection Method ： " + str((a+b)/2) + ", use " + str(counter) + " times." + "\n")

# 假位法
def FalsePositionMethod():
    counter = 0
    a = -7
    b = -6
    xold = 1
    c = 0

    temp1 = [a, b]
    temp2 = [FxAnswer(a), FxAnswer(b)]
    # 繪製基本 F(x) 值域圖與初始 a、b 的 f(a)、f(b) 連線
    plt.grid(True)
    plt.plot(FxPicX, FxPicY, '-', color='g', alpha = 0.5)
    plt.plot(temp1, temp2, '-o', color='r', alpha = 0.7, lw = 0.5)

    while(abs(xold - c) >= 1e-8):
        counter = counter + 1
        xold = c
        c = (a * FxAnswer(b) - b * FxAnswer(a)) / (FxAnswer(b) - FxAnswer(a))
        if(FxAnswer(a) * FxAnswer(c) < 0):
            b = c
            temp1 = [a]
            temp2 = [FxAnswer(a)]
        else:
            a = c
            temp1 = [b]
            temp2 = [FxAnswer(b)]
        temp1.append(c)
        temp2.append(FxAnswer(c))
        plt.plot(temp1, temp2, '-o', color='r', alpha = 0.7, lw = 0.5)

    plt.title('False Position Method')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.savefig('FalsePositionMethod.png')
    print("False Position Method : " + str(c) + ", use " + str(counter) + " times." +"\n")

def ModifyFalsePosition():
    counter = 0
    a = -7
    b = -6

# 割線法
#def SecantMethod():

# 牛頓法
def NewtonsMethod():
    counter = 0
    # 在 -6 和 -7 之間取一個浮點數亂數
    a = random.uniform(-6, -7)
    plt.grid(True)
    plt.plot(FxPicX, FxPicY, '-', color='g', alpha = 0.5)
    
    while(abs(-(FxAnswer(a) / FxDerAnswer(a))) > 1e-8):
        temp1 = [a]
        temp2 = [FxAnswer(a)]
        counter = counter + 1
        a = a - (FxAnswer(a) / FxDerAnswer(a))
        temp1.append(a)
        temp2.append(FxAnswer(a))
        plt.plot(temp1, temp2, '-+', color='r', alpha = 0.7, lw = 0.5)

    plt.title('Newtons Method')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.savefig('NewtonsMethod.png')
    print("Newtons Method : " + str(a) + ", use " + str(counter) + " times\n")


    
# 取得要計算的 x 值與其在曲線 F(x) 的數值後，繪製出圖型   
def SetUpPicXY():
    i = -10
    while(i <= 0):
        FxPicX.append(i)
        FxPicY.append(FxAnswer(i))
        i = i + 0.2
    plt.grid(True)
    plt.plot(FxPicX, FxPicY, '-', color='g', alpha = 0.5)
    plt.title('f(x) = e^x + x * cos(2x) + 3 in f(-7) ~ f(-6) value')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.savefig('F(x)ValuePic.png')

SetUpPicXY()
#BisectionMethod()
#FalsePositionMethod()
NewtonsMethod()

