import array
import math
import matplotlib.pyplot as plt

x = ["-10", "-9", "-8", "-7", "-6", "-5", "-4", "-3", "-2", "-1", "0"]
FxNumber = []


def FxAnswer(x):
    return(math.exp(x) + x * math.cos(2 * x) + 3)

def BisectionMethod():
    a = -7
    b = -6
    while(abs(a - b) >= 2 * 1e-8):
        c = (a + b) / 2
        if(FxAnswer(a) * FxAnswer(c) < 0):
            b = c
        else:
            a = c
    return (a + b) / 2

# 計算出當 x = 0 到 x = -10 的 f(x)
def FindAB():
    for i in range(-10, 1):
        FxNumber.append(FxAnswer(i))


def Draw():
    plt.gcf().set_size_inches(15, 10)
    # plot 為繪製折線圖、bar 為繪製長條圖
    plt.plot(x,FxNumber, '-o', color='r', alpha = 0.8)
    plt.title('f(x) = e^x + x * cos(2x) + 3 in f(-10) ~ f(0) value')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.savefig('F(x)Value.png')
    #plt.show()

print(BisectionMethod())
FindAB()
print(FxNumber)
Draw()
