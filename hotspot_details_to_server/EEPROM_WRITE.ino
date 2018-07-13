/**
     We prepping the data strings by adding the end of line symbol I decided to use ";".
     Then we pass it off to the write_EEPROM function to actually write it to memmory
  */
void write_to_Memory(String s, String p) {
    s += ";";
    write_EEPROM(s, 0);
    p += ";";
    write_EEPROM(p, 100);
    EEPROM.commit();
  }
  
  //write to memory
   
  void write_EEPROM(String x, int pos) {
    for (int n = pos; n < x.length() + pos; n++) 
    {
      EEPROM.write(n, x[n - pos]);
    }
    EEPROM.write(400,'1'); // set flag for connecting to the obtained SSID and PASSWORD
    delay(1000);
    EEPROM.commit();
    
    espreset();

  }
