#ifndef COMMUNICATIONRF_H
#define COMMUNICATIONRF_H

#include "_config.h"
#include "_types.h"
#include "Logger.h"
#include "Package.h"
#include "MonitorRF.h"

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
    void configurePacket(Telemetry& packet);

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
    com_serialized* getBufferReceiver() { return buffer_receiver; }

    /**
     * Retorna o ID do pacote.
    */
    static com_uint getPacketId() { return packet_id; }

    /**
     * Incrementa o ID do pacote.
    */
    void updatePacketId();

    /**
     * Retorna o último ID recebido.
    */
    static com_uint getLastReceivedId() { return telemetry_received.id; }

private:
    static com_uint packet_id;

    static const int telemetry_length = sizeof(Telemetry); // Tamanho da mensagem serializada
    com_serialized buffer_sender[telemetry_length];
    com_serialized buffer_receiver[telemetry_length];
    static Telemetry telemetry_received;
};

#endif // COMMUNICATIONRF_H