make clean
make
for p in 1 2 4 8 16 24 26 32 48 52 64
do
  echo "bsub -I -N 1 -cgsp 64 -b ./csr $p"
  bsub -I -q q_sw_expr -n 1 -cgsp 64 -b -o result.log ./csr $p
done
