#ifndef __EXT_IO_H
#define __EXT_IO_H

#include "sys.h"
#include "sram.h"

//M3�ڲ���ַ�����ߵ�ַƫ����1λ����Ѱַ�ռ�Ҫ16bit���룬���ⲿ���ŵ�λ�ò��䡣
//����Ҫ��ַ��1Ϊ�ߵ�ƽ����ҪѰַ��0x00000002�ĵ�ַ��16bit���룩�����е�ַ��Ҫ����1λ
#define EXT_O1_ADDR Bank1_SRAM3_ADDR|0x00000002
#define EXT_O2_ADDR Bank1_SRAM3_ADDR|0x00000004
#define EXT_I1_ADDR Bank1_SRAM3_ADDR|0x00000008
#define EXT_I2_ADDR Bank1_SRAM3_ADDR|0x00000010
#define EXT_I3_ADDR Bank1_SRAM3_ADDR|0x00000020

extern uint16_t input_buffer[3];
extern uint16_t output_buffer[2];

uint16_t read_input1_16(void);
uint16_t read_input17_32(void);
uint16_t read_input33_40(void);
void write_output1_16(uint16_t data);
void write_output17_32(uint16_t data);

void updata_all_input(uint16_t* in_buf);
void updata_all_output(uint16_t* out_buf);
void refresh_all_io(void);
#endif
