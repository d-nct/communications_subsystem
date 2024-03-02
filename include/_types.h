#ifndef _TYPES_H
#define _TYPES_H

#include "config.h"

#include <stdint.h>

/* Tipos de Sistema */
/* ---------------- */
/* Para o Log */
typedef enum {
  LOG_ERROR,
  LOG_WARNING,
  LOG_INFO,
  LOG_DEBUG
} LogLevel_t;

/* Status Feedback */
typedef enum {
  PACKET_GOOD = 0,   // 75-100%
  PACKET_NORMAL,     // 50-75%
  PACKET_WARNING,    // 25-50%
  PACKET_CRITICAL,   // 5-25%
  PACKET_NO_SIGNAL   // 0%
} RF_Packet_Status_t;

typedef enum {
  RSSI_GOOD = 0, 
  RSSI_NORMAL,
  RSSI_WARNING,
  RSSI_CRITICAL,
  RSSI_NO_SIGNAL
} RF_RSSI_Status_t;


/* Configurações de Telemetria */
/* --------------------------- */

/* Padronização dos Tipos */
typedef uint32_t                  com_uint;
typedef int32_t                   com_int;
typedef float                     com_float;
typedef double                    com_double;
typedef uint8_t                   com_serialized;

/* Pacote de Telemetria */
#pragma pack(push, 1) // Para que o alinhamento padrão seja de 1 byte. O compilador tá proibído de mudar isso, colocar bytes no meio etc
typedef struct {
    com_uint  id;
    com_uint  timestamp; 
    com_float latitude;  
    com_float longitude;  
    com_float altitude;
    com_float speed;
    com_float satellites;
    com_float voltage;
    com_float temperature;
} Telemetry;
#pragma pack(pop)

#endif // _TYPES_H