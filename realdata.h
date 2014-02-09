/**************************************************************
* Copyright (c) 2011-2012, xdsac
* All rights reserved.
* Author : RenGuangYu
**************************************************************/
#include "base.h"
//#include "hwcfg.h"


#ifndef _REALDATADEF_H
#define _REALDATADEF_H

#define MAX_PART_NUM 32	


/* ģ����Ϣ�ṹ */
typedef struct
{
	uint8_t		aucId[MAX_ID_LEN + 1];
	uint8_t		ucType;
	uint8_t		ucPosition;
	uint8_t		aucHwAddr[4];
	uint8_t		ucAiNum;
	uint8_t		ucAoNum;  						/* Ϊ���ݺ��������AO�ĸ��� */
	uint8_t		ucDiNum;
	uint8_t		ucDoNum;
	uint16_t	unAiSmplRate;
	uint16_t	unAiPts;							/* �ܲ��������� */
	uint32_t	ulDIModCurVaule;			/* DIģ���ĵ�ǰֵ��ֻ��DI������Ч */
	uint8_t		iVtBoxSeqNo;					/* ��� */
	uint8_t		ucVtBoxPos;					/* �������λ�ñ�ţ���0��ʼ */
	uint8_t		iVtBoxAddrInSameKind;			/* ��ַ������������ʹ�� */
	uint8_t		aucVtBoxFd[MAX_ID_LEN + 1];	/* ��λ�����������豸������ */
	uint8_t		ucAiModType;								/* ����ģ������ */
	uint32_t	servertype;									/* �������� */
} RD_PART_INFO;

/* װ����Դ���ýṹ */
typedef struct
{
	uint16_t	unPartNum;
} RD_SYS_INFO;

/* ���ֻ������ͣ��Ժ�����ʵ������� Ϊ�����޸ģ�6/8/2006 */
enum Box_Type
{
	RD_LOCAL_BOX			= 0X0,
	RD_EXTEND_BOX			= 0X1,
	RD_64K_OPT1_BOX		= 0X2,
	RD_2M_OPT1_BOX		= 0X3,
	RD_64K_OPT2_BOX		= 0X4,
	RD_2M_OPT2_BOX		= 0X05,
	RD_OTHER_CPU_BOX	= 0X06,
	RD_REDUN_BOX			= 0X08,
	RD_SAME_POLE_BOX	= 0X9,
	RD_HDL_BOX				= 0XA,
	RD_9_1_ASSM_BOX		= 0XB,
	RD_XN_ASSM_BOX		= 0XC,
	RD_VT_BOX			= 0XD,
};

typedef enum		/* ģ��ö�� */
{
	RD_RESERVED,
	RD_DSP_LGC_AI,
	RD_DSP_CALC_AI,
	RD_SPI_DI,
	RD_SPI_DO,
	RD_EXT_DI,
	RD_REDUN_DI,
	RD_REDUN_DO,
	RD_OPT1_DI,
	RD_OPT2_DI,
	RD_OPT1_DO,
	RD_OPT2_DO,
	RD_SAME_POLE_DI,
	RD_SAME_POLE_DO,
	RD_HDL_BOX_DI,
	RD_HDL_BOX_DO,
	RD_VT_BOX_DI,
	RD_VT_BOX_DO,
} RD_SRC_MOD;
/* ��������ͨ�� */
typedef struct
{
	uint8_t		aucId[MAX_ID_LEN + 1];
	uint16_t	unLgcSN;
	uint8_t		aucName[MAX_ID_LEN + 1];
	uint8_t		aucABRV[4];
        t_BOOL		bRec;
	uint8_t		aucRecId[MAX_ID_LEN + 1];
        t_BOOL		bFlag;
	uint8_t		aucFlagId[MAX_ID_LEN + 1];
        t_BOOL		bMea;
	uint8_t		aucMeaId[MAX_ID_LEN + 1];
        t_BOOL		*pbDI;  				  				 /* -1=no measurent channel related. */
	uint8_t		ucDIRefreshRate;		 	/* ˢ���ٶ�,0Ϊ����,1Ϊ����,2Ϊ����,�������� */
        int			iForceSts;  				   		/* -1=not force, TRUE/t_FALSE=force. */
	void		*pvSrc;
	uint32_t	ulChgTime;
	uint32_t	ulChgTimeAfterFilt;
	uint8_t		ucModCh;
        int			iVal; 													/* Low 15 bit is now status(TRUE or t_FALSE), bit15(0x8000) is flag of force. */
	int			iMeaCh;   
        t_BOOL		bVal;
	uint32_t	ulFiltTime;
	uint8_t		ReserveAttribute;							/* �Ƿ�����ƽ̨ʹ�ñ�־��0: ����ʹ��; 1: ƽ̨ʹ�� */
	uint8_t		DebounceTimeSetMod;					/* ȥ����ʱ�����÷�ʽ��־ */
	uint8_t		DebounceTimeDingzhiTag[MAX_ID_LEN + 1];
        t_BOOL		bDIInvalidDftVal;		/* DI��Чʱ��Ĭ��ֵ����ǰֻ�����ܲ����������� */
        t_BOOL		bSOE;							/* 1: �γ� 0: ���γ� */
	uint8_t		ucMmiShow;				/* �Ƿ����˻���������ʾ��ͨ��ֵ*/
	uint8_t		ucVtBoxPos;				/* �������λ�ñ�ţ���0��ʼ */
	uint32_t	servertype;					/* �������� */
	uint32_t	ChOffset;   					/* �洢��ַƫ�� */
	RD_PART_INFO *p_part;
	RD_SRC_MOD	mod;
} RD_LGC_DI_CH;

typedef struct			/* ����ͨ�� */
{
	uint8_t		aucId[MAX_ID_LEN + 1];
	uint16_t	unLgcSN;
	uint8_t		aucName[MAX_ID_LEN + 1];
	uint8_t		aucABRV[4];
	uint8_t		ucModCh;
        t_BOOL		bValid;
        t_BOOL		bRec;
	uint8_t		aucRecId[MAX_ID_LEN + 1];
        t_BOOL		bFlag;
	uint8_t		aucFlagId[MAX_ID_LEN + 1];
        t_BOOL		bMea;
	uint8_t		aucMeaId[MAX_ID_LEN + 1];
        t_BOOL		bCtrl;
	uint8_t		ucCtrlAttr;
	void		*pvSrc;
        int			iForceSts;  			   /* -1=not force, TRUE/t_FALSE=force. */
        t_BOOL		bVal;
	int			iTripDOCnt; 				 /* DO��բ���� */
	uint8_t		ReserveAttribute;
	uint8_t		ucMmiShow;				/* �Ƿ����˻���������ʾ��ͨ��ֵ*/
	uint8_t		ucVtBoxPos;		/* �������λ�ñ�ţ���0��ʼ */
	uint32_t	servertype;	/* �������� */
	RD_PART_INFO *p_part;
	RD_SRC_MOD	mod;
} RD_LGC_DO_CH;

typedef struct			/* Ӳ��ͨ������ */
{
	uint8_t		aucId[MAX_ID_LEN + 1];
	uint8_t		aucABRV[4];
	float		fMaxVal;
	float		fMinVal;
	uint8_t		ucModCh;
	float		fCoff;										/* CT���ϵ�� */
	uint16_t	uFstRatedVal;							/* һ�ζֵ */
	uint16_t	uSecRatedVal;						/* ���ζֵ */
	float		fOriginCoff;							/* ����ԭʼ����ֵ */
	float		fSetCoff;								/* �趨ϵ����Դ��Ӳ�����û�������� */
	float		fAmendCoff;
	float		fGain;										/* ����ϵ�� */
	float		fRatio;
	uint8_t		ucUnit;
	uint8_t		OptAOEnable;							/* ���ù����� */
	int			iSmplCh; 									/* ˲ʱֵ�洢ͨ�� */
	uint8_t		FactorSetModWord;				/* ���ò������÷�ʽ�� */
	uint8_t		MaxValueDingzhiTagBase[MAX_ID_LEN + 1];				/* �߼���־�ַ��� */
	uint8_t		MinValueDingzhiTagBase[MAX_ID_LEN + 1];
	uint8_t		ScalefactorDingzhiTagBase[MAX_ID_LEN + 1];
	uint8_t		OptAONameString[MAX_ID_LEN + 1];
	float		fExcCoff;										/* ���ƫ��ֵ */
        t_BOOL		bSetOptAo;    									/* ����Ϊ����AO */
	uint8_t		aucAoId[MAX_ID_LEN + 1];				/* ���������߼���־ */
        t_BOOL		bSetAo;    										/* ����ΪAO */
	uint8_t		aucAoLogicId[MAX_ID_LEN + 1];		/* AO�����߼���־ */
	uint8_t		ucMmiShow;									/* �Ƿ����˻���������ʾ��ͨ��ֵ*/
	uint8_t		ucVtBoxPos;									/* �������λ�ñ�ţ���0��ʼ */
	uint32_t	servertype;										/* �������� */
	RD_PART_INFO *p_part;   						/* module information. */
} RD_HW_AI_CH; 


enum Mea_Type
{
	RD_MEA_UINT32	= 0x01,
	RD_MEA_FLOAT	= 0x02,
	RD_MEA_COMPLEX	= 0x03,
};
typedef struct			/* �߼�ͨ������ */
{
	uint8_t		aucId[MAX_ID_LEN + 1];
	uint16_t	unLgcSN;
	RD_HW_AI_CH	*phwai;
	uint8_t		ucFiltTp;
	uint8_t		ucUnit;
        t_BOOL		bRec;
	uint8_t		aucRecId[MAX_ID_LEN + 1];
        t_BOOL		bFlag;
	uint8_t		aucFlagId[MAX_ID_LEN + 1];
        t_BOOL		bMea;
	uint8_t		aucMeaId[MAX_ID_LEN + 1];
        t_BOOL		bSetAo;    					/* ����ΪAO. */
	uint8_t		aucAoId[MAX_ID_LEN + 1];		/* AO�����߼���־ */
	//Mea_Value	pdat[MAX_MEA_SAMPLING_NUM];
} RD_LGC_AI_CH; 

typedef struct			/* AO���*/
{
	uint16_t	unLgcSN;
	uint8_t		aucId[MAX_ID_LEN + 1];				/* AO�߼���ʶ */
	uint8_t		aucName[MAX_ID_LEN + 1];		/* AO�ڲ����� */
	uint8_t		aucABRV[4];  								/* �ڲ���� */
	float		fMaxVal;
	float		fMinVal;
	uint8_t		ucModCh;						/* �����������е�ͨ���� */
	int			iAOSrcType;					/* AO��������Դ���� */
	void		*pvSrc;							/* ���ǹ���AI��Դ���ù���AO����Ӧ��Ӳ��AI����ͨ�������ǹ����м�����Դ����AO��Ӧ������Դָ��,����ʹ��ͬ�˲�����Դ */
	float		fOriCoff;							/* ԭʼ���� */
	float		fSetCoff;						/* �趨ϵ����Դ��Ӳ�����û�������� */
	float		fCoff;
	uint8_t		ucUnit;
	uint8_t		FactorSetModWord;								/* ���ò������÷�ʽ�� */
	uint8_t		MaxValueDingzhiTagBaseLen;				/* �߼���־�ַ������� */
	uint8_t		MaxValueDingzhiTagBase[MAX_ID_LEN + 1];	/* �߼���־�ַ��� */
	uint8_t		MinValueDingzhiTagBase[MAX_ID_LEN + 1];
	uint8_t		ScalefactorDingzhiTagBase[MAX_ID_LEN + 1];
	uint8_t		ucOptAOOutputIntv;				/* ���ݷ��ͼ�� */
	uint8_t		ucAttr;										/* �����֣�����ˢ���ٶ� */
	uint8_t		aucSrcId[MAX_ID_LEN + 1];		/* AO����Դ */
	uint8_t		ucSrcType;								/* ����Դ����, real or image. */
	uint8_t		ucVtBoxPos;							/* �������λ�ñ�ţ���0��ʼ */
	uint32_t	servertype;								/* �������� */
	RD_PART_INFO *p_part;							/* ����ģ�� */
} RD_HW_AO_CH;    

enum Handle_Type			/* ���־����������Ҫ�ɽ��е��� */
{
	RD_LGC_DI_HDL	= 0X01,
	RD_LGC_DO_HDL	= 0X02,
	RD_LGC_AI_HDL	= 0X03,
	RD_LGC_AO_HDL	= 0X04,
	/* ����ģ������� */
	RD_LGC_LED_HDL	= 0X05,
	RD_LGC_YB_HDL	= 0x06
};
/************************************************************************************
						ȫ�ֱ���
************************************************************************************/
RD_SYS_INFO		rdinfo_g;
RD_PART_INFO	apartinf_g[MAX_PART_NUM];/*ģ����Ϣ*/
RD_LGC_DI_CH	*plgcdich_g;
RD_LGC_DO_CH	*plgcdoch_g;
RD_HW_AI_CH		*phwaich_g;
RD_LGC_AI_CH	*plgcaich_g;
RD_HW_AO_CH		*phwaoch_g;

int				iLgcDiChNum_g;
int				iSubLgcNum_g;
int				iLgcDoChNum_g;
int				iHwAiChNum_g;
int				iLgcAiChNum_g;
int				iHwAoChNum_g;

uint8_t			uiAppType_g;			/*Ӧ������*/


#endif
