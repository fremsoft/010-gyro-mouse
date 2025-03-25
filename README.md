# 🖱️ Gyro Mouse – Controllo del Mouse con Inclinazione e Soffio

Il **Gyro Mouse** è un innovativo sistema di puntamento che consente di controllare il cursore del **mouse** attraverso l’**inclinazione della testa** e di simulare i click con il **soffio**. Questo dispositivo è stato progettato per offrire un'alternativa accessibile e intuitiva al tradizionale mouse.

## 📌 Caratteristiche
- **Controllo del cursore** tramite inclinazione della testa (coordinate assolute)
- **Emulazione dei click** con il soffio in un apposito imbuto
- **Compatibile con risoluzione 1920x1080**
- Basato su **Beetle (ATmega32U4)** o **Arduino Micro** o **Arduino Leonardo** per il supporto nativo USB
- Sensori utilizzati:
  - **MPU-6050** per rilevare l’inclinazione X-Y-Z
  - **BMP180** per il riconoscimento del soffio
- Progettato per il **fai-da-te** e l’integrazione in progetti di accessibilità

## 🎮 Modalità di Controllo
- **Inclinazione della testa** → Sposta il mouse su schermo
- **1 soffio breve** → Click sinistro
- **2 soffi brevi** → Doppio click
- **3 soffi brevi** → Click destro
- **Soffio prolungato** → Trascinamento

## 📂 Struttura del Repository
- `code/` → Contiene il codice sorgente del firmware
- `hardware/` → Schemi e dettagli sui componenti
- `docs/` → Guide e documentazione tecnica

## 🔧 Requisiti
Per costruire e utilizzare il Gyro Mouse, avrai bisogno di:
- **Beetle (ATmega32U4)**
- **MPU-6050 (accelerometro e giroscopio)**
- **BMP180 (sensore di pressione barometrica)**
- **Arduino IDE** per programmare il firmware
- **Cavi e connettori** per il cablaggio

## 📖 Istruzioni per l’Uso
1. **Scarica il codice** da questo repository
2. **Carica il firmware** su Beetle con Arduino IDE
3. **Collega i sensori** secondo lo schema fornito
4. **Indossa il dispositivo e testa il controllo del mouse** 🖱️

## 🎥 Video Dimostrativi
Guarda il progetto in azione su YouTube:
- [Gyro Mouse – in costruzione](#)

## 💡 Contribuisci
Vuoi migliorare il progetto? Sentiti libero di **fare fork del repository** e proporre modifiche tramite una pull request! Idee, miglioramenti e test sono sempre benvenuti.

## 📩 Contatti
Per domande, suggerimenti o collaborazioni, puoi contattarmi tramite [email] o aprire una issue su GitHub.

---  
✨ _Impara Giocando – Scuola di Robotica e Meccatronica_ ✨
