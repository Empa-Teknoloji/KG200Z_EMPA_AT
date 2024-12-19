# AT Komutları Dökümanı


### RETURN MESSAGE

- **Açıklama:** Geri dönüş mesajları (Return Message) genel olarak :
- Örnek :

```
Başarılı ise  = AT+OK
Başarısız ise = AT+ERROR
```

**AT?**

- **Açıklama:** Kullanılabilir tüm AT komutlarını listeler.
- **Örnek Kullanım:**
    
    ```
    AT?
    ```
    

### **AT+?**

- **Açıklama:** Belirli bir komut için yardım bilgisi verir.
- **Örnek Kullanım:**
    
    ```
    AT+<CMD>?
    ```
    

### **AT+=?**

- **Açıklama:** Mevcut değeri sorgular.
- **Örnek Kullanım:**
    
    ```
    AT+<CMD>=?
    
    ```
    

### **AT+VER**

- **Açıklama:** Cihaz yazılım versiyonunu sorgular.
- **Örnek Kullanım:**
    
    ```
    AT+VER
    
    ```
    

### **AT+VL**

- **Açıklama:** Detay seviyesi ayarı yapar veya sorgular.
    - **0:** Kapalı
    - **1:** Düşük detay seviyesi
    - **2:** Orta detay seviyesi
    - **3:** Yüksek detay seviyesi
- **Örnek Kullanım:**
    
    ```
    AT+VL=3
    
    ```
    

### **AT+LTIME**

- **Açıklama:** Yerel zamanı UTC formatında sorgular.
- **Örnek Kullanım:**
    
    ```
    AT+LTIME
    
    ```
    

### **ATZ**

- **Açıklama:** Mikrodenetleyiciyi sıfırlar.
- **Örnek Kullanım:**
    
    ```
    ATZ
    
    ```
    

### **AT+RFS**

- **Açıklama:** EEPROM fabrika ayarlarını geri yükler.
- **Örnek Kullanım:**
    
    ```
    AT+RFS
    
    ```
    

### **AT+CS**

- **Açıklama:** Mevcut bağlamı EEPROM'a kaydeder.
- **Örnek Kullanım:**
    
    ```
    AT+CS
    
    ```
    

### **AT+APPEUI**

- **Açıklama:** Uygulama EUI'sini alır veya ayarlar.
- **Örnek Kullanım:**
    
    ```
    AT+APPEUI=<XX:XX:XX:XX:XX:XX:XX:XX>
    
    ```
    

### **AT+NWKKEY**

- **Açıklama:** Ağ anahtarını alır veya ayarlar.
- **Örnek Kullanım:**
    
    ```
    AT+NWKKEY=<XX...XX>
    
    ```
    

### **AT+APPKEY**

- **Açıklama:** Uygulama anahtarını alır veya ayarlar.
- **Örnek Kullanım:**
    
    ```
    AT+APPKEY=<XX...XX>
    
    ```
    

### **AT+NWKSKEY**

- **Açıklama:** Ağ oturumu anahtarını alır veya ayarlar.
- **Örnek Kullanım:**
    
    ```
    AT+NWKSKEY=<XX...XX>
    
    ```
    

### **AT+APPSKEY**

- **Açıklama:** Uygulama oturumu anahtarını alır veya ayarlar.
- **Örnek Kullanım:**
    
    ```
    AT+APPSKEY=<XX...XX>
    
    ```
    

### **AT+DADDR**

- **Açıklama:** Cihaz adresini alır veya ayarlar.
- **Örnek Kullanım:**
    
    ```
    AT+DADDR=<XXXXXXXX>
    
    ```
    

### **AT+DEUI**

- **Açıklama:** Cihaz EUI'sini alır veya ayarlar.
- **Örnek Kullanım:**
    
    ```
    AT+DEUI=<XX:XX:XX:XX:XX:XX:XX:XX>
    
    ```
    

### **AT+NWKID**

- **Açıklama:** Ağ ID'sini alır veya ayarlar. Geçerli aralık: 0..127.
- **Örnek Kullanım:**
    
    ```
    AT+NWKID=<NwkID>
    
    ```
    

### **AT+JOIN**

- **Açıklama:** Ağa katılım işlemini başlatır.
    - **0:** ABP modunda katılım
    - **1:** OTAA modunda katılım
- **Örnek Kullanım:**
    
    ```
    AT+JOIN=1
    
    ```
    

### **AT+LINKC**

- **Açıklama:** Bir bağlantı kontrolü talebi ekler.
- **Örnek Kullanım:**
    
    ```
    AT+LINKC
    
    ```
    

### **AT+SEND**

- **Açıklama:** Uygulama portu ve onay bilgisi ile ikili veri gönderir.
    - **Port:** 1..199
    - **Ack:** 0 (onaysız), 1 (onaylı)
- **Örnek Kullanım:**
    
    ```
    AT+SEND=<Port>:<Ack>:<Payload>
    
    ```
    

### **AT+ADR**

- **Açıklama:** Adaptif veri hızını etkinleştirir veya devre dışı bırakır.
    - **0:** Adaptif veri hızı kapalı
    - **1:** Adaptif veri hızı açık
- **Örnek Kullanım:**
    
    ```
    AT+ADR=1
    
    ```
    

### **AT+DR**

- **Açıklama:** Veri hızını alır veya ayarlar. Geçerli aralık: 0..7.
- **Örnek Kullanım:**
    
    ```
    AT+DR=5
    
    ```
    

### **AT+BAND**

- **Açıklama:** Bant genişliğini alır veya ayarlar.
    - **0:** AS923
    - **1:** AU915
    - **2:** CN470
    - **3:** CN779
    - **4:** EU433
    - **5:** EU868
    - **6:** KR920
    - **7:** IN865
    - **8:** US915
    - **9:** RU864
- **Örnek Kullanım:**
    
    ```
    AT+BAND=5
    
    ```
    

### **AT+CLASS**

- **Açıklama:** LoRaWAN cihaz sınıfını alır veya ayarlar.
    - **A:** Sınıf A
    - **B:** Sınıf B
    - **C:** Sınıf C
- **Örnek Kullanım:**
    
    ```
    AT+CLASS=A
    
    ```
    

### **AT+DCS**

- **Açıklama:** ETSI Duty Cycle'ı etkinleştirir/devre dışı bırakır. Sadece test için kullanılmalıdır.
    - **0:** Devre dışı
    - **1:** Etkin
- **Örnek Kullanım:**
    
    ```
    AT+DCS=1
    
    ```
    

### **AT+JN1DL**

- **Açıklama:** RX1 penceresi için gecikme ayarı. Gecikme değeri milisaniye cinsindendir.
- **Örnek Kullanım:**
    
    ```
    AT+JN1DL=1000
    
    ```
    

### **AT+JN2DL**

- **Açıklama:** RX2 penceresi için gecikme ayarı. Gecikme değeri milisaniye cinsindendir.
- **Örnek Kullanım:**
    
    ```
    AT+JN2DL=2000
    
    ```
    

### **AT+RX1DL**

- **Açıklama:** TX'den sonra RX1 penceresi başlangıç gecikmesi. Gecikme değeri milisaniye cinsindendir.
- **Örnek Kullanım:**
    
    ```
    AT+RX1DL=1000
    
    ```
    

### **AT+RX2DL**

- **Açıklama:** TX'den sonra RX2 penceresi başlangıç gecikmesi. Gecikme değeri milisaniye cinsindendir.
- **Örnek Kullanım:**
    
    ```
    AT+RX2DL=2000
    
    ```
    

### **AT+RX2DR**

- **Açıklama:** RX2 penceresi için veri hızı. Geçerli aralık: 0..7.
- **Örnek Kullanım:**
    
    ```
    AT+RX2DR=3
    
    ```
    

### **AT+RX2FQ**

- **Açıklama:** RX2 penceresi için frekans ayarı (Hz).
- **Örnek Kullanım:**
    
    ```
    AT+RX2FQ=869525000
    
    ```
    

### **AT+TXP**

- **Açıklama:** Gönderim gücü ayarları. Geçerli aralık: 0..15 (bölgeye bağlı).
- **Örnek Kullanım:**
    
    ```
    AT+TXP=10
    
    ```
    

### **AT+PGSLOT**

- **Açıklama:** Unicast ping slot periyodunu alır veya ayarlar.
    - **0:** 1 saniye
    - **1:** 2 saniye
    - **...**
    - **7:** 128 saniye
- **Örnek Kullanım:**
    
    ```
    AT+PGSLOT=4
    
    ```
    

### **AT+TTONE**

- **Açıklama:** RF Tone testi başlatır.
- **Örnek Kullanım:**
    
    ```
    AT+TTONE
    
    ```
    

### **AT+TRSSI**

- **Açıklama:** RSSI ölçüm testi başlatır.
- **Örnek Kullanım:**
    
    ```
    AT+TRSSI
    
    ```
    

### **AT+TCONF**

- **Açıklama:** RF test konfigürasyon ayarları yapar.
- **Örnek Kullanım:**
    
    ```
    AT+TCONF=868000000:14:50000:50000:4/5:0:0:0:16:25000:2:3
    
    ```
    

### **AT+TTX**

- **Açıklama:** RF iletim testi başlatır. Gönderilecek paket sayısını belirler.
- **Örnek Kullanım:**
    
    ```
    AT+TTX=10
    
    ```
    

### **AT+TRX**

- **Açıklama:** RF alım testi başlatır. Beklenen paket sayısını belirler.
- **Örnek Kullanım:**
    
    ```
    AT+TRX=10
    
    ```
    

### **AT+TTH**

- **Açıklama:** RF geçiş testi başlatır.
- **Örnek Kullanım:**
    
    ```
    AT+TTH=868000000,869000000,5000,10
    
    ```
    

### **AT+TOFF**

- **Açıklama:** RF testi durdurur.
- **Örnek Kullanım:**
    
    ```
    AT+TOFF
    
    ```
    

### **AT+AUTOJOIN**

- **Açıklama:** LoRaWAN sertifikasyon test modunu başlatır.
    - **0:** ABP modunda
    - **1:** OTAA modunda
- **Örnek Kullanım:**
    
    ```
    AT+AUTOJOIN=1
    
    ```
    

### **AT+BAT**

- **Açıklama:** Pil seviyesini mV olarak sorgular.
- **Örnek Kullanım:**
    
    ```
    AT+BAT
    
    ```
    

### **AT+DISC**

- **Açıklama:** LoRaWAN ağından bağlantıyı keser.
- **Örnek Kullanım:**
    
    ```
    AT+DISC
    
    ```
    

### **AT+LORASTAT**

- **Açıklama:** Lora Network durumunu sorgular.
    - **0:** Katılmadı
    - **1:** Katıldı
- **Örnek Kullanım:**
    
    ```
    AT+**LORA**STAT
    
    ```
    

### **AT+TIMERSTART**

- **Açıklama:** Belirtilen zamanlayıcıyı başlatır.
    - **timerN:** Zamanlayıcı numarası (0-3)
- **Örnek Kullanım:**
    
    ```
    AT+TIMERSTART=0
    
    ```
    

### **AT+TIMERSTOP**

- **Açıklama:** Belirtilen zamanlayıcıyı durdurur.
    - **timerN:** Zamanlayıcı numarası (0-3)
- **Örnek Kullanım:**
    
    ```
    AT+TIMERSTOP=0
    
    ```
    

### **AT+TIMERCONF**

- **Açıklama:** Belirtilen zamanlayıcıyı yapılandırır.
    - **timerN:** Zamanlayıcı numarası (0-3)
    - **period:** Periyot süresi (ms)
- **Örnek Kullanım:**
    
    ```
    AT+TIMERCONF=0,1000
    
    ```
    

### **AT+GETTEMP**

- **Açıklama:** ADC değerini alır (sıcaklık).
- **Örnek Kullanım:**
    
    ```
    AT+GETTEMP
    
    ```
    

### **AT+TEMPSEND**

- **Açıklama:** Periyodik sıcaklık gönderimini başlatır.
    - **period:** Gönderim periyodu (ms)
- **Örnek Kullanım:**
    
    ```
    AT+TEMPSEND=5000
    
    ```
    

### **AT+I2CSCAN**

- **Açıklama:** I2C veri yolundaki aktif cihazları tarar.
- **Örnek Kullanım:**
    
    ```
    AT+I2CSCAN
    
    ```
    

### **AT+I2CREAD**

- **Açıklama:** Belirtilen cihaz adresinden ve kayıt adresinden veri okur.
- **Örnek Kullanım:**
    
    ```
    AT+I2CREAD=<DeviceAddress>,<RegisterAddress>
    
    ```
    

### **AT+I2CNREAD**

- **Açıklama:** Birden fazla kayıt adresinden veri okur.
- **Örnek Kullanım:**
    
    ```
    AT+I2CNREAD=<DeviceAddress>,<RegisterAddress>
    
    ```
    

### **AT+I2CWRITE**

- **Açıklama:** Belirtilen cihaz adresine ve kayıt adresine veri yazar.
- **Örnek Kullanım:**
    
    ```
    AT+I2CWRITE=<DeviceAddress>,<RegisterAddress>
    
    ```
    

### **AT+I2CNWRITE**

- **Açıklama:** Birden fazla kayıt adresine veri yazar.
- **Örnek Kullanım:**
    
    ```
    AT+I2CNWRITE=<DeviceAddress>,<RegisterAddress>
    
    ```
    

### **AT+DESKID**

- **Açıklama:** Cihazın bulunduğu masa numarasını ayarlar veya sorgular (Demoya özel)
- **Örnek Kullanım:**
    
    ```
    AT+DESKID=<Hex_value>
    
    ```
