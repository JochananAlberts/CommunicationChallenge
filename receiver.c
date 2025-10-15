#include <libpynq.h>
#include <stdio.h>
#include <stdint.h>

int main(void) {
    pynq_init();
    switchbox_init();

    switchbox_set_pin(IO_AR1, SWB_UART0_RX);
    switchbox_set_pin(IO_AR3, SWB_UART1_RX);

    uart_init(UART0);
    uart_init(UART1);
    uart_reset_fifos(UART0);
    uart_reset_fifos(UART1);

    printf("listening\n");

    char message[256];
    size_t i = 0;

    // Switch between channels by commenting out channel
    for (;;) {
        uint8_t b = uart_recv(UART0);
        // uint8_t b = uart_recv(UART1);                  
        if (b == ' ') continue;
        if (b == '\r') continue;              

        if (b == '\n') {                       
            message[i] = '\0';                 
            printf("MSG: %s\n", message);      
            i = 0;                             
            continue;
        }
    }

    switchbox_destroy();
    pynq_destroy();
    return EXIT_SUCCESS;
}