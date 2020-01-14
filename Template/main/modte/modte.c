#include "string.h"
#include "stdio.h"

#include "modte/modte.h"


esp_err_t modte_init(modte_frame_t *te)
{
 	te->ID=0x0000;
	te->Length =0x00;
	te->Function_Opcode=0xFF;
	te->Perihap =0x00; 
	te->Data=0x0000;

	return ESP_OK;
}
///////////////////////////////////////////////////////
//////////////////////////////////////////////////////
esp_err_t set_ID( modte_frame_t *te , uint16_t new_ID)
{
	te->ID=new_ID;

	return ESP_OK;
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
esp_err_t modte_pack_frame(modte_frame_t *te, char *packing)
{
	*(packing +6)= (char)(((te->ID)>>8) &0x0011);
	*(packing +5)= (char)((te->ID) & 0x0011);

	*(packing +4)= (char)((te->Length) &0x0011);

	*(packing +3)= (char)((te->Function_Opcode) &0x0011);

	*(packing +2)= (char)((te->Perihap) &0x0011);

	*(packing +1)= (char)(((te->Data)>>8) &0x0011);
	*(packing +0)= (char)((te->Data) &0x0011);

	return ESP_OK;
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
esp_err_t modte_analyze_frame(modte_frame_t *te, char *packing)
{
	te->ID= (((uint16_t)(*(packing +6)))<<8) | ((uint16_t)(*(packing +5)));

	te->Length= (uint8_t)(*(packing +4 ));

	te->Function_Opcode= (uint8_t)(*(packing +3));

	te->Perihap= (uint8_t)(*(packing +2));	

	te->Data= (((uint16_t)(*(packing +1)))<<8) | (uint16_t)(*(packing +0));

	return ESP_OK;
}
