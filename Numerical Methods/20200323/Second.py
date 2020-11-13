import array
import math
import random
import matplotlib.pyplot as plt

FxPicX = []
FxPicY = []

# 計算 F(x) 微分後在 X 點的數值
def FxDerAnswer(x):
    return(math.exp(x) + math.cos(2 * x) - 2 * x * math.sin(2 * x))
# 計算 F(x) 微分後在 X 點的數值
def FxAnswer(x):
    return(math.exp(x) + x * math.cos(2 * x) - 3)    

# 二分法
def BisectionMethod():
    # 準備將數據寫入黨案
    BisectionFile = open("Bisection.txt", "w")
    BisectionFile.write("Bisection Method\n\n")

    counter = 0
    a = -8
    b = -7
    
    while(abs(a - b) >= 2 * 1e-8):
        counter = counter + 1
        c = (a + b) / 2

        # 若 FxAnswer(a) * FxAnswer(c) < 0，即代表 a 和 c 之間有解
        if(FxAnswer(a) * FxAnswer(c) < 0):
            b = c
        else:
            a = c
        BisectionFile.write("Step " + str(counter) + " : c is " + str(c) + " and f(" + str(c) + ") is " + str(FxAnswer(c)) + "\n")
    # 輸出找到的最後解相近值
    print("Bisection Method ： " + str((a+b)/2) + ", use " + str(counter) + " times." + "\n")
    BisectionFile.close()

# 假位法
def FalsePositionMethod():
    FalsePositionFile = open("FalsePosition.txt", "w")
    FalsePositionFile.write("False Position Method\n\n")

    counter = 0
    a = -8
    b = -7
    xold = 1
    c = 0

    while(abs(xold - c) >= 1e-8):
        counter = counter + 1
        xold = c
        c = (a * FxAnswer(b) - b * FxAnswer(a)) / (FxAnswer(b) - FxAnswer(a))
        if(FxAnswer(a) * FxAnswer(c) < 0):
            b = c
        else:
            a = c
        FalsePositionFile.write("Step " + str(counter) + " : c is " + str(c) + " and f(" + str(c) + ") is " + str(FxAnswer(c)) + "\n")
    print("False Position Method : " + str(c) + ", use " + str(counter) + " times." +"\n")
    FalsePositionFile.close()

# 修正假位法
def ModifyFalsePositionMethod():
    ModifyFalsePositionFile = open("ModifyFalsePosition.txt", "w")
    ModifyFalsePositionFile.write("Modify False Position Method\n\n")

    counter = 0
    a = -8
    b = -7
    Fa = FxAnswer(a)
    Fb = FxAnswer(b)
    xold = 1
    c = 0

    while(abs(xold - c) >= 1e-8):
        counter = counter + 1
        c = ((a * Fb) - (b * Fa)) / (Fb - Fa)
        Fc = FxAnswer(c)
        xold = c
        if(FxAnswer(a) * FxAnswer(c) < 0):
            b = c
            Fa = Fa / 2
        else:
            a = c
            Fb = Fb / 2
        ModifyFalsePositionFile.write("Step " + str(counter) + " : c is " + str(c) + " and f(" + str(c) + ") is " + str(FxAnswer(c)) + "\n")
    print("Modify False Position Method : " + str(c) + ", use " + str(counter) + " times." +"\n")
    ModifyFalsePositionFile.close()

# 割線法
def SecantMethod():

    SecantFile = open("Secant.txt", "w")
    SecantFile.write("Secant Method\n\n")

    counter = 0
    a = random.uniform(-6, -8)
    b = random.uniform(-4, -6)

    while(abs(a - b) >= 1e-8):
        counter = counter + 1
        c = (a * FxAnswer(b) - b * FxAnswer(a)) / (FxAnswer(b) - FxAnswer(a))
        a = b
        b = c
        SecantFile.write("Step " + str(counter) + " : c is " + str(c) + " and f(" + str(c) + ") is " + str(FxAnswer(c)) + "\n")

    print("Secant Method : " + str(c) + ", use " + str(counter) + " times." +"\n")
    SecantFile.close()

# 牛頓法
def NewtonsMethod():
    NewtonsFile = open("Newtons.txt", "w")
    NewtonsFile.write("Newtons Method\n\n")

    counter = 0
    # 在 -6 和 -7 之間取一個浮點數亂數
    c = random.uniform(-7, -8)
    
    while(abs(-(FxAnswer(c) / FxDerAnswer(c))) > 1e-8):
        counter = counter + 1
        c = c - (FxAnswer(c) / FxDerAnswer(c))
        NewtonsFile.write("Step " + str(counter) + " : c is " + str(c) + " and f(" + str(c) + ") is " + str(FxAnswer(c)) + "\n")
    print("Newtons Method : " + str(c) + ", use " + str(counter) + " times\n")
    NewtonsFile.close()

# 固定點法
def FixedPointMethod():
    
    FixedPointFile = open("FixedPoint.txt", "w")
    FixedPointFile.write("Fixed Point Method")

    counter = 0
    xold = 0
    c = -7
    while(abs(xold - c) >= 1e-8):
        counter = counter + 1
        #print(c)
        xold = c
        c = math.log(-c * math.cos(2 * c) + 3)
        FixedPointFile.write("Step " + str(counter) + " : c is " + str(c) + " and f(" + str(c) + ") is " + str(FxAnswer(c)) + "\n")
    print("Fixed Point Method : " + str(c) + ", use " + str(counter) + " times\n")
    FixedPointFile.close()


    
# 取得要計算的 x 值與其在曲線 F(x) 的數值後，繪製出圖型   
def SetUpPicXY():
    i = -10
    while(i <= 2):
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

BisectionMethod()
FalsePositionMethod()
ModifyFalsePositionMethod()
NewtonsMethod()
SecantMethod()
FixedPointMethod()
