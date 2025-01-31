#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <math.h>

int compare_sz_asc(const void* a, const void* b) {
    return *((size_t*)a) < *((size_t*)b) ? -1 : 1;
}
int compare_sz_desc(const void* a, const void* b) {
    return *((size_t*)a) > * ((size_t*)b) ? -1 : 1;
}
int compare_i64_asc(const void* a, const void* b) {
    return *((int64_t*)a) < *((int64_t*)b) ? -1 : 1;
}
int compare_i64_desc(const void* a, const void* b) {
    return *((int64_t*)a) > * ((int64_t*)b) ? -1 : 1;
}
int compare_u64_asc(const void* a, const void* b) {
    return *((uint64_t*)a) < *((uint64_t*)b) ? -1 : 1;
}
int compare_u64_desc(const void* a, const void* b) {
    return *((uint64_t*)a) > * ((uint64_t*)b) ? -1 : 1;
}
int compare_c_asc(const void* a, const void* b) {
    return *((char*)a) < *((char*)b) ? -1 : 1;
}
int compare_c_desc(const void* a, const void* b) {
    return *((char*)a) > * ((char*)b) ? -1 : 1;
}
int compare_dp_asc(const void* a, const void* b) {
    return *((double*)a) < *((double*)b) ? -1 : 1;
}
static size_t powSz(const size_t base, const size_t exp) {
    if (exp == 0) {
        return 1;
    }
    if (exp == 1) {
        return base;
    }
    if (exp % 2 == 0) {
        return powSz(base * base, exp / 2);
    }
    else {
        return base * powSz(base, exp - 1);
    }
}
static size_t comb(const size_t n, const size_t r) {
    size_t result = 1;
    for (size_t i = 0; i < r; i++) {
        result *= n - i;
        result /= i + 1;
    }
    return result;
}
static uint64_t combU64(const uint64_t n, const uint64_t r) {
    uint64_t result = 1;
    for (uint64_t i = 0; i < r; i++) {
        result *= n - i;
        result /= i + 1;
    }
    return result;
}
static size_t gcdZu(size_t m, size_t n) {
    size_t temp;
    while (m % n != 0) {
        temp = n;
        n = m % n;
        m = temp;
    }
    return n;
}
static uint64_t gcdU64(uint64_t m, uint64_t n)
{
    uint64_t temp;
    while (m % n != 0) {
        temp = n;
        n = m % n;
        m = temp;
    }
    return n;
}
typedef struct {
    uint64_t A;
    uint64_t B;
    uint64_t val;
} _status;
static _status status[200000];
typedef struct {
    uint64_t idx;
}BHeap_Val;
static int _bHeap_Compare(const BHeap_Val* parent, const BHeap_Val* node) {
    const uint64_t parentVal = status[parent->idx].val;
    const uint64_t nodeVal = status[node->idx].val;
    return parentVal >= nodeVal ? -1 : 1;
}
typedef struct {
    BHeap_Val val;
} BHeap_Node;
static struct {
    size_t size;
    int (*compare)(const BHeap_Val* parent, const BHeap_Val* node);
} bHeap_Info;
static BHeap_Node bHeap_Node[1 << 20];
static void bHeap_Init(int(*compare)(const BHeap_Val* parent, const BHeap_Val* node)) {
    bHeap_Info.size = 0;
    bHeap_Info.compare = compare;
}
static void bHeap_UpHeap(const size_t nodeIdx) {
    if (nodeIdx == 0) {
        return;
    }
    const size_t parentIdx = (nodeIdx + 1) / 2 - 1;
    const int compareResult = bHeap_Info.compare(&(bHeap_Node[parentIdx].val), &(bHeap_Node[nodeIdx].val));
    if (0 < compareResult) {
        const BHeap_Val tmp = bHeap_Node[parentIdx].val;
        bHeap_Node[parentIdx].val = bHeap_Node[nodeIdx].val;
        bHeap_Node[nodeIdx].val = tmp;
        if (parentIdx != 0) {
            bHeap_UpHeap(parentIdx);
        }
    }
}
static void bHeap_DownHeap(const size_t nodeIdx) {
    if (bHeap_Info.size - 1 <= nodeIdx) {
        return;
    }
    const size_t leftIdx = 2 * (nodeIdx + 1) - 1;
    if (leftIdx < bHeap_Info.size) {
        const int leftResult = bHeap_Info.compare(&(bHeap_Node[nodeIdx].val), &(bHeap_Node[leftIdx].val));
        size_t swapTarget = leftResult < 0 ? ((size_t)100000000) : leftIdx;
        const size_t rightIdx = leftIdx + 1;
        if (rightIdx < bHeap_Info.size) {
            const int rightResult = bHeap_Info.compare(&(bHeap_Node[nodeIdx].val), &(bHeap_Node[rightIdx].val));
            if (swapTarget == ((size_t)100000000)) {
                if (0 < rightResult) {
                    swapTarget = rightIdx;
                }
            }
            else {
                if (0 < rightResult) {
                    const int rightLeftResult = bHeap_Info.compare(&(bHeap_Node[leftIdx].val), &(bHeap_Node[rightIdx].val));
                    if (0 < rightLeftResult) {
                        swapTarget = rightIdx;
                    }
                }
            }
        }
        if (swapTarget != ((size_t)100000000)) {
            const BHeap_Val tmp = bHeap_Node[nodeIdx].val;
            bHeap_Node[nodeIdx].val = bHeap_Node[swapTarget].val;
            bHeap_Node[swapTarget].val = tmp;
            bHeap_DownHeap(swapTarget);
        }
    }
}
static void bHeap_Add(const BHeap_Val val) {
    bHeap_Node[bHeap_Info.size].val = val;
    bHeap_Info.size++;
    bHeap_UpHeap(bHeap_Info.size - 1);
}
static void bHeap_RemoveTop(void) {
    if (bHeap_Info.size == 0) {
        return;
    }
    if (bHeap_Info.size == 1) {
        bHeap_Info.size--;
        return;
    }
    bHeap_Node[0].val = bHeap_Node[bHeap_Info.size - 1].val;
    bHeap_Info.size--;
    bHeap_DownHeap(0);
}
static BHeap_Val* bHeap_GetTopVal(void) {
    return bHeap_Info.size == 0 ? ((void *)0) : &(bHeap_Node[0].val);
}
typedef struct {
    uint64_t cnt;
    size_t* child;
    size_t numChild;
    size_t maxNumChild;
} Tree_Node;
static Tree_Node tree_Node[200000];
static void tree_Init(const uint64_t N) {
    for (uint64_t i = 0; i < N; i++) {
        tree_Node[i].cnt = 0;
        tree_Node[i].numChild = 0;
        tree_Node[i].child = malloc(sizeof(size_t) * (128));
        tree_Node[i].maxNumChild = (128);
    }
}
static void tree_AddChild(const size_t parent, const size_t child) {
    if (tree_Node[parent].maxNumChild <= tree_Node[parent].numChild) {
        tree_Node[parent].child = realloc(tree_Node[parent].child, sizeof(size_t) * tree_Node[parent].maxNumChild * 2);
        tree_Node[parent].maxNumChild *= 2;
    }
    tree_Node[parent].child[tree_Node[parent].numChild] = child;
    tree_Node[parent].numChild++;
}
static char S[100001];
int main(void) {
    uint64_t N, K;
    scanf("%""l" "u""%""l" "u""%s", &N, &K, S);
    size_t lSecCnt = 0;
    size_t rSecCnt = 0;
    for (uint64_t i = 1; i < N; i++) {
        if (S[i] != S[i-1]) {
            if (S[i - 1] == 'L') {
                lSecCnt++;
            }
            else {
                rSecCnt++;
            }
        }
    }
    if (S[N - 1] == 'L') {
        lSecCnt++;
    }
    else {
        rSecCnt++;
    }
    if (lSecCnt < rSecCnt) {
        if (lSecCnt <= K) {
            printf("%""l" "u", N - 1);
        }
        else {
            printf("%""l" "u", N - (lSecCnt - K) * 2 - 1);
        }
    }
    else if (lSecCnt == rSecCnt) {
        if (lSecCnt <= K) {
            printf("%""l" "u", N - 1);
        }
        else {
            printf("%""l" "u", N - (rSecCnt - K) * 2);
        }
    }
    else {
        if (rSecCnt <= K) {
            printf("%""l" "u", N - 1);
        }
        else {
            printf("%""l" "u", N - (rSecCnt - K) * 2 - 1);
        }
    }
    return 0;
}
