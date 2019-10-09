//BLOCK LIBRARY
#include <LiquidCrystal_I2C.h> //Untuk memasukan Library sebagai pengendali LCD
#include <DHT.h>
//______________________//

//INISIALISASI
int pinSensorApi=A0; // Inisialiasasi Sensor api terpasang di A0 Arduino
int pinSensorGas=A1; // Inisialiasasi Sensor Gas terpasang di A1 Arduino
int ledMerah=13;  //Indikator Sensor  Ketika Mendeteksi Api
int ledKuning=12; //Indikator Sensor  Ketika Mendeteksi GAS
int ledHijau=11;  //Indikator Sensor  Ketika Kelembaban melebihi batas
int buzzer=10;    //Indikator Sensor  Ketika Suhu melebihi batas
int DHTPIN=2;   //Inisialisasi Sensor DHT11 dipasang pada pin Digital 2 Arduino
int DHTTYPE=DHT11; //Type Sensor DHT yang digunakan yaitu DHT11

LiquidCrystal_I2C lcd(0x27, 16,2); //Konfigurasi Untuk LCD_I2C diganti menjadi lcd
DHT dht(DHTPIN,DHTTYPE); //Konfigurasi Sensor DHT
//______________________//

void setup() {
  //MEMANGGIL FUNGSI & MENENTUKAN FUNGSI
  Serial.begin(9600); //Memamnggil FUngsi Serial pada BAUDRATE 9600
  lcd.begin(); //Memamnggil FUngsi LCD pada komunikasi SPI (SDA & SCL)
  dht.begin(); //Memamnggil FUngsi DHT 
  pinMode(ledMerah,OUTPUT); //di fungsikan sebagai OUTPUT / KELUARAN
  pinMode(ledKuning,OUTPUT); //di fungsikan sebagai OUTPUT / KELUARAN
  pinMode(ledHijau,OUTPUT); //di fungsikan sebagai OUTPUT / KELUARAN
  pinMode(buzzer,OUTPUT); //di fungsikan sebagai OUTPUT / KELUARAN
  selamatdatang();  // VOID untuk menampilkan data ketika sistem pertama kali dijalankan
}


void loop() {
  //PEMBACAAN SENSOR DAN DEKLARASI SENSOR
  int dataApi=digitalRead(pinSensorApi); // Membaca Nilai DIgital 0 atau 1
  int dataGas=analogRead(pinSensorGas); // Membaca Nilai Analog 0 s/d 1024
  dataGas=map(dataGas,100,950,0,100); // Merubah Nilai pada Sensor
          //(Ambil Data,Nilai Awal, Nilai Ahir, Hasil Awal, Hasil Ahir);
          if(dataGas<1){ //Untuk mengubah data Gas ketika nilai (-) Minus
            dataGas=0;
          }
  int suhu=dht.readTemperature();
  int kelembaban=dht.readHumidity();
  
  //BLOCK PRINT DATA KE SERIAL & LCD
  Serial.print("DATA API :");Serial.print(dataApi);
  Serial.print(" | DATA GAS :");Serial.print(dataGas);Serial.println(" %");
  Serial.print("DATA SUHU :");Serial.print(suhu);Serial.print(" C");
  Serial.print(" | DATA KELEMBABAN :");Serial.print(kelembaban);
  Serial.println(" %");
  
  //LCD BARIS 1
  lcd.clear();
        if(dataApi==1){
          lcd.setCursor(4,0);lcd.print("OK");
        }else{
          lcd.setCursor(4,0);lcd.print("HT2");
        }
  lcd.setCursor(0,0);lcd.print("API:"); 
  lcd.setCursor(8,0);lcd.print("GAS:");
  lcd.setCursor(12,0);lcd.print(dataGas);
  lcd.setCursor(15,0);lcd.print("%");
  
  //LCD BARIS 2
  lcd.setCursor(0,1);lcd.print("TEM:"); 
  lcd.setCursor(4,1);lcd.print(suhu);
  lcd.setCursor(8,1);lcd.print("HUM:");
  lcd.setCursor(12,1);lcd.print(kelembaban);
  lcd.setCursor(15,1);lcd.print("%");
  delay(500);
  //___________________________//

  //LOGIKA PROGRAM
    //API
    if (dataApi==0){
      digitalWrite(ledMerah,HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("INFORMASI!!");
      lcd.setCursor(0,1);
      lcd.print("API TERDETEKSI!!");
      delay(2000);
    }else{
      digitalWrite(ledMerah,LOW);
 
    } 
    //GAS
    if(dataGas>50){
      digitalWrite(ledKuning,HIGH);
    } else{
      digitalWrite(ledKuning,LOW);
    }
    //SUHU
    if(suhu>34){
      digitalWrite(buzzer,HIGH);
    } else{
      digitalWrite(buzzer,LOW);
    }
    //KELEMBABAN
    if(kelembaban>80){
      digitalWrite(ledHijau,HIGH);
    } else{
      digitalWrite(ledHijau,LOW);
    }
  
}

void selamatdatang(){
  //LCD TAMPIL SELAMAT DATANG dan BUZZER
  lcd.setCursor(0,0);
  lcd.print("SELAMAT DATANG!!");
  lcd.setCursor(0,1);
  lcd.print("DISIST EM MONITOR");
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(100);
  digitalWrite(buzzer,HIGH);
  delay(100);
  digitalWrite(buzzer,LOW);
  delay(100);
}
