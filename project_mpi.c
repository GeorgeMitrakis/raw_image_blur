#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include <math.h>
#include <unistd.h>
#include "tools.h"
#include "black_and_white_header.h"
#include "rgb_header.h"

#define WIDTH 1920
#define HEIGHT 2520

#define	N 0
#define S 1
#define E 2
#define W 3
#define NE 4
#define NW 5
#define SE 6
#define SW 7

#define HP_AMOUNT 8

#define MAX_REPS 100

void Build_vertical_halo_point(
	int width,
	int height,
	MPI_Datatype MPI_elem_type,
	int elem_type_size,
	MPI_Datatype *vertical_halo_point);

void Build_horizontal_halo_point(
	int width,
	int height,
	MPI_Datatype MPI_elem_type,
	int elem_type_size,
	MPI_Datatype *horizontal_halo_point);

inline void black_and_white(char *image, int width, int height, int filter[3][3], int sumarray, int reduce_flag);

extern inline unsigned char elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline unsigned char northest_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline unsigned char southest_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline unsigned char eastest_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline unsigned char westest_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline unsigned char northeastern_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int height, int width, int north, int east);
extern inline unsigned char northwestern_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int height, int width, int north, int west);
extern inline unsigned char southeastern_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int height, int width, int south, int east);
extern inline unsigned char southwestern_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int height, int width, int south, int west);


inline void rgb_image(char *image, int width, int height, int filter[3][3], int sumarray, int reduce_flag);

extern inline int rgb_elem_equal(pixel x, pixel y);

extern inline void rgb_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline void rgb_northest_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline void rgb_southest_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline void rgb_eastest_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline void rgb_westest_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width);
extern inline void rgb_northwestern_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int height, int width, int north, int west);
extern inline void rgb_northeastern_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int height, int width, int north, int east);
extern inline void rgb_southwestern_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int height, int width, int south, int west);
extern inline void rgb_southeastern_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int height, int width, int south, int east);
int main(int argc, char **argv)
{

	char *image = NULL;
	int width = WIDTH;
	int height = HEIGHT;
	int grey = 0;
	int colored = 0;
	int fraction = 0;
	int multiple = 0;
	int reduce_flag = 0;

	int comm_sz = -1;
	int my_rank = -1;

	int filter[3][3] = { {0,-1,0}, {-1,5,-1}, {0,-1,0} };
	int sumarray 
					= filter[0][0]
					+ filter[0][1]
					+ filter[0][2]
					+ filter[1][0]
					+ filter[1][1]
					+ filter[1][2]
					+ filter[2][0]
					+ filter[2][1]
					+ filter[2][2];
	



	MPI_Init(&argc , &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	//check input validity
	int check=0;
	check = input_check(argc, argv, &image, &width, &height, &grey, &colored, &fraction, &multiple, &reduce_flag);
	
	if(my_rank==0)
	{
		if((check==-1) || (check==-2))
			printf("Usage: ./project_mpi\n"
			"-p <path to image file>\n"
			"-w <width>\n"
			"-h <height>\n"
			"-f <number> for fraction of the image / -m <number> for image multiple (optional)\n"
			"-g for black-and-white / -c for colored input\n"
			"-r to run with reduce (optional)\n");
		else if(check==-3)
			printf("cannot access file\n");
		else if(check==-4)
			printf("Image fraction must be 1/2 or 1/4. Exiting..\n");
		else if(check==-5)
			printf("Image multiple must be a power of 2. Exiting..\n");
		else if (check==0)
		{
			if(fraction!=0)
				printf("Shrinking image to 1/%d th\n", fraction);
			else if(multiple!=0)
				printf("Enlarging image X%d\n", multiple);
			printf("%s\n", image);
			if(grey==1)
				printf("Black and white image\n");
			else
				printf("RGB image\n");
			printf("Width: %d\n", width);
			printf("Height: %d\n", height);
			if(reduce_flag==1)
				printf("Running with reduce\n");
			else
				printf("Running without reduce\n");
		}
	}
	if (check < 0)
	{
		MPI_Finalize();
		return check;
	}


	int dimension = sqrt(comm_sz);

	//if image can't be divided equally to processes, exit
	if (((width % dimension)!=0) || ((height % dimension)!=0) || (dimension < sqrt(comm_sz)))
	{
		if(my_rank==0)
			printf("Error: could not divide image equally to %d processes. The program will now exit.\n", comm_sz);
		MPI_Finalize();
		return 0;
	}

	if (!colored)
		black_and_white(image, width, height, filter, sumarray, reduce_flag);
	else
		rgb_image(image, width, height, filter, sumarray, reduce_flag);


	MPI_Finalize();

	return 0;
}





void black_and_white(char *image, int width, int height, int filter[3][3], int sumarray, int reduce_flag)
{

	int my_rank, comm_sz;
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


	MPI_Status status;
	MPI_Datatype VERTICAL_HALO_POINT;
	MPI_Datatype HORIZONTAL_HALO_POINT;

	MPI_Request send_halo_point[HP_AMOUNT], recv_halo_point[HP_AMOUNT];


	srand((unsigned int) my_rank);

	//find size of current partition of the image
	int dimension = sqrt(comm_sz);
	width = width/dimension;
	height = height/dimension;

	unsigned char *array = NULL;
	unsigned char *results = NULL;
	//generate array with random 1-byte numbers
	//array must have space for halo points
	array = malloc((width+2) * (height+2) * sizeof(char));
	for (int i = 0; i < height + 2; i++)
	{
		for (int j = 0; j < width + 2; j++)
		{
			if ((i==0) || (i==(height+1)) || (j==0) || (j==(width+1)))//halo points
				array[ i * (width+2) + j] = 0;
			else
				array[ i * (width+2) + j] = rand() % 256;
		}
	}
	//convolution result array
	results = malloc((width+2) * (height+2) * sizeof(char));

	//fill result's halo with 0
	for(int i = 0; i < height + 2; i++)
	{
		if((i==0) || (i==width+1))
		{
			for(int j = 0; j < width + 2; j++)
				results[ i * (width+2) + j] = 0;
		}
		else
		{
			results[i * (width+2)] = 0;
			results[i * (width+2) + (width + 1)] = 0;
		}
	}

	//Create 2D cartesian topology
	MPI_Comm comm;
	int dim[2], period[2];
	dim[0]=dimension;
    dim[1]=dimension;
    period[0]=0;
    period[1]=0;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, 1, &comm);
	MPI_Comm_rank(comm, &my_rank);
	int coord[2];
	MPI_Cart_coords(comm, my_rank, 2, coord);

	//variables for neighbor ranks
	int north,south,east,west;
	int northeast, northwest, southeast, southwest;

	//find neighbors
	if ( coord[1]-1>=0)
    {
		coord[1]--;
		MPI_Cart_rank(comm, coord, &west);
		coord[1]++;
	}
	else
		west = -1;
	if ( coord[1]+1 < dimension)
	{
		coord[1]++;
		MPI_Cart_rank(comm, coord, &east);
		coord[1]--;
	}
	else
		east = -1;

	if ( coord[0]-1>=0)
    {
		coord[0]--;
		MPI_Cart_rank(comm, coord, &north);
		coord[0]++;
	}
	else
		north = -1;

	if ( coord[0]+1 < dimension )
    {
		coord[0]++;
		MPI_Cart_rank(comm, coord, &south);
		coord[0]--;
	}
	else
		south = -1;

	if((north!=-1)&&(east!=-1))
	{
		coord[0]--; coord[1]++;
		MPI_Cart_rank(comm, coord, &northeast);
		coord[0]++; coord[1]--;
	}
	else
		northeast = -1;

	if((north!=-1)&&(west!=-1))
	{
		coord[0]--; coord[1]--;
		MPI_Cart_rank(comm, coord, &northwest);
		coord[0]++; coord[1]++;
	}	
	else
		northwest = -1;

	if((south!=-1)&&(east!=-1))
	{
		coord[0]++; coord[1]++;
		MPI_Cart_rank(comm, coord, &southeast);
		coord[0]--; coord[1]--;
	}
	else
		southeast = -1;

	if((south!=-1)&&(west!=-1))
	{
		coord[0]++; coord[1]--;
		MPI_Cart_rank(comm, coord, &southwest);
		coord[0]--; coord[1]++;
	}
	else
		southwest = -1;

	//create struct type for eastern and western halo point
	Build_vertical_halo_point(width + 2, height, MPI_UNSIGNED_CHAR, (int) sizeof(unsigned char), &VERTICAL_HALO_POINT);
	//create struct type for northern and southern halo point
	Build_horizontal_halo_point(width , height , MPI_UNSIGNED_CHAR, (int) sizeof(unsigned char), &HORIZONTAL_HALO_POINT);

	double local_start, local_finish, local_elapsed, elapsed;
	int rec = 1;
	int reps = MAX_REPS;
	int change = 0;

	//wait for all processes to reach this point
	MPI_Barrier(comm);
	//starting time
	local_start = MPI_Wtime();
	while(rec && reps)
	{

		//send edge points to neighbors
		//NorthWest
		MPI_Isend(&array[(width + 2) +1] , 1 , MPI_UNSIGNED_CHAR, northwest, 0 , comm, &send_halo_point[NW]);
		//North
		MPI_Isend(&array[(width + 2) +1] , 1 , HORIZONTAL_HALO_POINT , north , 0 , comm, &send_halo_point[N]);
		//NorthEast
		MPI_Isend(&array[(width + 2) + width], 1, MPI_UNSIGNED_CHAR , northeast , 0 , comm, &send_halo_point[NE]);
		//West
		MPI_Isend(&array[(width + 2) +1] , 1 , VERTICAL_HALO_POINT , west , 0 , comm , &send_halo_point[W]);
		//East
		MPI_Isend(&array[(width + 2) + width] , 1 , VERTICAL_HALO_POINT , east, 0 , comm, &send_halo_point[E]);
		//SouthWest
		MPI_Isend(&array[ height*(width+2) +1], 1 , MPI_UNSIGNED_CHAR , southwest , 0 , comm , &send_halo_point[SW]);
		//South
		MPI_Isend(&array[ height*(width+2) +1] , 1 , HORIZONTAL_HALO_POINT , south , 0, comm , &send_halo_point[S]);
		//SouthEast
		MPI_Isend(&array[ height*(width+2) + width] , 1 , MPI_UNSIGNED_CHAR , southeast , 0 , comm , &send_halo_point[SE]);

		//receive halo points from neighbors
		//NorthWest
		MPI_Irecv(&array[0] , 1 , MPI_UNSIGNED_CHAR, northwest, 0 , comm, &recv_halo_point[NW]);
		//North
		MPI_Irecv(&array[1] , 1 , HORIZONTAL_HALO_POINT , north , 0 , comm, &recv_halo_point[N]);
		//NorthEast
		MPI_Irecv(&array[width + 1] , 1 , MPI_UNSIGNED_CHAR , northeast , 0 , comm, &recv_halo_point[NE]);
		//West
		MPI_Irecv(&array[width + 2] , 1 , VERTICAL_HALO_POINT , west , 0 , comm , &recv_halo_point[W]);
		//East
		MPI_Irecv(&array[(width + 2) + width + 1] , 1 , VERTICAL_HALO_POINT , east, 0 , comm, &recv_halo_point[E]);
		//SouthWest
		MPI_Irecv(&array[(height+1)*(width+2)], 1 , MPI_UNSIGNED_CHAR , southwest , 0 , comm , &recv_halo_point[SW]);
		//South
		MPI_Irecv(&array[(height+1)*(width+2) +1] , 1 , HORIZONTAL_HALO_POINT , south , 0, comm , &recv_halo_point[S]);
		//SouthEast
		MPI_Irecv(&array[(height+2)*(width+2) -1] , 1 , MPI_UNSIGNED_CHAR , southeast , 0 , comm , &recv_halo_point[SE]);



		//convolute internal elements of the array
		change = 0;
		for(int i = 2 ; i < height ; i++)
		{
			for(int j = 2 ; j < width ; j++)
			{

				results[(i)*(width+2) + (j)] =
				elem_calc(array, filter, sumarray, i, j, height, width);
				
				if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
					change=1;
			}
		}

		//convolute external elements of the array
		int flag[HP_AMOUNT];
		flag[N] = 0;
		flag[S] = 0;
		flag[E] = 0;
		flag[W] = 0;
		flag[NE] = 0;
		flag[NW] = 0;
		flag[SE] = 0;
		flag[SW] = 0;
		//while there is still a halo point to be received
		while(flag[N]==0 || flag[S]==0 || flag[E]==0 || flag[W]==0 ||
			  flag[NE]==0 || flag[NW]==0 || flag[SE]==0 || flag[SW]==0)
		{
			int a;
			//block until a halo point arrives
			MPI_Waitany(HP_AMOUNT, recv_halo_point, &a, &status);

			//then check which halo point arrived

			if(!(flag[N]))//check if nothrern halo point has arrived
			{
				MPI_Test(&recv_halo_point[N], &flag[N], &status);
				if (flag[N])
				{
					int i=1;
					if(north==-1)
					{
						for(int j = 2 ; j < width ; j++)
						{
							results[(i)*(width+2) + (j)] = 
							northest_elem_calc(array, filter, sumarray, i, j, height, width);

							if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
								change=1;
						}
					}
					else
					{
						for(int j = 2 ; j < width ; j++)
						{
							results[(i)*(width+2) + (j)] =
							elem_calc(array, filter, sumarray, i, j, height, width);

							if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
								change=1;
						}
					}
				}
			}
			if(!(flag[S]))//check if southern halo point has arrived
			{
				MPI_Test(&recv_halo_point[S], &flag[S], &status);
				if (flag[S])
				{
					int i = height;
					if(south==-1)//no southern neighbor exists
					{
						for(int j = 2 ; j < width ; j++)
						{
							results[(i)*(width+2) + (j)] = 
							southest_elem_calc(array, filter, sumarray, i, j, height, width);

							if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
								change=1;
						}
					}
					else//southern neighbor exists
					{
						for(int j = 2 ; j < width ; j++)
						{
							results[(i)*(width+2) + (j)] =
							elem_calc(array, filter, sumarray, i, j, height, width);

							if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
								change=1;
						}
					}
				}
			}
			if(!(flag[E]))//check if eastern halo point has arrived
			{
				MPI_Test(&recv_halo_point[E], &flag[E], &status);
				if (flag[E])
				{
					int j = width;
					if (east==-1)//no eastern neighbor exists
					{
						for (int i = 2; i < height; i++)
						{
							results[(i)*(width+2) + (j)]=
							eastest_elem_calc(array, filter, sumarray, i, j, height, width);

							if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
								change=1;
						}
					}
					else//eastern neighbor exists
					{
						for (int i = 2; i < height; i++)
						{
							results[(i)*(width+2) + (j)]=
							elem_calc(array, filter, sumarray, i, j, height, width);

							if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
								change=1;
						}
					}
				}
			}
			if(!(flag[W]))//check if western halo point has arrived
			{
				MPI_Test(&recv_halo_point[W], &flag[W], &status);
				if (flag[W])
				{
					int j=1;
					if (west==-1)//no western neighbor exists
					{
						for (int i = 2; i < height; i++)
						{
							results[(i)*(width+2) + (j)]=
							westest_elem_calc(array, filter, sumarray, i, j, height, width);

							if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
								change=1;
						}
					}
					else//western neighbor exists
					{
						for (int i = 2; i < height; i++)
						{
							results[(i)*(width+2) + (j)]=
							elem_calc(array, filter, sumarray, i, j, height, width);

							if((results[(i)*(width+2) + (j)] != array[(i)*(width+2) + (j)]) && (change==0))
								change=1;
						}
					}
				}
			}
			if(!(flag[NE]))//check if halo point has arrived
			{
				MPI_Test(&recv_halo_point[NE], &flag[NE], &status);
			}
			if(!(flag[NW]))//check if halo point has arrived
			{
				MPI_Test(&recv_halo_point[NW], &flag[NW], &status);
			}
			if(!(flag[SE]))//check if halo point has arrived
			{
				MPI_Test(&recv_halo_point[SE], &flag[SE], &status);
			}
			if(!(flag[SW]))//check if halo point has arrived
			{
				MPI_Test(&recv_halo_point[SW], &flag[SW], &status);
			}
		}

		results[(1)*(width+2) + (1)] = 
		northwestern_elem_calc(array, filter, sumarray, height, width, north, west);
		if((results[(1)*(width+2) + (1)] != array[(1)*(width+2) + (1)]) && (change==0))
			change=1;

		results[(1)*(width+2) + (width)] = 
		northeastern_elem_calc(array, filter, sumarray, height, width, north, east);
		if((results[(1)*(width+2) + (width)] != array[(1)*(width+2) + (width)]) && (change==0))
			change=1;

		results[(height)*(width+2) + (1)] = 
		southwestern_elem_calc(array, filter, sumarray, height, width, south, west);
		if((results[(height)*(width+2) + (1)] != array[(height)*(width+2) + (1)]) && (change==0))
			change=1;

		results[(height)*(width+2) + (width)] = 
		southeastern_elem_calc(array, filter, sumarray, height, width, south, east);
		if((results[(height)*(width+2) + (width)] != array[(height)*(width+2) + (width)]) && (change==0))
			change=1;

		//send handlers
		//NorthWest
		MPI_Wait(&send_halo_point[NW], &status);
		//North
		MPI_Wait(&send_halo_point[N], &status);
		//NorthEast
		MPI_Wait(&send_halo_point[NE], &status);
		//West
		MPI_Wait(&send_halo_point[W], &status);
		//East
		MPI_Wait(&send_halo_point[E], &status);
		//SouthWest
		MPI_Wait(&send_halo_point[SW], &status);
		//South
		MPI_Wait(&send_halo_point[S], &status);
		//SouthEast
		MPI_Wait(&send_halo_point[SE], &status);

		if(reduce_flag==1)
			MPI_Allreduce(&change,&rec,1,MPI_INT,MPI_LOR,comm);
		
		if(reps>1)
		{
			char *temp;
			temp = array;
			array = results;
			results = temp;
		}

		reps--;
	}

	//ending time
	local_finish = MPI_Wtime();
	//local convolution time
	local_elapsed = local_finish - local_start;
	//send maximum convolution time of the processes to process 0
	MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
	if (my_rank==0)
	{
		printf("Elapsed time: %f\n", elapsed);
	}

	MPI_Type_free(&VERTICAL_HALO_POINT);
	MPI_Type_free(&HORIZONTAL_HALO_POINT);


	free(array);
	free(results);
}

void rgb_image(char *image, int width, int height, int filter[3][3], int sumarray, int reduce_flag)
{
	int my_rank, comm_sz;
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	



	srand((unsigned int) my_rank);

	//find size of current partition of the image
	int dimension = sqrt(comm_sz);
	width = width/dimension;
	height = height/dimension;

	pixel *array = NULL;
	pixel *results = NULL;
	//generate array with random 1-byte numbers
	//array must have space for halo points
	array = malloc((width+2) * (height+2) * sizeof(pixel));
	for (int i = 0; i < height + 2; i++)
	{
		for (int j = 0; j < width + 2; j++)
		{
			if ((i==0) || (i==(height+1)) || (j==0) || (j==(width+1)))//halo points
			{
				array[ i * (width+2) + j].r = 0;
				array[ i * (width+2) + j].g = 0;
				array[ i * (width+2) + j].b = 0;
			}
			else
			{
				array[ i * (width+2) + j].r= rand() % 256;
				array[ i * (width+2) + j].g = rand() % 256;
				array[ i * (width+2) + j].b = rand() % 256;
			}
		}
	}

	//convolution result array
	results = malloc((width+2) * (height+2) * sizeof(pixel));

	//fill result's halo with 0
	for(int i = 0; i < height + 2; i++)
	{
		if((i==0) || (i==width+1))
		{
			for(int j = 0; j < width + 2; j++)
			{
				results[ i * (width+2) + j].r = 0;
				results[ i * (width+2) + j].g = 0;
				results[ i * (width+2) + j].b = 0;
			}
		}
		else
		{
			results[i * (width+2)].r = 0;
			results[i * (width+2)].g = 0;
			results[i * (width+2)].b = 0;

			results[i * (width+2) + (width + 1)].r = 0;
			results[i * (width+2) + (width + 1)].g = 0;
			results[i * (width+2) + (width + 1)].b = 0;
		}
	}

	//create MPI_PIXEL datatype
	MPI_Datatype MPI_PIXEL;
	int array_of_blocklengths[3] = {1,1,1};
	
	MPI_Aint r_addr, g_addr, b_addr;
	MPI_Get_address(&(array[0].r), &r_addr);
	MPI_Get_address(&(array[0].g), &g_addr);
	MPI_Get_address(&(array[0].b), &b_addr);
	MPI_Aint array_of_displacements[3] = {0, g_addr - r_addr, b_addr - r_addr};

	MPI_Datatype array_of_types[3] = {MPI_UNSIGNED_CHAR, MPI_UNSIGNED_CHAR, MPI_UNSIGNED_CHAR};
	MPI_Type_create_struct(3, array_of_blocklengths, array_of_displacements, array_of_types, &MPI_PIXEL);
	MPI_Type_commit(&MPI_PIXEL);

	MPI_Status status;
	MPI_Datatype VERTICAL_HALO_POINT;
	MPI_Datatype HORIZONTAL_HALO_POINT;

	MPI_Request send_halo_point[HP_AMOUNT], recv_halo_point[HP_AMOUNT];

	//Create 2D cartesian topology
	MPI_Comm comm;
	int dim[2], period[2];
	dim[0]=dimension;
    dim[1]=dimension;
    period[0]=0;
    period[1]=0;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, 1, &comm);
	MPI_Comm_rank(comm, &my_rank);
	int coord[2];
	MPI_Cart_coords(comm, my_rank, 2, coord);

	//variables for neighbor ranks
	int north,south,east,west;
	int northeast, northwest, southeast, southwest;

	//find neighbors
	if ( coord[1]-1>=0)
    {
		coord[1]--;
		MPI_Cart_rank(comm, coord, &west);
		coord[1]++;
	}
	else
		west = -1;
	if ( coord[1]+1 < dimension)
	{
		coord[1]++;
		MPI_Cart_rank(comm, coord, &east);
		coord[1]--;
	}
	else
		east = -1;

	if ( coord[0]-1>=0)
    {
		coord[0]--;
		MPI_Cart_rank(comm, coord, &north);
		coord[0]++;
	}
	else
		north = -1;

	if ( coord[0]+1 < dimension )
    {
		coord[0]++;
		MPI_Cart_rank(comm, coord, &south);
		coord[0]--;
	}
	else
		south = -1;

	if((north!=-1)&&(east!=-1))
	{
		coord[0]--; coord[1]++;
		MPI_Cart_rank(comm, coord, &northeast);
		coord[0]++; coord[1]--;
	}
	else
		northeast = -1;

	if((north!=-1)&&(west!=-1))
	{
		coord[0]--; coord[1]--;
		MPI_Cart_rank(comm, coord, &northwest);
		coord[0]++; coord[1]++;
	}	
	else
		northwest = -1;

	if((south!=-1)&&(east!=-1))
	{
		coord[0]++; coord[1]++;
		MPI_Cart_rank(comm, coord, &southeast);
		coord[0]--; coord[1]--;
	}
	else
		southeast = -1;

	if((south!=-1)&&(west!=-1))
	{
		coord[0]++; coord[1]--;
		MPI_Cart_rank(comm, coord, &southwest);
		coord[0]--; coord[1]++;
	}
	else
		southwest = -1;



	//create struct type for eastern and western halo point
	Build_vertical_halo_point(width + 2, height, MPI_PIXEL, (int) sizeof(pixel), &VERTICAL_HALO_POINT);
	//create struct type for northern and southern halo point
	Build_horizontal_halo_point(width , height , MPI_PIXEL, (int) sizeof(pixel), &HORIZONTAL_HALO_POINT);

	double local_start, local_finish, local_elapsed, elapsed;
	int rec = 1;
	int reps = MAX_REPS;
	int change = 0;

	//wait for all processes to reach this point
	MPI_Barrier(comm);
	//starting time
	local_start = MPI_Wtime();
	while(rec && reps)
	{

		//send edge points to neighbors
		//NorthWest
		MPI_Isend(&array[(width + 2) +1] , 1 , MPI_PIXEL, northwest, 0 , comm, &send_halo_point[NW]);
		//North
		MPI_Isend(&array[(width + 2) +1] , 1 , HORIZONTAL_HALO_POINT , north , 0 , comm, &send_halo_point[N]);
		//NorthEast
		MPI_Isend(&array[(width + 2) + width], 1, MPI_PIXEL , northeast , 0 , comm, &send_halo_point[NE]);
		//West
		MPI_Isend(&array[(width + 2) +1] , 1 , VERTICAL_HALO_POINT , west , 0 , comm , &send_halo_point[W]);
		//East
		MPI_Isend(&array[(width + 2) + width] , 1 , VERTICAL_HALO_POINT , east, 0 , comm, &send_halo_point[E]);
		//SouthWest
		MPI_Isend(&array[ height*(width+2) +1], 1 , MPI_PIXEL , southwest , 0 , comm , &send_halo_point[SW]);
		//South
		MPI_Isend(&array[ height*(width+2) +1] , 1 , HORIZONTAL_HALO_POINT , south , 0, comm , &send_halo_point[S]);
		//SouthEast
		MPI_Isend(&array[ height*(width+2) + width] , 1 , MPI_PIXEL , southeast , 0 , comm , &send_halo_point[SE]);

		//receive halo points from neighbors
		//NorthWest
		MPI_Irecv(&array[0] , 1 , MPI_PIXEL, northwest, 0 , comm, &recv_halo_point[NW]);
		//North
		MPI_Irecv(&array[1] , 1 , HORIZONTAL_HALO_POINT , north , 0 , comm, &recv_halo_point[N]);
		//NorthEast
		MPI_Irecv(&array[width + 1] , 1 , MPI_PIXEL , northeast , 0 , comm, &recv_halo_point[NE]);
		//West
		MPI_Irecv(&array[width + 2] , 1 , VERTICAL_HALO_POINT , west , 0 , comm , &recv_halo_point[W]);
		//East
		MPI_Irecv(&array[(width + 2) + width + 1] , 1 , VERTICAL_HALO_POINT , east, 0 , comm, &recv_halo_point[E]);
		//SouthWest
		MPI_Irecv(&array[(height+1)*(width+2)], 1 , MPI_PIXEL , southwest , 0 , comm , &recv_halo_point[SW]);
		//South
		MPI_Irecv(&array[(height+1)*(width+2) +1] , 1 , HORIZONTAL_HALO_POINT , south , 0, comm , &recv_halo_point[S]);
		//SouthEast
		MPI_Irecv(&array[(height+2)*(width+2) -1] , 1 , MPI_PIXEL , southeast , 0 , comm , &recv_halo_point[SE]);



		//convolute internal elements of the array
		change = 0;
		for(int i = 2 ; i < height ; i++)
		{
			for(int j = 2 ; j < width ; j++)
			{

				rgb_elem_calc(array, results, filter, sumarray, i, j, height, width);
				
				if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
					change=1;
			}
		}

		//convolute external elements of the array
		int flag[HP_AMOUNT];
		flag[N] = 0;
		flag[S] = 0;
		flag[E] = 0;
		flag[W] = 0;
		flag[NE] = 0;
		flag[NW] = 0;
		flag[SE] = 0;
		flag[SW] = 0;
		//while there is still a halo point to be received
		while(flag[N]==0 || flag[S]==0 || flag[E]==0 || flag[W]==0 ||
			  flag[NE]==0 || flag[NW]==0 || flag[SE]==0 || flag[SW]==0)
		{
			int a;
			//block until a halo point arrives
			MPI_Waitany(HP_AMOUNT, recv_halo_point, &a, &status);

			//then check which halo point arrived

			if(!(flag[N]))//check if nothrern halo point has arrived
			{
				MPI_Test(&recv_halo_point[N], &flag[N], &status);
				if (flag[N])
				{
					int i=1;
					if(north==-1)
					{
						for(int j = 2 ; j < width ; j++)
						{
							rgb_northest_elem_calc(array, results, filter, sumarray, i, j, height, width);

							if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
								change=1;
						}
					}
					else
					{
						for(int j = 2 ; j < width ; j++)
						{
							rgb_elem_calc(array, results, filter, sumarray, i, j, height, width);

							if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
								change=1;
						}
					}
				}
			}
			if(!(flag[S]))//check if southern halo point has arrived
			{
				MPI_Test(&recv_halo_point[S], &flag[S], &status);
				if (flag[S])
				{
					int i = height;
					if(south==-1)//no southern neighbor exists
					{
						for(int j = 2 ; j < width ; j++)
						{
							rgb_southest_elem_calc(array, results, filter, sumarray, i, j, height, width);

							if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
								change=1;
						}
					}
					else//southern neighbor exists
					{
						for(int j = 2 ; j < width ; j++)
						{
							rgb_elem_calc(array, results, filter, sumarray, i, j, height, width);

							if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
								change=1;
						}
					}
				}
			}
			if(!(flag[E]))//check if eastern halo point has arrived
			{
				MPI_Test(&recv_halo_point[E], &flag[E], &status);
				if (flag[E])
				{
					int j = width;
					if (east==-1)//no eastern neighbor exists
					{
						for (int i = 2; i < height; i++)
						{
							rgb_eastest_elem_calc(array, results, filter, sumarray, i, j, height, width);

							if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
								change=1;
						}
					}
					else//eastern neighbor exists
					{
						for (int i = 2; i < height; i++)
						{
							rgb_elem_calc(array, results, filter, sumarray, i, j, height, width);

							if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
								change=1;
						}
					}
				}
			}
			if(!(flag[W]))//check if western halo point has arrived
			{
				MPI_Test(&recv_halo_point[W], &flag[W], &status);
				if (flag[W])
				{
					int j=1;
					if (west==-1)//no western neighbor exists
					{
						for (int i = 2; i < height; i++)
						{
							rgb_westest_elem_calc(array, results, filter, sumarray, i, j, height, width);

							if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
								change=1;
						}
					}
					else//western neighbor exists
					{
						for (int i = 2; i < height; i++)
						{
							rgb_elem_calc(array, results, filter, sumarray, i, j, height, width);

							if((!(rgb_elem_equal(results[(i)*(width+2)+(j)], array[(i)*(width+2)+(j)]))) && (change==0))
								change=1;
						}
					}
				}
			}
			if(!(flag[NE]))//check if halo point has arrived
			{
				MPI_Test(&recv_halo_point[NE], &flag[NE], &status);
			}
			if(!(flag[NW]))//check if halo point has arrived
			{
				MPI_Test(&recv_halo_point[NW], &flag[NW], &status);
			}
			if(!(flag[SE]))//check if halo point has arrived
			{
				MPI_Test(&recv_halo_point[SE], &flag[SE], &status);
			}
			if(!(flag[SW]))//check if halo point has arrived
			{
				MPI_Test(&recv_halo_point[SW], &flag[SW], &status);
			}
		}
 
		rgb_northwestern_elem_calc(array, results, filter, sumarray, height, width, north, west);
		if((!(rgb_elem_equal(results[(1)*(width+2)+(1)], array[(1)*(width+2)+(1)]))) && (change==0))
			change=1;
 
		rgb_northeastern_elem_calc(array, results, filter, sumarray, height, width, north, east);
		if((!(rgb_elem_equal(results[(1)*(width+2)+(width)], array[(1)*(width+2)+(width)]))) && (change==0))
			change=1;

		rgb_southwestern_elem_calc(array, results, filter, sumarray, height, width, south, west);
		if((!(rgb_elem_equal(results[(height)*(width+2)+(1)], array[(height)*(width+2)+(1)]))) && (change==0))
			change=1;

		rgb_southeastern_elem_calc(array, results, filter, sumarray, height, width, south, east);
		if((!(rgb_elem_equal(results[(height)*(width+2)+(width)], array[(height)*(width+2)+(width)]))) && (change==0))
			change=1;

		//send handlers
		//NorthWest
		MPI_Wait(&send_halo_point[NW], &status);
		//North
		MPI_Wait(&send_halo_point[N], &status);
		//NorthEast
		MPI_Wait(&send_halo_point[NE], &status);
		//West
		MPI_Wait(&send_halo_point[W], &status);
		//East
		MPI_Wait(&send_halo_point[E], &status);
		//SouthWest
		MPI_Wait(&send_halo_point[SW], &status);
		//South
		MPI_Wait(&send_halo_point[S], &status);
		//SouthEast
		MPI_Wait(&send_halo_point[SE], &status);

		if(reduce_flag==1)
			MPI_Allreduce(&change,&rec,1,MPI_INT,MPI_LOR,comm);

		if(reps>1)
		{
			pixel *temp;
			temp = array;
			array = results;
			results = temp;
		}

		reps--;
	}

	//ending time
	local_finish = MPI_Wtime();
	//local convolution time
	local_elapsed = local_finish - local_start;
	//send maximum convolution time of the processes to process 0
	MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
	if (my_rank==0)
	{
		printf("Elapsed time: %f\n", elapsed);
	}

	MPI_Type_free(&VERTICAL_HALO_POINT);
	MPI_Type_free(&HORIZONTAL_HALO_POINT);
	MPI_Type_free(&MPI_PIXEL);


	free(array);
	free(results);
}

void Build_vertical_halo_point(
	int width,
	int height,
	MPI_Datatype MPI_elem_type,
	int elem_type_size,
	MPI_Datatype *vertical_halo_point)
{
	int array_of_blocklengths[height];
	for (int i = 0; i < height; i++)
	{
		array_of_blocklengths[i] = 1;
	}

	MPI_Aint array_of_displacements[height];
	for (int i = 0; i < height; i++)
	{
		array_of_displacements[i] = i*width*elem_type_size;
	}

	MPI_Datatype array_of_types[height];
	for (int i = 0; i < height; i++)
	{
		array_of_types[i] = MPI_elem_type;
	}

	MPI_Type_create_struct(
		height,
		array_of_blocklengths,
		array_of_displacements,
		array_of_types,
		vertical_halo_point);

	MPI_Type_commit(vertical_halo_point);
}


void Build_horizontal_halo_point(
	int width,
	int height,
	MPI_Datatype MPI_elem_type,
	int elem_type_size,
	MPI_Datatype *horizontal_halo_point)
{
	int array_of_blocklengths[width];
	for (int i = 0; i < width; i++)
	{
		array_of_blocklengths[i] = 1;
	}

	MPI_Aint array_of_displacements[width];
	for (int i = 0; i < width; i++)
	{
		array_of_displacements[i] = i*elem_type_size;
	}

	MPI_Datatype array_of_types[width];
	for (int i = 0; i < width; i++)
	{
		array_of_types[i] = MPI_elem_type;
	}

	MPI_Type_create_struct(
		width, 
		array_of_blocklengths,
		array_of_displacements,
		array_of_types,
		horizontal_halo_point);

	MPI_Type_commit(horizontal_halo_point);
}
