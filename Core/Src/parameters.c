#include "main.h"
#include "cmsis_os.h"

TypeParameters DeviceParam;

void InitParam(TypeParameters* Param){
	Param->LR_FREQ = LORA_FREQ;
	Param->tx_device_num = TX_DEV_NUM;
	Param->rx_device_num = RX_DEV_NUM;
	Param->Role = ROLE;
	Param->CommDevice = COMM_DEV;
	Param->Baranki = BARANKI;
	Param->ConcDelay = CONC_DELAY;
	Param->HPressSwitch = SWTCH_THRESHOLD;
	Param->HPressAlarm = ALRM_THRESHOLD;
	Param->PressLineMin = LINE_P_MIN;
	Param->PressLineMax = LINE_P_MAX;
	Param->PressConcMin = CONC_P_MIN;
	Param->PressConcMax = CONC_P_MAX;
	Param->CylinderNumberLeft = CYL_NUM_LEFT;
	Param->CylinderNumberRight = CYL_NUM_RIGHT;
}

