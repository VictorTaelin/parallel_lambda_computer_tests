__host__ __device__ void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

__host__ __device__ void swap4(int* a, int* b){
    for (int i=0; i<4; ++i)
        swap(a+i, b+i);
};

__host__ __device__ void erase(int* a){
    for (int i=0; i<4; ++i)
        a[i] = 0;
};

// Rewrites 3 memory nodes based on interaction rules
__host__ __device__ void rewrite(int* a, int* b, int* c){
    // Full block
    if (!(a[0] || b[0] || c[0]) || (a[0] && b[0] && c[0]))
        return;

    // Move
    if (!(a[0] || b[0]) || (a[0] && b[0]))
        swap4(&b[0], &c[0]);

    // Duplicate
    if (a[0] < 0 && b[0] == 0)
        swap(&a[1], &a[2]),
        b[0] = -a[0], b[1] = a[3], a[0] *= -1,
        b[2] = a[2] + (a[2]>0?2:-1),
        a[3] = a[2] + (a[2]>0?1:-2),
        b[3] = a[2] + (a[2]>0?3:-3);

    // Nothing to do
    if (!(a[0]>0 && !b[0] && c[0]>0))
        return;

    // Passthrough
    if (   (a[1] >  0 && c[1]  < 0)
        || (a[1] >  0 && a[0] == 1)
        || (c[0] == 1 && c[1]  < 0)){
        swap4(a, c);
        for (int i=1; i<=3; ++i)
            a[i] *= a[i]==-c[1] || a[i]==-c[2] || a[i]==-c[3] ? -1 : 1;
        for (int i=1; i<=3; ++i)
            c[i] *= c[i]== a[1] || c[i]== a[2] || c[i]== a[3] ? -1 : 1;
    };

    // Substitute
    for (int n=0; n<2; ++n){
        int* x = n ? c : a;
        int* y = n ? a : c;
        for (int i=1; i<=3; ++i){
            if (x[0] == 1 && x[1] == -y[i]){
                y[i] = x[2];
                erase(x);
                if (y[2] == -y[3] && y[2] < 0)
                    swap(&y[2], &y[3]);
                if (y[1] == -y[2])
                    erase(y);
            };
        };
    };

    // React
    if (a[0] > 1 && c[0] > 1 && a[1] == -c[1]){
        if (a[0] == c[0])
            a[0] = 1, a[1] = a[2], a[2] = c[2],
            c[0] = 1, c[1] = a[3], c[2] = c[3],
            a[3] = 0, c[3] = 0;
        else
            swap(a, c),
            a[0] *= -1,
            c[0] *= -1,
            a[1] = (a[1]*1103515245+12345)&0x7fffffff, // PRNG
            c[1] = -a[1];
    };
};

// Debug pretty print of a slice of the memory state
void print(int *S, int len){
    for (int j=0; j<4; ++j){
        for (int i=j; i<len*4; i+=4){
                 if (!j && S[i]<-1) printf("DD|");
            else if (!j && S[i]==1) printf("%%%%|");
            else if (S[i]>0) printf("%02x>", S[i]%256);
            else if (S[i]<0) printf("%02x<", (-S[i])%256);
            else if (j<3) printf("  |");
            else printf("__|");
        };
        printf("\n");
    };
};
