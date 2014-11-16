//
//  BlunoConnection.m
//  bluno-communicate
//
//  Created by Jason Chu on 7/30/14.
//  Copyright (c) 2014 Jason Chu. All rights reserved.
//

#import "BlunoConnection.h"

@implementation BlunoConnection

- (id)init
{
    self = [super init];
    if (self) {
        self.blunoManager = [DFBlunoManager sharedInstance];
        self.blunoManager.delegate = self;
        self.visibleDevices = [[NSMutableArray alloc] init];
        self.connectedDevices = [[NSMutableArray alloc] init];
    }
    return self;
}

- (void)startSearching {
    [self.visibleDevices removeAllObjects];
    [self.blunoManager scan];
}

- (void)stopSearching {
    [self.blunoManager stop];
}

- (void)connectToDevice:(DFBlunoDevice *)device {
    [self.blunoManager connectToDevice:device];
}

- (void)disconnectFromDevice:(DFBlunoDevice *)device {
    [self.blunoManager disconnectToDevice:device];
}

- (BOOL)sendMessageToDevice:(DFBlunoDevice *)device message:(NSString *)message {
    if (device.bReadyToWrite) {
        NSData *dataToBeSent = [message dataUsingEncoding:NSUTF8StringEncoding];
        [self.blunoManager writeDataToDevice:dataToBeSent Device:device];
        return YES;
    } else {
        return NO;
    }
}

- (void)bleDidUpdateState:(BOOL)bleSupported {
    if (bleSupported) {
        [self.blunoManager scan];
    }
}

- (void)didDiscoverDevice:(DFBlunoDevice *)dev {
    if (![self.visibleDevices containsObject:dev]) {
        [self.visibleDevices addObject:dev];
        [self.delegate foundDevice:dev];
    }
}


- (void)readyToCommunicate:(DFBlunoDevice *)dev {
    [self.delegate connectedToDevice:dev];
}

- (void)didDisconnectDevice:(DFBlunoDevice *)dev {
    [self.connectedDevices removeObject:dev];
    [self.delegate disconnectedFromDevice:dev];
}

- (void)didWriteData:(DFBlunoDevice *)dev {
    
}

- (void)didReceiveData:(NSData *)data Device:(DFBlunoDevice *)dev {
    NSString *receivedString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    [self.delegate receivedMessageFrom:dev message:receivedString];
}

@end
