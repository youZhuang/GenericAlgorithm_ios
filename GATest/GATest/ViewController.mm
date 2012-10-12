//
//  ViewController.m
//  GATest
//
//  Created by yiyang yuan on 8/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"
#import "SpriteView.h"

//#import "Bob.h"
//#import "defines.h"
//
//CgaBob* bob;

#import "BobGameView.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	// Do any additional setup after loading the view, typically from a nib.
    /*
    SpritesView *view = [[SpritesView alloc] initWithFrame:CGRectMake(0, 0, 320, 480)];
    [self.view addSubview:view];
    [view release];*/
//    bob = new CgaBob(CROSSOVER_RATE, MUTATION_RATE, POP_SIZE, CHROMO_LENGTH, GENE_LENGTH);
//    bob->Epoch();
    
    //[NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(nextGenerate:) userInfo:nil repeats:YES];
    BobGameView *v = [[BobGameView alloc] initWithFrame:CGRectMake(0, 0, 320, 480)];
    [self.view addSubview:v];
    [v release];
}

-(void)nextGenerate:(NSTimer*)timer
{
    //bob->Epoch();
    //udpate UI
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
