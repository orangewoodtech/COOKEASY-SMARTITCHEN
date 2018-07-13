//Shows when we get a misformt or wrong request for the web server
  void handleNotFound()
  {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    message += "<H2><a href=\"/\">go home</a></H2><br>";
    server.send(404, "text/plain", message);
  }
