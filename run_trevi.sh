#!/bin/bash
make
rm *.o


n=99900
d=4096
B=65536
dname=Trevi

qn=1000
c=2.0
dPath=./data/${dname}/${dname}
dFolder=./data/${dname}/

./drusilla -alg 0 -n ${n} -qn ${qn} -d ${d} -ds ${dPath}.ds -qs ${dPath}.q -ts ${dPath}ID.fn2.0


################################################################################
l=2
m=15
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=3
m=10
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=5
m=6
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=6
m=5
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=10
m=3
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=15
m=2
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}



