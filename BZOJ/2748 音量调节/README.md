BZOJ 2748 ��������

f(i, j)��ʾ����i�׸��ܷ�������j��ת�Ƶ�f(i + 1, k), k = j +/- c_(i + 1), k >= 0 && k <= maxLevel��

��ʼ��f(0, beginLevel) = true����Ϊf(N, k) = true������k��

ʱ�临�Ӷ�O(NmaxLevel)��
