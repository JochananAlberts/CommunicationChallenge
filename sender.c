// #include <libpynq.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{

    // pynq_init();
    // switchbox_init();

    // switchbox_set_pin(IO_AR0, SWB_UART0_RX); 
    // switchbox_set_pin(IO_AR2, SWB_UART1_RX);

    // uart_init(UART0);
    // uart_reset_fifos(UART0);
    // uart_init(UART1);
    // uart_reset_fifos(UART1);

    
    for (;;) {
        char message[256];

        printf("Type a message (or /stop to exit): ");
        if (!fgets(message, sizeof message, stdin)) {
            break;
        }
        message[strcspn(message, "\r\n")] = '\0';

        if (strcmp(message, "/stop") == 0) {
            break;
        }

        for (int i = 0; message[i] != '\0'; i++){
            uint8_t b = (uint8_t) message[i];
            // uart_send (UART0, b);
            // uart_send (UART1, b);
            printf("sent byte %u\n", b);
        }
 
}
    // switchbox_destroy();
    // pynq_destroy();

    return EXIT_SUCCESS;
}