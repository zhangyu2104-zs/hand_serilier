#ifndef DEVICE_PI_H
#define DEVICE_PI_H

#define pin_ad_spi_rdy 22
#define tof10120_Address_left  0x52
#define tof10120_Address_right 0x53
#define pcf8591_device_Address 0x48
//#define pcf8591_BASE 64
//#define A0 pcf8591BASE+0
//#define A1 pcf8591BASE+1
//#define A2 pcf8591BASE+2
//#define A3 pcf8591BASE+3

#define pin_dq_left		7
#define DS18B20_IO_IN()  	pinMode (pin_dq_left, INPUT)
#define DS18B20_IO_OUT() 	pinMode (pin_dq_left, OUTPUT)
//IO操作函数
#define	DS18B20_DQ_OUT1 digitalWrite(pin_dq_left, HIGH) 		//数据端口
#define	DS18B20_DQ_OUT0 digitalWrite(pin_dq_left, LOW) 		//数据端口
#define	DS18B20_DQ_IN  	digitalRead(pin_dq_left)  		   //数据端口
#define   u8	unsigned char
#define   u16  	unsigned int



#include <QObject>


class device_pi
{
//    Q_OBJECT
public:
     device_pi();

    //interface function
    bool    get_keyValue_start(void);
    bool    get_UVC_status(void);
    float   get_temperature_sensor_left(void);
    float   get_temperature_sensor_right(void);
    float   get_supply_power_48V(void);
    float   get_supply_power_5V(void);
    float   get_infrared_range_left(void);
    float   get_infrared_range_right(void);
    char    get_fan_left_status(void);
    char    get_fan_right_status(void);
    char    get_begin(void);
    char    get_demo(void);

    void    uvc_autoControl(void);
    void    demo_autoControl(void);
    void    device_stop(void);

    void    set_UVC_OUT(char UVC_PIN);
    char    DHT11_Read(char *temperature,char *humidity);
    void    set_begin(int value);
    void    set_power_switch(int p48V_baterry);
    void    set_demo(int value);
    void set_fan_left(char fan_left_out);
    void set_fan_right(char fan_right_out);

private:

    const char pin_key_switch  = 27;
    const char pin_uvc_out     = 6;
    const char pin_temp_left   = 2;
    const char pin_temp_right  = 3 ;
    const char pin_fan_left    = 1;
    const char pin_fan_right   = 23;
    const char pin_power_switch = 21;
    char       uvc_value;
    char       begin_value;
    char       demo_value;

    int fd_52,fd_53;
    int tempBorder_times;

    struct _sensor_data_save
    {
        char    temp[2]={0,0};
        float   infrared[2];
        float   ad_power[2];
        char    fan[2];
    }sensor_data_save;

//    mydebug debug_obj;

    void SetMyAppAutoRun(bool isstart);
    void pi_pin_init(void);

    short DS18B20_Get_Temp(void);	//获取温度
    u8 DS18B20_Init(void);			//初始化DS18B20
    void DS18B20_Start(void);		//开始温度转换
    void DS18B20_Write_Byte(u8 dat);//写入一个字节
    u8 DS18B20_Read_Byte(void);		//读出一个字节
    u8 DS18B20_Read_Bit(void);		//读出一个位
    u8 DS18B20_Check(void);			//检测是否存在DS18B20
    void DS18B20_Rst(void);			//复位DS18B20


protected slots:
    void showValue(int value);



};

#endif // DEVICE_PI_H
