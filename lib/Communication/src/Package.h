#ifndef PACKAGE_H
#define PACKAGE_H

#include "_config.h"
#include "_types.h"
#include "Logger.h"

#include <cstring>

class Package {
public:
    /**
     * Serializa a mensagem.
     * 
     * @param message A mensagem a ser serializada.
     * @param lenght O tamanho da mensagem.
    */
    static com_serialized* serialize(const Telemetry& data, com_serialized* serializedData);

    /**
     * Deserializa a mensagem.
     * 
     * TODO: repensar essa coisa de retornar um objeto novo. 
     * 
     * @param serializedData A mensagem a ser deserializada.
    */
    static Telemetry deserialize(const com_serialized* serializedData);

    /**
     * Imprime a telemetria no nível LOG_INFO.
     * 
     * @param telemetry A telemetria a ser impressa.
    */
    static void printTelemetry(const Telemetry& telemetry);
};

#endif // PACKAGE_H