#define Lab 9

#include "uart.h"
#include "mbox.h"
#include "rand.h"
#include "delays.h"
#include "power.h"
#include "lfb.h"

void main()
{
#if Lab == 1
    //Lab 1: Multicore C
    while(1);
#elif Lab == 2
    //Lab 2: UART1
    // set up serial console
    uart_init();
    
    // say hello
    uart_puts("Hello World!\n");
    
    // echo everything back
    while(1) {
        uart_send(uart_getc());
    }

#elif Lab == 3
    //Lab 3: Mailboxes
    // set up serial console
    uart_init();
    
    // get the board's unique serial number with a mailbox call
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    
    mbox[2] = MBOX_TAG_GETSERIAL;   // get serial number command
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;

    // send the message to the GPU and receive answer
    if (mbox_call(MBOX_CH_PROP)) {
        uart_puts("My serial number is: ");
        uart_hex(mbox[6]);
        uart_hex(mbox[5]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query serial!\n");
    }

    // echo everything back
    while(1) {
        uart_send(uart_getc());
    }
    
#elif Lab == 4
    //Lab 4: Uart0
    // set up serial console
    uart_init();
    
    // get the board's unique serial number with a mailbox call
    mbox[0] = 8*4;                  // length of the message
    mbox[1] = MBOX_REQUEST;         // this is a request message
    
    mbox[2] = MBOX_TAG_GETSERIAL;   // get serial number command
    mbox[3] = 8;                    // buffer size
    mbox[4] = 8;
    mbox[5] = 0;                    // clear output buffer
    mbox[6] = 0;

    mbox[7] = MBOX_TAG_LAST;

    // send the message to the GPU and receive answer
    if (mbox_call(MBOX_CH_PROP)) {
        uart_puts("My serial number is: ");
        uart_hex(mbox[6]);
        uart_hex(mbox[5]);
        uart_puts("\n");
    } else {
        uart_puts("Unable to query serial!\n");
    }

    // echo everything back
    while(1) {
        uart_send(uart_getc());
    }
#elif Lab == 5
    //Lab 5: Random
    // set up serial console and random number generator
    uart_init();
    rand_init();
    
    uart_puts("Here goes a random number: ");
    uart_hex(rand(0,4294967295));
    uart_puts("(Hex)(0~4294967295)\n");

    // echo everything back
    while(1) {
        uart_send(uart_getc());
    }
#elif Lab == 6
    //Lab 6: Delay
    // set up serial console
    uart_init();
    
    uart_puts("Waiting 1000000 CPU cycles (ARM CPU): ");
    wait_cycles(1000000);
    uart_puts("OK\n");

    uart_puts("Waiting 1000000 microsec (ARM CPU): ");
    wait_msec(1000000);
    uart_puts("OK\n");

    uart_puts("Waiting 1000000 microsec (BCM System Timer): ");
    if(get_system_timer()==0) {
        uart_puts("Not available\n");
    } else {
        wait_msec_st(1000000);
        uart_puts("OK\n");
    }

    // echo everything back
    while(1) {
        uart_send(uart_getc());
    }
#elif Lab == 7
    char c;

    // set up serial console
    uart_init();

    while(1) {
        uart_puts(" 1 - power off\n 2 - reset\nChoose one: ");
        c=uart_getc();
        uart_send(c);
        uart_puts("\n\n");
        if(c=='1') power_off();
        if(c=='2') reset();
    }
#elif Lab == 8
    // set up serial console and linear frame buffer
    uart_init();
    lfb_init();

    // display a pixmap
    lfb_showpicture();

    // echo everything back
    while(1) {
        uart_send(uart_getc());
    }
#elif Lab == 9
    // set up serial console and linear frame buffer
    uart_init();
    lfb_init();

    // display an ASCII string on screen with PSF
    lfb_print(80, 80, "Hello World!");

    // display a UTF-8 string on screen with SSFN
    lfb_proprint(80, 120, "Hello 多种语言 Многоязычный többnyelvű World!");

    // echo everything back
    while(1) {
        uart_send(uart_getc());
    }
#endif
}