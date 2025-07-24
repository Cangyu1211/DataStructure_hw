#include <iostream>
// ���J�Ҩ��-���j��k
int ackermann(int m, int n) {
    // �Ĥ@�ر��p�A�p�G m = 0�A�^�� n + 1
    if (m == 0) return n + 1;
    // �ĤG�ر��p�A�p�G n = 0�A���j�I�s ackermann(m - 1, 1)
    else if (n == 0) return ackermann(m - 1, 1);
    // ��L���p�A���p�� ackermann(m, n - 1)�A
    // �A�Υ������G�I�s ackermann(m - 1, ...) ����i�}����o�X���� 
    else return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    int m, n;

    //��J m ����
    std::cout << "��Jm����:";
    std::cin >> m;

    //��J n ����
    std::cout << "��Jn����:";
    std::cin >> n;

    //���J�Ҩ�ƻ��j��k ���G��X
    std::cout << "A(" << m << "," << n << "): " << ackermann(m, n) << std::endl;

    return 0;
}

