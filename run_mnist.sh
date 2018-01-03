#!/bin/bash
make
rm *.o


n=59000
qn=1000
d=50
B=4096
l=16
m=18
c=2.0
dname=Mnist

dPath=./data/${dname}/${dname}
dFolder=./data/${dname}/
oFolder=./results/${dname}/${l}-${m}/

# ground truth
./drusilla -alg 0 -n ${n} -qn ${qn} -d ${d} -ds ${dPath}.ds -qs ${dPath}.q -ts ${dPath}ID.fn2.0

# indexing
./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}

# drusilla select
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}
