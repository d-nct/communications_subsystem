#ifndef MONITORRF_H
#define MONITORRF_H

#include "_config.h"
#include "_types.h"
#include "Logger.h"
#include "Package.h"
#include "CommunicationRF.h"

#include <LoRa.h>

class MonitorRF {
public: 
    /**
     * Monitora a comunicação LoRa.
    */
    static void monitor();

    /**
     * Retorna a taxa de sucesso dos pacotes.
    */
    static float getPacketReceivedRate() { return packet_received_rate; }

    /**
     * Retorna o status do RSSI.
    */
    static RF_RSSI_Status_t getRSSIStatus() { return status_rssi; }

    /**
     * Incrementa o contador de pacotes enviados.
    */
    static void incrementPacketSended();

    /**
     * Incrementa o contador de pacotes recebidos.
    */
    static void incrementPacketReceived();

    static void updateRSSIStatus();

    static void updatePacketStatus();

private:
    /* Monitoramento da taxa de sucesso dos pacotes */
    static uint32_t packet_received;
    static uint32_t packet_sended;
    static uint32_t packet_lost;
    static float    packet_received_rate;

    /* Indicadores da transmissão */
    static RF_RSSI_Status_t   status_rssi;
    static RF_Packet_Status_t status_packet;
};

#endif // MONITORRF_H