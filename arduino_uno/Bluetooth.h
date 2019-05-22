/*
 * Bluetooth.h
 *
 * Created: 2019-05-15 오전 11:09:30
 *  Author: scolpig
 */ 


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

void Bluetooth_init(void);
void setName(char *name);
void setPIN(char *pin);
void connectTest(void);


#endif /* BLUETOOTH_H_ */