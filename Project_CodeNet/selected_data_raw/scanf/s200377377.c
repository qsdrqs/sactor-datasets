#include<stdio.h>
#include<stdlib.h>


int main(void){
    int N = 0;
    int z[101] ={ };
    int index=0;
    int colorFlags[9] = {};
    int min=0, max = 0,colors=0;
    colorFlags[8]=0; colorFlags[9]=0;

    scanf("%d \n", &N);
    do{
      scanf("%d ",&z[index]);
      index++;
    }while(index < N);
   // qsort( &z, N, sizeof(int), int_sort);
    index=0;
    while(index<N){
       if(0<z[index] && z[index]<=399){
          if(colorFlags[0]=0) colorFlags[0]=1;
       }
       if ((400<= z[index] && z[index] <= 799) && (colorFlags[1]==0) ) 
       {colorFlags[1]=1;}
       else if ((800<= z[index] && z[index] <= 1199) && (colorFlags[2]==0))
       {    colorFlags[2]=1;  }
       else if ((1200<= z[index] && z[index] <= 1599) && (colorFlags[3]== 0 ))
       {    colorFlags[3]=1;}
       else if ((1600 <= z[index] && z[index] < 1999) && colorFlags[4]==0) 
        {    colorFlags[4] =1;}
       else if ((2000<= z[index] && z[index] <= 2399) && colorFlags[5]==0)
        {   colorFlags[5]=1;}
       else if ((2400<= z[index] && z[index] <= 2799) && colorFlags[6]== 0 )
         {  colorFlags[6]=1;}
       else if ((2800 <= z[index] && z[index] < 3199) && colorFlags[7]==0) 
         { colorFlags[7] =1;}
       if ( 3200 <= z[index] ) colorFlags[8] +=1;
       index++;
    }
    for (index=0; index<9; index++){
       printf("%d ", colorFlags[index]);
        min += colorFlags[index];
    }
    if( colorFlags[8] + min >= 8) { max = 8; }else{ max = colorFlags[8]+min; }

printf("\n%d %d\n", min, max);
    return 0;
}