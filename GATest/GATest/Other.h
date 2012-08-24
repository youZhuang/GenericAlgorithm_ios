//
//  Other.cpp
//  GATest
//
//  Created by yiyang yuan on 8/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define POPSIZE 500                    //种群大小
#define chromlength 8                  //染色体长度

int popsize ;                          //种群大小
int maxgeneration;                    //最大世代数
double pc = 0.0;                            //交叉率
double pm = 0.0;                            //变异率

struct individual                      //定义染色体个体结构体
{ 
    int   chrom[chromlength];      //定义染色体二进制表达形式，edit by ppme 将char 转为 int
    double value;                //染色体的值
    double fitness;                        //染色体的适应值
};

int generation;                        //当前执行的世代数
int best_index;                        //最好的染色体索引序号
int worst_index;                       //最差的染色体索引序号

struct individual bestindividual;      //最佳染色体个体
struct individual worstindividual;     //最差染色体个体
struct individual currentbest;         //当前最好的染色体个体 currentbest
struct individual population[POPSIZE];//种群数组

//函数声明                                       
void generateinitialpopulation();      //ok-初始化当代种群      
void generatenextpopulation();         //？？产生下一代种群
void evaluatepopulation();             //评价种群
void calculateobjectfitness();         //计算种群适应度
//long decodechromosome(char *,int,int);//染色体解码
double decodechromosome(int,int); //染色体解码
void findbestandworstindividual();     //寻找最好的和最坏的染色体个体
void performevolution();               //进行演变进化
void selectoperator();                 //选择操作
void crossoveroperator();              //交换操作
void mutationoperator();               //变异操作
void input();                          //输入接口
void outputtextreport();               //输出文字报告

void testGA()     //主函数
{
    int i;
    srand((unsigned)time(NULL));             //强制类型转化，以当前时间戳定义随机数种子
    printf("本程序为求函数y=x*x的最大值\n");
    generation=0;                    //初始化generation当前执行的代
    input();                         //初始化种群大小、交叉率、变异率
    
    
    //edit by ppme
    //调试用。。。。。显示input()结果
    printf("popsize %d;maxgeneration %d;pc %f;pm %f\n\n",popsize,maxgeneration,pc,pm);
    //edit by ppme
    
    
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
}
void generateinitialpopulation( )   //种群初始化
{
    int i,j;
    srand((unsigned)time(NULL));             //强制类型转化，以当前时间戳定义随机数种子
    for (i=0;i<popsize; i++)
    {
        for(j=0;j<chromlength;j++)
        {
            population[i].chrom[j]=(rand()%10<5)?0:1;   //rand()%10随机产生0-9的整数
            //,小于5标注0,否则标注1
        }
    }
    
    
}

void generatenextpopulation()   //生成下一代
{
    selectoperator();
    crossoveroperator();
    mutationoperator();
}

void evaluatepopulation()    //评价种群???
{
    calculateobjectfitness();        //计算种群?个体的适应度
    findbestandworstindividual();    //赵到最好和最差的染色体个体
}
void calculateobjectfitness()   //计算染色体个体适应值和适应度
{  
    int i;
    int j;
    printf("calculateobjectfitness is executing!");
    for(i=0;i<popsize;i++)
    {
        double temp; 
        temp=decodechromosome(i,chromlength); //计算个体适应值
        population[i].value=(double)temp;
        population[i].fitness=population[i].value*population[i].value;
    }
    //调试用
    
    printf("显示当前种群结果:\n");
    for(i = 0 ; i < popsize ; i++)
    {
        for(j = 0 ; j < chromlength ; j++)
        {
            printf(" %d",population[i].chrom[j]);
        }
        
        
        printf(" %lf",population[i].value);
        printf(" %lf",population[i].fitness);
        printf("\n");
    }
    
}
//error
double decodechromosome(int pop_index , int length) //给染色体解码 
{
    int i; 
    double decimal=0;
    for( i = 0 ; i < length ; i++ )
        decimal += population[pop_index].chrom[i]*pow(2,i);    //遍历染色体二进制编码,
    return (decimal);                                                    //并计算出其10进制的value值
}

void findbestandworstindividual( ) //求最佳个体和最差个体
{
    int i;
    double sum=0.0;
    
    bestindividual=population[0];
    worstindividual=population[0];
    for (i=1;i<popsize; i++)
    {
        if (population[i].fitness>bestindividual.fitness)        //依次比较,找出最佳个体
        {
            bestindividual=population[i];
            best_index=i;
        }
        else if (population[i].fitness<worstindividual.fitness) //依次比较,找出最差个体
        {
            worstindividual=population[i];
            worst_index=i;
            
        }
        sum+=population[i].fitness;                  //sum 存放种群总体适应值
    }//for
    
    if (generation==0)
    {
        currentbest=bestindividual;             //第一代最好的暂时存放在currentbest
    }
    else
    {
        if(bestindividual.fitness>=currentbest.fitness)//第n代最好的，通过比较大于以往最好个体的话，
        {                                  //暂时存放在currentbest
            currentbest=bestindividual;
        }
    }
}

void performevolution() //演示评价结果
{
    if (bestindividual.fitness>currentbest.fitness)
    {
        currentbest=population[best_index];
    }
    else
    {
        population[worst_index]=currentbest;
    }
}
void selectoperator() //比例选择算法
{
    int i,index;
    double p,sum=0.0;                   //p存放随机概率，sum存放个体适应率和累计适应率
    double cfitness[POPSIZE];                    //当代种群染色体个体的适应率
    struct individual newpopulation[POPSIZE];    //新种群
    srand((unsigned) time(NULL));                //种下随机种子
    for(i=0;i<popsize;i++)                       //
    {
        sum+=population[i].fitness;                //sum存放种群适应值总和
    }
    for(i=0;i<popsize; i++){
        cfitness[i]=population[i].fitness/sum;     // cfitness[] = fitness/sum得到个体适应率
    }
    for(i=1;i<popsize; i++){
        cfitness[i]=cfitness[i-1]+cfitness[i];     //cfitness[]= cfitness[i-1]+cfitness[i]得到种群
    }                                            //累计适应率
    for (i=0;i<popsize;i++)                      //for循环实现轮盘赌算法
    {
        p=rand()%1000/1000.0;                      //得到千分位小数
        index=0;
        while (p>cfitness[index])
        {
            index++;
        }
        newpopulation[i]=population[index];        //选出的个体组成新的一代,暂时存放于newpopulation[]中
    }
    for(i=0;i<popsize; i++){
        population[i]=newpopulation[i];            //全局变量populaiton存放新的种群（有重复的值）
    }
}

void crossoveroperator() //交叉算法
{
    int i,j;
    int index[POPSIZE];                         
    int point,temp;
    double p;
    
    srand((unsigned) time(NULL));                //种下随机种子
    
    
    for (i=0;i<popsize;i++){                     //初始化index[]数组
        index[i]=i;
    }
    for (i=0;i<popsize;i++){                     //for 循环实现种群内随机两两交换
        point=rand()%(popsize-i);                  //打乱种群顺序
        temp=index[i];
        index[i]=index[point+i];
        index[point+i]=temp;
    }
    for (i=0;i<popsize-1;i+=2){
        p=rand()%1000/1000.0;
        if (p<pc){                                  //单点交叉算法
            point=rand()%(chromlength-1)+1;
            for (j=point; j<chromlength;j++){
                temp=population[index[i]].chrom[j];
                population[index[i]].chrom[j]=population[index[i+1]].chrom[j];
                population[index[i+1]].chrom[j]=temp;
            }
        }
    }
}

void mutationoperator() //变异操作
{
    int i,j;
    double p;
    srand((unsigned) time(NULL));                //种下随机种子
    for (i=0;i<popsize;i++){
        for(j=0;j<chromlength;j++){
            p=rand()%1000/1000.0;
            if (p<pm){
                population[i].chrom[j]=(population[i].chrom[j]==0)?1:0;
            }
        }
    }
    
}

void input() //数据输入
{
    printf("初始化全局变量:\n");
    
    printf("     种群大小(50-500偶数)：");
    scanf("%d", &popsize);                 //输入种群大小，必须为偶数
    if((popsize%2) != 0)          
    {
        printf( "    种群大小已设置为偶数\n");
        popsize++;
    };
    printf("      最大世代数(100-300)："); //输入最大世代数
    scanf("%d", &maxgeneration);
    printf("      交叉率(0.2-0.99)：");     //输入交叉率
    scanf("%lf", &pc);
    printf("      变异率(0.001-0.1)：");    //输入变异率
    scanf("%lf", &pm);
}

void outputtextreport()//数据输出
{
    int i;
    double sum;
    double average;
    sum=0.0;
    for(i=0;i<popsize;i++)
    {
        sum+=population[i].value;
    }
    average=sum/popsize;
    
    printf("当前世代=%d\n当前世代染色体平均值=%f\n当前世代染色体最高值=%f\n",generation,average,population[best_index].value);
}
