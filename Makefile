CC = mpicc
OPENMP = -fopenmp
CFLAGS = -lm -g
OBJ1 = project_mpi.o 
OBJ2 = project_hybrid.o
HEAD = tools.h black_and_white_header.h rgb_header.h
OUT1 = project_mpi
OUT2 = project_hybrid

all:	project_mpi \
		project_hybrid

clean:
	rm -f $(OBJ1) $(OBJ2) $(OUT1) $(OUT2)

project_mpi: $(OBJ1)
	$(CC) -o project_mpi $(OBJ1) $(CFLAGS)

project_hybrid: $(OBJ2)
	$(CC) $(OPENMP) -o project_hybrid $(OBJ2) $(CFLAGS)

project_mpi.o: project_mpi.c $(HEAD)
	$(CC) -c project_mpi.c

project_hybrid.o: project_hybrid.c $(HEAD)
	$(CC) -c project_hybrid.c


