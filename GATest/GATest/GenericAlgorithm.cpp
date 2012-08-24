//
//  GenericAlgorithm.cpp
//  GATest
//
//  Created by yiyang yuan on 8/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include "GenericAlgorithm.h"


double TPopulation::decodeChromosome(int i, int chrom_len)
{
    double decode;
    for (int j = 0; j < chrom_len; j++) {
        decode += pop[i].chrome[j]*pow(2, j);
    }
    return decode;
}

void TPopulation::analytics()
{
    
}