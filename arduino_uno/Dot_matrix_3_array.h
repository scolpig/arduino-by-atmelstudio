#define Dotmatrix_shiftR_DDR DDRC
#define Dotmatrix_shiftR_PORT PORTC
#define RClk PORTC4
#define SRClk PORTC5
#define SER PORTC3

void Dotmatrix_left_countinue(void);
void Dotmatrix_flow_left_out(void);
void Dotmatrix_flow_left_in(void);
void Dotmatrix_flow_right_out(void);
void Dotmatrix_flow_right_in(void);
void Dotmatrix_init_shiftR(void);
void Dotmatrix_shift_out(uint32_t data);