/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ghy",
    /* First member's full name */
    "ghy",
    /* First member's email address */
    "guhaiyao56@gmail.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* Single word (4) or double word (8) alignment */
#define ALIGNMENT 8
#define ALIGN(size) ((((size) + (ALIGNMENT - 1)) / (ALIGNMENT)) * (ALIGNMENT))

/* Basic constants and macros */
#define WSIZE 4
#define DSIZE 8
#define INITCHUNKSIZE (1 << 6)
#define CHUNKSIZE (1 << 12)
#define MAX_LEN 16

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */ 
#define PACK(size, alloc) ((size) | (alloc))
 
/* Read and write a word at address p */
#define GET(p) (*(size_t *)(p))
#define PUT(p, val) (*(size_t *)(p) = (val))
 
/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
 
/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
 
/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))
 
#define PRED_BP(bp) ((char *)(bp))
#define SUCC_BP(bp) ((char *)(bp) + WSIZE)
 
#define PRED(bp) (*(char **)(bp))
#define SUCC(bp) (*(char **)(SUCC_BP(bp)))

#define SET_BP(p, bp) (*(unsigned int *)(p) = (unsigned int)(bp))


/* Global variables */
static char *heap_head;  /* pointer to first block */
void *list[MAX_LEN]; /* 分离空闲链表 */
static void *extend_heap(size_t size);/* 扩展堆 */
static void *coalesce(void *p);/* 合并相邻的空闲块 */
static void *place(void *p, size_t size);/* 分离后放入空闲链表 */
static void insertblock(void *p, size_t size); /* 插入到空闲链表 */
static void deleteblock(void *p);  /* 删除块空闲链表 */
static void checkblock(void *p); /* 检查块 */
void mm_checkheap(int v); /* 检查堆 */
static void printblock(void *p); /* 打印相关信息 */

/* 扩展堆 */
static void *extend_heap(size_t size) {
    char *p;
    size = ALIGN(size);

    /* Allocate an even number of word to mountain alignment */
    if((long)(p = mem_sbrk(size)) == -1)
        return NULL;

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(p), PACK(size, 0));/* Free block header */
    PUT(FTRP(p), PACK(size, 0));/* Free block footer */
    PUT(HDRP(NEXT_BLKP(p)), PACK(0, 1));/* New epilogue header */

    /* 空闲链表插入结点 */
    insertblock(p, size);

    /* 进行判断 */
    return coalesce(p);
}

/* 插入到空闲链表 */
static void insertblock(void *p, size_t size) {
    
    void *now = NULL;
    void *pre = NULL;
    int  i = 0;

    /* 找到空闲链表 */
    for (i = 0; i < MAX_LEN - 1 && size > 1; ++i) 
        size >>= 1;

    /* 链中块由小到大分布 */
    now = list[i];
    while (now != NULL && size > GET_SIZE(HDRP(now))) {
        pre = now;
        now = SUCC(now);
    }
    
    /* 插入情况共有四种 */
    if(now != NULL) {
        if(pre != NULL) {
            SET_BP(PRED_BP(p), pre);
            SET_BP(SUCC_BP(pre), p);
            SET_BP(SUCC_BP(p), now);
            SET_BP(PRED_BP(now), p);
        }
        else {
            SET_BP(PRED_BP(p), NULL);
            SET_BP(SUCC_BP(p), now);
            SET_BP(PRED_BP(now), p);
            list[i] = p;
        }
    }
    else {
        if(pre != NULL) {
            SET_BP(PRED_BP(p), pre);
            SET_BP(SUCC_BP(p), NULL);
            SET_BP(PRED_BP(pre), p);
        }
        else {
            SET_BP(PRED_BP(p), NULL);
            SET_BP(SUCC_BP(p), NULL);
            list[i] = p;
        }
    }
}
/* 删除 */
static void deleteblock(void *p) {

    size_t size = GET_SIZE(HDRP(p));
    int i = 0;
    /* 找到对应的分离空闲链表 */
    for (i = 0; i < MAX_LEN - 1 && size > 1; ++i) 
        size >>= 1;
    /* 前继不为空 */
    if (PRED(p) != NULL) {
        /* 从中间删除 */
        if (SUCC(p) != NULL) {
            SET_BP(SUCC_BP(PRED(p)), SUCC(p));
            SET_BP(PRED_BP(SUCC(p)), PRED(p));
        }
        /* 从表尾删除 */
        else {
            SET_BP(SUCC_BP(PRED(p)), NULL);
        }
    }
    else {
        /* 表头删除 */
        if (SUCC(p) != NULL) {
            SET_BP(PRED_BP(SUCC(p)), NULL);
            list[i] = SUCC(p);
        }
        /* 链表只有一个结点 */
        else 
            list[i] = NULL;
    }
}
/* 合并相邻的空闲块 */
static void *coalesce(void *p) {
    size_t  prev = GET_ALLOC(HDRP(PREV_BLKP(p)));
    size_t  next = GET_ALLOC(HDRP(NEXT_BLKP(p)));
    size_t size = GET_SIZE(HDRP(p));

    /* 前后均非空闲块 */
    if (prev && next) {
        return p;
    }
    /* 后面是空闲块 */
    else if (prev) {
        deleteblock(p);
        deleteblock(NEXT_BLKP(p));
        size += GET_SIZE(HDRP(NEXT_BLKP(p)));
        PUT(HDRP(p), PACK(size, 0));
        PUT(FTRP(p), PACK(size, 0));
    }
    /* 前面是空闲块 */
    else if (next) {
        deleteblock(p);
        deleteblock(PREV_BLKP(p));
        size += GET_SIZE(HDRP(PREV_BLKP(p)));
        PUT(FTRP(p), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(p)), PACK(size, 0));
        p = PREV_BLKP(p);
    }
    /* 前后均为空 */
    else {
        deleteblock(p);
        deleteblock(PREV_BLKP(p));
        deleteblock(NEXT_BLKP(p));
        size += GET_SIZE(HDRP(PREV_BLKP(p))) + GET_SIZE(HDRP(NEXT_BLKP(p)));
        PUT(HDRP(PREV_BLKP(p)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(p)), PACK(size, 0));
        p = PREV_BLKP(p);
    }

    /* 合并后的插入到空闲链表 */
    insertblock(p, size);
    return p;
}
/* 分离后放入空闲链表 */
static void *place(void *p, size_t size) {
    size_t csize = GET_SIZE(HDRP(p));
    size_t r = csize - size; /* 剩余的大小 */
 
    deleteblock(p);
 
    /* 如果剩余的大小小于最小块，则不分离原块 */
    if (r < DSIZE * 2) {
        PUT(HDRP(p), PACK(csize, 1));
        PUT(FTRP(p), PACK(csize, 1));
    }
    /* 嗯……这个96是试出来的，取96左右甚至是70~120时最优，这样避免小大小大小大的布局 */
    else if (size >= 96) {
        PUT(HDRP(p), PACK(r, 0));
        PUT(FTRP(p), PACK(r, 0));
        PUT(HDRP(NEXT_BLKP(p)), PACK(size, 1));
        PUT(FTRP(NEXT_BLKP(p)), PACK(size, 1));
        insertblock(p, r);
        return NEXT_BLKP(p);
    }
    else {
        PUT(HDRP(p), PACK(size, 1));
        PUT(FTRP(p), PACK(size, 1));
        PUT(HDRP(NEXT_BLKP(p)), PACK(r, 0));
        PUT(FTRP(NEXT_BLKP(p)), PACK(r, 0));
        insertblock(NEXT_BLKP(p), r);
    }
    return p;
}
/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void) {
    int i;
    /* 初始化 */
    for (i = 0; i < MAX_LEN; i++)
        list[i] = NULL;
    /* Create the initial empty heap */
    if ((heap_head = mem_sbrk(4 * WSIZE)) == NULL)
        return -1;
    PUT(heap_head, 0);/* Alignment padding */
    PUT(heap_head + (1 * WSIZE), PACK(DSIZE, 1));/* Prologue header */
    PUT(heap_head + (2 * WSIZE), PACK(DSIZE, 1));/* Prologue footer */
    PUT(heap_head + (3 * WSIZE), PACK(0, 1));/* Epilogue header */
 
    /* Extend the empty heap with a free block of INITCHUNKSIZE bytes */
    if (extend_heap(INITCHUNKSIZE) == NULL)
        return -1;
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size) {
    char *p = NULL;
    /* 不分配直接返回 */
    if (size == 0)
        return NULL;
    /* 已分配块需要脚部，再加上对齐 */
    size = ALIGN(size + DSIZE);
 
    size_t asize = size;
    for (int i = 0; i < MAX_LEN; ++i) {
        /* 找空闲链表find_fit */
        if(asize <= 1 && list[i] != NULL) {
            p = list[i];
            /* 找合适的分配块 */
            while (p != NULL && size > GET_SIZE(HDRP(p)))
                p = SUCC(p);
            if(p != NULL)
                break;
        }
        asize >>= 1;
    }
 
    /* 没有找到合适的未分配块，则扩展堆 */
    if (p == NULL){
        if ((p = extend_heap(MAX(size, CHUNKSIZE))) == NULL)
            return NULL;
    }
    /* 在未分配块中分配size大小的块 */
    p = place(p, size);
 
    return p;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr) {
    size_t size = GET_SIZE(HDRP(ptr));
 
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    insertblock(ptr, size);
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size) {
    void *now = ptr;
    int r;
    /*Ingore spurious requests*/
    if (size == 0)
        return NULL;
    /* 已分配块需要头部和脚部，对齐 */
    size = ALIGN(size + DSIZE);
 
    /* size小于原来块的大小，直接返回 */
    if ((r = GET_SIZE(HDRP(ptr)) - size) >= 0)
        return ptr;
 
    /* 先检查 */
    else if (!GET_ALLOC(HDRP(NEXT_BLKP(ptr))) || !GET_SIZE(HDRP(NEXT_BLKP(ptr)))) {
        /* 扩展块 */
        if ((r = GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(NEXT_BLKP(ptr))) - size) < 0) {
            if (extend_heap(MAX(-r, CHUNKSIZE)) == NULL)
                return NULL;
            r += MAX(-r, CHUNKSIZE);
        }
        /* 删除，设置 */
        deleteblock(NEXT_BLKP(ptr));
        PUT(HDRP(ptr), PACK(size + r, 1));
        PUT(FTRP(ptr), PACK(size + r, 1));
    }
    /* 如申请新的不连续的未分配块 */
    else {
        now = mm_malloc(size);
        memcpy(now, ptr, GET_SIZE(HDRP(ptr)));
        mm_free(ptr);
    }
    return now;
}
static void printblock(void *p) {
    size_t hsize, halloc, fsize, falloc;
 
    hsize = GET_SIZE(HDRP(p));
    halloc = GET_ALLOC(HDRP(p));
    fsize = GET_SIZE(FTRP(p));
    falloc = GET_ALLOC(FTRP(p));
 
    if (hsize == 0) {
	    printf("%p: EOL\n", p);
	    return;
    }
 
    printf("%p: header: [%d:%c] footer: [%d:%c]\n", p, hsize, (halloc ? 'a' : 'f'), fsize, (falloc ? 'a' : 'f'));
}
/*检查堆的一致性*/
void mm_checkheap(int v) {
    char *p = heap_head;
 
    if (v)
	    printf("Heap (%p):\n", heap_head);
 
    if ((GET_SIZE(HDRP(heap_head)) != DSIZE) || !GET_ALLOC(HDRP(heap_head)))
	    printf("Bad prologue header\n");
    checkblock(heap_head);
 
    for (p = heap_head; GET_SIZE(HDRP(p)) > 0; p = NEXT_BLKP(p)) {
	    if (v)
	        printblock(p);
	    checkblock(p);
    }
 
    if (v)
	    printblock(p);
    if ((GET_SIZE(HDRP(p)) != 0) || !(GET_ALLOC(HDRP(p))))
	    printf("Bad epilogue header\n");
}
static void checkblock(void *p) {
    if ((size_t)p % 8)
	    printf("Error: %p is not doubleword aligned\n", p);
    if (GET(HDRP(p)) != GET(FTRP(p)))
	    printf("Error: header does not match footer\n");
}
