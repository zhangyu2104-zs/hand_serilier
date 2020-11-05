#include "devicedriver.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>

Devicedriver::Devicedriver(QObject *parent) : QObject(parent)
{
    pi_pin_init();
}

void Devicedriver::set_begin(int value)
{
    begin_value = value;
}
char Devicedriver::get_begin()
{
    return begin_value;
}

bool Devicedriver::get_keyValue_start()
{
    if (digitalRead(pin_key_switch) == 1)
    {
        delay(20);
        if (digitalRead(pin_key_switch) == 1)
            return true;
        else return false;
    }
    else
        return false;
}

bool Devicedriver::get_UVC_status()
{
    return uvc_value;
}
void Devicedriver::set_fan_left(char fan_left_out)
{
    digitalWrite(pin_fan_left,fan_left_out);
    sensor_data_save.fan[0] = fan_left_out;
}

void Devicedriver::set_fan_right(char fan_right_out)
{
    digitalWrite(pin_fan_right,fan_right_out);
    sensor_data_save.fan[1] = fan_right_out;
}

char Devicedriver::get_fan_left_status()
{
    return sensor_data_save.fan[0];
}


char Devicedriver::get_fan_right_status()
{
    return sensor_data_save.fan[1];
}

float Devicedriver::get_temperature_sensor_left()
{
//    return sensor_data_save.temp[0];
    float temp_debug=0;
//    ds18b20 temp;
    temp_debug = DS18B20_Get_Temp();
    temp_debug /= 10;
    return temp_debug;
//    qDebug("temp = %.2f",temp_debug);
}



float Devicedriver::get_temperature_sensor_right()
{
    return 0;
}
float Devicedriver::get_infrared_range_left()
{
    unsigned short int left_dis;
    left_dis = wiringPiI2CReadReg16(fd_52,0x00);
    left_dis = (left_dis<<8) | (left_dis>>8);
//    qDebug("left_dis:%d",left_dis);
    return left_dis;
}

float Devicedriver::get_infrared_range_right()
{
    unsigned short int right_dis;
    right_dis = wiringPiI2CReadReg16(fd_53,0x00);
    right_dis = (right_dis<<8) | (right_dis>>8);
//    qDebug("right_dis:%d",right_dis);
    return right_dis;
}

void Devicedriver::set_UVC_OUT(char UVC_PIN)
{
    if(UVC_PIN)
    {
        digitalWrite(pin_uvc_out,1);
        uvc_value = 1;
        qDebug("uvc_out:%d",uvc_value);
    }
    else
    {
        digitalWrite(pin_uvc_out,0);
        uvc_value = 0;
    }

}

void Devicedriver::pi_pin_init()
{
    wiringPiSetup() ;
    pinMode (pin_uvc_out,OUTPUT) ;
    pinMode (pin_key_switch,INPUT) ;
    pullUpDnControl(pin_key_switch, PUD_UP);
    pinMode(pin_ad_spi_rdy,INPUT);
    fd_52= wiringPiI2CSetup(tof10120_Address_left);
    fd_53= wiringPiI2CSetup(tof10120_Address_right);
    pinMode (pin_fan_left,OUTPUT) ;
    pinMode (pin_fan_right,OUTPUT) ;
    pinMode(pin_power_switch,OUTPUT);
//    digitalWrite(pin_power_switch,0);
    delay(10);
}
void Devicedriver::device_start()
{
    set_UVC_OUT(1);
    //set_fan_left(0);
   // qDebug("uvc_value =%d, demo_value =%d",get_UVC_status(),get_fan_left_status());
}
void Devicedriver::device_stop()
{
    set_UVC_OUT(0);
    //set_fan_left(0);
   // qDebug("uvc_value =%d, demo_value =%d",get_UVC_status(),get_fan_left_status());
}

void Devicedriver::uvc_autoControl(void)
{
    unsigned int counter =0;
    if(get_keyValue_start())
    {
        qDebug("key_start_down!");
        if((get_temperature_sensor_left()<60) && ((get_infrared_range_left()<500) || (get_infrared_range_right()<500)))
        {
            set_fan_left(0);
            set_UVC_OUT(1);
            set_fan_left(1);
            set_fan_right(1);
            qDebug("uvc_out: 1");
        }
        else
        {
            set_UVC_OUT(0);
            set_fan_left(0);
            set_fan_right(0);
            qDebug("uvc_out: 0");
        }
    }
    else
    {
        qDebug("key_start_up!");
        set_UVC_OUT(0);
        set_fan_left(0);
        set_fan_right(0);
        uvc_value = 0;
    }
    qDebug("temp = %.2f",get_temperature_sensor_left());
    qDebug("dis_left = %f dis_left_right= %f",get_infrared_range_left(),get_infrared_range_right());
    qDebug("uvc_out: %d",get_UVC_status());
    //qDebug("fan_left: %d",get_fan_left_status());
//    if(counter % 300 ==0)
//        get_temperature_sensor_left_debug();
    delay(10);
    counter++;
}

//复位DS18B20
void Devicedriver::DS18B20_Rst(void)
{
    DS18B20_IO_OUT(); 	//SET GPIO7 OUTPUT
    DS18B20_DQ_OUT0; 	//拉低DQ
    delayMicroseconds(750);    	//拉低750us
    DS18B20_DQ_OUT1; 	//DQ1
    delayMicroseconds(15);     	//15US
}

//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
u8 Devicedriver::DS18B20_Check(void)
{
    u8 retry=0;
    DS18B20_IO_IN();	//SET GPIO7 INPUT
    while (DS18B20_DQ_IN&&retry<200)
    {
        retry++;
        delayMicroseconds(1);
    };
    if(retry>=200)return 1;
    else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
    {
        retry++;
        delayMicroseconds(1);
    };
    if(retry>=240)return 1;
    return 0;
}
//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在
u8 Devicedriver::DS18B20_Init(void)
{
    wiringPiSetup() ;
    DS18B20_Rst();
    return DS18B20_Check();
}

//从DS18B20读取一个位
//返回值：1/0
u8 Devicedriver::DS18B20_Read_Bit(void)
{
    u8 data;
    DS18B20_IO_OUT();	//SET PG11 OUTPUT
    DS18B20_DQ_OUT0;
    delayMicroseconds(2);
    DS18B20_DQ_OUT1;
    DS18B20_IO_IN();	//SET PG11 INPUT
    delayMicroseconds(12);
    if(DS18B20_DQ_IN)data=1;
    else data=0;
    delayMicroseconds(50);
    return data;
}

//从DS18B20读取一个字节
//返回值：读到的数据
u8 Devicedriver::DS18B20_Read_Byte(void)
{
    u8 i,j,dat;
    dat=0;
    for (i=1;i<=8;i++)
    {
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }
    return dat;
}

//写一个字节到DS18B20
//dat：要写入的字节
void Devicedriver::DS18B20_Write_Byte(u8 dat)
 {
    u8 j;
    u8 testb;
    DS18B20_IO_OUT();	//SET PG11 OUTPUT;
    for (j=1;j<=8;j++)
    {
        testb=dat&0x01;
        dat=dat>>1;
        if (testb)
        {
            DS18B20_DQ_OUT0;	// Write 1
            delayMicroseconds(2);
            DS18B20_DQ_OUT1;
            delayMicroseconds(60);
        }
        else
        {
            DS18B20_DQ_OUT0;	// Write 0
            delayMicroseconds(60);
            DS18B20_DQ_OUT1;
            delayMicroseconds(2);
        }
    }
}


//开始温度转换
void Devicedriver::DS18B20_Start(void)
{
    DS18B20_Rst();
    DS18B20_Check();
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0x44);	// convert
}

//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250）
short Devicedriver::DS18B20_Get_Temp(void)
{
    u8 temp;
    u8 TL,TH;
    short tem;
    DS18B20_Start ();  			// ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0xbe);	// convert
    TL=DS18B20_Read_Byte(); 	// LSB
    TH=DS18B20_Read_Byte(); 	// MSB

    if(TH>7)
    {
        TH=~TH;
        TL=~TL;
        temp=0;					//温度为负
    }else temp=1;				//温度为正
    tem=TH; 					//获得高八位
    tem<<=8;
    tem+=TL;					//获得底八位
    tem=(float)tem*0.625;		//转换
    if(temp)return tem; 		//返回温度值
    else return -tem;
}

