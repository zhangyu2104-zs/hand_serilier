#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H
#define pin_ad_spi_rdy 22
#define tof10120_Address_left  0x52
#define tof10120_Address_right 0x53

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

class Devicedriver : public QObject
{
    Q_OBJECT
public:
    explicit Devicedriver(QObject *parent = nullptr);

    //interface function
    void    set_begin(int value);
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

    void    uvc_autoControl(void);

    void    set_UVC_OUT(char UVC_PIN);
    char    DHT11_Read(char *temperature,char *humidity);
    void    set_power_switch(int p48V_baterry);

    void pi_pin_init(void);
    void device_start();
    void device_stop();

private:
    const char pin_key_switch  = 27;
    const char pin_uvc_out     = 6;
    const char pin_temp_left   = 2;
    const char pin_temp_right  = 3 ;
    const char pin_fan_left    = 1;
    const char pin_fan_right   = 23;
    const char pin_power_switch = 0;
    char       uvc_value;
    char       begin_value      = 0;
    
    void set_fan_left(char fan_left_out);
    void set_fan_right(char fan_right_out);
    short DS18B20_Get_Temp(void);	//获取温度
    u8 DS18B20_Init(void);			//初始化DS18B20
    void DS18B20_Start(void);		//开始温度转换
    void DS18B20_Write_Byte(u8 dat);//写入一个字节
    u8 DS18B20_Read_Byte(void);		//读出一个字节
    u8 DS18B20_Read_Bit(void);		//读出一个位
    u8 DS18B20_Check(void);			//检测是否存在DS18B20
    void DS18B20_Rst(void);			//复位DS18B20
    int fd_52,fd_53;

    struct _sensor_data_save
    {
        char    temp[2]={0,0};
        float   infrared[2];
        float   ad_power[2];
        char    fan[2];
    }sensor_data_save;

signals:

};

#endif // DEVICEDRIVER_H
