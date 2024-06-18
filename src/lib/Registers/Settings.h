#ifndef _Settings_H_
#define _Settings_H_

// USER CONTROL REGISTERS

#define SYSTEM1 0x00  // Sets device modes.
#define CCA 0x01 // Sets CCA parameters.
#define SNR 0x02 // Estimate RF input CNR value
#define RSSISIG 0x03  //In-band signal RSSI dBμV value.
#define STATUS1 0x04 //System status.
#define CID1 0x05 //Device ID numbers.
#define CID2 0x06 //Device ID numbers.
#define CH 0x07 //Lower 8 bits of 10-bit channel index.
#define CH_START 0x08 //Lower 8 bits of 10-bit channel scan start channel index.
#define CH_STOP 0x09 //Lower 8 bits of 10-bit channel scan stop channel index.
#define CH_STEP 0x0A //Channel scan frequency step. Highest 2 bits of channel indexes.
#define RDSD0 0x0B //RDS data byte 0.
#define RDSD1 0x0C //RDS data byte 1.
#define RDSD2 0x0D //RDS data byte 2.
#define RDSD3 0x0E //RDS data byte 3.
#define RDSD4 0x0F //RDS data byte 4.
#define RDSD5 0x10 //RDS data byte 5.
#define RDSD6 0x11 //RDS data byte 6.
#define RDSD7 0x12 //RDS data byte 7.
#define STATUS2 0x13 //RDS status indicators.
#define VOL_CTL 0x14 //Audio controls.
#define XTAL_DIV0 0x15 //Frequency select of reference clock source
#define XTAL_DIV1 0x16 //Frequency select of reference clock source
#define XTAL_DIV2 0x17 //Frequency select of reference clock source
#define INT_CTRL 0x18 //RDS control



enum SYSTEM1__SWRST
{
    SWRST__Keep = 0, 
    SWRST__Reset  = 1,
};

enum SYSTEM1__RECAL
{
    RECAL__NoReset = 0, 
    RECAL__Reset  = 1,
};

enum SYSTEM1__STNBY 
{
    STNBY__NoStandby = 0, 
    STNBY__Standby  = 1,
};

enum SYSTEM1__RXREQ 
{
    RXREQ__IdleMode = 0, 
    RXREQ__ReceiveMode  = 1,
};

enum SYSTEM1__RDSEN 
{
    RDSEN__NoRDS = 0, 
    RDSEN__RDSEnable  = 1,
};

enum SYSTEM1__FORCE_MO  
{
    FORCE_MO__Auto = 0, 
    FORCE_MO__Mono  = 1,
};

enum SYSTEM1__CHSC  
{
    CHSC__NormalOperation = 0, 
    CHSC__ChannelScanmode  = 1,
};

enum SYSTEM1__CCA_CH_DIS 
{
    CCA_CH_DIS__CCA = 0, 
    CCA_CH_DIS__CH  = 1,
};





enum STATUS1__FSM 
{
    FSM__STBY = 0, 
    FSM__RESET  = 1,
    FSM__CALI = 3, 
    FSM__IDLE  = 4,
    FSM__CALIPLL = 5, 
    FSM__RECEIVEING  = 6,
    FSM__Reserved  = 7,
    FSM__RXCCA  = 8
};

enum STATUS1__RXCCA_FAIL
{
    RXCCA_FAIL__successfulfinds = 0, 
    RXCCA_FAIL__failstofind  = 1
};

enum STATUS1__RXAGCSET
{
    RXAGCSET__NotSettled = 0, 
    RXAGCSET__Settled = 1
};

enum STATUS1__RXAGCERR
{
    RXAGCERR__NoError = 0, 
    RXAGCERR__AGCError = 1
};

enum STATUS1__ST_MO_RX
{
    ST_MO_RX__Mono = 1, 
    ST_MO_RX__Stereo = 0
};


enum CCA__XTAL_INJ 
{
    SineWaveClock = 0, 
    SquareWaveClock = 1
};

enum CCA__XTAL_IMR
{
    IMR__LO_Smaller_RF = 0, 
    IMR__LO_Bigger_RF = 1
};




#define INIT_FREQ    95.3

#define LOW_FREQ    88.0
#define HIGH_FREQ   108.0

#define REG_VOL_CTL_MAX_ANALOG_GAIN 0x07
#define REG_VOL_CTL_MIN_ANALOG_GAIN 0x00
#define REG_VOL_CTL_START_ANALOG_GAIN 0x03


typedef enum 
{
    SCAN_DOWN,
    SCAN_UP
} ScanDirection;

typedef enum 
{
    VOLUME_DOWN,
    VOLUME_UP
} VolumeDirection;




#endif
