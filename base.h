/**************************************************************
* Copyright (c) 2011-2012, xdsac
* All rights reserved.
* Author : RenGuangYu
**************************************************************/
#include "stdint.h"
#ifndef _BASE_H
#define _BASE_H


#define U8_TO_U16(ucH8, ucL8)\
	(uint16_t)((uint8_t)(ucH8)*0x100U+(uint8_t)(ucL8))
#define U16_TO_U32(unH16, unL16)\
	(uint32_t)((uint16_t)(unH16)*0x10000UL+(uint16_t)unL16)	
#define U8_TO_U32(ucHH8, ucHL8, ucLH8, ucLL8)\
	(uint32_t)((uint8_t)(ucHH8)*0x1000000UL+(uint8_t)(ucHL8)*0x10000UL+\
	(uint8_t)(ucLH8)*0x100U+(uint8_t)(ucLL8))

#define BYTES_TO_U32(pucIn) U8_TO_U32(((uint8_t*)(pucIn))[3],\
	((uint8_t*)(pucIn))[2], ((uint8_t*)(pucIn))[1], ((uint8_t*)(pucIn))[0])
/***********************************************************************
	Intel����(Little Endian)���ֽ���ת��Ϊ������
	������pucIn����ת����Intel����(Little Endian)4�ֽ�����
	����ֵ��������ת�����
	ע�⣺�����4�ֽڱ��밴�յ��ֽڵ͵�ַ(Little Endian)��Intel����
	(��EDP 01���ڲ�ͨ�Ź�Լ��ƥ��) 
***********************************************************************/
#define BYTES_TO_FLT(pucIn) (float)U8_TO_U32(((uint8_t*)(pucIn))[3],\
	((uint8_t*)(pucIn))[2], ((uint8_t*)(pucIn))[1], ((uint8_t*)(pucIn))[0])

//typedef __complex__ float COMPLEX;

/*******************************************************************************************/
#define MAX_ID_LEN 128


typedef signed char int8_t;
typedef unsigned char	uint8_t;

//typedef int				int16_t;
//typedef unsigned int	uint16_t;

//typedef long			int32_t;
//typedef unsigned long	uint32_t;

typedef enum _BOOL
{
        t_FALSE	= 0,
        t_TRUE
}t_BOOL;

struct HIOBody
{

};


#endif
