#include <stdio.h>


#define BIT_A	0x00000001
#define BIT_B	0x00000002
#define BIT_V	0x00000004
#define BIT_G	0x00000008
#define BIT_D	0x00000010
#define BIT_E	0x00000020
#define BIT_ZH	0x00000040
#define BIT_Z	0x00000080
#define BIT_I	0x00000100
#define BIT_J	0x00000200
#define BIT_K	0x00000400
#define BIT_L	0x00000800
#define BIT_M	0x00001000
#define BIT_N	0x00002000
#define BIT_O	0x00004000
#define BIT_P	0x00008000
#define BIT_R	0x00010000
#define BIT_S	0x00020000
#define BIT_T	0x00040000
#define BIT_U	0x00080000
#define BIT_F	0x00100000
#define BIT_X	0x00200000
#define BIT_C	0x00400000
#define BIT_CH	0x00800000
#define BIT_SH	0x01000000
#define BIT_W	0x02000000
#define BIT_HZ	0x04000000
#define BIT_Y	0x08000000
#define BIT_SZ	0x10000000
#define BIT_JE	0x20000000
#define BIT_JU	0x40000000
#define BIT_JA	0x80000000

#define A_SIZE 32 /* russian alphabet size without yo letter */
#define CYR_UTF8_CAP_START	0xD090
#define CYR_UTF8_CAP_END	0xD0AF
#define CYR_UTF8_SMALL_START_1	0xD0B0
#define CYR_UTF8_SMALL_END_1	0xD0BF
#define CYR_UTF8_SMALL_START_2	0xD180
#define CYR_UTF8_SMALL_END_2	0xD18F

typedef __dict_node dict_node;

struct __dict_node {
	u32 size;
	u16 letter;
	u32 children;
	dict_node *child[A_SIZE];
	u32 *rule_idx[];
} dict_node;

u8 is_final(dict_node *node)
{
	return (node->size == sizeof(dict_node)) ? 0 : 1;
}

u16 to_upper(u16 let)
{
	if(let >= CYR_UTF8_CAP_START && let <= CYR_UTF8_CAP_END)
		return let;
	else if (let >= CYR_UTF8_SMALL_START_1 && let <= CYR_UTF8_SMALL_END_1)
		return let - 0x20;
	else if (let >= CYR_UTF8_SMALL_START_2 && let <= CYR_UTF8_SMALL_END_2)
		return let - 0xE0;
	else
		return 0;
}


u8 is_equal(u16 let1, u16 let2)
{
	return (to_upper(let1) == to_upper(let2)) ? 1 :  0;
}

u16 bit_to_letter(u32 bit)
{
	u16 i = 0;
	while(!(bit & 1)) {
		i++;
		bit >>= 1;
	}
	return i + CYR_UTF8_CAP_START;
}
	
u8 bit_to_index(u32 bit)
{
	u8 i = 0;
	while(!(bit & 1)) {
		i++;
		bit >>= 1;
	}
	return i;
}

u8 is_alpha(u16 let)
{
	return (to_upper(let) == 0) ? 0 : 1;
}


u8 get_num_rules(dict_node *node)
{
	return (node->size - sizeof(dict_node)) / sizeof(u32);
}
