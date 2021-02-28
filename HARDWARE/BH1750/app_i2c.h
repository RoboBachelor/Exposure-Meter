#ifndef _APP_I2C_H
#define _APP_I2C_H

#include "defines.h"

void I2C2_config (void);
void I2C2_write(unsigned char HW_address, unsigned char sub, unsigned char data);
char I2C2_read (unsigned char HW_address, unsigned char sub);
void I2C2_read_buf (unsigned char HW_address, unsigned char sub, unsigned char * p_buf, unsigned char buf_size);


#endif
