#!/bin/bash
make
rm *.o

# ------------------------------------------------------------------------------
#  Parameters
# ------------------------------------------------------------------------------
dname=P53
n=30159
qn=1000
d=5408
B=65536
dPath=./data/${dname}/${dname}
dFolder=./data/${dname}/

# ------------------------------------------------------------------------------
#  Running Scripts
# ------------------------------------------------------------------------------
L_list=(2 3 4 5 6 8 12) 
M_list=(12 8 6 5 4 3 2)
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
