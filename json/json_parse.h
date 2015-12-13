#include "stm32f4xx.h"

/** some types for work with json using jsmn lib **/

typedef enum {
	t_int8, t_uint8, t_uint16, t_uint32, t_string, t_object
} json_type;

typedef enum {parse_ok, parse_recursion_err, parse_not_object_err, parse_wrong_attr_err, parse_wrong_number_err, parse_wrong_type}
    parse_result_t;

struct json_attr_struct{
	char attribute[16];
	json_type type;
	union {
		int8_t *int8;
		uint8_t *uint8;
		uint16_t *uint16;
		uint32_t *uint32;
		char *string;
		struct json_attr_struct *object;
	} addr;
};

typedef struct json_attr_struct json_attr_t;

parse_result_t tokens_parse(const char * buff, const jsmntok_t* tok,
		const json_attr_t* json_attr, const uint8_t level);
