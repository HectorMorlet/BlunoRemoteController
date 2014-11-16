//
//  ViewController.m
//  RemoteController
//
//  Created by Jason Chu on 10/21/14.
//  Copyright (c) 2014 HamLann. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property UIAlertView *shownAlert;
@property DFBlunoManager *bluetoothDevice;
@property DFBlunoDevice *realDevice;
@property bool turnOnLeftMotor;
@property bool turnOnRightMotor;
@property bool activeServoEditing;
@property double lastSyncTime;

@property float lastAngle;
@property int angleResends;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    [self.leftView colorsForView:[UIColor lightGrayColor] activeColor:[UIColor blueColor]];
    self.leftView.delegate = self;
    [self.rightView colorsForView:[UIColor lightGrayColor] activeColor:[UIColor blueColor]];
    self.rightView.delegate = self;

    self.shownAlert = [[UIAlertView alloc] initWithTitle:@"Initialising Bluetooth"
                                                 message:@"One moment..."
                                                delegate:self
                                       cancelButtonTitle:nil
                                       otherButtonTitles:nil];
    [self.shownAlert show];
    
    self.bluetoothDevice = [DFBlunoManager sharedInstance];
    self.bluetoothDevice.delegate = self;
    
    self.angleResends = 3;
    
    [NSTimer scheduledTimerWithTimeInterval:1
                                     target:self
                                   selector:@selector(syncData)
                                   userInfo:nil
                                    repeats:YES];
    
    [NSTimer scheduledTimerWithTimeInterval:0.3
                                     target:self
                                   selector:@selector(responsiveServo)
                                   userInfo:nil
                                    repeats:YES];
    
}

- (void)didReceiveData:(NSData *)data Device:(DFBlunoDevice *)dev {
    NSString* received = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
//    NSLog(@"%@", received);
//    NSLog(@"Data from: %@", dev.identifier);
}

- (void)didDiscoverDevice:(DFBlunoDevice *)dev {
    NSLog(@"Trying to connect");
    NSLog(@"Found: %@", dev.identifier);
//    if ([dev.identifier isEqualToString:@"BD54BA6A-5753-531E-B9F0-8BDE8C247A32"]) {
        NSLog(@"Found you!");
        [self.bluetoothDevice connectToDevice:dev];
//    }
}


- (void)didDisconnectDevice:(DFBlunoDevice *)dev {
    NSLog(@"Uhhhh crud");
    [self.bluetoothDevice stop];
    [self.bluetoothDevice scan];
}

- (void)readyToCommunicate:(DFBlunoDevice *)dev {
    NSLog(dev.identifier);
    [self.shownAlert dismissWithClickedButtonIndex:0 animated:YES];
//    
//    self.shownAlert = [[UIAlertView alloc] initWithTitle:@"SUCCESS!"
//                                                 message:@"YEAHHHHHHHHHH!!11111"
//                                                delegate:self
//                                       cancelButtonTitle:@"lolwut ok"
//                                       otherButtonTitles:nil];
//    [self.shownAlert show];
    self.realDevice = dev;
}

- (void)bleDidUpdateState:(BOOL)bleSupported {
    if (bleSupported) {
        [self.shownAlert dismissWithClickedButtonIndex:-1 animated:YES];
        self.shownAlert = [[UIAlertView alloc] initWithTitle:@"Connecting to Arduino..."
                                                     message:@"Please make sure the Arduino is powered on and running"
                                                    delegate:self
                                           cancelButtonTitle:@"Cancel"
                                           otherButtonTitles:nil];
        [self.shownAlert show];
        
        [self.bluetoothDevice scan];
        
    } else {
        [self.shownAlert dismissWithClickedButtonIndex:-1 animated:YES];
        self.shownAlert = [[UIAlertView alloc] initWithTitle:@"Bluetooth is not turned on!"
                                                     message:@"Bluetooth is currently not turned on or is unavailable"
                                                    delegate:self
                                           cancelButtonTitle:@"Cancel"
                                           otherButtonTitles:nil];
        [self.shownAlert show];
    }
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (buttonIndex >= 0 && [[alertView buttonTitleAtIndex:buttonIndex] isEqualToString:@"Retry"]) {
        
        self.shownAlert = [[UIAlertView alloc] initWithTitle:@"Initialising Bluetooth"
                                                     message:@"One moment..."
                                                    delegate:self
                                           cancelButtonTitle:nil
                                           otherButtonTitles:nil];
        [self.shownAlert show];
        
        self.bluetoothDevice = nil;
        self.bluetoothDevice = [DFBlunoManager sharedInstance];
        self.bluetoothDevice.delegate = self;
    }
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)servoLift:(UISlider *)sender {
    NSLog(@"Servo editing complete!");
    [self syncData];
}

- (IBAction)servoEditing:(UISlider *)sender {
    float floatAngle = (sender.value * 90) + 45;
    NSString* angleString = [NSString stringWithFormat:@"%i Degrees", (int)floatAngle];
    
    self.angleLabel.text = angleString;
    self.activeServoEditing = true;
}


- (void)touchDownView:(TouchView *)view {
    if (view == self.leftView) {
        NSLog(@"Left");
        self.turnOnLeftMotor = true;
        [self syncData];
    } else {
        NSLog(@"Right");
        self.turnOnRightMotor = true;
        [self syncData];
    }
}

- (void)touchUpView:(TouchView *)view {
    if (view == self.leftView) {
        NSLog(@"Left");
        self.turnOnLeftMotor = false;
        [self syncData];
    } else {
        NSLog(@"Right");
        self.turnOnRightMotor = false;
        [self syncData];
    }
}

- (void)responsiveServo {
    if (self.activeServoEditing) {
        self.activeServoEditing = false;
        [self syncData];
    }
}

- (void)syncData {
    if (self.realDevice && self.realDevice.bReadyToWrite) {
        double currentTime = CACurrentMediaTime();
        
        if (true) {
            NSLog(@"Syncing data");
            self.lastSyncTime = currentTime;
            NSString* stringTransmission = @"";
            
            if (!self.turnOnLeftMotor && !self.turnOnRightMotor) {
                stringTransmission = [NSString stringWithFormat:@"%@%@", stringTransmission, @"A"];
            } else if (self.turnOnLeftMotor && self.turnOnRightMotor) {
                stringTransmission = [NSString stringWithFormat:@"%@%@", stringTransmission, @"D"];
            } else if (self.turnOnLeftMotor) {
                stringTransmission = [NSString stringWithFormat:@"%@%@", stringTransmission, @"B"];
            } else if (self.turnOnRightMotor) {
                stringTransmission = [NSString stringWithFormat:@"%@%@", stringTransmission, @"C"];
            }
            
            float floatAngle = (self.servoSlider.value * 90) + 45;

            if ((floatAngle != self.lastAngle) || self.angleResends < 3) {
                
                if (floatAngle != self.lastAngle) {
                    self.angleResends = 0;
                }
                NSString* angleString = [NSString stringWithFormat:@"%i", (int)floatAngle];
                stringTransmission = [NSString stringWithFormat:@"%@%@", stringTransmission, angleString];
                self.lastAngle = floatAngle;
                self.angleResends++;
            }
            
            NSData* transmission = [stringTransmission dataUsingEncoding:NSASCIIStringEncoding];
            NSLog(@"Gonna send: %@", stringTransmission);
            
            [self.bluetoothDevice writeDataToDevice:transmission Device:self.realDevice];
        }
    }
}

@end
