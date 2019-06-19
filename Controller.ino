void get_data(){
/*
LF "LiquidFuel"
OX "Oxidizer"
SF "SolidFuel"
MP "MonoPropellant"
XE "XenonGas"
EL "ElectricCharge"
AIR "IntakeAir"
*/
  if (runOnce){
    krpc_SpaceCenter_Resources_Max(conn, &max_lf, resources, "LiquidFuel");
    if (int(max_lf) > 0) { 
      has_lf = true; 
    } else {
      has_lf = false; 
      sendToDisplay1(String("tlf.txt=\"0/0\""));
      sendToDisplay1(String("jlf.val=100"));
    }

    krpc_SpaceCenter_Resources_Max(conn, &max_ox, resources, "Oxidizer");
    if (int(max_ox) > 0) {
      has_ox = true;
    } else {
      has_ox = false;
      sendToDisplay1(String("tox.txt=\"0/0\""));
      sendToDisplay1(String("jox.val=100"));
    }

    krpc_SpaceCenter_Resources_Max(conn, &max_sf, resources, "SolidFuel");
    if (int(max_sf) > 0) {
      has_sf = true;
    } else {
      has_sf = false;
      sendToDisplay1(String("tsf.txt=\"0/0\""));
      sendToDisplay1(String("jsf.val=100"));
    }

    krpc_SpaceCenter_Resources_Max(conn, &max_mp, resources, "MonoPropellant");
    if (int(max_mp) > 0) {
      has_mp = true;
    } else {
      has_mp = false;
      sendToDisplay1(String("tmp.txt=\"0/0\""));
      sendToDisplay1(String("jmp.val=100"));
    }

    krpc_SpaceCenter_Resources_Max(conn, &max_xe, resources, "XenonGas");
    if (int(max_xe) > 0) {
      has_xe = true;
    } else {
      has_xe = false;
      sendToDisplay1(String("txe.txt=\"0/0\""));
      sendToDisplay1(String("jxe.val=100"));
    }

    krpc_SpaceCenter_Resources_Max(conn, &max_el, resources, "ElectricCharge");
    if (int(max_el) > 0) {
      has_el = true;
    } else {
      has_el = false;
      sendToDisplay1(String("tel.txt=\"0/0\""));
      sendToDisplay1(String("jel.val=100"));
    }

    krpc_SpaceCenter_Resources_Max(conn, &max_air, resources, "IntakeAir");
    if (int(max_air) > 0) {
      has_air = true;
    } else {
      has_air = false;
      sendToDisplay1(String("tair.txt=\"0/0\""));
      sendToDisplay1(String("jair.val=100"));
    }

    runOnce = false;
  }

  if (has_lf){
    krpc_SpaceCenter_Resources_Amount(conn, &amt_lf, resources, "LiquidFuel");
    sendToDisplay1(String("tlf.txt=\"") + String(int(amt_lf)) + String("/") + String(int(max_lf)) + String("\""));
    sendToDisplay1(String("jlf.val=") + String(100-int(amt_lf/max_lf*100)));
  }

  if (has_ox){
    krpc_SpaceCenter_Resources_Amount(conn, &amt_ox, resources, "Oxidizer");
    sendToDisplay1(String("tox.txt=\"") + String(int(amt_ox)) + String("/") + String(int(max_ox)) + String("\""));
    sendToDisplay1(String("jox.val=") + String(100-int(amt_ox/max_ox*100)));
  }


  if (has_sf){
      krpc_SpaceCenter_Resources_Amount(conn, &amt_sf, resources, "SolidFuel");
      sendToDisplay1(String("tsf.txt=\"") + String(int(amt_sf)) + String("/") + String(int(max_sf)) + String("\""));
      sendToDisplay1(String("jsf.val=") + String(100-int(amt_sf/max_sf*100)));
  }


  if (has_mp){
      krpc_SpaceCenter_Resources_Amount(conn, &amt_mp, resources, "MonoPropellant");
      sendToDisplay1(String("tmp.txt=\"") + String(int(amt_mp)) + String("/") + String(int(max_mp)) + String("\""));
      sendToDisplay1(String("jmp.val=") + String(100-int(amt_mp/max_mp*100)));
  }

  if (has_xe){
      krpc_SpaceCenter_Resources_Amount(conn, &amt_xe, resources, "XenonGas");
      sendToDisplay1(String("txe.txt=\"") + String(int(amt_xe)) + String("/") + String(int(max_xe)) + String("\""));
      sendToDisplay1(String("jxe.val=") + String(100-int(amt_xe/max_xe*100)));
  }
  
  if (has_el){
    krpc_SpaceCenter_Resources_Amount(conn, &amt_el, resources, "ElectricCharge");
    sendToDisplay1(String("tel.txt=\"") + String(int(amt_el)) + String("/") + String(int(max_el)) + String("\""));
    sendToDisplay1(String("jel.val=") + String(100-int(amt_el/max_el*100)));
  }

  if (has_air){
    krpc_SpaceCenter_Resources_Amount(conn, &amt_air, resources, "IntakeAir");
    sendToDisplay1(String("tair.txt=\"") + String(int(amt_air)) + String("/") + String(int(max_air)) + String("\""));
    sendToDisplay1(String("jair.val=") + String(100-int(amt_air/max_air*100)));
  }
}

void send_data(){

  motorfader();
  
//****************************************************************************************************
// PAUSE BUTTON
  if (debouncePause.pressed()) {
      if (PAUSED) { PAUSED = false; }
      else { PAUSED  = true; }
      krpc_KRPC_set_Paused(conn, PAUSED);
  }

//****************************************************************************************************
// STAGE BUTTON
  if (debounceStage.pressed()) {
    if (digitalRead(pARM)){
      krpc_UI_Message(conn, "Not Armed", 2.5, KRPC_UI_MESSAGEPOSITION_TOPCENTER, &red, 20);
    } else {
      krpc_SpaceCenter_Control_ActivateNextStage(conn, NULL, control);
    }
  }

//****************************************************************************************************
// BRAKES BUTTON
  if (debounceBrakes.pressed()) {
      if (BRAKES) { BRAKES = false; }
      else { BRAKES = true; }
      krpc_SpaceCenter_Control_set_Brakes(conn, control, BRAKES);
}

//****************************************************************************************************
// GEAR BUTTON
  if (debounceGear.pressed()) {
      if (GEAR) { GEAR = false; }
      else { GEAR = true; }
      krpc_SpaceCenter_Control_set_Gear(conn, control, GEAR);
  }

//****************************************************************************************************
// CHUTES BUTTON
  if (debounceChutes.pressed()) {
      if (CHUTES) { CHUTES = false; }
      else { CHUTES = true; }
      krpc_SpaceCenter_Control_set_Parachutes(conn, control, CHUTES);
  }

//****************************************************************************************************
// SOLAR BUTTON
  if (debounceSolar.pressed()) {
      if (SOLAR) { SOLAR = false; }
      else { SOLAR = true; }
      krpc_SpaceCenter_Control_set_SolarPanels(conn, control, SOLAR);
  }

//****************************************************************************************************
// LIGHTS BUTTON
  if (debounceLights.pressed()) {
      if (LIGHTS) { LIGHTS = false; }
      else { LIGHTS = true; }
      krpc_SpaceCenter_Control_set_Lights(conn, control, LIGHTS);
  }

//****************************************************************************************************
// MAP/CAMERA BUTTON
  if (debounceMap.pressed()) {
      if (MAP) {
        MAP = false;
        krpc_SpaceCenter_Camera_set_Mode(conn, camera, KRPC_SPACECENTER_CAMERAMODE_AUTOMATIC);
      } else { 
        MAP = true; 
        krpc_SpaceCenter_Camera_set_Mode(conn, camera, KRPC_SPACECENTER_CAMERAMODE_MAP);
    }
  }

//****************************************************************************************************
// QUICKSAVE BUTTON
  if (debounceSave.pressed()) {
    krpc_SpaceCenter_Quicksave(conn);
    krpc_UI_Message(conn, "Quicksaving...", 2.5, KRPC_UI_MESSAGEPOSITION_TOPCENTER, &yellow, 20);
  }

//****************************************************************************************************
// TIMENORM BUTTON
  if (debounceTIMENORM.pressed()) {
    
  }

//****************************************************************************************************
// SAS TOGGLE
  bool TEMP = digitalRead(pSAS) == LOW;
  krpc_SpaceCenter_Control_set_SAS(conn, control, TEMP);

//****************************************************************************************************
// RCS TOGGLE
  TEMP = digitalRead(pRCS) == LOW;
  krpc_SpaceCenter_Control_set_RCS(conn, control, TEMP);

//****************************************************************************************************
// ABORT TOGGLE
  if (debounceAbort.pressed()){
    krpc_SpaceCenter_Control_set_Abort(conn, control, true);
  } else {
    krpc_SpaceCenter_Control_set_Abort(conn, control, false);
  }
  

//****************************************************************************************************
// ANALOG VALUES
  readValues();
  //THROTTLE
  float d_th;
  float d_stix;
  if (digitalRead(pPRECISE)) {
    d_th = 980;
    d_stix = 512;
  } else {
    d_th = 980*5;
    d_stix = 512*5;
  }
  krpc_SpaceCenter_Control_set_Throttle(conn, control, throttle_value/d_th);
  //Right X
  krpc_SpaceCenter_Control_set_Yaw(conn, control, rx_value/d_stix);
  //Right Y
  krpc_SpaceCenter_Control_set_Pitch(conn, control, ry_value/d_stix);
  //Right Z
  krpc_SpaceCenter_Control_set_Roll(conn, control, rz_value/d_stix);

}

void readValues(){
    throttle_value = 1024 - analogRead(pTHROTTLE) - 20;
    if (throttle_value < 0) { throttle_value = 0; }
    else if (throttle_value > 980) { throttle_value = 980; }

//    throttle_value = 1024-analogRead(pTHROTTLE); //Max high, Min low
    tx_value = analogRead(pTX);  // Left low, Right high
    if (tx_value < 499) {
      tx_value = (tx_value-499);
    } else if (tx_value > 528) {
      tx_value = (tx_value-528);
    } else {
      tx_value = 0;
    }
   
    ty_value = analogRead(pTY);  // Up high, Down low
    if (ty_value < 531) {
      ty_value = 0-(ty_value-531);
    } else if (ty_value > 555) {
      ty_value = 0-(ty_value-555);
    } else {
      ty_value = 0;
    }

    tz_value = analogRead(pTZ);  // CCW low, CW high
    if (tz_value < 516) {
      tz_value = (tz_value-516);
    } else if (tz_value > 526) {
      tz_value = (tz_value-526);
    } else {
      tz_value = 0;
    }

    rx_value = analogRead(pRX);  // Left low, Right high
    if (rx_value < 499) {
      rx_value = (rx_value-499);
    } else if (rx_value > 531) {
      rx_value = (rx_value-531);
    } else {
      rx_value = 0;
    }

    ry_value = analogRead(pRY);  // Up high, Down low
    if (ry_value < 519) {
      ry_value = 0-(ry_value-519);
    } else if (ry_value > 540) {
      ry_value = 0-(ry_value-540);
    } else {
      ry_value = 0;
    }

    rz_value = analogRead(pRZ); // CCW low, CW high 
    if (rz_value < 509) {
      rz_value = (rz_value-509);
    } else if (rz_value > 523) {
      rz_value = (rz_value-523);
    } else {
      rz_value = 0;
    }
}

//*
void motorfader() {
  if(debounceMax.pressed()){
    digitalWrite(pMOTORON, HIGH);
    maxTH = true;
    startMillis = millis();
    }
  else if(debounceMin.pressed()){
    digitalWrite(pMOTORON, HIGH);
    minTH = true;
    startMillis = millis();
  } 
    
  if (minTH) {
    minThrottle();
  } else if (maxTH) {
    maxThrottle();
  } else {
    digitalWrite(pMOTORON, LOW);
    analogWrite(pMOTORDOWN, 0);
    analogWrite(pMOTORUP, 0);
  }
}


void minThrottle(){
  currMillis = millis();
  if (analogRead(pTHROTTLE) < (980) && currMillis - startMillis < deltaMillis){
    analogWrite(pMOTORDOWN, 160);
    analogWrite(pMOTORUP, 0);
  } else {
    digitalWrite(pMOTORON, LOW);
    analogWrite(pMOTORUP, 0);
    analogWrite(pMOTORDOWN, 0);
    minTH = false;
  }
}

void maxThrottle(){
  currMillis = millis();
  if (analogRead(pTHROTTLE) > 50 && currMillis - startMillis < deltaMillis) {
    analogWrite(pMOTORDOWN, 0);
    analogWrite(pMOTORUP, 180);
  } else {
    digitalWrite(pMOTORON, LOW);
    analogWrite(pMOTORUP, 0);
    analogWrite(pMOTORDOWN, 0);
    maxTH = false;
  }
}

//*/
