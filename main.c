#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define I2C_BUS "/dev/i2c-1"
#define MCP4725_ADDR 0x60
int main()
{
int fd;
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
}
