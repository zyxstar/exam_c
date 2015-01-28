#include <stdio.h>
#include <unistd.h>

typedef long Align;

union header{
    struct{
        union header *ptr; //空闲块链表的的下一块
        unsigned size; //本块的大小 (单位为sizeof(Header))
    } s;
    Align x; //强制块的对齐
};

typedef union header Header;

static Header base; //空链表开始
static Header *freep = NULL; //空闲链表的初始指针

void *malloc(unsigned nbytes){
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if((prevp = freep) == NULL) { //没有空闲链表
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for(p = prevp->s.ptr; ;prevp = p, p = p->s.ptr){
        if(p->s.size >= nunits){//空间够大
            if(p->s.size == nunits) //空间正好
                prevp->s.ptr = p->s.ptr;
            else{ //分配末尾部分
                p->s.size -= nunits; //前半部分头 修改数据
                p += p->s.size;
                p->s.size = nunits; //后半部分头 修改数据
            }
            freep = prevp;
            return (void *)(p + 1); //返回的是除去头接点的空间首地址
        }
        if(p == freep) //闭环了 未找到合适空间
            if((p = morecore(nunits)) == NULL) //申请空间，进入下面循环
                return NULL;
    }
}

#define NALLOC 1024

// 向系统申请更多的存储空间
Header *morecore(unsigned nu){
    char *cp;
    Header *up;
    void free(void *);

    if(nu < NALLOC) nu = NALLOC; // 最小分配1024
    cp = sbrk(nu * sizeof(Header));
    if(cp == (char *)-1) // 没有空间
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up + 1)); //空闲空间插入
    return freep;
}

//将块ap放入空闲块链表中
void free(void *ap){
    Header *bp, *p;

    bp = (Header *)ap -1; //指向块头
    for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr){
        if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; //被释放在块在链表的开头或末尾
    }

    if(bp + bp->s.size == p->s.ptr){ // 与上一相邻合并
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;

    if(p + p->s.size == bp){ // 与下一相邻合并
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;

    freep = p;

}

int main(int argc, const char* argv[]){

    char *str1 = malloc(10);
    char *str2 = malloc(20);
    free(str2);

    return 0;
}

// gcc chp8_malloc.c -o chp8_malloc.out && ./chp8_malloc.out
