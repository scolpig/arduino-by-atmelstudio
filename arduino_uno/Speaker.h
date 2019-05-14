/*
 * Speaker.h
 *
 * Created: 2019-05-01 오후 4:04:01
 *  Author: scolpig
 */ 


#ifndef SPEAKER_H_
#define SPEAKER_H_

#define DO_03 65
#define DO_03s 69
#define RE_03 73
#define RE_03s 78
#define MI_03 82
#define FA_03 87
#define FA_03s 93
#define SO_03 98
#define SO_03s 104
#define LA_03 110
#define LA_03s 116
#define SI_03 123
#define DO_04 131
#define DO_04s 139
#define RE_04 147
#define RE_04s 156
#define MI_04 165
#define FA_04 175
#define FA_04s 185
#define SO_04 196
#define SO_04s 208
#define LA_04 220
#define LA_04s 233
#define SI_04 247
#define DO_05 262
#define DO_05s 277
#define RE_05 294
#define RE_05s 311
#define MI_05 330
#define FA_05 350
#define FA_05s 370
#define SO_05 392
#define SO_05s 415
#define LA_05 440
#define LA_05s 466
#define SI_05 494
#define DO_06 523
#define DO_06s 554
#define RE_06 587
#define RE_06s 622
#define MI_06 659
#define FA_06 698
#define FA_06s 740
#define SO_06 784
#define SO_06s 831
#define LA_06 880
#define LA_06s 932
#define SI_06 988
#define DO_07 1047
#define DO_07s 1109
#define RE_07 1175
#define RE_07s 1245
#define MI_07 1319
#define FA_07 1397
#define FA_07s 1480
#define SO_07 1568
#define SO_07s 1661
#define LA_07 1760
#define LA_07s 1865
#define SI_07 1976

#define BEAT_4 5456
#define BEAT_2 2728
#define BEAT_1 1364
#define BEAT_1_2 682
#define BEAT_1_4 341
#define BEAT_1_8 170
#define BEAT_1_16 86
#define BEAT_1_32 42

void beep(char repeat);
void siren(char repeat);
void Music_Player(int *tune, int *beat);
void delay_ms(int ms);


#endif /* SPEAKER_H_ */