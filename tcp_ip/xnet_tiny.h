#ifndef __XNET_TINY_H__
#define __XNET_TINY_H__

#include <stdint.h>

#define XNET_CFG_PACKET_MAX_SIZE 1516

typedef struct _xnet_packet_t {
	uint16_t size;
	uint8_t* data;
	uint8_t payload[XNET_CFG_PACKET_MAX_SIZE];
} xnet_packet_t;

xnet_packet_t* xnet_alloc_for_send(uint16_t data_size);
xnet_packet_t* xnet_alloc_for_recv(uint16_t data_size);
