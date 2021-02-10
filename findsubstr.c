#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint16_t strlen_(const unsigned char *string);
int find_substr(const unsigned char *string, const unsigned char *template);
void mktable(const unsigned char *str, uint16_t *table);


uint16_t strlen_(const unsigned char *string)
{
	unsigned char *strend = (unsigned char *)string;
	while (*strend != '\0')
		strend++;
	return (strend - string);
}

int find_substr(const unsigned char *string, const unsigned char *template)
{
	uint16_t template_len = strlen_(template);
	unsigned char *rbegin_template = (unsigned char *)template + template_len - 1;
	uint16_t template_table[256];
	for (uint16_t i = 0; i < 256; ++i)
		template_table[i] = template_len;
	uint16_t string_len = strlen_(string);
	mktable(template, template_table);
	int16_t temp_pos = template_len - 1;
	int16_t str_pos = temp_pos;
	while (temp_pos > 0) 
	{
		if (template[temp_pos] == string[str_pos])
		{
			temp_pos--;
			str_pos--;
		} else
		{
			str_pos += template_table[string[str_pos]];
			temp_pos = template_len - 1;
		}
		if (str_pos >= string_len)
			return -1;

	}
				
	return str_pos;
}


void mktable(const unsigned char *str, uint16_t *table)
{
	uint16_t length = strlen_(str);
	for (int i = length - 2; i >= 0; --i) 
	{
		uint16_t char_index = (uint16_t)str[i];
		if (table[char_index] > i)
			table[char_index] = length - 1 - i;
	}
}


int main(int argc, char** argv)
{
	if (argc < 3) {
		printf("Usage:%s <string> <substring>\n", argv[0]);
		return 1;
	}
	int res = find_substr(argv[1], argv[2]);
	if (res >= 0)
		printf("Substring position is %d\n", res);
	else
		printf("Substring is not found\n");
	return 0;
}
