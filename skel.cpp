// https://blog.csdn.net/u013407012/article/details/80671402
#include "trace_skeleton.h"

void chr_op()
{
    uchar a = 0;
    uchar b = 1;
    uchar c = 2;
    uchar uand = a & b;  // 0
    uchar aand1 = a & 1; // 0
    uchar band1 = b & 1; //1
    uchar cand1 = c & 1; // 0
    uchar aor1 = a | 1;  // 1
    uchar bor1 = b | 1;  // 1
    uchar cor1 = c | 1;  //3
}

void int_op()
{
    uchar a = 0;
    uchar b = 1;
    uchar c = 2;
    uchar d = 3;
    uchar uand = a & b; // 0
    int aand1 = a & 1;  // 0
    int band1 = b & 1;  //1
    int cand1 = c & 1;  // 0
    int aor1 = a | 1;   // 1
    int bor1 = b | 1;   // 1
    int cor1 = c | 1;   //3
    int aor2 = a | 2;   // 2
    int bor2 = b | 2;   // 3
    int cor2 = c | 2;   //2
    int armv = a >> 1;
    int brmv = b >> 1;
    int crmv = c >> 1;
    int drmv = d >> 1;
}

int main()
{
    typedef SkelTracer::Polyline Polyline;
    SkelTracer *T = new SkelTracer;

    // Polyline *ln0 = new Polyline;
    // Polyline *ln1 = new Polyline;
    // Polyline *ln2 = new Polyline;
    // ln0->push_back({0, 0});
    // ln0->push_back({1, 0});

    // ln1->push_back({2, 0});
    // ln1->push_back({3, 0});
    // ln1->push_back({4, 0});

    // ln2->push_back({5, 0});
    // ln2->push_back({6, 0});

    // Polyline *c1 = T->prepend_polyline(ln1, ln0);
    // cout << c1;
    // Polyline *c0 = ln2;

    // c0 = T->merge_frags(c0, c1, 4, 1);

    T->fill_H();

    print(T->im, T->W, T->H);
    T->thinning_zs();
    printf("-------------------------\n");
    print(T->im, T->W, T->H);
    printf("-------------------------\n");
    T->print_stat();
    T->trace_skeleton(0, 0, T->W, T->H, 0);

    delete T;
    return 0;
}