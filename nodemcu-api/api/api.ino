#include <ESP8266WiFi.h>
#include "DHT.h"
#include <ArduinoJson.h>

#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define DHTPIN 4 // GPIo4 ou porta D2 do NodeMCU
#define REDLED 14 // GPIO14 ou porta D5 do NodeMCU
#define GREENLED 12 // GPIO12 ou porta D6 do NodeMCU

// Redes possíveis
StaticJsonBuffer<200> networkBuffer;
String networkObject = "{"
  "\"network1\": \"password1\","
  "\"network2\": \"password2\""
"}";
JsonObject& networks = networkBuffer.parseObject(networkObject);

// Buffer de saída
char output[256];

// Sensor de umidade e temperatura
DHT dht(DHTPIN, DHTTYPE,11);

// Requisicoes http
WiFiServer server(80);

/*
 * Adiciona os headers e formata a requisicão
*/
String printJson(String object) {
  String result = 
    String("HTTP/1.1 200 OK\r\n") +
      "Content-Type: application/json\r\n" +
      "Connection: close\r\n" +
      "\r\n" +
      object +
      "\r\n";
    return result;
}

/*
 * Pega o output dos sensores e formata em JSON
*/
String getSensorData() {
  String output;
  String strHum;
  String strTemp;
  float t,h;
  
  // Le os dados dos sensores
  t = dht.readTemperature();
  h = dht.readHumidity();

  // Formata os dados em json
  StaticJsonBuffer<100> tempBuffer;
  StaticJsonBuffer<100> humBuffer;
  StaticJsonBuffer<200> arrBuffer;
  JsonObject& temp = tempBuffer.createObject();
  JsonObject& hum = humBuffer.createObject();
  JsonArray& info = arrBuffer.createArray();

  temp["key"] = "temperature";
  temp["value"] = t;
  temp["scale"] = "ºC";
  
  hum["key"] = "humidity";
  hum["value"] = h;
  hum["scale"] = "%";

  info.add(temp);
  info.add(hum);
  
  info.printTo(output);
  String result = printJson(output);
  
  return result;
}

void setup() {
  // Leds indicadores
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  
  Serial.begin(115200);
  Serial.setTimeout(10);

  String ssid, password;
//  const char* password;
  
  int numberOfNetworks = WiFi.scanNetworks();
  for (int i = 0; i < numberOfNetworks; i++) {
    if (networks.containsKey(WiFi.SSID(i))) {
        ssid = WiFi.SSID(i);
        password  = networks[ssid].as<String>();
    }
  }
  

  Serial.print("Conectando a ");
  Serial.print(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

    digitalWrite(GREENLED, LOW);
    digitalWrite(REDLED, HIGH);
  }
  Serial.println("");
  Serial.print("Conectado a rede sem fio ");
  Serial.println(ssid);
  server.begin();
  Serial.println("Servidor iniciado");
   
  Serial.print("IP para se conectar ao NodeMCU: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  dht.begin();

  digitalWrite(GREENLED, HIGH);
  digitalWrite(REDLED, LOW);
}



void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Recebe a conexão e realiza o parse
  if (client) {
    boolean currentLineIsBlank = true;
    Serial.println("[Client connected]");
    while(client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        client.flush();
        if (c == '\n' && currentLineIsBlank) {
          String result = getSensorData();
          Serial.print(result);
          client.print(result);
          break;
        }
      }
    }
  }

  delay(1);
  Serial.println("[Client disconnected]\n");
  
}
