/*
 * mesh_model.c
 *
 *  Created on: 2024年9月19日
 *      Author: Tanzhiqing
 */

/*自定义发送测试*/
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include "esp_log.h"

#include "mesh_model.h"
#include "esp_ble_mesh_provisioning_api.h"
#include "esp_ble_mesh_config_model_api.h"
#include "esp_ble_mesh_generic_model_api.h"
#include "esp_ble_mesh_networking_api.h"
#include "esp_ble_mesh_defs.h"
#define CID_ESP 0x02E5
#define MSG_SEND_TTL        3
#define MSG_TIMEOUT         0

#define MSG_SEND_REL        false
#define TAG "UART_DEBUG"

#define ESP_BLE_MESH_VND_MODEL_ID_CLIENT    0x0000
#define ESP_BLE_MESH_VND_MODEL_ID_SERVER    0x0001

#define ESP_BLE_MESH_VND_MODEL_OP_SEND      ESP_BLE_MESH_MODEL_OP_3(0x00, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_STATUS    ESP_BLE_MESH_MODEL_OP_3(0x01, CID_ESP)

uint16_t opnode_addr =0xffff;

struct  esp_ble_mesh_model_t *p_model;

void example_ble_mesh_send_vendor_message(bool resend,uint16_t lenght,uint8_t *data)
{
    esp_ble_mesh_msg_ctx_t ctx = {0};
    uint32_t opcode;
    esp_err_t err;
 //获取net_idx ,app_idx

    ctx.net_idx = 0x0000;
    ctx.app_idx = 0x0000;
    
    //这个是广播地址
   // ctx.addr = opnode_addr;   /* to all nodes */
    ctx.addr = 0xffff;
    ctx.send_ttl = MSG_SEND_TTL;
    ctx.send_rel = MSG_SEND_REL;
    opcode = ESP_BLE_MESH_VND_MODEL_OP_STATUS;
 	
    if (resend == false) {
        data[0]++;
    }

    ESP_LOGI(TAG, "net_idx 0x%04x, app_idx 0x%04x, addr 0x%04x",ctx.net_idx ,ctx.app_idx,ctx.addr );

    //向client上报消息，其他server收不到
    err = esp_ble_mesh_server_model_send_msg(p_model,&ctx, opcode,lenght, (uint8_t *)data);
  //  err = esp_ble_mesh_server_model_send_msg(p_model,&ctx, ESP_BLE_MESH_VND_MODEL_OP_STATUS,lenght, (uint8_t *)data);
}