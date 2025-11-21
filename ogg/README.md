# Code base

Directory `./ogg` downloaded from [Github:xiph/ogg](https://github.com/xiph/ogg) on August 13, 2025, unchanged. Commit id: 0288fadac3ac62d453409dfc83e9c4ab617d2472

# How to use SACTOR to translate `ogg`

1. Install build tools and configure build of `ogg` until you can build and pass all test cases by running command line `make test` in `./ogg/src`. See README of `ogg`. 

1. Produce C object files for test cases: 
    ```bash
    cd ./ogg/src

    gcc -DHAVE_CONFIG_H -I. -I..  -I../include -I../include  -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -O2 -c -o ../../test_bitwise.o ../../test_bitwise.c -Og -g

    gcc -DHAVE_CONFIG_H -I. -I..  -I../include -I../include  -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -O2 -c -o ../../test_framing.o ../../test_framing.c -Og -g
    ```
    Note: refer to output of command `make build` running in `./ogg/src` about compiling `framing.c` and `bitwise.c` for respective compiler flags but the last two `-Og -g` should be added regardless.

1. Run SACTOR for each source file:
    ```bash
    cd ./ogg/src

    sactor translate framing.c ../../test_task.json -r ../sactor_result_framing --type lib -e ../../test_framing.o -a "gcc -DHAVE_CONFIG_H -I. -I..  -I../include -I../include  -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -O2 -MT test_framing-framing.o -MD -MP -MF .deps/test_framing-framing.Tpo -c -o test_framing-framing.o `test -f 'framing.c' || echo './'`framing.c
    /bin/bash ../libtool  --tag=CC   --mode=link gcc -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -O2   -o test_framing test_framing-framing.o" 

    sactor translate bitwise.c ../../test_task.json -r ../sactor_result_bitwise --type lib -e ../../test_bitwise.o --idiomatic-only -a "gcc -DHAVE_CONFIG_H -I. -I..  -I../include -I../include  -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -O2 -c -o test_bitwise-bitwise.o `test -f 'bitwise.c' || echo './'`bitwise.c
    /bin/bash ../libtool  --tag=CC   --mode=link gcc -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -O2   -o test_bitwise test_bitwise-bitwise.o"
    ```

    Note: The -a argument should be verbatim from your `make build` output for compiling and linking the respective C source file. 

# Translation

Directory `./translation` is the Rust code translated to by SACTOR.

# Generate coverage info

```bash
# script to generate libogg's coverage info
cd ogg/src
gcc -DHAVE_CONFIG_H -I. -I..  -I../include -I../include  -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -Og --coverage -MT test_framing-framing.o -MD -MP -MF .deps/test_framing-framing.Tpo -c -o test_framing-framing.o `test -f 'framing.c' || echo './'`framing.c
/bin/bash ../libtool  --tag=CC   --mode=link gcc -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -Og --coverage -o test_framing test_framing-framing.o
./test_framing

gcc -DHAVE_CONFIG_H -I. -I..  -I../include -I../include  -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -Og --coverage -c -o test_bitwise-bitwise.o `test -f 'bitwise.c' || echo './'`bitwise.c
/bin/bash ../libtool  --tag=CC   --mode=link gcc -D_V_SELFTEST -O2 -Wall -Wextra -ffast-math -fsigned-char -g -Og --coverage -o test_bitwise test_bitwise-bitwise.o
./test_bitwise

lcov --capture --directory ./ --output-file ../build/coverage.info
# we only include non-test code in the result
genhtml --erase-functions '\w*test\w*|main|ilog|report|checkpacket|check_page|print_header|copy_page|error|compare_packet|free_page' ../build/coverage.info --output-directory ../coverage
```
Again, the compiler flags should be adjusted by `make build` output from your computer.