/*
 * ov7670.h
 *
 *  Created on: 2017/08/25
 *      Author: take-iwiw
 */

#ifndef OV7670_OV7670_H_
#define OV7670_OV7670_H_

typedef uint32_t RET;

#define RET_OK           0x00000000
#define RET_NO_DATA      0x00000001
#define RET_DO_NOTHING   0x00000002
#define RET_ERR          0x80000001
#define RET_ERR_OF       0x80000002
#define RET_ERR_TIMEOUT  0x80000004
#define RET_ERR_STATUS   0x80000008
#define RET_ERR_PARAM    0x80000010
#define RET_ERR_FILE     0x80000020
#define RET_ERR_MEMORY   0x80000040


#define OV7670_CAP_CONTINUOUS   0
#define OV7670_CAP_SINGLE_FRAME 1

#define OV7670_QVGA_WIDTH  320u
#define OV7670_QVGA_HEIGHT 240u

RET ov7670_init(DCMI_HandleTypeDef *p_hdcmi, DMA_HandleTypeDef *p_hdma_dcmi, I2C_HandleTypeDef *p_hi2c);
RET ov7670_config(uint32_t mode);
RET ov7670_startCap(uint32_t capMode, uint32_t destAddress);
RET ov7670_stopCap();
void ov7670_registerCallback(void (*cbHsync)(uint32_t h), void (*cbVsync)(uint32_t v));

#endif /* OV7670_OV7670_H_ */
