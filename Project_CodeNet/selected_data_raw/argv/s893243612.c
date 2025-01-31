#include <stdio.h>

int    main(int argc, char *argv[])
{
    int x;
    int ans;

    if(2 == argc)
    {
        if(argv[1][0] == '1' && argv[1][1] == '0')
        {
            printf("%d",1110);
        }
        else if(argv[1][0] > '0' && argv[1][0] <= '9' && argv[1][1] == '\0')
        {
            x = (argv[1][0]) - 48;
            ans = x + (x * x) + (x * x * x);
            printf("%d",ans);
        }
        return (0);
    }
    return (0);
}