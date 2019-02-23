#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include "DHT.h"
#define Pino_Conexao 3
#define Tipo_Sensor_Temperatura_Umidade DHT22

Adafruit_TSL2561_Unified tsl=Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT,12345);
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
byte servidor[] = {192, 168, 0, 101};
#define portaHTTP 80
EthernetClient client;
DHT Sensor_Temperatura_Umidade(Pino_Conexao, Tipo_Sensor_Temperatura_Umidade);

void configureSensor(void)
{
  tsl.enableAutoRange(true);         
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

void setup(void) {
  Serial.begin(9600);
  Ethernet.begin(mac);
  Sensor_Temperatura_Umidade.begin();
  if(Ethernet.begin(mac) == 0) {
    Serial.println("Falha na conexão");
    Ethernet.begin(mac);
  }
  Serial.print("IP em que esta conectado:");
  Serial.println(Ethernet.localIP());
  if (!tsl.begin())
  {
    Serial.print("TSL2561 nao detectado,verifique a conexao e o endereco I2C");
    while (1);
  }
  configureSensor();
}

void loop(void) {
  float umidade = Sensor_Temperatura_Umidade.readHumidity();
  float temperatura = Sensor_Temperatura_Umidade.readTemperature();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha na Leitura do Sensor!");
    return;
  }

  float indice_calor = Sensor_Temperatura_Umidade.computeHeatIndex(temperatura, umidade, false);
  if(client.connect(servidor, portaHTTP)) {
    client.print("GET /SmartCity/Insere_Temperatura_Umidade.php");
    client.print("?temperatura=");
    client.print(temperatura);
    client.print("&umidade=");
    client.print(umidade);
    client.print("&indice_calor=");
    client.print(indice_calor);
    client.println(" HTTP/1.0");
    client.println("Host: 192.168.0.100");
    client.println("Connection: close");
    client.println();
    client.stop();
  } else {
    Serial.println("Falha ao conectar o Servidor");
    client.stop();
  }
  delay(2000);
  Calcula_Lux();
}

void Calcula_Lux()
{
  sensors_event_t event;
  tsl.getEvent(&event);
  if (event.light)
  {
    if(client.connect(servidor, portaHTTP)) {
    client.print("GET /SmartCity/Insere_Lux.php");
    client.print("?lux=");
    client.print(event.light);
    client.println(" HTTP/1.0");
    client.println("Host: 192.168.0.100");
    client.println("Connection: close");
    client.println();
    client.stop();
  } else {
    Serial.println("Falha ao conectar o Servidor");
    client.stop();
    }
  }
  else
  {
    Serial.println("Sensor overload");
  }
  delay(250);
}
