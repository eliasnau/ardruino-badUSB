#include <Keyboard.h>
#include <SD.h>

const int chipSelect = 4;  // Set the chip select pin for the SD card module

void setup() {
  Serial.begin(9600);
  Keyboard.setManufacturer("404 H4CKS");
  Keyboard.setProductName("404 Keyboard");
  Keyboard.setSerialNumber("6753DVG");
  Keyboard.begin();
  delay(1000);

  // Initialize the SD card4
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  // Open the script file
  File scriptFile = SD.open("payload.txt");

  // Check if the file opened successfully
  if (scriptFile) {
    // Read the file line by line
    while (scriptFile.available()) {
      String line = scriptFile.readStringUntil('\n');
      processLine(line);
    }

    // Close the file
    scriptFile.close();
  } else {
    Serial.println("Error opening script.txt");
  }
}

void loop() {
  // Your main loop code here
}

void processLine(String line) {
  // Check if the line contains "SELF_DESTRUCT" at the start
  if (line.startsWith("SELF_DESTRUCT")) {
    // Delete the script file
    SD.remove("script.txt");
    Serial.println("Script file deleted.");
  } else {
    // Process other commands if "SELF_DESTRUCT" is not present
    if (line.startsWith("WRITE")) {
      // Extract the text to type from the line
      String textToType = line.substring(6);

      // Type the text
      Keyboard.print(textToType);
    } else if (line.startsWith("DELAY")) {
      // Extract the timeout value from the line
      int timeoutValue = line.substring(6).toInt();

      // Wait for the specified timeout in seconds
      delay(timeoutValue * 1000);
    } else if (line.startsWith("KEY")) {
      // Extract the second parameter after "KEY"
      String keyParameter = line.substring(4);

      // Split the keyParameter into individual keys
      String[] keys = keyParameter.split(" ");

      // Press each key in the list simultaneously
      for (String key : keys) {
        int keyCode = getKeyCode(key);
        Keyboard.press(keyCode);
      }

      // Release all keys
      Keyboard.releaseAll();

    } else if (line.startsWith("REM")){
      Searial.println(line.substring(4));
    }
  }
}
