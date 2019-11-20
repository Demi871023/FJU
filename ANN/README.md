### 
1. 程式碼裡面有使用亂數，故編譯的時候需要多加上 -std=c++11，如以下
```
g++ ANNHW_2Neurons.cpp -o ANNHW_2Neurons.exe -std=c++11
```
2. 執行時直接輸入 ANNHW_2Neurons.exe 即可。
3. 程式碼一開始有define幾個變數，可以透過直接更改這些變數所代表的數值，來調整神經元個數及所使用的屬性個數。
```cpp=
#define trainingMAXN 1005
#define testMAXN 45
#define useProperty 3
#define useNeurons 4
```
4. 但此作業為方便執行，我將題目所要求的兩個神經元及四個神經元直接分開成兩個檔案。分別為兩個神經元的cpp檔(ANNHW_2Neurons.cpp)，以及四個神經元的cpp檔(ANNHW_4Neurons.cpp)。
