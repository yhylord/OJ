271 - Codeforces Round #166 (Div. 2)

A. Beautiful Year

����Ŀ���⡿

�������y(1000 <= y <= 9000)�������y����С����λ���ָ�����ͬ����ݡ�

���㷨������

ö�٣�ʱ�临�Ӷ�O(Y)��

B. Prime Matrix

����Ŀ���⡿

��һ��N * M(1 <= N, M <= 500)�ľ���ÿ��������������10^5����ÿһ�����ԶԾ�����ĳ������1�������ٵĲ���ʹ�þ�����������һ�л�һ�ж���������

���㷨������

��Ԥ����10^5���ڵ�ÿ�������������Ҫ�Ӽ������������ɸ���Ĺ�������ɡ�ö��ȫ�ص���һ��/�У��ֱ�����ȡ��С�ļ��ɣ�ʱ�临�Ӷ�O(NM)��

C. Secret

����Ŀ���⡿

������1 ~ N�ֳ�K�����ཻ����(2 <= K <= N <= 10^6)��ʹ��ÿ�����ϲ����ɵȲ����У������ٴ��ڵ���3����һ�ֿ��з�����

���㷨������

���ȣ�N < 3 * KΪ�޽������Ȼ�������ų�1 1 2 2 3 3 ... K K 1 2 3 ... K�����б�Ȼ�����ڵȲ����У�ʣ�µ�N - 3 * K�����������ˣ�ʱ�临�Ӷ�O(N)��

D. Good Substrings

����Ŀ���⡿

����26��Сд��ĸ����Щ�Ǻõģ���Щ�ǻ��ģ�������ĳ���ΪN���ַ���(1 <= N <= 1500)�ж��ٸ���������ĸ������K���Ĳ�ͬ�Ӵ���

���㷨������

�㷨һ��ö���Ӵ���㣬���β���һ��Trie�У��Ӷ������ظ����⡣������ͳ�ƻ���ĸ�������ɣ�ʱ�临�Ӷ�O(N^2)��

�㷨����ʹ�ñ����㷨ʵ�ֺ�׺���飬����׺��С˳�����μ��㣬ÿ�μ���max(��sa(i)Ϊ��㻵��ĸ������K��������쳤��L - height(i), 0)������L����ʹ�ö���ʵ�֣�ʱ�临�Ӷ�O(NlogN)��

�㷨����˼·ͬ�ϣ���ʹ��DC3�㷨ʵ�ֺ�׺���飬ͬʱ��������ָ���ƶ���ɨ�跽�����L��Ԥ������ʱ�临�Ӷ�O(N)��

E. Three Horses

����Ŀ���⡿

����N(1 <= N <= 10^5)������a_1, ..., a_N(1 <= a_i <= 10^9)��M(2 <= M <= 10^9)���������(x, y)(1 <= x < y <= M)�ĸ�����ʹ�ó�ʼ����(x, y)����һϵ�в������ڹ����еõ����������԰���(1, a_i)������(a, b)��������(a + 1, b + 1)������ż����(a, b)��������(a / 2, b / 2)����������(a, b)��(b, c)��������(a, c)��

���㷨������

�������ֲ��������Ƿ��֣�������һϵ�в���ȫ�ǳ����Ǳ�Ȼ���Եġ���ô��������y - x = d�������ֲ�������ʹ�������Ĳ��Ϊԭ����k���������֮ǰ��Ȼ�����(2^t, 2^t + kd)��

����k���⣬��ش���k = 2^t * p����ô�Ϳ��Ա�ʾΪ(2^t, 2^t(1 + pd))�������õ�(1, 1 + pd)����ˣ����d������a_i - 1�Ĺ�Լ������Ȼ�ǺϷ��ġ�

��ͬʱ���ǵ������ڳ����Ĵ��ڣ�����d' = d * 2^r����Ȼ���Եõ�d���������ǵ������ǣ����gcd(a_i)�����������ӣ��������ǵ�2^r����Ӧ�Ľ�ĸ���������𰸣�ʱ�临�Ӷ�O(NlogN)��