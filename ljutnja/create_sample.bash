for i in {1..100000}; do echo $(( 1 + RANDOM % 2000000000 )) >> sample3.txt; done