
//
// IOSConnection.h
// Hector Morlet and Jason Chu
// 31/7/2014
//


#define FALSE 0
#define TRUE 1


// ------------------------------------------------------------
//                             Send
// ------------------------------------------------------------

char *sendData(char *data);


// ------------------------------------------------------------
//                            Recieve
// ------------------------------------------------------------

char *recieveData(void);

int getServoState(int *data);
int getMotorOneState(int *data);
int getMotorTwoState(int *data);
