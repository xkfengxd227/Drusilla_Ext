#!/bin/bash
make
rm *.o

# ------------------------------------------------------------------------------
#  Parameters
# ------------------------------------------------------------------------------
dname=Mnist
n=59000
qn=1000
d=50
B=4096
dPath=./data/${dname}/${dname}
dFolder=./data/${dname}/

# ------------------------------------------------------------------------------
#  Running Scripts
# ------------------------------------------------------------------------------
l=16
m=18
oFolder=./results2.0/${dname}/drusilla/${l}-${m}/

./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds \
  -df ${dFolder} -of ${oFolder}

./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}.fn2.0 \
  -df ${dFolder} -of ${oFolder}
