#include <iostream>
#include <cmath>
using namespace std;

// Node 結構用於鏈結串列
struct Node {
    int coef;   // 係數
    int exp;    // 指數
    Node* link; // 指向下一個節點的指針
};

// Polynomial 類別定義
class Polynomial {
private:
    Node* header; // header，標識鏈結串列的開始

    // 輔助函數：按指數降序添加項
    void addTerm(int c, int e) {
        Node* newNode = new Node{c, e, nullptr};
        if (!header->link || header->link == header || e > header->link->exp) {
            newNode->link = header->link;
            header->link = newNode;
        } else {
            Node* current = header->link;
            while (current->link != header && current->link->exp > e) {
                current = current->link;
            }
            newNode->link = current->link;
            current->link = newNode;
        }
        // 合併同類項
        Node* prev = header;
        Node* curr = header->link;
        while (curr->link != header) {
            if (curr->exp == curr->link->exp) {
                curr->coef += curr->link->coef;
                Node* temp = curr->link;
                curr->link = temp->link;
                delete temp;
            } else {
                curr = curr->link;
            }
        }
    }

    // 輔助函數：清除串列 
    void clear() {
        if (!header) return;
        Node* current = header->link;
        while (current != header) { // 遍歷並刪除所有節點
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        delete header; // 刪除標頭
        header = nullptr;
    }

public:
    // 建構函數：初始化空多項式
    Polynomial() {
        header = new Node{0, 0, nullptr};
        header->link = header; // 形成鏈結串列
    }

    // (c) 拷貝函數
    Polynomial(const Polynomial& a) {
        header = new Node{0, 0, nullptr};
        header->link = header;
        Node* current = a.header->link;
        while (current != a.header) {
            addTerm(current->coef, current->exp); // 複製每個項
            current = current->link;
        }
    }

    // (d) 賦值運算：將多項式 a 賦值給當前多項式
    const Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this; // 檢查賦值
        clear();
        header = new Node{0, 0, nullptr};
        header->link = header;
        Node* current = a.header->link;
        while (current != a.header) {
            addTerm(current->coef, current->exp); // 複製每個項
            current = current->link;
        }
        return *this;
    }

    // (e) 解構函數：釋放所有節點
    ~Polynomial() {
        clear();
    }

    // (a) 輸入運算：從輸入讀取多項式並轉為鏈結串列
    friend istream& operator>>(istream& is, Polynomial& x) {
        x.clear();
        x.header = new Node{0, 0, nullptr};
        x.header->link = x.header;
        int n;
        is >> n; // 讀項數
        for (int i = 0; i < n; i++) {
            int c, e;
            is >> c >> e; // 讀係數和指數
            x.addTerm(c, e);
        }
        return is;
    }

    // (b) 輸出運算：將串列轉為輸出格式並輸出
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        Node* current = x.header->link;
        int count = 0;
        bool first = true;
        while (current != x.header) {
            if (current->coef == 0) {
                current = current->link;
                continue;
            }
            if (!first) os << " + ";
            if (current->exp == 0) {
                os << current->coef; // 指數為 0 時僅顯示係數
            } else {
                os << current->coef << "x^" << current->exp;
            }
            first = false;
            current = current->link;
            count++;
        }
        if (count == 0) os << "0";
        return os;
    }

    // (f) 加法運算：返回當前多項式與 b 的和
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Node* aCurrent = header->link;
        Node* bCurrent = b.header->link;

        while (aCurrent != header || bCurrent != b.header) {
            int aExp = (aCurrent == header) ? -1 : aCurrent->exp;
            int bExp = (bCurrent == b.header) ? -1 : bCurrent->exp;
            int coef = 0;

            if (aExp > bExp) {
                coef = aCurrent->coef;
                aCurrent = aCurrent->link;
            } else if (bExp > aExp) {
                coef = bCurrent->coef;
                bCurrent = bCurrent->link;
            } else if (aExp != -1) {
                coef = aCurrent->coef + bCurrent->coef;
                aCurrent = aCurrent->link;
                bCurrent = bCurrent->link;
            }

            if (coef != 0) result.addTerm(coef, aExp != -1 ? aExp : bExp);
        }
        return result;
    }

    // (g) 減法運算：返回當前多項式與 b 的差
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        Node* aCurrent = header->link;
        Node* bCurrent = b.header->link;

        while (aCurrent != header || bCurrent != b.header) {
            int aExp = (aCurrent == header) ? -1 : aCurrent->exp;
            int bExp = (bCurrent == b.header) ? -1 : bCurrent->exp;
            int coef = 0;

            if (aExp > bExp) {
                coef = aCurrent->coef;
                aCurrent = aCurrent->link;
            } else if (bExp > aExp) {
                coef = -bCurrent->coef;
                bCurrent = bCurrent->link;
            } else if (aExp != -1) {
                coef = aCurrent->coef - bCurrent->coef;
                aCurrent = aCurrent->link;
                bCurrent = bCurrent->link;
            }

            if (coef != 0) result.addTerm(coef, aExp != -1 ? aExp : bExp);
        }
        return result;
    }

    // (h) 乘法運算：返回當前多項式與 b 的乘積
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        Node* aCurrent = header->link;
        while (aCurrent != header) {
            Polynomial temp;
            Node* bCurrent = b.header->link;
            while (bCurrent != b.header) {
                int newCoef = aCurrent->coef * bCurrent->coef; // 計算新係數
                int newExp = aCurrent->exp + bCurrent->exp;    // 計算新指數
                temp.addTerm(newCoef, newExp);
                bCurrent = bCurrent->link;
            }
            result = result + temp;
            aCurrent = aCurrent->link;
        }
        return result;
    }

    // (i) 求值函數：計算多項式代入x=某值的結果 
    float Evaluate(float x) const {
        float result = 0;
        Node* current = header->link;
        while (current != header) {
            result += current->coef * pow(x, current->exp); // 按項計算總和
            current = current->link;
        }
        return result;
    }
};
int main() {
    Polynomial p1, p2;
    cout << "請輸入 p1 的項數：";
    cin >> p1;
    cout << "請輸入 p2 的項數：";
    cin >> p2;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p1 + p2 = " << (p1 + p2) << endl;
    cout << "p1 - p2 = " << (p1 - p2) << endl;
    cout << "p1 * p2 = " << (p1 * p2) << endl;
    cout << "p1(2.0) = " << p1.Evaluate(2.0) << endl;

    return 0;
}
