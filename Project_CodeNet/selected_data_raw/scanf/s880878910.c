#include<stdio.h>
int mothernum, mother[100000];
int binary(int aim)
{
 int Start, End, Center;
   Start  = 0;
   End    = mothernum;

   while(Start < End){
     Center = (End + Start) / 2;
     if(mother[Center] > aim){
       End   = Center;
     } else if(mother[Center] < aim){
       Start = Center + 1;
     } else if(mother[Center] == aim){
       return 1;
     }
   }

 return 0;

}
int main()
{
 int  kidsnum, kids[50000], i, Count=0,flag;
 
 scanf("%d", &mothernum);
 for (i = 0; i < mothernum; i++) {
   scanf("%d", &mother[i]);
 }
  
 scanf("%d", &kidsnum);
 for(i = 0; i < kidsnum; i++) {
   scanf("%d", &kids[i]);
 }

 for(i = 0; i< kidsnum; i++){
   flag = binary(kids[i]);
   if(flag==1){
     Count++;
   }
 }
 
 printf("%d",Count);

 return 0;
}