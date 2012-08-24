#include "CBobsMap.h"


//this defines our little maze which Bob wanders
//around in
 int CBobsMap::map[MAP_HEIGHT][MAP_WIDTH] = 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
 8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1,
 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5,
 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


const int CBobsMap::m_iMapHeight = MAP_HEIGHT;
const int CBobsMap::m_iMapWidth  = MAP_WIDTH;

const int CBobsMap::m_iStartX = 14;
const int CBobsMap::m_iStartY = 7;

const int CBobsMap::m_iEndX = 0;
const int CBobsMap::m_iEndY = 2;

void CBobsMap::randMap()
{
    srand((unsigned)time(NULL));
    int startX = rand()%MAP_HEIGHT;
    int startY = rand()%MAP_WIDTH;
    int endX   = rand()%MAP_HEIGHT;
    int endY   = rand()%MAP_WIDTH;
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            CBobsMap::map[i][j] = rand()%2;
            CBobsMap::map[startX][startY] = 5;
            CBobsMap::map[endX][endY]     = 8;
        }
    }
}



//---------------------------- TestRoute ---------------------------
//
//	given a decoded vector of directions and a map object representing
//	Bob's memory, this function moves Bob through the maze as far as 
//	he can go updating his memory as he moves.
//-------------------------------------------------------------------
double CBobsMap::TestRoute(const vector<int> &vecPath, CBobsMap &Bobs)
{
	int posX = m_iStartX;
	int posY = m_iStartY;

	for (int dir=0; dir<vecPath.size(); ++dir)
	{
		switch(vecPath[dir])
		{
		case 0: //North

			//check within bounds and that we can move
			if ( ((posY-1) < 0 ) || (map[posY-1][posX] == 1) )
			{
				break;
			}

			else
			{
				posY -= 1;
			}

			break;

		case 1: //South

			//check within bounds and that we can move
			if ( ((posY+1) >= m_iMapHeight) || (map[posY+1][posX] == 1) )
			{
				break;
			}
			
			else
			{
				posY += 1;
			}

			break;

		case 2: //East

			//check within bounds and that we can move
			if ( ((posX+1) >= m_iMapWidth ) || (map[posY][posX+1] == 1) )
			{
				break;
			}
			
			else
			{
				posX += 1;
			}

			break;

		case 3: //West

			//check within bounds and that we can move
			if ( ((posX-1) < 0 ) || (map[posY][posX-1] == 1) )
			{
				break;
			}
			
			else
			{
				posX -= 1;
			}

			break;

		}//end switch

		//mark the route in the memory array
		Bobs.memory[posY][posX] = 1;

	}//next direction

	//now we know the finish point of Bobs journey, let's assign
	//a fitness score which is proportional to his distance from
	//the exit

	int	DiffX = abs(posX - m_iEndX);
	int DiffY = abs(posY - m_iEndY);
    
    printf("diffx :%d",DiffX);
    printf("diffy :%d\n",DiffY);

	//we add the one to ensure we never divide by zero. Therefore
	//a solution has been found when this return value = 1
	return 1/(double)(DiffX+DiffY+1);
}

//--------------------- ResetMemory --------------------------
//
//	resets the memory map to zeros
//------------------------------------------------------------
void CBobsMap::ResetMemory()
{
	for (int y=0; y<m_iMapHeight; ++y)
	{
		for (int x=0; x<m_iMapWidth; ++x)
		{
			memory[y][x] = 0;
		}
	}
}



