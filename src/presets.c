#include <string.h>
#include "jsmn.h"
#include "json_parse.h"
#include "presets.h"
#include "sd_fatfs.h"

/*to remove*/
#include "leds.h"
#include "log.h"
/************/



presetType Preset;
currentStateType Current_state={{0},{0}};
calibrationType Calibration;

/*jsmn global variables*/
jsmntok_t tokens[TOKENS_NUM];
char js_buff[JSON_BUFF_SIZE];

extern char slider_names[][MAX_ATTR_SIZE];
extern char button_names[][MAX_ATTR_SIZE];

/***********************/

static FIO_status json_write_string(uint8_t level, const char* st, FIL* fff) { //use to write brackets into json
	char sss[20] = { 0 };
	memset(sss, ' ', level * JSON_TAB);
	strcat(sss, st);
	strcat(sss, "\r\n");
	if (f_puts(sss, fff) == FR_OK) {
		return FIO_OK;
	} else {
		return FIO_WRITE_ERROR;
	}
}

static FIO_status json_write_value(uint8_t level, const char* name,
		const char* value, uint8_t colon, FIL* fff) {
	char sss[64] = { 0 };
	memset(sss, ' ', level * JSON_TAB);
	strcat(sss, "\"");
	strcat(sss, name);
	strcat(sss, "\": \"");
	strcat(sss, value);
	if (colon != 0) {
		strcat(sss, "\",\r\n");
	} else {
		strcat(sss, "\"\r\n");
	}
	if (f_puts(sss, fff) == FR_OK) {
		return FIO_OK;
	} else {
		return FIO_WRITE_ERROR;
	}
}

static FIO_status json_write_object(uint8_t level, const char* name, FIL* fff) {
	char sss[64] = { 0 };
	memset(sss, ' ', level * JSON_TAB);
	strcat(sss, "\"");
	strcat(sss, name);
	strcat(sss, "\": {\r\n");
	if (f_puts(sss, fff) == FR_OK) {
		return FIO_OK;
	} else {
		return FIO_WRITE_ERROR;
	}
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


static FIO_status json_write_number(uint8_t level, const char* name,
		int number, uint8_t colon, FIL* fff) {
	char sss[64]={0};
	char lll[16];
	memset(sss, ' ', level * JSON_TAB);
	strcat(sss, "\"");
	strcat(sss, name);
	strcat(sss,"\": ");
	itoa(number,lll);
	strcat(sss,lll);
	if (colon) {
		strcat(sss,",\r\n");
	}else{
		strcat(sss,"\r\n");
	}
	if (f_puts(sss, fff)==FR_OK) {
		return FIO_OK;
	}else{
		return FIO_WRITE_ERROR;
	}
}


FIO_status currentState_save(void){
	FIL fff; // File handler
	if (SDFS_open(&fff, "0:/" SETTING_NAME, F_WR_CLEAR) != SDFS_OK){
		return FIO_FILE_CREATE_ERROR;
	}
	json_write_string(0,"{",&fff);
	json_write_value(1, ATTR_SET_CALIBR,Current_state.calibration_name,1,&fff);
	json_write_value(1, ATTR_SET_PRESET,Current_state.preset_name,0,&fff);
	json_write_string(0,"}",&fff);
	SDFS_close(&fff);
	return FIO_OK;
}

FIO_status calibration_save(const char* path, calibrationType* cal){
	FIL fff; // File handler
	int i;
	if (SDFS_open(&fff, path, F_WR_CLEAR) != SDFS_OK) {
        LED_light(7);
		return FIO_FILE_CREATE_ERROR;
	}
	json_write_string(0, "{", &fff);
	json_write_string(1, "\"" ATTR_CAL_SLIDERS "\":{", &fff);

	for (i = 0; i < SLIDERS_AMOUNT; i++) {
		json_write_object(2, slider_names[i],  &fff);
		json_write_number(3, ATTR_CAL_S_MIN, cal->calibr[i].min_in_value, 1, &fff);
		json_write_number(3, ATTR_CAL_S_MAX, cal->calibr[i].max_in_value, 1, &fff);
		json_write_number(3, ATTR_CAL_S_DELTA, cal->calibr[i].delta, 0, &fff);
		if (i < SLIDERS_AMOUNT-1){
    		json_write_string(2, "},", &fff);
		}else{
    		json_write_string(2, "}", &fff);
		}
	}
	json_write_string(1, "}", &fff);
	json_write_string(0, "}", &fff);
	SDFS_close(&fff);
	return FIO_OK;

}

FIO_status preset_save(const char* path, presetType* pr){
	FIL fff; // File handler
	int i;
	if (SDFS_open(&fff, path, F_WR_CLEAR) != SDFS_OK) {
        LED_light(7);
		return FIO_FILE_CREATE_ERROR;
	}
	json_write_string(0, "{", &fff);
	json_write_number(1, ATTR_CHANNEL, pr->MidiChannel, 1, &fff);
	json_write_string(1, "\"" ATTR_SPLIT "\":{", &fff);
	json_write_number(2, ATTR_SPLIT_KEY, pr->SplitKey, 1, &fff);
	json_write_number(2, ATTR_SPLIT_CHANNEL, pr->SplitChannel, 0, &fff);
	json_write_string(1, "},", &fff);
	json_write_number(1, ATTR_HIRES, pr->HighResEnable, 1, &fff);
	json_write_number(1, ATTR_ANALOGMIDI, pr->AnalogMidiEnable, 1, &fff);
	json_write_value(1, ATTR_CURVE,pr->CurveFileName,1,&fff);
	json_write_string(1, "\"" ATTR_SLIDERS "\":{", &fff);
	for (i = 0; i < SLIDERS_AMOUNT; i++) {
		json_write_object(2, slider_names[i],  &fff);
		json_write_number(3, ATTR_S_ACTIVE, pr->sliders[i].active, 1, &fff);
		json_write_number(3, ATTR_S_REVERSE, pr->sliders[i].reverse, 1, &fff);
		json_write_number(3, ATTR_S_CHANNEL, pr->sliders[i].channel, 1, &fff);
		json_write_number(3, ATTR_S_EVENT, pr->sliders[i].event, 1, &fff);
		json_write_number(3, ATTR_S_MIN, pr->sliders[i].min_out_value, 1, &fff);
		json_write_number(3, ATTR_S_MAX, pr->sliders[i].max_out_value, 0, &fff);
		if (i<SLIDERS_AMOUNT-1){
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
		json_write_number(3, ATTR_B_TOGGLE, pr->buttons[i].toggle, 1, &fff);
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
	SDFS_close(&fff);
	return FIO_OK;
}

FIO_status curve_save(const char* path, curve_points_type* curve){
	FIL fff; // File handler
	if (SDFS_open(&fff, path, F_WR_CLEAR) != SDFS_OK) {
        LED_light(7);
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
	SDFS_close(&fff);
	return FIO_OK;
}

/***Structures and arrays describing expected JSON attributes, objects and values***/

static json_attr_t setting_attr[] = {
    {ATTR_SET_CALIBR,   t_string, .addr.string = Current_state.calibration_name},
    {ATTR_SET_PRESET,   t_string, .addr.string = Current_state.preset_name},
    {"",},
};

static json_attr_t split_attr[]={
		{ATTR_SPLIT_KEY, t_uint8,},
		{ATTR_SPLIT_CHANNEL, t_uint8,},
		{"",},
};

static json_attr_t sliders_param_attr[SLIDERS_AMOUNT+1][7];
static json_attr_t buttons_param_attr[BUTTONS_AMOUNT+1][8];
static json_attr_t sliders_attr[SLIDERS_AMOUNT+1];
static json_attr_t buttons_attr[BUTTONS_AMOUNT+1];

static json_attr_t preset_attr[16] = {
		{ATTR_CHANNEL, t_uint8,},
		{ATTR_SPLIT,t_object, .addr.object = split_attr},
		{ATTR_HIRES, t_uint8,},
		{ATTR_ANALOGMIDI, t_uint8,},
		{ATTR_CURVE, t_string,},
		{ATTR_SLIDERS, t_object,.addr.object=sliders_attr},
		{ATTR_BUTTONS, t_object,.addr.object=buttons_attr},
		{"",},
};

static json_attr_t calibr_sliders_attr[SLIDERS_AMOUNT+1];
static json_attr_t calibr_sliders_param_attr[SLIDERS_AMOUNT+1][4];
static json_attr_t calibr_attr[]={
		{ATTR_CAL_SLIDERS, t_object, .addr.object=calibr_sliders_attr},
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

/* Functions makes links between JSON structures and variables*/
/*Modify some structures fields and assign addresses of variables to structures fields*/
/************************Not good looking :-( *************************/
static void init_json_preset_attr(presetType *preset) {
	preset_attr[0].addr.uint8 = &(preset->MidiChannel);
	preset_attr[2].addr.uint8 = &(preset->HighResEnable);
	preset_attr[3].addr.uint8 = &(preset->AnalogMidiEnable);
	preset_attr[4].addr.string = preset->CurveFileName;

	split_attr[0].addr.uint8 = &(preset->SplitKey);
	split_attr[1].addr.uint8 = &(preset->SplitChannel);

	sliders_attr[SLIDERS_AMOUNT].attribute[0] =0;
	/*Assign sliders addresses and attributes*/
	for (int i = 0; i < SLIDERS_AMOUNT; i++) {
		strcpy(sliders_attr[i].attribute, slider_names[i]);
		sliders_attr[i].type = t_object;
		sliders_attr[i].addr.object = sliders_param_attr[i];
		strcpy(sliders_param_attr[i][0].attribute, ATTR_S_ACTIVE);
		sliders_param_attr[i][0].addr.uint8 = &(preset->sliders[i].active);
		strcpy(sliders_param_attr[i][1].attribute, ATTR_S_REVERSE);
		sliders_param_attr[i][1].addr.uint8 = &(preset->sliders[i].reverse);
		strcpy(sliders_param_attr[i][2].attribute, ATTR_S_CHANNEL);
		sliders_param_attr[i][2].addr.uint8 = &(preset->sliders[i].channel);
		strcpy(sliders_param_attr[i][3].attribute, ATTR_S_EVENT);
		sliders_param_attr[i][3].addr.uint8 = &(preset->sliders[i].event);
		strcpy(sliders_param_attr[i][4].attribute, ATTR_S_MIN);
		sliders_param_attr[i][4].addr.uint8 = &(preset->sliders[i].min_out_value);
		strcpy(sliders_param_attr[i][5].attribute, ATTR_S_MAX);
		sliders_param_attr[i][5].addr.uint8 = &(preset->sliders[i].max_out_value);
		for (int j = 0; j < 6; j++) {
			sliders_param_attr[i][j].type = t_uint8;
		}
		sliders_param_attr[i][6].attribute[0]=0;
	}
	sliders_attr[SLIDERS_AMOUNT].attribute[0]=0;
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
		strcpy(buttons_param_attr[i][3].attribute, ATTR_B_TOGGLE);
		buttons_param_attr[i][3].addr.uint8 = &(preset->buttons[i].toggle);
		strcpy(buttons_param_attr[i][4].attribute, ATTR_B_EVENT);
		buttons_param_attr[i][4].addr.uint8 = &(preset->buttons[i].event);
		strcpy(buttons_param_attr[i][5].attribute, ATTR_B_ON);
		buttons_param_attr[i][5].addr.uint8 = &(preset->buttons[i].on);
		strcpy(buttons_param_attr[i][6].attribute, ATTR_B_OFF);
		buttons_param_attr[i][6].addr.uint8 = &(preset->buttons[i].off);
		for (int j = 0; j < 7; j++) {
			buttons_param_attr[i][j].type = t_uint8;
		}
		buttons_param_attr[i][7].attribute[0]=0;
	}
	buttons_attr[BUTTONS_AMOUNT].attribute[0]=0;
}
	/*Assign calibration addresses and attributes*/
static void init_json_calibr_attr(calibrationType *cal) {
	for (int i = 0; i < SLIDERS_AMOUNT; i++){
		strcpy(calibr_sliders_attr[i].attribute, slider_names[i]);
		calibr_sliders_attr[i].type = t_object;
		calibr_sliders_attr[i].addr.object = calibr_sliders_param_attr[i];
		strcpy(calibr_sliders_param_attr[i][0].attribute, ATTR_CAL_S_MIN);
		sliders_param_attr[i][0].addr.uint16 = &(cal->calibr[i].min_in_value);
		strcpy(calibr_sliders_param_attr[i][1].attribute, ATTR_CAL_S_MAX);
		sliders_param_attr[i][1].addr.uint16 = &(cal->calibr[i].max_in_value);
		strcpy(calibr_sliders_param_attr[i][2].attribute, ATTR_CAL_S_DELTA);
		sliders_param_attr[i][2].addr.uint16 = &(cal->calibr[i].delta);
		for (int j = 0; j < 3; j++) {
			calibr_sliders_param_attr[i][j].type = t_uint16;
		}
		calibr_sliders_param_attr[i][3].attribute[0]=0;
	}
	calibr_sliders_attr[SLIDERS_AMOUNT].attribute[0]=0;
}
	/*Assign curve addresses*/
static void init_json_curve_attr(presetType *preset) {
	curve_attr[0].addr.uint32=&(preset->Curve.xw1);
	curve_attr[1].addr.uint32=&(preset->Curve.yw1);
	curve_attr[2].addr.uint32=&(preset->Curve.xw2);
	curve_attr[3].addr.uint32=&(preset->Curve.yw2);
	curve_attr[4].addr.uint32=&(preset->Curve.xw3);
	curve_attr[5].addr.uint32=&(preset->Curve.yw3);
	curve_attr[6].addr.uint32=&(preset->Curve.xb1);
	curve_attr[7].addr.uint32=&(preset->Curve.yb1);
	curve_attr[8].addr.uint32=&(preset->Curve.xb2);
	curve_attr[9].addr.uint32=&(preset->Curve.yb2);
	curve_attr[10].addr.uint32=&(preset->Curve.xb3);
	curve_attr[11].addr.uint32=&(preset->Curve.yb3);
}

/*******************************************************/

/*Load setting file start.cfg with current calibration file name and preset file name*/




FIO_status load_JSON(char* path, char *js_buff,  jsmntok_t *tokens, json_attr_t *json_attr){
	FIL fff; // File handler
	jsmn_parser parser;
	UINT size;
	PRINTF("Load_JSON : start, path:%s\n\r",path);
	SDFS_status_type res = SDFS_open(&fff, path, F_RD);
	if (res != SDFS_OK)  //Calibration not file exist
		return FIO_FILE_NOT_FOUND;
	FRESULT f_res=f_read(&fff, js_buff, JSON_BUFF_SIZE, &size);
	PRINTF("Load_JSON : read result: %d\n\r",f_res);
	if (f_res!=FR_OK)
			return FIO_READ_ERROR;
	js_buff[size] = 0;
	jsmn_init(&parser);
	jsmnerr_t result = jsmn_parse(&parser, js_buff, size, tokens, TOKENS_NUM);
    if (result<0){
    	return FIO_JSON_FORMAT_ERR;
    }
    parse_result_t parse_result = tokens_parse(js_buff, tokens, json_attr, 0);
	if (parse_result != parse_ok)
		return FIO_JSON_DATA_ERR;
    return FIO_OK;
}

FIO_status currentState_load(void) {
     	FIO_status status=load_JSON("0:/" SETTING_NAME, js_buff, tokens, setting_attr );
	return status;
}


FIO_status start_load_setting(void){
	PRINTF("Presets start_load_setting SDFS_mount finished Ok: \n\r");
	if (currentState_load() == FIO_OK) { //Current state loaded
		PRINTF("Presets start_load_setting: Current state is loaded\n\r");
		return FIO_OK;
	} else { 		//Current state file not exist
		Current_state.calibration_name[0] = 0;
		Current_state.preset_name[0] = 0;
		return FIO_FILE_NOT_FOUND;
	}
}

/*3 functions loading parameters from json files to structure object*/
/*If some parameters do not exist in JSON they will not change*/

FIO_status calibration_load(char* path, calibrationType* cal ){
    	init_json_calibr_attr(cal);
     	FIO_status status=load_JSON(path, js_buff, tokens, calibr_attr);
        return status;
}

FIO_status curve_load(char* path, presetType* pr) {
	init_json_curve_attr(pr);
	FIO_status status=load_JSON(path, js_buff, tokens, curve_attr);
    return status;
}


FIO_status preset_load(char* path, presetType* pr) {
	init_json_preset_attr(pr);
	FIO_status status=load_JSON(path, js_buff, tokens, preset_attr);
    return status;
}

static void preset_set_defaults(presetType* pr){
	pr->MidiChannel=0;
	pr->HighResEnable=0;
	pr->SplitKey=0;
	pr->SplitChannel=0;
	pr->AnalogMidiEnable=0;
}

/*Default curve reproduces old VMK188+ behavior*/
static void curve_set_defaults(presetType* pr){
	pr->Curve.xw1=3600;
	pr->Curve.yw1=125*0x80;
	pr->Curve.xw2=20000;
	pr->Curve.yw2=31*0x80;
	pr->Curve.xw3=101400;
	pr->Curve.yw3=1*0x80;
	pr->Curve.xb1=3000;
	pr->Curve.yb1=118*0x80;
	pr->Curve.xb2=20600;
	pr->Curve.yb2=20*0x80;
	pr->Curve.xb3=75000;
	pr->Curve.yb3=1*0x80;
	calculate_velocity_formula(&pr->Curve);
}





FIO_status start_load_calibration(calibrationType* cal){
	file_list_type fl;
	SDFS_status_type res;
	FIO_status fiores;
	static char path[128] = "0:/" CALIBR_DIR_NAME "/";

	if (Current_state.calibration_name[0]) { //name is not empty string
		strcat(path, Current_state.calibration_name);
		fiores = calibration_load(path, cal); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
			PRINTF("Calibration was loaded successfully\n\r");
			return FIO_OK; //all is done
		} else {
			if (fiores == FIO_SD_ERROR) {
				return FIO_SD_ERROR;
			}
		}
	}

	/*Otherwise  we look for first any calibration file*/
	res = SDFS_scandir("0:/" CALIBR_DIR_NAME, &fl);
	if (res != SDFS_OK) { //Calibration directory is  not found
		f_mkdir("0:/" CALIBR_DIR_NAME);
		fl.num = 0;
	}
	if (fl.num != 0) { // Some calibration file exists
		strcpy(Current_state.calibration_name, fl.names[0]); //Current calibration is a first file in a calibration directory
		strcat(path, Current_state.calibration_name);
		fiores = calibration_load(path, cal); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
			return FIO_OK; //all is done
		} else {
			return fiores;
		}
	} else { //Directory is empty, so save default calibration file
		strcpy(Current_state.calibration_name, DEFAULT_CALIBR_NAME);
		strcat(path, Current_state.calibration_name);
		if (calibration_save(path, cal) != FIO_OK) {
			PRINTF("Calibration save ERROR\n\r");
			return FIO_SD_ERROR;
		}
		return FIO_OK;
	}
}

FIO_status start_load_curve(presetType* preset) {
	file_list_type fl;
	SDFS_status_type res;
	FIO_status fiores;
	static char path[128] = "0:/" CURVE_DIR_NAME "/";
	if (preset->CurveFileName[0]) { //name is not empty string
		strcat(path, preset->CurveFileName); //add file name to path
		fiores = curve_load(path, preset); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
//			PRINTF("Curve was loaded successfully\n\r");
			calculate_velocity_formula(&preset->Curve);
			return FIO_OK; //all is done
		} else {
			if (fiores == FIO_SD_ERROR) {
				return FIO_SD_ERROR;
			}
		}
	}
	/*Otherwise  we look for first any preset file*/
	res = SDFS_scandir("0:/" CURVE_DIR_NAME, &fl);
	if (res != SDFS_OK) { //Preset directory is  not found
		f_mkdir("0:/" CURVE_DIR_NAME);
		fl.num = 0;
	}
	if (fl.num != 0) { // Some curve file exists
		strcpy(preset->CurveFileName, fl.names[0]); //Current curve is a first file in a preset directory
		strcat(path, preset->CurveFileName);
		fiores = curve_load(path, preset); //Load curve from file.
		calculate_velocity_formula(&preset->Curve); //calculate parameters for velocity formula
		if (fiores == FIO_OK) { //loading was successful
			return FIO_OK; //all is done
		} else {
			return fiores;
		}
	} else { //Directory is empty
		strcpy(preset->CurveFileName, DEFAULT_CURVE_NAME);
		strcat(path, preset->CurveFileName);
		if (curve_save(path, &preset->Curve) != FIO_OK) {
			return FIO_SD_ERROR;
		}
		return FIO_OK;
	}
    return FIO_OK;
}

FIO_status start_load_preset(presetType* preset, calibrationType* cal){
	file_list_type fl;
	SDFS_status_type res;
	FIO_status fiores;
	static char path[128]="0:/" PRESET_DIR_NAME "/";

	if (Current_state.preset_name[0]) { //name is not empty string
		strcat(path,Current_state.preset_name);//add file name to path
		fiores = preset_load(path, preset); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
			PRINTF("Preset was loaded successfully\n\r");
			return FIO_OK; //all is done
		} else {
			if (fiores == FIO_SD_ERROR) {
				return FIO_SD_ERROR;
			}
		}
	}
	/*Otherwise  we look for first any preset file*/
	res = SDFS_scandir("0:/" PRESET_DIR_NAME, &fl);
	if (res != SDFS_OK) { //Preset directory is  not found
		f_mkdir("0:/" PRESET_DIR_NAME);
		fl.num = 0;
	}
	if (fl.num != 0) { // Some preset file exists
		strcpy(Current_state.preset_name, fl.names[0]); //Current preset is a first file in a preset directory
		strcat(path, Current_state.preset_name);
		fiores = preset_load(path, preset); //Load calibration from file.
		if (fiores == FIO_OK) { //loading was successful
			return FIO_OK; //all is done
		} else {
			return fiores;
		}
	} else { //Directory is empty
		strcpy(Current_state.preset_name, DEFAULT_PRESET_NAME);
		strcat(path, Current_state.preset_name);
		if (preset_save(path, preset) != FIO_OK) {
			PRINTF("Presets start_load_preset: preset no saved");
			return FIO_SD_ERROR;
		}
		return FIO_OK;
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
	/*Init structures for JSON files description*/
	init_json_calibr_attr(cal);
	init_json_preset_attr(preset);
	init_json_curve_attr(preset);
}

FIO_status start_load_all(presetType* preset, calibrationType* cal){
	if (SDFS_mount() != SDFS_OK) {
		PRINTF("MOUNT ERROR\r\n");
		return FIO_SD_ERROR;
	}

	if (start_load_setting() == FIO_SD_ERROR) {
		return FIO_SD_ERROR;
	}
	if (start_load_calibration(cal) == FIO_SD_ERROR) {
		return FIO_SD_ERROR;
	}
	if (start_load_preset(preset, cal) == FIO_SD_ERROR) {
		return FIO_SD_ERROR;
	}
	if (start_load_curve(preset) == FIO_SD_ERROR) {
		return FIO_SD_ERROR;
	}
	if (currentState_save() != FIO_OK) {
		return FIO_SD_ERROR;
	}
	return FIO_OK;
}


