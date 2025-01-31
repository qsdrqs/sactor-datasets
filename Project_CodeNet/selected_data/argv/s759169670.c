#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
        int l=0;
        long l3=0;
        double v=0.0;
        if(argc<2) return 1;
        l=atoi(argv[1]);
        l3 = l*l*l;
        v = l3/27.0;
        printf("%.12lf\n", v);
        return 0;
}
