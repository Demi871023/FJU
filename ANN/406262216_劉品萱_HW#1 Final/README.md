1. 程式作業共 6 小題，共分成 6 個 source code file，檔名的部分因為編譯執行有問題，所以我把題號的括號()拿掉了。
2. 因為 source code 中有使用亂數產生 initial weight 和 initial bias，因此編譯的時候指令要多打 -std=c++11。Example： ```g++ a_Two-neuron_1.cpp -o a_Two-neuron_1.exe -std=c++11```
3. 執行的時候直接輸入 ``` a_Two-neuron_1.exe``` 即可
4. Dataset 1 是直接將訓練資料以及測試資料寫進 code 中，而 Dataset 2 則是將 training_data.txt 以及 testint_data.txt 利用 freopen 讀入。
5. 最後 testing data 測試後輸出類別時，有的測資的測試結果會輸出 ? ，代表訓練出來的 perceptron network 無法使得他分類於某個類別。
6. 為配合報告中的第三點，比較各個 learning rates，因此我有特別在不同 learning rate 的情況下各跑 10000 筆來評估 learning rate 對 epoch 之間的關係，其10000 筆的結果我寫出至各自的txt檔（如：LearningRate05In4Neurons 代表在 learning rate = 0.5 且神經元為 4 個的時候所寫出的 txt 檔案），並與此檔放置在相同的 406262216_劉品萱_HW#1 目錄之下，而其 source code（ANNHW_4Neurons_countAVGepoch.cpp) 及 exe（ANNHW_4Neurons_countAVGepoch.exe) 我放置在各自所屬目錄下
