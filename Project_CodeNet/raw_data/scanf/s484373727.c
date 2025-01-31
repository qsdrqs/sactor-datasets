#include<stdio.h>
int main()
{
      int n;
      scanf("%d",&n);
      int a[n],i,b[100001]={ };
      long long int sum=0;
      for(i=0;i<n;i++){
            scanf("%d",&a[i]);
            b[a[i]]++;
            sum+=a[i];
      }
      int q;
      scanf("%d",&q);
      for(i=1;i<=q;i++){
            int c,d;
            scanf("%d%d",&c,&d);
            sum+=(long long int)(d*b[c])-(b[c]*c);
            b[d]+=b[c];
            b[c]=0;
            printf("%lld\n",sum);
      }

      return 0;
}
