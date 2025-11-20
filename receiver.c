#include <libpynq.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_CHARS_PER_LINE  40

int main(void) {
    pynq_init();
    switchbox_init();

    switchbox_set_pin(IO_AR1, SWB_UART0_RX);
    switchbox_set_pin(IO_AR3, SWB_UART1_RX);
    uart_init(UART0);
    uart_reset_fifos(UART0);
    uart_init(UART1);
    uart_reset_fifos(UART1);

    setvbuf(stdout, NULL, _IONBF, 0);
    printf("listening\n");

    display_t d;
    display_init(&d);
    displayDisplayOff(&d);  sleep_msec(150);
    displayDisplayOn(&d);   sleep_msec(150);
    displayBacklightOn(&d);

    FontxFile f[2];
    InitFontx(f, "../../fonts/ILGH16XB.FNT", "");
    displaySetFontDirection(&d, TEXT_DIRECTION0);
    displayFillScreen(&d, RGB_WHITE);
    displayDrawString(&d, f, 6, 18, (uint8_t*)"UART0 -> LCD", RGB_BLACK);
    displayDrawString(&d, f, 6, 42, (uint8_t*)"listening...", RGB_BLACK);

    char message[1000];
    size_t i = 0;

    for (;;) {
        uint8_t b = uart_recv(UART0);
        // uint8_t b = uart_recv(UART1);
        // if (b >= 'z') continue;
        if (b == '\r') continue;

        if (b == '\n') {
            message[i] = '\0';
            printf("MSG: %s\n", message);

            char line[MAX_CHARS_PER_LINE + 1];
            strncpy(line, message, MAX_CHARS_PER_LINE);
            line[MAX_CHARS_PER_LINE] = '\0';

            displayDrawFillRect(&d, 0, 60, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, RGB_WHITE);
            displayDrawString(&d, f, 6, 80, (uint8_t*)line, RGB_BLUE);

            i = 0;
            continue;
        }

        if (i < sizeof(message) - 1) {
            message[i++] = (char)b;
        } else {
            message[i] = '\0';
            printf("MSG(partial): %s\n", message);
            i = 0;
        }
    }

    display_destroy(&d);
    switchbox_destroy();
    pynq_destroy();

    return 0;
}