#include "main.h"
#include "cmsis_os.h"

uint8_t ActiveGas = LEFT;
uint8_t OldActiveGas = LEFT;
uint8_t ConcOldOK = 0;
uint8_t ActiveCylinder = LEFT;
extern uint8_t OneSeconTick; //needed for transmitting ticks from timer every second
uint8_t flagLEDodd = 0; //flip-flop var. for led on-off

extern TypeParameters DeviceParam;
extern uint8_t SwitchGasRequest;
extern uint8_t ActiveGasRequested;

uint8_t SilentTimer = 0;
uint8_t ConcNORMCounter = 0; //Counter for delay when conc. was off but now is on
uint8_t TickForward = 0;
uint8_t BlinkFlag = 0;
uint8_t ConcSIGCounter = 0;  //beep duration when concentrator is off
uint8_t UPS_SoundActive = 0;
uint8_t PowerAlarmActivated = 0;

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

TypeAlarm Alarm = {0, 0, 1, 0, 0, 0, 0};
TypeDisplay DisplaySet = {0, 0};
uint32_t ALRM_BYTE;

extern uint8_t LORA_busy;
extern unsigned char LoraLinkOK;
extern int16_t LR_RSSI;

void make_action(const TypeVolt* Volt){
//	static uint8_t ActiveGas = LEFT;
	
	if(DeviceParam.LoRa == RECEIVER){
			if(xQueueReceive(myQueueLORAHandle, &logic_q_buff, 0) == pdTRUE){
				if(UnPackPacket(&Alarm, logic_q_buff, &LEDvalueL, &LEDvalueR, &ActiveGas) == 0){
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
	}else{
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
	if((DeviceParam.LoRa == SENDER)||(DeviceParam.LoRa == NOLORA)){
		//User control section
		if(SwitchGasRequest){
			if((Volt->PressRight >= DeviceParam.HPressSwitch) && 
				(Volt->PressLeft >= DeviceParam.HPressSwitch) &&
				(ActiveGas != CONCENTRATOR)
			) ActiveGas = ActiveGasRequested;
			SwitchGasRequest = 0;
		}
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
        if((ConcOldOK == 0)&&(!Alarm.ConcentratorNOT_OK)){
          ConcNORMCounter = DeviceParam.ConcDelay;
          ConcOldOK = 1;
        }
        if((ConcOldOK)&&(ConcNORMCounter == 0))ActiveGas = CONCENTRATOR;
        //swap button
        /*if((ButtSwCounter == BUTT_TRIM)&&(flagOldSwButt == 0)){
          if((Volt->PressRight > DeviceParam.HPressSwitch) || 
						((Volt->PressRight <= DeviceParam.HPressSwitch) && (Volt->PressRight <= DeviceParam.HPressSwitch))){
            ActiveGas = RIGHT;
            ActiveCylinder = RIGHT;
          }
          flagOldSwButt = 1;
        }*/
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
        if((ConcOldOK == 0)&&(!Alarm.ConcentratorNOT_OK)){
          ConcNORMCounter = DeviceParam.ConcDelay;
          ConcOldOK = 1;
        }
        if((ConcOldOK)&&(ConcNORMCounter == 0))ActiveGas = CONCENTRATOR;
        //swap button
        /*if((ButtSwCounter == BUTT_TRIM)&&(flagOldSwButt == 0)){
          if((Volt->PressLeft > DeviceParam.HPressSwitch) || 
						((Volt->PressRight <= DeviceParam.HPressSwitch) && (Volt->PressRight <= DeviceParam.HPressSwitch))){
            ActiveGas = LEFT;
            ActiveCylinder = LEFT;
          }
          flagOldSwButt = 1;
        }*/
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
          ConcOldOK = 0;
        }
        //swap button
        /*if((ButtSwCounter == BUTT_TRIM)&&(flagOldSwButt == 0)){
          flagOldSwButt = 1;
        }*/
        break;
    default: break;
    }
		}
	
		if(DeviceParam.LoRa == RECEIVER){			
			if((OldActiveGas == CONCENTRATOR) && (ActiveGas != CONCENTRATOR)) ConcSIGCounter = CONC_SIG_DUR;			
			
			if(LoraLinkOK){ //there is succesfull radiolink
			switch(ActiveGas){
      case(LEFT):
        if((ConcOldOK == 0)&&(!Alarm.ConcentratorNOT_OK)){
          ConcNORMCounter = DeviceParam.ConcDelay;
          ConcOldOK = 1;
        }
        break;
       case(RIGHT):
        if((ConcOldOK == 0)&&(!Alarm.ConcentratorNOT_OK)){
          ConcNORMCounter = DeviceParam.ConcDelay;
          ConcOldOK = 1;
        }
        break;
       case(CONCENTRATOR):
        if(Alarm.ConcentratorNOT_OK){
          ConcSIGCounter = CONC_SIG_DUR;
          ConcOldOK = 0;
        }
        break;
			default: break;
			}
		}else{//no successfull radio-link
		}
			
		}
		
		OldActiveGas = ActiveGas;
		/* ---------------------------------------------------------------------- */
    /*           EVERY ONE SECOND ROUTINE                                     */
    /* ---------------------------------------------------------------------- */
    if(OneSeconTick){
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
			
		if((DeviceParam.LoRa == SENDER) && (LORA_busy == 0)){
			PackPacket(&Alarm, logic_q_buff, &LEDvalueL, &LEDvalueR, &ActiveGas);
			if(xQueueSend(myQueueLORAHandle, &logic_q_buff, 0) != pdTRUE){
				while(1){}
			}
		}
	}
		/* ---------------------------------------------------------------------- */
	  /*           ALARM GENERATION                                             */
    /* ---------------------------------------------------------------------- */
		if((DeviceParam.LoRa == SENDER) || (DeviceParam.LoRa == NOLORA)){
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
	
    /* ---------------------------------------------------------------------- */
    /*           BUTTONS PROCESSING                                           */
    /* ---------------------------------------------------------------------- */
/*    if((ButtAlCounter == BUTT_TRIM)&&(flagOldAlButt == 0)){
      if((Alarm.ConcentratorMax)||(Alarm.CylindersEmpty)||(Alarm.LineMax)||(Alarm.LineMin))SilentTimer = ALRM_PAUSE;
      if(Alarm.PowerOff)UPS_SoundActive = 0;
      flagOldAlButt = 1;
    }
    if(ButtAlCounter == 0)flagOldAlButt = 0;
    if(ButtSwCounter == 0)flagOldSwButt = 0;*/

    /* ---------------------------------------------------------------------- */
    /*           ALARM SOUNDS AND LEDs PROCESSING                             */
    /* ---------------------------------------------------------------------- */
		if(LoraLinkOK || (DeviceParam.LoRa == SENDER)||(DeviceParam.LoRa == NOLORA)){
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
		}else Buzzer(1);
		/* ---------------------------------------------------------------------- */
	  /*           SLOW TIMERS                                                  */
    /* ---------------------------------------------------------------------- */		
		if(TickForward){
      if(BlinkFlag) BlinkFlag = 0; else BlinkFlag = 1;
      if(SilentTimer) SilentTimer--;
      if(ConcNORMCounter) ConcNORMCounter--;
      if(ConcSIGCounter) ConcSIGCounter--;
      TickForward = 0;
    }
		osDelay(3);
//		IWDG->KR = KR_KEY_RELOAD;
}
