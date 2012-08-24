//
//  Sprite.h
//  GATest
//
//  Created by yiyang yuan on 8/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GATest_Sprite_h
#define GATest_Sprite_h

#include "GA.h"

#define POPSIZE 50
#define CHROMELENGTH 8

//===========================================================
//目标: 获得最稳定的精灵,参考变量为: velocity,power,x,y;
//velocity <= 0 || power <= 0 || x < 0 || y < 0
//===========================================================

class Sprite: public GA
{
public:
    Sprite(int size , float pm = 0.03,float pc = 0.6):GA(size,8,pm,pc){}
    virtual ~Sprite();
    
    void generateInit();//初始化种群
    void getBestAndWorstSprites();
    void evolution();
    void thisGenerateReport();
    void debug();
    virtual void analytics();
    virtual void Generate();//产生新的一代
    virtual INDIVADUAL& Select();
    virtual void Crossover(INDIVADUAL &parent1, INDIVADUAL &parent2,INDIVADUAL &child1,INDIVADUAL &child2);
    virtual ALLELE Mutation(ALLELE allele);
    virtual void Crossover();
    virtual void Mutation();
    
private:
    
};

#endif
