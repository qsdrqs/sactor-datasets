#include <stdio.h>
#include <stdlib.h>

long long MOD(long long a){
 a %= (long long)(1e9 + 7);
 return a >= 0 ? a : a + (long long)(1e9 + 7);
}
typedef struct {
 long long v_num;
 long long dis;
 long long prev;
}pair;
long long compare(pair a, pair b){
 return a.dis - b.dis;
}
typedef struct graph_edge_sub graph_edge;
typedef struct {
 long long num;
 long long next_num;
 graph_edge *next;
 long long prev_num;
}graph_vertex_sub;
struct graph_edge_sub{
 graph_vertex_sub *v;
 long long w;
 graph_edge *next;
};
typedef struct graph_v_sub graph_vertex;
struct graph_v_sub{
 long long num;
 long long val;
 long long next_num;
 graph_vertex **next;
 long long *next_weight;
 long long prev_num;
 graph_vertex **prev;
 long long *prev_weight;
};
typedef struct {
 long long N;
 graph_vertex_sub **v_s;
 graph_vertex **v;
}graph;
//頂点数N, 各頂点の初期値ini_valのグラフを作る
graph *make_graph(long long N, long long ini_val){
 long long i;
 graph *g = (graph *)malloc(sizeof(graph));
 g->N = N;
 g->v_s = (graph_vertex_sub **)malloc(sizeof(graph_vertex_sub *) * N);
 g->v = (graph_vertex **)malloc(sizeof(graph_vertex *) * N);
 for(i = 0; i < N; i++){
  (g->v_s)[i] = (graph_vertex_sub *)malloc(sizeof(graph_vertex_sub));
  (g->v_s)[i]->num = i;
  (g->v_s)[i]->next_num = 0;
  (g->v_s)[i]->next = ((void *)0);
  (g->v_s)[i]->prev_num = 0;
  (g->v)[i] = (graph_vertex *)malloc(sizeof(graph_vertex));
  (g->v)[i]->num = i;
  (g->v)[i]->val = ini_val;
  (g->v)[i]->next_num = 0;
  (g->v)[i]->next = ((void *)0);
  (g->v)[i]->next_weight = ((void *)0);
  (g->v)[i]->prev_num = 0;
  (g->v)[i]->prev = ((void *)0);
  (g->v)[i]->prev_weight = ((void *)0);
 }
 return g;
}
//グラフgの頂点aから頂点bに重みwの有向辺を張る (0 <= a, b <= N - 1)
void set_edge_graph(long long a, long long b, long long w, graph *g){
 graph_edge *new1 = (graph_edge *)malloc(sizeof(graph_edge));
 new1->v = (g->v_s)[b];
 new1->w = w;
 new1->next = (g->v_s)[a]->next;
 (g->v_s)[a]->next = new1;
 (g->v_s)[a]->next_num++;
 (g->v_s)[b]->prev_num++;
}
//set_edge_graph後に呼び出す
void build_graph(graph *g){
 long long i;
 graph_vertex_sub **v_s = g->v_s;
 graph_vertex **v = g->v;
 graph_vertex *nowv;
 graph_edge *nowe;
 for(i = 0; i < g->N; i++){
  v[i]->next = (graph_vertex **)malloc(sizeof(graph_vertex *) * v_s[i]->next_num);
  v[i]->next_weight = (long long *)malloc(sizeof(long long) * v_s[i]->next_num);
  v[i]->prev = (graph_vertex **)malloc(sizeof(graph_vertex *) * v_s[i]->prev_num);
  v[i]->prev_weight = (long long *)malloc(sizeof(long long) * v_s[i]->prev_num);
 }
 for(i = 0; i < g->N; i++){
  nowv = v[i];
  for(nowe = v_s[i]->next; nowe != ((void *)0); nowe = nowe->next){
   (nowv->next)[nowv->next_num] = v[nowe->v->num];
   (nowv->next_weight)[nowv->next_num] = nowe->w;
   nowv->next_num++;
   (v[nowe->v->num]->prev)[v[nowe->v->num]->prev_num] = nowv;
   (v[nowe->v->num]->prev_weight)[v[nowe->v->num]->prev_num] = nowe->w;
   v[nowe->v->num]->prev_num++;
  }
 }
}
typedef struct heap_node_sub{
 pair val;
 struct heap_node_sub *parent;
 struct heap_node_sub *prev;
 struct heap_node_sub *next;
 struct heap_node_sub *left;
 struct heap_node_sub *right;
}heap_node;
typedef struct {
 long long N;
 heap_node *root;
 heap_node *last;
}heap;
//heapを生成
heap *make_heap(){
 heap *h = (heap *)malloc(sizeof(heap));
 h->N = 0;
 h->root = ((void *)0);
 h->last = ((void *)0);
 return h;
}
long long element_num_heap(heap *h){
 return h->N;
}
void up_heapify(heap_node *n, heap *h){
 if(n->parent != ((void *)0)){
  if(compare(n->val, n->parent->val) < 0){
   pair tmp;
   tmp = n->val;
   n->val = n->parent->val;
   n->parent->val = tmp;
   up_heapify(n->parent, h);
  }
 }
}
//データを追加
void add_data_heap(pair val, heap *h){
 heap_node *new = (heap_node *)malloc(sizeof(heap_node));
 new->val = val;
 new->next = ((void *)0);
 new->left = ((void *)0);
 new->right = ((void *)0);
 if(element_num_heap(h) == 0){
  new->parent = ((void *)0);
  new->prev = ((void *)0);
  h->root = new;
  h->last = new;
 }
 else if(element_num_heap(h) == 1){
  new->parent = h->root;
  new->prev = h->root;
  h->root->left = new;
  h->root->next = new;
  h->last = new;
  up_heapify(new, h);
 }
 else{
  new->prev = h->last;
  h->last->next = new;
  if(h->last->parent->right == ((void *)0)){
   new->parent = h->last->parent;
   h->last->parent->right = new;
  }
  else{
   new->parent = h->last->parent->next;
   h->last->parent->next->left = new;
  }
  h->last = new;
  up_heapify(new, h);
 }
 h->N++;
}
void down_heappify(heap_node *n, heap *h){
 if(n->left != ((void *)0)){
  pair tmp;
  if(n->right == ((void *)0)){
   if(compare(n->val, n->left->val) > 0){
    tmp = n->val;
    n->val = n->left->val;
    n->left->val = tmp;
    down_heappify(n->left, h);
   }
  }
  else{
   if(compare(n->left->val, n->right->val) <= 0 && compare(n->val, n->left->val) > 0){
    tmp = n->val;
    n->val = n->left->val;
    n->left->val = tmp;
    down_heappify(n->left, h);
   }
   else if(compare(n->left->val, n->right->val) > 0 && compare(n->val, n->right->val) > 0){
    tmp = n->val;
    n->val = n->right->val;
    n->right->val = tmp;
    down_heappify(n->right, h);
   }
  }
 }
}
//最小のものを取り出す
pair take_min_heap(heap *h){
 if(element_num_heap(h) == 0){
  printf("no data in the heap\n");
 }
 pair ans = h->root->val;
 heap_node *ln = h->last;
 if(element_num_heap(h) == 1){
  h->root = ((void *)0);
  h->last = ((void *)0);
 }
 else{
  ln->prev->next = ((void *)0);
  if(ln->parent->right == ((void *)0)){
   ln->parent->left = ((void *)0);
  }
  else{
   ln->parent->right = ((void *)0);
  }
  h->last = ln->prev;
  h->root->val = ln->val;
  down_heappify(h->root, h);
 }
 free(ln);
 h->N--;
 return ans;
}
pair look_min_heap(heap *h){
 if(element_num_heap(h) == 0){
  printf("no data in the heap\n");
 }
 return h->root->val;
}
long long *Dijkstra(graph *g, long long s, long long *path_num){
 long long N = g->N, i;
 long long *distance = (long long *)malloc(sizeof(long long) * N);
 for(i = 0; i < N; i++){
  distance[i] = (long long)(1e18);
 }
 heap *h = make_heap();
 pair p;
 p.v_num = s;
 p.dis = 0;
 p.prev = s;
 add_data_heap(p, h);
 graph_vertex *nowv;
 while(element_num_heap(h) > 0){
  p = take_min_heap(h);
  nowv = g->v[p.v_num];
  if(p.dis == distance[nowv->num]){
   path_num[nowv->num] = MOD(path_num[nowv->num] + path_num[p.prev]);
  }
  if(p.dis < distance[nowv->num]){
   distance[nowv->num] = p.dis;
   path_num[nowv->num] = path_num[p.prev];
   for(i = 0; i < nowv->next_num; i++){
    p.v_num = nowv->next[i]->num;
    p.dis = distance[nowv->num] + nowv->next_weight[i];
    p.prev = nowv->num;
    add_data_heap(p, h);
   }
  }
 }
 return distance;
}
signed main(){
 long long N, M, S, T, u, v, d, i, j;
 scanf("%lld%lld", &N, &M);
 scanf("%lld%lld", &S, &T);
 S--;
 T--;
 graph *g = make_graph(N, 0);
 for(i = 0; i < M; i++){
  scanf("%lld%lld%lld", &u, &v, &d);
  u--;
  v--;
  set_edge_graph(u, v, d, g);
  set_edge_graph(v, u, d, g);
 }
 build_graph(g);
 long long *path_num_S = (long long *)malloc(sizeof(long long) * N);
 long long *path_num_T = (long long *)malloc(sizeof(long long) * N);
 for(i = 0; i < N; i++){
  path_num_S[i] = 0;
  path_num_T[i] = 0;
 }
 path_num_S[S] = 1;
 path_num_T[T] = 1;
 long long *dis_S = Dijkstra(g, S, path_num_S);
 long long *dis_T = Dijkstra(g, T, path_num_T);
 long long ans = MOD(path_num_S[T] * path_num_T[S]);
 graph_vertex *nowv;
 for(i = 0; i < N; i++){
  if(dis_S[i] + dis_T[i] == dis_S[T] && dis_S[i] == dis_T[i]){
   ans = MOD(ans - MOD(path_num_S[i] * path_num_S[i]) * MOD(path_num_T[i] * path_num_T[i]));
  }
  nowv = g->v[i];
  for(j = 0; j < nowv->next_num; j++){
   if(/*nowv->num < nowv->next[j]->num 
			 &&*/ dis_S[nowv->num] + nowv->next_weight[j] + dis_T[nowv->next[j]->num] == dis_S[T]
    && 2 * dis_S[nowv->num] < dis_S[T]
    && 2 * dis_T[nowv->next[j]->num] < dis_T[S]){
     ans = MOD(ans - MOD(path_num_S[nowv->num] * path_num_S[nowv->num]) * MOD(path_num_T[nowv->next[j]->num] * path_num_T[nowv->next[j]->num]));
   }
  }
 }
/*	for(i = 0; i < N; i++){
		printf("dis_S[%lld] = %lld\n", i, dis_S[i]);
	}
	printf("\n");
	for(i = 0; i < N; i++){
		printf("dis_T[%lld] = %lld\n", i, dis_T[i]);
	}
	printf("\n");
	for(i = 0; i < N; i++){
		printf("path_num_S[%lld] = %lld\n", i, path_num_S[i]);
	}
	printf("\n");
	for(i = 0; i < N; i++){
		printf("path_num_T[%lld] = %lld\n", i, path_num_T[i]);
	}
	printf("\n");
*/ printf("%lld\n", ans);
 return 0;
}
