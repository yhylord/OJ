SPOJ FTOUR2

����Ŀ���⡿

����N(1 <= N <= 200000)����������������M���Ǻڽ�㣬�����������K���ڵ��·��������ȡ�

���㷨������

�������Ƕ���������е���Σ����������Ǵ�����rootΪ����������

��������ظ��´𰸣����ڸ��µ���һ�����䣬��״̬�����Ƿǳ���ġ�

��ô�����ǿ��ǰ�root�Ķ��Ӱ�·�������ڽ������Ӵ�С������b[i](0 <= i <= K)��ʾ��root�İ���������i���ڽ���·��������ȡ�

���ĳ����������ȥ·�����ڽ�����ΪR����������a[i](0 <= i <= R)��ʾ�������������ȥ·������i���ڽ�������ȡ�

��һ����������֮ǰ��b�͵�ǰ��a���´𰸣���a[i] + b[K - i](0 <= i <= R)��

�ڶ����������õ�ǰ��a������b�����Ƿ��֣����ڱ�֤��R�ĵ���������Ҫ���µ�b��Ԫ�ظ������ΪR���ٶ��Ժ�ĵ�һ���������õ������������ֻҪ����b[i](K - R <= i <= K)���ɡ�

ע����µ�ʱ����Ҫ����[0, R]��[K - R, K]�ཻ�������

�������Ӷȣ�ö��ÿ������ʱ����R��ȻС�ڵ���������ӵĴ�С����˶�a, b�ĸ��¹��̱�Ȼ��������rootΪ�����������ܽ������

��ˣ����µ��ܸ��Ӷ�ΪO(NlogN)�����⣬ÿ���������һ�������У��临�Ӷ���ΪO(NlogN)�����ϣ��㷨����ʱ�临�Ӷ�O(NlogN)��