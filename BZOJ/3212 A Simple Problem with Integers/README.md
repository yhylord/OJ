BZOJ 3212 A Simple Problem with Integers

����Ҫ��һ���������ĳ��ֵ����Ҫ��ѯĳ������ĺ͡�

��Ȼ���޸ĺͲ�ѯ������[x, y]������ת��Ϊ[1, x - 1]��[1, y]��

��ô�����ǰ��޸�[1, x']���Ϊx'���ӵ���Ϊd��ѯ��[1, x]���Ϊx��

����ά��������״���飬�ֱ����������������

��x' <= xʱ��x'��x�Ĺ���ֵΪx' * d���������״����ά������x��sigma{x' * d}��

��x' > xʱ��x'��x�Ĺ���ֵΪx * d���������״����ά������x��sigma{d}��

ά����ʱ�����м���һ��Ӱ��ķ�Χ�Ϳ����ˡ�

ʱ�临�Ӷ�O(N + QlogN)��