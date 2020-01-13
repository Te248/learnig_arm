#include "string.h"
#include "stdio.h"

#include "modte/modte.h"


static void modte_init(modte_frame_t *te)
{
 	te->ID=0x0000;
	te->Length =0x00;
	te->Function_Opcode=0xFF;
	te->Perihap =0x00; 
	te->Data=0x0000;
}
///////////////////////////////////////////////////////
//////////////////////////////////////////////////////
static void set_ID( modte_frame_t *te , uint16_t new_ID)
{
	te->ID=new_ID;
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
static void modte_pack_frame(modte_frame_t *te, uint8_t *packing)
{
	*(packing +6)= (uint8_t)(((te->ID)>>8) &0x0011);
	*(packing +5)= (uint8_t)((te->ID) &0x0011);

	*(packing +4)= (uint8_t)((te->Length) &0x0011);

	*(packing +3)= (uint8_t)((te->Function_Opcode) &0x0011);

	*(packing +2)= (uint8_t)((te->Perihap) &0x0011);

	*(packing +1)= (uint8_t)(((te->Data)>>8) &0x0011;
	*(packing +0)= (uint8_t)((te->Data) &0x0011);
}
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
static void modte_analyze_frame(modte_frame_t *te, uint8_t *packing);
{
	te->ID= (uint16_t)(*(packing +6)<<8) | (uint16_t)(*(packing +5));

	te->Length= *(packing +4 );

	te->Function_Opcode= *(packing +3);

	te->Perihap= *(packing +4 );	

	te->Data= (uint16_t)(*(packing +1)<<8) | (uint16_t)(*(packing +0));
}
