#define pin1 5
#define pin2 4
#define pin3 14
#define pin4 12
#define pin5 13

class LedBlink {
  public:
    unsigned int maxTempo = 50;
    unsigned int pin;
    
    bool isLedOn = false;
    unsigned int currentIndexArray = 0;

    int beat[20];
    unsigned long waktuSblm; //penghitung jeda antar on dan off
    unsigned long waktuSdh;

  LedBlink(int _pin, int _beat[]){
      for (int i = 0; i < 20; ++i) {
        beat[i] = _beat[i];
      }
      pin = _pin;
      pinMode(pin, OUTPUT);
    }


  void init(){
    // inisiasi waktusblm = 0 di awal sistem dimulai
    waktuSblm = millis();
  }

  void update(){
    /*
      WaktuSdh di awal start itu = 0;
      tiap update ditingkatkan
    */
    waktuSdh = millis();

    // jika selisih sudah melebihi nilai maxtempo yang ditentukan pada array beat, maka waktusblm diupdate jadi waktusblm
    // waktuSblm akan mengupdate terus sampai nilai selisih kembali lebih besar dari maxtempo
    if((waktuSdh-waktuSblm) >= maxTempo){
      waktuSblm = waktuSdh;
      currentIndexArray++;

      // jika indek array sudah mencapai nilai length, maka index kembali ke nol
      if(currentIndexArray == 20){
        currentIndexArray = 0;
      }

      // jika beat = true, maka led on, jika beat = false, maka led off
      if (beat[currentIndexArray] == 1){
        isLedOn = true;
      }
      else{
        isLedOn = false;
      }
    }
  }

  void check(){
    // cek, jika bool led on, maka nyalakan led, jika tidak, matikan led
    if(isLedOn){
      digitalWrite(pin, HIGH);
    }else{
      digitalWrite(pin, LOW);
    }
  }
};
int beat1[] = {1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1};
int beat2[] = {0,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,1};
int beat3[] = {0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0};
int beat4[] = {0,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0};
int beat5[] = {1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0};

LedBlink blink[] = {LedBlink(pin1, beat1), 
                    LedBlink(pin2, beat2), 
                    LedBlink(pin3, beat3), 
                    LedBlink(pin4, beat4), 
                    LedBlink(pin5, beat5)};

void setup() {
  Serial.begin(115200);
  for(int i = 0; i < 5; i++){
    blink[i].init();
  }
}

void loop() {
  for(int i = 0; i < 5; i++){
    blink[i].update();
  }
  for(int i = 0; i < 5; i++){
    blink[i].check();
  }
}