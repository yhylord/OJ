SPOJ COOLNUMS

����Ŀ���⡿

�����λ���ֿ��Էֳ���������ȵļ��ϵ�һ������cool number������23450��3+4+0 = 2+5��

��[A, B](1 <= A <= B <= 4 * 10^9)���ж��ٸ�cool number��

���㷨������

���ȣ���Ŀת��Ϊ[1, N]���ж��ٸ�cool number��

ֱ�����Ļ�������Щ���ѣ����ö������λ���������ظ��ͺ��Ѵ����ˡ�

��������һ��û��ֱ�����������ʺ���λ˳���޹ص���Ŀ�����ǿ����ñ���һ��ķ�����

����N <= 4 * 10^9��Ҳ���������10λ�����ǿ���ö�����10λ�����м���0������1������2����

��ö�ٳ���������ΪS����Լ100000����ÿ����Ͽ�����һ��11����������ʾ�ġ������ð�0�ĸ����������������棬��Ϊ0��Ӱ���ж����������λDP�������޶��˳��ȣ�

Ȼ�����ǿ����ñ���������֤�����з�����Ϊ��λDP�ı߽�������

ͬʱ���Ƿ��֣��κ�һ��N���ڵ������ǿ�������100000��������һ�ֱ�ʾ�����ġ�

��ô����f[less][dep][state]��ʾ�Ƿ��Ѿ�С��N����depλ��״̬Ϊstate�����ĸ��������仯�����Ϳ����ˡ�

�賤��ΪL��ת�Ƹ��Ӷ�ΪP����Լ100����ʱ�临�Ӷ�O(LPS)��