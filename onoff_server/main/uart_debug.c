/*
 * uart_debug.c
 *
 *  Created on: 2024年8月23日
 *      Author: Tanzhiqing
 */
#include "uart_debug.h"
#include "esp_log.h"
#include "strings.h"
#include "string.h"
#include "esp_ble_mesh_networking_api.h"
#include "esp_ble_mesh_provisioning_api.h"
#include "bms.h"
#include "mesh_model.h"
#define TAG "UART_DEBUG"


#define ESP_BLE_MESH_VND_MODEL_OP_SEND      ESP_BLE_MESH_MODEL_OP_3(0x00, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_STATUS    ESP_BLE_MESH_MODEL_OP_3(0x01, CID_ESP)
QueueHandle_t uart0_queue;
extern uint16_t opnode_addr;
/************************************************************************************
* Function Name  : Chr2Hex
* Description    : 格式转换
* Input          : None
* Output         : None
* Return         : None
************************************************************************************/ 
static uint8_t Chr2Hex(uint8_t Chr)
{
    if (Chr >= '0' && Chr <= '9')
        return Chr - '0';
    if ((Chr >= 'A') && (Chr <= 'F'))
        return Chr - 'A' + 10;
    if ((Chr >= 'a') && (Chr <= 'f'))
        return Chr - 'a' + 10;
    return 0;
}
/************************************************************************************
* Function Name  : Str2Hex
* Description    : 格式转换
* Input          : None
* Output         : None
* Return         : None
************************************************************************************/ 
uint32_t Str2Hex(char *pMessage, char tailChar, bool isHex)
{
    uint8_t i = 0;
    uint32_t retDataLen = 0;
    uint8_t value;
    bool signFlag = false;
    
    do {
        value = pMessage[i++];
        if (/* (value != ' ') & */ (value != '\r') & (value != '\n')) {
            if (isHex == false) {
                if (value == '-') {
                    signFlag = true;
                } else {
                    retDataLen = retDataLen * 10 + value - '0';
                }
            } else {
                retDataLen = retDataLen * 16 + Chr2Hex(value);
            }
        }
    } while ((pMessage[i] != tailChar) && (pMessage[i] != '\n'));
    
    if (signFlag == true) {
        retDataLen = 0xFFFFFFFFUL - retDataLen;
    }
    return retDataLen;
}

 
void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    uint8_t* dtmp = (uint8_t*) malloc(RD_BUF_SIZE);
     char *pHead;
    for(;;) {
        //Waiting for UART event.
        if(xQueueReceive(uart0_queue, (void * )&event, (TickType_t)portMAX_DELAY)) {
            bzero(dtmp, RD_BUF_SIZE);
            //ESP_LOGI(TAG, "uart[%d] event:", EX_UART_NUM);
            switch(event.type) 
            {
                //Event of UART receving data
                case UART_DATA:
                    //ESP_LOGI(TAG, "[UART DATA]: %d", event.size);
                    uart_read_bytes(EX_UART_NUM, dtmp, event.size, portMAX_DELAY);
                    ESP_LOGI(TAG, "read data: %s,datalen:%d", dtmp,event.size);
                    if(strstr((const char *)dtmp,"reset_node"))
                    {
						 ESP_LOGI(TAG, "node reset");
						 esp_ble_mesh_node_local_reset();
						 esp_ble_mesh_node_prov_enable((esp_ble_mesh_prov_bearer_t)(ESP_BLE_MESH_PROV_ADV | ESP_BLE_MESH_PROV_GATT));

						// esp_restart();
						 break;
					}
					pHead =strstr((const char *)dtmp,"opnode_addr");
					if(pHead)
                    {
						pHead += strlen("opnode_addr");
						opnode_addr = Str2Hex(pHead + 1, '\r', true);
						 ESP_LOGI(TAG, "opnode_addr :%d",opnode_addr);
						// esp_restart();'
						 break;
					}

                    BMS_RUN();

                    BMS_STOP();

                    example_ble_mesh_send_vendor_message(true,event.size+1,dtmp);

                    uart_write_bytes(EX_UART_NUM, (const char*) dtmp, event.size);

                    break;
                //Event of HW FIFO overflow detected
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    // If fifo overflow happened, you should consider adding flow control for your application.
                    // The ISR has already reset the rx FIFO,
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(EX_UART_NUM);
                    xQueueReset(uart0_queue);
                    break;
                //Event of UART ring buffer full
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    // If buffer full happened, you should consider increasing your buffer size
                    // As an example, we directly flush the rx buffer here in order to read more data.
                    uart_flush_input(EX_UART_NUM);
                    xQueueReset(uart0_queue);
                    break;
                //Event of UART RX break detected
                case UART_BREAK:
                    ESP_LOGI(TAG, "uart rx break");
                    break;
                //Event of UART parity check error
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error");
                    break;
                //Event of UART frame error
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error");
                    break;
                //UART_PATTERN_DET
                case UART_PATTERN_DET:
                    uart_get_buffered_data_len(EX_UART_NUM, &buffered_size);
                    int pos = uart_pattern_pop_pos(EX_UART_NUM);
                    ESP_LOGI(TAG, "[UART PATTERN DETECTED] pos: %d, buffered size: %d", pos, buffered_size);
                    if (pos == -1) {
                        // There used to be a UART_PATTERN_DET event, but the pattern position queue is full so that it can not
                        // record the position. We should set a larger queue size.
                        // As an example, we directly flush the rx buffer here.
                        uart_flush_input(EX_UART_NUM);
                    } else {
                        uart_read_bytes(EX_UART_NUM, dtmp, pos, 100 / portTICK_PERIOD_MS);
                        uint8_t pat[PATTERN_CHR_NUM + 1];
                        memset(pat, 0, sizeof(pat));
                        uart_read_bytes(EX_UART_NUM, pat, PATTERN_CHR_NUM, 100 / portTICK_PERIOD_MS);
                        ESP_LOGI(TAG, "read data: %s", dtmp);
                        ESP_LOGI(TAG, "read pat : %s", pat);
                    }
                    break;
                //Others
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

void uart_debug_init()
{
	uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
	//Install UART driver, and get the queue.
    uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 20, &uart0_queue, 0);
    uart_param_config(EX_UART_NUM, &uart_config);


    //Set UART log level
    esp_log_level_set(TAG, ESP_LOG_INFO);
    //Set UART pins (using UART0 default pins ie no changes.)
    uart_set_pin(EX_UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);


    //Set uart pattern detect function.
    uart_enable_pattern_det_baud_intr(EX_UART_NUM, '+', PATTERN_CHR_NUM, 9, 0, 0);
    //Reset the pattern queue length to record at most 20 pattern positions.
    uart_pattern_queue_reset(EX_UART_NUM, 20);
 
    //Create a task to handler UART event from ISR
    xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 12, NULL);
 
}







