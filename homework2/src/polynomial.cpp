#include <iostream>

using namespace std;

// �w���ŧi Polynomial ���O
class Polynomial;

// ���]Term�^���O�G�N��h���������C�@��
class Term {
    friend class Polynomial; // Polynomial ���O�i�H�s�� Term �� private ����
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);
    friend std::istream& operator>>(std::istream&, Polynomial&);

private:
    float coef; // �Y��
    int exp;    // ����
};

// �h�����]Polynomial�^���O
class Polynomial {
public:
    // �غc�l�A��l�Ʈe�q�P����
    Polynomial(int cap = 10) {
        capacity = cap;
        termArray = new Term[capacity];
        terms = 0;
    }

    // �ƻs�غc�l
    Polynomial(const Polynomial& other) {
        terms = other.terms;
        capacity = other.capacity;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i)
            termArray[i] = other.termArray[i];
    }

    // �����B��l�h��
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

    // �Ѻc�l
    ~Polynomial() {
        delete[] termArray;
    }

    // �h�����ۥ[
    Polynomial Add(const Polynomial& poly) {
        Polynomial result;
        int i = 0, j = 0;

        // �X�֨�Ӧh����������
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

        // �N�ѤU�����[�i��
        for (; i < terms; ++i)
            result.NewTerm(termArray[i].coef, termArray[i].exp);
        for (; j < poly.terms; ++j)
            result.NewTerm(poly.termArray[j].coef, poly.termArray[j].exp);

        return result;
    }

    // �h�����ۭ�
    Polynomial Mult(const Polynomial& poly) {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            Polynomial temp;
            for (int j = 0; j < poly.terms; ++j) {
                float newCoef = termArray[i].coef * poly.termArray[j].coef;
                int newExp = termArray[i].exp + poly.termArray[j].exp;
                temp.NewTerm(newCoef, newExp);
            }
            result = result.Add(temp); // �⭼�n�[�i���G��
        }
        return result;
    }

    // �p��h�����b x=f �ɪ���
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

    // �h������J
    friend istream& operator>>(istream& in, Polynomial& p) {
        int n;
        cout << "�п�J�h���������ơG";
        in >> n;

        // ���s�t�m termArray
        delete[] p.termArray;
        p.terms = 0;
        p.capacity = n;
        p.termArray = new Term[p.capacity];

        cout << "�Ш̧ǿ�J�C�@�����Y�ƻP����]�榡�G�Y�� ����^�G\n";
        for (int i = 0; i < n; i++) {
            float c;
            int e;
            in >> c >> e;
            p.NewTerm(c, e);
        }

        return in;
    }

    // �h������X
    friend ostream& operator<<(ostream& out, const Polynomial& p) {
        for (int i = 0; i < p.terms; i++) {
            out << p.termArray[i].coef << "x^" << p.termArray[i].exp;
            if (i != p.terms - 1)
                out << " + ";
        }
        return out;
    }

private:
    Term* termArray; // �x�s�h���������}�C
    int capacity;    // �e�q
    int terms;       // ��e����

    // �s�W�@���]�Y���ۦP����|�X�֡^
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
    cout << "��J�Ĥ@�Ӧh����:\n";
    cin >> p1;
    cout << "��J�ĤG�Ӧh����:\n";
    cin >> p2;

    Polynomial sum = p1.Add(p2);  // �ۥ[���G
    Polynomial prod = p1.Mult(p2); // �ۭ����G

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "�ۥ[���G: " << sum << endl;
    cout << "�ۭ����G: " << prod << endl;

    float x;
    cout << "�п�J x ���ȡA�Ψӭp�� p1(x): ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}

