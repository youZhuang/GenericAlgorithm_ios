//
//  Sprite.cpp
//  GATest
//
//  Created by yiyang yuan on 8/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Sprite.h"

#define MIN_X 160 - 80
#define MAX_X 160 + 80
#define MIN_Y 240 - 120
#define MAX_Y 240 + 120
#define MIN_V -2.0
#define MAX_V  2.0

#define MAX_GEN 20

Sprite::~Sprite()
{
    for (int i = 0; i < size; i++) {
        //delete [] pop[i].chrome;
    }
    //delete [] pop;
}

void Sprite::debug()
{
    generateInit();
    analytics();
    while (gen < MAX_GEN) {
        gen++;
        Generate();
        analytics();
        thisGenerateReport();
    }
    for (int i = 0; i < len_chrom; i++) {
        printf("%d",currentBest.chrome[i]);
    }
}

//规则是 越是靠近中间的,适应度越高
void Sprite::generateInit()
{
    srand((unsigned)time(NULL));
    pop = new INDIVADUAL[size];
    for (int i = 0; i < size; i++) {
        pop[i].x     = rand()%320+1;
        pop[i].y     = rand()%480 +1 ;
        pop[i].velocity.v_x = rand()%10-4.5;
        pop[i].velocity.v_y = rand()%10-4.5;
        pop[i].chrome = new int[len_chrom];
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < len_chrom; j++) {//初始化种群基因
//            if ((pop[i].x < MIN_X && pop[i].velocity.v_x < MIN_V) || (pop[i].x > MAX_X && pop[i].velocity.v_x > MAX_V) || (pop[i].y < MIN_Y && pop[i].velocity.v_y < MIN_V) || (pop[i].y > MAX_Y && pop[i].velocity.v_y > MAX_V)) {
//                pop[i].chrome[j] = 0;//位置太靠左 或者太靠右的 以及速度过大或者过小的 基因码为 0
//            }else {
//                pop[i].chrome[j] = 1;
//            }
            if ((pop[i].x < MIN_X ) || (pop[i].x > MAX_X ) || (pop[i].y < MIN_Y ) || (pop[i].y > MAX_Y)) {
                pop[i].chrome[j] = 0;//位置太靠左 或者太靠右的  基因码为 0
            }else {
                pop[i].chrome[j] = 1;
            }
        }
    }
}

void TPopulation::FillFitness()
{
    for (int i = 0; i < size; i++) {
        double temp = decodeChromosome(i, len_chrom);
        pop[i].value = temp;
        pop[i].fitness = pop[i].value;// y = x * x
    }
}

void Sprite::analytics()
{
    FillFitness();
    getBestAndWorstSprites();
}

void Sprite::evolution()
{
    if (currentBest.fitness < best.fitness) {
        currentBest = best;
    }//否则 将currentbest作为最坏的那个
}

void Sprite::Generate()//生成一下代
{
    Select();
    Crossover();
    Mutation();
    
}

void Sprite::getBestAndWorstSprites()
{
    best = pop[0];
    worst = pop[0];
    for (int i = 0; i < size ; i++) {
        if (best.fitness < pop[i].fitness) {
            best = pop[i];
            bestIndex = i;
        }else if (worst.fitness > pop[i].fitness) {
            worst = pop[i];
            worstIndex = i;
        }
        sumFitness += pop[i].fitness;
    }
    if (gen == 0) {
        currentBest = best;
    }else {
        if (currentBest.fitness < best.fitness) {
            currentBest = best;
        }
    }
    average = sumFitness/size;
    
}

INDIVADUAL& Sprite::Select()
{
    double sum ;
    double cFitness[size];
    INDIVADUAL newPop[size];
    for (int i = 0; i < size; i++) {
        sum += pop[i].fitness;      //得到种群总的适应度
    }
    for (int i = 0; i < size; i++) {
        cFitness[i] = pop[i].fitness/sum;//计算个体的适应率
    }
    for (int i = 1; i < size; i++) {
        cFitness[i] = cFitness[i-1] + cFitness[i]; // 计算 个体 累积 适应率
    }
    for (int i = 0; i < size; i++) {//通过轮盘赌方法筛选个体
        double p = rand()%1000 / 1000.0;
        int index = 0;
        while (p > cFitness[index]) {
            index++;
        }
        newPop[i] = pop[index];//这样会得到适应度高的个体,适应度低的将被放弃
    }
    for (int i = 0; i < size; i++) {
        pop[i] = newPop[i];
    }
    return pop[0];
    
}

void Sprite::Crossover(INDIVADUAL &parent1, INDIVADUAL &parent2, INDIVADUAL &child1, INDIVADUAL &child2)
{
    
}

ALLELE Sprite::Mutation(ALLELE allele)
{
    
}

void Sprite::Crossover()
{
    int index[size];
    int point;
    int temp;
    double p;
    srand((unsigned) time(NULL));
    for (int i = 0 ; i < size; i++) {
        index[i] = i;
    }
    for (int i = 0; i < size; i++) {//打乱种群顺序
        point = rand()%(size - i);//0 -- size-i-1
        temp = index[i];
        index[i] = index[point + i];
        index[point + i] = temp;
    }
    for (int i = 0; i < size - 1; i+= 2) {//单点交叉法
        p = rand()%1000/1000.0;
        if (p < pCross) {
            point = rand()%(len_chrom - 1)+1;// 0-- len_chrom-1
            for (int j = point; j < len_chrom; j++) {
                temp = pop[index[i]].chrome[j];
                pop[index[i]].chrome[j] = pop[index[i+1]].chrome[j];
                pop[index[i+1]].chrome[j] = temp;
            }
            
        }
    }
}
void Sprite::Mutation()//变异
{
    double p ;
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < len_chrom; j++) {
            p = rand()%1000/1000.0;
            if (p < pMutation) {
                pop[i].chrome[j] = (pop[i].chrome[j] == 0) ? 1 : 0;
            }
        }
    }
}

void Sprite::thisGenerateReport()
{
    int sum;float average;
    for (int i = 0; i < size; i++) {
        sum += pop[i].fitness;
    }
    average = sum/size;
    
    printf("第%d代染色体最好的是:第%d个 x = %f , y = %f  v_x = %f,v_y = %f\n",gen,bestIndex,pop[bestIndex].x,pop[bestIndex].y,pop[bestIndex].velocity.v_x,pop[bestIndex].velocity.v_y);
    printf("第%d代染色体平均适应度:%f\n",gen,average);
}
