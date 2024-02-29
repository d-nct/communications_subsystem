#include "MonitorRF.h"

void MonitorRF::updateRSSIStatus() {
    /* Atualiza o status do RSSI */
    int rssi = LoRa.packetRssi();
    if (rssi > -85) {
        status_rssi = RSSI_GOOD;
    } else if (rssi > -100) {
        status_rssi = RSSI_NORMAL;
    } else if (rssi > -115) {
        status_rssi = RSSI_WARNING;
    } else if (rssi > -130) {
        status_rssi = RSSI_CRITICAL;
    } else {
        status_rssi = RSSI_NO_SIGNAL;
    }
}

void MonitorRF::updatePacketStatus() {
    /* Atualiza a taxa dos pacotes recebidos */
    packet_received_rate = (float) packet_received / packet_sended;

    if (packet_received_rate > 0.75) {
        status_packet = PACKET_GOOD;
    } else if (packet_received_rate > 0.50) {
        status_packet = PACKET_NORMAL;
    } else if (packet_received_rate > 0.25) {
        status_packet = PACKET_WARNING;
    } else if (packet_received_rate > 0.05) {
        status_packet = PACKET_CRITICAL;
    } else {
        status_packet = PACKET_NO_SIGNAL;
    }
}

void MonitorRF::monitor() {
    /* Atualiza os indicadores */
    updateRSSIStatus();
    updatePacketStatus();

    /* Logga */
    Logger::log(LOG_INFO, "Monitoramento da comunicação LoRa: ");
    Logger::print(LOG_INFO, "Pacotes enviados: ");
    Logger::print(LOG_INFO, packet_sended);
    Logger::print(LOG_INFO, "\nPacotes recebidos: ");
    Logger::print(LOG_INFO, packet_received);
    Logger::print(LOG_INFO, "\nTaxa de sucesso: ");
    Logger::print(LOG_INFO, packet_received_rate);
    Logger::print(LOG_INFO, "\nRSSI: ");
    Logger::print(LOG_INFO, status_rssi);
    Logger::print(LOG_INFO, "\nStatus do pacote: ");
    Logger::print(LOG_INFO, status_packet);
    Logger::print(LOG_INFO, "\n");
}

void MonitorRF::incrementPacketSended() {
    packet_sended++;
}

void MonitorRF::incrementPacketReceived() {
    packet_received++;
}