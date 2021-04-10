#! /bin/sh
make clean && make
echo ""
for I in 1 2 3 4 5 6 
do
    printf "TEST $I "
	./proj < tests/T0$I/input > out
    if cmp -s "out" "tests/T0$I/output"; then
        tput setaf 2; echo "PASSED"
        tput sgr0;
	else
        tput setaf 1; echo "FAILED"
        tput sgr0;
        if [ ! "$1" != "-d" ]; then
            diff out tests/T0$I/output
        fi
    fi
    echo ""
done