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
    int a0, a1, a2, a3,
        b0, b1, b2, b3,
        c0, c1, c2, c3,
        tmp;

    a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
    b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
    c0 = c[0], c1 = c[1], c2 = c[2], c3 = c[3];

    // Full block
    if (!(a0 || b0 || c0) || (a0 && b0 && c0))
        return;

    // Move
    if (!(a0 || b0) || (a0 && b0))
        tmp = b0, b0 = c0, c0 = tmp,
        tmp = b1, b1 = c1, c1 = tmp,
        tmp = b2, b2 = c2, c2 = tmp,
        tmp = b3, b3 = c3, c3 = tmp;

    // Duplicate
    if (a0 < 0 && b0 == 0)
        tmp = a1, a1 = a2, a2 = tmp,
        b0 = -a0, b1 = a3, a0 *= -1,
        b2 = a2 + (a2>0?2:-1),
        a3 = a2 + (a2>0?1:-2),
        b3 = a2 + (a2>0?3:-3);

    // Nothing to do
    if ((a0>0 && !b0 && c0>0)){

        // Passthrough
        if (   (a1 >  0 && c1  < 0)
            || (a1 >  0 && a0 == 1)
            || (c0 == 1 && c1  < 0)){
            tmp = a0, a0 = c0, c0 = tmp,
            tmp = a1, a1 = c1, c1 = tmp,
            tmp = a2, a2 = c2, c2 = tmp,
            tmp = a3, a3 = c3, c3 = tmp;
            a1 *= a1==-c1 || a1==-c2 || a1==-c3 ? -1 : 1;
            a2 *= a2==-c1 || a2==-c2 || a2==-c3 ? -1 : 1;
            a3 *= a3==-c1 || a3==-c2 || a3==-c3 ? -1 : 1;
            c1 *= c1== a1 || c1== a2 || c1== a3 ? -1 : 1;
            c2 *= c2== a1 || c2== a2 || c2== a3 ? -1 : 1;
            c3 *= c3== a1 || c3== a2 || c3== a3 ? -1 : 1;
        };

        // Substitute
        // TODO: clean this mess
        if (c0 == 1 && c1 == -a1){ a1 = c2; c0=c1=c2=c3=0; if (a2 == -a3 && a2 < 0) tmp = a2, a2 = a3, a3 = tmp; if (a1 == -a2) a0=a1=a2=a3=0; };
        if (c0 == 1 && c1 == -a2){ a2 = c2; c0=c1=c2=c3=0; if (a2 == -a3 && a2 < 0) tmp = a2, a2 = a3, a3 = tmp; if (a1 == -a2) a0=a1=a2=a3=0; };
        if (c0 == 1 && c1 == -a3){ a3 = c2; c0=c1=c2=c3=0; if (a2 == -a3 && a2 < 0) tmp = a2, a2 = a3, a3 = tmp; if (a1 == -a2) a0=a1=a2=a3=0; };
        if (a0 == 1 && a1 == -c1){ c1 = a2; a0=a1=a2=a3=0; if (c2 == -c3 && c2 < 0) tmp = c2, c2 = c3, c3 = tmp; if (c1 == -c2) c0=c1=c2=c3=0; };
        if (a0 == 1 && a1 == -c2){ c2 = a2; a0=a1=a2=a3=0; if (c2 == -c3 && c2 < 0) tmp = c2, c2 = c3, c3 = tmp; if (c1 == -c2) c0=c1=c2=c3=0; };
        if (a0 == 1 && a1 == -c3){ c3 = a2; a0=a1=a2=a3=0; if (c2 == -c3 && c2 < 0) tmp = c2, c2 = c3, c3 = tmp; if (c1 == -c2) c0=c1=c2=c3=0; };

        // React
        if (a0 > 1 && c0 > 1 && a1 == -c1){
            if (a0 == c0)
                a0 = 1, a1 = a2, a2 = c2,
                c0 = 1, c1 = a3, c2 = c3,
                a3 = 0, c3 = 0;
            else
                tmp = a0, a0 = c0, c0 = tmp,
                a0 *= -1,
                c0 *= -1,
                a1 = (a1*1103515245+12345)&0x7fffffff, // PRNG
                c1 = -a1;
        };
    }

    a[0] = a0, a[1] = a1, a[2] = a2, a[3] = a3;
    b[0] = b0, b[1] = b1, b[2] = b2, b[3] = b3;
    c[0] = c0, c[1] = c1, c[2] = c2, c[3] = c3;
};

__host__ __device__ void tick(int *mem, int total_nodes){
    for (int j=0; j<3; ++j)
        for (int i=j; i<total_nodes-2; i+=3)
            rewrite(mem+i*4, mem+i*4+4, mem+i*4+8);
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
