#ifndef _PROJECT_MPI_H_
#define _PROJECT_MPI_H_


int input_check(int argc, char **argv, char **image, int *width, int *height, int *grey, int *colored, int *fraction, int *multiple, int *reduce_flag)//file existance needs to be added
{
	if ((argc!=8) && (argc!=9) && (argc!=10) && (argc!=11))
		return -1;
	else
	{
		for (int i = 0; i < argc; i++)
		{
			if ((strcmp(argv[i] , "-p"))==0)
			{
				*image = malloc((strlen(argv[i+1])+1)*sizeof(char));
				strcpy(*image, argv[i+1]);
				i++;
			}
			else if ((strcmp(argv[i] , "-w"))==0)
			{
				*width = atoi(argv[i+1]);
				i++;
			}
			else if ((strcmp(argv[i] , "-h"))==0)
			{
				*height = atoi(argv[i+1]);
				i++;
			}
			else if ((strcmp(argv[i] , "-f"))==0)
			{
				*fraction = atoi(argv[i+1]);
				i++;
			}
			else if ((strcmp(argv[i] , "-m"))==0)
			{
				*multiple = atoi(argv[i+1]);
				i++;
			}
			else if ((strcmp(argv[i] , "-g"))==0)
			{
				*grey = 1;
			}
			else if ((strcmp(argv[i] , "-c"))==0)
			{
				*colored = 1;
			}
			else if((strcmp(argv[i] , "-r"))==0)
			{
				*reduce_flag = 1;
			}
		}
	}

	if ((*image == NULL)||
		(*width == 0)||
		(*height == 0)||
		((*grey ^ *colored) == 0)||
		((*fraction!=0) && (*multiple!=0)))
	{
		if (*image!=NULL)
			free(*image);
		return -2;
	}

	if ((*fraction!=0) && ((*fraction==2) || (*fraction==4)))
	{
		int cnt = 0;
		int fr = *fraction;

		while(fr >1 )
		{
			fr = fr/2;
			cnt++;
		}
		while(cnt > 0)
		{
			if (cnt>0)
			{
				*height = *height/2;
				cnt--;
			}
			if (cnt>0)
			{
				*width = *width/2;
				cnt--;
			}
		}
	}
	else if(*fraction!=0)
	{
		
		free(*image);
		return -4;
	}

	if ((*multiple!=0) && (*multiple%2 == 0))
	{
		
		int cnt = 0;
		int mult = *multiple;

		while(mult >1 )
		{
			mult = mult/2;
			cnt++;
		}
		while(cnt > 0)
		{
			if (cnt>0)
			{
				*width = *width*2;
				cnt--;
			}
			if (cnt>0)
			{
				*height = *height*2;
				cnt--;
			}
		}
	}
	else if ((*multiple%2 != 0))
	{
		free(*image);
		return -5;
	}
	return 0;
}




#endif