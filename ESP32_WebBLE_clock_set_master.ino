//*
//*    ESP32 clock --  Current time is set by Browser using WebBLE. 
//*              This code advertises GATT's Current Time service which you can access using Browser. 
//*              When you write current Unix time on the descriptor value,
//*              this value is set on ESP32's RTC, and then a clock displays current time.
//*
#include <BLEDevice.h>
#include <TimeLib.h>
#include <Adafruit_GFX.h>       // To use OLED dispay, install using lib tool
#include <Adafruit_SSD1306.h>   // install using lib tool too

#define LED_BUILTIN 5   // esp32c3 supermini 8 ,  pi pico 25 esp32 2
#define LED_CTL 17      // LED controled
#define LOCAL_NAME "ESP32_2"
#define I2C_SDA      21         // I2C DATA
#define I2C_SCK      22         // I2C CLOCK
#define OLED_I2C_ADDRESS 0x3C   // Check the I2C bus of your OLED device
#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels
#define OLED_RESET -1           // Reset pin # (or -1 if sharing Arduino reset pin)

static BLEUUID CTSserviceUUID("00001805");  // Current time service
static BLEUUID CTScharUUID("00002a2b");     // Current time service characteristic
//#define CTSSUUID "00001805-0000-1000-8000-00805f9b34fb"
//#define CTSCUUID "00002a2b-0000-1000-8000-00805f9b34fb"
static bool connected = false;  // connection is active 
static bool wrote = false;      // onwrite() of decriptorcallback
static char strbuff[24];

BLEServer  *pServer = NULL;
BLEClient  *pClient = NULL;
BLEAddress *pBLEAddress = NULL;
BLEDescriptor *pDescriptor = new BLEDescriptor((uint16_t)0x2901);

const char* time_zone  = "JST-9";
struct tm *tm;
int d_mon ;
int d_mday ;
int d_hour ;
int d_min ;
int d_sec ;
int d_wday ;
static const char *weekStr[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"}; //3文字の英字
const long  gmtOffset_sec = 32400;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class MyDescriptorCallbacks: public BLEDescriptorCallbacks {
  void onWrite(BLEDescriptor *pDesciptor) {
    uint8_t *value = pDescriptor->getValue();
    int vl = pDescriptor->getLength();
    int i;
    wrote = true;
    if (vl >= sizeof(strbuff)) vl = 22;
    Serial.print("***** New value: ");
    memcpy(strbuff, value, vl);
    strbuff[vl] = '\n';
    strbuff[vl+1] = 0;
    Serial.print(strbuff);
  }
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      Serial.print("***** New value: ");
      for (int i = 0; i < value.length(); i++)
        Serial.print(value[i]);
      Serial.println();
    }
  }
};

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer, esp_ble_gatts_cb_param_t *param) {
    pBLEAddress = new BLEAddress(param->connect.remote_bda);
    Serial.printf("MyServerCallbacks Server Connected: %s\n", pBLEAddress->toString().c_str());
    connected = true;
    pServer->getAdvertising()->stop();  // stop Advertise
    Serial.println("MyServerCallbacks Stop Advertising");
  }

  void onDisconnect(BLEServer* pServer) {
    Serial.println("MyServerCallbacks Server Disconnected");
    connected = false;
  }
};

void setup() {
  struct tm tm_init;
  struct timeval tv = { 1710000000 + gmtOffset_sec , 0 };  // initial value is 2024/3/9 16:00 + 9:00
  settimeofday(&tv, NULL);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_CTL, OUTPUT);
  digitalWrite(LED_CTL, LOW);
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial.begin(115200);

  Wire.begin(); // i2C
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS);
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);

  delay(1000);
  splash();

  digitalWrite(LED_BUILTIN, LOW); 
  Serial.println("\nBLEServer");

  BLEDevice::init(LOCAL_NAME);
  BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Service and Characteristic
  BLEService *pService = pServer->createService(CTSserviceUUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
   CTScharUUID,
   BLECharacteristic::PROPERTY_READ |
   BLECharacteristic::PROPERTY_WRITE
  );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Current Time Service");
  // Descriptor
  pDescriptor->setValue("1710032400");
  pDescriptor->setCallbacks(new MyDescriptorCallbacks());
  pCharacteristic->addDescriptor(pDescriptor);
  // start service 
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Start Advertising");

  while (!connected) {
    delay(100);
    dispClock();
  }

}

void splash()
{
  oled.setTextSize(2); // Draw 2X-scale text
  oled.setCursor(0, 0);
  oled.print("Clock");
  oled.setCursor(0, 15);
  oled.print(" by BLE");
  oled.display();
  delay(500);
  oled.setCursor(0, 30);
  oled.print("OLED");
  oled.setCursor(0, 45);
  oled.print("V0.1.0");
  oled.display();
  delay(1000);
}

void dispClock()
{
  char ts[80];
  time_t t = time(NULL);
  tm = localtime(&t);
  d_mon  = tm->tm_mon+1;
  d_mday = tm->tm_mday;
  d_hour = tm->tm_hour;
  d_min  = tm->tm_min;
  d_sec  = tm->tm_sec;
  d_wday = tm->tm_wday;
  //Serial.print("time ");
  sprintf(ts, "%02d-%02d %s", d_mon, d_mday, weekStr[d_wday]);
  //Serial.println(ts);
  oled.setTextSize(2); // Draw 2X-scale text
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print(ts);

  sprintf(ts,"%02d:%02d:%02d",d_hour,d_min,d_sec);
  //Serial.println(ts);
  oled.setCursor(0, 15);
  oled.print(ts);
  oled.display();
}

void loop() {
  dispClock();
  delay(800);
  digitalWrite(LED_BUILTIN, HIGH);   // turn pilot LED on 
  delay(800);                        // wait for a while
  digitalWrite(LED_BUILTIN, LOW);    // turn pilot LED off 
  if (!connected) {  // connection is not active
    pServer->getAdvertising()->start();
    Serial.println("Start Advertising");
    while (!connected) { 
      delay(100);
      dispClock();
    }    
  }
  if (wrote) { // If there is a signal, run it.
    wrote = false;
    if ((strbuff[0] - '0' >= 0) && (strbuff[0] - '9' <= 9)) { // Unix time(sec) ?
      long t_sec = 0;
      String *tstr = new String(strbuff);
      t_sec = tstr->toInt();
      struct timeval tv = { t_sec + gmtOffset_sec, 0 };  // set current time
      settimeofday(&tv, NULL);
    } else { // command input
      if (strbuff[1]=='n') { // on
        digitalWrite(LED_CTL, HIGH); // put on LED
      } else { // other off
        digitalWrite(LED_CTL, LOW);  // put off LED
      }
    }
  }
}