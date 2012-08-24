//
//  SpriteView.h
//  GATest
//
//  Created by yiyang yuan on 8/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SpritesView : UIView{
    
    NSMutableArray *spriteImages;
    UIButton *nextGen;
}

-(void)startTimer;

@end
