#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// �ĤG�D ���j�C�X�r�� S ���Ҧ��l���]powerset�^
// S: ��l�r��A���ϥ� & �i�`�ٰO�����קK�ƻs���r��
// index: �ثe���b�Ҽ{�n���n�[�i�l�����r��
// current: �ثe�w��ܪ��l���r��
// counter: �p�ƥثe�O�ĴX�Ӥl��
// total: �Ҧ��l���`�ơ]2^n�^
void powerset(const string& S, int index, string current, long long& counter, long long total) {
    // �� index ����r����סA�N��w�Ҽ{���Ҧ��r��
    if (index == S.length()) {
        // �p�G current ���šA��ܬO�Ŷ��X
        if (current.empty()) {
            cout << "()";
        } else {
            // �N current �榡�Ƭ����X�Φ� (a,b,...)
            cout << "(";
            for (size_t i = 0; i < current.length(); ++i) {
                cout << current[i];
                if (i < current.length() - 1) {
                    cout << ",";
                }
            }
            cout << ")";
        }

        // �p�G���O�̫�@�Ӥl���A�h�L�X�r�����j
        if (counter < total - 1) {
            cout << ",";
        }
        counter++;
        return;
    }
	
    // ���� 1�G����� S[index]�A�������U�@�r�����j
    powerset(S, index + 1, current, counter, total);
    
    // ���� 2�G��� S[index]�A�N�Ӧr���[�J current�A�A���j
    powerset(S, index + 1, current + S[index], counter, total);

}

int main() {
    string s;
    cout << "�п�J�@�Ӧr�� S�G";
    cin >> s;

    // �w���p��l���`�ơ]2^n�^
    long long total = 1LL << s.length();
    long long counter = 0;

    // ��X powerset ���Y
    cout << "powerset(" << s << ")={";

    // �I�s powerset ���ͨæL�X�Ҧ��l��
    powerset(s, 0, "", counter, total);

    // ��X�̫᪺�k�j�A��
    cout << "}" << endl;

    return 0;
}

