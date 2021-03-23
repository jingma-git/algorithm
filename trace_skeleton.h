#pragma once
#include <cstdlib>
#include <climits>
#include <cstring>
#include <iostream>

using namespace std;

typedef unsigned char uchar;

inline void print(uchar *im, int W, int H)
{
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            int idx = i * W + j;
            // printf("%c", im[idx] == 2 ? '.' : (im[idx] == 0 ? ' ' : '@'));
            if (im[idx] == 0)
            {
                printf("%c", ' ');
            }
            else
            {
                printf("%d", im[idx]);
            }
        }
        printf("\n");
    }
}

struct SkelTracer
{

    struct Point
    {
        int x, y;
        Point *next;

        Point()
        {
            next = NULL;
        }

        Point(int x_, int y_) : x(x_), y(y_)
        {
            next = NULL;
        }

        Point(const Point &p)
        {
            x = p.x;
            y = p.y;
            next = p.next;
        }

        friend std::ostream &operator<<(std::ostream &out, const Point &p)
        {
            out << "(" << p.x << "," << p.y << ")";
            return out;
        }
    };

    struct Polyline
    {
        Polyline()
        {
            head = NULL;
            tail = NULL;
            prev = NULL;
            next = NULL;
            size = 0;
        }

        ~Polyline()
        {
            Point *it = head;
            while (it)
            {
                Point *nxt = it->next;
                delete it;
                it = nxt;
            }
        }

        Polyline(const Polyline &other)
        {
            head = other.head;
            tail = other.tail;
            prev = other.prev;
            next = other.next;
            size = other.size;
        }

        Polyline &operator=(const Polyline &other)
        {
            head = other.head;
            tail = other.tail;
            prev = other.prev;
            next = other.next;
            size = other.size;
            return *this;
        }

        void push_back(Point point)
        {
            Point *p = new Point(point);
            if (!head)
            {
                head = p;
                tail = p;
            }
            else
            {
                tail->next = p;
                tail = p;
            }
            size++;
        }

        friend void reverse(Polyline *ln)
        {
            if (ln->size <= 1)
                return;

            // when doing modification for 'pointers', syntax order is extremely important!!!
            Point *first_tmp = ln->head;
            Point *v0 = ln->head;
            Point *v1 = v0->next;
            Point *v2 = v1->next;
            while (1)
            {
                v1->next = v0;

                if (!v2)
                    break;

                v0 = v1;
                v1 = v2;
                v2 = v2->next;
            }

            first_tmp->next = NULL;
            ln->head = v1;
        }

        // concat ln1 to the end of ln0
        friend void cat_tail(Polyline *ln0, Polyline *ln1)
        {
            if (!ln1)
                return;
            if (!ln0)
            {
                ln0 = new Polyline();
            }
            if (!ln0->head)
            {
                ln0->head = ln1->head;
                ln0->tail = ln1->tail;
                return;
            }

            ln0->tail->next = ln1->head;
            ln0->size += ln1->size;
        }

        // concat ln1 to the head of ln0
        friend void cat_head(Polyline *ln0, Polyline *ln1)
        {
            if (!ln1)
                return;
            if (!ln0)
                ln0 = new Polyline();

            if (!ln0->head)
            {
                ln0->head = ln1->head;
                ln0->tail = ln1->tail;
                return;
            }

            ln1->tail->next = ln0->head;
            ln0->head = ln1->head;
            ln0->size += ln1->size;
        }

        friend std::ostream &operator<<(std::ostream &out, const Polyline &ln)
        {
            Point *it = ln.head;
            while (it)
            {
                out << (*it) << " ";
                it = it->next;
            }
            out << endl;
            return out;
        }

        friend std::ostream &operator<<(std::ostream &out, Polyline *lns)
        {
            Polyline *it = lns;
            while (it)
            {
                out << (*it);
                it = it->next;
            }
            return out;
        }

        Point *head;
        Point *tail;
        Polyline *prev;
        Polyline *next;
        int size;
    };

    struct Rect
    {
        int x;
        int y;
        int w;
        int h;
        Rect *next;
    };

    struct Rects
    {
        Rect *head;
        Rect *tail;
    };

    void fill_H()
    {
        int pad = 2;
        int hl = 6;  // horizontal middle line width
        int ht = 4;  // horizontal middle line thickness
        int leg = 6; // H's four legs

        W = (hl + 2) * 2 + hl + 2 * pad;
        H = leg * 2 + ht + 2 * pad;
        im = new uchar[W * H]; // allocate memory and call the constructor if it is a class
                               // uchar *im = (uchar *)malloc(sizeof(uchar) * W * H);
                               // for primitive type, new==malloc
        memset(im, 0, sizeof(im));
        for (int i = 0; i < H; i++)
        {
            if (i < pad || i >= (H - pad))
                continue;

            for (int j = 0; j < W; j++)
            {
                int idx = i * W + j;
                if (i < (leg + pad) || i >= (leg + ht + pad))
                {
                    if (j >= pad && j < (hl + pad + 2))
                        im[idx] = 1;
                    if (j >= (hl + pad + 2 + hl) && j < (W - pad))
                        im[idx] = 1;
                }
                else
                {
                    if (j >= pad && j < W - pad)
                    {
                        im[idx] = 1;
                    }
                }
            }
        }
    }

    void print_stat()
    {
        printf("----Statistic\n");
        for (int i = 0; i < H; i++)
        {
            int s = 0;
            for (int j = 0; j < W; j++)
            {
                s += im[i * W + j];
            }
            printf("row%d #pixels=%d\n", i, s);
        }
        printf("\n");
        for (int j = 0; j < W; j++)
        {
            int s = 0;
            for (int i = 0; i < H; i++)
            {
                s += im[i * W + j];
            }
            printf("col%d #pixels=%d\n", j, s);
        }
        printf("\n");
    }

    void destroy_polylines(Polyline *q)
    {
        if (!q)
        {
            return;
        }
        Polyline *it = q;
        while (it)
        {
            Polyline *lt = it->next;
            delete it;
            it = lt;
        }
    }

    // add ln1 before ln0
    Polyline *prepend_polyline(Polyline *ln0, Polyline *ln1)
    {
        if (!ln0)
            return ln1;
        ln1->next = ln0;
        ln0->prev = ln1;
        return ln1;
    }

    bool thinning_subiter(int iter)
    {
        bool diff = false;
        for (int i = 1; i < H - 1; i++)
        {
            for (int j = 1; j < W - 1; j++)
            { // could be paralleled

                int idx = i * W + j;

                int p2 = im[(i - 1) * W + j] & 1;
                int p3 = im[(i - 1) * W + (j + 1)] & 1;
                int p4 = im[i * W + (j + 1)] & 1;
                int p5 = im[(i + 1) * W + (j + 1)] & 1;
                int p6 = im[(i + 1) * W + j] & 1;
                int p7 = im[(i + 1) * W + (j - 1)] & 1;
                int p8 = im[i * W + (j - 1)] & 1;
                int p9 = im[(i - 1) * W + (j - 1)] & 1;

                int A = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
                int B = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
                        (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                        (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                        (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
                int C = (iter == 0) ? p2 * p4 * p6 : p2 * p4 * p8;
                int D = (iter == 0) ? p4 * p6 * p8 : p2 * p6 * p8;

                if ((A >= 2 && A <= 6) && B == 1 && C == 0 && D == 0)
                {
                    im[idx] |= 2; // 1|2==3 0|2==2
                }
            }
        }

        // printf("-----------iter%d-------------\n", iter);
        // print(im, W, H);
        // printf("\n");
        for (int i = 0; i < H * W; i++)
        {
            int marker = im[i] >> 1; // 0>>2==0 1>>2==0 2>>2==1 3>>2==1
            int old = im[i] & 1;     // 0&1==0 1&1==1 2&1==0 3&1==1
            im[i] = old & (!marker);
            if (!diff && (im[i] != old))
            {
                diff = true;
            }
        }
        // print(im, W, H);
        // printf("\n");
        return diff;
    }

    void thinning_zs()
    {
        int diff = 0;
        do
        {
            diff = thinning_subiter(0);
            diff = thinning_subiter(1);
        } while (diff);
    }

    Polyline *chunk_to_frags(int x, int y, int w, int h)
    {
        Polyline *frags = NULL;
        int fsize = 0;
        int on = 0; // to deal with strokes thicker than 1px
        int li = -1, lj = -1;

        // walk around the edge clockwise
        for (int k = 0; k < h + h + w + w - 4; k++)
        {
            int i, j;
            if (k < w)
            {
                i = y + 0;
                j = x + k;
            }
            else if (k < w + h - 1)
            {
                i = y + k - w + 1;
                j = x + w - 1;
            }
            else if (k < w + h + w - 2)
            {
                i = y + h - 1;
                j = x + w - (k - w - h + 3);
            }
            else
            {
                i = y + h - (k - w - h - w + 4);
                j = x + 0;
            }
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }

    Polyline *trace_skeleton(int x, int y, int w, int h, int iter)
    {
        Polyline *frags = NULL;
        Polyline *frags0 = NULL;
        Polyline *frags1 = NULL;
        if (iter > MAX_ITER)
        {
            return frags;
        }

        if (w <= CHUNK_SIZE && h <= CHUNK_SIZE)
        { // recursive bottom
            frags = chunk_to_frags(x, y, w, h);
            return frags;
        }

        int ms = INT_MAX;
        int mi = -1;
        int mj = -1;

        if (h > CHUNK_SIZE)
        { // try splitting top and bottom
            for (int i = y + 3; i < y + h - 3; i++)
            {
                if (im[i * W + x] || im[(i - 1) * W + x] || im[i * W + x + w - 1] || im[(i - 1) * W + x + w - 1])
                {
                    continue;
                }
                int s = 0;
                for (int j = x; j < x + w; j++)
                {
                    s += im[i * W + j];
                    s += im[(i - 1) * W + j];
                }
                if (s < ms)
                {
                    ms = s;
                    mi = i;
                }
                else if (s == ms && abs(i - (y + h / 2)) < abs(mi - (y + h / 2)))
                {
                    // if there is a draw (very common), we want the seam to be near the middle
                    // to balance the divide and conquer tree
                    ms = s;
                    mi = i;
                }
            }
        }
        if (w > CHUNK_SIZE)
        { // same as above, try splitting left and right
            for (int j = x + 3; j < x + w - 3; j++)
            {
                if (im[W * y + j] || im[W * (y + h) - W + j] || im[W * y + j - 1] || im[W * (y + h) - W + j - 1])
                {
                    continue;
                }
                int s = 0;
                for (int i = y; i < y + h; i++)
                {
                    s += im[i * W + j] ? 1 : 0;
                    s += im[i * W + j - 1] ? 1 : 0;
                }

                if (s < ms)
                {
                    ms = s;
                    mi = -1; // horizontal seam is defeated
                    mj = j;
                }
                else if (s == ms && abs(j - (x + w / 2)) < abs(mj - (x + w / 2)))
                {
                    ms = s;
                    mi = -1;
                    mj = j;
                }
            }
        }

        int L0 = -1;
        int L1;
        int L2;
        int L3;
        int R0 = -1;
        int R1;
        int R2;
        int R3;
        int dr = 0;
        int sx;
        if (h > CHUNK_SIZE && mi != -1)
        { // split top and bottom
            L0 = x;
            L1 = y;
            L2 = w;
            L3 = mi - y;
            R0 = x;
            R1 = mi;
            R2 = w;
            R3 = y + h - mi;
            dr = VERTICAL;
            sx = mi;
        }
        else if (w > CHUNK_SIZE && mj != -1)
        { // split left and right
            L0 = x;
            L1 = y;
            L2 = mj - x;
            L3 = h;
            R0 = mj;
            R1 = y;
            R2 = x + w - mj;
            R3 = h;
            dr = HORIZONTAL;
            sx = mj;
        }

        cout << "mi=" << mi << " mj=" << mj << " sx=" << sx << endl;

        if (dr != 0 && not_empty(L0, L1, L2, L3))
        { // if there are no white pixels, don't waste time
            frags0 = trace_skeleton(L0, L1, L2, L3, iter + 1);
        }

        if (dr != 0 && not_empty(R0, R1, R2, R3))
        {
            frags1 = trace_skeleton(R0, R1, R2, R3, iter + 1);
            frags = merge_frags(frags0, frags1, sx, dr);
        }

        return frags;
    }
    // check if a region has any white pixel
    int not_empty(int x, int y, int w, int h)
    {
        for (int i = y; i < y + h; i++)
        {
            for (int j = x; j < x + w; j++)
            {
                if (im[i * W + j])
                {
                    return 1;
                }
            }
        }
        return 0;
    }

    int merge_impl(Polyline *c0, Polyline *c1i, int sx, int isv, int mode)
    {
        int b0 = (mode >> 1 & 1) > 0; // match c0 left
        int b1 = (mode >> 0 & 1) > 0; // match c1 left

        int md = 4; // maximum offset to be regarded as continuous

        Point *p1 = b1 ? c1i->head : c1i->tail;
        if (abs((isv ? p1->y : p1->x) - sx) > 0)
        {
            return 0;
        }
        cout << mode << " b0=" << b0 << " b1=" << b1 << " p1=" << *p1 << endl;

        // find best match
        Polyline *c0j = NULL;
        Polyline *it = c0;
        while (it)
        {
            Point *p0 = b0 ? (it->head) : (it->tail);
            if (abs((isv ? (p0->y) : (p0->x)) - sx) > 1)
            { // not on the seam, skip
                it = it->next;
                continue;
            }
            cout << "p0=" << (*p0) << endl;
            int d = abs((isv ? (p0->x) : (p0->y)) - (isv ? (p1->x) : (p1->y)));
            if (d < md)
            {
                c0j = it;
                md = d;
            }
            it = it->next;
        }

        if (c0j)
        {
            if (b0 && b1)
            {
                reverse(c1i);
                cat_head(c0j, c1i);
            }
            else if (!b0 && b1)
            {
                cat_tail(c0j, c1i);
            }
            else if (b0 && !b1)
            {
                cout << "cat_head" << endl;
                cat_head(c0j, c1i);
                cout << c0j << endl;
            }
            else
            {
                reverse(c1i);
                cat_tail(c0j, c1i);
            }
            return 1;
        }
        return 0;
    }

    Polyline *merge_frags(Polyline *c0, Polyline *c1, int sx, int dr)
    {
        if (!c0)
        {
            return c1;
        }
        if (!c1)
        {
            return c0;
        }

        Polyline *it = c1;
        while (it)
        {
            Polyline *tmp = it->next;

            if (dr == HORIZONTAL)
            {
                if (merge_impl(c0, it, sx, 0, 1))
                    goto rem;
                if (merge_impl(c0, it, sx, 0, 3))
                    goto rem;
                if (merge_impl(c0, it, sx, 0, 0))
                    goto rem;
                if (merge_impl(c0, it, sx, 0, 2))
                    goto rem;
            }
            else
            {
                if (merge_impl(c0, it, sx, 1, 1))
                    goto rem;
                if (merge_impl(c0, it, sx, 1, 3))
                    goto rem;
                if (merge_impl(c0, it, sx, 1, 0))
                    goto rem;
                if (merge_impl(c0, it, sx, 1, 2))
                    goto rem;
            }

            goto next;
        rem:
            cout << "selected it" << endl;
            cout << (*it) << endl;
            if (!it->prev)
            {
                c1 = it->next;
                if (it->next)
                {
                    it->next->prev = NULL;
                }
            }
            else
            {
                // delete merged polyline
                it->prev->next = it->next;
                if (it->next)
                {
                    it->next->prev = it->prev;
                }
            }
            delete it;
        next:
            it = tmp;
        }

        it = c1;
        cout << "c1" << endl;
        cout << c1 << endl;
        while (it)
        {
            Polyline *tmp = it->next;
            it->prev = NULL;
            it->next = NULL;
            c0 = prepend_polyline(c0, it);
            it = tmp;
        }
        cout << "c0" << endl;
        cout << c0 << endl;
        return c0;
    }

    SkelTracer()
    {
        im = NULL;
        rects.head = NULL;
        rects.tail = NULL;
    }

    ~SkelTracer()
    {
        if (im)
        {
            delete im;
            im = NULL;
        }
    }

    int HORIZONTAL = 1;
    int VERTICAL = 2;

    int CHUNK_SIZE = 10; // the chunk size
    int SAVE_RECTS = 1;  // additionally save bounding rects of chunks (for visualization)
    int MAX_ITER = 999;  // maximum number of iterations

    uchar *im; // the image
    int W;     // width
    int H;     // height
    Rects rects;
};