//****************************************************************************************************
//                              DEBUG LOOP
//****************************************************************************************************

void debugLoop(){

    readValues();
    sendToDisplay1(String("throttleV.txt=\"") + String(throttle_value)+String("\""));
    sendToDisplay1(String("transxV.txt=\"") + String(tx_value)+String("\""));
    sendToDisplay1(String("transyV.txt=\"") + String(ty_value)+String("\""));
    sendToDisplay1(String("trasnzV.txt=\"") + String(tz_value)+String("\""));
    sendToDisplay1(String("rotxV.txt=\"") + String(rx_value)+String("\""));
    sendToDisplay1(String("rotyV.txt=\"") + String(ry_value)+String("\""));
    sendToDisplay1(String("rotzV.txt=\"") + String(rz_value)+String("\""));

    if (!digitalRead(pSAS)){
      sendToDisplay1(String("sasV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay1(String("sasV.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pRCS)){
      sendToDisplay1(String("rcsV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay1(String("rcsV.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pPRECISE)){
      sendToDisplay1(String("preccoV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay1(String("preccoV.txt=\"") + String(0)+String("\""));
    }

    for (int i = 2; i < 54; i++){
      if (!digitalRead(i) && i != pSAS && i != pRCS && i != pPRECISE && i != pABORT && i != pARM & i != pBODY && i != pTARGET && i != pSURFACE && i != pORBIT && i != pDEBUG){
        sendToDisplay1(String("atmoV.txt=\"") + String(i)+String("\""));        
      }
      if (i == 3){
        i = 21;
      }
    }

/*
    if (!digitalRead(pFWD)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pFWD)+String("\""));
    } else if (!digitalRead(pREV)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pREV)+String("\""));
    } else if (!digitalRead(pESTAGE)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pESTAGE)+String("\""));
    } else if (!digitalRead(pLSTAGE)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pLSTAGE)+String("\""));
    } else if (!digitalRead(pTIMENORM)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pTIMENORM)+String("\""));
    } else if (!digitalRead(pTIMESLOW)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pTIMESLOW)+String("\""));
    } else if (!digitalRead(pTIMEFAST)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pTIMEFAST)+String("\""));
    } else if (!digitalRead(pSAVE)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pSAVE)+String("\""));
    } else if (!digitalRead(pMAP)){
      sendToDisplay1(String("atmoV.txt=\"") + String(pMAP)+String("\""));
    } else {
      sendToDisplay1(String("atmoV.txt=\"") + String("-")+String("\""));
    }
*/

    if (!digitalRead(pBODY)) {
      val = 4;
    } else if (!digitalRead(pTARGET)){
      val = 3;
    } else if (!digitalRead(pSURFACE)){
      val = 2;
    } else if (!digitalRead(pORBIT)){
      val = 1;
    }
    sendToDisplay1(String("dispswV.txt=\"") + String(val)+String("\""));


    if (!digitalRead(pDEBUG)){
      sendToDisplay2(String("debugV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("debugV.txt=\"") + String(0)+String("\""));
    }

    motorfader();

    if (!digitalRead(pMAX)){
      sendToDisplay2(String("maxV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("maxV.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pMIN)){
      sendToDisplay2(String("minV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("minV.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pABORT)){
      sendToDisplay2(String("abortV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("abortV.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pARM)){
      sendToDisplay2(String("armV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("armV.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pRSTAGE)){
      sendToDisplay2(String("stageV.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("stageV.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pA1)){
      sendToDisplay2(String("A1V.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("A1V.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pA2)){
      sendToDisplay2(String("A2V.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("A2V.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pA3)){
      sendToDisplay2(String("A3V.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("A3V.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pA4)){
      sendToDisplay2(String("A4V.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("A4V.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pA5)){
      sendToDisplay2(String("A5V.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("A5V.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pA6)){
      sendToDisplay2(String("A6V.txt=\"") + String(1)+String("\""));
    } else {
      sendToDisplay2(String("A6V.txt=\"") + String(0)+String("\""));
    }

    if (!digitalRead(pBRAKES)){
      sendToDisplay1(String("brakesV.txt=\"") + String(1)+String("\""));
      digitalWrite(lBRAKES, HIGH);
    } else {
      sendToDisplay1(String("brakesV.txt=\"") + String(0)+String("\""));
      digitalWrite(lBRAKES, LOW);
    }

    if (!digitalRead(pLIGHTS)){
      sendToDisplay1(String("lightsV.txt=\"") + String(1)+String("\""));
      digitalWrite(lLIGHTS, HIGH);
    } else {
      sendToDisplay1(String("lightsV.txt=\"") + String(0)+String("\""));
      digitalWrite(lLIGHTS, LOW);
    }

    if (!digitalRead(pCHUTES)){
      sendToDisplay2(String("chutesV.txt=\"") + String(1)+String("\""));
      digitalWrite(lCHUTES, HIGH);
    } else {
      sendToDisplay2(String("chutesV.txt=\"") + String(0)+String("\""));
      digitalWrite(lCHUTES, LOW);
    }

    if (!digitalRead(pLADDER)){
      sendToDisplay2(String("ladderV.txt=\"") + String(1)+String("\""));
      digitalWrite(lLADDER, HIGH);
    } else {
      sendToDisplay2(String("ladderV.txt=\"") + String(0)+String("\""));
      digitalWrite(lLADDER, LOW);
    }

    if (!digitalRead(pSOLAR)){
      sendToDisplay2(String("solarV.txt=\"") + String(1)+String("\""));
      digitalWrite(lSOLAR, HIGH);
    } else {
      sendToDisplay2(String("solarV.txt=\"") + String(0)+String("\""));
      digitalWrite(lSOLAR, LOW);
    }

    if (!digitalRead(pGEAR)){
      sendToDisplay2(String("gearsV.txt=\"") + String(1)+String("\""));
      digitalWrite(lGEAR, HIGH);
    } else {
      sendToDisplay2(String("gearsV.txt=\"") + String(0)+String("\""));
      digitalWrite(lGEAR, LOW);
    }

}
