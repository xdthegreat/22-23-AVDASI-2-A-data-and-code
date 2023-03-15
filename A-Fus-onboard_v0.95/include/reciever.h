#ifndef _reciever_h_
#define _reciever_h_

//include <config.h>

#include <SPI.h>
#include <RH_RF69.h>

// Change to 434.0 or other frequency, must match RX's freq!
class RADIO {
    private:
        static const float RF69_FREQ = 915.0;
        static const int RFM69_RST = 3;
        static const int RFM69_CS = 10;
        static const int RFM69_INT = digitalPinToInterrupt(2);
        static const int MAX_SEND = 3;
        
        RH_RF69 rf69;
        uint8_t buf[5];
        uint8_t len = sizeof(buf);
    public:
        char *flag = (char *)&buf[4];
        float *data = (float *)&buf;
        bool receive();
        bool send(char flag_send, float data_send);
        void begin();
        float read(char flag);
};

void RADIO::begin(){
    pinMode(RFM69_RST, OUTPUT);
    digitalWrite(RFM69_RST, LOW);

    // manual reset
    digitalWrite(RFM69_RST, HIGH);
    delay(10);
    digitalWrite(RFM69_RST, LOW);
    delay(10);

    if (!rf69.init()) {
        Serial.println("RFM69 radio init failed");
    }
    // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
    // No encryption
    if (!rf69.setFrequency(RF69_FREQ)) {
        Serial.println("setFrequency failed");
    }
    Serial.println("RFM69 radio init OK!");

    rf69.setTxPower(20, true);  // range from 14-20 for power, 2nd arg must be true for 69HCW
}

bool RADIO::receive(){
    *flag = 'F';
    if(rf69.available()){
        if (rf69.recv(buf, &len)) {


            rf69.send((uint8_t *)buf, len);
            rf69.waitPacketSent();
            rf69.setModeRx();
            return true;
        }
    }
    return false;
}
bool RADIO::send(char flag_send, float data_send){
    *flag = flag_send;
    //Serial.print(*flag);
    *data = data_send;
    //Serial.print(*data);
    //*data = aa;
    for(int i = 0; i < 1; i++)
    {
        rf69.send((uint8_t *)buf, len);
        rf69.waitPacketSent();
        if (rf69.waitAvailableTimeout(5))  {
            uint8_t buf_check[5];
            uint8_t len_check = sizeof(buf_check);
            Serial.print("in");
            // Should be a reply message for us now   
            if (rf69.recv(buf_check, &len_check)) {
                if (buf_check[0] == buf[0]) {
                    Serial.print("Transmit Success");
                    return true;
                }
                else continue;
            } 
        }
    }
    //Serial.print("Transmit f\n");
    return false;
}

float RADIO::read(char flag){
    if(flag == 'A'){
        return *data;
    }
}

RADIO radio;

#endif