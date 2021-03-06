#include "main.h"
#include "cmsis_os.h"
#include <string.h>

uint8_t ActiveGas = LEFT;
uint8_t EmergGasWas = LEFT;
uint8_t OldActiveGas = LEFT;
uint8_t ActiveCylinder = LEFT;
extern uint8_t OneSeconTick; //needed for transmitting ticks from timer every second
extern uint32_t EpochTime;
//uint8_t flagLEDodd = 0; //flip-flop var. for led on-off

extern TypeParameters DeviceParam;
extern uint8_t SwitchGasRequest;
extern uint8_t ManIsHere;
extern uint8_t ActiveGasRequested;

extern TypeVolt PhValues_output;

extern TypeTCP_excange tcp_exchange;


uint8_t ConcNORMCounter = 0; //Counter for delay when conc. was off but now is on
uint8_t TickForward = 0;
uint8_t BlinkFlag = 0;
uint8_t UPS_SoundActive = 0;

uint8_t SilentTimer = 0;
uint8_t ConcSIGCounter = 0;  //beep duration when concentrator is off
uint8_t PowerAlarmActivated = 0;
uint8_t  CounterValveSuspend = 0;
uint16_t CounterEmergWork = 0;

//Buttons global variables
uint8_t flagOldSwButt = 0;
uint8_t flagOldAlButt = 0;
//extern uint8_t ButtSwCounter;
//extern uint8_t ButtAlCounter;
extern uint8_t buzz_on;
uint8_t ALRM_BUTT_COUNTER = 0;

extern QueueHandle_t myQueueLORAHandle;
uint8_t logic_q_buff[MESS_LEN];

uint8_t LEDvalueL;
uint8_t LEDvalueR;

TypeAlarm Alarm = {0, 0, 1, 0, 0, 0, 0, 0};
TypeAlarm AlarmBuffer;
TypeDisplay DisplaySet = {0, 0};
uint32_t ALRM_BYTE;

extern uint8_t LORA_busy;
extern unsigned char LoraLinkOK;
extern int16_t LR_RSSI;

void make_action(const TypeVolt* Volt){
//	static uint8_t ActiveGas = LEFT;
	
	if(DeviceParam.Role == REPEATER){
		if(DeviceParam.CommDevice == LORA){
			//LoRa received data applying is here
			if(xQueueReceive(myQueueLORAHandle, &logic_q_buff, 0) == pdTRUE){
				if(UnPackLoRa(&Alarm, logic_q_buff, &LEDvalueL, &LEDvalueR, &ActiveGas) == 0){
					LEDvalueL = 0;
					LEDvalueR = 0;
					Alarm.BatteryOut = 0;
					Alarm.ConcentratorMax = 0;
					Alarm.ConcentratorNOT_OK = 0;
					Alarm.CylindersEmpty = 0;
					Alarm.LineMax = 0;
					Alarm.LineMin = 0;
					Alarm.PowerOff = 0;
					ActiveGas = CONCENTRATOR;
				}
			}
		}
		if(DeviceParam.CommDevice == ETHERNET){
			
		}
	}else{ //if it is CONTROLLER
      LEDvalueL = (uint8_t)(1 + Volt->PressLeft /  Pquant);
      if(LEDvalueL < 1) LEDvalueL = 1;
      if(LEDvalueL > 20) LEDvalueL = 20;
      LEDvalueR = (uint8_t)(1 + Volt->PressRight /  Pquant);
      if(LEDvalueR < 1) LEDvalueR = 1;
      if(LEDvalueR > 20) LEDvalueR = 20;
	}
		/* ---------------------------------------------------------------------- */
    /*           GAS SOURCE SENSITIVE LOGIC                                   */
    /* ---------------------------------------------------------------------- */
	if(DeviceParam.Role == CONTROLER){
		//User control section
		
		
		if(SwitchGasRequest){
			/*if(ActiveGas != CONCENTRATOR){
				if(((Volt->PressRight >= DeviceParam.HPressSwitch) && (Volt->PressLeft >= DeviceParam.HPressSwitch)) || 
					((Volt->PressLeft < DeviceParam.HPressSwitch) && (Volt->PressRight < DeviceParam.HPressSwitch)))  
						ActiveGas = ActiveGasRequested;
				}*/			
				if(ActiveGas != CONCENTRATOR){
					if((Volt->PressRight >= DeviceParam.HPressSwitch) == (Volt->PressLeft >= DeviceParam.HPressSwitch)) {
						CounterEmergWork = 0;
						if(Alarm.LineMin == 0) ActiveGas = ActiveGasRequested;
					}
				}
				SwitchGasRequest = 0;			
		}
		
		//if((EpochTime % 20) < 10)  ActiveGas = LEFT; else ActiveGas = RIGHT;
		
	switch(ActiveGas){
      case(LEFT):
        /*      actuation    */
        HAL_GPIO_WritePin(PORT_LEFT_VLV, LEFT_VLV, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(PORT_RIGHT_VLV, RIGHT_VLV, GPIO_PIN_SET);
        /*       logic          */
        //pressure criteria
        if((Volt->PressLeft <= DeviceParam.HPressSwitch) && 
					(DeviceParam.Baranki || Alarm.LineMin) &&
					(Volt->PressRight >= DeviceParam.HPressSwitch)){
						ActiveGas = RIGHT;
						ActiveCylinder = RIGHT;
        }
				if(Alarm.ConcentratorNOT_OK) ConcNORMCounter = DeviceParam.ConcDelay; //keeps it loaded. Another routing decrements it every second
				if(ConcNORMCounter == 0) ActiveGas = CONCENTRATOR;				
        break;
       case(RIGHT):
        /*      actuation    */
        HAL_GPIO_WritePin(PORT_LEFT_VLV, LEFT_VLV, GPIO_PIN_SET);
        HAL_GPIO_WritePin(PORT_RIGHT_VLV, RIGHT_VLV, GPIO_PIN_RESET);
        /*       logic          */
        //pressure criteria
        if((Volt->PressRight <= DeviceParam.HPressSwitch) &&
					(DeviceParam.Baranki || Alarm.LineMin) &&
					(Volt->PressLeft >= DeviceParam.HPressSwitch)){
						ActiveGas = LEFT;
						ActiveCylinder = LEFT;
        }
				if(Alarm.ConcentratorNOT_OK) ConcNORMCounter = DeviceParam.ConcDelay; //keeps it loaded. Another routing decrements it every second
				if(ConcNORMCounter == 0) ActiveGas = CONCENTRATOR;				
        break;
       case(CONCENTRATOR):
        /*      actuation    */
        HAL_GPIO_WritePin(PORT_LEFT_VLV, LEFT_VLV, GPIO_PIN_SET);
        HAL_GPIO_WritePin(PORT_RIGHT_VLV, RIGHT_VLV, GPIO_PIN_SET);
        /*       logic          */
        //pressure criteria
        if(Alarm.ConcentratorNOT_OK){
          ConcSIGCounter = CONC_SIG_DUR;
          ActiveGas = ActiveCylinder;
        }
        //swap button
        /*if((ButtSwCounter == BUTT_TRIM)&&(flagOldSwButt == 0)){
          flagOldSwButt = 1;
        }*/
        break;
				case(BOTH_VALVES):
				HAL_GPIO_WritePin(GPIOC, LEFT_VLV, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOC, RIGHT_VLV, GPIO_PIN_RESET);
				//swap button
        /*if((ButtSwCounter == BUTT_TRIM)&&(flagOldSwButt == 0)){
					CounterEmergWork = 0; //try to return to normal mode
          flagOldSwButt = 1;
        }*/
				if(CounterEmergWork == 0){//time to try to work normally
					if(Alarm.LineMin == 0) ActiveGas = EmergGasWas;
					CounterValveSuspend = VALVE_SUSPEND_T;
					Alarm.EmergState = 0;
				}
				break;
    default: NVIC_SystemReset(); break;
    }
		}
	
		if(DeviceParam.Role == REPEATER){
			if((OldActiveGas == CONCENTRATOR) && (ActiveGas != CONCENTRATOR)) ConcSIGCounter = CONC_SIG_DUR;			
			
			if(LoraLinkOK){ //there is succesfull radiolink
//			switch(ActiveGas){
//      case(LEFT):
//        if((ConcOldOK == 0)&&(!Alarm.ConcentratorNOT_OK)){
//          ConcNORMCounter = DeviceParam.ConcDelay;
//        }
//        break;
//       case(RIGHT):
//        if((ConcOldOK == 0)&&(!Alarm.ConcentratorNOT_OK)){
//          ConcNORMCounter = DeviceParam.ConcDelay;
//        }
//        break;
//       case(CONCENTRATOR):
//        if(Alarm.ConcentratorNOT_OK){
//          ConcSIGCounter = CONC_SIG_DUR;
//        }
//        break;
//			default: break;
//			}
		}else{//no successfull radio-link
		}
			
		}
		
		OldActiveGas = ActiveGas;
		/* ---------------------------------------------------------------------- */
    /*           EVERY ONE SECOND ROUTINE                                     */
    /* ---------------------------------------------------------------------- */
    if(OneSeconTick){
			EpochTime++;
			/*if(ButtAlCounter == BUTT_TRIM){
				//If Alarm Button is holded
				ALRM_BYTE = make_byte(&Alarm);
				inject_rssi(&ALRM_BYTE, LR_RSSI);
			}else{
					if(flagLEDodd){
						flagLEDodd = 0;
					}else{
						flagLEDodd = 1;
					}   											
			}		*/
		OneSeconTick = 0;
    TickForward = 1;
			
																								//*******SENDING DATA*****************************
		if(DeviceParam.Role == CONTROLER) {
			//filling in outgoung data
			if((DeviceParam.CommDevice == LORA) && (LORA_busy == 0)){
				PackLoRa(&Alarm, logic_q_buff, &LEDvalueL, &LEDvalueR, &ActiveGas);
				if(xQueueSend(myQueueLORAHandle, &logic_q_buff, 0) != pdTRUE){
					while(1){}
				}
			}			
		}
		if((DeviceParam.CommDevice == ETHERNET) && (tcp_exchange.needs_send == 0)){
			tcp_exchange.modification = 1;      //kind of "critical section"
			memcpy(&tcp_exchange.rx_tx_buff , &PhValues_output, sizeof(PhValues_output));
			tcp_exchange.modification = 0;      //end of "critical section"
			tcp_exchange.needs_send = 1;    //data must be sent
		}
	}
		/* ---------------------------------------------------------------------- */
	  /*           ALARM GENERATION                            */
    /* ---------------------------------------------------------------------- */
		if(DeviceParam.Role == CONTROLER){
    //one cylinder < 10 bar, second cylinder < 40 bar
    if(((Volt->PressLeft <= DeviceParam.HPressSwitch)&&(Volt->PressRight <= DeviceParam.HPressAlarm))
       ||((Volt->PressRight <= DeviceParam.HPressSwitch)&&(Volt->PressLeft <= DeviceParam.HPressAlarm))){
         Alarm.CylindersEmpty = 1;
       }else{
         Alarm.CylindersEmpty = 0;
       }
   //Line is high
    if(Volt->PressLine > DeviceParam.PressLineMax){
			Alarm.LineMax = 1;
    }else{
			Alarm.LineMax = 0;
    }
    //Line is low
    if(Volt->PressLine < DeviceParam.PressLineMin){
			if((CounterValveSuspend == 0) && (Alarm.LineMin == 0)) CounterValveSuspend = VALVE_SUSPEND_T;  //Situation just happened
			if((CounterValveSuspend == 0) && (Alarm.LineMin == 1) && (ActiveGas != BOTH_VALVES)){ //Time to switch to the emergency state
				EmergGasWas = ActiveGas; //save the context
				ActiveGas = BOTH_VALVES;				
				CounterEmergWork = EMERGENCY_MODE_T;
				Alarm.EmergState = 1;
			}
      Alarm.LineMin = 1;
    }else{
      Alarm.LineMin = 0;
    }
    //Concentrator pressure high
    if(Volt->PressConc > DeviceParam.PressConcMax){
      Alarm.ConcentratorMax = 1;
    }else{
      Alarm.ConcentratorMax = 0;
    }
    //Concentrator pressure low
    if(Volt->PressConc >= DeviceParam.PressConcMin){
      Alarm.ConcentratorNOT_OK = 0;
    }else{
      Alarm.ConcentratorNOT_OK = 1;
    }

    //PSU high or low alarm
    if((Volt->PSUVolt > PSU_HIGH) || (Volt->PSUVolt < PSU_LOW)){
      Alarm.PowerOff = 1;
      if(PowerAlarmActivated == 0){
        UPS_SoundActive = 1;
        PowerAlarmActivated = 1;
      }
    }else{
      UPS_SoundActive = 1;
      Alarm.PowerOff = 0;
      PowerAlarmActivated = 0;
    }
    //Battery low alarm
    if((Volt->BatVolt < BatteryLow) && (Volt->PSUVolt < PSU_LOW)){
      Alarm.BatteryOut = 1;
    }else{
      if(Volt->BatVolt > BatteryOK) Alarm.BatteryOut = 0;
    }
		if(CompareAlarms(&Alarm, &AlarmBuffer) == 0){
				LOG_Log();
		}
		CopyAlarms(&Alarm, &AlarmBuffer);
	}
		
		/* ---------------------------------------------------------------------- */
	  /*           DISPLAY DATA SENDING                                         */
    /* ---------------------------------------------------------------------- */	
	  if(Volt->PressRight < DeviceParam.HPressAlarm) DisplaySet.RightPressAlarm = 1; else DisplaySet.RightPressAlarm = 0;
	  if(Volt->PressLeft < DeviceParam.HPressAlarm) DisplaySet.LeftPressAlarm = 1; else DisplaySet.LeftPressAlarm = 0;
		if((Volt->PressConc > DeviceParam.PressConcMax) || (Volt->PressConc < DeviceParam.PressConcMin)) 
			DisplaySet.ConcPressAlarm = 1; else DisplaySet.ConcPressAlarm = 0;
		if((Volt->PressLine > DeviceParam.PressLineMax) || (Volt->PressLine < DeviceParam.PressLineMin)) 
			DisplaySet.LinePressAlarm = 1; else DisplaySet.LinePressAlarm = 0;
	
    /* ----------------------------------------------------------------------- */
    /*           BUTTONS PROCESSING                        */
    /* ---------------------------------------------------------------------- */
/*    if((ButtAlCounter == BUTT_TRIM)&&(flagOldAlButt == 0)){
      if((Alarm.ConcentratorMax)||(Alarm.CylindersEmpty)||(Alarm.LineMax)||(Alarm.LineMin))SilentTimer = ALRM_PAUSE;
      if(Alarm.PowerOff)UPS_SoundActive = 0;
      flagOldAlButt = 1;
    }
    if(ButtAlCounter == 0)flagOldAlButt = 0;
    if(ButtSwCounter == 0)flagOldSwButt = 0;*/

    /* ------------------------------------------------------------------------------------------ */
    /*           ALARM SOUNDS AND LEDs PROCESSING                */
    /* ------------------------------------------------------------------------------------------ */
		//if(DeviceParam.Role == CONTROLER){
    if(Alarm.BatteryOut){
     //Highest priority alarm. Out of battery. Sound can not be off.
			Buzzer(1);      
    }else{
      if((Alarm.ConcentratorMax)||(Alarm.CylindersEmpty)||(Alarm.LineMax)||(Alarm.LineMin)){
        //High priority alarms.
        if(SilentTimer)Buzzer(0); else Buzzer(1);
      }else{
        if(Alarm.PowerOff){
          //Lower priority alarm. Power off.
          if(ConcSIGCounter){
           Buzzer(1);
          }else{
            if(BlinkFlag){
              if(UPS_SoundActive)Buzzer(1); else Buzzer(0);
            }else{
              Buzzer(0);
            }
          }
        }else{
          if(ConcSIGCounter){
            Buzzer(1);
          }else{
            Buzzer(0);
          }
          SilentTimer = 0;
        }
      }
    }
		//}else Buzzer(1);
		/* ---------------------------------------------------------------------- */
	  /*           SLOW TIMERS                                       */
    /* ---------------------------------------------------------------------- */		
		if(TickForward){
      if(BlinkFlag) BlinkFlag = 0; else BlinkFlag = 1;
      if(SilentTimer) SilentTimer--;
      if(ConcNORMCounter) ConcNORMCounter--;
      if(ConcSIGCounter) ConcSIGCounter--;
			if(CounterValveSuspend) CounterValveSuspend--;
			if(CounterEmergWork) CounterEmergWork--;
      TickForward = 0;
    }
		osDelay(3);
//		IWDG->KR = KR_KEY_RELOAD;
}

/**
  * @brief  
  * @param  alrm copied to alrm_copy
  * @retval
  */
void CopyAlarms(TypeAlarm* alrm, TypeAlarm* alrm_copy){
	*alrm_copy = *alrm;
}

/**
  * @brief  
  * @param  alrm copied to alrm_copy
  * @retval
  */
uint8_t CompareAlarms(TypeAlarm* alrm1, TypeAlarm* alrm2){
	uint8_t var = 1;
	if(alrm1->BatteryOut != alrm2->BatteryOut) var = 0;
	if(alrm1->ConcentratorMax != alrm2->ConcentratorMax) var = 0;
	if(alrm1->ConcentratorNOT_OK != alrm2->ConcentratorNOT_OK) var = 0;
	if(alrm1->CylindersEmpty != alrm2->CylindersEmpty) var = 0;
	if(alrm1->EmergState != alrm2->EmergState) var = 0;
	if(alrm1->LineMax != alrm2->LineMax) var = 0;
	if(alrm1->LineMin != alrm2->LineMin) var = 0;
	if(alrm1->PowerOff != alrm2->PowerOff) var = 0;
	return(var);
}
