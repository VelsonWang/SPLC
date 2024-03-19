#ifndef __DEVICE_H__
#define __DEVICE_H__

#ifdef __cplusplus
extern "C"{
#endif

//����ָ��16λ��32λ����
//mbyte���ݻ�������,����һ��mbyte����8λ��������Ҫ�޸Ķ�ȡ�ļ�����
//ʹ��linux˼�룬û����Ϣ������õ���Ϣ���ɹ���0����

#if defined( _WIN32 )
	#include "../Win32/win32.h"
#elif defined( _STM32 )
	#include "../stm32/stm32.h"
#elif defined( _DSP )
	#include "../Win32/win32.h"
#else
	#error "undefine device!"
#endif

#ifndef _DPRINTF
#define _DPRINTF( ... )
#endif

//����Ĵ������
#define RES_OK		1
#define RES_ERR		-1

#ifdef __cplusplus
}
#endif
#endif


