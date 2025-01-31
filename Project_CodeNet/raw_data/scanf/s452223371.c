#include<stdio.h>


char ssss[1000];


int main(){

	int cnt;

	int i,j,m;

	long long n,q,w,e,r,t,y;

	
	long long s[17]={0,283,3638,42033,474028,5274023,

	58074018,634074013,6874074008,74074074003,794074073998,

	8474074073993,90074074073988,954074074073983,

	10074074074073978,106074074074073973,1114074074074073968};
	

	long long ss[16]={48,56,64,72,80,88,96,104,

					112,120,128,136,144,152,160,168};
	long long sss[16]={1,91,991,9991,99991,999991,9999991,
	99999991,999999991,9999999991,99999999991,
	999999999991,9999999999991,99999999999991,999999999999991,
	9999999999999991};



	scanf("%lld",&n);



	for(i = 0;i < 16;i++)if(s[i] > n)break;

	i--;


	q = n-s[i];

	w = (q+5)/ss[i];

	q = (q+5)%ss[i];
	if(!w)q -= 5;

	



	e = sss[i]+w*15;
printf("e:%lld q:%lld w:%lld\n",e,q,w);
	sprintf(ssss,
	"%lld%lldFizz%lldBuzzFizz%lld%lldFizzBuzz%lldFizz%lld%lldFizzBuzz%lld%lldFizz%lldBuzzFizz%lld%lldFizzBuzz%lldFizz%lld%lldFizzBuzz",
	e,e+1,e+3,e+6,e+7,e+10,e+12,e+13,e+15,e+16,e+18,e+21,e+22,e+25,e+27,e+28);
//printf("%s\n\n",ssss);
//printf("e:%d q:%d w:%lld\n",e,q,w);
//printf("w:%lld\n",w);
	for(j = 0;j<20;j++)printf("%c",ssss[j+q-1]);
	puts("");
	
	return 0;
}