//Dealing with the call to root

void handleRoot() {
    if (server.hasArg("ssid") && server.hasArg("Password")) { //If all form fields contain data call handelSubmit()
      handleSubmit();
    }
    else {//Redisplay the form
      server.send(200, "text/html", INDEX_HTML);
    }
  }
