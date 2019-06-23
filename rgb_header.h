#ifndef _RGB_HEADER_H
#define _RGB_HEADER_H

struct pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
typedef struct pixel pixel;


inline int rgb_elem_equal(pixel x, pixel y)
{
	return((x.r == y.r) && (x.g == y.g) && (x.b == y.b));
}

inline void rgb_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width)
{
	results[(i)*(width+2) + (j)].r = 
		//Red
		/*upper row*/
		( array[(i-1)*(width+2) + (j-1)].r	*filter[0][0]
		+array[(i-1)*(width+2) + (j)].r		*filter[0][1]
		+array[(i-1)*(width+2) + (j+1)].r	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].r		*filter[1][0]
		+array[(i)*(width+2) + (j)].r  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].r		*filter[1][2]
		/*bottom row*/
		+array[(i+1)*(width+2) + (j-1)].r	*filter[2][0]			
		+array[(i+1)*(width+2) + (j)].r		*filter[2][1]			
		+array[(i+1)*(width+2) + (j+1)].r	*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].g =
		//Green
		/*upper row*/
		( array[(i-1)*(width+2) + (j-1)].g	*filter[0][0]
		+array[(i-1)*(width+2) + (j)].g		*filter[0][1]
		+array[(i-1)*(width+2) + (j+1)].g	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].g		*filter[1][0]
		+array[(i)*(width+2) + (j)].g  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].g		*filter[1][2]
		/*bottom row*/
		+array[(i+1)*(width+2) + (j-1)].g	*filter[2][0]			
		+array[(i+1)*(width+2) + (j)].g		*filter[2][1]			
		+array[(i+1)*(width+2) + (j+1)].g	*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].b =
		//Blue
		/*upper row*/
		( array[(i-1)*(width+2) + (j-1)].b	*filter[0][0]
		+array[(i-1)*(width+2) + (j)].b		*filter[0][1]
		+array[(i-1)*(width+2) + (j+1)].b	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].b		*filter[1][0]
		+array[(i)*(width+2) + (j)].b  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].b		*filter[1][2]
		/*bottom row*/
		+array[(i+1)*(width+2) + (j-1)].b	*filter[2][0]			
		+array[(i+1)*(width+2) + (j)].b		*filter[2][1]			
		+array[(i+1)*(width+2) + (j+1)].b	*filter[2][2] )
		/sumarray ;
}


inline void rgb_northest_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width)
{
	results[(i)*(width+2) + (j)].r = 
		//Red
		/*upper row*/
		( array[(i)*(width+2) + (j)].r	*filter[0][0]
		+array[(i)*(width+2) + (j)].r		*filter[0][1]
		+array[(i)*(width+2) + (j)].r	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].r		*filter[1][0]
		+array[(i)*(width+2) + (j)].r  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].r		*filter[1][2]
		/*bottom row*/
		+array[(i+1)*(width+2) + (j-1)].r	*filter[2][0]			
		+array[(i+1)*(width+2) + (j)].r		*filter[2][1]			
		+array[(i+1)*(width+2) + (j+1)].r	*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].g =
		//Green
		/*upper row*/
		( array[(i)*(width+2) + (j)].g	*filter[0][0]
		+array[(i)*(width+2) + (j)].g		*filter[0][1]
		+array[(i)*(width+2) + (j)].g	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].g		*filter[1][0]
		+array[(i)*(width+2) + (j)].g  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].g		*filter[1][2]
		/*bottom row*/
		+array[(i+1)*(width+2) + (j-1)].g	*filter[2][0]			
		+array[(i+1)*(width+2) + (j)].g		*filter[2][1]			
		+array[(i+1)*(width+2) + (j+1)].g	*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].b =
		//Blue
		/*upper row*/
		( array[(i)*(width+2) + (j)].b	*filter[0][0]
		+array[(i)*(width+2) + (j)].b		*filter[0][1]
		+array[(i)*(width+2) + (j)].b	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].b		*filter[1][0]
		+array[(i)*(width+2) + (j)].b  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].b		*filter[1][2]
		/*bottom row*/
		+array[(i+1)*(width+2) + (j-1)].b	*filter[2][0]			
		+array[(i+1)*(width+2) + (j)].b		*filter[2][1]			
		+array[(i+1)*(width+2) + (j+1)].b	*filter[2][2] )
		/sumarray ;
}


inline void rgb_southest_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width)
{
	results[(i)*(width+2) + (j)].r = 
		//Red
		/*upper row*/
		( array[(i-1)*(width+2) + (j-1)].r	*filter[0][0]
		+array[(i-1)*(width+2) + (j)].r		*filter[0][1]
		+array[(i-1)*(width+2) + (j+1)].r	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].r		*filter[1][0]
		+array[(i)*(width+2) + (j)].r  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].r		*filter[1][2]
		/*bottom row*/
		+array[(i)*(width+2) + (j)].r		*filter[2][0]			
		+array[(i)*(width+2) + (j)].r		*filter[2][1]			
		+array[(i)*(width+2) + (j)].r		*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].g =
		//Green
		/*upper row*/
		( array[(i-1)*(width+2) + (j-1)].g	*filter[0][0]
		+array[(i-1)*(width+2) + (j)].g		*filter[0][1]
		+array[(i-1)*(width+2) + (j+1)].g	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].g		*filter[1][0]
		+array[(i)*(width+2) + (j)].g  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].g		*filter[1][2]
		/*bottom row*/
		+array[(i)*(width+2) + (j)].g		*filter[2][0]			
		+array[(i)*(width+2) + (j)].g		*filter[2][1]			
		+array[(i)*(width+2) + (j)].g		*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].b =
		//Blue
		/*upper row*/
		( array[(i-1)*(width+2) + (j-1)].b	*filter[0][0]
		+array[(i-1)*(width+2) + (j)].b		*filter[0][1]
		+array[(i-1)*(width+2) + (j+1)].b	*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)].b		*filter[1][0]
		+array[(i)*(width+2) + (j)].b  		*filter[1][1]
		+array[(i)*(width+2) + (j+1)].b		*filter[1][2]
		/*bottom row*/
		+array[(i)*(width+2) + (j)].b		*filter[2][0]			
		+array[(i)*(width+2) + (j)].b		*filter[2][1]			
		+array[(i)*(width+2) + (j)].b		*filter[2][2] )
		/sumarray ;
}


inline void rgb_eastest_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width)
{
	results[(i)*(width+2) + (j)].r = 
		//Red
		/*left column*/
		( array[(i-1)*(width+2) + (j-1)].r 	*filter[0][0]
		+array[(i)*(width+2) + (j-1)].r 	*filter[1][0]
		+array[(i+1)*(width+2) + (j-1)].r 	*filter[2][0]
		/*same column*/
		+array[(i-1)*(width+2) + (j)].r 	*filter[0][1]
		+array[(i)*(width+2) + (j)].r 	  	*filter[1][1]
		+array[(i+1)*(width+2) + (j)].r 	*filter[2][1]
		/*right column*/
		+array[(i)*(width+2) + (j)].r 		*filter[0][2]
		+array[(i)*(width+2) + (j)].r 		*filter[1][2]
		+array[(i)*(width+2) + (j)].r 		*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].g =
		//Green
		/*left column*/
		( array[(i-1)*(width+2) + (j-1)].g 	*filter[0][0]
		+array[(i)*(width+2) + (j-1)].g 	*filter[1][0]
		+array[(i+1)*(width+2) + (j-1)].g 	*filter[2][0]
		/*same column*/
		+array[(i-1)*(width+2) + (j)].g 	*filter[0][1]
		+array[(i)*(width+2) + (j)].g 	  	*filter[1][1]
		+array[(i+1)*(width+2) + (j)].g 	*filter[2][1]
		/*right column*/
		+array[(i)*(width+2) + (j)].g 		*filter[0][2]
		+array[(i)*(width+2) + (j)].g 		*filter[1][2]
		+array[(i)*(width+2) + (j)].g 		*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].b =
		//Blue
		/*left column*/
		( array[(i-1)*(width+2) + (j-1)].b 	*filter[0][0]
		+array[(i)*(width+2) + (j-1)].b 	*filter[1][0]
		+array[(i+1)*(width+2) + (j-1)].b 	*filter[2][0]
		/*same column*/
		+array[(i-1)*(width+2) + (j)].b 	*filter[0][1]
		+array[(i)*(width+2) + (j)].b 	  	*filter[1][1]
		+array[(i+1)*(width+2) + (j)].b 	*filter[2][1]
		/*right column*/
		+array[(i)*(width+2) + (j)].b 		*filter[0][2]
		+array[(i)*(width+2) + (j)].b 		*filter[1][2]
		+array[(i)*(width+2) + (j)].b 		*filter[2][2] )
		/sumarray ;
}


inline void rgb_westest_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int i, int j, int height, int width)
{
	results[(i)*(width+2) + (j)].r = 
		//Red
		/*left column*/
		( array[(i)*(width+2) + (j)].r 		*filter[0][0]
		+array[(i)*(width+2) + (j)].r 		*filter[1][0]
		+array[(i)*(width+2) + (j)].r 		*filter[2][0]
		/*same column*/
		+array[(i-1)*(width+2) + (j)].r 	*filter[0][1]
		+array[(i)*(width+2) + (j)].r 	  	*filter[1][1]
		+array[(i+1)*(width+2) + (j)].r 	*filter[2][1]
		/*right column*/
		+array[(i-1)*(width+2) + (j+1)].r 	*filter[0][2]
		+array[(i)*(width+2) + (j+1)].r 	*filter[1][2]
		+array[(i+1)*(width+2) + (j+1)].r 	*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].g =
		//Green
		/*left column*/
		( array[(i)*(width+2) + (j)].g 		*filter[0][0]
		+array[(i)*(width+2) + (j)].g 		*filter[1][0]
		+array[(i)*(width+2) + (j)].g 		*filter[2][0]
		/*same column*/
		+array[(i-1)*(width+2) + (j)].g 	*filter[0][1]
		+array[(i)*(width+2) + (j)].g 	  	*filter[1][1]
		+array[(i+1)*(width+2) + (j)].g 	*filter[2][1]
		/*right column*/
		+array[(i-1)*(width+2) + (j+1)].g 	*filter[0][2]
		+array[(i)*(width+2) + (j+1)].g		*filter[1][2]
		+array[(i+1)*(width+2) + (j+1)].g 	*filter[2][2] )
		/sumarray ;

	results[(i)*(width+2) + (j)].b =
		//Blue
		/*left column*/
		( array[(i)*(width+2) + (j)].b 		*filter[0][0]
		+array[(i)*(width+2) + (j)].b 		*filter[1][0]
		+array[(i)*(width+2) + (j)].b 		*filter[2][0]
		/*same column*/
		+array[(i-1)*(width+2) + (j)].b 	*filter[0][1]
		+array[(i)*(width+2) + (j)].b 	  	*filter[1][1]
		+array[(i+1)*(width+2) + (j)].b 	*filter[2][1]
		/*right column*/
		+array[(i-1)*(width+2) + (j+1)].b 	*filter[0][2]
		+array[(i)*(width+2) + (j+1)].b 	*filter[1][2]
		+array[(i+1)*(width+2) + (j+1)].b 	*filter[2][2] )
		/sumarray ;
}


inline void rgb_northwestern_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int height, int width, int north, int west)
{
	if((north ==-1) && (west ==-1))
	{
		results[(1)*(width+2) + (1)].r = 
			//Red
			/*upper row*/
			( array[(1)*(width+2) + (1)].r		*filter[0][0]
			+array[(1)*(width+2) + (1)].r		*filter[0][1]
			+array[(1)*(width+2) + (1)].r		*filter[0][2]
			/*same row*/
			+array[(1)*(width+2) + (1)].r		*filter[1][0]
			+array[(1)*(width+2) + (1)].r  		*filter[1][1]
			+array[(1)*(width+2) + (1+1)].r		*filter[1][2]
			/*bottom row*/
			+array[(1+1)*(width+2) + (1)].r		*filter[2][0]			
			+array[(1+1)*(width+2) + (1)].r		*filter[2][1]			
			+array[(1+1)*(width+2) + (1+1)].r	*filter[2][2] )
			/sumarray ;

		results[(1)*(width+2) + (1)].g =
			//Green
			/*upper row*/
			( array[(1)*(width+2) + (1)].g		*filter[0][0]
			+array[(1)*(width+2) + (1)].g		*filter[0][1]
			+array[(1)*(width+2) + (1)].g		*filter[0][2]
			/*same row*/
			+array[(1)*(width+2) + (1)].g		*filter[1][0]
			+array[(1)*(width+2) + (1)].g  		*filter[1][1]
			+array[(1)*(width+2) + (1+1)].g		*filter[1][2]
			/*bottom row*/
			+array[(1+1)*(width+2) + (1)].g		*filter[2][0]			
			+array[(1+1)*(width+2) + (1)].g		*filter[2][1]			
			+array[(1+1)*(width+2) + (1+1)].g	*filter[2][2] )
			/sumarray ;

		results[(1)*(width+2) + (1)].b =
			//Blue
			/*upper row*/
			( array[(1)*(width+2) + (1)].b		*filter[0][0]
			+array[(1)*(width+2) + (1)].b		*filter[0][1]
			+array[(1)*(width+2) + (1)].b		*filter[0][2]
			/*same row*/
			+array[(1)*(width+2) + (1)].b		*filter[1][0]
			+array[(1)*(width+2) + (1)].b  		*filter[1][1]
			+array[(1)*(width+2) + (1+1)].b		*filter[1][2]
			/*bottom row*/
			+array[(1+1)*(width+2) + (1)].b		*filter[2][0]			
			+array[(1+1)*(width+2) + (1)].b		*filter[2][1]			
			+array[(1+1)*(width+2) + (1+1)].b	*filter[2][2] )
			/sumarray ;
	}
	else if (north ==-1)
	{
		rgb_northest_elem_calc(array, results, filter, sumarray, 1, 1, height, width);
	}
	else if (west ==-1)
	{
		rgb_westest_elem_calc(array, results, filter, sumarray, 1, 1, height, width);
	}
	else
	{
		rgb_elem_calc(array, results, filter, sumarray, 1, 1, height, width);
	}
}


inline void rgb_northeastern_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int height, int width, int north, int east)
{
	if ((north ==-1) && (east ==-1))
	{
		results[(1)*(width+2) + (width)].r = 
			//Red
			/*upper row*/
			( array[(1)*(width+2) + (width)].r		*filter[0][0]
			+array[(1)*(width+2) + (width)].r		*filter[0][1]
			+array[(1)*(width+2) + (width)].r		*filter[0][2]
			/*same row*/
			+array[(1)*(width+2) + (width-1)].r		*filter[1][0]
			+array[(1)*(width+2) + (width)].r  		*filter[1][1]
			+array[(1)*(width+2) + (width)].r		*filter[1][2]
			/*bottom row*/
			+array[(1+1)*(width+2) + (width-1)].r	*filter[2][0]			
			+array[(1+1)*(width+2) + (width)].r		*filter[2][1]			
			+array[(1+1)*(width+2) + (width)].r		*filter[2][2] )
			/sumarray ;

		results[(1)*(width+2) + (width)].g =
			//Green
			/*upper row*/
			( array[(1)*(width+2) + (width)].g		*filter[0][0]
			+array[(1)*(width+2) + (width)].g		*filter[0][1]
			+array[(1)*(width+2) + (width)].g		*filter[0][2]
			/*same row*/
			+array[(1)*(width+2) + (width-1)].g		*filter[1][0]
			+array[(1)*(width+2) + (width)].g  		*filter[1][1]
			+array[(1)*(width+2) + (width)].g		*filter[1][2]
			/*bottom row*/
			+array[(1+1)*(width+2) + (width-1)].g	*filter[2][0]			
			+array[(1+1)*(width+2) + (width)].g		*filter[2][1]			
			+array[(1+1)*(width+2) + (width)].g		*filter[2][2] )
			/sumarray ;

		results[(1)*(width+2) + (width)].b =
			//Blue
			/*upper row*/
			( array[(1)*(width+2) + (width)].b		*filter[0][0]
			+array[(1)*(width+2) + (width)].b		*filter[0][1]
			+array[(1)*(width+2) + (width)].b		*filter[0][2]
			/*same row*/
			+array[(1)*(width+2) + (width-1)].b		*filter[1][0]
			+array[(1)*(width+2) + (width)].b  		*filter[1][1]
			+array[(1)*(width+2) + (width)].b		*filter[1][2]
			/*bottom row*/
			+array[(1+1)*(width+2) + (width-1)].b	*filter[2][0]			
			+array[(1+1)*(width+2) + (width)].b		*filter[2][1]			
			+array[(1+1)*(width+2) + (width)].b		*filter[2][2] )
			/sumarray ;
	}
	else if (north ==-1)//same with northest elem calc
	{
		rgb_northest_elem_calc(array, results, filter, sumarray, 1, width, height, width);
	}
	else if (east ==-1)
	{
		rgb_eastest_elem_calc(array, results, filter, sumarray, 1, width, height, width);
	}
	else
	{
		rgb_elem_calc(array, results, filter, sumarray, 1, width, height, width);
	}
}


inline void rgb_southwestern_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int height, int width, int south, int west)
{
	if ((south ==-1) && (west ==-1))
	{
		results[(height)*(width+2) + (1)].r = 
			//Red
			/*upper row*/
			( array[(height)*(width+2) + (1)].r		*filter[0][0]
			+array[(height-1)*(width+2) + (1)].r	*filter[0][1]
			+array[(height-1)*(width+2) + (1+1)].r	*filter[0][2]
			/*same row*/
			+array[(height)*(width+2) + (1)].r		*filter[1][0]
			+array[(height)*(width+2) + (1)].r  	*filter[1][1]
			+array[(height)*(width+2) + (1+1)].r	*filter[1][2]
			/*bottom row*/
			+array[(height)*(width+2) + (1)].r		*filter[2][0]			
			+array[(height)*(width+2) + (1)].r		*filter[2][1]			
			+array[(height)*(width+2) + (1)].r		*filter[2][2] )
			/sumarray ;

		results[(height)*(width+2) + (1)].g =
			//Green
			/*upper row*/
			( array[(height)*(width+2) + (1)].g		*filter[0][0]
			+array[(height-1)*(width+2) + (1)].g	*filter[0][1]
			+array[(height-1)*(width+2) + (1+1)].g	*filter[0][2]
			/*same row*/
			+array[(height)*(width+2) + (1)].g		*filter[1][0]
			+array[(height)*(width+2) + (1)].g  	*filter[1][1]
			+array[(height)*(width+2) + (1+1)].g	*filter[1][2]
			/*bottom row*/
			+array[(height)*(width+2) + (1)].g		*filter[2][0]			
			+array[(height)*(width+2) + (1)].g		*filter[2][1]			
			+array[(height)*(width+2) + (1)].g		*filter[2][2] )
			/sumarray ;

		results[(height)*(width+2) + (1)].b =
			//Blue
			/*upper row*/
			( array[(height)*(width+2) + (1)].b		*filter[0][0]
			+array[(height-1)*(width+2) + (1)].b	*filter[0][1]
			+array[(height-1)*(width+2) + (1+1)].b	*filter[0][2]
			/*same row*/
			+array[(height)*(width+2) + (1)].b		*filter[1][0]
			+array[(height)*(width+2) + (1)].b  	*filter[1][1]
			+array[(height)*(width+2) + (1+1)].b	*filter[1][2]
			/*bottom row*/
			+array[(height)*(width+2) + (1)].b		*filter[2][0]			
			+array[(height)*(width+2) + (1)].b		*filter[2][1]			
			+array[(height)*(width+2) + (1)].b		*filter[2][2] )
			/sumarray ;
	}
	else if (south ==-1)
	{
		rgb_southest_elem_calc(array, results, filter, sumarray, height, 1, height, width);
	}
	else if (west ==-1)
	{
		rgb_westest_elem_calc(array, results, filter, sumarray, height, 1, height, width);
	}
	else
	{
		rgb_elem_calc(array, results, filter, sumarray, height, 1, height, width);
	}			
}


inline void rgb_southeastern_elem_calc(pixel *array, pixel *results, int filter[3][3], int sumarray, int height, int width, int south, int east)
{
	if ((south ==-1) && (east ==-1))
	{	
		results[(height)*(width+2) + (width)].r = 
			//Red
			/*upper row*/
			( array[(height-1)*(width+2) + (width-1)].r 	*filter[0][0]
			+array[(height-1)*(width+2) + (width)].r 		*filter[0][1]
			+array[(height-1)*(width+2) + (width)].r 		*filter[0][2]
			/*same row*/
			+array[(height)*(width+2) + (width-1)].r 		*filter[1][0]
			+array[(height)*(width+2) + (width)].r 	  		*filter[1][1]
			+array[(height)*(width+2) + (width)].r 			*filter[1][2]
			/*bottom row*/
			+array[(height)*(width+2) + (width)].r 			*filter[2][0]			
			+array[(height)*(width+2) + (width)].r 			*filter[2][1]			
			+array[(height)*(width+2) + (width)].r 			*filter[2][2] )
			/sumarray ;

		results[(height)*(width+2) + (width)].g =
			//Green
			/*upper row*/
			( array[(height-1)*(width+2) + (width-1)].g 	*filter[0][0]
			+array[(height-1)*(width+2) + (width)].g 		*filter[0][1]
			+array[(height-1)*(width+2) + (width)].g 		*filter[0][2]
			/*same row*/
			+array[(height)*(width+2) + (width-1)].g 		*filter[1][0]
			+array[(height)*(width+2) + (width)].g 	  		*filter[1][1]
			+array[(height)*(width+2) + (width)].g 			*filter[1][2]
			/*bottom row*/
			+array[(height)*(width+2) + (width)].g 			*filter[2][0]			
			+array[(height)*(width+2) + (width)].g 			*filter[2][1]			
			+array[(height)*(width+2) + (width)].g 			*filter[2][2] )
			/sumarray ;

		results[(height)*(width+2) + (width)].b =
			//Blue
			/*upper row*/
			( array[(height-1)*(width+2) + (width-1)].b 	*filter[0][0]
			+array[(height-1)*(width+2) + (width)].b 		*filter[0][1]
			+array[(height-1)*(width+2) + (width)].b 		*filter[0][2]
			/*same row*/
			+array[(height)*(width+2) + (width-1)].b 		*filter[1][0]
			+array[(height)*(width+2) + (width)].b 	  		*filter[1][1]
			+array[(height)*(width+2) + (width)].b 			*filter[1][2]
			/*bottom row*/
			+array[(height)*(width+2) + (width)].b 			*filter[2][0]			
			+array[(height)*(width+2) + (width)].b 			*filter[2][1]			
			+array[(height)*(width+2) + (width)].b 			*filter[2][2] )
			/sumarray ;
	}
	else if (south ==-1)
	{
		rgb_southest_elem_calc(array, results, filter, sumarray, height, width, height, width);
	}
	else if (east ==-1)
	{
		rgb_eastest_elem_calc(array, results, filter, sumarray, height, width, height, width);
	}
	else
	{
		rgb_elem_calc(array, results, filter, sumarray, height, width, height, width);
	}
}




#endif