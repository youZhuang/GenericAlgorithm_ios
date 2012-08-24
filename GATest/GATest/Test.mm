//
//  Test.m
//  GATest
//
//  Created by yiyang yuan on 8/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Test.h"


@implementation Test

-(id)init
{
    self = [super init];
    
    int i;
    srand((unsigned)time(NULL));             //强制类型转化，以当前时间戳定义随机数种子
    printf("本程序为求函数y=x*x的最大值\n");
    generation=0;                    //初始化generation当前执行的代
    input();                         //初始化种群大小、交叉率、变异率
    
    
    /*edit by ppme*/
    //调试用。。。。。显示input()结果
    printf("popsize %d;maxgeneration %d;pc %f;pm %f\n\n",popsize,maxgeneration,pc,pm);
    /*edit by ppme*/
    
    
    generateinitialpopulation();     //产生初始化种群
    evaluatepopulation();         //评价当前种群,(A.计算种群/个体的适应度;B.找出最好和最差的个体)    
    while(generation<maxgeneration) //小于最大世代数,执行循环体
    {
        generation++;                   
        generatenextpopulation();         //生成子代种群(A.选择; B.交叉; C.变异)
        evaluatepopulation();             //评价新生子代种群
        performevolution();               //进行子代进化
        outputtextreport();               //输入当代最终种群
    }
    printf("\n");
    printf("          统计结果:         ");
    printf("\n");
    printf("最大函数值等于：%f\n",currentbest.fitness);
    printf("其染色体编码为：");
    
    //计算currentbest的value
    for( i = 0 ; i < chromlength ; i++ )
        printf(" %d",currentbest.chrom[i]);
    return self;
}

@end
