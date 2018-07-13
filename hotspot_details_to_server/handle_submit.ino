void handleSubmit() { //dispaly values and write to memmory
    String response = "<p>The ssid is ";
    response += server.arg("ssid");
    response += "<br>";
    response += "And the password is ";
    response += server.arg("Password");
    response += "<br>";
    response += "And the IP Address is ";
    response += "</P><BR>";
    response += "<H2><a href=\"/\">go home</a></H2><br>";

    server.send(200, "text/html", response);
    //calling function that writes data to memory
    write_to_Memory(String(server.arg("ssid")), String(server.arg("Password")));
  }
