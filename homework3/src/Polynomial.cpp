#include <iostream>
#include <cmath>
using namespace std;

// Node ���c�Ω��쵲��C
struct Node {
    int coef;   // �Y��
    int exp;    // ����
    Node* link; // ���V�U�@�Ӹ`�I�����w
};

// Polynomial ���O�w�q
class Polynomial {
private:
    Node* header; // header�A�����쵲��C���}�l

    // ���U��ơG�����ƭ��ǲK�[��
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
        // �X�֦P����
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

    // ���U��ơG�M����C 
    void clear() {
        if (!header) return;
        Node* current = header->link;
        while (current != header) { // �M���çR���Ҧ��`�I
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        delete header; // �R�����Y
        header = nullptr;
    }

public:
    // �غc��ơG��l�ƪŦh����
    Polynomial() {
        header = new Node{0, 0, nullptr};
        header->link = header; // �Φ��쵲��C
    }

    // (c) �������
    Polynomial(const Polynomial& a) {
        header = new Node{0, 0, nullptr};
        header->link = header;
        Node* current = a.header->link;
        while (current != a.header) {
            addTerm(current->coef, current->exp); // �ƻs�C�Ӷ�
            current = current->link;
        }
    }

    // (d) ��ȹB��G�N�h���� a ��ȵ���e�h����
    const Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this; // �ˬd���
        clear();
        header = new Node{0, 0, nullptr};
        header->link = header;
        Node* current = a.header->link;
        while (current != a.header) {
            addTerm(current->coef, current->exp); // �ƻs�C�Ӷ�
            current = current->link;
        }
        return *this;
    }

    // (e) �Ѻc��ơG����Ҧ��`�I
    ~Polynomial() {
        clear();
    }

    // (a) ��J�B��G�q��JŪ���h�������ର�쵲��C
    friend istream& operator>>(istream& is, Polynomial& x) {
        x.clear();
        x.header = new Node{0, 0, nullptr};
        x.header->link = x.header;
        int n;
        is >> n; // Ū����
        for (int i = 0; i < n; i++) {
            int c, e;
            is >> c >> e; // Ū�Y�ƩM����
            x.addTerm(c, e);
        }
        return is;
    }

    // (b) ��X�B��G�N��C�ର��X�榡�ÿ�X
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
                os << current->coef; // ���Ƭ� 0 �ɶ���ܫY��
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

    // (f) �[�k�B��G��^��e�h�����P b ���M
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

    // (g) ��k�B��G��^��e�h�����P b ���t
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

    // (h) ���k�B��G��^��e�h�����P b �����n
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        Node* aCurrent = header->link;
        while (aCurrent != header) {
            Polynomial temp;
            Node* bCurrent = b.header->link;
            while (bCurrent != b.header) {
                int newCoef = aCurrent->coef * bCurrent->coef; // �p��s�Y��
                int newExp = aCurrent->exp + bCurrent->exp;    // �p��s����
                temp.addTerm(newCoef, newExp);
                bCurrent = bCurrent->link;
            }
            result = result + temp;
            aCurrent = aCurrent->link;
        }
        return result;
    }

    // (i) �D�Ȩ�ơG�p��h�����N�Jx=�Y�Ȫ����G 
    float Evaluate(float x) const {
        float result = 0;
        Node* current = header->link;
        while (current != header) {
            result += current->coef * pow(x, current->exp); // �����p���`�M
            current = current->link;
        }
        return result;
    }
};
int main() {
    Polynomial p1, p2;
    cout << "�п�J p1 �����ơG";
    cin >> p1;
    cout << "�п�J p2 �����ơG";
    cin >> p2;

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;
    cout << "p1 + p2 = " << (p1 + p2) << endl;
    cout << "p1 - p2 = " << (p1 - p2) << endl;
    cout << "p1 * p2 = " << (p1 * p2) << endl;
    cout << "p1(2.0) = " << p1.Evaluate(2.0) << endl;

    return 0;
}
