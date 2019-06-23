#ifndef _BLACK_AND_WHITE_HEADER_H_
#define _BLACK_AND_WHITE_HEADER_H_




inline unsigned char elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width)
{
	return(
		/*upper row*/
		( array[(i-1)*(width+2) + (j-1)]*filter[0][0]
		+array[(i-1)*(width+2) + (j)]*filter[0][1]
		+array[(i-1)*(width+2) + (j+1)]*filter[0][2]
		/*same row*/
		+array[(i)*(width+2) + (j-1)]*filter[1][0]
		+array[(i)*(width+2) + (j)]  *filter[1][1]
		+array[(i)*(width+2) + (j+1)]*filter[1][2]
		/*bottom row*/
		+array[(i+1)*(width+2) + (j-1)]*filter[2][0]			
		+array[(i+1)*(width+2) + (j)]*filter[2][1]			
		+array[(i+1)*(width+2) + (j+1)]*filter[2][2] )
		/sumarray );
}

inline unsigned char northest_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width)
{//convolution of an array element that is in the first row of the array and has no northern neighbor
	return(
	/*upper row*/
	( array[(i)*(width+2) + (j)]*filter[0][0]
	+array[(i)*(width+2) + (j)]*filter[0][1]
	+array[(i)*(width+2) + (j)]*filter[0][2]
	/*same row*/
	+array[(i)*(width+2) + (j-1)]*filter[1][0]
	+array[(i)*(width+2) + (j)]  *filter[1][1]
	+array[(i)*(width+2) + (j+1)]*filter[1][2]
	/*bottom row*/
	+array[(i+1)*(width+2) + (j-1)]*filter[2][0]			
	+array[(i+1)*(width+2) + (j)]*filter[2][1]			
	+array[(i+1)*(width+2) + (j+1)]*filter[2][2] )
	/sumarray );
}

inline unsigned char southest_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width)
{//convolution of an array element that is in the last row of the array and has no southern neighbor
	return(
	/*upper row*/
	( array[(i-1)*(width+2) + (j-1)]*filter[0][0]
	+array[(i-1)*(width+2) + (j)]*filter[0][1]
	+array[(i-1)*(width+2) + (j+1)]*filter[0][2]
	/*same row*/
	+array[(i)*(width+2) + (j-1)]*filter[1][0]
	+array[(i)*(width+2) + (j)]  *filter[1][1]
	+array[(i)*(width+2) + (j+1)]*filter[1][2]
	/*bottom row*/
	+array[(i)*(width+2) + (j)]*filter[2][0]			
	+array[(i)*(width+2) + (j)]*filter[2][1]			
	+array[(i)*(width+2) + (j)]*filter[2][2] )
	/sumarray );
}

inline unsigned char eastest_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width)
{//convolution of an array element that is in the last column of the array and has no eastern neighbor
	return(
	/*left column*/
	( array[(i-1)*(width+2) + (j-1)]*filter[0][0]
	+array[(i)*(width+2) + (j-1)]*filter[1][0]
	+array[(i+1)*(width+2) + (j-1)]*filter[2][0]
	/*same column*/
	+array[(i-1)*(width+2) + (j)]*filter[0][1]
	+array[(i)*(width+2) + (j)]  *filter[1][1]
	+array[(i+1)*(width+2) + (j)]*filter[2][1]
	/*right column*/
	+array[(i)*(width+2) + (j)]*filter[0][2]
	+array[(i)*(width+2) + (j)]*filter[1][2]
	+array[(i)*(width+2) + (j)]*filter[2][2] )
	/sumarray );
}

inline unsigned char westest_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int i, int j, int height, int width)
{//convolution of an array element that is in the first column of the array and has no western neighbor
	return(
	/*left column*/
	( array[(i)*(width+2) + (j)]*filter[0][0]
	+array[(i)*(width+2) + (j)]*filter[1][0]
	+array[(i)*(width+2) + (j)]*filter[2][0]
	/*same column*/
	+array[(i-1)*(width+2) + (j)]*filter[0][1]
	+array[(i)*(width+2) + (j)]  *filter[1][1]
	+array[(i+1)*(width+2) + (j)]*filter[2][1]
	/*right column*/
	+array[(i-1)*(width+2) + (j+1)]*filter[0][2]
	+array[(i)*(width+2) + (j+1)]*filter[1][2]
	+array[(i+1)*(width+2) + (j+1)]*filter[2][2] )
	/sumarray );
}


inline unsigned char northwestern_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int height, int width, int north, int west)
{
	//i=1 j=1
	if ((north ==-1) && (west ==-1))
	{
		return(
		/*upper row*/
		( array[(1)*(width+2) + (1)]*filter[0][0]
		+array[(1)*(width+2) + (1)]*filter[0][1]
		+array[(1)*(width+2) + (1)]*filter[0][2]
		/*same row*/
		+array[(1)*(width+2) + (1)]*filter[1][0]
		+array[(1)*(width+2) + (1)]  *filter[1][1]
		+array[(1)*(width+2) + (1+1)]*filter[1][2]
		/*bottom row*/
		+array[(1+1)*(width+2) + (1)]*filter[2][0]			
		+array[(1+1)*(width+2) + (1)]*filter[2][1]			
		+array[(1+1)*(width+2) + (1+1)]*filter[2][2] )
		/sumarray );
	}
	else if (north ==-1)
	{
		return(northest_elem_calc(array, filter, sumarray, 1, 1, height, width));
	}
	else if (west ==-1)
	{
		return(westest_elem_calc(array, filter, sumarray, 1, 1, height, width));
	}
	else
	{
		return(elem_calc(array, filter, sumarray, 1, 1, height, width));
	}
}


inline unsigned char northeastern_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int height, int width, int north, int east)
{
	//i=1 j=width
	if ((north ==-1) && (east ==-1))
	{
		return(
		/*upper row*/
		( array[(1)*(width+2) + (width)]*filter[0][0]
		+array[(1)*(width+2) + (width)]*filter[0][1]
		+array[(1)*(width+2) + (width)]*filter[0][2]
		/*same row*/
		+array[(1)*(width+2) + (width-1)]*filter[1][0]
		+array[(1)*(width+2) + (width)]  *filter[1][1]
		+array[(1)*(width+2) + (width)]*filter[1][2]
		/*bottom row*/
		+array[(1+1)*(width+2) + (width-1)]*filter[2][0]			
		+array[(1+1)*(width+2) + (width)]*filter[2][1]			
		+array[(1+1)*(width+2) + (width)]*filter[2][2] )
		/sumarray );
	}
	else if (north ==-1)//same with northest elem calc
	{
		return(northest_elem_calc(array, filter, sumarray, 1, width, height, width));
	}
	else if (east ==-1)
	{
		return(eastest_elem_calc(array, filter, sumarray, 1, width, height, width));
	}
	else
	{
		return(elem_calc(array, filter, sumarray, 1, width, height, width));
	}
}


inline unsigned char southwestern_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int height, int width, int south, int west)
{
	//i=height, j=1
	if ((south ==-1) && (west ==-1))
	{
		return(
		/*upper row*/
		( array[(height)*(width+2) + (1)]*filter[0][0]
		+array[(height-1)*(width+2) + (1)]*filter[0][1]
		+array[(height-1)*(width+2) + (1+1)]*filter[0][2]
		/*same row*/
		+array[(height)*(width+2) + (1)]*filter[1][0]
		+array[(height)*(width+2) + (1)]  *filter[1][1]
		+array[(height)*(width+2) + (1+1)]*filter[1][2]
		/*bottom row*/
		+array[(height)*(width+2) + (1)]*filter[2][0]			
		+array[(height)*(width+2) + (1)]*filter[2][1]			
		+array[(height)*(width+2) + (1)]*filter[2][2] )
		/sumarray );
	}
	else if (south ==-1)
	{
		return(southest_elem_calc(array, filter, sumarray, height, 1, height, width));
	}
	else if (west ==-1)
	{
		return(westest_elem_calc(array, filter, sumarray, height, 1, height, width));
	}
	else
	{
		return(elem_calc(array, filter, sumarray, height, 1, height, width));
	}
}


inline unsigned char southeastern_elem_calc(unsigned char *array, int filter[3][3], int sumarray, int height, int width, int south, int east)
{
	//i=height j=width
	if ((south ==-1) && (east ==-1))
	{
		return(
		/*upper row*/
		( array[(height-1)*(width+2) + (width-1)]*filter[0][0]
		+array[(height-1)*(width+2) + (width)]*filter[0][1]
		+array[(height-1)*(width+2) + (width)]*filter[0][2]
		/*same row*/
		+array[(height)*(width+2) + (width-1)]*filter[1][0]
		+array[(height)*(width+2) + (width)]  *filter[1][1]
		+array[(height)*(width+2) + (width)]*filter[1][2]
		/*bottom row*/
		+array[(height)*(width+2) + (width)]*filter[2][0]			
		+array[(height)*(width+2) + (width)]*filter[2][1]			
		+array[(height)*(width+2) + (width)]*filter[2][2] )
		/sumarray );
	}
	else if (south ==-1)
	{
		return(southest_elem_calc(array, filter, sumarray, height, width, height, width));
	}
	else if (east ==-1)
	{
		return(eastest_elem_calc(array, filter, sumarray, height, width, height, width));
	}
	else
	{
		return(elem_calc(array, filter, sumarray, height, width, height, width));
	}
}

#endif