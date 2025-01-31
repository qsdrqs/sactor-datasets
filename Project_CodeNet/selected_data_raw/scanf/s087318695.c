#include <stdio.h>

int main(void){
  int n;
  int min,max,sum;
  
  scanf("%d",&n);
  
  int  a[n];
  sum=0;
  
  int i;
 
  for(i=0;i<n;i++){
	  scanf("%d",&a[i]);
	  if(i==0){min=a[i]; max=a[i]; sum=a[i];}
	  else{
	  if(min>a[i]) min=a[i];
	  if(max<a[i]) max=a[i];
	  sum+=a[i];
	  }
  }
	  
  printf("%d %d %d\n",min,max,sum);
    
  return 0;
}