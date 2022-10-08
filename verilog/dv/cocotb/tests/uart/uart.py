from curses import baudrate
import random
import cocotb
from cocotb.triggers import FallingEdge,RisingEdge,ClockCycles,Timer
import cocotb.log
from cpu import RiskV
from defsParser import Regs
from cocotb.result import TestSuccess
from tests.common_functions.test_functions import *
from tests.bitbang.bitbang_functions import *
from caravel import GPIO_MODE


bit_time_ns = 0
reg = Regs()


@cocotb.test()
@repot_test
async def uart_tx(dut):
    caravelEnv,clock = await test_configure(dut,timeout_cycles=375862)
    cpu = RiskV(dut)
    cpu.cpu_force_reset()
    cpu.cpu_release_reset()
    cocotb.log.info(f"[TEST] Start uart test")  
    expected_msg = "Monitor: Test UART (RTL) passed"
    # calculate bit time
    clk = clock.period/1000
    global bit_time_ns
    bit_time_ns = round(10**5 * clk / (96))
    # wait for start of sending
    await wait_reg1(cpu,caravelEnv,0XAA) 
        
    cocotb.log.info (f"[TEST] start receiving from uart")
    counter =0
    data_out =''
    while True:
        if counter %8 == 0: 
            if counter != 0:
                data_out = data_out+chr(int(char,2))
                cocotb.log.info (f"[TEST] msg is:'{data_out}' expected '{expected_msg}'")
            if data_out == expected_msg:
                cocotb.log.info (f"[TEST] Pass recieve the full expected msg '{data_out}'")
                break
            await start_of_tx(caravelEnv)
            char  = ''
        # if temp != caravelEnv.monitor_gpio((6,6))
        char = caravelEnv.monitor_gpio((6,6)).binstr + char
        cocotb.log.debug (f"[TEST] bit[{counter}] = {caravelEnv.monitor_gpio((6,6))} data out = {char} ")
        await Timer(bit_time_ns, units='ns')  
        counter +=1
    
async def start_of_tx(caravelEnv):
    while (True): # wait for the start of the transimission it 1 then 0
        if (caravelEnv.monitor_gpio((6,6)).integer == 0):
            break
        await Timer(bit_time_ns, units='ns')
    await Timer(bit_time_ns, units='ns')


@cocotb.test()
@repot_test
async def uart_rx(dut):
    caravelEnv,clock = await test_configure(dut,timeout_cycles=95844)
    cpu = RiskV(dut)
    cpu.cpu_force_reset()
    cpu.cpu_release_reset()
    cocotb.log.info(f"[TEST] Start uart test")  
    caravelEnv.drive_gpio_in((5,5),1)
    # calculate bit time
    clk = clock.period/1000
    global bit_time_ns
    bit_time_ns = round(10**5 * clk / (96))
    print (clk)
    # send first char
    await wait_reg1(cpu,caravelEnv,0XAA)  
    await uart_send_char(caravelEnv,"B")
    await uart_check_char_recieved(caravelEnv,cpu)
    # send second char  
    await wait_reg1(cpu,caravelEnv,0XBB)  
    await uart_send_char(caravelEnv,"M")
    await uart_check_char_recieved(caravelEnv,cpu)
    # send third char  
    await wait_reg1(cpu,caravelEnv,0XCC)  
    await uart_send_char(caravelEnv,"A")
    await uart_check_char_recieved(caravelEnv,cpu)

   
        
async def uart_send_char(caravelEnv,char):
    char_bits = [int(x) for x in '{:08b}'.format(ord(char))]
    cocotb.log.info (f"[TEST] start sending on uart {char}")
    #send start bit
    caravelEnv.drive_gpio_in((5,5),0)
    await Timer(bit_time_ns, units='ns')
    #send bits 
    for i in range(8):
        caravelEnv.drive_gpio_in((5,5),char_bits[i])
        await Timer(bit_time_ns, units='ns')

    # stop of frame
    caravelEnv.drive_gpio_in((5,5),1)
    await Timer(bit_time_ns, units='ns')
    await Timer(bit_time_ns, units='ns')
    # insert 4 bit delay just for debugging
    await Timer(bit_time_ns, units='ns')
    await Timer(bit_time_ns, units='ns')
    await Timer(bit_time_ns, units='ns')
    await Timer(bit_time_ns, units='ns')

        
async def uart_check_char_recieved(caravelEnv,cpu):
 # check cpu recieved the correct character
    while True: 
        reg_uart_data = caravelEnv.caravel_hdl.soc.core.uart_rxtx_w.value.binstr
        reg1 = cpu.read_debug_reg1()
        cocotb.log.debug(f"[TEST] reg1 = {hex(reg1)}")   
        if  reg1 == 0x1B:
            cocotb.log.info(f"[TEST] Pass cpu has recieved the correct character {chr(int(reg_uart_data,2))}")   
            return
        if reg1 == 0x1E:
            cocotb.log.error(f"[TEST] Failed Pass cpu has recieved the wrong character {chr(int(reg_uart_data,2))}")  
            return
               
        await ClockCycles(caravelEnv.clk,1) 