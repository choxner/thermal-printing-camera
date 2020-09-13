#ifndef	PrinterModule_H_
#define PrinterModule_H_

void pinAssignments(void);
void lineByLine(void);
void energizingSequence(int lineNumber)
void latch(bool latchEnable)
void strobe(int pinNumber)
void stepperEnable(bool motorEnable);

void oddOrEven(bool lineNumber);
void driveStep(int stepNumber); 

#endif /* PrinterModule_H_ */