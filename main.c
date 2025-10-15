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
int fd;
int value,angle;
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

int N=1000;
for(int k=0; k<N-1; k++)
{
    angle=2*M_PI*k/N;
    value=(sin(angle)+1.0)/2.0*4095;
    uint8_t ob = (value>>4)&0xFF;
    uint8_t sb = (value&0x0F)<<4;
    uint8_t buff[2] = { ob, sb };
    write(fd,buff,2);
    usleep(100);
    if(k==N)
    {
        k=0;
    }
}
}
