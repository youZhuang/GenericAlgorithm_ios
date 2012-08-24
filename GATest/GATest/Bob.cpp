//
//  Bob.cpp
//  GATest
//
//  Created by yiyang yuan on 8/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Bob.h"

SGenome& CgaBob::RouletteWheelSelection()
{
	double fSlice	= RandFloat() * m_dTotalFitnessScore;
	
	double cfTotal	= 0.0;
	
	int	SelectedGenome = 0;
	
	for (int i=0; i<m_iPopSize; ++i)
	{
		
		cfTotal += m_vecGenomes[i].dFitness;
		
		if (cfTotal > fSlice) 
		{
			SelectedGenome = i;
			break;
		}
	}
	
	return m_vecGenomes[SelectedGenome];
}

//----------------------------Mutate---------------------------------
//	iterates through each genome flipping the bits acording to the
//	mutation rate
//--------------------------------------------------------------------
void CgaBob::Mutate(vector<int> &vecBits)
{
	for (int curBit=0; curBit<vecBits.size(); curBit++)
	{
		//do we flip this bit?
		if (RandFloat() < m_dMutationRate)
		{
			//flip the bit
			vecBits[curBit] = !vecBits[curBit];
		}
	}//next bit
}

//----------------------------Crossover--------------------------------
//	Takes 2 parent vectors, selects a midpoint and then swaps the ends
//	of each genome creating 2 new genomes which are stored in baby1 and
//	baby2.
//---------------------------------------------------------------------
void CgaBob::Crossover( const vector<int> &mum,
                       const vector<int> &dad,
                       vector<int>		  &baby1,
                       vector<int>		  &baby2)
{
	//just return parents as offspring dependent on the rate
	//or if parents are the same
	if ( (RandFloat() > m_dCrossoverRate) || (mum == dad)) 
	{
		baby1 = mum;
		baby2 = dad;
        
		return;
	}
	
	//determine a crossover point
	int cp = RandInt(0, m_iChromoLength - 1);
    
	//swap the bits
	for (int i=0; i<cp; ++i)
	{
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}
    
	for (int i=cp; i<mum.size(); ++i)
	{
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}
}

void CgaBob::report()
{
    
}

//-----------------------------------Run----------------------------------
//
//	This is the function that starts everything. It is mainly another 
//	windows message pump using PeekMessage instead of GetMessage so we
//	can easily and dynamically make updates to the window while the GA is 
//	running. Basically, if there is no msg to be processed another Epoch
//	is performed.
//------------------------------------------------------------------------
void CgaBob::Run()
{
	//The first thing we have to do is create a random population
	//of genomes
	CreateStartPopulation();
	
	m_bBusy = true;
    
}
//----------------------CreateStartPopulation---------------------------
//
//-----------------------------------------------------------------------
void CgaBob::CreateStartPopulation()
{
	//clear existing population
	m_vecGenomes.clear();
	
	for (int i=0; i<m_iPopSize; i++)
	{
		m_vecGenomes.push_back(SGenome(m_iChromoLength));
        //printf("vecgenomes count :%lu",m_vecGenomes[i].vecBits.size());
	}
    
	//reset all variables
	m_iGeneration		 = 0;
	m_iFittestGenome	 = 0;
	m_dBestFitnessScore  = 0;
	m_dTotalFitnessScore = 0;
}
//--------------------------------Epoch---------------------------------
//
//	This is the workhorse of the GA. It first updates the fitness
//	scores of the population then creates a new population of
//	genomes using the Selection, Croosover and Mutation operators
//	we have discussed
//----------------------------------------------------------------------
void CgaBob::Epoch()
{
	
	UpdateFitnessScores();
    
	//Now to create a new population
	int NewBabies = 0;
    
	//create some storage for the baby genomes 
	vector<SGenome> vecBabyGenomes;
    
	while (NewBabies < m_iPopSize)
	{
		//select 2 parents
		SGenome mum = RouletteWheelSelection();
		SGenome dad = RouletteWheelSelection();
        
		//operator - crossover
		SGenome baby1, baby2;
		Crossover(mum.vecBits, dad.vecBits, baby1.vecBits, baby2.vecBits);
        
		//operator - mutate
		Mutate(baby1.vecBits);
		Mutate(baby2.vecBits);
        
		//add to new population
		vecBabyGenomes.push_back(baby1);
		vecBabyGenomes.push_back(baby2);
        
		NewBabies += 2;
	}
    
	//copy babies back into starter population
	m_vecGenomes = vecBabyGenomes;
    
	//increment the generation counter
	++m_iGeneration;
}

//---------------------------UpdateFitnessScores------------------------
//	updates the genomes fitness with the new fitness scores and calculates
//	the highest fitness and the fittest member of the population.
//	Also sets m_pFittestGenome to point to the fittest. If a solution
//	has been found (fitness == 1 in this example) then the run is halted
//	by setting m_bBusy to false
//-----------------------------------------------------------------------
void CgaBob::UpdateFitnessScores()
{
	m_iFittestGenome		= 0;
	m_dBestFitnessScore		= 0;
	m_dTotalFitnessScore	= 0;
    
	CBobsMap TempMemory;
    
	//update the fitness scores and keep a check on fittest so far
	for (int i=0; i<m_iPopSize; ++i)
	{
        
		//decode each genomes chromosome into a vector of directions
		vector<int> vecDirections = Decode(m_vecGenomes[i].vecBits);
        
		//get it's fitness score
		m_vecGenomes[i].dFitness = m_BobsMap.TestRoute(vecDirections, TempMemory);
        
		//update total
		m_dTotalFitnessScore += m_vecGenomes[i].dFitness;
        
		//if this is the fittest genome found so far, store results
		if (m_vecGenomes[i].dFitness > m_dBestFitnessScore)
		{
			m_dBestFitnessScore = m_vecGenomes[i].dFitness;
            
			m_iFittestGenome = i;
            
			m_BobsBrain = TempMemory;
            //printf("genome fitness :%f",m_vecGenomes[i].dFitness);
			//Has Bob found the exit?
			if (m_vecGenomes[i].dFitness == 1)
			{
				//is so, stop the run
				m_bBusy = false;
			}
		} 
		TempMemory.ResetMemory();
        
	}//next genome
}

//---------------------------Decode-------------------------------------
//
//	decodes a vector of bits into a vector of directions (ints)
//
//	0=North, 1=South, 2=East, 3=West
//-----------------------------------------------------------------------
vector<int> CgaBob::Decode(const vector<int> &bits)
{
	vector<int>	directions;
    
	//step through the chromosome a gene at a time
	for (int gene=0; gene < bits.size(); gene += m_iGeneLength)
	{
		//get the gene at this position
		vector<int> ThisGene;
		
		for (int bit = 0; bit < m_iGeneLength; ++bit)
		{
			ThisGene.push_back(bits[gene+bit]);
		}
        
		//convert to decimal and add to list of directions
		directions.push_back(BinToInt(ThisGene));
	}
    
	return directions;
}

//-------------------------------BinToInt-------------------------------
//	converts a vector of bits into an integer
//----------------------------------------------------------------------
int	CgaBob::BinToInt(const vector<int> &vec)
{
	int val = 0;
	int multiplier = 1;
	
	for (int cBit=vec.size(); cBit>0; cBit--)
	{
		val += vec[cBit-1] * multiplier;
		
		multiplier *= 2; // (0+1)*2+0 (0+1)*2+1 (0+0)*2+1 (0+0)*2+0
	}
    
	return val;
}
