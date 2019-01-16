#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include "si1132.h"

int si1132_begin(const char *device)
{
	int status = 0;
	si1132Fd = -1;

	si1132Fd = open(device, O_RDWR);
	if (si1132Fd < 0) {
		printf("ERROR: si1132 open failed\n");
		return -1;
	}

	status = ioctl(si1132Fd, I2C_SLAVE, Si1132_ADDR);
	if (status < 0) {
		printf("ERROR: si1132 ioctl error\n");
		close(si1132Fd);
		return -1;
	}

	if (Si1132_I2C_read8(Si1132_REG_PARTID) != 0x32) {
		printf("ERROR: si1132 read failed the PART ID\n");
		return -1;
	}

	initialize();

	return si1132Fd;
}

void si1132_end() {
	if (si1132Fd)
		close(si1132Fd);
}

void initialize(void)
{
	reset();

	Si1132_I2C_write8(Si1132_REG_UCOEF0, 0x7B);
	Si1132_I2C_write8(Si1132_REG_UCOEF1, 0x6B);
	Si1132_I2C_write8(Si1132_REG_UCOEF2, 0x01);
	Si1132_I2C_write8(Si1132_REG_UCOEF3, 0x00);

	Si1132_I2C_writeParam(Si1132_PARAM_CHLIST, Si1132_PARAM_CHLIST_ENUV |
		Si1132_PARAM_CHLIST_ENALSIR | Si1132_PARAM_CHLIST_ENALSVIS);
	Si1132_I2C_write8(Si1132_REG_INTCFG, Si1132_REG_INTCFG_INTOE);
	Si1132_I2C_write8(Si1132_REG_IRQEN, Si1132_REG_IRQEN_ALSEVERYSAMPLE);

	Si1132_I2C_writeParam(Si1132_PARAM_ALSIRADCMUX, Si1132_PARAM_ADCMUX_SMALLIR);
	usleep(10000);
	// fastest clocks, clock div 1
	Si1132_I2C_writeParam(Si1132_PARAM_ALSIRADCGAIN, 0);
	usleep(10000);
	// take 511 clocks to measure
	Si1132_I2C_writeParam(Si1132_PARAM_ALSIRADCCOUNTER, Si1132_PARAM_ADCCOUNTER_511CLK);
	// in high range mode
	Si1132_I2C_writeParam(Si1132_PARAM_ALSIRADCMISC, Si1132_PARAM_ALSIRADCMISC_RANGE);
	usleep(10000);
	// fastest clocks
	Si1132_I2C_writeParam(Si1132_PARAM_ALSVISADCGAIN, 0);
	usleep(10000);
	// take 511 clocks to measure
	Si1132_I2C_writeParam(Si1132_PARAM_ALSVISADCCOUNTER, Si1132_PARAM_ADCCOUNTER_511CLK);
	//in high range mode (not normal signal)
	Si1132_I2C_writeParam(Si1132_PARAM_ALSVISADCMISC, Si1132_PARAM_ALSVISADCMISC_VISRANGE);
	usleep(10000);

	Si1132_I2C_write8(Si1132_REG_MEASRATE0, 0xFF);
	Si1132_I2C_write8(Si1132_REG_COMMAND, Si1132_ALS_AUTO);
}

void reset()
{
	Si1132_I2C_write8(Si1132_REG_MEASRATE0, 0);
	Si1132_I2C_write8(Si1132_REG_MEASRATE1, 0);
	Si1132_I2C_write8(Si1132_REG_IRQEN, 0);
	Si1132_I2C_write8(Si1132_REG_IRQMODE1, 0);
	Si1132_I2C_write8(Si1132_REG_IRQMODE2, 0);
	Si1132_I2C_write8(Si1132_REG_INTCFG, 0);
	Si1132_I2C_write8(Si1132_REG_IRQSTAT, 0xFF);

	Si1132_I2C_write8(Si1132_REG_COMMAND, Si1132_RESET);
	usleep(10000);
	Si1132_I2C_write8(Si1132_REG_HWKEY, 0x17);

	usleep(10000);
}

void Si1132_readVisible(float *result)
{
	usleep(10000);
	*result = ((Si1132_I2C_read16(0x22) - 256) / 0.282) * 14.5;
}

void Si1132_readIR(float *result)
{
	usleep(10000);
	*result = ((Si1132_I2C_read16(0x24) - 250) / 2.44) * 14.5;
}

void Si1132_readUV(int *result)
{
	usleep(10000);
	*result = (int)Si1132_I2C_read16(0x2c);
}

unsigned char Si1132_I2C_read8(unsigned char reg)
{
	unsigned char ret;
	write(si1132Fd, &reg, 1);
	read(si1132Fd, &ret, 1);
	return ret;
}

unsigned short Si1132_I2C_read16(unsigned char reg)
{
	unsigned char rbuf[2];
	write(si1132Fd, &reg, 1);
	read(si1132Fd, rbuf, 2);
	return (unsigned short)(rbuf[0] | rbuf[1] << 8);
}

void Si1132_I2C_write8(unsigned char reg, unsigned char val)
{
	unsigned char wbuf[2];
	wbuf[0] = reg;
	wbuf[1] = val;
	write(si1132Fd, wbuf, 2);
}

void Si1132_I2C_writeParam(unsigned char param, unsigned char val)
{
	Si1132_I2C_write8(Si1132_REG_PARAMWR, val);
	Si1132_I2C_write8(Si1132_REG_COMMAND, param | Si1132_PARAM_SET);
}
