#include <SFE_MMA8452Q.h>
#include <Ethernet.h>

MMA8452Q accel;

const int button1 = 2;
int button1State = 0;
const int button2 = 3;
int button2State = 0;

EthernetClient client;

// Arduino MAC and IP Address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte arduino[] = { 172, 16, 115, 77 };

// Server IP
byte ip[] = { 172, 16, 200, 37 };

void setup() {
  Ethernet.begin(mac, arduino);
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  accel.init(SCALE_8G);
}

void loop() {  
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);

  // Se o botão for pressionado, enviar mensagem de emergência
  if (button1State == HIGH && button2State == HIGH){
    sendEmergencyMessage();
  }
  
  if (accel.available()) {
    accel.read();
    
    // Detecção de queda
    if (accel.cy > 2.5) {
      sendEmergencyMessage();
    }
  }
}

void sendEmergencyMessage() {
    
  Serial.println("Conectando...");

  // Tentativa de conexão com o servidor
  if (client.connect(ip, 8080)) {
    Serial.println("Conectado");

    // Requisição GET ao servidor
    client.println("GET /");
    client.println();

    // Aguardando envio da requisição
    delay(1000);

    Serial.println("Mensagem enviada");
    
    client.stop();
    
    Serial.println("Desconectado");
  } else {
    Serial.println("Falha na conexão");
  }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
