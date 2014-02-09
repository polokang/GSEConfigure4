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


/* 模件信息结构 */
typedef struct
{
	uint8_t		aucId[MAX_ID_LEN + 1];
	uint8_t		ucType;
	uint8_t		ucPosition;
	uint8_t		aucHwAddr[4];
	uint8_t		ucAiNum;
	uint8_t		ucAoNum;  						/* 为光纵和励磁添加AO的个数 */
	uint8_t		ucDiNum;
	uint8_t		ucDoNum;
	uint16_t	unAiSmplRate;
	uint16_t	unAiPts;							/* 周波采样点数 */
	uint32_t	ulDIModCurVaule;			/* DI模件的当前值，只对DI摸件有效 */
	uint8_t		iVtBoxSeqNo;					/* 序号 */
	uint8_t		ucVtBoxPos;					/* 虚拟机箱位置编号，从0开始 */
	uint8_t		iVtBoxAddrInSameKind;			/* 地址，供驱动程序使用 */
	uint8_t		aucVtBoxFd[MAX_ID_LEN + 1];	/* 所位于虚拟机箱的设备描述符 */
	uint8_t		ucAiModType;								/* 交流模件类型 */
	uint32_t	servertype;									/* 服务类型 */
} RD_PART_INFO;

/* 装置资源配置结构 */
typedef struct
{
	uint16_t	unPartNum;
} RD_SYS_INFO;

/* 各种机箱类型，以后可以适当调整， 为光纵修改，6/8/2006 */
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

typedef enum		/* 模件枚举 */
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
/* 开入配置通道 */
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
	uint8_t		ucDIRefreshRate;		 	/* 刷新速度,0为快速,1为中速,2为慢速,其他保留 */
        int			iForceSts;  				   		/* -1=not force, TRUE/t_FALSE=force. */
	void		*pvSrc;
	uint32_t	ulChgTime;
	uint32_t	ulChgTimeAfterFilt;
	uint8_t		ucModCh;
        int			iVal; 													/* Low 15 bit is now status(TRUE or t_FALSE), bit15(0x8000) is flag of force. */
	int			iMeaCh;   
        t_BOOL		bVal;
	uint32_t	ulFiltTime;
	uint8_t		ReserveAttribute;							/* 是否保留给平台使用标志，0: 保护使用; 1: 平台使用 */
	uint8_t		DebounceTimeSetMod;					/* 去抖动时间设置方式标志 */
	uint8_t		DebounceTimeDingzhiTag[MAX_ID_LEN + 1];
        t_BOOL		bDIInvalidDftVal;		/* DI无效时的默认值，当前只对智能操作箱起作用 */
        t_BOOL		bSOE;							/* 1: 形成 0: 不形成 */
	uint8_t		ucMmiShow;				/* 是否在人机界面上显示该通道值*/
	uint8_t		ucVtBoxPos;				/* 虚拟机箱位置编号，从0开始 */
	uint32_t	servertype;					/* 服务类型 */
	uint32_t	ChOffset;   					/* 存储地址偏移 */
	RD_PART_INFO *p_part;
	RD_SRC_MOD	mod;
} RD_LGC_DI_CH;

typedef struct			/* 开出通道 */
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
	int			iTripDOCnt; 				 /* DO跳闸计数 */
	uint8_t		ReserveAttribute;
	uint8_t		ucMmiShow;				/* 是否在人机界面上显示该通道值*/
	uint8_t		ucVtBoxPos;		/* 虚拟机箱位置编号，从0开始 */
	uint32_t	servertype;	/* 服务类型 */
	RD_PART_INFO *p_part;
	RD_SRC_MOD	mod;
} RD_LGC_DO_CH;

typedef struct			/* 硬件通道配置 */
{
	uint8_t		aucId[MAX_ID_LEN + 1];
	uint8_t		aucABRV[4];
	float		fMaxVal;
	float		fMinVal;
	uint8_t		ucModCh;
	float		fCoff;										/* CT变比系数 */
	uint16_t	uFstRatedVal;							/* 一次额定值 */
	uint16_t	uSecRatedVal;						/* 二次额定值 */
	float		fOriginCoff;							/* 保存原始配置值 */
	float		fSetCoff;								/* 设定系数，源自硬件配置或软件配置 */
	float		fAmendCoff;
	float		fGain;										/* 增益系数 */
	float		fRatio;
	uint8_t		ucUnit;
	uint8_t		OptAOEnable;							/* 设置光纵量 */
	int			iSmplCh; 									/* 瞬时值存储通道 */
	uint8_t		FactorSetModWord;				/* 配置参数设置方式字 */
	uint8_t		MaxValueDingzhiTagBase[MAX_ID_LEN + 1];				/* 逻辑标志字符串 */
	uint8_t		MinValueDingzhiTagBase[MAX_ID_LEN + 1];
	uint8_t		ScalefactorDingzhiTagBase[MAX_ID_LEN + 1];
	uint8_t		OptAONameString[MAX_ID_LEN + 1];
	float		fExcCoff;										/* 零点偏移值 */
        t_BOOL		bSetOptAo;    									/* 设置为光纵AO */
	uint8_t		aucAoId[MAX_ID_LEN + 1];				/* 光纵引用逻辑标志 */
        t_BOOL		bSetAo;    										/* 设置为AO */
	uint8_t		aucAoLogicId[MAX_ID_LEN + 1];		/* AO引用逻辑标志 */
	uint8_t		ucMmiShow;									/* 是否在人机界面上显示该通道值*/
	uint8_t		ucVtBoxPos;									/* 虚拟机箱位置编号，从0开始 */
	uint32_t	servertype;										/* 服务类型 */
	RD_PART_INFO *p_part;   						/* module information. */
} RD_HW_AI_CH; 


enum Mea_Type
{
	RD_MEA_UINT32	= 0x01,
	RD_MEA_FLOAT	= 0x02,
	RD_MEA_COMPLEX	= 0x03,
};
typedef struct			/* 逻辑通道配置 */
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
        t_BOOL		bSetAo;    					/* 设置为AO. */
	uint8_t		aucAoId[MAX_ID_LEN + 1];		/* AO引用逻辑标志 */
	//Mea_Value	pdat[MAX_MEA_SAMPLING_NUM];
} RD_LGC_AI_CH; 

typedef struct			/* AO输出*/
{
	uint16_t	unLgcSN;
	uint8_t		aucId[MAX_ID_LEN + 1];				/* AO逻辑标识 */
	uint8_t		aucName[MAX_ID_LEN + 1];		/* AO内部名称 */
	uint8_t		aucABRV[4];  								/* 内部简称 */
	float		fMaxVal;
	float		fMinVal;
	uint8_t		ucModCh;						/* 在所属摸件中的通道号 */
	int			iAOSrcType;					/* AO的数据来源类型 */
	void		*pvSrc;							/* 若是光纵AI来源，该光纵AO所对应的硬件AI物理通道，若是光纵中间结果来源，该AO对应的数据源指针,可以使用同杆并架来源 */
	float		fOriCoff;							/* 原始配置 */
	float		fSetCoff;						/* 设定系数，源自硬件配置或软件配置 */
	float		fCoff;
	uint8_t		ucUnit;
	uint8_t		FactorSetModWord;								/* 配置参数设置方式字 */
	uint8_t		MaxValueDingzhiTagBaseLen;				/* 逻辑标志字符串长度 */
	uint8_t		MaxValueDingzhiTagBase[MAX_ID_LEN + 1];	/* 逻辑标志字符串 */
	uint8_t		MinValueDingzhiTagBase[MAX_ID_LEN + 1];
	uint8_t		ScalefactorDingzhiTagBase[MAX_ID_LEN + 1];
	uint8_t		ucOptAOOutputIntv;				/* 光纵发送间隔 */
	uint8_t		ucAttr;										/* 属性字，包含刷新速度 */
	uint8_t		aucSrcId[MAX_ID_LEN + 1];		/* AO数据源 */
	uint8_t		ucSrcType;								/* 数据源类型, real or image. */
	uint8_t		ucVtBoxPos;							/* 虚拟机箱位置编号，从0开始 */
	uint32_t	servertype;								/* 服务类型 */
	RD_PART_INFO *p_part;							/* 所属模件 */
} RD_HW_AO_CH;    

enum Handle_Type			/* 各种句柄，根据需要可进行调整 */
{
	RD_LGC_DI_HDL	= 0X01,
	RD_LGC_DO_HDL	= 0X02,
	RD_LGC_AI_HDL	= 0X03,
	RD_LGC_AO_HDL	= 0X04,
	/* 增加模拟量输出 */
	RD_LGC_LED_HDL	= 0X05,
	RD_LGC_YB_HDL	= 0x06
};
/************************************************************************************
						全局变量
************************************************************************************/
RD_SYS_INFO		rdinfo_g;
RD_PART_INFO	apartinf_g[MAX_PART_NUM];/*模件信息*/
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

uint8_t			uiAppType_g;			/*应用类型*/


#endif
