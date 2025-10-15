#include <libpynq.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE "Hello\n"


int main(void)
{

    pynq_init();
    display_t display;
    display_init(&display);
    switchbox_init();

    switchbox_set_pin(IO_AR0, SWB_UART0_RX); 
    switchbox_set_pin(IO_AR2, SWB_UART1_RX);

    uart_init(UART0);
    uart_reset_fifos(UART0);
    uart_init(UART1);
    uart_reset_fifos(UART1);

    displayFillScreen(&display, RGB_BLACK);
    
    uint8_t message[] = MESSAGE;
    int i = 0;
    while (message[i] != '\0'){
        uart_send (UART0, message[i]);
        uart_send (UART1, message[i]);
        printf("sent byte %d\n", message[i]);
        i++;
    }

    switchbox_destroy();
    pynq_destroy();
    display_destroy(&display);
    return EXIT_SUCCESS;
}