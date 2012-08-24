//
//  SpriteView.m
//  GATest
//
//  Created by yiyang yuan on 8/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "SpriteView.h"
#import "Sprite.h"

#define MAX_GEN 20
#define SIZE    50

static Sprite sprite = Sprite(SIZE);

@implementation SpritesView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        sprite.generateInit();
        sprite.analytics();
        sprite.Generate();
        spriteImages = [[NSMutableArray alloc] initWithCapacity:50];
        srandom((unsigned)time(NULL));
        for (int i = 0; i < 50; i++) {
            UIImageView *v = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 5, 5)];
            if (i == 0) {
                v.frame = CGRectMake(0, 0, 10, 10);
            }
            v.center = CGPointMake(sprite.pop[i].x, sprite.pop[i].y);
            int r = rand()%255;
            int g = rand()%255;
            int b = rand()%255;
            v.backgroundColor = [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0];
            v.tag = 1000 + i;
            [self addSubview:v];
            [v release];
        }
        nextGen = [UIButton buttonWithType:UIButtonTypeRoundedRect];
        [nextGen setTitle:[NSString stringWithFormat:@"第%d代",sprite.gen+1] forState:UIControlStateNormal];
        nextGen.frame = CGRectMake(0, 0, 80, 40);
        nextGen.center = CGPointMake(160, 240 + 100);
        //[nextGen addTarget:self action:@selector(nextGenerate:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:nextGen];
        
        [self startTimer];
        
    }
    return self;
}

-(void)startTimer
{
    [NSTimer scheduledTimerWithTimeInterval:2.0 target:self selector:@selector(nextGenerate:) userInfo:nil repeats:YES];
}

-(void)nextGenerate:(NSTimer*)timer
{
    if (sprite.gen < MAX_GEN) {
        sprite.gen++;
        sprite.Generate();
        sprite.analytics();
    }else {
        [timer invalidate];
        return;
    }
    //udpate UI
    [nextGen setTitle:[NSString stringWithFormat:@"第%d代",sprite.gen+1] forState:UIControlStateNormal];
    for (int i = 0; i < 50; i++) {
        UIView *v = [self viewWithTag:1000+i];
        v.center = CGPointMake(sprite.pop[i].x, sprite.pop[i].y);
        NSLog(@"view center ;%f,%f",sprite.pop[i].x, sprite.pop[i].y);
    }
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
