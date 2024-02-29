#include "CommunicationRF.h"

int ComRF::setup() {
    int status;

    /* Inicialização das variáveis privadas */
    packet_id = 1; // Inicializa o ID do pacote em 1
    telemetry_received.id = 0; // Inicializa o ID do último pacote recebido em 0

    // Inicializa o LoRa
    LoRa.setPins(LORA_PIN_SS, LORA_PIN_RST, LORA_PIN_DIO0);
    
    if (status = LoRa.begin(LORA_FREQUENCY) != 1){
        Logger::log(LOG_ERROR, "Erro ao inicializar o LoRa.");
        while (1);
    }
    
    LoRa.setSyncWord(LORA_SYNC_WORD);
    
    Logger::log(LOG_INFO, "LoRa inicializado.");
    return status;
}

void ComRF::sendPacket(const Telemetry& packet) {
    // Serializa a mensagem
    Package::serialize(packet, buffer_sender);

    // Envia a mensagem serializada
    LoRa.beginPacket();
    LoRa.write(buffer_sender, telemetry_length);
    LoRa.endPacket();

    // Logga
    Logger::log(LOG_INFO, "LoRa: Pacote enviado.");
    Logger::print(LOG_DEBUG, "Conteúdo serializado: ");
    for (size_t i = 0; i < telemetry_length; i++) {
        Logger::print(LOG_DEBUG, (char*) buffer_sender[i]);
    }
    Logger::print(LOG_DEBUG, "\n");

    // Atualiza o contador de pacotes enviados
    MonitorRF::incrementPacketSended();
}

void ComRF::configurePacket(Telemetry& packet) {
    packet.id = getPacketId();
    packet.timestamp = millis();
}

void ComRF::updatePacketId() {
    packet_id++;
}


Telemetry* ComRF::receivePacket() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // atualiza o contador de pacotes recebidos
        MonitorRF::incrementPacketReceived();

        // Logga
        Logger::log(LOG_INFO, "LoRa: Pacote recebido.");
        Logger::print(LOG_DEBUG, "Conteúdo serializado: ");
        
        int i = 0;
        while (LoRa.available()) {
            com_serialized c = LoRa.read();
            buffer_receiver[i] = c;

            Logger::print(LOG_DEBUG, (char*) c);
        }
        
        Logger::print(LOG_DEBUG, "\n");
    }

    // Deserializa a mensagem
    telemetry_received = Package::deserialize(buffer_receiver);

    return &telemetry_received;
}