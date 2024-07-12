#ifndef __RPI_LIB__
#define __RPI_LIB__
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <string>
#include <chrono>
#include "mraa/common.hpp"
#include "mraa/uart.hpp"
#include "mraa/gpio.hpp"

enum Uart_Port{
    UART0=0,
    UART1,
    UART2,
    UART3,
    UART4,
    UART5,
};
enum RS485_Gpio_Port{
    RS485_RW_Switch_Gpio3 = 36,
    RS485_RW_Switch_Gpio4 = 38,
    RS485_RW_Switch_Gpio5 = 40,
    Fault_Gpio = -1,
};
namespace devices{
    inline  std::string dev_path[6]={
        "/dev/ttyAMA0",
        "/dev/ttyS0",
        "/dev/ttyAMA1",
        "/dev/ttyAMA2",
        "/dev/ttyAMA3",
        "/dev/ttyAMA4",
    };
    
};
class uart_module{
    public:
        uart_module(int baudrate = 115200,int uart_delay=10 ,Uart_Port port=UART0,int databyte=8,mraa::UartParity parity=mraa::UART_PARITY_NONE,int stopbits = 1,bool xonxoff=false,bool rtscts=false);
        ~uart_module();
        void setBaudRate(int baudrate){ _baudrate = baudrate;}
        void setUartDelay(int uart_delay){ _uart_delay=uart_delay;}
        void setUartPort(Uart_Port port){ _port=port;}
        void setDataByte(int databyte){ _databyte=databyte;}
        void setParity(mraa::UartParity parity){ _parity=parity;}
        void setStopBits(int stopbits){ _stopbyte=stopbits;}
        void setXonxoff(bool xonxoff){ _xonxoff=xonxoff;}
        void setRtscts(bool rtscts){ _rtscts=rtscts;}
        int getBaudRate(){return _baudrate;}
        int getUartDelay(){return _uart_delay;}
        Uart_Port getUartPort(){return _port;}
        int getDataByte(){ return _databyte;}
        mraa::UartParity getParity(){ return _parity;}
        int getStopBits(){ return _stopbyte;}
        bool getXonxoff(){ return _xonxoff;}
        bool getRtscts(){ return _rtscts;}
        void open_uart();
        void close_uart();
        void send_packet(std::string packet);
        void recv_packet(char *packet,int max_size);
    private:
        int _baudrate;
        int _uart_delay;
        Uart_Port _port;
        int _databyte;
        int _stopbyte;
        bool _xonxoff;
        bool _rtscts;
        mraa::UartParity _parity;
        mraa::Uart *uart=NULL, *temp=NULL;
};

class rs485_module:public uart_module{
    public:
        rs485_module(int baudrate = 115200,int uart_delay=1200 ,Uart_Port port=UART0,int databyte=8,mraa::UartParity parity=mraa::UART_PARITY_NONE,int stopbits = 1,bool xonxoff=false,bool rtscts=false);
        ~rs485_module();
        void open_rs485();
        void close_rs485();
        void set_RsSwPort(RS485_Gpio_Port port){ _Rs_SwPort=port;}
        RS485_Gpio_Port get_RsSwPort(){return _Rs_SwPort;}
        void send_485packet(std::string packet);
        void recv_485packet(char *packet,int max_size);
    private:
        RS485_Gpio_Port _Rs_SwPort;
        mraa::Gpio *gpio;
};
#endif