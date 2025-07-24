#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// 第二題 遞迴列出字串 S 的所有子集（powerset）
// S: 原始字串，有使用 & 可節省記憶體避免複製整串字串
// index: 目前正在考慮要不要加進子集的字元
// current: 目前已選擇的子集字串
// counter: 計數目前是第幾個子集
// total: 所有子集總數（2^n）
void powerset(const string& S, int index, string current, long long& counter, long long total) {
    // 當 index 等於字串長度，代表已考慮完所有字元
    if (index == S.length()) {
        // 如果 current 為空，表示是空集合
        if (current.empty()) {
            cout << "()";
        } else {
            // 將 current 格式化為集合形式 (a,b,...)
            cout << "(";
            for (size_t i = 0; i < current.length(); ++i) {
                cout << current[i];
                if (i < current.length() - 1) {
                    cout << ",";
                }
            }
            cout << ")";
        }

        // 如果不是最後一個子集，則印出逗號分隔
        if (counter < total - 1) {
            cout << ",";
        }
        counter++;
        return;
    }
	
    // 分支 1：不選擇 S[index]，直接往下一字元遞迴
    powerset(S, index + 1, current, counter, total);
    
    // 分支 2：選擇 S[index]，將該字元加入 current，再遞迴
    powerset(S, index + 1, current + S[index], counter, total);

}

int main() {
    string s;
    cout << "請輸入一個字串 S：";
    cin >> s;

    // 預先計算子集總數（2^n）
    long long total = 1LL << s.length();
    long long counter = 0;

    // 輸出 powerset 標頭
    cout << "powerset(" << s << ")={";

    // 呼叫 powerset 產生並印出所有子集
    powerset(s, 0, "", counter, total);

    // 輸出最後的右大括號
    cout << "}" << endl;

    return 0;
}

