//
//  ViewController.h
//  RemoteController
//
//  Created by Jason Chu on 10/21/14.
//  Copyright (c) 2014 HamLann. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TouchView.h"
#import "DFBlunoManager.h"

@interface ViewController : UIViewController<TouchViewDelegate, DFBlunoDelegate, UIAlertViewDelegate>

@property (weak, nonatomic) IBOutlet TouchView *leftView;
@property (weak, nonatomic) IBOutlet TouchView *rightView;
@property (weak, nonatomic) IBOutlet UISlider *servoSlider;


- (IBAction)servoLift:(UISlider *)sender;
- (IBAction)servoEditing:(UISlider *)sender;

@property (weak, nonatomic) IBOutlet UILabel *angleLabel;

@end

