/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */
 /*
	ZAKARIYA ABBAS
	22I-0801
	CS-E 
 */
//---Piece Starts to Fall When Game Starts---//

void fallingPiece(float& timer, float& delay, int& colorNum, int my_color[], bool& flag, int& count, int level, int next[][4][2]){
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        
        if (!anamoly() || flag){
			int n=0;
			for (int i=0;i<4;i++){
                   
                    point_1[i][0] = next[0][i][0];   //new block x-coordinates  
                    point_1[i][1] = next[0][i][1];   //new bloxk y-coordinates  
                }
			//
			for(int x=0 ; x<2; x++)
			{
				for(int i=0 ; i<4 ; i++)
				{
					next[x][i][0] = next[x+1][i][0];
					next[x][i][1] = next[x+1][i][1];
				}
			}
			switch(level)						//defines the random block for given levels
			{
            	case 1:
					   n=rand()%3;
					   break;
				case 2:
					   n=rand()%5;
					   break;
				case 3:
					   n=rand()%7;
					   break;
			}
             colorNum = my_color[0];
			 for(int i=0 ; i<2 ; i++)
			 {
				my_color[i] = my_color[i+1];
			 }
			 my_color[2] = 1+rand()%7;
            //--- Un-Comment this Part When You Make BLOCKS array---//
                
				for (int i=0; i<4; i++)
				{
					next[2][i][0] = BLOCKS[n][i] % 4;    // %2 changed to %4 for better user-friendly program
					next[2][i][1] = BLOCKS[n][i] / 4;    // /2 changed to /4 for better user-friendly program
				}
				 count++;
				 flag = 0;
        }
        timer=0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
int max1(int& x_comp) 						   					//calculates the max value of x-coordinate of block for shadow
{		   
	int max = point_1[0][1];
	for(int i=0 ; i<4 ; i++)
		if(point_1[i][1] > max)
		{	max = point_1[i][1];
			x_comp = point_1[i][0];
		}
	return max;
}
bool boundary_check(int delta_x)   								//checks boundary for right left movement
{
	bool flag=1;
	for (int i=0;i<4;i++)
	{
		if ((point_1[i][0]-1<0 && delta_x == -1) || (point_1[i][0]==N-1 && delta_x == 1) || (gameGrid[point_1[i][1]][point_1[i][0]-1]) || (gameGrid[point_1[i][1]][point_1[i][0]+1]) )
		{
			flag = false;
		}
		
	}
	return flag;
}
void shadow_remove()			   								//removes shadow before any action
{
	for(int i=M-1 ; i>=0 ; i--)
		for(int j=N-1 ; j>=0 ; j--)
		{
			if(gameGrid[i][j] == 9)
				gameGrid[i][j] = 0;
				
		}
}
bool shadow_check(int x)		   								//calculates the position for shadow
{
	bool flag=1;
	for(int i=0 ; i<4 ; i++)
	{
				if(gameGrid[x+1][point_1[i][0]]!=0)
					flag = 0;
	}
	return flag;
}
void shadow_draw(int shadow_x[], int shadow_y[])				//provides the coordinates for shadow 
{
	for(int i=0 ; i<M ; i++)
	{
		int temp  =0;
		bool flag = 0;
		int max_1 = max1(temp);
		if(shadow_check(i)) 
			continue;
		
		for(int x=0 ; x<4 ; x++)
		{
			if(point_1[x][1] == max_1)
			{
				gameGrid[i][point_1[x][0]] = 9;
				shadow_x[x] = point_1[x][0];
				shadow_y[x] = i;
			}
			else
			{
				if(point_1[x][1] == max_1-1)
				{
					gameGrid[i-1][point_1[x][0]] = 9;
					shadow_x[x] = point_1[x][0];
					shadow_y[x] = i-1;
				}
				else
				{
					if(point_1[x][1] == max_1-2)
					{
						gameGrid[i-2][point_1[x][0]] = 9;
						shadow_x[x] = point_1[x][0];
						shadow_y[x] = i-2;
					}
					else
					{
						gameGrid[i-3][point_1[x][0]] = 9;
						shadow_x[x] = point_1[x][0];
						shadow_y[x] = i-3;		
					}
				}
			}
		}
		break;
	}
}
bool shift(int delta_x)											//moves the block right or left depending upon delta_x
{
	if(boundary_check(delta_x))
		for(int x=0; x<4 ; x++)
		{
			point_1[x][0] += delta_x;
		}
	return false;
}
bool line_delete(int x)											//deletes a line after it is completely filled
{
	for(int i=0 ; i<N ; i++)
	{
		gameGrid[x][i] = 0;
		
		for(int j=0 ; j<4 ; j++)
		{
			point_1[i][0] = 0;
			point_1[i][1] = 0;				
		}
	}
	int a = M-1;
	for (int i = M-1; i>=0; i--)
	{
		int flag = 0;
		int count = 0;
		for (int j=0; j<N; j++)
		{
			if(gameGrid[i][j]) 
				flag = 1;
			gameGrid[a][j] = gameGrid[i][j];
		}
		if(flag)
			a--;		
        }
	return 1;
}
void line_check(bool& flag, int& lines, int score[])			//checks if a line is completely filled or not
{
	int num_line = 0;
	for(int x=0 ; x<4 ; x++)
	{
		for (int i = M-1; i>=0; i--)
		{
			int count = 0;
			for (int j=0; j<N; j++)
			{
				if(gameGrid[i][j] && gameGrid[i][j]!=10) 
					count++;
			}
			if (count==N){
				num_line++;
				flag = line_delete(i);		
        	}
		}
	}
	switch (num_line)
	{
	case 1: 
			score[1] += 1;
			break;
	
	case 2:
			score[1] += 3;
			break;
	case 3:
			score[1] += 6;
			break;
	case 4: 
			score[1] += 0;
			score[2] += 1;
			break;
	}
	lines += num_line;
}
void fix_piece(int color)										//fixes a piece at the bottom of grid
{
	for(int i=0 ; i<4 ; i++)
	{
		gameGrid[point_1[i][1]][point_1[i][0]] = color;
	}
}
bool rotate_check(int temp[][2])								//checks if a block can rotate easily to the new coordinates
{
	bool flag=1;
	for(int i=0 ; i<4 ; i++){
		if(gameGrid[temp[i][1]][temp[i][0]+1]!=0 && gameGrid[temp[i][1]][temp[i][0]-1]!=0)
			flag = 0;
		if(gameGrid[temp[i][1]][temp[i][0]+2]!=0 && gameGrid[temp[i][1]][temp[i][0]-1]!=0)
			flag = 0;	
	}
	return flag;
}
bool rotator()													//finds the rotated coordinates and rotates the block
{
	int temp[4][2];
	for(int i=0 ; i<4 ; i++)
	{
		temp[i][0] = point_1[i][0];
		temp[i][1] = point_1[i][1];
	}
	for(int i=0 ; i<4 ; i++)
	{
		temp[i][0] = temp[i][0] - point_1[2][0];
		temp[i][1] = temp[i][1] - point_1[2][1];
	}
	for(int i=0 ; i<4 ; i++)
	{
		int ghost = temp[i][0]; 
		temp[i][0] = temp[i][1]*(-1);
		temp[i][1] = ghost;
	}
	for(int i=0 ; i<4 ; i++)
	{
		temp[i][0] += point_1[2][0];
		temp[i][1] += point_1[2][1];
	}
	
	if(rotate_check(temp))
	{
		for(int i=0 ; i<4 ; i++)
		{
			point_1[i][0] = temp[i][0];
			point_1[i][1] = temp[i][1];
		}
		bool check = 0;
		for(int i=0 ; i<4 ; i++)
			if(point_1[i][0]<0)
			{
				check = 1;
				break;
			}
		while(check)
		{
			for(int i=0 ; i<4 ; i++)
				point_1[i][0] +=1;
			for(int i=0 ; i<4 ; i++)
			{
				if(point_1[i][0]<0)
				{
					check = 1;
					break;
				}
				else
					check = 0;	
			}
		}
		check = 0;
		for(int i=0 ; i<4 ; i++)
			if(point_1[i][0]>=N)
			{
				check = 1;
				break;
			}
		while(check)
		{
			for(int i=0 ; i<4 ; i++)
				point_1[i][0] -=1;
			for(int i=0 ; i<4 ; i++)
			{
				if(point_1[i][0]>=N)
				{
					check = 1;
					break;
				}
				else
					check = 0;	
			}
		}	
	}
	return 0;
}
bool bomb(int& count)											//makes the bomb
{
		for (int i = 0; i < 4; i++)
		{
			point_1[i][1] = 0; 
		}
		point_1[0][0] = rand() % N;
		for (int i=1; i < 4; i++)
		{
			point_1[i][0] = point_1[0][0];
		}
		count++;
		return 1;
}
void bomb_delete(int colorNum, int& count, bool& flag)			//perfomes the given conditions when bomb falls 
{
	if (colorNum == gameGrid[point_1[0][1]+1][point_1[0][0]])
	{
		for(int i=0 ; i<M ;i++)
		{
			for(int j=0 ; j<N ; j++)
			{
				if(gameGrid[i][j] && gameGrid[i][j]!=10)
					gameGrid[i][j] = 0;
			}
		}
	}
	else
	{
		if (point_1[0][1]+1 == M);
		else
		{
			for(int i=point_1[0][1]+1, j=1 ; i<=point_1[0][1]+4 ; i++,j++)
			{
				if(gameGrid[i][point_1[0][0]]!=10)
					gameGrid[i][point_1[0][0]] = 0;
			}
		}
		
	}
	for(int i=0 ; i<4 ; i++)
			{
				point_1[i][0] = 0;
				point_1[i][1] = 0;
				flag =1;
			}
	count++;
}
void bomb_check(bool& bombs, int colorNum, int& count, bool& flag)//checks if bomb has fallen or not
{
	bool flag_1 = 0;
   	if(gameGrid[point_1[0][1]+1][point_1[0][0]] || point_1[0][1]+1 == M)
   	{
		flag_1 = 1;
		bombs = 0;
	}	
	if (flag_1)
	{
		bomb_delete(colorNum, count, flag);
	}
	
}
void score_setting(int score[])									//sets the odd values of score 
{
	
	if(score[1]>9)
	{	
		score[2] += score[1] /10;
		score[1] = score[1] % 10;
	}

}
void shrinker()													//shrinks size with passage of time
{
	for(int i=0 ; i<M-1 ; i++)
	{
		for (int j=0; j<N; j++)
			gameGrid[i][j] = gameGrid[i+1][j];
	}
	for(int j=0 ; j<N ; j++)
	{
		gameGrid[M-1][j] = 10;
	}
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
