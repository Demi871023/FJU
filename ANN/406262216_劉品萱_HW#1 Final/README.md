1. 程式作業共 6 小題，共分成 6 個 source code file，檔名的部分因為編譯執行有問題，所以我把題號的括號()拿掉了。
2. 因為 source code 中有使用亂數產生 initial weight 和 initial bias，因此編譯的時候指令要多打 -std=c++11。Example： ```g++ a_Two-neuron_1.cpp -o a_Two-neuron_1.exe -std=c++11```
3. 執行的時候直接輸入 ``` a_Two-neuron_1.exe``` 即可
4. Dataset 1 是直接將訓練資料以及測試資料寫進 code 中，而 Dataset 2 則是將 training_data.txt 以及 testint_data.txt 利用 freopen 讀入。
