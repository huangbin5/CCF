/**
 * default_init_memmap
 * default_alloc_pages
 * default_free_pages
 */

typedef struct {
    list_entry_t free_list; // the list header
    unsigned int nr_free; // # of free pages in this free list
} free_area_t;

struct Page {
    int ref; // 映射此物理页的虚拟页个数
    uint32_t flags; // 物理页属性（空或不空）
    unsigned int property; // 连续空页有多少(只在地址最低页有值，其余为0)
    list_entry_t page_link; // 双向链接各个Page结构的page_link双向链表(用于释放)
};

static void default_init_memmap(struct Page* base, size_t n) {
    assert(n > 0);
    struct Page* p = base;
    for (; p != base + n; p++) {
        //检查此页是否为保留页
        assert(PageReserved(p));
        //设置标志位
        p->flags = p->property = 0;
        SetPageProperty(p);
        //清零此页的引用计数
        set_page_ref(p, 0);
        //将空闲页插入到链表
        list_add_before(&free_list, &(p->page_link));
    }
    base->property = n;
    //计算空闲页总数
    nr_free += n;
}

static struct Page* default_alloc_pages(size_t n) {
    assert(n > 0);
    if (n > nr_free) {
        return NULL;
    }
    list_entry_t* len;
    list_entry_t* le = &free_list;
    //在空闲链表中寻找合适大小的页块
    while ((le = list_next(le)) != &free_list) {
        struct Page* p = le2page(le, page_link);
        //找到了合适大小的页块
        if (p->property >= n) {
            int i;
            for (i = 0; i < n; i++) {
                len = list_next(le);
                //让pp指向分配的那一页
                // le2page宏可以根据链表元素获得对应的Page指针p
                struct Page* pp = le2page(temp_le, page_link);
                //设置每一页的标志位
                SetPageReserved(pp);
                ClearPageProperty(pp);
                //清除free_list中的链接
                list_del(le);
                le = len;
            }
            if (p->property > n) {
                //分割的页需要重新设置空闲大小
                (le2page(le, page_link))->property = p->property - n;
            }
            //第一页重置标志位
            ClearPageProperty(p);
            SetPageReserved(p);
            nr_free -= n;
            return p;
        }
    }
    //否则分配失败
    return NULL;
}

static void default_free_pages(struct Page* base, size_t n) {
    assert(n > 0);
    assert(PageReserved(base));
    struct Page* p = base;
    //查找该插入的位置le
    list_entry_t* le = &free_list;
    while ((le = list_next(le)) != &free_list) {
        p = le2page(le, page_link);
        if (p > base)
            break;
    }
    //向le之前插入n个页（空闲），并设置标志位
    for (p = base; p < base + n; p++) {
        list_add_before(le, &(p->page_link));
        p->flags = 0;
        set_page_ref(p, 0);
        ClearPageProperty(p);
        SetPageProperty(p);
    }
    //将页块信息记录在头部
    base->property = n;
    //是否需要合并
    //向高地址合并
    p = le2page(le, page_link);
    if (base + n == p) {
        base->property += p->property;
        list_del(&(p->page_link));
    }
    //向低地址合并
    le = list_prev(&(base->page_link));
    p = le2page(le, page_link);
    //若低地址已分配则不需要合并
    if (le != &free_list && p == base - 1) {
        while (le != &free_list) {
            if (p->property) {
                p->property += base->property;
                base->property = 0;
                break;
            }
            le = list_prev(le);
            p = le2page(le, page_link);
        }
    }
    nr_free += n；
}