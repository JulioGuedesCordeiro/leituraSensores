#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

WiFiServer server(80);
const char *nome_rede = "SmartHome";
const char *senha_rede = "julioguedes12";
const char *host = "192.168.1.9";

void configuracao()
{
    IPAddress staticIP(192, 168, 1, 11);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.mode(WIFI_STA);
    WiFi.config(staticIP, gateway, subnet);
    WiFi.begin(nome_rede, senha_rede);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(200);
        Serial.print(".");
    }
};

void setup()
{
    Serial.begin(115200);
    delay(10);
    configuracao();
    server.begin();
    Serial.println("Ip do Equipamento: ");
    Serial.print(WiFi.localIP());
}

String lerChamada()
{
    WiFiClient client = server.available();
    if (!client)
    {
        return "";
    }
    while (!client.available())
    {
        delay(1);
    }
    String request = client.readStringUntil('\r');
    request = request.substring(request.indexOf("/") + 1, request.indexOf("HTTP") - 1);
    client.flush();
    return request;
};

void loop()
{
    String request = lerChamada();
    float leitura;
    if (request != "")
    {
        if (request == "temperatura")
        {
            leitura = lerTemperatura();
        }
        else if (request == "umidade")
        {
            leitura = lerUmidade();
        }
        else if (request == "lux")
        {
            leitura = lerLux();
        }
        gravaBanco(request, leitura);
    }
};

void gravaBanco(String controller, float leitura)
{
    WiFiClient client;
    String url = "http://192.168.1.9:3000/api/";
    String rota = url + controller + "/" + leitura;
    const int httpPort = 3000;
    if (!client.connect(host, httpPort))
    {
        Serial.println("Falha ao conectador o servidor");
        return;
    }
    client.print(String("POST ") + rota + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    while (client.available())
    {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }
    client.print("HTTP/1.1 200 OK\n\n");
    client.flush();
};

float lerTemperatura()
{
    return 1;
};

float lerUmidade()
{
    return 2;
};

float lerLux()
{
    return 3;
};