# 51115102

## 作業一-第一題

## 解題說明

本題要求實現一個函式來計算 Ackermann 函數並輸出計算結果。

### 解題策略

1. **遞迴函式設計**：
   - 當 $m = 0$ 時，$A(m, n) = n + 1$。
   - 當 $n = 0$ 時，$A(m, n) = A(m - 1, 1)$。
   - 否則，$A(m, n) = A(m - 1, A(m, n - 1))$。
   - 使用遞迴實現上述條件。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
// 阿克曼函數-遞迴算法
int ackermann(int m, int n) {
    //第一種情況,如果 m = 0，回傳 n + 1
    if (m == 0) return n + 1;
    //第二種情況,如果 n = 0，遞迴呼叫 ackermann(m - 1, 1)
    else if (n == 0) return ackermann(m - 1, 1);
    //其他情況,先計算 ackermann(m, n - 1)，再用它的結果呼叫 ackermann(m - 1,...) 持續展開直到得出答案 
    else return ackermann(m - 1, ackermann(m, n - 1));
}
int main() {
    // 問題一 阿克曼函數遞迴算法 結果輸出
    std::cout << "A(2,3): " << ackermann(2, 3) << std::endl;
    return 0;
}
```

## 效能分析

1. **時間複雜度**：$O(A(m, n))$
2. **空間複雜度**：$O(A(m, n))$

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $(m, n)$ | 預期輸出 | 實際輸出 |
|----------|-------------------|----------|----------|
| 測試一   | $(0, 0)$          | 1        | 1        |
| 測試二   | $(1, 0)$          | 2        | 2        |
| 測試三   | $(2, 1)$          | 5        | 5        |
| 測試四   | $(2, 3)$          | 9        | 9        |
| 測試五   | $(4, 0)$          | 13        | 13        |
| 測試六   | $(4, 1)$          | 65533        | 異常 執行結果未顯示        |


### 結論

1. 程式正確實現了 Ackermann 函數的遞迴定義。
2. 測試案例驗證了程式的正確性，輸出也符合預期。
3. Ackermann 函數成長的速度相當快 在A(4,0)時還可正常顯示 到了A(4,1)因為數值過高 直接導致電腦無法計算

## 申論

### 選擇遞迴的原因

  **邏輯簡單易於理解**  
   Ackermann 函數的數學定義使用遞迴可以簡化程式設計。 
   遞迴比較容易理解程式的運作方式，透過一層一層解出來更好去看見他展開的過程。
# 51115102

作業一-第二題

## 解題說明

本題要求實現一個遞迴函式來計算字串 $S$ 的所有子集（powerset），並輸出結果。
### 解題策略

1. **遞迴函式設計**：
   - 使用遞迴函數 `powerset`，參數包括原始字串 $S$、當前索引 $index$、當前子集字串 $current$、計數器 $counter$ 及總子集數 $total$。
   - 當 $index$ 達到字串長度時，格式化並輸出當前子集，並更新計數器。
   - 對於每個索引，有兩種選擇：不選該字元（繼續遞迴下一索引）或選該字元（將字元加入 $current$ 後遞迴）。

## 程式實作

以下為主要程式碼：

```cpp
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
```

## 效能分析

1. **時間複雜度**：$O(2^n)$
2. **空間複雜度**：$O(n)$

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $S$ | 預期輸出 | 實際輸出 |
|----------|--------------|-----------------|-----------------|
| 測試一   | "ab"         | powerset(ab)={(),(b),(a),(a,b)}               | powerset(ab)={(),(b),(a),(a,b)}               |
| 測試二   | "abc"        | powerset(abc)={(),(c),(b),(b,c),(a),(a,c),(a,b),(a,b,c)}               | powerset(abc)={(),(c),(b),(b,c),(a),(a,c),(a,b),(a,b,c)}               |
| 測試三   | "abcd"       | powerset(abcd)={(),(d),(c),(c,d),(b),(b,d),(b,c),(b,c,d),(a),(a,d),(a,c),(a,c,d),(a,b),(a,b,d),(a,b,c),(a,b,c,d)}              | powerset(abcd)={(),(d),(c),(c,d),(b),(b,d),(b,c),(b,c,d),(a),(a,d),(a,c),(a,c,d),(a,b),(a,b,d),(a,b,c),(a,b,c,d)}              |



### 結論

1. 程式正確生成了輸入字串的 powerset，總數符合 $2^n$。

## 申論

### 選擇遞迴的原因

1. **易於實現且語意清晰**  
   Powerset 的生成依賴於每個字元的選擇，遞迴自然模擬決策樹的分支結構，每次遞迴代表對下一個字元的決策。
