//
//  GenericAlgorithm.h
//  GATest
//
//  Created by yiyang yuan on 8/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GATest_GenericAlgorithm_h
#define GATest_GenericAlgorithm_h

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <math.h>

using namespace std;

using std::vector;

typedef struct Vector{
    float v_x;
    float v_y;
} Vector;

typedef int ALLELE;//基因类型

typedef struct INDIVADUAL{
    ALLELE *chrome;
    float fitness;
    double value;
    float x;
    float y;
    Vector velocity;
    float power;
} INDIVADUAL;//个体



class TPopulation {
public:
    int size;//群体数量 必须是偶数
    int len_chrom;//染色体的长度
    float sumFitness,average;//总的适应度，平均适应度
    INDIVADUAL worst,best;//最坏的群体，最好的群体
    INDIVADUAL *pop;//所有的
    
    
    int index;
    int bestIndex;
    int worstIndex;
    INDIVADUAL currentBest;
    
public:
    
    TPopulation(int popSize, int chromeLength):size(popSize),len_chrom(chromeLength){}
    ~TPopulation(){}
    
    inline INDIVADUAL & indivadual(int i){return pop[i];}
    
    void FillFitness();//计算种群适应度
    double decodeChromosome(int i,int chrom_len);//计算染色体的编码
    
    virtual void analytics();
    
};



#endif
