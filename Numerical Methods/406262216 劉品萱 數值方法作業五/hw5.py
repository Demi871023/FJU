import numpy as np
import matplotlib.pyplot as plt
import math

n = 45

# 存放讀入數據
x = []
y = []

# 存放次方數值
xtmp = []
ytmp = []

err = []

# 讀入 x y 數據
def SetUp():
    file = open("xyfile.txt")
    for i in range(0, 45):
        text = file.readline()
        x.append(float(text.split("  ", 2)[0]))
        xtmp.append(1)
        y.append(float(text.split("  ", 2)[1].replace("\n", "")))
        ytmp.append(0)
    file.close()

def GetMatrix():
    # a 為二維 np array，b 為一維 np array
    a = np.zeros((n,n))
    b = np.array([])

    # 決定這回合填入 knn 次填入 np array
    knn = 1
    ky = 0

    # 總共要走 k 次對角線（91）
    for k in range(0, 88):  # 做 k+1 * k+1 就代表右下角 i+j == k

        # 上三角與下三角的起始值不同，但方向同為右上到左下
        if(k < 45):
            i = 0
            j = k - i
        else:
            j = 44
            i = k - j

        sumx = 0
        sumy = 0

        # 針對每個點計算總和
        for nn in range(0, 45):
            sumy = sumy + y[nn] * xtmp[nn]      # sigma yx^ky
            sumx = sumx + xtmp[nn]              # sigma x^k
            xtmp[nn] = xtmp[nn] * x[nn]
        
        # 將 sumy 寫入 b np array
        if(ky < 45):
            b = np.append(b, sumy)
            ky = ky + 1
        
        # 將 sumx 斜著放入 a np array
        for kn in range(0, knn):
                a[i][j] = sumx
                i = i + 1
                j = j - 1

        # 第 k 回合中，要將數值填入 knn 次
        if(k < 44):
            knn = knn + 1
        else:
            knn = knn - 1

    np.savetxt("A_output", a)
    np.savetxt("B_output", b)
    return a, b

def GetSolve(m, a, b):
    aa = np.zeros((m+1, m+1))
    bb = np.array([])
    for i in range(0, m+1):
        for j in range(0, m+1):
            aa[i][j] = a[i][j]
        bb = np.append(bb, b[i])
    
    xx = np.linalg.solve(aa, bb)
    return xx

# 計算 P(X)，m 代表維度，即最高次方
def GetPxAns(m, x, xx):
    yy = []

    error = 0
    # 計算每一個 x 點在 m 維度情況下的數值
    for i in range(0, len(x)):
        sum = 0
        # p(x) = a0 + a1x + a2^2
        for j in range(0, m+1):
            sum = sum + xx[j] * pow(x[i], j)

        yy.append(sum)

        error = error + pow((sum - y[i]), 2)
        
    CountError(m, error)

    plt.figure()
    plt.grid(True)
    plt.plot(x, y, '-o', color='green', alpha = 0.5, label='Basic F(x)', Markersize=3)
    plt.plot(x, yy, '-o', color='red', alpha = 0.5, label='P(x)', Markersize = 3)
    plt.title("m = " + str(m))
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.legend()
    plt.savefig("./IMG/m = " + str(m) + " P(x).png", dpi=300)


def CountError(m, e):
    sigma = math.sqrt(e/(n-m))
    err.append(sigma)

def BestChoise():
    f = open("Error.txt", "w")
    max = 100000000
    best = 0
    for i in range(0, len(err)):
        f.write("m = " + str(i+2) + ", err is : " + str(err[i]) + "\n")
        if(max > err[i]):
            max = err[i]
            best = i + 2
    f.close()
    return best


#### main ####

SetUp()
A, B = GetMatrix()
# m 代表 P(x) 維度
for m in range(2, 45):
    # 求得在 m 維度下的係數 XX
    XX = GetSolve(m, A, B)
    GetPxAns(m, x, XX)

print("Best Choise is " + str(BestChoise()))
