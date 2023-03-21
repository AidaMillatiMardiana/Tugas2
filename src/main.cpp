    #include <Arduino.h>
    #include <SimpleDHT.h>

    #define pinDHT 7 // SD3 pin signal sensor DHT
    #define RED_LED D2
    #define GREEN_LED D5
    #define BLUE_LED D6
    

    byte temperature = 0;
    byte humidity = 0;

    SimpleDHT11 dht11(D1); //instan sensor dht11

    void printTemperature(float tempc)
    {
        float tempR = tempc * 0.8; // konversi ke reamur
        float tempK = tempc + 273.15; // konversi ke reamur
        
        Serial.print("Temperature: ");
        Serial.print(tempc);
        Serial.print(" *C, ");
        Serial.print(tempR);
        Serial.print(" *R. ");
        Serial.print(tempK);
        Serial.print(" *K. ");
        
    }
    void KelembabanSuhu()
    {
        int err = SimpleDHTErrSuccess;

        if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
        {
            Serial.print("Pembacaan DHT11 gagal, err=");
            Serial.println(err);
            delay(1000);
            return;
        }

        Serial.print("Sample OK: ");
        printTemperature((float)temperature);

        Serial.print((int)humidity);
        Serial.println(" H");

        // Kategori suhu berdasarkan rentang nilai suhu
        if (temperature <= 20) {
          digitalWrite(GREEN_LED, HIGH);
          digitalWrite(BLUE_LED, LOW);
          digitalWrite(RED_LED, LOW);
          Serial.println("Kategori Suhu: Dingin");
          delay(1500);
        } else if (temperature > 20 && temperature < 30) {
          digitalWrite(GREEN_LED, LOW);
          digitalWrite(BLUE_LED, HIGH);
          digitalWrite(RED_LED, LOW);
          Serial.println("Kategori Suhu: Normal");
          delay(1500);
        } else {
          digitalWrite(GREEN_LED, LOW);
          digitalWrite(BLUE_LED, LOW);
          digitalWrite(RED_LED, HIGH);
          Serial.println("Kategori Suhu: Panas");
          delay(1500);
        }
        delay(1500);
    }

    void setup()
    {
        Serial.begin(115200);
        Serial.println("Simple DHT");
        pinMode(RED_LED, OUTPUT);
        pinMode(BLUE_LED, OUTPUT);
        pinMode(GREEN_LED, OUTPUT);
        delay(1000);
    }

    void loop()
    {
        KelembabanSuhu();
    }