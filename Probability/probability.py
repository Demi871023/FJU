# 機率與統計 作業一

import random
import numpy as np
import array
import matplotlib.pyplot as plt

#%matplotlib inline

# (1) 以亂數產生 100000 筆身高資料，畫出各個高度累計次數之長條圖

x = [
    '130','131','132','133','134','135','136','137','138','139',
    '140','141','142','143','144','145','146','147','148','149',
    '150','151','152','153','154','155','156','157','158','159',
    '160']

# Height_Random 為產生 100000 筆隨機身高所用
Height_Random = []
# Height_Count 為計算各個身高出現的次數
Height_Count = []

count = 0
while count < 100000:
    Height_Random.append(random.randint(130, 160))
    count = count + 1

height = 130;
while height < 161:
    Height_Count.append(Height_Random.count(height))
    height = height + 1

plt.gcf().set_size_inches(15, 10)
plt.bar(x,Height_Count, 0.4, color='g', alpha = 0.8)
plt.title('Each height total number in 100000 people')
plt.xlabel('Height(cm)')
plt.ylabel('Num(people)')

for x,y in enumerate(Height_Count):
    plt.text(x,y+100, '%s' %y, ha='center')

plt.show()


# (2) 由 10~80 任選 10 個數字，算出每個平均出現的頻率

# n 存放每幾個切割 100000 筆資料來計算平均
n = [10, 15, 20, 25, 30, 35, 40, 50, 60, 70]

# 每 n 筆計算每個平均出現的機率
for i in n:
    x = [
    '130','131','132','133','134','135','136','137','138','139',
    '140','141','142','143','144','145','146','147','148','149',
    '150','151','152','153','154','155','156','157','158','159',
    '160']
    Height_AVG = []
    Height_AVG_Count = []
    time = 0
    # 每 n 筆計算平均，共要計算 time 次
    while time < (100000/i)-1:
        k = 0
        total = 0
        # index 從 0 到 i
        while k < i:
            index = (i * time) + k
            total = total + Height_Random[index]
            k = k + 1
        Height_AVG.append((int)(total / i))
        time = time + 1
    
    # 計算每個平均出現的次數
    height = 130;
    while height < 161:
        Height_AVG_Count.append(Height_AVG.count(height))
        height = height + 1

    plt.gcf().set_size_inches(25, 5)
    plt.bar(x,Height_AVG_Count, 0.4, color='r', alpha = 0.8)
    plt.title('N = ')
    plt.xlabel('Height(cm)')
    plt.ylabel('Num(people)')
    
    plt.show()
    