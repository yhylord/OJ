SPOJ GOT

����Ŀ���⡿

����һ��N(1 <= N <= 100000)�����������M(1 <= M <= 200000)��ѯ�ʣ�ÿ��ѯ��u��v·�����Ƿ����Ȩֵc�ıߡ�

���㷨������

����ʹ�ÿɳ־û��߶��������

������T_i��ʾ�������i·���ϵ����γɵ�Ȩֵ�߶�������ô������ͨ��T_father(i)����a_i�õ����׵ã�·��u -> v�ϵ����γɵ�Ȩֵ�߶���T = T_u + T_v - T_LCA(u, v) - T_father(LCA(u, v))���ٲ�ѯ�Ƿ����Ȩֵc���ɡ�

����LCA����ʹ�ñ����㷨ʵ�֣���Ҫע����ǣ���������a_i��˳��ҲҪ����DFS������ʱ�临�Ӷ�ΪO(NlogN)��