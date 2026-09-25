mkdir files

for i in {1..1}
do
/usr/bin/time -f "%U user\n%S system\n%E elapsed\n%P CPU\n%M max. mem\n%F pagefaults\n" ./pf 2> files/${i}.out &
done
