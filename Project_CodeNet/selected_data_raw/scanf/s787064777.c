#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>
#include<string.h>

typedef int32_t i32;
typedef int64_t i64;

typedef i64 flow_type;

const flow_type flow_inf = (i64) 5000 * 1000000000;

typedef struct flow_edge {
  int32_t vertex;
  int32_t next;
  flow_type capacity;
} flow_edge;

typedef struct maxFlowGraph {
  flow_edge *edge;
  int32_t *start;
  int32_t vertex_num;
  int32_t pointer;
  int32_t edge_length;
} graph;

graph* new_graph (const int32_t vertex_num) {
  graph *g = (graph *) calloc (1, sizeof (graph));
  g->vertex_num = vertex_num;
  const int32_t initial_length = 4;
  g->edge = (flow_edge *) calloc (initial_length, sizeof (flow_edge));
  g->start = (int32_t *) calloc (vertex_num, sizeof (int32_t));
  g->pointer = 0;
  g->edge_length = initial_length;
  for (int32_t i = 0; i < vertex_num; ++i) {
    g->start[i] = -1;
  }
  return g;
}

void free_graph (graph * const g) {
  free (g->edge);
  free (g->start);
  free (g);
}

void clear_graph (graph * const g) {
  g->pointer = 0;
  memset (g->start, -1, sizeof (int32_t) * g->vertex_num);
}

void add_edge (graph * const g, const int32_t from, const int32_t to, const flow_type capa) {
  if (g->pointer == g->edge_length) {
    g->edge_length *= 2;
    g->edge = (flow_edge *) realloc (g->edge, sizeof (flow_edge) * g->edge_length);
  }
  const int32_t p = g->pointer;
  g->edge[p] = (flow_edge) {to, g->start[from], capa};
  g->start[from] = p;
  g->edge[p + 1] = (flow_edge) {from, g->start[to], 0};
  g->start[to] = p + 1;
  g->pointer += 2;
}

void add_edge_undirected (graph * const g, const int32_t u, const int32_t v, const flow_type capa) {
  if (g->pointer == g->edge_length) {
    g->edge_length *= 2;
    g->edge = (flow_edge *) realloc (g->edge, sizeof (flow_edge) * g->edge_length);
  }
  const int32_t p = g->pointer;
  g->edge[p] = (flow_edge) {v, g->start[u], capa};
  g->start[u] = p;
  g->edge[p + 1] = (flow_edge) {u, g->start[v], capa};
  g->start[v] = p + 1;
  g->pointer += 2;
}

flow_type dinic_dfs (const int32_t v, const graph * const g, const int32_t dst, const int32_t * const level, int32_t * const iter, flow_type e) {
  if (v == dst) return e;
  flow_type sum = 0;
  for (int32_t p = iter[v]; p != -1; p = g->edge[p].next, iter[v] = p) {
    const int32_t u = g->edge[p].vertex;
    const flow_type capa = g->edge[p].capacity;
    if (level[u] <= level[v] || capa <= 0) continue;
    const flow_type f = dinic_dfs (u, g, dst, level, iter, capa < e ? capa : e);
    if (f > 0) {
      g->edge[p].capacity -= f;
      g->edge[p ^ 1].capacity += f;
      sum += f;
      e -= f;
      if (e <= 0) return sum;
    }
  }
  return sum;
}

flow_type dinic (const graph * const g, const int32_t src, const int32_t dst) {
  const int32_t vertex_num = g->vertex_num;
  int32_t * const level = (int32_t *) calloc (vertex_num, sizeof (int32_t));
  int32_t * const queue = (int32_t *) calloc (vertex_num, sizeof (int32_t));
  int32_t * const iter  = (int32_t *) calloc (vertex_num, sizeof (int32_t));
  flow_type flow = 0;
  while (1) {
    memset (level, 0, sizeof (int32_t) * vertex_num);
    int32_t front = 0;
    int32_t last = 0;
    level[dst] = vertex_num;
    queue[last++] = dst;
    while (front < last && level[src] == 0) {
      const int32_t v = queue[front++];
      for (int32_t p = g->start[v]; p!=-1; p = g->edge[p].next) {
        const int32_t u = g->edge[p].vertex;
        if (g->edge[p ^ 1].capacity > 0 && level[u] == 0) {
          level[u] = level[v] - 1;
          queue[last++] = u;
        }
      }
    }
    if (level[src] == 0) break;
    memcpy (iter, g->start, sizeof (int32_t) * vertex_num);
    while (1) {
      flow_type f = dinic_dfs (src, g, dst, level, iter, flow_inf);
      if (f <= 0) break;
      flow += f;
    }
  }
  free (level);
  free (queue);
  free (iter);
  return flow;
}

typedef struct edge {
  i32 from, to;
  i64 capa;
} edge;

typedef struct edge_list {
  edge e;
  struct edge_list *next;
} list;

const i32 dummy = -1;
list* add (list *lst, i32 from, i32 to, i64 capa) {
  if (from == dummy || to == dummy) return lst;
  list *l = (list *) calloc (1, sizeof (list));
  l->e = (edge) {from, to, capa};
  l->next = lst;
  return l;
}

i32 new_node (void) {
  static i32 val = 0;
  return val++;
}

void run (void) {
  i32 n, a, b;
  scanf ("%" SCNi32 "%" SCNi32 "%" SCNi32, &n, &a, &b);
  i32 *p = (i32 *) calloc (n, sizeof (i32));
  list *e = NULL;
  const i32 src = new_node();
  const i32 dst = new_node();
  i32 *va = (i32 *) calloc (n, sizeof (i32));
  i32 *vb = (i32 *) calloc (n, sizeof (i32));
  for (i32 i = 0; i < n; ++i) {
    scanf ("%" SCNi32, p + i);
    p[i]--;
    va[i] = new_node();
    e = add (e, src, va[i], a);
    vb[i] = new_node();
    e = add (e, vb[i], dst, b);
  }
  i32 k = 1;
  while (k < n) k *= 2;
  i32 *s = (i32 *) calloc (2 * k, sizeof (i32));
  for (i32 i = 0; i < n; ++i) {
    s[i + k] = vb[i];
  }
  for (i32 i = n; i < k; ++i) {
    s[i + k] = dummy;
  }
  for (i32 i = k - 1; i > 0; --i) {
    if (s[2 * i] == dummy || s[2 * i + 1] == dummy) {
      s[i] = dummy;
    } else {
      s[i] = new_node();
      e = add (e, s[i], s[2 * i], flow_inf);
      e = add (e, s[i], s[2 * i + 1], flow_inf);
    }
  }
  for (i32 i = 0; i < n; ++i) {
    for (i32 l = k, r = p[i] + k; l < r; l >>= 1, r >>= 1) {
      if (l & 1) e = add (e, va[i], s[l++], flow_inf);
      if (r & 1) e = add (e, va[i], s[--r], flow_inf);
    }
    s[k + p[i]] = dummy;
    for (i32 x = (k + p[i]) / 2; x > 0; x >>= 1) {
      if (s[x] == dummy) continue;
      if (s[2 * x] == dummy || s[2 * x + 1] == dummy) {
        s[x] = s[2 * x] + s[2 * x + 1] - dummy;
      } else {
        s[x] = new_node();
        e = add (e, s[x], s[2 * x], flow_inf);
        e = add (e, s[x], s[2 * x + 1], flow_inf);
      }
    }
  }
  i32 size = new_node();
  graph *g = new_graph (size);
  while (e != NULL) {
    add_edge (g, e->e.from, e->e.to, e->e.capa);
    e = e->next;
  }
  i64 ans = dinic (g, src, dst);
  printf ("%" PRIi64 "\n", ans);
}

int main (void) {
  run();
  return 0;
}
