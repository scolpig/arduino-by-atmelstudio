/*
 * ADC.h
 *
 * Created: 2019-04-24 오후 5:34:45
 *  Author: scolpig
 */ 


#ifndef ADC_H_
#define ADC_H_

int ADC_converting_value(char channel);
void ADC_init(void);
int volt_to_cm(int value);
int volt_to_temperature(int value);

#endif /* ADC_H_ */