 #include <stdio.h>                                                                              

 int main(int argc, char *argv[])
 {
    if (argv[1][0] == 'A' && argv[1][1] == 'A' && argv[1][2] == 'A')
       printf("No\n");
    else if (argv[1][0] == 'B' && argv[1][1] == 'B' && argv[1][2] == 'B')
       printf("No\n");
    else
       printf("Yes\n");
    return (0);
}
