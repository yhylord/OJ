POJ 1038 Bugs Integrated, Inc.

����Ŀ���⡿

����һ��N * M(1 <= N <= 150, 1 <= M <= 10)�����̣�Ҫ���������2 * 3�Ĺ��ƣ��Ҹ���K(0 <= K <= N * M)���޷����õĸ��ӣ�������ܷ��ö��ٸ���

���㷨������

������f[i][j]��ʾǰi - 2�и���������i - 1�к͵�i��״̬Ϊj��0��ʾ�����գ�1��ʾ��i - 1��������i�����գ�2��ʾ������������ܷż�����

��ô�����ǿ�����DFS������кϷ���ת�ƹ�ϵ������ĳһ�������ְڷź��������շ�ʽ��ע��ϸ�ڼ��ɡ�

�޷��ڷŵ�λ�ÿ������ȴ���һ�£�ʱ�临�Ӷ�O(NM + K + N * 3^M)��