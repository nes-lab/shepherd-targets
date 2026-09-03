#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrf_gpiote.h"

#include "peripherals.h"
#include "printf.h"

#include "pt.h"

// see shepherd_node_id.c for details
extern const uint16_t SHEPHERD_NODE_ID;

// Adapted pinout for Target V1.2 (Riotee)
#define PIN_UART_TX (8)  // P0.08
#define PIN_UART_RX (21) // P0.21

#ifndef SHEPHERD_BAUDRATE
  #define SHEPHERD_BAUDRATE (115200)
#endif


/* PLATFORM SPECIFIC CODE */

static inline void delay_ms(const uint32_t duration)
{
    timer_reset();
    const uint32_t duration_us = duration * 1000;
    while (timer_now_us() < duration_us);
}

/* PRIMARY ROUTINE */

int main(void)
{

    /* Optimize latency over power */
    NRF_POWER->TASKS_CONSTLAT   = 1;
    /* Start HF crystal oscillator */
    NRF_CLOCK->TASKS_HFCLKSTART = 1;

    uart_init(PIN_UART_TX, PIN_UART_RX, SHEPHERD_BAUDRATE);
    timer_init();

    delay_ms(100);
    printf("Unfinite Lorem ipsum Generator @ %d baud.\r\n", SHEPHERD_BAUDRATE);
    delay_ms(100);

    while (1u)
    {
        printf("Lorem ipsum dolor sit amet, consetetur sadipscing elitr,  sed diam nonumy eirmod "
               "tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua.\r\n");
        printf("At vero eos et accusam et justo duo dolores et ea rebum.\r\n");
        printf("Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit "
               "amet.\r\n");
        printf("\r\n");
        printf("Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium "
               "doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore "
               "veritatis et quasi architecto beatae vitae dicta sunt explicabo.\r\n");
        printf("Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed "
               "quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt.\r\n");
        printf("Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, "
               "adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et "
               "dolore magnam aliquam quaerat voluptatem.\r\n");
        printf("Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit "
               "laboriosam, nisi ut aliquid ex ea commodi consequatur?\r\n");
        printf("Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil "
               "molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla "
               "pariatur?\r\n");
        printf("\r\n");
        printf("At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis "
               "praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias "
               "excepturi sint occaecati cupiditate non provident, similique sunt in culpa qui "
               "officia deserunt mollitia animi, id est laborum et dolorum fuga.\r\n");
        printf("Et harum quidem rerum facilis est et expedita distinctio.\r\n");
        printf("Nam libero tempore, cum soluta nobis est eligendi optio cumque nihil impedit quo "
               "minus id quod maxime placeat facere possimus, omnis voluptas assumenda est, omnis "
               "dolor repellendus.\r\n");
        printf("Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe "
               "eveniet ut et voluptates repudiandae sint et molestiae non recusandae.\r\n");
        printf("Itaque earum rerum hic tenetur a sapiente delectus, ut aut reiciendis voluptatibus "
               "maiores alias consequatur aut perferendis doloribus asperiores repellat.\r\n");
        printf("\r\n");
        printf("\r\n");
    }
}
