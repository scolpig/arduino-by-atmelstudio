/*
 * Dot_matrix.c
 *
 * Created: 2019-04-08 오전 10:51:17
 *  Author: scolpig
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Dot_matrix.h"

/*ISR(TIMER0_COMPA_vect){      //Timer.c의 내용을 수정
	static int msec = 0;
	static char i = 0;
	msec++;
	i++;
	if(i>=8)i=0;
	if(i<4){
		dot_matrix_comm_high_PORT &= 0b11110000;
		dot_matrix_comm_low_PORT &= 0b11110000;
		dot_matrix_comm_low_PORT |= 1 << i;
		dot_matrix_data_PORT = dotmatrix_row[i];
	}
	else {
		dot_matrix_comm_low_PORT &= 0b11110000;
		dot_matrix_comm_high_PORT &= 0b11110000;
		dot_matrix_comm_high_PORT |= 1 << (i-4);
		dot_matrix_data_PORT = dotmatrix_row[i];
	}
	if(!(msec%500))PORTB ^= 1<<PORTB5;
}*/

char dotmatrix_row[8];
char dotmatrix_buffer[8];
char JEONG[8] = {
	0b00000101,
	0b11011001,
	0b10101101,
	0b01110101,
	0b11111111,
	0b10000011,
	0b01111101,
	0b10000011
};
const char KYOUNG[8] = {
	0b00001101,
	0b11101001,
	0b11011101,
	0b00111001,
	0b11111101,
	0b10000011,
	0b01111101,
	0b10000011
};
const char YOON[8] = {
	0b10000011,
	0b01111101,
	0b10000011,
	0b11111111,
	0b00000001,
	0b11010111,
	0b01111111,
	0b00000001
};

char name[3][8] = {
	{
		0b00000101,
		0b11011001,
		0b10101101,
		0b01110101,
		0b11111111,
		0b10000011,
		0b01111101,
		0b10000011
	},
	{
		0b00001101,
		0b11101001,
		0b11011101,
		0b00111001,
		0b11111101,
		0b10000011,
		0b01111101,
		0b10000011
	},
	{
		0b10000011,
		0b01111101,
		0b10000011,
		0b11111111,
		0b00000001,
		0b11010111,
		0b01111111,
		0b00000001
	}
};
int Dot_matrix_main(void){
	//char pattern1=0, pattern2=0, char_num=0;
	//int msec = 0;
	
	
	
	
	/*for(int j=0;j<8;j++){
		name[0][j] = JEONG[j];
	}
	for(int j=0;j<8;j++){
		name[1][j] = KYOUNG[j];
	}
	for(int j=0;j<8;j++){
		name[2][j] = YOON[j];
	}*/
	dotmatrix_init(); 
	
	while(1){
		dotmatrix_test();
		//dotmatrix_flow(name, 3, 10);
	}
			
		/*msec += 16;
		if(msec >= 500){
			msec=0;
			char_num++;
			if(char_num>=3)char_num=0;
		}*/
		/*for(int l=0;l<3;l++){
			for(int j=0;j<8;j++){
				for(int k=0;k<10;k++){
					for(int i=0;i<4;i++){
						dot_matrix_comm_low_PORT = 1 << i;
						dot_matrix_data_PORT = name[(l+1)%3][i]>>(8-j) | name[l][i]<<j;
						_delay_ms(2);
					}
					dot_matrix_comm_low_PORT = 0;
					for(int i=0;i<4;i++){
						dot_matrix_comm_high_PORT = 1 << i;
						dot_matrix_data_PORT = name[(l+1)%3][i+4]>>(8-j) | name[l][i+4]<<j;
						_delay_ms(2);
					}
					dot_matrix_comm_high_PORT = 0;
				}
			}*/
		/*for(int j=0;j<8;j++){
				for(int k=0;k<5;k++){
					for(int i=0;i<4;i++){
						dot_matrix_comm_low_PORT = 1 << i;
						dot_matrix_data_PORT = name[l][i]<<j | ~(0b11111111<<j);
						_delay_ms(2);
					}
					dot_matrix_comm_low_PORT = 0;
					for(int i=0;i<4;i++){
						dot_matrix_comm_high_PORT = 1 << i;
						dot_matrix_data_PORT = name[l][i+4]<<j | ~(0b11111111<<j);
						_delay_ms(2);
					}
					dot_matrix_comm_high_PORT = 0;
				}
			}
		}*/
		/*dot_matrix_data_PORT = 0b11111111;
		for(int i=0;i<4;i++){
			dot_matrix_comm_low_PORT = 1 << i;
			dot_matrix_data_PORT = name[char_num][i];
			_delay_ms(2);
		}
		dot_matrix_comm_low_PORT = 0;
		for(int i=0;i<4;i++){
			dot_matrix_comm_high_PORT = 1 << i;
			dot_matrix_data_PORT = name[char_num][i+4];
			_delay_ms(2);
		}
		dot_matrix_comm_high_PORT = 0;*/
		/*//		pattern1 = 0;
//		pattern2 = 0;	
// 		for(int i=0;i<4;i++){
// 			dot_matrix_comm_low_PORT = 1 << i;
// 			pattern1 |= 0b10000000>>i;
// 			pattern2 |= 0b00000001<<i;
// 			PORTD = ~(pattern1 ^ pattern2);
// 			_delay_ms(2);
// 		}
// 		dot_matrix_comm_low_PORT = 0;
// 		for(int i=0;i<4;i++){
// 			dot_matrix_comm_high_PORT = 1 << i;
// 			pattern1 |= 0b10000000>>(i+4);
// 			pattern2 |= 0b00000001<<(i+4);
// 			PORTD = ~(pattern1 ^ pattern2);
// 			_delay_ms(2);
// 		}*/
	return 0;
}
void dotmatrix_test(void){
	for(int j=0;j<4;j++){
		for(int i=0;i<8;i++){
			dot_matrix_comm_low_PORT = 1 << j;
			dot_matrix_data_PORT = ~(1<<i);
			_delay_ms(100);
		}
		dot_matrix_comm_low_PORT = 0;
	}
	for(int j=0;j<4;j++){
		for(int i=0;i<8;i++){
			dot_matrix_comm_high_PORT = 1 << j;
			dot_matrix_data_PORT = ~(1<<i);
			_delay_ms(100);
		}
		dot_matrix_comm_high_PORT = 0;
	}
	return;
}
void dotmatrix_operator(void){
	for(int i=0;i<4;i++){
		dot_matrix_comm_low_PORT = 1 << i;
		dot_matrix_data_PORT = dotmatrix_row[i];
		_delay_ms(2);
	}
	dot_matrix_comm_low_PORT = 0;
	for(int i=0;i<4;i++){
		dot_matrix_comm_high_PORT = 1 << i;
		dot_matrix_data_PORT = dotmatrix_row[i+4];
		_delay_ms(2);
	}
	dot_matrix_comm_high_PORT = 0;
	return;
}
void dotmatrix_update(char* pattern){
	for(int i=0;i<8;i++){
		dotmatrix_row[i] = pattern[i];
	}
	return;
}
void dotmatrix_init(void){
	dot_matrix_comm_low_DDR |= 0b00001111;
	dot_matrix_comm_low_PORT = 0;
	dot_matrix_comm_high_DDR |= 0b00001111;
	dot_matrix_comm_high_PORT = 0;
	dot_matrix_data_DDR = 0b11111111;
	dot_matrix_data_PORT = 0b11111111;
	for(int i=0;i<8;i++){
		dotmatrix_row[i] = 255;    //0b11111111,   0xff
	}
	return;
}
void dotmatrix_flow(char (*data)[8], char char_len, char interval ){
	for(int k=0;k<char_len;k++){
		for(int j=0;j<8;j++){
			for(int i=0;i<8;i++){
				dotmatrix_row[i] = data[(k+1)%char_len][i]>>(8-j) | data[k][i]<<j;
			}
			for(int i=0;i<interval;i++){
				dotmatrix_operator();
			}
		}
	}
	return;
}
void dotmatrix_flow_buffer(char (*data)[8], char char_len){
	for(int k=0;k<char_len;k++){
		for(int j=0;j<8;j++){
			for(int i=0;i<8;i++){
				dotmatrix_buffer[i] = data[(k+1)%char_len][i]>>(8-j) | data[k][i]<<j;
			}
			dotmatrix_update(dotmatrix_buffer);
			_delay_ms(200);
		}
	}
}