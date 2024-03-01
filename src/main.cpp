/* Includes */
#include "_config.h"
#include "_types.h"

/* Bibliotecas */
#include "CommunicationRF.h"
#include "MonitorRF.h"
#include "Package.h"
#include "Logger.h"

/* Declaração dos Objetos */
ComRF comm;
Telemetry telemetry_sender;
ulong clk = 0;

void setup() {
  comm.setup(); // Inicializa o LoRa
}

void loop() {
  /* Rotina de TX */
  if (millis() - clk > LORA_INTERVAL) {
    comm.configurePacket(telemetry_sender); // Configura o pacote com o ID e timestamp
    comm.sendPacket(telemetry_sender); // Envia o pacote
    clk = millis();
  }

  /* Rotina de RX */
  Telemetry* received = comm.receivePacket(); // Recebe o pacote
  if (received != NULL) {
    Package::printTelemetry(*received); // Logga o pacote recebido
  }

  /* Monitoramento */
  MonitorRF::monitor();
}