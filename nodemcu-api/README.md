# API utilizando NodeMCU

Tutorial de como criar uma API REST simples utilizando a plataforma NodeMCU como uma estacão meteorológica.  
**Autor**: Matheus Lemos<<matheuslemosf@protonmail.com>>

## Componentes eletrônicos

* NodeMCU com esp8266
* Sensor de umidade e temperatura DHT22
* Led vermelho
* Led verde
* 5 fios "jumper"
* 2 protoboards pequenas
* 1 resistor 10K

## Ferramentas

* Arduino IDE
* Biblioteca ArduinoJson5
* Biblioteca ESP8266WiFi.h
* Biblioteca DHT22.h

## Montagem

A montagem deve ser feita de acordo com o apresentado na imagem abaixo:  

IMAGEM

## Código

Para executar o programa basta copiar a pasta para a sua pasta **Arduino** e executar com o Arduino IDE

	cp -R api/ $HOME/Arduino/

## Referências

[Arduino IDE](https://www.arduino.cc/en/main/software)  
[ArduinoJSON 5 Documentation](https://arduinojson.org/v5/doc/)
	
