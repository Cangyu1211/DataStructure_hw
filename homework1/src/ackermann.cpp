#include <iostream>
// 阿克曼函數-遞迴算法
int ackermann(int m, int n) {
    // 第一種情況，如果 m = 0，回傳 n + 1
    if (m == 0) return n + 1;
    // 第二種情況，如果 n = 0，遞迴呼叫 ackermann(m - 1, 1)
    else if (n == 0) return ackermann(m - 1, 1);
    // 其他情況，先計算 ackermann(m, n - 1)，
    // 再用它的結果呼叫 ackermann(m - 1, ...) 持續展開直到得出答案 
    else return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    int m, n;

    //輸入 m 的值
    std::cout << "輸入m的值:";
    std::cin >> m;

    //輸入 n 的值
    std::cout << "輸入n的值:";
    std::cin >> n;

    //阿克曼函數遞迴算法 結果輸出
    std::cout << "A(" << m << "," << n << "): " << ackermann(m, n) << std::endl;

    return 0;
}

