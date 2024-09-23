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
#define CID_ESP 0x02E5
#define MSG_SEND_TTL        3
#define MSG_TIMEOUT         0

#define MSG_SEND_REL        false
#define TAG "UART_DEBUG"
uint16_t opnode_addr =0xffff;

esp_ble_mesh_generic_server_cb_param_t generic_param;

void example_ble_mesh_send_vendor_message(bool resend,uint16_t lenght,uint8_t *data)
{
    esp_ble_mesh_msg_ctx_t ctx = {0};
    uint32_t opcode;
    esp_err_t err;
 //获取net_idx ,app_idx
    ctx.net_idx = generic_param.ctx.net_idx;
    ctx.app_idx = generic_param.ctx.app_idx;
    //这个是广播地址
    ctx.addr = opnode_addr;   /* to all nodes */
    ctx.send_ttl = 3;
    ctx.send_rel = 0;
    opcode = ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS;
 	esp_ble_mesh_server_recv_gen_onoff_set_t onoff_set;
 	
 	onoff_set.onoff =0x1;
 	
 	ctx.recv_op=ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_GET;
    if (resend == false) {
        data[0]++;
    }
    esp_ble_mesh_server_recv_gen_onoff_set_t set;
    set.op_en = 1;

    ESP_LOGI(TAG, "net_idx 0x%04x, app_idx 0x%04x, addr 0x%04x",ctx.net_idx ,ctx.app_idx,ctx.addr );
    esp_ble_mesh_gen_onoff_srv_t *srv = (esp_ble_mesh_gen_onoff_srv_t *)generic_param.model->user_data;
    
    //example_handle_gen_onoff_msg(generic_param.model, &ctx, &set);
	  uint8_t xdata=0x2;
	  esp_ble_mesh_server_model_send_msg(generic_param.model, &ctx,ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS, sizeof(srv->state.onoff), &xdata);

    //向client上报消息，其他server收不到
    //err = esp_ble_mesh_server_model_send_msg(generic_param.model,&ctx, ESP_BLE_MESH_GENERIC_SERVER_STATE_CHANGE_EVT,lenght, (uint8_t *)data);

  #if 0  
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to send vendor message 0x%06" PRIx32, opcode);
        return;
    }
  #endif
}