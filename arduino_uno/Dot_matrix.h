/*
 * Dot_matrix.h
 *
 * Created: 2019-04-09 오후 5:08:17
 *  Author: scolpig
 */ 


#ifndef DOT_MATRIX_H_
#define DOT_MATRIX_H_

#define dot_matrix_comm_low_DDR DDRB
#define dot_matrix_comm_high_DDR DDRC
#define dot_matrix_data_DDR DDRD
#define dot_matrix_comm_low_PORT PORTB
#define dot_matrix_comm_high_PORT PORTC
#define dot_matrix_data_PORT PORTD

void dotmatrix_operator(void);
void dotmatrix_update(char* pattern);
void dotmatrix_init(void);
void dotmatrix_flow(char (*data)[8], char char_len, char interval );
void dotmatrix_flow_buffer(char (*data)[8], char char_len);
int Dot_matrix_main(void);
void dotmatrix_test(void);

#endif /* DOT_MATRIX_H_ */