#ifndef COMMUNICATIONRF_H
#define COMMUNICATIONRF_H

#include "_config.h"
#include "_types.h"
#include "Logger.h"
#include "Package.h"

#include <LoRa.h>

class ComRF {
public:
    /**
     * Inicializa o LoRa com as configurações de Definitions.h.
    */
    int setup();

    /**
     * Envia uma mensagem serializada via LoRa. Certifique-se de que o pacote está configurado antes de enviar.
     * 
     * @param packet O pacote de telemetria a ser serializado e enviado.
    */
    void sendPacket(const Telemetry& packet);

    /**
     * Configura o pacote com o ID e timestamp.
    */
    void configurePackage(Telemetry& packet);

    /**
     * Recebe uma mensagem serializada via LoRa.
     * 
     * Atenção: a mensagem fica armazenada no buffer_receiver até receber a próxima, então seja rápido!0.
     * A responsabilidade de desserializar a mensagem é do usuário. Use Package::deserializeStruct(buffer_receiver) para isso.
    */
    Telemetry* receivePacket();

    /**
     * Retorna o buffer de recebimento.
    */
    com_serialized* getBufferReceiver();

    /**
     * Monitora a comunicação LoRa.
    */
    void monitor();

    com_uint getPackageId();

    void updatePackageId();

private:
    com_uint package_id = 0;
    uint packages_received = 0;
    uint packages_sended = 0;
    uint packages_lost = 0;
    float packages_received_rate = 0;

    static const int telemetry_length = sizeof(Telemetry); // Tamanho da mensagem serializada
    com_serialized buffer_sender[telemetry_length];
    com_serialized buffer_receiver[telemetry_length];
    Telemetry telemetry_received;
    
    RF_RSSI_Status_t status_rssi;
    RF_Packet_Status_t status_packet;


};

#endif // COMMUNICATIONRF_H