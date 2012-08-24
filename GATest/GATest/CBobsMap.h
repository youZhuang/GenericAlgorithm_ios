#ifndef CBOBSMAP_H
#define CBOBSMAP_H

///////////////////////////////////////////////////////////////////////
//
//		File: CBobsMap.h
//
//		Author: Mat Buckland
//
//		Desc: Class for defining the map described in chapter 3
//
///////////////////////////////////////////////////////////////////////

#include "stdlib.h"
#include <vector>

#include "defines.h"


using namespace std;




class CBobsMap
{
private:
	
	//storage for the map
	

	static const int	m_iMapWidth;
	static const int	m_iMapHeight;

	//index into the array which is the start point
	static const int	m_iStartX;
	static const int	m_iStartY;

	//and the finish point
	static const int	m_iEndX;
	static const int	m_iEndY;


public:

	//we can use this array as Bobs memory if rqd
    static int	map[MAP_HEIGHT][MAP_WIDTH];
	int					memory[MAP_HEIGHT][MAP_WIDTH];

	CBobsMap()
	{
		ResetMemory();

	}

	//takes a string of directions and see's how far Bob
	//can get. Returns a fitness score proportional to the 
	//distance reached from the exit.
	double TestRoute(const vector<int> &vecPath, CBobsMap &memory);
    
    void randMap();

	void ResetMemory();
    
    static const int getMapWidth(){return m_iMapWidth;}
    static const int getMapHeight(){return m_iMapHeight;}
    
    static const int getStartX(){return m_iStartX;}
    static const int getStartY(){return m_iStartY;}
    
    static const int getEndX(){return m_iEndX;}
    static const int getEndY(){return m_iEndY;}


};



#endif



			