//
//  BlunoConnection.h
//  bluno-communicate
//
//  Created by Jason Chu on 7/30/14.
//  Copyright (c) 2014 Jason Chu. All rights reserved.
//

#import "DFBlunoManager.h"
#import <Foundation/Foundation.h>


@protocol BlunoConnectionDelegate <NSObject>

- (void)receivedMessageFrom:(DFBlunoDevice *)device message:(NSString *)message;
- (void)connectedToDevice:(DFBlunoDevice *)device;
- (void)disconnectedFromDevice:(DFBlunoDevice *)device;
- (void)connectionError:(DFBlunoDevice *)device;
- (void)foundDevice:(DFBlunoDevice *)device;


@end

@interface BlunoConnection : NSObject<DFBlunoDelegate>

@property (nonatomic,weak) id<BlunoConnectionDelegate> delegate;

@property NSString *blunoName;
@property NSMutableArray *visibleDevices;
@property NSMutableArray *connectedDevices;
@property DFBlunoManager *blunoManager;

- (void)startSearching;
- (void)stopSearching;
- (void)connectToDevice:(DFBlunoDevice *)device;
- (void)disconnectFromDevice:(DFBlunoDevice *)device;
- (BOOL)sendMessageToDevice:(DFBlunoDevice *)device message:(NSString *)message;

@end