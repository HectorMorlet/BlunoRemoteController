
//
// IOS Communicate
// Hector Morlet and Jason Chu
// 31/7/2014
//

// Output
void updatePins();

// Output - received data
void setPinsFromData(int *rawData);

// Output - AI
void setPinsFromAI(int *lengthTime);
int getAIState(int *data);

// Send
char *sendData(char *data);

// Receive
int *recieveData(void);

// Getting stuff from functions
int getServoState(int *data);
int getMotorOneState(int *data);
int getMotorTwoState(int *data);
