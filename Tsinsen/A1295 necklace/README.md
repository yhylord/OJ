Tsinsen A1295 necklace

����Ŀ���⡿

һ������ÿһλ��������M(2 <= M <= 10)����ɫ�е�һ�֣�����һ���������˶�Ϊ���ͬ��ɫ�Ӵ��ĳ��ȡ�

��������ΪN(2 <= N <= 1000)�Ĵ�ÿһλ��ÿ����ɫ�ĸ��ʣ�����������˶ȵ�������

���㷨������

һ��ֱ�ӵĵ���״̬����f(i, j, k, l)��ʾ����iλ����ǰ��������Ϊj����ʷ��󳤶�Ϊk����ǰλΪl�ĸ��ʡ�

��ô������Ȼ��ö����һλ�Ϳ������ת�ơ�Ȼ������״̬�Ѿ�O(N^3M)�ˣ����ת�Ƶ�O(M)����ʱ�临�Ӷ�O(N^3M^2)��

Ҫ���з�Ծ������ı�״̬��ʾ��ͻ�ƿ����ڣ����ǿ��԰ѵ�ǰ����������һά��ȥ������Ϊö����һ�β�ͬλ�����

������״̬�Ѿ��������Ż���O(N^2M)�ˣ�����f(i, j, k)��ʾ����iλ����ʷ��󳤶�Ϊj����ǰλΪk�ĸ��ʡ�

��ô������Ҫʹ��O(1)��ʱ�����ת�ƣ��������뵽���ֺ��Ż���

ת�Ʒ�Ϊ���������

��һ�֣����һ�γ��� = ��ʷ��󳤶ȣ���ôf(i, j, k)Ҫ����sigma{f(i - j, p, q) * probability(i - j + 1, i, k)}(1 <= p <= j, 1 <= q <= M && q != k)����Ȼ�ǿ��Բ��ֺ͵ġ�

�ڶ��֣����һ�γ��� < ��ʷ��󳤶ȣ���ôf(i, j, k)Ҫ����sigma{f(i - p, j, q) * probability(i - p + 1, i, k)}(1 <= p < j��1 <= q <= M && q != k)����ȻҲ�ǿ��Բ��ֺ͵ģ�ȡ��һ�κ͵�ʱ�����ʹ������ȡ��һ��hash�ļ��㷽����

����probability(i, j, k)��ʾ�ӵ�iλ����jλȫ��Ϊk�ĸ��ʣ��ǿ�����O(N^2M)��ʱ����Ԥ���������ġ�

����ʱ�临�Ӷ�O(N^2M)��