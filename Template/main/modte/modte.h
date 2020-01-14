
#ifndef __MODTE_H
#define __MODTE_H

typedef struct
{
	uint16_t ID;
	uint8_t Length;
	uint8_t Function_Opcode;
	uint8_t Perihap;
	uint16_t Data;
}modte_frame_t;

// FRAME modte ////
//_______________________________________________________________________________________________
//  ID    |  Length  |  function-opcode   | Perihap | Data
//--------------------------------------------------------------------------------------------
// 2-byte |     1    |     1-byte         | 1-byte  | 2 byte
//---------------------------------------------------------------------------------------------------
//   0000 |     00   |     FF             | 00      | 0000   \\\ to receive a PID from server
//---------------------------------------------------------------------------------------------------
   

/*
	after make first frame, you should send it to get ID  
 
*/
esp_err_t modte_init( modte_frame_t *te);

/*
	after make first frame, you should send it to get ID  
 
*/
esp_err_t set_ID( modte_frame_t *te , uint16_t new_ID);


/*
	we will pakage a message to send
 
*/
esp_err_t modte_pack_frame(modte_frame_t *te, char *packing);

/*
	we will analyze a message
 
*/
esp_err_t modte_analyze_frame(modte_frame_t *te, char *packing);

#endif
