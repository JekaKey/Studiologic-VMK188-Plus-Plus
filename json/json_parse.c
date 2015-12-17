#include <string.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "jsmn.h"
#include "json_parse.h"
#include "log.h"


static int token_number=0;



parse_result_t tokens_parse(const char * buff, const jsmntok_t* tok,
		const json_attr_t* json_attr, const uint8_t level) {

	int j;
	uint8_t found;
	json_type j_type;
	static char st[32];

	if (level > 4){
		return parse_recursion_err; //Infinite recursion protection
	}
	if (level==0) //start parse from the beginning of new JSON
		token_number=0;
	if (tok[token_number].type != JSMN_OBJECT){
		return parse_not_object_err; //Start token must be object
	}
	uint16_t size = tok[token_number].size/2;

	token_number++;
	for (int i = 0; i < size; i ++) {
		found = 0;
		int len = tok[token_number].end - tok[token_number].start;
		memcpy(st, &buff[tok[token_number].start], len); //copy attribute name from buff
		st[len] = '\0'; //string ends with zero
		j = 0;
		while (json_attr[j].attribute[0]) {
			if (strcmp(json_attr[j].attribute, st) == 0) { //Attribute found
				found = 1;
				break;
			}
			j++;
		}
		if (!found){
			PRINTF("not found\n\r");
//			return parse_wrong_attr_err; //Wrong attribute
		}
		token_number++;
		j_type = json_attr[j].type;
		if (j_type == t_object) {
            if(tok[token_number].type!=JSMN_OBJECT){
            	return parse_wrong_type;
            }
			parse_result_t par_result = tokens_parse(buff, tok,
					json_attr[j].addr.object, level + 1);
			if (par_result != parse_ok)
				return par_result;
		} else {
			int len = tok[token_number].end - tok[token_number].start;
			memcpy(st, &buff[tok[token_number].start], len); //copy value from buff
			st[len] = '\0'; //string ends with zero
			if (j_type == t_string) {
				if (tok[token_number].type != JSMN_STRING) { //Check token type
					return parse_wrong_type;
				}
				strcpy(json_attr[j].addr.string, st); //copy text value to address
			} else {
	            if(tok[token_number].type!=JSMN_PRIMITIVE){
	            	return parse_wrong_type;
	            }
				unsigned long l = strtoul(st, NULL, 10);
				switch (j_type) {
				case t_uint8:
					*(json_attr[j].addr.uint8) = (uint8_t)l;
					break;
				case t_uint16:
					*(json_attr[j].addr.uint16) = (uint16_t)l;
					break;
				case t_uint32:
					*(json_attr[j].addr.uint32) = (uint32_t)l;
					break;
				case t_int8:
					*(json_attr[j].addr.int8) = (int8_t)l;
					break;
				default:
					break;
				}
			}
			token_number++;
		}
	}
	return parse_ok;
}
