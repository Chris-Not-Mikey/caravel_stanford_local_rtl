#include <defs.h>
#include <stub.c>
#include "bitbang_functions.c"

void main(){
    unsigned int i, j, k;
    reg_wb_enable =1; // for enable writing to reg_debug_1 and reg_debug_2
    reg_debug_1  = 0x0;
    reg_debug_2  = 0x0;

    reg_mprj_io_37 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_36 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_35 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_34 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_33 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_32 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_31 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_30 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_29 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_28 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_27 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_26 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_25 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_24 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_23 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_22 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_21 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_20 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_19 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_18 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_17 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_16 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_9  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_8  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_7  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_6  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_5  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_4  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_3  = 0x1803 ;
    reg_mprj_io_2  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_1  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_0  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_0  = GPIO_MODE_MGMT_STD_OUTPUT;

    // bitbang
    // Configure all as output except reg_mprj_io_3
    clock_in_right_o_left_o_standard(0); // 18	and 19	
    clock_in_right_o_left_o_standard(0); // 17	and 20	
    clock_in_right_o_left_o_standard(0); // 16	and 21	
    clock_in_right_o_left_o_standard(0); // 15	and 22	
    clock_in_right_o_left_o_standard(0); // 14	and 23	
    clock_in_right_o_left_o_standard(0); // 13	and 24	
    clock_in_right_o_left_o_standard(0); // 12	and 25	
    clock_in_right_o_left_o_standard(0); // 11	and 26	
    clock_in_right_o_left_o_standard(0); // 10	and 27	
    clock_in_right_o_left_o_standard(0); // 9	and 28	
    clock_in_right_o_left_o_standard(0); // 8	and 29	
    clock_in_right_o_left_o_standard(0); // 7	and 30	
    clock_in_right_o_left_o_standard(0); // 6	and 31	
    clock_in_right_o_left_o_standard(0); // 5	and 32	
    clock_in_right_o_left_o_standard(0); // 4	and 33	
    clock_in_right_o_left_i_standard(0); // 3	and 34	
    clock_in_right_o_left_o_standard(0); // 2	and 35	
    clock_in_right_o_left_o_standard(0); // 1	and 36	
    clock_in_right_o_left_o_standard(0); // 0 and 37	
    load();
    reg_debug_1 = 0xFF; // finish configuration 
    reg_mprj_datal = 0x0;
    reg_mprj_datah = 0x0;
    i = 0x20;
	for (j = 0; j < 5; j++) {
        reg_mprj_datah = i;
        reg_debug_2 = 37-j;
        reg_mprj_datah = 0x00000000;
        reg_debug_2 = 0;
        i >>=1;
        i |= 0x20;
	}
	i = 0x80000000;
	for (j = 0; j < 32; j++) {
        reg_mprj_datah = 0x3f;
        reg_mprj_datal = i;
        reg_debug_2 = 32-j;
        reg_mprj_datah = 0x00;
        reg_mprj_datal = 0x00000000;
        reg_debug_2 = 0;
        i >>=1;
        i |= 0x80000000;
	}

}


