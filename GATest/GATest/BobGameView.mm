//
//  BobGameView.m
//  GATest
//
//  Created by yiyang yuan on 8/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "BobGameView.h"
#import "Bob.h"
#import "defines.h"

CgaBob* bob;

@implementation BobGameView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        self.backgroundColor = [UIColor whiteColor];
        bob = new CgaBob(CROSSOVER_RATE, MUTATION_RATE, POP_SIZE, CHROMO_LENGTH, GENE_LENGTH);
        //bob->GetMap().randMap();
        bob->Run();
        [NSTimer scheduledTimerWithTimeInterval:0.2 target:self selector:@selector(nextGenerate:) userInfo:nil repeats:YES];
        int i = 10;
        i = ++i + ++i;
        NSLog(@"i:%d",i);
    }
    return self;
}

-(void)nextGenerate:(NSTimer*)timer
{
    if (bob->Started()) {
        bob->Epoch();
        [self setNeedsDisplay];
    }
    //udpate UI
    
}

-(void)drawPhotoCircleWith:(CGContextRef)context withRect:(CGRect)rect lineWidth:(CGFloat)width fillColor:(UIColor*)color
{
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathAddRect(path, NULL, rect);
    CGContextAddPath(context, path);
    [color setFill];
    UIColor *strokeColor = [UIColor colorWithRed:183.0/255.0 green:183.0/255.0 blue:183.0/255.0 alpha:1.0];
    [strokeColor setStroke];
    CGContextSetLineWidth(context, width);
    CGContextDrawPath(context, kCGPathFillStroke);
    CGPathRelease(path);
}

-(void)drawColorWith:(CGContextRef)context withRect:(CGRect)rect withColor:(UIColor*)color
{
    CGMutablePathRef path = CGPathCreateMutable();
    CGPathAddRect(path, NULL, rect);
    CGContextAddPath(context, path);
    [color setFill];
    CGContextDrawPath(context, kCGPathFill);
    CGPathRelease(path);
}

-(void)renderMapWith:(CGFloat)width height:(CGFloat)height withContext:(CGContextRef)context
{
    CGFloat offset = 0;
    CGFloat mapW = bob->GetMap().getMapWidth();
    CGFloat mapH = bob->GetMap().getMapHeight();
    CGFloat blockWidth = (width - 2 * offset)/mapW;
    CGFloat blockHeight = (height - 2 * offset)/mapH;
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (bob->GetMap().map[j][i] == 1) {
                [self drawColorWith:context withRect:CGRectMake(i * blockWidth + offset, j*blockHeight + offset, blockWidth, blockHeight) withColor:[UIColor blackColor]];
            }
            if (bob->GetMap().map[j][i] == 5 || bob->GetMap().map[j][i] == 8) {
                [self drawColorWith:context withRect:CGRectMake(i * blockWidth + offset, j*blockHeight + offset, blockWidth, blockHeight) withColor:[UIColor redColor]];
            }
        }
    }

}

-(void)renderMemoryWith:(CGFloat)width height:(CGFloat)height withContext:(CGContextRef)context
{
    CGFloat offset = 0;
    CGFloat mapW = bob->GetMap().getMapWidth();
    CGFloat mapH = bob->GetMap().getMapHeight();
    CGFloat blockWidth = (width - 2 * offset)/mapW;
    CGFloat blockHeight = (height - 2 * offset)/mapH;
    for (int j = 0; j < MAP_HEIGHT; j++) {
        for (int i = 0; i < MAP_WIDTH; i++) {
            if (bob->GetMemory().memory[j][i] == 1) {
                [self drawColorWith:context withRect:CGRectMake(i * blockWidth + offset, j*blockHeight + offset, blockWidth, blockHeight) withColor:[UIColor grayColor]];
            }
        }
    }
}

// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    CGContextRef currentContext = UIGraphicsGetCurrentContext();
    CGContextSaveGState(currentContext);
    //绘制地图
    [self renderMapWith:rect.size.width height:rect.size.height-40 withContext:currentContext];
    //绘制记忆地图
    [self renderMemoryWith:rect.size.width height:rect.size.height - 40 withContext:currentContext];
}

@end
