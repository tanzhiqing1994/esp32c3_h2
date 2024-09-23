/*
 * uart_debug.h
 *
 *  Created on: 2024年8月23日
 *      Author: Tanzhiqing
 */

#ifndef MAIN_UART_DEBUG_H_
#define MAIN_UART_DEBUG_H_


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"


#define EX_UART_NUM UART_NUM_0
#define PATTERN_CHR_NUM    (3)         /*!< Set the number of consecutive and identical characters received by receiver which defines a UART pattern*/


#define BUF_SIZE (1024)
#define RD_BUF_SIZE (BUF_SIZE)



#define MSG_SEND_TTL        3
#define MSG_SEND_REL        false
#define MSG_TIMEOUT         0
#define MSG_ROLE            ROLE_PROVISIONER

extern QueueHandle_t uart0_queue;

void uart_debug_init();
void uart_event_task(void *pvParameters);
void example_ble_mesh_send_vendor_message(bool resend,uint16_t lenght,uint8_t *data);

#endif /* MAIN_UART_DEBUG_H_ */
