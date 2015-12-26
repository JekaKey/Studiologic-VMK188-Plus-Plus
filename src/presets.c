#include <string.h>
#include "jsmn.h"
#include "json_parse.h"
#include "presets.h"
#include "keyboardscan.h"
#include "sd_fatfs.h"

/*to remove*/
#include "leds.h"
#include "log.h"
/************/

uint8_t okIO=1;//if this flag is zero all I/O operations will be canceled.


presetType Preset;  //Current preset global structure

currentStateType Current_state={"",""};
calibrationType Calibration;
curve_points_type Curve;

/*jsmn global variables*/
jsmntok_t tokens[TOKENS_NUM];
char js_buff[JSON_BUFF_SIZE];

extern const char slider_names[][MAX_ATTR_SIZE];
extern const char button_names[][MAX_ATTR_SIZE];
extern const uint8_t pedalsN[PEDALS_N];
extern const uint8_t slidersN[SLIDERS_N];
extern const uint8_t knobsN[KNOBS_N];

void set_okIOzero(void){
	okIO=0;
}

uint16_t presetCRC(presetType *pr) {
	uint16_t crc = 0xFFFF;
	uint8_t i;
	uint8_t * data = (uint8_t*)pr+2; //first 2 bytes is crc itself
	uint16_t len=sizeof(presetType)-2;
    while(len--) {
        crc ^= *data++ << 8;

        for(i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}
/***********************/

static void json_write_string(uint8_t level, const char* st, FIL* fff) { //use to write brackets into json
	char sss[20] = { 0 };
	memset(sss, '\t', level * JSON_TAB);
	strcat(sss, st);
	strcat(sss, "\r\n");
	f_puts(sss, fff);
}

static void json_write_value(uint8_t level, const char* name,
	                  const char* value, uint8_t colon, FIL* fff) {
	char sss[64] = { 0 };
	memset(sss, '\t', level * JSON_TAB);
	strcat(sss, "\"");
	strcat(sss, name);
	strcat(sss, "\":\"");
	strcat(sss, value);
	if (colon != 0) {
		strcat(sss, "\",\r\n");
	} else {
		strcat(sss, "\"\r\n");
	}
	f_puts(sss, fff);
}

static void json_write_object(uint8_t level, const char* name, FIL* fff) {
	char sss[64] = { 0 };
	memset(sss, '\t', level * JSON_TAB);
	strcat(sss, "\"");
	strcat(sss, name);
	strcat(sss, "\":{\r\n");
	f_puts(sss, fff);
}

char* itoa(int i, char* b){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as you go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}


static void json_write_number(uint8_t level, const char* name,
	int number, uint8_t colon, FIL* fff) { //write some json parameter with numeric int value
	char sss[64]={0};
	char lll[16];
	memset(sss, '\t', level * JSON_TAB);
	strcat(sss, "\"");
	strcat(sss, name);
	strcat(sss,"\":");
	itoa(number,lll);
	strcat(sss,lll);
	if (colon) {
		strcat(sss,",\r\n");
	}else{
		strcat(sss,"\r\n");
	}
	f_puts(sss, fff);
}


FIO_status calibration_rename(file_list_type *cal_list, char *new_name){
	char name[MAX_FNAME];
	char path_old[64] = "0:/" CALIBR_DIR_NAME "/";
	char path_new[64] = "0:/" CALIBR_DIR_NAME "/";
	strcpy(name,new_name);
	strcat(name, CALIBR_EXT); //add file name to path
	strcat(path_old, cal_list->names[cal_list->pos]); //add file name to path;
	strcat(path_new, name); //add file name to path;
	FRESULT res = f_rename(path_old, path_new);
	if (res == FR_OK) {
		strcpy(cal_list->names[cal_list->pos], name);
		return FIO_OK;
	} else {
		return FIO_RENAME_ERROR;
	}
}

FIO_status calibration_delete(file_list_type *cal_list){
	char path[64] = "0:/" CALIBR_DIR_NAME "/";
	strcat(path, cal_list->names[cal_list->pos]); //path to delete;
	FRESULT res = f_unlink(path);
	if (res == FR_OK) {
		return FIO_OK;
	} else {
		return FIO_DELETE_ERROR;
	}
}


FIO_status currentState_save(void){
	FIL fff; // File handler
	FIO_status res = FIO_OK;
	if (SDFS_open(&fff, "0:/" SETTING_NAME, F_WR_CLEAR) != SDFS_OK){
		return FIO_FILE_CREATE_ERROR;
	}
	json_write_string(0,"{",&fff);
	json_write_value(1, ATTR_SET_CALIBR,Current_state.calibration_name,1,&fff);
	json_write_value(1, ATTR_SET_PRESET,Current_state.preset_name,0,&fff);
	json_write_string(0,"}",&fff);
	if (SDFS_close(&fff)!= SDFS_OK)
		return FIO_FILE_CLOSE_ERROR;
	return res;
}

FIO_status calibration_save(const char* path, calibrationType* cal){
	FIL fff; // File handler
	FIO_status res = FIO_OK;
	int i;
	if (SDFS_open(&fff, path, F_WR_CLEAR) != SDFS_OK) {
		return FIO_FILE_CREATE_ERROR;
	}
	json_write_string(0, "{", &fff);
	json_write_string(1, "\"" ATTR_CAL_SLIDERS "\":{", &fff);

	for (i = 0; i < SLIDERS_AMOUNT; i++) {
		json_write_object(2, slider_names[i],  &fff);
		json_write_number(3, ATTR_CAL_S_MIN, cal->calibr[i].min_in_value, 1, &fff);
		json_write_number(3, ATTR_CAL_S_MAX, cal->calibr[i].max_in_value, 1, &fff);
		json_write_number(3, ATTR_CAL_S_DELTA, cal->calibr[i].delta, 1, &fff);
		json_write_number(3, ATTR_CAL_S_DEAD, cal->calibr[i].dead, 1, &fff);
		json_write_number(3, ATTR_CAL_S_GAP, cal->calibr[i].gap, 0, &fff);
		if (i < SLIDERS_AMOUNT-1){
			json_write_string(2, "},", &fff);
		}else{
			json_write_string(2, "}", &fff);
		}
	}
	json_write_string(1, "}", &fff);
	json_write_string(0, "}", &fff);
	if (SDFS_close(&fff)!= SDFS_OK)
		return FIO_FILE_CLOSE_ERROR;
	return res;

}

FIO_status preset_rename(file_list_type *pr_list, char *new_name){
	char name[MAX_FNAME];
	char path_old[64] = "0:/" PRESET_DIR_NAME "/";
	char path_new[64] = "0:/" PRESET_DIR_NAME "/";
	strcpy(name,new_name);
	strcat(name, PRESET_EXT); //add file name to path
	strcat(path_old, pr_list->names[pr_list->pos]); //add file name to path;
	strcat(path_new, name); //add file name to path;
	FRESULT res = f_rename(path_old, path_new);
	if (res == FR_OK) {
		strcpy(pr_list->names[pr_list->pos], name);
		return FIO_OK;
	} else {
		return FIO_RENAME_ERROR;
	}
}

FIO_status preset_delete(file_list_type *pr_list){
	char path[64] = "0:/" PRESET_DIR_NAME "/";
	strcat(path, pr_list->names[pr_list->pos]); //path to delete;
	FRESULT res = f_unlink(path);
	if (res == FR_OK) {
		return FIO_OK;
	} else {
		return FIO_DELETE_ERROR;
	}
}


FIO_status preset_save(const char* path, presetType* pr){
	FIL fff; // File handler
	FIO_status res = FIO_OK;
	int i;
	if (SDFS_open(&fff, path, F_WR_CLEAR) != SDFS_OK) {
		return FIO_FILE_CREATE_ERROR;
	}
	json_write_string(0, "{", &fff);
	json_write_number(1, ATTR_CHANNEL, pr->MidiChannel, 1, &fff);
	json_write_string(1, "\"" ATTR_SPLIT "\":{", &fff);
	json_write_number(2, ATTR_SPLIT_ACTIVE, pr->SplitActive, 1, &fff);
	json_write_number(2, ATTR_SPLIT_KEY, pr->SplitKey, 1, &fff);
	json_write_number(2, ATTR_SPLIT_CHANNEL, pr->SplitChannel, 1, &fff);
	json_write_number(2, ATTR_SPLIT_OCTAVE, pr->SplitOctShift, 0, &fff);
	json_write_string(1, "},", &fff);
	json_write_number(1, ATTR_HIRES, pr->HighResEnable, 1, &fff);
	json_write_number(1, ATTR_ANALOGMIDI, pr->AnalogMidiEnable, 1, &fff);
	json_write_number(1, ATTR_TRANSPOSE, pr->Transpose, 1, &fff);
	json_write_number(1, ATTR_OCTAVE, pr->OctaveShift, 1, &fff);
	json_write_string(1, "\"" ATTR_CURVE "\":{", &fff);
	json_write_number(2, ATTR_CURVE_XW1, pr->Curve.xw1, 1, &fff);
	json_write_number(2, ATTR_CURVE_YW1, pr->Curve.yw1, 1, &fff);
	json_write_number(2, ATTR_CURVE_XW2, pr->Curve.xw2, 1, &fff);
	json_write_number(2, ATTR_CURVE_YW2, pr->Curve.yw2, 1, &fff);
	json_write_number(2, ATTR_CURVE_XW3, pr->Curve.xw3, 1, &fff);
	json_write_number(2, ATTR_CURVE_YW3, pr->Curve.yw3, 1, &fff);
	json_write_number(2, ATTR_CURVE_XB1, pr->Curve.xb1, 1, &fff);
	json_write_number(2, ATTR_CURVE_YB1, pr->Curve.yb1, 1, &fff);
	json_write_number(2, ATTR_CURVE_XB2, pr->Curve.xb2, 1, &fff);
	json_write_number(2, ATTR_CURVE_YB2, pr->Curve.yb2, 1, &fff);
	json_write_number(2, ATTR_CURVE_XB3, pr->Curve.xb3, 1, &fff);
	json_write_number(2, ATTR_CURVE_YB3, pr->Curve.yb3, 0, &fff);
	json_write_string(1, "},", &fff);

	json_write_object(1, slider_names[SLIDER_PITCH],  &fff);
	json_write_number(2, ATTR_S_ACTIVE, pr->sliders[SLIDER_PITCH].active, 1, &fff);
	json_write_number(2, ATTR_S_CHANNEL, pr->sliders[SLIDER_PITCH].channel, 0, &fff);
	json_write_string(1, "},", &fff);

	json_write_object(1, slider_names[SLIDER_AT],  &fff);
	json_write_number(2, ATTR_S_ACTIVE, pr->sliders[SLIDER_AT].active, 1, &fff);
	json_write_number(2, ATTR_S_CHANNEL, pr->sliders[SLIDER_AT].channel, 1, &fff);
	json_write_number(2, ATTR_S_MIN, pr->sliders[SLIDER_AT].min_out_value, 1, &fff);
	json_write_number(2, ATTR_S_MAX, pr->sliders[SLIDER_AT].max_out_value, 0, &fff);
	json_write_string(1, "},", &fff);

	json_write_object(1, slider_names[SLIDER_MOD],  &fff);
	json_write_number(2, ATTR_S_ACTIVE, pr->sliders[SLIDER_MOD].active, 1, &fff);
	json_write_number(2, ATTR_S_REVERSE, pr->sliders[SLIDER_MOD].reverse, 1, &fff);
	json_write_number(2, ATTR_S_CHANNEL, pr->sliders[SLIDER_MOD].channel, 1, &fff);
	json_write_number(2, ATTR_S_EVENT, pr->sliders[SLIDER_MOD].event, 1, &fff);
	json_write_number(2, ATTR_S_MIN, pr->sliders[SLIDER_MOD].min_out_value, 1, &fff);
	json_write_number(2, ATTR_S_MAX, pr->sliders[SLIDER_MOD].max_out_value, 0, &fff);
	json_write_string(1, "},", &fff);


	json_write_string(1, "\"" ATTR_PEDALS "\":{", &fff);
	for (i = 0; i < PEDALS_N; i++) {
		json_write_object(2, slider_names[pedalsN[i]],  &fff);
		json_write_number(3, ATTR_S_ACTIVE, pr->sliders[pedalsN[i]].active, 1, &fff);
		json_write_number(3, ATTR_S_REVERSE, pr->sliders[pedalsN[i]].reverse, 1, &fff);
		json_write_number(3, ATTR_S_BINARY, pr->sliders[pedalsN[i]].binary, 1, &fff);
		json_write_number(3, ATTR_S_CHANNEL, pr->sliders[pedalsN[i]].channel, 1, &fff);
		json_write_number(3, ATTR_S_EVENT, pr->sliders[pedalsN[i]].event, 1, &fff);
		json_write_number(3, ATTR_S_MIN, pr->sliders[pedalsN[i]].min_out_value, 1, &fff);
		json_write_number(3, ATTR_S_MAX, pr->sliders[pedalsN[i]].max_out_value, 0, &fff);
		if (i<PEDALS_N-1){
			json_write_string(2, "},", &fff);
		}else{
			json_write_string(2, "}", &fff);
		}
	}
	json_write_string(1, "},", &fff);
	json_write_string(1, "\"" ATTR_SLIDERS "\":{", &fff);
	for (i = 0; i < SLIDERS_N; i++) {
		json_write_object(2, slider_names[slidersN[i]],  &fff);
		json_write_number(3, ATTR_S_ACTIVE, pr->sliders[slidersN[i]].active, 1, &fff);
		json_write_number(3, ATTR_S_REVERSE, pr->sliders[slidersN[i]].reverse, 1, &fff);
		json_write_number(3, ATTR_S_CHANNEL, pr->sliders[slidersN[i]].channel, 1, &fff);
		json_write_number(3, ATTR_S_EVENT, pr->sliders[slidersN[i]].event, 1, &fff);
		json_write_number(3, ATTR_S_MIN, pr->sliders[slidersN[i]].min_out_value, 1, &fff);
		json_write_number(3, ATTR_S_MAX, pr->sliders[slidersN[i]].max_out_value, 0, &fff);
		if (i<SLIDERS_N-1){
			json_write_string(2, "},", &fff);
		}else{
			json_write_string(2, "}", &fff);
		}
	}
	json_write_string(1, "},", &fff);
	json_write_string(1, "\"" ATTR_KNOBS "\":{", &fff);
	for (i = 0; i < KNOBS_N; i++) {
		json_write_object(2, slider_names[knobsN[i]],  &fff);
		json_write_number(3, ATTR_S_ACTIVE, pr->sliders[knobsN[i]].active, 1, &fff);
		json_write_number(3, ATTR_S_REVERSE, pr->sliders[knobsN[i]].reverse, 1, &fff);
		json_write_number(3, ATTR_S_CHANNEL, pr->sliders[knobsN[i]].channel, 1, &fff);
		json_write_number(3, ATTR_S_EVENT, pr->sliders[knobsN[i]].event, 1, &fff);
		json_write_number(3, ATTR_S_MIN, pr->sliders[knobsN[i]].min_out_value, 1, &fff);
		json_write_number(3, ATTR_S_MAX, pr->sliders[knobsN[i]].max_out_value, 0, &fff);
		if (i<KNOBS_N-1){
			json_write_string(2, "},", &fff);
		}else{
			json_write_string(2, "}", &fff);
		}
	}
	json_write_string(1, "},", &fff);
	json_write_string(1, "\"" ATTR_BUTTONS "\":{", &fff);
	for (i = 0; i < BUTTONS_AMOUNT; i++) {
		json_write_object(2, button_names[i],  &fff);
		json_write_number(3, ATTR_B_ACTIVE, pr->buttons[i].active, 1, &fff);
		json_write_number(3, ATTR_B_TYPE, pr->buttons[i].type, 1, &fff);
		json_write_number(3, ATTR_B_CHANNEL, pr->buttons[i].channel, 1, &fff);
		json_write_number(3, ATTR_B_EVENT, pr->buttons[i].event, 1, &fff);
		json_write_number(3, ATTR_B_ON, pr->buttons[i].on, 1, &fff);
		json_write_number(3, ATTR_B_OFF, pr->buttons[i].off, 0, &fff);
		if (i<BUTTONS_AMOUNT-1){
			json_write_string(2, "},", &fff);
		}else{
			json_write_string(2, "}", &fff);
		}
	}
	json_write_string(1, "}", &fff);
	json_write_string(0, "}", &fff);
	pr->Crc=presetCRC(pr);
	if (SDFS_close(&fff)!= SDFS_OK)
		return FIO_FILE_CREATE_ERROR;
	return res;
}



FIO_status curve_save(const char* path, curve_points_type* curve){
	FIL fff; // File handler
	FIO_status res = FIO_OK;
	if (SDFS_open(&fff, path, F_WR_CLEAR) != SDFS_OK) {
		return FIO_FILE_CREATE_ERROR;
	}
	json_write_string(0, "{", &fff);
	json_write_number(1, ATTR_CURVE_XW1, curve->xw1, 1, &fff);
	json_write_number(1, ATTR_CURVE_YW1, curve->yw1, 1, &fff);
	json_write_number(1, ATTR_CURVE_XW2, curve->xw2, 1, &fff);
	json_write_number(1, ATTR_CURVE_YW2, curve->yw2, 1, &fff);
	json_write_number(1, ATTR_CURVE_XW3, curve->xw3, 1, &fff);
	json_write_number(1, ATTR_CURVE_YW3, curve->yw3, 1, &fff);
	json_write_number(1, ATTR_CURVE_XB1, curve->xb1, 1, &fff);
	json_write_number(1, ATTR_CURVE_YB1, curve->yb1, 1, &fff);
	json_write_number(1, ATTR_CURVE_XB2, curve->xb2, 1, &fff);
	json_write_number(1, ATTR_CURVE_YB2, curve->yb2, 1, &fff);
	json_write_number(1, ATTR_CURVE_XB3, curve->xb3, 1, &fff);
	json_write_number(1, ATTR_CURVE_YB3, curve->yb3, 0, &fff);
	json_write_string(0, "}", &fff);
	if (SDFS_close(&fff)!= SDFS_OK)
		return FIO_FILE_CLOSE_ERROR;
	return res;
}

FIO_status curve_delete(file_list_type *cur_list){
	char path[64] = "0:/" CURVE_DIR_NAME "/";
	strcat(path, cur_list->names[cur_list->pos]); //path to delete;
	FRESULT res = f_unlink(path);
	if (res == FR_OK) {
		return FIO_OK;
	} else {
		return FIO_DELETE_ERROR;
	}
}

FIO_status curve_rename(file_list_type *cur_list, char *new_name){
	char name[MAX_FNAME];
	char path_old[64] = "0:/" CURVE_DIR_NAME "/";
	char path_new[64] = "0:/" CURVE_DIR_NAME "/";
	strcpy(name,new_name);
	strcat(name, CURVE_EXT); //add file name to path
	strcat(path_old, cur_list->names[cur_list->pos]); //add file name to path;
	strcat(path_new, name); //add file name to path;
	FRESULT res = f_rename(path_old, path_new);
	if (res == FR_OK) {
		strcpy(cur_list->names[cur_list->pos], name);
		return FIO_OK;
	} else {
		return FIO_RENAME_ERROR;
	}
}


/***Structures and arrays describing expected JSON attributes, objects and values***/

static json_attr_t setting_attr[] = {
    {ATTR_SET_CALIBR,   t_string, .addr.string = Current_state.calibration_name},
    {ATTR_SET_PRESET,   t_string, .addr.string = Current_state.preset_name},
    {"",},
};

static json_attr_t split_attr[]={
		{ATTR_SPLIT_ACTIVE, t_uint8,},
		{ATTR_SPLIT_KEY, t_uint8,},
		{ATTR_SPLIT_CHANNEL, t_uint8,},
		{ATTR_SPLIT_OCTAVE, t_int8,},
		{"",},
};


static json_attr_t pedals_param_attr[PEDALS_N+1][8];
static json_attr_t pedals_attr[PEDALS_N+1];

static json_attr_t sliders_param_attr[SLIDERS_N+1][7];
static json_attr_t sliders_attr[SLIDERS_N+1];

static json_attr_t knobs_param_attr[KNOBS_N+1][7];
static json_attr_t knobs_attr[KNOBS_N+1];

static json_attr_t buttons_param_attr[BUTTONS_AMOUNT+1][7];
static json_attr_t buttons_attr[BUTTONS_AMOUNT+1];

static json_attr_t pitch_param_attr[3];
static json_attr_t pitch_attr;

static json_attr_t mod_param_attr[7];
static json_attr_t mod_attr;

static json_attr_t at_param_attr[5];
static json_attr_t at_attr;


static json_attr_t preset_curve_attr[] ={
		{ATTR_CURVE_XW1, t_uint32, },
		{ATTR_CURVE_YW1, t_uint32, },
		{ATTR_CURVE_XW2, t_uint32, },
		{ATTR_CURVE_YW2, t_uint32, },
		{ATTR_CURVE_XW3, t_uint32, },
		{ATTR_CURVE_YW3, t_uint32, },
		{ATTR_CURVE_XB1, t_uint32, },
		{ATTR_CURVE_YB1, t_uint32, },
		{ATTR_CURVE_XB2, t_uint32, },
		{ATTR_CURVE_YB2, t_uint32, },
		{ATTR_CURVE_XB3, t_uint32, },
		{ATTR_CURVE_YB3, t_uint32, },
		{"",},
};


static json_attr_t preset_attr[20] = {
		{ATTR_CHANNEL, t_uint8,},
		{ATTR_SPLIT,t_object, .addr.object = split_attr},
		{ATTR_HIRES, t_uint8,},
		{ATTR_ANALOGMIDI, t_uint8,},
		{ATTR_TRANSPOSE, t_int8,},
		{ATTR_OCTAVE, t_int8,},
		{ATTR_CURVE, t_object, .addr.object = preset_curve_attr},
		{ATTR_PI, t_object, .addr.object = &pitch_attr},
		{ATTR_AT, t_object, .addr.object = &at_attr},
		{ATTR_MO, t_object, .addr.object = &mod_attr},
		{ATTR_PEDALS, t_object, .addr.object = pedals_attr},
		{ATTR_SLIDERS, t_object, .addr.object = sliders_attr},
		{ATTR_KNOBS, t_object, .addr.object = knobs_attr},
		{ATTR_BUTTONS, t_object, .addr.object = buttons_attr},
		{"",},
};

static json_attr_t calibr_sliders_attr[SLIDERS_AMOUNT+1];
static json_attr_t calibr_sliders_param_attr[SLIDERS_AMOUNT+1][6];
static json_attr_t calibr_attr[] = {
		{ATTR_CAL_SLIDERS, t_object, .addr.object = calibr_sliders_attr},
		{"",},
};

static json_attr_t curve_attr[] ={
		{ATTR_CURVE_XW1, t_uint32, },
		{ATTR_CURVE_YW1, t_uint32, },
		{ATTR_CURVE_XW2, t_uint32, },
		{ATTR_CURVE_YW2, t_uint32, },
		{ATTR_CURVE_XW3, t_uint32, },
		{ATTR_CURVE_YW3, t_uint32, },
		{ATTR_CURVE_XB1, t_uint32, },
		{ATTR_CURVE_YB1, t_uint32, },
		{ATTR_CURVE_XB2, t_uint32, },
		{ATTR_CURVE_YB2, t_uint32, },
		{ATTR_CURVE_XB3, t_uint32, },
		{ATTR_CURVE_YB3, t_uint32, },
		{"",},
};

/***END Structures and arrays describing expected JSON attributes, objects and values END***/

/* Functions make links between JSON structures and variables*/
/*Modify some structures fields and assign addresses of variables to structures fields*/
/************************Not good looking :-( *************************/
static void init_json_preset_attr(presetType *preset) {
	preset_attr[0].addr.uint8 = &(preset->MidiChannel);
	preset_attr[2].addr.uint8 = &(preset->HighResEnable);
	preset_attr[3].addr.uint8 = &(preset->AnalogMidiEnable);
	preset_attr[4].addr.int8 = &(preset->Transpose);
	preset_attr[5].addr.int8 = &(preset->OctaveShift);

	split_attr[0].addr.uint8 = &(preset->SplitActive);
	split_attr[1].addr.uint8 = &(preset->SplitKey);
	split_attr[2].addr.uint8 = &(preset->SplitChannel);
	split_attr[3].addr.int8 = &(preset->SplitOctShift);

	/* Assign pitch attribite*/
	strcpy(pitch_attr.attribute, slider_names[SLIDER_PITCH]);
	pitch_attr.type = t_object;
	pitch_attr.addr.object = pitch_param_attr;
	strcpy(pitch_param_attr[0].attribute, ATTR_S_ACTIVE);
	pitch_param_attr[0].addr.uint8 = &(preset->sliders[SLIDER_PITCH].active);
	strcpy(pitch_param_attr[1].attribute, ATTR_S_CHANNEL);
	pitch_param_attr[1].addr.uint8 = &(preset->sliders[SLIDER_PITCH].channel);
	for (int j = 0; j < 2; j++) {
		pitch_param_attr[j].type = t_uint8;
	}
	pitch_param_attr[2].attribute[0] = 0;
	/*****/



    /* Assign mod attribite*/
	strcpy(mod_attr.attribute, slider_names[SLIDER_MOD]);
	mod_attr.type = t_object;
	mod_attr.addr.object = mod_param_attr;
	strcpy(mod_param_attr[0].attribute, ATTR_S_ACTIVE);
	mod_param_attr[0].addr.uint8 = &(preset->sliders[SLIDER_MOD].active);
	strcpy(mod_param_attr[1].attribute, ATTR_S_REVERSE);
	mod_param_attr[1].addr.uint8 = &(preset->sliders[SLIDER_MOD].reverse);
	strcpy(mod_param_attr[2].attribute, ATTR_S_CHANNEL);
	mod_param_attr[2].addr.uint8 = &(preset->sliders[SLIDER_MOD].channel);
	strcpy(mod_param_attr[3].attribute, ATTR_S_EVENT);
	mod_param_attr[3].addr.uint8 = &(preset->sliders[SLIDER_MOD].event);
	strcpy(mod_param_attr[4].attribute, ATTR_S_MIN);
	mod_param_attr[4].addr.uint16 = &(preset->sliders[SLIDER_MOD].min_out_value);
	strcpy(mod_param_attr[5].attribute, ATTR_S_MAX);
	mod_param_attr[5].addr.uint16 = &(preset->sliders[SLIDER_MOD].max_out_value);
	for (int j = 0; j < 6; j++) {
		mod_param_attr[j].type = t_uint8;
	}
	mod_param_attr[6].attribute[0]=0;
    /*****/

	/* Assign at attribite*/
	strcpy(at_attr.attribute, slider_names[SLIDER_AT]);
	at_attr.type = t_object;
	at_attr.addr.object = at_param_attr;
	strcpy(at_param_attr[0].attribute, ATTR_S_ACTIVE);
	at_param_attr[0].addr.uint8 = &(preset->sliders[SLIDER_AT].active);
	strcpy(at_param_attr[1].attribute, ATTR_S_CHANNEL);
	at_param_attr[1].addr.uint8 = &(preset->sliders[SLIDER_AT].channel);
	strcpy(at_param_attr[2].attribute, ATTR_S_MIN);
	at_param_attr[2].addr.uint16 = &(preset->sliders[SLIDER_AT].min_out_value);
	strcpy(at_param_attr[3].attribute, ATTR_S_MAX);
	at_param_attr[3].addr.uint16 = &(preset->sliders[SLIDER_AT].max_out_value);
	for (int j = 0; j < 4; j++) {
		at_param_attr[j].type = t_uint8;
	}
	at_param_attr[4].attribute[0] = 0;
	/*****/


	/*Assign pedals addresses and attributes*/
	for (int i = 0; i < PEDALS_N; i++) {
		strcpy(pedals_attr[i].attribute, slider_names[pedalsN[i]]);
		pedals_attr[i].type = t_object;
		pedals_attr[i].addr.object = pedals_param_attr[i];
		strcpy(pedals_param_attr[i][0].attribute, ATTR_S_ACTIVE);
		pedals_param_attr[i][0].addr.uint8 = &(preset->sliders[pedalsN[i]].active);
		strcpy(pedals_param_attr[i][1].attribute, ATTR_S_REVERSE);
		pedals_param_attr[i][1].addr.uint8 = &(preset->sliders[pedalsN[i]].reverse);
		strcpy(pedals_param_attr[i][2].attribute, ATTR_S_BINARY);
		pedals_param_attr[i][2].addr.uint8 = &(preset->sliders[pedalsN[i]].binary);
		strcpy(pedals_param_attr[i][3].attribute, ATTR_S_CHANNEL);
		pedals_param_attr[i][3].addr.uint8 = &(preset->sliders[pedalsN[i]].channel);
		strcpy(pedals_param_attr[i][4].attribute, ATTR_S_EVENT);
		pedals_param_attr[i][4].addr.uint8 = &(preset->sliders[pedalsN[i]].event);
		strcpy(pedals_param_attr[i][5].attribute, ATTR_S_MIN);
		pedals_param_attr[i][5].addr.uint16 = &(preset->sliders[pedalsN[i]].min_out_value);
		strcpy(pedals_param_attr[i][6].attribute, ATTR_S_MAX);
		pedals_param_attr[i][6].addr.uint16 = &(preset->sliders[pedalsN[i]].max_out_value);
		for (int j = 0; j < 7; j++) {
			pedals_param_attr[i][j].type = t_uint8;
		}
		pedals_param_attr[i][7].attribute[0]=0;
	}
	pedals_attr[PEDALS_N].attribute[0]=0;

	/*Assign sliders addresses and attributes*/
	for (int i = 0; i < SLIDERS_N; i++) {
		strcpy(sliders_attr[i].attribute, slider_names[slidersN[i]]);
		sliders_attr[i].type = t_object;
		sliders_attr[i].addr.object = sliders_param_attr[i];
		strcpy(sliders_param_attr[i][0].attribute, ATTR_S_ACTIVE);
		sliders_param_attr[i][0].addr.uint8 = &(preset->sliders[slidersN[i]].active);
		strcpy(sliders_param_attr[i][1].attribute, ATTR_S_REVERSE);
		sliders_param_attr[i][1].addr.uint8 = &(preset->sliders[slidersN[i]].reverse);
		strcpy(sliders_param_attr[i][2].attribute, ATTR_S_CHANNEL);
		sliders_param_attr[i][2].addr.uint8 = &(preset->sliders[slidersN[i]].channel);
		strcpy(sliders_param_attr[i][3].attribute, ATTR_S_EVENT);
		sliders_param_attr[i][3].addr.uint8 = &(preset->sliders[slidersN[i]].event);
		strcpy(sliders_param_attr[i][4].attribute, ATTR_S_MIN);
		sliders_param_attr[i][4].addr.uint16 = &(preset->sliders[slidersN[i]].min_out_value);
		strcpy(sliders_param_attr[i][5].attribute, ATTR_S_MAX);
		sliders_param_attr[i][5].addr.uint16 = &(preset->sliders[slidersN[i]].max_out_value);
		for (int j = 0; j < 6; j++) {
			sliders_param_attr[i][j].type = t_uint8;
		}
		sliders_param_attr[i][6].attribute[0]=0;
	}
	sliders_attr[SLIDERS_N].attribute[0]=0;

	/*Assign knobs addresses and attributes*/
	for (int i = 0; i < KNOBS_N; i++) {
		strcpy(knobs_attr[i].attribute, slider_names[knobsN[i]]);
		knobs_attr[i].type = t_object;
		knobs_attr[i].addr.object = knobs_param_attr[i];
		strcpy(knobs_param_attr[i][0].attribute, ATTR_S_ACTIVE);
		knobs_param_attr[i][0].addr.uint8 = &(preset->sliders[knobsN[i]].active);
		strcpy(knobs_param_attr[i][1].attribute, ATTR_S_REVERSE);
		knobs_param_attr[i][1].addr.uint8 = &(preset->sliders[knobsN[i]].reverse);
		strcpy(knobs_param_attr[i][2].attribute, ATTR_S_CHANNEL);
		knobs_param_attr[i][2].addr.uint8 = &(preset->sliders[knobsN[i]].channel);
		strcpy(knobs_param_attr[i][3].attribute, ATTR_S_EVENT);
		knobs_param_attr[i][3].addr.uint8 = &(preset->sliders[knobsN[i]].event);
		strcpy(knobs_param_attr[i][4].attribute, ATTR_S_MIN);
		knobs_param_attr[i][4].addr.uint16 = &(preset->sliders[knobsN[i]].min_out_value);
		strcpy(knobs_param_attr[i][5].attribute, ATTR_S_MAX);
		knobs_param_attr[i][5].addr.uint16 = &(preset->sliders[knobsN[i]].max_out_value);
		for (int j = 0; j < 6; j++) {
			knobs_param_attr[i][j].type = t_uint8;
		}
		knobs_param_attr[i][6].attribute[0]=0;
	}
	knobs_attr[KNOBS_N].attribute[0]=0;


	/*Assign buttons addresses and attributes*/
	for (int i = 0; i < BUTTONS_AMOUNT; i++) {
		strcpy(buttons_attr[i].attribute, button_names[i]);
		buttons_attr[i].type = t_object;
		buttons_attr[i].addr.object = buttons_param_attr[i];
		strcpy(buttons_param_attr[i][0].attribute, ATTR_B_ACTIVE);
		buttons_param_attr[i][0].addr.uint8 = &(preset->buttons[i].active);
		strcpy(buttons_param_attr[i][1].attribute, ATTR_B_TYPE);
		buttons_param_attr[i][1].addr.uint8 = &(preset->buttons[i].type);
		strcpy(buttons_param_attr[i][2].attribute, ATTR_B_CHANNEL);
		buttons_param_attr[i][2].addr.uint8 = &(preset->buttons[i].channel);
		strcpy(buttons_param_attr[i][3].attribute, ATTR_B_EVENT);
		buttons_param_attr[i][3].addr.uint8 = &(preset->buttons[i].event);
		strcpy(buttons_param_attr[i][4].attribute, ATTR_B_ON);
		buttons_param_attr[i][4].addr.uint8 = &(preset->buttons[i].on);
		strcpy(buttons_param_attr[i][5].attribute, ATTR_B_OFF);
		buttons_param_attr[i][5].addr.uint8 = &(preset->buttons[i].off);
		for (int j = 0; j < 6; j++) {
			buttons_param_attr[i][j].type = t_uint8;
		}
		buttons_param_attr[i][6].attribute[0]=0;
	}
	buttons_attr[BUTTONS_AMOUNT].attribute[0]=0;

	preset_curve_attr[0].addr.uint32=&(preset->Curve.xw1);
	preset_curve_attr[1].addr.uint32=&(preset->Curve.yw1);
	preset_curve_attr[2].addr.uint32=&(preset->Curve.xw2);
	preset_curve_attr[3].addr.uint32=&(preset->Curve.yw2);
	preset_curve_attr[4].addr.uint32=&(preset->Curve.xw3);
	preset_curve_attr[5].addr.uint32=&(preset->Curve.yw3);
	preset_curve_attr[6].addr.uint32=&(preset->Curve.xb1);
	preset_curve_attr[7].addr.uint32=&(preset->Curve.yb1);
	preset_curve_attr[8].addr.uint32=&(preset->Curve.xb2);
	preset_curve_attr[9].addr.uint32=&(preset->Curve.yb2);
	preset_curve_attr[10].addr.uint32=&(preset->Curve.xb3);
	preset_curve_attr[11].addr.uint32=&(preset->Curve.yb3);
}
	/*Assign calibration addresses and attributes*/
static void init_json_calibr_attr(calibrationType *cal) {
	for (int i = 0; i < SLIDERS_AMOUNT; i++){
		strcpy(calibr_sliders_attr[i].attribute, slider_names[i]);
		calibr_sliders_attr[i].type = t_object;
		calibr_sliders_attr[i].addr.object = calibr_sliders_param_attr[i];
		strcpy(calibr_sliders_param_attr[i][0].attribute, ATTR_CAL_S_MIN);
		calibr_sliders_param_attr[i][0].addr.uint16 = &(cal->calibr[i].min_in_value);
		strcpy(calibr_sliders_param_attr[i][1].attribute, ATTR_CAL_S_MAX);
		calibr_sliders_param_attr[i][1].addr.uint16 = &(cal->calibr[i].max_in_value);
		strcpy(calibr_sliders_param_attr[i][2].attribute, ATTR_CAL_S_DELTA);
		calibr_sliders_param_attr[i][2].addr.uint16 = &(cal->calibr[i].delta);
		strcpy(calibr_sliders_param_attr[i][3].attribute, ATTR_CAL_S_DEAD);
		calibr_sliders_param_attr[i][3].addr.uint8 = &(cal->calibr[i].dead);
		strcpy(calibr_sliders_param_attr[i][4].attribute, ATTR_CAL_S_GAP);
		calibr_sliders_param_attr[i][4].addr.uint8 = &(cal->calibr[i].gap);
		for (int j = 0; j < 3; j++) {
			calibr_sliders_param_attr[i][j].type = t_uint16;
		}
		calibr_sliders_param_attr[i][3].type = t_uint8;
		calibr_sliders_param_attr[i][4].type = t_uint8;
		calibr_sliders_param_attr[i][5].attribute[0]=0;
	}
	calibr_sliders_attr[SLIDERS_AMOUNT].attribute[0]=0;
}
	/*Assign curve addresses*/
static void init_json_curve_attr(curve_points_type * curve) {
	curve_attr[0].addr.uint32=&(curve->xw1);
	curve_attr[1].addr.uint32=&(curve->yw1);
	curve_attr[2].addr.uint32=&(curve->xw2);
	curve_attr[3].addr.uint32=&(curve->yw2);
	curve_attr[4].addr.uint32=&(curve->xw3);
	curve_attr[5].addr.uint32=&(curve->yw3);
	curve_attr[6].addr.uint32=&(curve->xb1);
	curve_attr[7].addr.uint32=&(curve->yb1);
	curve_attr[8].addr.uint32=&(curve->xb2);
	curve_attr[9].addr.uint32=&(curve->yb2);
	curve_attr[10].addr.uint32=&(curve->xb3);
	curve_attr[11].addr.uint32=&(curve->yb3);
}

/*******************************************************/

/*Load setting file start.cfg with current calibration file name and preset file name*/




FIO_status load_JSON(char* path, char *js_buff,  jsmntok_t *tokens, json_attr_t *json_attr){
	FIL fff; // File handler
	jsmn_parser parser;
	UINT size;
	SDFS_status_type res = SDFS_open(&fff, path, F_RD);
	if (res != SDFS_OK)  //Calibration not file exist
		return FIO_FILE_NOT_FOUND;
	FRESULT f_res=f_read(&fff, js_buff, JSON_BUFF_SIZE, &size);
	if (f_res!=FR_OK){
		if (SDFS_close(&fff)!= SDFS_OK)
			return FIO_FILE_CLOSE_ERROR;
		return FIO_READ_ERROR;
	}
	js_buff[size] = 0;
	jsmn_init(&parser);
	jsmnerr_t result = jsmn_parse(&parser, js_buff, size, tokens, TOKENS_NUM);
    if (result<0){
	    SDFS_close(&fff);
    	return FIO_JSON_FORMAT_ERR;
    }

    parse_result_t parse_result = tokens_parse(js_buff, tokens, json_attr, 0);
	if (parse_result != parse_ok){
		if (SDFS_close(&fff)!= SDFS_OK)
			return FIO_FILE_CLOSE_ERROR;
		return FIO_JSON_DATA_ERR;
	}
	if (SDFS_close(&fff)!= SDFS_OK)
		return FIO_FILE_CLOSE_ERROR;
    return FIO_OK;
}

FIO_status currentState_load(void) {
     	FIO_status status=load_JSON("0:/" SETTING_NAME, js_buff, tokens, setting_attr );
	return status;
}


FIO_status start_load_setting(void){
	if (currentState_load() == FIO_OK) { //Current state loaded
		return FIO_OK;
	} else { 		//Current state file not exist
		return currentState_save();
	}
}

/*3 functions loading parameters from json files to structure object*/
/*If some parameters do not exist in JSON they will not change*/

FIO_status calibration_load(char* name, calibrationType* cal ){
	    char path[64] = "0:/" CALIBR_DIR_NAME "/";
    	strcat(path, name);
    	init_json_calibr_attr(cal);
     	FIO_status status=load_JSON(path, js_buff, tokens, calibr_attr);
        return status;
}

FIO_status curve_load(char* name, curve_points_type  *curve) {
	char path[64] = "0:/" CURVE_DIR_NAME "/";
	strcat(path, name); //add file name to path
	init_json_curve_attr(curve);
	FIO_status status=load_JSON(path, js_buff, tokens, curve_attr);
    return status;
}


FIO_status preset_load(char* name, presetType* pr) {
	char path[64]="0:/" PRESET_DIR_NAME "/";
	strcat(path,name);//add file name to path
	init_json_preset_attr(pr);
	FIO_status status=load_JSON(path, js_buff, tokens, preset_attr);
	calculate_velocity_formula(&pr->Curve);
	return status;
}



static void preset_set_defaults(presetType* pr){
	pr->MidiChannel=1;
	pr->HighResEnable=0;
	pr->SplitActive=0;
	pr->SplitKey=0;
	pr->SplitChannel=1;
	pr->SplitOctShift=0;
	pr->AnalogMidiEnable=0;
	pr->Transpose=0;
	pr->OctaveShift=0;
}

static void curve_set_defaults(presetType* pr){
	pr->Curve.xw1=3600;
	pr->Curve.yw1=127*0x80;
	pr->Curve.xw2=13800;
	pr->Curve.yw2=50*0x80;
	pr->Curve.xw3=101400;
	pr->Curve.yw3=1*0x80;
	pr->Curve.xb1=2800;
	pr->Curve.yb1=127*0x80;
	pr->Curve.xb2=10000;
	pr->Curve.yb2=50*0x80;
	pr->Curve.xb3=75000;
	pr->Curve.yb3=1*0x80;
	calculate_velocity_formula(&pr->Curve);
}



file_list_type presets_list, calibrations_list, curves_list;

static void init_calibration_list(void){
	calibrations_list.active = 0; //Position of an active item
	calibrations_list.num = 1; //Number of items in a file list
	calibrations_list.pos = 0; //Current position in a list
	strcpy(calibrations_list.names[0], DEFAULT_CALIBR_NAME);
}

FIO_status start_load_calibration(calibrationType* cal){
	SDFS_status_type res;
	FIO_status fiores;
	char path[64];
	if (Current_state.calibration_name[0]) { //name is not empty string
		fiores = calibration_load(Current_state.calibration_name, cal); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
			res = SDFS_scandir("0:/" CALIBR_DIR_NAME, &calibrations_list);
			return FIO_OK; //all is done
		} else {
			if (fiores == FIO_SD_ERROR) {
				return FIO_SD_ERROR;
			}
		}
	}

	/*Otherwise  we look for first any calibration file*/
	res = SDFS_scandir("0:/" CALIBR_DIR_NAME, &calibrations_list);
	if (res != SDFS_OK) { //Calibration directory is  not found
		f_mkdir("0:/" CALIBR_DIR_NAME);
		calibrations_list.num = 0;
	}
	if (calibrations_list.num != 0) { // Some calibration file exists

		strcpy(Current_state.calibration_name, calibrations_list.names[0]); //Current calibration is a first file in a calibration directory
		fiores = calibration_load(Current_state.calibration_name, cal); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
			return FIO_OK; //all is done
		} else {
			return fiores;
		}
	} else { //Directory is empty, so save default calibration file
		strcpy(Current_state.calibration_name, DEFAULT_CALIBR_NAME);
		strcpy(path, "0:/" CALIBR_DIR_NAME "/");
		strcat(path, DEFAULT_CALIBR_NAME);
		if (calibration_save(path, cal) == FIO_OK) {
			init_calibration_list();
		} else{
			return FIO_SD_ERROR;
		}
	}
	return FIO_OK;
}

FIO_status start_load_curve_list(void) {
	SDFS_status_type res;
	res = SDFS_scandir("0:/" CURVE_DIR_NAME, &curves_list);
	if (res != SDFS_OK) { //Preset directory is  not found
		f_mkdir("0:/" CURVE_DIR_NAME);
		curves_list.num = 0;
	}
    return FIO_OK;
}

static void init_preset_list(void){
	presets_list.active=0; //Position of an active item
	presets_list.num = 1; //Number of items in a file list
	presets_list.pos=0;  //Current position in a list
	strcpy(presets_list.names[0],DEFAULT_PRESET_NAME);
}

FIO_status start_load_preset(presetType* preset, calibrationType* cal){
	SDFS_status_type res;
	FIO_status fiores;
    char path[64];
	if (Current_state.preset_name[0]) { //name is not empty string
		fiores = preset_load(Current_state.preset_name, preset); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
			preset->Crc=presetCRC(preset);
			return FIO_OK; //all is done
		} else {
			if (fiores == FIO_SD_ERROR) {
				return FIO_SD_ERROR;
			}
		}
	}
	/*Otherwise  we look for first any preset file*/
	res = SDFS_scandir("0:/" PRESET_DIR_NAME, &presets_list);
	if (res != SDFS_OK) { //Preset directory is  not found
		f_mkdir("0:/" PRESET_DIR_NAME);
		presets_list.num = 0;
	}
	if (presets_list.num != 0) { // Some preset file exists
		strcpy(Current_state.preset_name, presets_list.names[0]); //Current preset is a first file in a preset directory
		fiores = preset_load(Current_state.preset_name, preset); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
			return FIO_OK; //all is done
		} else {
			return fiores;
		}
	} else { //Directory is empty
		strcpy(Current_state.preset_name, DEFAULT_PRESET_NAME);
		strcpy(path, "0:/" PRESET_DIR_NAME "/");
		strcat(path, DEFAULT_PRESET_NAME);
		fiores = preset_save(path, preset);
		if (fiores == FIO_OK) {
			init_preset_list();
		}else{
			return FIO_SD_ERROR;
		}
	}
    return FIO_OK;
}


/*Initialize  all calibration, preset and curve with default values*/
void set_defaults_all(presetType* preset, calibrationType* cal){
	sliders_calibr_set_defaults(cal->calibr); //Set default calibration
	curve_set_defaults(preset); //Default curve
	preset_set_defaults(preset); //Default preset
	sliders_set_defaults(preset->sliders, cal->calibr); //Set defaults sliders
	buttons_set_defaults(preset->buttons);//Set default buttons
	init_preset_list();
	init_calibration_list();
	/*Init structures for JSON files description*/
	init_json_calibr_attr(cal);
	init_json_preset_attr(preset);
	init_json_curve_attr(&(preset->Curve));
}
FIO_status start_load_all(presetType* preset, calibrationType* cal){

	if (SDFS_mount() != SDFS_OK) {
		return 0;
	}
	if (start_load_setting() != FIO_OK) {
		return 0;
	}
	if (start_load_calibration(cal) != FIO_OK) {
		return 0;
	}
	if (start_load_preset(preset, cal) != FIO_OK) {
		return 0;
	}
	if (start_load_curve_list() != FIO_OK) {
		return 0;
	}
	if (currentState_save() != FIO_OK) {
		return 0;
	}
	return 1;
}


