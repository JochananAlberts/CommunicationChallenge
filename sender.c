#include <libpynq.h>
#include <string.h>
#include <stdio.h>


#define MAX_CHARS_PER_LINE  40

int main(void)
{

    pynq_init();
    switchbox_init();

    switchbox_set_pin(IO_AR0, SWB_UART0_TX); 
    switchbox_set_pin(IO_AR2, SWB_UART1_TX);

    uart_init(UART0);
    uart_reset_fifos(UART0);
    uart_init(UART1);
    uart_reset_fifos(UART1);

    display_t d;
    display_init(&d);
    displayDisplayOff(&d);  
    sleep_msec(150);
    displayDisplayOn(&d);   
    sleep_msec(150);
    displayBacklightOn(&d);

    FontxFile f[2];
    InitFontx(f, "../../fonts/ILGH16XB.FNT", "");
    displaySetFontDirection(&d, TEXT_DIRECTION0);
    displayFillScreen(&d, RGB_WHITE);
    displayDrawString(&d, f, 6, 42, (uint8_t*)"Sending messages...", RGB_BLACK);

    sleep_msec(2);
    
    for (;;) {
        char message[256];
        
        printf("Type a message (or /stop to exit): ");
        if (!fgets(message, sizeof message, stdin)) {
            break;
        }

        if (strcmp(message, "/stop") == 0) {
            break;
        }

        for (int i = 0; message[i] != '\0'; i++){

            uint8_t b = (uint8_t) message[i];
            uart_send (UART0, b);
            uart_send (UART1, b);
            printf("sent byte %u\n", b);
        }
        char line[MAX_CHARS_PER_LINE + 1];
        strncpy(line, message, MAX_CHARS_PER_LINE);
        line[MAX_CHARS_PER_LINE] = '\0';

        displayDrawFillRect(&d, 0, 60, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, RGB_WHITE);
        displayDrawString(&d, f, 6, 80, (uint8_t*)line, RGB_BLUE);
 
}
    switchbox_destroy();
    pynq_destroy();

    return EXIT_SUCCESS;
}
