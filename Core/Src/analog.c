#include "main.h"
#include "cmsis_os.h"

#define adc_timeout 500

//uint16_t global_adc;
extern uint32_t EpochTime;

ADC_ChannelConfTypeDef ADC_CONF;
extern ADC_HandleTypeDef hadc1;

int16_t FlowArray[F_ARR_SIZE];
uint16_t flow_prediction_arr[FLOW_30AVG];
uint16_t flow_arr_index = 0;
uint32_t flow_accumulator = 0;;
uint16_t flow_counter = 0;
uint32_t flow_30accumulator = 0;;
uint16_t flow_30counter = 0;
uint16_t Last30flowAVG = 0;

float TotalVolume = 0;
uint16_t PredictedTime = 0;
uint16_t OldPredictedTime = 0;
extern TypeParameters DeviceParam;

extern uint8_t ActiveGas;


void measure_volt(TypeVolt* Volt){
		//ADC global variables
	static uint32_t ADCL_acc = 0;
	static uint32_t ADCR_acc = 0;
  static uint32_t ADCPSU_acc = 0;
	static uint32_t ADCBat_acc = 0;
	static uint32_t ADCLine_acc = 0;
  static uint32_t ADCConc_acc = 0;
	static uint32_t ADCFlow_acc = 0;
	static uint16_t ADC_counter = 0;
	static double ADC_avg;
	float PressLeft;
  float PressRight;
  float PSUVolt;
  float BatVolt;
	float ConcPress;
  float LinePress;
  int16_t FlowV;
	
		ADC_CONF.Channel = ADC_Left_Press;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCL_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_Right_Press;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCR_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_PSU;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCPSU_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_BAT;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCBat_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_Concentrator;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCConc_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_Line;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCLine_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_CONF.Channel = ADC_Flow;
		HAL_ADC_ConfigChannel(&hadc1, &ADC_CONF);
		HAL_ADC_Start (&hadc1);
		HAL_ADC_PollForConversion (&hadc1, adc_timeout);
		ADCFlow_acc += HAL_ADC_GetValue (&hadc1);
		
		ADC_counter++;
    if(ADC_counter == ADC_AVG_NUM){
      //Left Pressure calculation
      ADC_avg = (double)ADCL_acc;
      ADCL_acc = 0;
      PressLeft = ADC_avg * H_P_a + H_P_b;
      if(PressLeft < 0) PressLeft = 0;
			
      //Right pressure calculation
      ADC_avg = (double)ADCR_acc;
      ADCR_acc = 0;
      PressRight = ADC_avg * H_P_a + H_P_b;
      if(PressRight < 0) PressRight = 0;
			
      //PSU voltage calculation
      ADC_avg = (double)ADCPSU_acc;
      ADCPSU_acc = 0;
      PSUVolt = ADC_avg * Volt_a + Volt_b;
			if(PSUVolt < 0) PSUVolt = 0;
			
      //Battery voltage calculation
      ADC_avg = (double)ADCBat_acc;
      ADCBat_acc = 0;
      BatVolt = ADC_avg * Volt_a + Volt_b;   
			if(BatVolt < 0) BatVolt = 0;
			
			//Concentrator pressure calculation
      ADC_avg = (double)ADCConc_acc;
      ADCConc_acc = 0;
			ConcPress = ADC_avg * P_a + P_b;
			if(ConcPress < 0) ConcPress = 0;
			
			//Line pressure calculation
			ADC_avg = (double)ADCLine_acc;
      ADCLine_acc = 0;
			LinePress = ADC_avg * P_a + P_b;
			if(LinePress < 0) LinePress = 0;
			
			//Flow calculation
      ADC_avg = (double)ADCFlow_acc;
      ADCFlow_acc = 0;
			FlowV = (int16_t)(ADC_avg * V_a + V_b);
			if(FlowV < 0) FlowV = 0;			
			//Flow averaging for plot
			flow_accumulator += (uint32_t)FlowV;
			flow_counter++;
			if(flow_counter == FLOW_AVG){				
				FlowArray[flow_arr_index] = flow_accumulator / FLOW_AVG;
				flow_accumulator = 0;
				flow_arr_index++;
				if(flow_arr_index == F_ARR_SIZE) flow_arr_index = 0;
				flow_counter = 0;
			}
			//Flow averaging for prediction
			//flow_30accumulator += (uint32_t)FlowV;
			flow_prediction_arr[flow_30counter] = (uint32_t)FlowV;
			flow_30counter++;
			flow_30accumulator = 0;			
			if(flow_30counter == FLOW_30AVG) flow_30counter = 0;
			for(uint16_t i = 0; i < FLOW_30AVG; i++){
				flow_30accumulator += flow_prediction_arr[i];
			}			
			Last30flowAVG = flow_30accumulator / FLOW_30AVG;
			
			ADC_counter = 0;

			Volt->PressLeft = PressLeft;
			Volt->PressRight = PressRight;
			Volt->BatVolt = BatVolt;
			Volt->PSUVolt = PSUVolt;
			Volt->PressConc = ConcPress;
			Volt->PressLine = LinePress;
			Volt->Flow = FlowV;
			Volt->new_data = 1;
			
			//Prediction of gas amount
			TotalVolume = (Volt->PressLeft * (float)DeviceParam.CylinderNumberLeft + 
				Volt->PressRight * (float) DeviceParam.CylinderNumberRight)  * 
					CylinderVolume / (float)PressMAX;
			if(Last30flowAVG > 0) 
				PredictedTime = (uint16_t)(TotalVolume / Last30flowAVG);
			else
				PredictedTime = 0xffff;
			if(FAKE_SENSORS) fake_volt(Volt);
    }
		
}


//faking phisycal values
void fake_volt(TypeVolt* Volt){	
	static uint16_t PressLeft = 200;
	static uint16_t PressRight = 200;
	    vTaskDelay(88);
	    //gas consumption
			if(ActiveGas == LEFT) 	PressLeft -= 0.45;				
			if(ActiveGas == RIGHT)  PressRight -= 0.45;
				
			Volt->PressLeft = PressLeft;
			Volt->PressRight = PressRight;
	
			//cylinders change
			if(Volt->PressRight < ALRM_THRESHOLD) {
				PressRight = 200;
				ActiveGas = LEFT;
			}
	    if(Volt->PressLeft < ALRM_THRESHOLD){
				PressLeft = 200;
				ActiveGas = RIGHT;
			}
			
			Volt->PressLeft = PressLeft;
			Volt->PressRight = PressRight;
			
	//concentrator
			//if((EpochTime % 60)  <  30) Volt->PressConc = 0.01; else Volt->PressConc = 5.26;
			Volt->PressConc = 0.1;
	//line
	    //Volt->PressLine = 4.00 + ((float)(EpochTime % 200))/ 200;
	    Volt->PressLine = 4.5;
			
			Volt->new_data = 1;
}
