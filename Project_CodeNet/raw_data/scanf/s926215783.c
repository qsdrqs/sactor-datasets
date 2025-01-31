#pragma region kyopuro_templates
#pragma GCC optimize("Ofast")
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include<time.h>
#include<ctype.h>
typedef long long ll;
typedef long double ld;
#define rep(i,l,r)for(ll i=(l);i<(r);i++)
#define repp(i,l,r,k)for(ll i=(l);i<(r);i+=(k))
#define rrep(i,l,r)for(ll i=(l);i>=(r);i--)
#define INF (1LL<<62)
#define MOD1 1000000007
#define MOD2 998244353
#define MAX_N (1 << 20)
#define YES printf("Yes\n")
#define NO printf("No\n")
#define PN printf("\n")
#define charsize 100005 //10^5+5
#define PI 3.141592653589793238

void swap(ll *a, ll *b){ll c;c=*b;*b=*a;*a= c;}
void cin(ll *n){ scanf("%lld",&(*n)); }
void PriAll1(ll a[], ll n){ rep(i,0,n){ printf("%lld",a[i]); if(i!=n-1) printf(" "); }PN; }
ll max2(ll a,ll b){return a>=b?a:b;}
ll min2(ll a,ll b){return a>=b?b:a;}
ll min3(ll a, ll b, ll c){return (a<=b && a<=c) ? a : b<=c ? b : c;}
ll max3(ll a, ll b, ll c){return (a>=b && a>=c) ? a : b>=c ? b : c;}
ll minn(ll n, ll a[]){ll b=INF;rep(i,0,n) b=min2(b,a[i]);return b;}
ll maxn(ll n, ll a[]){ll b=-INF;rep(i,0,n) b=max2(b,a[i]);return b;}
ll POW(ll a, ll b){ll c=1;rep(i,0,b) c*=a;return c;}
double POW_d(double a, double b){double c=1;rep(i,0,b) c*=a;return c;}
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a/gcd(a,b)*b;}
ll mod_MOD1(ll n){n+= n<0?((-n)/MOD1+1)*MOD1:0; return n%=MOD1;}
ll mod_p(ll n ,ll p){n+= n<0?((-n)/p+1)*p:0; return n%=p;}
ll change_into_num(char s[] , ll len, ll p){ return !p ? 0 : POW(10,p-1)*(s[len-p]-'0') + change_into_num(s,len,p-1); }
ll digits(ll a, ll b){return a/b?1+digits(a/b,b):1;}
ll base(ll n, ll a, ll i){return i==1?n%a:base(n/a,a,i-1);}
ll is_inArr1(ll x, ll n){ return ( x<0 || x>=n ) ? 0 : 1 ; }
ll is_inArr2(ll y, ll x, ll h, ll w){ return ( y<0 || y>=h || x<0 || x>=w ) ? 0 : 1 ; }


void lr_lower( int *l, int *r, ll am, ll val , int type ){ (type<3) ? ( am < val ?  ( *l = (*l+*r)/2 ) : ( *r= (*l+*r)/2 ) ) : ( am <= val ? ( *l = (*l+*r)/2 ) : ( *r= (*l+*r)/2 ) ); }
void lr_upper( int *l, int *r, ll am, ll val , int type ){ (type<3) ? ( am <= val ?  ( *l = (*l+*r)/2 ) : ( *r= (*l+*r)/2 ) ) : ( am < val ? ( *l = (*l+*r)/2 ) : ( *r= (*l+*r)/2 ) ); }
int cmp_lower( ll a, ll b, int type ){ return (type==1) ? ( a==b ? 1 : 0 ) : (type==2) ? ( a>=b ? 1 : 0 ) : ( a>b ? 1 : 0 ) ; }
int cmp_upper( ll a, ll b, int type ){ return (type==1) ? ( a==b ? 1 : 0 ) : (type==2) ? ( a<=b ? 1 : 0 ) : ( a<b ? 1 : 0 ) ; }
// return smallest p  which meets  a[p]==val :1  >=:2   >:3
ll lower_bound( ll a[], int l, int r, ll val , int type ){  while(r-l>1) lr_lower(&l,&r,a[ (l+r)/2 ],val,type);  return cmp_lower(a[l],val,type) ? l : cmp_lower(a[r],val,type) ? r : -1;  }
// return biggest p  which meets   a[p]==val :1  <=:2   <:3
ll upper_bound( ll a[], int l, int r, ll val , int type ){  while(r-l>1) lr_upper(&l,&r,a[ (l+r)/2 ],val,type); return cmp_upper(a[r],val,type) ? r : cmp_upper(a[l],val,type) ? l : -1; }
// count i  which meets ai==x
ll count(ll a[], int l, int r, ll x){  int p = lower_bound(a,l,r,x,1);  return p==-1 ? 0 : upper_bound(a,p,r,x,1)-p+1; }

ll *factors[2] , fac_cnt=0 , is_factor_prepared=0;
ll factor_pre(){  rep(i,0,1){ if(is_factor_prepared++) return 0; }  ll tmp=(1e6)/2+1, fac_tmp[tmp];  rep(i,0,tmp){fac_tmp[i]=i?2*i+1:2;}  rep(i,1,tmp){if(fac_tmp[i]){  repp(j,3,tmp/(2*i+1)+1,2 ){  if( j*(2*i+1)<tmp ) fac_tmp[ (j*(2*i+1)-1)/2 ]=0;  }  }else continue;}  rep(i,0,tmp){if(fac_tmp[i]){  rep(j,0,2){ factors[j] = realloc( factors[j] , sizeof(ll)*( fac_cnt +1 ) );  factors[j][j?fac_cnt++:fac_cnt]=j?0:fac_tmp[i];  }  } }  return 0;  }
ll factor(ll n, ll new_common_plus){ factor_pre();  rep(i,0,fac_cnt){ ll cnt=0; rep(j,0,1){ while( ( cnt+= n %factors[0][i]==0 ? 1 : 0 )  && (n/=factors[0][i]) %factors[0][i]==0 ) continue; } factors[1][i]= new_common_plus==1 ? cnt :  new_common_plus==2 ? max2(factors[1][i],cnt) : factors[1][i]+cnt ;  if( factors[0][i]> n ) break; } return n; }
ll judge_prime(ll n){ factor_pre(); rep(i,0,fac_cnt){ if(n<factors[0][i]*factors[0][i] || n==factors[0][i]) break; else if(n%factors[0][i]==0) n/=n; }  return n==1?0:1; }

ll *mf_arr,*inv_arr,*finv_arr,is_minv_made=0,is_mf_made=0,num_of_inv=2*1e6+10;
ll makeinv(ll n , ll mod){  rep(i,0,1){if(is_minv_made++) return 0;}  inv_arr = realloc(inv_arr, sizeof(ll)*2 );  finv_arr = realloc(finv_arr, sizeof(ll)*2 );  inv_arr[1]=1;finv_arr[0]=finv_arr[1]=1;  rep(i,2,n+1){  inv_arr = realloc(inv_arr, sizeof(ll)*(i+1) );  finv_arr = realloc(finv_arr, sizeof(ll)*(i+1) );  inv_arr[i]= mod - inv_arr[mod%i] * (mod / i) % mod;  finv_arr[i] = finv_arr[i - 1] * inv_arr[i] % mod;  }  return 0; }
ll make_mf(ll n, ll mod){  rep(i,0,1){ if(is_mf_made++) return 0; }  mf_arr = realloc(mf_arr, sizeof(ll)*2 );  ll x=1;  mf_arr[0]=mf_arr[1]=x;  rep(i,2,n+1){   x=x*i%mod;  mf_arr = realloc(mf_arr, sizeof(ll)*(i+1) );  mf_arr[i]=x; }  return 0;  }
ll m_inv(ll x, ll mod, ll is_fac ){ makeinv(num_of_inv,mod);  return is_fac?finv_arr[x]:inv_arr[x]; }
ll m_f(ll x, ll mod){  make_mf(num_of_inv,mod);  return mf_arr[x];  }
ll mod_nck(ll n, ll k, ll mod){ return m_f(n,mod)*m_inv(k,mod,1)%mod*m_inv(n-k,mod,1)%mod; }
ll m_p(ll r,ll n,ll mod){  ll t=1,s=r;  while(n>0){ t = (n&1) ? t*s%mod : t;  s=s*s%mod; n>>=1; }  return r?t:0;  }
ll m_mul2(ll a, ll b, ll mod){ return a*b%mod; }
ll m_mul3(ll a, ll b, ll c, ll mod){ return m_mul2(a*b%mod,c,mod); }
ll m_mul4(ll a, ll b, ll c, ll d, ll mod){ return m_mul3(a*b%mod,c,d,mod); }
ll m_mul5(ll a, ll b, ll c, ll d, ll e, ll mod){ return m_mul4(a*b%mod,c,d,e,mod); }

int upll(const void*a, const void*b){return*(ll*)a<*(ll*)b?-1:*(ll*)a>*(ll*)b?1:0;}
int downll(const void*a, const void*b){return*(ll*)a<*(ll*)b?1:*(ll*)a>*(ll*)b?-1:0;}
int cmp_string( const void * a , const void * b ) {  return strcmp( (char *)a , (char *)b ); }  // qsort((void*)s,n,sizeof(s[0]),int_sort );
int cmp_char(const void * a, const void * b) { return *(char *)a - *(char *)b;}
void sortup(ll*a,int n){qsort(a,n,sizeof(ll),upll);}
void sortdown(ll*a,int n){qsort(a,n,sizeof(ll),downll);}
void sort_string(int n,int size,char s[][size]){ qsort( (void*)s , n , sizeof(s[0]) , cmp_string ); }
void sort_char(char *s){ qsort( (void *)s , strlen(s) , sizeof(char) , cmp_char ); }
ll unique_string(ll n ,ll size, char s[][size]){ ll ans=1; rep(i,1,n) if( strcmp(s[i],s[i-1]) ) ans++; return ans; }
ll unique_num(ll n , ll a[]){ ll ans=1; rep(i,1,n) if( a[i]!=a[i-1] ) ans++; return ans; }

ll compare(ll a, ll b){ return a<b?-1:a>b?1:0; }
typedef struct{ ll a , b;}fr;
int cmp1( const void *p, const void *q ){  
    ll pa=((fr*)p)->a; ll qa=((fr*)q)->a;  return compare(pa,qa);  
}
int cmp2( const void *p, const void *q ){
    ll pa=((fr*)p)->a; ll qa=((fr*)q)->a;  return compare(qa,pa);
}
void strsortup(fr*a,int n){qsort(a,n,sizeof(fr),cmp1);}
void strsortdown(fr*a,int n){qsort(a,n,sizeof(fr),cmp2);}

void sort_partial(ll a[],int begin,int end,int is_increase){
    ll *b;  b = (ll *) malloc( sizeof(ll)*(end-begin) );

    rep(i,begin,end) b[i-begin]=a[i];
    if(is_increase) sortup(b,end-begin); else sortdown(b,end-begin);
    rep(i,begin,end) a[i]=b[i-begin];
}


#pragma region AVL
/*---------------------------AVL start--------------------------------*/
//https://qiita.com/mikecat_mixc/items/e9f8248de2ae7f7a0a29
typedef struct node_AVL_set{  
    ll val;
    int diff;
    int cnt;
    struct node_AVL_set *child[2];
}AVL_set;
void AVL_set_inside_rotate(AVL_set **node, int is_right){
    int l = is_right==false , r = is_right==true , sign = is_right ? 1 : -1;
    if((*node)->child[l] != NULL){
        AVL_set* left = (*node)->child[l];
        int a= (*node)->diff * sign , b= left->diff * sign ,na,nb;
        if(b+1){
            na=a-1-b;
            nb= (a-b) ? b-1 : a-2;
        }else{
            na=a-1;
            nb= a ? b-1 : a+b-2;
        }
        (*node)->diff = na * sign;
        left->diff = nb * sign;
        /* rotate-> */
        (*node)->child[l] = (*node)->child[l]->child[r];
        left->child[r] = *node;
        *node = left;
    }
}
int AVL_set_inside_update(AVL_set **node, ll data, int add){
    if(*node == NULL){
        if(add==2){
            *node = malloc(sizeof(AVL_set));
            (*node)->val = data;
            (*node)->cnt = 1;
            (*node)->diff = 0;
            (*node)->child[0] = NULL;
            (*node)->child[1] = NULL;
        }
        return add==2 ? *node != NULL : 0; 
    }else{
        int l, delta, delta_sign; AVL_set *next_node;
        if(data == (*node)->val){
            if(add==2){
                (*node)->cnt++;
                return 0;
            }else{
                if( add && (*node)->cnt > 1 ){
                    (*node)->cnt--; return 0;
                }else{
                    if((*node)->child[1] == NULL){
                        next_node = (*node)->child[0];
                        free(*node);
                        *node = next_node;
                        return -1;
                    }else if((*node)->child[0] == NULL){
                        next_node = (*node)->child[1];
                        free(*node);
                        *node = next_node;
                        return -1;
                    }else{
                        for(next_node = (*node)->child[0];
                        next_node->child[1] != NULL;
                        next_node = next_node->child[1]);
                        (*node)->val = next_node->val;
                        l=0;
                        delta_sign=1;
                        delta = AVL_set_inside_update(&(*node)->child[l], next_node->val, add);
                    }
                }
            }
        }else{
            l = data >= (*node)->val ? 1 : 0;
            delta_sign = data < (*node)->val ? 1 : -1;
            delta = AVL_set_inside_update(&(*node)->child[l], data, add);
        }
        if( delta ){
            int orig_diff = (*node)->diff;
            int do_rotate = 0, rotate_l , diff_sign , rotate_right;
            (*node)->diff += delta * delta_sign;
            if((*node)->diff > 1){
                do_rotate = 1;
                rotate_l = 0;
                diff_sign = 1;
                rotate_right = 1;
            }else if((*node)->diff < -1){
                do_rotate = 1;
                rotate_l = 1;
                diff_sign = -1;
                rotate_right = 0;
            }
            if(do_rotate){
                int child_diff = (*node)->child[rotate_l]->diff;
                if((*node)->child[rotate_l]->diff * diff_sign < 0){
                    AVL_set_inside_rotate(&(*node)->child[rotate_l], !rotate_right);
                }
                AVL_set_inside_rotate(node, rotate_right);
                return delta < 0 && child_diff != 0 ? -1 : 0;
            }
            if     (delta > 0 && orig_diff == 0) return 1;
            else if(delta < 0 && orig_diff != 0) return -1;
            else                                 return 0;
        }else{ 
            return 0;
        }
    }
}

void AVL_set_inside_print(const AVL_set *node, int depth){
    if(node == NULL) return;
    AVL_set_inside_print(node->child[1], depth + 1);
    printf("%lld %d\n", node->val,node->cnt);
    AVL_set_inside_print(node->child[0], depth + 1);    
}
void AVL_set_inside_free(AVL_set *node){
    if(node == NULL) return;
    AVL_set_inside_free(node->child[0]);
    AVL_set_inside_free(node->child[1]);
    free(node);
}
ll AVL_set_inside_count(AVL_set *root, ll val){
    AVL_set *node; node = root;
    while(node){
        if     (val < node->val) node = node->child[0];
        else if(val > node->val) node = node->child[1];
        else                     return node->cnt;
    }
    return 0;
}


int AVL_set_lowcomp(ll node, ll val, int type){
    if(node==val){
        if(type!=3) return 0;
        else return 1;
    }
    if(node<val) return 1;
    if(node>val) return -1;
    return 0;
}
// return smallest p  which meets  a[p]==val :1  >=:2   >:3
AVL_set* AVL_set_inside_lowerbound(AVL_set *root, ll val, int type){
    AVL_set *node; node = root;
    while(node){
        int com=AVL_set_lowcomp(node->val,val,type);
        if(com==0) return node;
        if(com==1) node = node->child[1];
        if(com==-1){
            AVL_set *small;
            small=AVL_set_inside_lowerbound(node->child[0],val,type);
            if(type==1){
                return small;
            }else{
                if(small!=NULL) return small;
                else return node;                 
            }
        }
    }
    return node;
}

int AVL_set_upcomp(ll node, ll val, int type){
    if(node==val){
        if(type!=3) return 0;
        else return -1;
    }
    if(node<val) return 1;
    if(node>val) return -1;
    return 0;
}
// return biggest p  which meets   a[p]==val :1  <=:2   <:3
AVL_set* AVL_set_inside_upperbound(AVL_set *root, ll val, int type){
    AVL_set *node; node = root;
    while(node){
        int com=AVL_set_upcomp(node->val,val,type);
        if(com==0) return node;
        if(com==-1) node = node->child[0];
        if(com==1){
            AVL_set *big;
            big=AVL_set_inside_upperbound(node->child[1],val,type);
            if(type==1){
                return big;
            }else{
                if(big!=NULL) return big;
                else return node;                 
            }
        }
    }
    return node;
}


ll AVL_set_inside_minmax(AVL_set *root, int type){
    while(root->child[type] !=NULL)  root= root->child[type];
    return root->val;
}
void AVL_set_inside_swap(AVL_set **node1, AVL_set **node2){  
    AVL_set *tmp;  tmp=*node1; *node1=*node2; *node2=tmp;
}

#define set_MAX_SIZE 514511
ll set_main( int command , int set_num , ll val ,ll option){
    static bool set_is_init=false;
    static AVL_set *set_pointer[set_MAX_SIZE];
    static ll set_siz[set_MAX_SIZE];
    if(!set_is_init){ set_is_init=true; rep(i,0,set_MAX_SIZE){ *(set_pointer+i) = NULL; set_siz[i]=0; } }
    if(command==-1){ AVL_set_inside_print( set_pointer[set_num] ,0); }
    if(command==1){ AVL_set_inside_count(set_pointer[set_num],val) ? 1 : set_siz[set_num]++;  AVL_set_inside_update( &set_pointer[set_num] , val , 2 ); }
    if(command==2){ return AVL_set_inside_count(set_pointer[set_num],val); }
    if(command==3){ ( AVL_set_inside_count(set_pointer[set_num],val) > 1 ) ? 1 : set_siz[set_num]--;  AVL_set_inside_update( &set_pointer[set_num] , val,1); }
    if(command==4){ set_siz[set_num]--; AVL_set_inside_update( &set_pointer[set_num] , val , 0 ); }
    if(command==5){ set_siz[set_num]=0; AVL_set_inside_free( set_pointer[set_num] ); set_pointer[set_num] = NULL; }
    if(command==6){ return set_siz[set_num]; }
    if(command==7){ return AVL_set_inside_minmax(set_pointer[set_num],1); }
    if(command==8){ return AVL_set_inside_minmax(set_pointer[set_num],0); }
    if(command==9){ AVL_set_inside_swap(&set_pointer[set_num],&set_pointer[val]); }
    if(10<=command&&command<=12){
        AVL_set *lowbound = AVL_set_inside_lowerbound(set_pointer[set_num],val,command-9);
        if(lowbound==NULL) return option;
        else return lowbound->val;
    }
    if(13<=command&&command<=15){
        AVL_set *upbound = AVL_set_inside_upperbound(set_pointer[set_num],val,command-12);
        if(upbound==NULL) return option;
        else return upbound->val;
    }
    return 0;
}

void set_print(int set_num){ set_main(-1,set_num,0,0); }
void set_insert(int set_num, ll val){ set_main(1,set_num,val,0); }
ll set_count(int set_num, ll val){ return set_main(2,set_num,val,0); }
void set_erase(int set_num, ll val, int is_all){ if(is_all) set_main(4,set_num,val,0); else set_main(3,set_num,val,0); }
void set_clear(int set_num){ set_main(5,set_num,0,0); }
ll set_size(int set_num){ return set_main(6,set_num,0,0); }
ll set_max(int set_num){ return set_main(7,set_num,0,0); }
ll set_min(int set_num){ return set_main(8,set_num,0,0); }
void set_swap(int set_num1, int set_num2){ set_main(9,set_num1,set_num2,0); }


// return smallest p  which meets  a[p]==val :1  >=:2   >:3
ll set_lowerbound(int set_num, ll val, int type, ll error){
    return set_main(9+type,set_num,val,error);
}
// return biggest p  which meets   a[p]==val :1  <=:2   <:3
ll set_upperbound(int set_num, ll val, int type, ll error){
    return set_main(12+type,set_num,val,error);
}

/*
insert *
size *
clear *
erase *
count *
max *
min *
swap *
begin x
end x
merge  source の要素のキーと等価なキーの要素がある場合、その要素は source から抽出されない
lower_bound *
upper_bound *
*/

// ll map_main()

/*---------------------------AVL start--------------------------------*/

#pragma endregion AVL



#pragma endregion kyopuro_templates




ll (*seg_ope)(ll,ll);
ll (*seg_def)(void);

ll seg[551551],seg_size=1;

ll seg_def_max(){ return -INF; }
ll seg_def_min(){ return INF; }
ll seg_def_sum(){ return 0; }
ll seg_def_gcd(){ return 0; }

ll seg_ope_max(ll a, ll b){ return max2(a,b); }
ll seg_ope_min(ll a, ll b){ return min2(a,b); }
ll seg_ope_sum(ll a, ll b){ return a+b; }
ll seg_ope_gcd(ll a, ll b){ return gcd(a,b); }


void segmake(int n, ll a[]){
    while(seg_size<n) seg_size*=2;
    ll t=seg_size;
    rep(i,0,t){
        if(i<n) seg[t-1+i]=a[i]; 
        else    seg[t-1+i]=seg_def();        
    }
    while(t/=2) rep(i,0,t) seg[t+i-1]= seg_ope(seg[2*(t+i)],seg[2*(t+i)-1]);
}
ll seg_query_inside(ll ql, ll qr, ll x, ll l, ll r){
    return (l>=ql && r<=qr) ? seg[x] : (l>qr || r<ql) ? seg_def() : seg_ope(seg_query_inside(ql,qr,2*x+1,l,(l+r)/2),seg_query_inside(ql,qr,2*x+2,(l+r)/2+1,r));
}
ll seg_query(int l, int r){
    return seg_query_inside(l,r,0,0,seg_size-1);
}


void segupdate(ll a, ll b){
    ll c=seg_size-1+a;
    seg[c]=b;
    while(c>0){
        c--; c/=2;
        seg[c]=seg_ope(seg[2*(c+1)],seg[2*(c+1)-1]);
    }
}



int main(void){
    // char ;
    ll n,ans=0;
    scanf("%lld",&n);
    ll a[n];
    rep(i,0,n){
        scanf("%lld",&a[i]);
    }

    // ll t=1;
    // while(t<n) t*=2;
    seg_ope=seg_ope_gcd;
    seg_def=seg_def_gcd;
    segmake(n,a);

    // ans=seggcd(1,n-1,0,0,t-1);
    ans=seg_query(1,n-1);
    // ans=max2( ans , seggcd(0,n-2,0,0,t-1) );
    ans=max2( ans , seg_query(0,n-2) );

    rep(i,1,n-1){
        ans = max2( ans , gcd( seg_query(0,i-1) , seg_query(i+1,n-1) ) );
    }

    printf("%lld\n",ans);
    return 0;
}
