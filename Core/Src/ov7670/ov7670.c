/*
 * ov7670.c
 *
 *  Created on: 2017/08/25
 *      Author: take-iwiw
 */
#include <stdio.h>
#include "main.h"
#include "stm32f7xx_hal.h"

#include "ov7670.h"
#include "ov7670Config.h"
#include "ov7670Reg.h"



uint32_t h_events = 0;
uint32_t v_events = 0;
uint32_t f_events = 0;
uint32_t frame_received=0;
/*** Internal Const Values, Macros ***/



/*** Internal Static Variables ***/
static DCMI_HandleTypeDef *sp_hdcmi;
static DMA_HandleTypeDef  *sp_hdma_dcmi;
static I2C_HandleTypeDef  *sp_hi2c;
static uint32_t    s_destAddressForContiuousMode;


/*** Internal Function Declarations ***/
static RET ov7670_write(uint8_t regAddr, uint8_t data);
static RET ov7670_read(uint8_t regAddr, uint8_t *data);

/*** External Function Defines ***/
RET ov7670_init(DCMI_HandleTypeDef *p_hdcmi, DMA_HandleTypeDef *p_hdma_dcmi, I2C_HandleTypeDef *p_hi2c)
{
  sp_hdcmi     = p_hdcmi;
  sp_hdma_dcmi = p_hdma_dcmi;
  sp_hi2c      = p_hi2c;
  s_destAddressForContiuousMode = 0;

  HAL_GPIO_WritePin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(CAMERA_RESET_GPIO_Port, CAMERA_RESET_Pin, GPIO_PIN_SET);
  HAL_Delay(100);

  ov7670_write(0x12, 0x80);  // RESET
  HAL_Delay(30);

  uint8_t buffer[4];
  ov7670_read(0x0b, buffer);
  ov7670_read(0x01, &buffer[1]);


  return RET_OK;
}

RET ov7670_config(uint32_t mode)
{
  uint8_t ret_value;
  ov7670_stopCap();
  ov7670_write(0x12, 0x80);  // RESET
  HAL_Delay(30);
  for(int i = 0; OV7670_reg[i][0] != REG_BATT; i++) {
    ov7670_write(OV7670_reg[i][0], OV7670_reg[i][1]);
    HAL_Delay(1);
  }
  for(int i = 0; OV7670_reg_read[i][0] != REG_BATT; i++) {
	ret_value = ov7670_read(OV7670_reg_read[i][0], &OV7670_reg_read[i][1]);
    if (ret_value != HAL_OK){
    	OV7670_reg_read[i][1]=0xFF;
    }
    HAL_Delay(1);
  }
  return RET_OK;
}

RET ov7670_startCap(uint32_t capMode, uint32_t destAddress)
{
  ov7670_stopCap();
  if (capMode == OV7670_CAP_CONTINUOUS) {
    /* note: continuous mode automatically invokes DCMI, but DMA needs to be invoked manually */
    s_destAddressForContiuousMode = destAddress;
    HAL_DCMI_Start_DMA(sp_hdcmi, DCMI_MODE_CONTINUOUS, destAddress, OV7670_WIDTH * OV7670_HEIGHT / 2);
  } else if (capMode == OV7670_CAP_SINGLE_FRAME) {
    s_destAddressForContiuousMode = 0;
    HAL_DCMI_Start_DMA(sp_hdcmi, DCMI_MODE_SNAPSHOT, destAddress, OV7670_WIDTH * OV7670_HEIGHT / 2);
  }

  return RET_OK;
}

RET ov7670_stopCap()
{
  HAL_DCMI_Stop(sp_hdcmi);
  return RET_OK;
}



void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	f_events++;
	frame_received = 1;
    if (f_events == 1){
		//HAL_DCMI_Stop(sp_hdcmi);
	}

  if(s_destAddressForContiuousMode != 0) {
    //HAL_DMA_Start_IT(hdcmi->DMA_Handle, (uint32_t)&hdcmi->Instance->DR, s_destAddressForContiuousMode, OV7670_WIDTH * OV7670_HEIGHT /2);
  }
}

void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	v_events++;

}

void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	h_events++;
}

/*** Internal Function Defines ***/
static RET ov7670_write(uint8_t regAddr, uint8_t data)
{
  HAL_StatusTypeDef ret;
  do {
    ret = HAL_I2C_Mem_Write(sp_hi2c, SLAVE_ADDR, regAddr, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
  } while (ret != HAL_OK && 0);
  return ret;
}

static RET ov7670_read(uint8_t regAddr, uint8_t *data)
{
  HAL_StatusTypeDef ret;
  do {
    // HAL_I2C_Mem_Read doesn't work (because of SCCB protocol(doesn't have ack))? */
//    ret = HAL_I2C_Mem_Read(sp_hi2c, SLAVE_ADDR, regAddr, I2C_MEMADD_SIZE_8BIT, data, 1, 1000);
    ret = HAL_I2C_Master_Transmit(sp_hi2c, SLAVE_ADDR, &regAddr, 1, 100);
    ret |= HAL_I2C_Master_Receive(sp_hi2c, SLAVE_ADDR, data, 1, 100);
  } while (ret != HAL_OK && 0);
  return ret;
}


