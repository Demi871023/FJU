1. 因程式碼使用到亂數（Random），因此編譯時需額外加上 -std=c++11。
```
g++ ANN2.cpp -o ANN2.exe -std=c++11
```
2. 最上面有一排 #define 的變數，可透過直接更改數值來測試並比較不同參數數值下的結果
```cpp
#define EpochMax 500000             // 最大世代數
#define LearningRate 1
#define tao 0.1                     // 最大 ERMSE 數值
```
