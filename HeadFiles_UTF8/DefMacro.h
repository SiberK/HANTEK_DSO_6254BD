#ifndef _HT_SCOPE_DEFINE_MACRO_H
#define _HT_SCOPE_DEFINE_MACRO_H

#define MAX_TIMEDIV_NUM		      	36	// Общее количество передач временной базы
#define TIMEDIV_OFFSET		      	2	// смещение временной базы

#define DRIVERVERLEN			8	// Должно быть четное число
#define AUTOSET_TIME1 			19
#define AUTOSET_TIME2 			18
#define ZERO_START_VOLT 		5
#define BUF_10K_LIMIT			

#define	PI			      	3.14159265358979323846


#define BUF_4K_LEN		      	0x1000
#define BUF_3K_LEN		      	0x0C00	//3072
#define BUF_8K_LEN		      	0x2000
#define BUF_16K_LEN		      	0x4000
#define BUF_32K_LEN		      	0x8000
#define BUF_64K_LEN		      	0x10000

#define BUF_INSERT_LEN 		      	BUF_72K_LEN


#define DEF_READ_DATA_LEN	      	BUF_4K_LEN 	//BUF_10K_LEN		//Длина считываемых данных по умолчанию
#define DEF_DRAW_DATA_LEN	      	2500 		//10000


#define MAX_INSERT_TIMEDIV	      	6	//200nS	Максимальная временная база, необходимая для интерполяции
#define MAX_DOUBLE_TIMEDIV	      	MAX_INSERT_TIMEDIV
#define MAX_SF_T_TIMEDIV	      	MAX_INSERT_TIMEDIV - 2  //Необходимо программное обеспечение для определения временной базы триггера.
#define MAX_SINE_TIMEDIV	      	3////2////2  //Менее 3 необходимо синусоидально интерполировать




#define MIN_SCAN_TIMEDIV	      	25//22	//Минимальная временная развертка режима сканирования
#define MIN_ROLL_TIMEDIV	      	27//24	//
#define MIN_ROLL_TIMEDIV	      	27//24	//



#define SINE_WAVE_LEN		       	128 	//Длина сигнала среднего окна
#define MAX_ETS_TIMEDIV		       	3   	//0,1,2,3
#define ETS_SAMPLING_100M	       	0   	//ETS 100M

//9-точечная калибровка опорного уровня *********************************************/
#define NEW_CAL_LEVEL_LEN	       	400 	//1*9+9*(4*9)=334		//首个点为9代表9点校准发


// вертикальный ***********************************************************/
//определениеCH
#define CH1			    	0
#define CH2			    	1
#define CH3			    	2
#define CH4			    	3

#define MAX_CH_NUM		    	4

#define	TRG_T				4
#define	TRG_V				5


#define HORIZONTAL		    	MAX_CH_NUM    	//CH1/CH2/CH3/CH4/HORIZONTAL/(уровеньlever)
#define MATH			    	MAX_CH_NUM    	//CH1/CH2/CH3/CH4/MATH/REF (вертикальный lever)
#define REF			    	MAX_CH_NUM+1	//CH1/CH2/CH3/CH4/MATH/REF (вертикальный lever)
#define ALL_CH			    	MAX_CH_NUM+2
#define MIN_DATA		    	0	       	//
#define MAX_DATA		    	255	       	//
#define MID_DATA		    	128	       	//
#define MAX_VOLTDIV_NUM		    	12

#define YT			    	0
#define XY			    	1
#define YT_NORMAL		    	0
#define YT_SCAN			    	1
#define YT_ROLL			    	2

#define DC			    	0
#define AC			    	1
#define GND			    	2


// TRIGGER **********************************************************/
#define MAX_TRIGGER_SOURCE_NUM		MAX_CH_NUM+2	//CH1/CH2/CH3/CH4/EXT/(EXT/10)
#define MAX_ALT_TRIGGER_NUM	    	MAX_CH_NUM+2   	//CH1/CH2/CH3/CH4
#define EXT			    	MAX_CH_NUM
#define EXT10			    	MAX_CH_NUM + 1

#define EDGE			    	0
#define PULSE			    	1
#define VIDEO			    	2
#define CAN			    	3
#define LIN			    	4
#define UART			    	5
#define SPI			    	6
#define IIC			    	7

#define FORCE			    	0x80


#define AUTO			    	0
#define NORMAL			    	1
#define SINGLE			    	2

#define RISE			    	0
#define FALL			    	1

//结构体
typedef struct _HT_MEASURE_ITEM
{
	int Enable;
	short nSource;
	short nType;
}HT_MEASURE_ITEM, *PHT_MEASURE_ITEM;
//
struct CAN_DECODE
{
	unsigned char nInfo;
	unsigned char nAck;
	unsigned char nEOF;
	//unsigned char pCRC[3];
	unsigned char pData[8];
	unsigned short nReadCRC;
	unsigned short nCalCRC;
	unsigned short nStartIndex;
	unsigned short nEndIndex;
	unsigned int nID;
};
struct LIN_DECODE
{
	unsigned char  nID;
	unsigned char pData[8];
	unsigned char nReadCRC;
	unsigned char nCalCRC;
	unsigned short nStartIndex;
	unsigned short nEndIndex;

};
struct IIC_DECODE
{
	unsigned char nData;
	unsigned char nType;
	unsigned char nAck;
	unsigned short nStartIndex;
	unsigned short nEndIndex;
};
struct UART_DECODE
{
	unsigned char nData;
	unsigned short nStartIndex;
	unsigned short nEndIndex;
};
struct SPI_DECODE
{
	unsigned char nData[4];
	unsigned short nStartIndex;
	unsigned short nEndIndex;
};

/*
typedef struct _HT_DATA_MATCH
{
	unsigned short nTimeDIV			;//временная база
	unsigned short nVoltDIV			;//Уровень напряжения
	unsigned short nLeverPos		;//Положение нулевого уровня
	long nHTriggerPos			;//горизонтальная триггерная точка
	unsigned int nReadDataLen		;//Чтение длины данных
	unsigned int nAlreadyReadLen		;//Длина прочитанных данных
}DATAMATCH, *PDATAMATCH;

typedef struct _HT_RELAY_CONTROL
{
	unsigned int bCHEnable[MAX_CH_NUM];
	unsigned short nCHVoltDIV[MAX_CH_NUM];
	unsigned short nCHCoupling[MAX_CH_NUM];
	unsigned int bCHBWLimit[MAX_CH_NUM];
	unsigned short nTrigSource;
	unsigned int bTrigFilt;
	unsigned short nALT;
}RELAYCONTROL, *PRELAYCONTROL;
typedef struct _HT_CONTROL_DATA
{
	unsigned short nCHSet;
	unsigned short nTimeDIV;
	unsigned short nTriggerSource;
	unsigned short nHTriggerPos;
	unsigned short nVTriggerPos;
	unsigned short nTriggerSlope;
	unsigned int nBufferLen;//对应于10K，1M，2M.....16M
	unsigned int nReadDataLen;//记录本次将要从硬件读取的数据总共长度
	unsigned int nAlreadyReadLen;//记录本次已经读取的数据长度，在扫描/滚动模式下有效,在NORMAL模式下无效
	unsigned short nALT;
	unsigned short nETSOpen;
	unsigned short nDriverCode;		//驱动编号
	unsigned int nLastAddress;  //    记录扫描模式上次读取的终止地址
	unsigned short nFPGAVersion;//FPGA 版本号
	//unsigned short nAddressOffset;//触发抖动加偏移


}CONTROLDATA, *PCONTROLDATA;
*/






//
#define MAX_DRIVER_NAME				64		//Максимальная длина имени устройства
#define USB_PACK_SIZE				512		//Размер пакета загрузки USB



///////////////////////////////////////////////////
#endif
