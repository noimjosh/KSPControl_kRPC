void InitializeDisplays() {
  //Right Screen
  Serial1.begin(115200);
  //Left Screen
  Serial2.begin(115200);
  sendToDisplay1(String("page 0"));
  sendToDisplay2(String("page 0"));
  sendToDisplay1(String("boot.txt=\"") + String("connecting")+String("\""));
  sendToDisplay2(String("boot.txt=\"") + String("connecting")+String("\""));
}

void sendToDisplay2(String command)   //send Data to Right Display
{
  Serial1.print(command);
  Serial1.write(0xff);
  Serial1.write(0xff);
  Serial1.write(0xff);
} 

void sendToDisplay1(String command)   //send Data to Left Display
{
  Serial2.print(command);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
} 

void displayDebug()
{
  if (!debugDisp){
    debugDisp = true;
    sendToDisplay1(String("page 3"));
    sendToDisplay2(String("page 6"));
    delay(1500);
    sendToDisplay1(String("atmoT.txt=\"Buttons\""));
  }
}

void setDisplays() {
  if (debugDisp){
    debugDisp = false;
    rightScreen = 6;
    sendToDisplay1(String("page 2"));
  }
  // val = rightScreen;
  if (!digitalRead(pBODY)) {
    val = 5;
  } else if (!digitalRead(pTARGET)){
    val = 4;
  } else if (!digitalRead(pSURFACE)){
    val = 3;
  } else if (!digitalRead(pORBIT)){
    val = 2;
  }

  if (val != rightScreen) {
    sendToDisplay2(String("page ") + String(val));
    rightScreen = val;
  }
  
}
