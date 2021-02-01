#include <LiquidCrystal.h>

// başla butonu
#define btnstart A0

// fan
#define fan 7
#define fanters 8

// alarm ledleri
#define yecled A15
#define yphled A14
#define ynitratled A13
#define ysodyumled A12
#define ykalsiyumled A11

// alarm ledleri
#define decled A10
#define dphled A9
#define dnitratled A8
#define dsodyumled A4
#define dkalsiyumled A5

// ekran tanımlaması
LiquidCrystal lcd(34, 35, 36, 38, 39, 40, 41, 42, 43, 44, 45);

void ledYak(char led)
{
  delay(1000);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

void lcdYaz(String text)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
}

int phdata, ecdata, nitratdata, sodyumdata, kalsiyumdata, nemdata;
bool kontrol = true;

void getPHData()
{
  lcdYaz("PH verisi bekleniyor");
  delay(1000);
  phdata = Serial.parseInt();
  delay(1000);
  while (phdata == 0)
  {
    delay(1000);
    lcdYaz("Tekrar PH");
    phdata = Serial.parseInt();
  }
  Serial.print("PH Degeri: ");
  Serial.println(phdata);
  Serial.print("PH Durumu: ");
  delay(1000);
  if (phdata < 30 && phdata < 20)
  {
    Serial.println("Normal");
    lcdYaz("Normal PH");
    delay(1000);
  }
  else if (phdata > 30)
  {
    Serial.println("Yuksek");
    lcdYaz("YUKSEK PH DEGERI");
    ledYak(yphled);
  }
  else
  {
    Serial.println("Dusuk");
    lcdYaz("DUSUK PH DEGERI");
    ledYak(dphled);
  }
}

void getECData()
{
  lcdYaz("Ec verisi bekleniyor");
  ecdata = Serial.parseInt();
  delay(1000);
  while (ecdata == 0)
  {
    lcdYaz("Tekrar EC");
    ecdata = Serial.parseInt();
    delay(1000);
  }
  Serial.print("EC degeri: ");
  Serial.println(ecdata);
  Serial.print("EC durumu: ");
  if (ecdata < 30 && ecdata < 20)
  {
    Serial.println("Normal");
    lcdYaz("Normal EC");
    delay(1000);
  }
  else if (ecdata > 30)
  {
    Serial.println("Yuksek");
    lcdYaz("Yuksek EC");
    ledYak(yecled);
  }
  else
  {
    Serial.println("Dusuk");
    lcdYaz("Dusuk EC");
    ledYak(decled);
  }
}

void getNitratData()
{
  lcdYaz("NITRAT verisi bekleniyor");
  nitratdata = Serial.parseInt();
  delay(1000);
  while (nitratdata == 0)
  {
    lcdYaz("Tekrar NITRAT");
    nitratdata = Serial.parseInt();
    delay(1000);
  }
  Serial.print("NITRAT degeri: ");
  Serial.println(nitratdata);
  Serial.print("NITRAT durumu: ");
  if (nitratdata < 30 && nitratdata < 20)
  {
    Serial.println("Normal");
    lcdYaz("Normal NITRAT");
    delay(1000);
  }
  else if (nitratdata > 30)
  {
    Serial.println("Yuksek");
    lcdYaz("YUKSEK NITRAT");
    ledYak(ynitratled);
  }
  else
  {
    Serial.println("Dusuk");
    lcdYaz("Dusuk NITRAT");
    ledYak(dnitratled);
  }
}

void getSodyumData()
{
  lcdYaz("SODYUM verisi bekleniyor");
  sodyumdata = Serial.parseInt();
  delay(1000);
  while (sodyumdata == 0)
  {
    lcdYaz("Tekrar SODYUM");
    sodyumdata = Serial.parseInt();
    delay(1000);
  }
  Serial.print("SODYUM degeri: ");
  Serial.println(sodyumdata);
  Serial.print("SODYUM durumu: ");
  if (sodyumdata < 30 && sodyumdata < 20)
  {
    Serial.println("Normal");
    lcdYaz("Normal SODYUM");
    delay(1000);
  }
  else if (sodyumdata > 30)
  {
    Serial.println("Yuksek");
    lcdYaz("Yuksek SODYUM");
    ledYak(ysodyumled);
  }
  else
  {
    Serial.println("Dusuk");
    lcdYaz("Dusuk SODYUM");
    ledYak(dsodyumled);
  }
}

void getKalsiyumData()
{
  lcdYaz("KALSIYUM verisi bekleniyor");
  kalsiyumdata = Serial.parseInt();
  delay(1000);
  while (kalsiyumdata == 0)
  {
    lcdYaz("Tekrar KALSIYUM");
    kalsiyumdata = Serial.parseInt();
    delay(1000);
  }
  Serial.print("KALSIYUM degeri: ");
  Serial.println(kalsiyumdata);
  Serial.print("KALSIYUM Durumu: ");
  if (kalsiyumdata < 30 && kalsiyumdata < 20)
  {
    Serial.println("Normal");
    lcdYaz("NORMAL KALSiYUM");
    delay(1000);
  }
  else if (kalsiyumdata > 30)
  {
    Serial.println("Yuksek");
    lcdYaz("YUKSEK KALSiYUM");
    ledYak(ykalsiyumled);
  }
  else
  {
    Serial.println("Dusuk");
    lcdYaz("DUSUK KALSiYUM");
    ledYak(dkalsiyumled);
  }
}

void getNemData()
{
  lcdYaz("Nem verisi bekleniyor");
  nemdata = Serial.parseInt();
  delay(1000);
  while (nemdata == 0)
  {
    lcdYaz("Tekrar Nem");
    nemdata = Serial.parseInt();
    delay(1000);
  }
  Serial.print("Nem degeri: ");
  Serial.println(nemdata);
  Serial.print("Nem Durumu: ");
  if (nemdata < 30 && nemdata < 20)
  {
    Serial.println("Normal");
    lcdYaz("NORMAL Nem");
    // ters fan durdur
    digitalWrite(fanters, HIGH);
    // düz fan durdur
    digitalWrite(fan, LOW);
    delay(1000);
  }
  else if (nemdata > 30)
  {
    Serial.println("Yuksek");
    lcdYaz("YUKSEK NEM");
    // ters fan durdur
    digitalWrite(fanters, HIGH);
    // düz fan çalıştır
    digitalWrite(fan, HIGH);
  }
  else
  {
    Serial.println("Dusuk");
    lcdYaz("DUSUK NEM");
    // düz fan durdur
    digitalWrite(fan, LOW);
    // ters fan çalıştır
    digitalWrite(fanters, LOW);
  }
}

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(btnstart, INPUT);

  pinMode(fan, OUTPUT);
  pinMode(fanters, OUTPUT);

  pinMode(yecled, OUTPUT);
  pinMode(yphled, OUTPUT);
  pinMode(ynitratled, OUTPUT);
  pinMode(ysodyumled, OUTPUT);
  pinMode(ykalsiyumled, OUTPUT);

  pinMode(decled, OUTPUT);
  pinMode(dphled, OUTPUT);
  pinMode(dnitratled, OUTPUT);
  pinMode(dsodyumled, OUTPUT);
  pinMode(dkalsiyumled, OUTPUT);

  // ters fan durdur
  digitalWrite(fanters, HIGH);
  // düz fan durdur
  digitalWrite(fan, LOW);
}

void loop()
{
  lcdYaz("Akilli Tarim");
  delay(100);

  if (digitalRead(btnstart) == 1 && kontrol)
  {
    kontrol = false;
    getPHData();
    getECData();
    getNitratData();
    getSodyumData();
    getKalsiyumData();
    getNemData();
  }
  delay(100);
}
