### 
1. 程式碼裡面有使用亂數，故編譯的時候需要多加上 -std=c++11
2. 程式碼一開始有define幾個變數，可以透過直接更改這些變數所代表的數值，來調整神經元個數及所使用的屬性個數。
#define trainingMAXN 1005
#define testMAXN 45
#define useProperty 3
#define useNeurons 4

