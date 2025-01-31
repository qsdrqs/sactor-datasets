#include<stdio.h>

int main(void){

double a,b,c,d,e,f,g,h;
while(scanf("%lf %lf %lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f,&g,&h) != EOF){
if(scanf("%lf %lf %lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f,&g,&h) == EOF){
break;
}
if(c-a==0&&h-f==0){
printf("YES\n");
}
else if(d-b==0&&g-e==0){
printf("YES\n");
}
else if(c-a==0&&g-e==0){
printf("NO\n");
}
else if(d-b==0&&h-f==0){
printf("NO\n");
}
else if((d-b)/(c-a) == -(h-f)/(g-e)){
printf("YES\n");
}
else{
printf("NO\n");
}
}
return 0;
}

