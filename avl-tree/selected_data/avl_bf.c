#include <stdio.h>
#include <stdlib.h>
/* Copyright (C) 1991-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/*
 * Copyright (c) 2019 xieqing. https://github.com/xieqing
 * May be freely redistributed, but copyright notice must be retained.
 */
/*
 * Copyright (c) 2019 xieqing. https://github.com/xieqing
 * May be freely redistributed, but copyright notice must be retained.
 */
/*
 * node->bf = height(node->right) - height(node->left)
 * balance factors can be kept up-to-date by knowning the previous balance factors and the change in height
 * it is not necesary to know the absolute height
 */
enum avlbf {
 LEFTHEAVY = -1,
 BALANCED = 0,
 RIGHTHEAVY = 1
};
enum avltraversal {
 PREORDER,
 INORDER,
 POSTORDER
};
typedef struct avlnode {
 struct avlnode *left;
 struct avlnode *right;
 struct avlnode *parent;
 char bf;
 void *data;
} avlnode;
typedef struct {
 int (*compare)(const void *, const void *);
 void (*print)(void *);
 void (*destroy)(void *);
 avlnode root;
 avlnode nil;
 avlnode *min;
} avltree;
avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *));
void avl_destroy(avltree *avlt);
avlnode *avl_find(avltree *avlt, void *data);
avlnode *avl_successor(avltree *avlt, avlnode *node);
int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order);
void avl_print(avltree *avlt, void (*print_func)(void *));
avlnode *avl_insert(avltree *avlt, void *data);
void *avl_delete(avltree *avlt, avlnode *node, int keep);
int avl_check_order(avltree *avlt, void *min, void *max);
int avl_check_height(avltree *avlt);
static avlnode *rotate_left(avltree *avlt, avlnode *x);
static avlnode *rotate_right(avltree *avlt, avlnode *x);
static avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p);
static int check_order(avltree *avlt, avlnode *n, void *min, void *max);
static int check_height(avltree *avlt, avlnode *n);
static void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label);
static void destroy(avltree *avlt, avlnode *n);
/*
 * construction
 * return NULL if out of memory
 */
avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *))
{
 avltree *avlt;
 avlt = (avltree *) malloc(sizeof(avltree));
 if (avlt == NULL)
  return NULL; /* out of memory */
 avlt->compare = compare_func;
 avlt->destroy = destroy_func;
 /* sentinel node nil */
 avlt->nil.left = avlt->nil.right = avlt->nil.parent = (&(avlt)->nil);
 avlt->nil.bf = 0;
 avlt->nil.data = NULL;
 /* sentinel node root */
 avlt->root.left = avlt->root.right = avlt->root.parent = (&(avlt)->nil);
 avlt->root.bf = 0;
 avlt->root.data = NULL;
 avlt->min = NULL;
 return avlt;
}
/*
 * destruction
 */
void avl_destroy(avltree *avlt)
{
 destroy(avlt, ((avlt)->root.left));
 free(avlt);
}
/*
 * look up
 * return NULL if not found
 */
avlnode *avl_find(avltree *avlt, void *data)
{
 avlnode *p;
 p = ((avlt)->root.left);
 while (p != (&(avlt)->nil)) {
  int cmp;
  cmp = avlt->compare(data, p->data);
  if (cmp == 0)
   return p; /* found */
  p = (cmp < 0) ? p->left : p->right;
 }
 return NULL; /* not found */
}
/*
 * next larger
 * return NULL if not found
 */
avlnode *avl_successor(avltree *avlt, avlnode *node)
{
 avlnode *p;
 p = node->right;
 if (p != (&(avlt)->nil)) {
  /* move down until we find it */
  for ( ; p->left != (&(avlt)->nil); p = p->left) ;
 } else {
  /* move up until we find it or hit the root */
  for (p = node->parent; node == p->right; node = p, p = p->parent) ;
  if (p == (&(avlt)->root))
   p = NULL; /* not found */
 }
 return p;
}
/*
 * apply func
 * return non-zero if error
 */
int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order)
{
 int err;
 if (node != (&(avlt)->nil)) {
  if (order == PREORDER && (err = func(node->data, cookie)) != 0) /* preorder */
   return err;
  if ((err = avl_apply(avlt, node->left, func, cookie, order)) != 0) /* left */
   return err;
  if (order == INORDER && (err = func(node->data, cookie)) != 0) /* inorder */
   return err;
  if ((err = avl_apply(avlt, node->right, func, cookie, order)) != 0) /* right */
   return err;
  if (order == POSTORDER && (err = func(node->data, cookie)) != 0) /* postorder */
   return err;
 }
 return 0;
}
/*
 * print tree
 */
void avl_print(avltree *avlt, void (*print_func)(void *))
{
 printf("\n--\n");
 print(avlt, ((avlt)->root.left), print_func, 0, "T");
 printf("\nheight = %d\n", check_height(avlt, ((avlt)->root.left)));
}
/*
 * check order of tree
 */
int avl_check_order(avltree *avlt, void *min, void *max)
{
 return check_order(avlt, ((avlt)->root.left), min, max);
}
/*
 * check height of tree
 */
int avl_check_height(avltree *avlt)
{
 int height;
 height = check_height(avlt, ((avlt)->root.left));
 return (height < 0) ? 0 : 1;
}
/*
 * insert (or update) data
 * return NULL if out of memory
 */
avlnode *avl_insert(avltree *avlt, void *data)
{
 avlnode *current, *parent;
 avlnode *new_node;
 /* do a binary search to find where it should be */
 current = ((avlt)->root.left);
 parent = (&(avlt)->root);
 while (current != (&(avlt)->nil)) {
  int cmp;
  cmp = avlt->compare(data, current->data);
  parent = current;
  current = (cmp < 0) ? current->left : current->right;
 }
 /* replace the termination NIL pointer with the new node pointer */
 current = new_node = (avlnode *) malloc(sizeof(avlnode));
 if (current == NULL)
  return NULL; /* out of memory */
 current->left = current->right = (&(avlt)->nil);
 current->parent = parent;
 current->bf = 0;
 current->data = data;
 if (parent == (&(avlt)->root) || avlt->compare(data, parent->data) < 0)
  parent->left = current;
 else
  parent->right = current;
 if (avlt->min == NULL || avlt->compare(current->data, avlt->min->data) < 0)
  avlt->min = current;
 /*
	 * After insertion it is necessary to update the balance factors of all nodes, 
	 * observe that all nodes requiring correction must be on the path from the root to the new node.
	 * 
	 * Backtracking the top-down path from the root to the new node:
	 * 1. update the balance factor of parent node; 
	 * 2. rebalance if the balance factor of parent node temporarily becomes +2 or -2 (parent subtree has the same height as before, thus backtracking terminate immediately); 
	 * 3. terminate if the height of that parent subtree remains unchanged.
	 */
 while (current != ((avlt)->root.left)) { /* Loop (possibly up to the root) */
  if (current == parent->left) { /* The height of left subtree of parent subtree increases */
   if (parent->bf == 1) { /* parent subtree is right-heavy */
    /*
				 * height increase of left subtree is absorbed at parent node, 
				 * height of parent subtree remains unchanged, thus backtracking terminate.
				 */
    parent->bf = 0; /* height unchanged, balanced, goto break */
    break;
   } else if (parent->bf == 0) { /* parent subtree is balanced */
    /*
				 * height of parent subtree increases by one, thus backtracking continue.
				 */
    parent->bf = -1; /* height increased, left-heavy, goto loop */
   } else if (parent->bf == -1) { /* parent subtree is left-heavy */
    /*
				 * the balance factor becomes -2, this has to be repaired by an appropriate rotation
				 * after which parent subtree has the same height as before.
				 */
    fix_insert_leftimbalance(avlt, parent); /* height unchanged, balanced, goto break */
    break;
   }
  } else { /* The height of right subtree of parent subtree increases */
   if (parent->bf == -1) { /* parent subtree is left-heavy */
    /*
				 * height increase of right subtree is absorbed at parent node, 
				 * height of parent subtree remains unchanged, thus backtracking terminate.
				 */
    parent->bf = 0; /* height unchanged, balanced, goto break */
    break;
   } else if (parent->bf == 0) { /* parent subtree is balanced */
    /*
				 * height of parent subtree increases by one, thus backtracking continue.
				 */
    parent->bf = 1; /* height increased, right-heavy, goto loop */
   } else if (parent->bf == 1) {
    /*
				 * the balance factor becomes 2, this has to be repaired by an appropriate rotation
				 * after which parent subtree has the same height as before.
				 */
    fix_insert_rightimbalance(avlt, parent); /* height unchanged, balanced, goto break */
    break;
   }
  }
  /* move up */
  current = parent;
  parent = current->parent;
 }
 return new_node;
}
/*
 * delete node
 * return NULL if keep is zero (already freed)
 */
void *avl_delete(avltree *avlt, avlnode *node, int keep)
{
 avlnode *current, *parent;
 avlnode *target;
 void *data;
 data = node->data;
 /* choose node's in-order successor if it has two children */
 if (node->left == (&(avlt)->nil) || node->right == (&(avlt)->nil)) {
  target = node;
  if (avlt->min == target)
   avlt->min = avl_successor(avlt, target); /* deleted, thus min = successor */
 } else {
  target = avl_successor(avlt, node); /* node->right must not be NIL, thus move down */
  node->data = target->data; /* data swapped */
  /* if min == node, then min = successor = node (swapped), thus idle */
  /* if min == target, then min = successor, which is not the minimal, thus impossible */
 }
 /*
	 * After deletion it is necessary to update the balance factors of all nodes, 
	 * observe that all nodes requiring correction must be on the path from the root to the target node,
	 * which is either the subject node or the replacement node.
	 * 
	 * Backtracking the top-down path from the root to the target node:
	 * 1. update the balance factor of parent node;
	 * 2. rebalance if the balance factor of parent node temporarily becomes +2 or -2;
	 * 3. terminate if the height of that parent subtree remains unchanged.
	 */
 current = target;
 parent = current->parent;
 while (current != ((avlt)->root.left)) { /* Loop (possibly up to the root) */
  if (current == parent->left) { /* The height of left subtree of parent subtree decreases */
   if (parent->bf == -1) { /* parent subtree is left-heavy */
    /*
				 * height of parent subtree decreases by one, thus backtracking continue.
				 */
    parent->bf = 0; /* height decreased, balanced, goto loop */
   } else if (parent->bf == 0) { /* parent subtree is balanced */
    /*
				 * height decrease of left subtree is absorbed at parent node, 
				 * height of parent subtree remains unchanged, thus backtracking terminate.
				 */
    parent->bf = 1;
    break; /* height unchanged, right-heavy, goto break */
   } else if (parent->bf == 1) { /* parent subtree is right-heavy */
    /*
				 * the balance factor becomes 2, this has to be repaired by an appropriate rotation after which 
				 * height of parent subtree remains unchanged or
				 * height of parent subtree decreases by one.
				 */
    parent = fix_delete_rightimbalance(avlt, parent);
    if (parent->bf == -1)
     break; /* height unchanged, left-heavy, goto break */
    /* parent->bf == 0; height decreased, balanced, goto loop */
   }
  } else { /* The height of right subtree of parent subtree decreases */
   if (parent->bf == 1) { /* parent subtree is right-heavy */
    /*
				 * height of parent subtree decreases by one, thus backtracking continue.
				 */
    parent->bf = 0; /* height decreased, balanced, goto loop */
   } else if (parent->bf == 0) {
    /*
				 * height decrease of right subtree is absorbed at parent node, 
				 * height of parent subtree remains unchanged, thus backtracking terminate.
				 */
    parent->bf = -1;
    break; /* height unchanged, left-heavy, goto break */
   } else if (parent->bf == -1) { /* parent subtree is left-heavy */
    /*
				 * the balance factor becomes -2, this has to be repaired by an appropriate rotation after which 
				 * height of parent subtree remains unchanged or
				 * height of parent subtree decreases by one.
				 */
    parent = fix_delete_leftimbalance(avlt, parent);
    if (parent->bf == 1)
     break; /* height unchanged, right-heavy, goto break */
    /* height decreased, balanced, goto loop */
   }
  }
  /* move up */
  current = parent;
  parent = current->parent;
 }
 /* replace the target node with its child (may be NIL) */
 avlnode *child; /* child of target */
 child = (target->left == (&(avlt)->nil)) ? target->right : target->left; /* child may be NIL */
 if (child != (&(avlt)->nil))
  child->parent = target->parent;
 if (target == target->parent->left)
  target->parent->left = child;
 else
  target->parent->right = child;
 free(target);
 /* keep or discard data */
 if (keep == 0) {
  avlt->destroy(data);
  data = NULL; /* freed */
 }
 return data;
}
/*
 * rotate left about x
 * return the new root
 */
avlnode *rotate_left(avltree *avlt, avlnode *x)
{
 avlnode *y;
 y = x->right; /* child */
 /* tree x */
 x->right = y->left;
 if (x->right != (&(avlt)->nil))
  x->right->parent = x;
 /* tree y */
 y->parent = x->parent;
 if (x == x->parent->left)
  x->parent->left = y;
 else
  x->parent->right = y;
 /* assemble tree x and tree y */
 y->left = x;
 x->parent = y;
 return y;
}
/*
 * rotate right about x
 * return the new root
 */
avlnode *rotate_right(avltree *avlt, avlnode *x)
{
 avlnode *y;
 y = x->left; /* child */
 /* tree x */
 x->left = y->right;
 if (x->left != (&(avlt)->nil))
  x->left->parent = x;
 /* tree y */
 y->parent = x->parent;
 if (x == x->parent->left)
  x->parent->left = y;
 else
  x->parent->right = y;
 /* assemble tree x and tree y */
 y->right = x;
 x->parent = y;
 return y;
}
/*
 * fix left imbalance after insertion
 * return the new root
 */
avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p)
{
 /* p->left->bf updated here */
 if (p->left->bf == p->bf) { /* -1, -1 */
  p = rotate_right(avlt, p);
  p->bf = p->right->bf = 0;
 } else { /* 1, -1 */
  int oldbf;
  oldbf = p->left->right->bf;
  rotate_left(avlt, p->left);
  p = rotate_right(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}
/*
 * fix right imbalance after insertion
 * return the new root
 */
avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p)
{
 if (p->right->bf == p->bf) { /* 1, 1 */
  p = rotate_left(avlt, p);
  p->bf = p->left->bf = 0;
 } else { /* -1, 1 */
  int oldbf;
  oldbf = p->right->left->bf;
  rotate_right(avlt, p->right);
  p = rotate_left(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}
/*
 * fix left imbalance after deletion
 * return the new root
 */
avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p)
{
 if (p->left->bf == -1) {
  p = rotate_right(avlt, p);
  p->bf = p->right->bf = 0;
 } else if (p->left->bf == 0) {
  p = rotate_right(avlt, p);
  p->bf = 1;
  p->right->bf = -1;
 } else if (p->left->bf == 1) {
  int oldbf;
  oldbf = p->left->right->bf;
  rotate_left(avlt, p->left);
  p = rotate_right(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}
/*
 * fix right imbalance after deletion
 * return the new root
 */
avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p)
{
 if (p->right->bf == 1) {
  p = rotate_left(avlt, p);
  p->bf = p->left->bf = 0;
 } else if (p->right->bf == 0) {
  p = rotate_left(avlt, p);
  p->bf = -1;
  p->left->bf = 1;
 } else if (p->right->bf == -1) {
  int oldbf;
  oldbf = p->right->left->bf;
  rotate_right(avlt, p->right);
  p = rotate_left(avlt, p);
  p->bf = 0;
  if (oldbf == -1) {
   p->left->bf = 0;
   p->right->bf = 1;
  } else if (oldbf == 1) {
   p->left->bf = -1;
   p->right->bf = 0;
  } else if (oldbf == 0) {
   p->left->bf = p->right->bf = 0;
  }
 }
 return p;
}
/*
 * check order recursively
 */
int check_order(avltree *avlt, avlnode *n, void *min, void *max)
{
 if (n == (&(avlt)->nil))
  return 1;
 if (avlt->compare(n->data, min) < 0 || avlt->compare(n->data, max) > 0)
  return 0;
 return check_order(avlt, n->left, min, n->data) && check_order(avlt, n->right, n->data, max);
}
/*
 * check height recursively
 */
int check_height(avltree *avlt, avlnode *n)
{
 int lh, rh, cmp;
 if (n == (&(avlt)->nil))
  return 0;
 lh = check_height(avlt, n->left);
 if (lh < 0)
  return lh;
 rh = check_height(avlt, n->right);
 if (rh < 0)
  return rh;
 cmp = rh - lh;
 if (cmp < -1 || cmp > 1 || cmp != n->bf) /* check recomputed/cached balance factor */
  return -1;
 return 1 + ((lh > rh) ? lh : rh);
}
/*
 * print node recursively
 */
void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label)
{
 if (n != (&(avlt)->nil)) {
  print(avlt, n->right, print_func, depth + 1, "R");
  printf("%*s", 8 * depth, "");
  if (label)
   printf("%s: ", label);
  print_func(n->data);
  printf(" (%s%d)\n", (n->bf >= 0) ? "+" : "", n->bf);
  print(avlt, n->left, print_func, depth + 1, "L");
 }
}
/*
 * destroy node recursively
 */
void destroy(avltree *avlt, avlnode *n)
{
 if (n != (&(avlt)->nil)) {
  destroy(avlt, n->left);
  destroy(avlt, n->right);
  avlt->destroy(n->data);
  free(n);
 }
}
