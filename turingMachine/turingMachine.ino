#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>



int inputzero = 2;
int inputone = 3;
int inputtwo = 4;
int inputthree = 5;
int val0 = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;
String message;
char buffer[50];

void setup() {
  // put your setup code here, to run once:
  pinMode(inputzero, INPUT);
  pinMode(inputone, INPUT);
  pinMode(inputtwo, INPUT);
  pinMode(inputthree, INPUT);
  Serial.begin(9600);
  //Serial.print((int)'a');
  //Serial.print(binconvert('a'));
}

void loop() {
  // put your main code here, to run repeatedly:
  val0 = digitalRead(inputzero);
  val1 = digitalRead(inputone);
  val2 = digitalRead(inputtwo);
  val3 = digitalRead(inputthree);
  String pad = String(val0) + String(val1) + String(val2) + String(val3);
  
  if (Serial.available()){
    Serial.println(pad);
    message = Serial.readString();
    Serial.println(message); 
    String binmessage = convert(message);
    Serial.println(binmessage);
    String crypt = encrypt(pad, binmessage);
    Serial.println(crypt);
    String fencrypt = binToString(crypt);
    Serial.println(fencrypt);
  }
  //delay(1000);
}

String encrypt(String pad, String message){
  while (pad.length() < message.length()){
    pad = pad + pad;
  }
  
  String encrypted = "";
  for(unsigned int i = 0; i<message.length(); i++) {
    encrypted = encrypted + String(message[i] xor pad[i]);
  }
  String wehatearduinoide = "";
  for(unsigned int j = 0; j<encrypted.length()-2; j++){
    wehatearduinoide = wehatearduinoide + encrypted[j];
  }

  return (wehatearduinoide);
}

String convert(String message){
 String binMessage = "";
 for(unsigned int i = 0; i<message.length(); i++){
  binMessage = binMessage + binconvert(message[i]); 
 }
 return (binMessage);
}

String binconvert(char c){
  int num = (int)c;
  return binary(num);
}

String binary(int num){
  if (num == 0){
    return ("");
  }
  else{
    return (binary(num/2) + String(num%2));
  }
}

String binToString(String s){
  int len = s.length()/8;
  String finalString = ""; 
  for(unsigned int i = 0; i<len; i++){
    String str = "";
    for(unsigned int j = 0; j<8; j++){
       str = str + s[j];
    }
    finalString = finalString + binToChar(str);
  }
  return (finalString);
}

String binToChar(String s){
  int num = binToNum(s);
  char c = (char)num;
  return (String(c));
}

int binToNum(String s){
  int num = 0;
  for(unsigned int i = 0; i < 8; i++){
    if(s[i] == '1'){
      num = num + (2^i);
    }
  }
  return (num);
}
