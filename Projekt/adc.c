#include "adc.h"

void ADC1Init() {	
	// Config structs
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC1_InitStruct;
	
	// Enable the clock for ADC and the ADC GPIOs
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	// Configure these ADC pins in analog mode using GPIO_Init();		
	GPIO_StructInit(&GPIO_InitStruct); // Reset gpio init structure
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN; // Obvezno AIN !!!
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
  // Common ADC init sets the prescaler
	ADC_CommonStructInit(&ADC_CommonInitStruct);
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);

  /* ADC1 Configuration */
	ADC_StructInit(&ADC1_InitStruct);
	ADC1_InitStruct.ADC_Resolution = ADC_Resolution_10b;
	ADC_Init(ADC1, &ADC1_InitStruct);
	ADC_Cmd(ADC1, ENABLE);	

  /* Now do the setup */
  ADC_Init(ADC1, &ADC1_InitStruct);
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */
  //ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  //while(ADC_GetResetCalibrationStatus(ADC1));
  /* Start ADC1 calibaration */
  //ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  //while(ADC_GetCalibrationStatus(ADC1));
}

int ADC1Read(u8 channel) {
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_15Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);
	return ADC_GetConversionValue(ADC1);
}

u16 readADC1(u8 channel){
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_15Cycles);
  // Start the conversion
  ADC_Cmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  return ADC_GetConversionValue(ADC1);
}
