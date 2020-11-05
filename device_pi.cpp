#include "device_pi.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include <pcf8591.h>
//#include "mydialog.h"

//MyObject::MyObject(QObject *parent) : QObject(parent)
device_pi::device_pi()
{
    pi_pin_init();
//    MyDialog *dlg = new MyDialog(this);
    // 将对话框中的自定义信号与主界面中的自定义槽进行关联
//  connect(dlg, SIGNAL(dlgReturn(int)), this, SLOT(showValue(int)));
//    connect(dlg, &MyDialog::dlgReturn, this, &Widget::showValue);
}


void device_pi::showValue(int value)         // 自定义槽
{
//    ui->label->setText(tr("获取的值是：%1").arg(value));
    set_begin(value);
    qDebug("rec_begin =%d",get_begin());
}

void device_pi::set_power_switch(int p48V_baterry)
{
    digitalWrite(pin_power_switch,p48V_baterry);
    qDebug("p48V-->battery");
}

//void device_pi::show_demo(int value)
//{
//    set_demo(value);
//    qDebug("demo_value = %d",get_demo());
//}


//-----------------------------------------------------------------
void device_pi::set_begin(int value)
{
    begin_value = value;
}

char device_pi::get_begin()
{
    return begin_value;
}

void device_pi::set_demo(int value)
{
    demo_value = value;
    begin_value = ~value;
}

char device_pi::get_demo()
{
    return demo_value;
}

bool device_pi::get_keyValue_start()
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

bool device_pi::get_UVC_status()
{
    return uvc_value;
}

float device_pi::get_temperature_sensor_left()
{
//    return sensor_data_save.temp[0];
    float temp_debug=0;
//    ds18b20 temp;
    temp_debug = DS18B20_Get_Temp();
    temp_debug /= 10;
    return temp_debug;
//    qDebug("temp = %.2f",temp_debug);
}



float device_pi::get_temperature_sensor_right()
{
    return 0;
}


float device_pi::get_supply_power_5V()
{
//    qDebug("5v_value: %dmv",analogRead(65)*3300/255);
    return analogRead(65)*(5/3.3)/255;
}

float device_pi::get_supply_power_48V()
{
//    qDebug("48v_value: %dmv",analogRead(64)*3300/255);
    return analogRead(65)*(48/3.3)/255;
}

float device_pi::get_infrared_range_left()
{
    unsigned short int left_dis;
    left_dis = wiringPiI2CReadReg16(fd_52,0x00);
    left_dis = (left_dis<<8) | (left_dis>>8);
//    qDebug("left_dis:%d",left_dis);
    return left_dis;
}

float device_pi::get_infrared_range_right()
{
    unsigned short int right_dis;
    right_dis = wiringPiI2CReadReg16(fd_53,0x00);
    right_dis = (right_dis<<8) | (right_dis>>8);
//    qDebug("right_dis:%d",right_dis);
    return right_dis;
}

void device_pi::pi_pin_init()
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
//        pcf8591Setup(BASE,Address);
    pcf8591Setup(64,0x48);
    delay(10);
}


void device_pi::set_UVC_OUT(char UVC_PIN)
{
    if(UVC_PIN)
    {
        digitalWrite(pin_uvc_out,1);
        uvc_value = 1;
    }
    else
    {
        digitalWrite(pin_uvc_out,0);
        uvc_value = 0;
    }

}

void device_pi::set_fan_left(char fan_left_out)
{
    digitalWrite(pin_fan_left,fan_left_out);
    sensor_data_save.fan[0] = fan_left_out;
}

void device_pi::set_fan_right(char fan_right_out)
{
    digitalWrite(pin_fan_right,fan_right_out);
    sensor_data_save.fan[1] = fan_right_out;
}

char device_pi::get_fan_left_status()
{
    return sensor_data_save.fan[0];
}


char device_pi::get_fan_right_status()
{
    return sensor_data_save.fan[1];
}

void device_pi::device_stop()
{
    set_UVC_OUT(0);
    set_fan_left(0);
    qDebug("uvc_value =%d, demo_value =%d",get_UVC_status(),get_fan_left_status());
}

void device_pi::demo_autoControl()
{
    if(get_keyValue_start())
    {
        set_UVC_OUT(0);
        delay(10);
        set_fan_left(1);
        delay(10);
    }
    else
    {
        set_fan_left(0);
        set_UVC_OUT(0);
        delay(10);
    }
    qDebug("fan_value = %d uvc_out =%d",get_fan_left_status(),get_UVC_status());
}

void device_pi::uvc_autoControl()
{
    unsigned int counter =0;
    if(get_keyValue_start())
    {
        qDebug("key_start_down!");
        if((tempBorder_times<=3) && ((get_infrared_range_left()<500) || (get_infrared_range_right()<500)))
        {
            set_fan_left(0);
            set_UVC_OUT(1);
            set_fan_left(1);
//            set_fan_right(1);
            qDebug("uvc_out: 1");
        }
        else
        {
            set_UVC_OUT(0);
            set_fan_left(0);
//            set_fan_right(0);
            qDebug("uvc_out: 0");
        }
    }
    else
    {
        qDebug("key_start_up!");
        set_UVC_OUT(0);
        set_fan_left(0);
//        set_fan_right(0);
//        uvc_value = 0;
    }
    if(get_temperature_sensor_left()>70)
    {
        tempBorder_times++;
        if(tempBorder_times>3)
            tempBorder_times=4;
    }
    else tempBorder_times=0;
    qDebug("temp = %.2f",get_temperature_sensor_left());
    qDebug("dis_left = %f dis_left_right= %f",get_infrared_range_left(),get_infrared_range_right());
    qDebug("uvc_out: %d",get_UVC_status());
    qDebug("fan_left: %d",get_fan_left_status());
    qDebug("tempBorder_times=%d",tempBorder_times);
    //    if(counter % 300 ==0)
//        get_temperature_sensor_left_debug();
    delay(10);
    counter++;
}

char device_pi::DHT11_Read(char *temperature,char *humidity)
{
    unsigned char t=0,i,j;
    unsigned char buf[5]={0,0,0,0,0};
    char Data =0;
    pinMode(Data,OUTPUT); 	    //SET OUTPUT
    pullUpDnControl(Data,PUD_UP);
    digitalWrite(Data,0); 	    //Data=0
    delay(20);         	        //Pull down Least 18ms
    digitalWrite(Data,1); 	    //Data =1
    delayMicroseconds(30);     	//Pull up 20~40us
    pinMode(Data,INPUT);        //SET INPUT

    while (digitalRead(Data) && t <100)//DHT11 Pull down 80us
    {
        t++;
        delayMicroseconds(1);
    };
    if(t >= 100)return 1;
    t = 0;
    while (!digitalRead(Data) && t<100)//DHT11 Pull up 80us
    {
        t++;
        delayMicroseconds(1);
    };
    if(t >= 100)return 1;
    for(i=0;i < 5;i++)
    {
        buf[i] = 0;
        for(j=0;j<8;j++)
        {
            buf[i] <<= 1;
            t = 0;
            while(digitalRead(Data) && t < 100)
            {
                t++;
                delayMicroseconds(1);
            }
            if(t >= 100) return 1;
            t = 0;
            while(!digitalRead(Data) && t <100)
            {
                t++;
                delayMicroseconds(1);
            }
            if(t >= 100) return 1;
            delayMicroseconds(40);
            if(digitalRead(Data))
                buf[i] += 1;
        }
    }
    if(buf[0]+buf[1]+buf[2]+buf[3]!=buf[4])return 2;
    *humidity = buf[0];
    *temperature =buf[2];

    sensor_data_save.temp[0]=buf[2];

    return 0;
}

//复位DS18B20
void device_pi::DS18B20_Rst(void)
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
u8 device_pi::DS18B20_Check(void)
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
u8 device_pi::DS18B20_Init(void)
{
    wiringPiSetup() ;
    DS18B20_Rst();
    return DS18B20_Check();
}

//从DS18B20读取一个位
//返回值：1/0
u8 device_pi::DS18B20_Read_Bit(void)
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
u8 device_pi::DS18B20_Read_Byte(void)
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
void device_pi::DS18B20_Write_Byte(u8 dat)
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
void device_pi::DS18B20_Start(void)
{
    DS18B20_Rst();
    DS18B20_Check();
    DS18B20_Write_Byte(0xcc);	// skip rom
    DS18B20_Write_Byte(0x44);	// convert
}

//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250）
short device_pi::DS18B20_Get_Temp(void)
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




