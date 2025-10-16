#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS "/dev/i2c-1"
#define MCP4725_ADDR 0x60
#define PI 3.14159
int main()
{
int16_t fd,value;
double v_d,angle;
fd=open(I2C_BUS,O_RDWR);
        if(fd<0)
        {
            perror("Can't open i2c bus");
            return 1;
        }
        if(ioctl(fd,I2C_SLAVE,MCP4725_ADDR)<0)
        {
            perror("Can't connect to mcp4725");
            close(fd);
            return 1;
        }

printf("Connected to mcp4725 (0x%02X)\r\n",MCP4725_ADDR);
while(1)
{
    int N=1000;
for(int k=0; k<N; k++)
{
    angle=2*PI*k/N;
    value = (int)round((sin(angle)+1.0)/2*4095);
    if(value<0) value =0;
    if(value > 4095) value = 4095;

    uint8_t ob = (value>>4)&0xFF;
    uint8_t sb = (value&0x0F)<<4;
    uint8_t buff[2] = { ob, sb };
    if(k==0 || k==N/4 || k==N/2 || k==3*N/4 || k==N-1)
    {
        printf("%d - value\r\n ",value);
    }

    write(fd,buff,2);
    usleep(500);

}
}

}
