#!/bin/bash
make
rm *.o


n=999000
d=128
B=4096
dname=Sift

qn=1000
c=2.0
dPath=./data/${dname}/${dname}
dFolder=./data/${dname}/

./drusilla -alg 0 -n ${n} -qn ${qn} -d ${d} -ds ${dPath}.ds -qs ${dPath}.q -ts ${dPath}ID.fn2.0


################################################################################
l=2
m=66
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=3
m=44
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=4
m=33
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=6
m=22
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=11
m=12
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=12
m=11
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=22
m=6
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=33
m=4
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=44
m=3
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


################################################################################
l=66
m=2
oFolder=./results/${dname}/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds -df ${dFolder} -of ${oFolder}
./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}ID.fn2.0 -df ${dFolder} -of ${oFolder}


