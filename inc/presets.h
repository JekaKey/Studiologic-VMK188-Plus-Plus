#ifndef PRESETS__H
#define PRESETS__H

#include "stm32f4xx.h"
#include "controls.h"
#include "velocity.h"
#include "sd_fatfs.h"

#define CALIBR_EXT ".cal"
#define PRESET_EXT ".pst"
#define CURVE_EXT ".crv"
#define DEFAULT_CALIBR_NAME  "default" CALIBR_EXT
#define DEFAULT_PRESET_NAME  "default" PRESET_EXT
#define DEFAULT_CURVE_NAME "default" CURVE_EXT
#define SETTING_NAME "start.cfg"

#define CALIBR_DIR_NAME "CALIBRATION"
#define PRESET_DIR_NAME "PRESET"
#define CURVE_DIR_NAME "CURVE"

#define JSON_TAB 1 //size of tabulation in generated JSON files

#define TOKENS_NUM 1000 //Max number of tokens for JSMN parser
#define JSON_BUFF_SIZE 8000 //Size of JSON buffer in bytes


#define MAX_ATTR_SIZE 24 //Size of strings for json attributes


/***The following defines contains names of attributes in JSON files***/
#define ATTR_SET_PRESET "preset"
#define ATTR_SET_CALIBR "calibration"

#define ATTR_CAL_SLIDERS "sliders"
#define ATTR_CAL_S_MIN "min"
#define ATTR_CAL_S_MAX "max"
#define ATTR_CAL_S_DELTA "delta"

#define ATTR_CURVE_XW1 "xw1"
#define ATTR_CURVE_YW1 "yw1"
#define ATTR_CURVE_XW2 "xw2"
#define ATTR_CURVE_YW2 "yw2"
#define ATTR_CURVE_XW3 "xw3"
#define ATTR_CURVE_YW3 "yw3"
#define ATTR_CURVE_XB1 "xb1"
#define ATTR_CURVE_YB1 "yb1"
#define ATTR_CURVE_XB2 "xb2"
#define ATTR_CURVE_YB2 "yb2"
#define ATTR_CURVE_XB3 "xb3"
#define ATTR_CURVE_YB3 "yb3"


#define ATTR_CHANNEL "channel"
#define ATTR_SPLIT "split"
#define ATTR_SPLIT_CHANNEL "channel"
#define ATTR_SPLIT_KEY "key"
#define ATTR_SPLIT_OCTAVE "octave"
#define ATTR_CURVE "curve"
#define ATTR_HIRES "hires"
#define ATTR_ANALOGMIDI "analogmidi"
#define ATTR_TRANSPOSE "transpose"
#define ATTR_OCTAVE "octave"

#define ATTR_SLIDERS "sliders"
#define ATTR_PEDALS "pedals"
#define ATTR_KNOBS "knobs"

#define ATTR_S1 "Slider 1"
#define ATTR_S2 "Slider 2"
#define ATTR_S3 "Slider 3"
#define ATTR_S4 "Slider 4"
#define ATTR_S5 "Slider 5"
#define ATTR_S6 "Slider 6"
#define ATTR_S7 "Slider 7"
#define ATTR_S8 "Slider 8"
#define ATTR_S9 "Slider 9"
#define ATTR_R1 "Knob 1"
#define ATTR_R2 "Knob 2"
#define ATTR_R3 "Knob 3"
#define ATTR_R4 "Knob 4"
#define ATTR_R5 "Knob 5"
#define ATTR_R6 "Knob 6"
#define ATTR_R7 "Knob 7"
#define ATTR_R8 "Knob 8"
#define ATTR_AT "Aftertouch"
#define ATTR_PI "Pitch"
#define ATTR_MO "Modulation"
#define ATTR_P1 "Pedal 1"
#define ATTR_P2 "Pedal 2"
#define ATTR_P3 "Pedal 3"
#define ATTR_EY "Empty"

#define ATTR_S_ACTIVE "active"
#define ATTR_S_REVERSE "reverse"
#define ATTR_S_BINARY "binary"
#define ATTR_S_CHANNEL "channel"
#define ATTR_S_EVENT "event"
#define ATTR_S_MIN "min"
#define ATTR_S_MAX "max"

#define ATTR_BUTTONS "buttons"
#define ATTR_B1 "button1"
#define ATTR_B2 "button2"
#define ATTR_B3 "button3"
#define ATTR_B4 "button4"
#define ATTR_B5 "button5"
#define ATTR_B6 "button6"
#define ATTR_B7 "button7"
#define ATTR_B8 "button8"
#define ATTR_BLF "buttonleft"
#define ATTR_BRT "buttonright"
#define ATTR_BRC "buttonrecord"
#define ATTR_BST "buttonstop"
#define ATTR_BPL "buttonplay"

#define ATTR_B_ACTIVE "active"
#define ATTR_B_TYPE "type"
#define ATTR_B_CHANNEL "channel"
#define ATTR_B_EVENT "event"
#define ATTR_B_ON "on"
#define ATTR_B_OFF "off"

#define OCTAVE_SHIFT_MAX 3

/********************************/

typedef enum  {FIO_OK=0, FIO_SD_ERROR, FIO_FILE_NOT_FOUND,FIO_FILE_CREATE_ERROR,FIO_GETFREE_ERR,FIO_MOUNT_ERR,FIO_WRITE_ERROR,FIO_READ_ERROR,
	FIO_JSON_FORMAT_ERR, FIO_JSON_DATA_ERR, FIO_RENAME_ERROR, FIO_DELETE_ERROR, FIO_FILE_CLOSE_ERROR} FIO_status;
 //To keep information about Sliders calibration and so on


typedef struct {//Keeps names of current presets and calibrations.
	char preset_name[MAX_FNAME-FEXT_SIZE];
	char calibration_name[MAX_FNAME-FEXT_SIZE];
} currentStateType;

typedef struct{
	uint8_t Id; //
	Calibration_slider_type calibr[SLIDERS_AMOUNT];
}calibrationType;

typedef struct {
	uint8_t MidiChannel; //1-16
	uint8_t SplitKey;//0 - NoSplit, 1-87 - Split
	uint8_t SplitChannel; //1-16, MIDI Channel for a left part of a split keyboard
	int8_t SplitOctShift; //-3..3
	int8_t Transpose; //-11..11
	int8_t OctaveShift; //-3..3
	uint8_t HighResEnable; //bool
	uint8_t AnalogMidiEnable; //bool
	curve_points_type Curve;//curve nodes for B&W keys
	Slider_type sliders[SLIDERS_AMOUNT];
	Button_type buttons[BUTTONS_AMOUNT];
	uint8_t Changed;
} presetType;


FIO_status start_load_setting(void);
FIO_status start_load_calibration(calibrationType* cal);
FIO_status start_load_preset(presetType* preset, calibrationType* cal);
void set_defaults_all(presetType* preset, calibrationType* cal);
FIO_status start_load_all(presetType* preset, calibrationType* cal);

FIO_status currentState_load(void);
FIO_status currentState_save(void);

FIO_status calibration_load(char* name, calibrationType* cal );
FIO_status calibration_save(const char* path, calibrationType* cal);
FIO_status calibration_rename(file_list_type *pr_list, char *new_name);
FIO_status calibration_delete(file_list_type *pr_list);

FIO_status preset_load(char* name, presetType* preset);
FIO_status preset_rename(file_list_type *pr_list, char *new_name);
FIO_status preset_delete(file_list_type *pr_list);
FIO_status preset_save(const char* name, presetType* preset );
FIO_status preset_save_current(void);

FIO_status curve_load(char* name, curve_points_type  *curve);
FIO_status curve_delete(file_list_type *cur_list);
FIO_status curve_rename(file_list_type *cur_list, char *new_name);
FIO_status curve_save(const char* path, curve_points_type* curve);

#endif //PRESETS__H
