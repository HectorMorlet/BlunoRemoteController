//
//  TouchView.m
//  RemoteController
//
//  Created by Jason Chu on 10/21/14.
//  Copyright (c) 2014 HamLann. All rights reserved.
//

#import "TouchView.h"

@interface TouchView ()

@property UIColor* inactiveColor;
@property UIColor* activeColor;

@end

@implementation TouchView

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (void)colorsForView:(UIColor*)inactiveColor activeColor:(UIColor*)activeColor {
    self.inactiveColor = inactiveColor;
    self.activeColor = activeColor;

    [self setBackgroundColor:inactiveColor];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    [self setBackgroundColor:self.activeColor];
    [self.delegate touchDownView:self];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    [self setBackgroundColor:self.inactiveColor];
    [self.delegate touchUpView:self];
}

@end
