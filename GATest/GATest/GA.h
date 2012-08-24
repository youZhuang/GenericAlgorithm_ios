//
//  GA.h
//  GATest
//
//  Created by yiyang yuan on 8/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GATest_GA_h
#define GATest_GA_h

#include "GenericAlgorithm.h"

class GA : public TPopulation{
    
    
public:
    int gen;//进化的代数
    float pCross;//杂交率
    float pMutation;//突变率
    GA(int size ,int length,float pm=0.03,float pc=0.6):TPopulation(size,length){gen = 0;pMutation = pm;pCross = pc;}
    virtual INDIVADUAL& Select();
    virtual void Crossover(INDIVADUAL &parent1, INDIVADUAL &parent2,INDIVADUAL &child1,INDIVADUAL &child2);
    virtual ALLELE Mutation(ALLELE allele);
    virtual void Generate();//产生新的一代
    virtual void Crossover();
    virtual void Mutation();
    
};

#endif
