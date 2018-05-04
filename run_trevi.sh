#!/bin/bash
make
rm *.o

# ------------------------------------------------------------------------------
#  Parameters
# ------------------------------------------------------------------------------
dname=Trevi
n=99900
qn=1000
d=4096
B=65536
dPath=./data/${dname}/${dname}
dFolder=./data/${dname}/

# ------------------------------------------------------------------------------
#  Running Scripts
# ------------------------------------------------------------------------------
L_list=(2 3 5 6 10 15) 
M_list=(15 10 6 5 3 2)
length=`expr ${#L_list[*]} - 1`

for j in $(seq 0 ${length})
do 
  l=${L_list[j]}
  m=${M_list[j]}
  oFolder=./results2.0/${dname}/drusilla/${l}-${m}/

  ./drusilla -alg 1 -n ${n} -d ${d} -B ${B} -l ${l} -m ${m} -ds ${dPath}.ds \
    -df ${dFolder} -of ${oFolder}

  ./drusilla -alg 2 -qn ${qn} -d ${d} -qs ${dPath}.q -ts ${dPath}.fn2.0 \
    -df ${dFolder} -of ${oFolder}
done
