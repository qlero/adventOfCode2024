#~/bin/bash
(echo $1 && find $WORKSPACE -mindepth 2 -name "*.c") | xargs --no-run-if-empty gcc -o ./build/main
./build/main