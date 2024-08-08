#cc = sw3cc -host -O3 
#cc_slave = sw3cc -O3 
cc = sw5cc -host -O3
cc_slave = sw5cc -slave -O3

#FLAGS= -DTMAX=100 -DNX=1200 -DNY=1200  -DTZ1=30 -DTZ2=30 -DPROFILING
#LIBFLAGS =  -I/usr/sz/swcc/sw3gcc-binary/include
FLAGS = #-g #-D_SPAWN

OBJECT = master.o slave.o interface.o interface_slave.o #task.o

rcsr:$(OBJECT)
	$(cc_slave) -hybrid  -o csr $(OBJECT)
master.o:
	$(cc) $(FLAGS)  -c  master.c
interface.o:
	$(cc) $(FLAGS) -c interface.c
interface_slave.o:
	$(cc_slave) $(FLAGS) -c interface_slave.c
slave.o:
	$(cc_slave) $(FLAGS) -c slave.c
#task.o:
#	$(cc_slave) $(FLAGS) -c task.c
clean:
	rm *.o csr
