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

//	PRINTF("Token_parse started, Level=%d \n\r",level);
	if (level > 4){
//		PRINTF("Parse recursion error, Level=%d \n\r",level);
		return parse_recursion_err; //Infinite recursion protection
	}
	if (level==0) //start parse from the beginning of new JSON
		token_number=0;
	if (tok[token_number].type != JSMN_OBJECT){
		return parse_not_object_err; //Start token must be object
	}
	uint16_t size = tok[token_number].size/2;
//	PRINTF("Token size :%d \n\r",size);

	token_number++;
	for (int i = 0; i < size; i ++) {
//		PRINTF("Cycle i=%d \n\r",i);
		found = 0;
		int len = tok[token_number].end - tok[token_number].start;
		memcpy(st, &buff[tok[token_number].start], len); //copy attribute name from buff
		st[len] = '\0'; //string ends with zero
//		PRINTF("Token_parse: Token number: %d,  current token:  %s \n\r",token_number, st);
		j = 0;
		while (json_attr[j].attribute[0]) {
//			PRINTF("Token parse: j=%d, Attr: %s \r\n",j, json_attr[j].attribute);
			if (strcmp(json_attr[j].attribute, st) == 0) { //Attribute found
//				PRINTF("Attribute found :%s j= %d \n\r",st,j);
				found = 1;
				break;
			}
			j++;
		}
		if (!found){
//			PRINTF("Attribute not found: %s \n\r",st);
			return parse_wrong_attr_err; //Wrong attribute
		}
		token_number++;
		j_type = json_attr[j].type;
		PRINTF("Json type :%d, token type : %d \n\r",j_type, tok[token_number].type);
		if (j_type == t_object) {
			PRINTF("Json type=t_object :%d \n\r",j_type);
            if(tok[token_number].type!=JSMN_OBJECT){
            	return parse_wrong_type;
            }
			parse_result_t par_result = tokens_parse(buff, tok,
					json_attr[j].addr.object, level + 1);
			PRINTF("Return to level %d, parse_result= %d\n\r", level, par_result);
			if (par_result != parse_ok)
				return par_result;
		} else {
			int len = tok[token_number].end - tok[token_number].start;
			memcpy(st, &buff[tok[token_number].start], len); //copy value from buff
			st[len] = '\0'; //string ends with zero
			PRINTF("Not object string :%s \n\r",st);
			if (j_type == t_string) {
				if (tok[token_number].type != JSMN_STRING) { //Check token type
					return parse_wrong_type;
				}
				PRINTF("J_type=string :%d \n\r",j_type);
				strcpy(json_attr[j].addr.string, st); //copy text value to address
			} else {
	            if(tok[token_number].type!=JSMN_PRIMITIVE){
	            	return parse_wrong_type;
	            }
				PRINTF("J_type=number :%d \n\r",j_type);
				unsigned long l = strtoul(st, NULL, 10);
				PRINTF("Digital value :%u \n\r",l);
//				if (end_ptr){ //Wrong format of a number was read
//					PRINTF("End_ptr : %d \n\r",end_ptr);
//					return parse_wrong_number_err;
//				}
				switch (j_type) {
				case t_uint8: {
					*(json_attr[j].addr.uint8)=(uint8_t)l;
					break;
				}
				case t_uint16: {
					*(json_attr[j].addr.uint16)=(uint16_t)l;
					break;
				}
				case t_uint32: {
					*(json_attr[j].addr.uint32)=(uint32_t)l;
					break;
				}
				case t_integer: {
					*(json_attr[j].addr.integer)=(int)l;
					break;
				}
				default:
					break;
				}
			}
			token_number++;
		}
	}
//	PRINTF("Finished OK, level=%d\n\r",level);
	return parse_ok;
}
