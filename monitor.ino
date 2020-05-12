void displayMonitor()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);

    if (currentSensor == SENSOR_POS_12V) {
        display.print("+ 12V");
    } else if (currentSensor == SENSOR_NEG_12V) {
        display.print("- 12V");
    } else if (currentSensor == SENSOR_POS_5V) {
        display.print("+ 5V");
    } else {
        display.print("ERROR");
    }
    

    display.setTextSize(1);
    display.setCursor(0, 25);
    display.print("Bus     ");
    display.print(busvoltage);
    display.print(" V");

    display.setCursor(0, 35);
    display.print("Current ");
    display.print(current_mA);
    display.print(" mA");

    display.setCursor(0, 45);
    display.print("Power   ");
    display.print(power_mW);
    display.print(" mW");

    display.setCursor(0, 55);
    display.print("Shunt   ");
    display.print(shuntvoltage);
    display.print(" mV");

    display.display();
}

void updateSensorData(sensor)
{
    shuntvoltage = sensors[sensor].getShuntVoltage_mV();
    busvoltage = sensors[sensor].getBusVoltage_V();
    current_mA = sensors[sensor].getCurrent_mA();
    power_mW = sensors[sensor].getPower_mW();
}

void displayLogo(){
    display.clearDisplay();

    display.fillScreen(SSD1306_BLACK);
    display.drawLine(34, 5, 34, 57, SSD1306_WHITE);
    display.drawLine(35, 5, 35, 57, SSD1306_WHITE);
    display.drawLine(36, 5, 36, 57, SSD1306_WHITE);
    display.drawLine(37, 5, 37, 57, SSD1306_WHITE);

    display.drawLine(86, 5, 86, 57, SSD1306_WHITE);
    display.drawLine(87, 5, 87, 57, SSD1306_WHITE);
    display.drawLine(88, 5, 88, 57, SSD1306_WHITE);
    display.drawLine(89, 5, 89, 57, SSD1306_WHITE);

    display.drawLine(59, 5, 59, 57, SSD1306_WHITE);
    display.drawLine(60, 5, 60, 57, SSD1306_WHITE);
    display.drawLine(61, 5, 61, 57, SSD1306_WHITE);
    display.drawLine(62, 5, 62, 57, SSD1306_WHITE);

    display.drawLine(38, 30, 85, 30, SSD1306_WHITE);
    display.drawLine(38, 31, 85, 31, SSD1306_WHITE);
    display.drawLine(38, 32, 85, 32, SSD1306_WHITE);
    display.drawLine(38, 33, 85, 33, SSD1306_WHITE);

    display.drawLine(37, 54, 86, 5, SSD1306_WHITE);
    display.drawLine(37, 55, 86, 6, SSD1306_WHITE);
    display.drawLine(37, 56, 86, 7, SSD1306_WHITE);
    display.drawLine(37, 57, 86, 8, SSD1306_WHITE);

    display.display();
}