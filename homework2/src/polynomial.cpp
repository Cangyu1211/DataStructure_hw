#include <iostream>

using namespace std;

// 預先宣告 Polynomial 類別
class Polynomial;

// 項（Term）類別：代表多項式中的每一項
class Term {
    friend class Polynomial; // Polynomial 類別可以存取 Term 的 private 成員
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
    friend std::istream& operator>>(std::istream&, Polynomial&);

private:
    float coef; // 係數
    int exp;    // 次方
};

// 多項式（Polynomial）類別
class Polynomial {
public:
    // 建構子，初始化容量與項數
    Polynomial(int cap = 10) {
        capacity = cap;
        termArray = new Term[capacity];
        terms = 0;
    }

    // 複製建構子
    Polynomial(const Polynomial& other) {
        terms = other.terms;
        capacity = other.capacity;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i)
            termArray[i] = other.termArray[i];
    }

    // 指派運算子多載
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            delete[] termArray;
            terms = other.terms;
            capacity = other.capacity;
            termArray = new Term[capacity];
            for (int i = 0; i < terms; ++i)
                termArray[i] = other.termArray[i];
        }
        return *this;
    }

    // 解構子
    ~Polynomial() {
        delete[] termArray;
    }

    // 多項式相加
    Polynomial Add(const Polynomial& poly) {
        Polynomial result;
        int i = 0, j = 0;

        // 合併兩個多項式中的項
        while (i < terms && j < poly.terms) {
            if (termArray[i].exp == poly.termArray[j].exp) {
                float sum = termArray[i].coef + poly.termArray[j].coef;
                if (sum != 0)
                    result.NewTerm(sum, termArray[i].exp);
                i++;
                j++;
            }
            else if (termArray[i].exp > poly.termArray[j].exp) {
                result.NewTerm(termArray[i].coef, termArray[i].exp);
                i++;
            }
            else {
                result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);
                j++;
            }
        }

        // 將剩下的項加進來
        for (; i < terms; ++i)
            result.NewTerm(termArray[i].coef, termArray[i].exp);
        for (; j < poly.terms; ++j)
            result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);

        return result;
    }

    // 多項式相乘
    Polynomial Mult(const Polynomial& poly) {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            Polynomial temp;
            for (int j = 0; j < poly.terms; ++j) {
                float newCoef = termArray[i].coef * poly.termArray[j].coef;
                int newExp = termArray[i].exp + poly.termArray[j].exp;
                temp.NewTerm(newCoef, newExp);
            }
            result = result.Add(temp); // 把乘積加進結果中
        }
        return result;
    }

    // 計算多項式在 x=f 時的值
    float Eval(float f) {
        float sum = 0;
        for (int i = 0; i < terms; i++) {
            float termValue = termArray[i].coef;
            for (int j = 0; j < termArray[i].exp; j++) {
                termValue *= f;
            }
            sum += termValue;
        }
        return sum;
    }

    // 多項式輸入
    friend istream& operator>>(istream& in, Polynomial& p) {
        int n;
        cout << "請輸入多項式的項數：";
        in >> n;

        // 重新配置 termArray
        delete[] p.termArray;
        p.terms = 0;
        p.capacity = n;
        p.termArray = new Term[p.capacity];

        cout << "請依序輸入每一項的係數與次方（格式：係數 次方）：\n";
        for (int i = 0; i < n; i++) {
            float c;
            int e;
            in >> c >> e;
            p.NewTerm(c, e);
        }

        return in;
    }

    // 多項式輸出
    friend ostream& operator<<(ostream& out, const Polynomial& p) {
        for (int i = 0; i < p.terms; i++) {
            out << p.termArray[i].coef << "x^" << p.termArray[i].exp;
            if (i != p.terms - 1)
                out << " + ";
        }
        return out;
    }

private:
    Term* termArray; // 儲存多項式項的陣列
    int capacity;    // 容量
    int terms;       // 當前項數

    // 新增一項（若有相同次方會合併）
    void NewTerm(float c, int e) {
        for (int i = 0; i < terms; i++) {
            if (termArray[i].exp == e) {
                termArray[i].coef += c;
                return;
            }
        }
        if (terms == capacity) {
            capacity *= 2;
            Term* newArray = new Term[capacity];
            for (int i = 0; i < terms; i++)
                newArray[i] = termArray[i];
            delete[] termArray;
            termArray = newArray;
        }
        termArray[terms].coef = c;
        termArray[terms].exp = e;
        terms++;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "輸入第一個多項式:\n";
    cin >> p1;
    cout << "輸入第二個多項式:\n";
    cin >> p2;

    Polynomial sum = p1.Add(p2);  // 相加結果
    Polynomial prod = p1.Mult(p2); // 相乘結果

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "相加結果: " << sum << endl;
    cout << "相乘結果: " << prod << endl;

    float x;
    cout << "請輸入 x 的值，用來計算 p1(x): ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}

