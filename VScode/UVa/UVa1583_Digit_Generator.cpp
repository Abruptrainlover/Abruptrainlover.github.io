#include<stdio.h>
#include<string.h>
#define M 100005
int ans[M];
int main(void){
    int T,n;
    memset(ans,0,sizeof(int));
    for(int i=1;i<M;i++){
        int x=i,y=i;
        while(x>0)  {y+=x%10;x/=10;}
        if(ans[y]==0) ans[y]=i;
    }
    scanf("%d",&T);
    while (T--)
    {
        scanf("%d",&n);
        printf("%d\n",ans[n]);
    }
    return 0;

}

//�����ķ�ʽ������n��mλ������������Ԫ�����ǰ�����9mλ�ã�������ǰ���㣬�ڸ�����ѯ����С��ʱ�������
// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>
// #include <time.h>

// int main()
// {
// 	int n, x, y, m=0, sum, got;
// 	scanf("%d", &n);
// 	y = n;
// 	while(y>0) // ���y��λ��m
// 	{
// 		y /= 10;
// 		m++;
// 	}
	
// 	got = 0; // �Ƿ�õ���
// 	if(n-9*m<=0) x=1;// ����n-9*m��ֵ�����
// 	else x=n-9*m;
// 	for(; x<n; x++)
// 	{
// 		sum = 0;
// 		int temp = x;
// 		while(temp>0) // �õ�x������λ֮��sum
// 		{
// 			sum += temp%10;
// 			temp /= 10;
// 		}
// 		if(x+sum==n){
// 			got = 1;
// 			break;
// 		}
// 	}
// 	if(got==0) printf("%d\n", 0);
// 	else printf("%d\n", x);
// 	return 0; // ����
// }
