/*
 * modem_packet.h
 *
 */

#ifndef MODEM_PACKET_H
#define MODEM_PACKET_H


#include "modem_channels.h"

/*
* -------------------------------------------------------------------------
* |0xFE|ChanInfo(1Byte)|TranHi(1Byte)|TranLow(1Byte)|Dummy|Paylaod|Padding|
* -------------------------------------------------------------------------
*
* bits map of Transfer High Byte show below
* ------------------------------------------------------------------------------------------------------------
* |0xFE|ChanInfo(1Byte)|Payload offset(2bit)-Reserved(2bit)-ThanHi(4bit)|TranLow(1Byte)|Dummy|Paylaod|Padding|
* ------------------------------------------------------------------------------------------------------------
*/
/*
* packet length = packet header size + Dymmy size + Payload size;
* packet transfer data length = Dymmy size + Payload size;
* packet payload length = Payload size;
*
* payload offset = Dymmy size;
*
*/

/* total 12 bits present packet tansfer data length, that is 4095 bytes, but for 32bit-aligned in FIFO, so round down to 4092 bytes */
#define MAX_PACKET_LENGTH (1024)
#define MAX_PACKET_TRANSFER_DATA_LENGTH (MAX_PACKET_LENGTH - 4)
#define SMALL_PACKET_LENGTH (512)
#define SMALL_PACKET_TRANSFER_DATA_LENGTH (SMALL_PACKET_LENGTH - 4)

#define MODEM_PACKET_END_DUMMY_SIZE         (4)
#define MODEM_PACKET_MAX_LENGTH    (4096)
#define MODEM_PACKET_MAX_TRANSFER_DATA_TLENGTH    (4092)

/* MACROs to get information from packet header */
#define GET_START_FLAG(p_head)    (p_head->m_start_flag)
#define GET_CHANNEL_NUMBER(p_head)    (p_head->m_chanInfo)
#define GET_PACKET_TRANSFER_DATA_LENGTH(p_head)    (((p_head->m_tranHi & 0x0F) << 8) | (p_head->m_tranLow & 0xFF))
#define GET_PACKET_PAYLOAD_OFFSET(p_head)    ((p_head->m_tranHi & 0xC0) >> 6)
#define GET_PACKET_PAYLOAD_LENGTH(p_head)    (GET_PACKET_TRANSFER_DATA_LENGTH(p_head) - GET_PACKET_PAYLOAD_OFFSET(p_head))


typedef struct modem_packet_head {
    unsigned char m_start_flag;       /*start flag(1), little endian*/
    unsigned char m_chanInfo;         /*channel id*/
    unsigned char m_tranHi;           /*len High byte, little endian*/
    unsigned char m_tranLow;          /*len low byte, little endian*/
} modem_packet_head_t;

/* data struct of modem packet driver */
typedef struct modem_packet {
    unsigned char *pm_rx_pkt_buf; /* rx packet buffer include both packet header and packet data */
    unsigned char *pm_tx_pkt_buf; /* tx packet buffer include both packet header and packet data */
    unsigned int m_tx_pkt_len; /* whole tx packet size include both packet header size and packet data size in tx packet buffer */
} modem_packet_t;


int modem_one_packet_read(int t_given_pkt_len);
int modem_write_packets(char *pt_buf, int t_len, unsigned int t_chan_num);
int modem_packet_init(void);
void modem_packet_exit(void);
int modem_write_rnic_packets(char *pt_buf, int t_len, unsigned int t_chan_num);

#endif
