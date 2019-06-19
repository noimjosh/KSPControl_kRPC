void get_data(){

  if (has_lf){
    error = krpc_SpaceCenter_Resources_Amount(conn, &amt_lf, resources, lf);
    if (error != KRPC_OK) {hasError = true;}
    error = krpc_SpaceCenter_Resources_Max(conn, &max_lf, resources, lf);
    if (error != KRPC_OK) {hasError = true;}
    sendToDisplay1(String("tlf.txt=\"") + String(int(amt_lf)) + String("/") + String(int(max_lf)) + String("\""));
    sendToDisplay1(String("jlf.val=") + String(100-int(amt_lf/max_lf*100)));
  }

  if (has_ox){
    error = krpc_SpaceCenter_Resources_Amount(conn, &amt_ox, resources, ox);
    if (error != KRPC_OK) {hasError = true;}
    error = krpc_SpaceCenter_Resources_Max(conn, &max_ox, resources, ox);
    if (error != KRPC_OK) {hasError = true;}
    sendToDisplay1(String("tox.txt=\"") + String(int(amt_ox)) + String("/") + String(int(max_ox)) + String("\""));
    sendToDisplay1(String("jox.val=") + String(100-int(amt_ox/max_ox*100)));
  }

  if (has_sf){
    error = krpc_SpaceCenter_Resources_Amount(conn, &amt_sf, resources, sf);
    if (error != KRPC_OK) {hasError = true;}
    error = krpc_SpaceCenter_Resources_Max(conn, &max_sf, resources, sf);
    if (error != KRPC_OK) {hasError = true;}
    sendToDisplay1(String("tsf.txt=\"") + String(int(amt_sf)) + String("/") + String(int(max_sf)) + String("\""));
    sendToDisplay1(String("jsf.val=") + String(100-int(amt_sf/max_sf*100)));
  }

  if (has_mp){
    error = krpc_SpaceCenter_Resources_Amount(conn, &amt_mp, resources, mp);
    if (error != KRPC_OK) {hasError = true;}
    error = krpc_SpaceCenter_Resources_Max(conn, &max_mp, resources, mp);
    if (error != KRPC_OK) {hasError = true;}
    sendToDisplay1(String("tmp.txt=\"") + String(int(amt_mp)) + String("/") + String(int(max_mp)) + String("\""));
    sendToDisplay1(String("jmp.val=") + String(100-int(amt_mp/max_mp*100)));
  }

  if (has_xe){
    error = krpc_SpaceCenter_Resources_Amount(conn, &amt_xe, resources, xe);
    if (error != KRPC_OK) {hasError = true;}
    error = krpc_SpaceCenter_Resources_Max(conn, &max_xe, resources, xe);
    if (error != KRPC_OK) {hasError = true;}
    sendToDisplay1(String("txe.txt=\"") + String(int(amt_xe)) + String("/") + String(int(max_xe)) + String("\""));
    sendToDisplay1(String("jxe.val=") + String(100-int(amt_xe/max_xe*100)));
  }
  
  if (has_el){
    error = krpc_SpaceCenter_Resources_Amount(conn, &amt_el, resources, el);
    if (error != KRPC_OK) {hasError = true;}
    error = krpc_SpaceCenter_Resources_Max(conn, &max_el, resources, el);
    if (error != KRPC_OK) {hasError = true;}
    sendToDisplay1(String("tel.txt=\"") + String(int(amt_el)) + String("/") + String(int(max_el)) + String("\""));
    sendToDisplay1(String("jel.val=") + String(100-int(amt_el/max_el*100)));
  }

  if (has_air){
    error = krpc_SpaceCenter_Resources_Amount(conn, &amt_air, resources, air);
    if (error != KRPC_OK) {hasError = true;}
    error = krpc_SpaceCenter_Resources_Max(conn, &max_air, resources, air);
    if (error != KRPC_OK) {hasError = true;}
    sendToDisplay1(String("tair.txt=\"") + String(int(amt_air)) + String("/") + String(int(max_air)) + String("\""));
    sendToDisplay1(String("jair.val=") + String(100-int(amt_air/max_air*100)));
  }

  if (hasError) { errorLoop(); }
}

void send_data(){

  motorfader();
  
//****************************************************************************************************
// PAUSE BUTTON
  if (debouncePause.pressed()) {
      if (PAUSED) { PAUSED = false; }
      else { PAUSED  = true; }
      error = krpc_KRPC_set_Paused(conn, PAUSED);
      if (error != KRPC_OK) {hasError = true;}
  }

//****************************************************************************************************
// STAGE BUTTON
  if (debounceStage.pressed()) {
    if (digitalRead(pARM)){
      error = krpc_UI_Message(conn, "Not Armed", 2.5, KRPC_UI_MESSAGEPOSITION_TOPCENTER, &red, 20);
      if (error != KRPC_OK) {hasError = true;}
    } else {
      error = krpc_SpaceCenter_Control_ActivateNextStage(conn, NULL, control);
      if (error != KRPC_OK) {hasError = true;}
    }
  }

//****************************************************************************************************
// BRAKES BUTTON
  if (debounceBrakes.pressed()) {
      if (BRAKES) { BRAKES = false; }
      else { BRAKES = true; }
      error = krpc_SpaceCenter_Control_set_Brakes(conn, control, BRAKES);
      if (error != KRPC_OK) {hasError = true;}
}

//****************************************************************************************************
// GEAR BUTTON
  if (debounceGear.pressed()) {
      if (GEAR) { GEAR = false; }
      else { GEAR = true; }
      error = krpc_SpaceCenter_Control_set_Gear(conn, control, GEAR);
      if (error != KRPC_OK) {hasError = true;}
  }

//****************************************************************************************************
// CHUTES BUTTON
  if (debounceChutes.pressed()) {
      if (CHUTES) { CHUTES = false; }
      else { CHUTES = true; }
      error = krpc_SpaceCenter_Control_set_Parachutes(conn, control, CHUTES);
      if (error != KRPC_OK) {hasError = true;}
  }

//****************************************************************************************************
// SOLAR BUTTON
  if (debounceSolar.pressed()) {
      if (SOLAR) { SOLAR = false; }
      else { SOLAR = true; }
      error = krpc_SpaceCenter_Control_set_SolarPanels(conn, control, SOLAR);
      if (error != KRPC_OK) {hasError = true;}
  }

//****************************************************************************************************
// LIGHTS BUTTON
  if (debounceLights.pressed()) {
      if (LIGHTS) { LIGHTS = false; }
      else { LIGHTS = true; }
      error = krpc_SpaceCenter_Control_set_Lights(conn, control, LIGHTS);
      if (error != KRPC_OK) {hasError = true;}
  }

//****************************************************************************************************
// MAP/CAMERA BUTTON
  if (debounceMap.pressed()) {
      if (MAP) {
        MAP = false;
        error = krpc_SpaceCenter_Camera_set_Mode(conn, camera, KRPC_SPACECENTER_CAMERAMODE_AUTOMATIC);
        if (error != KRPC_OK) {hasError = true;}
      } else { 
        MAP = true; 
        error = krpc_SpaceCenter_Camera_set_Mode(conn, camera, KRPC_SPACECENTER_CAMERAMODE_MAP);
        if (error != KRPC_OK) {hasError = true;}
    }
  }

//****************************************************************************************************
// QUICKSAVE BUTTON
  if (debounceSave.pressed()) {
    error = krpc_SpaceCenter_Quicksave(conn);
    if (error != KRPC_OK) {hasError = true;}
    error = krpc_UI_Message(conn, "Quicksaving...", 2.5, KRPC_UI_MESSAGEPOSITION_TOPCENTER, &yellow, 20);
    if (error != KRPC_OK) {hasError = true;}
  }

//****************************************************************************************************
// TIMENORM BUTTON
  if (debounceTIMENORM.pressed()) {
    
  }

//****************************************************************************************************
// SAS TOGGLE
  bool TEMP = digitalRead(pSAS) == LOW;
  error = krpc_SpaceCenter_Control_set_SAS(conn, control, TEMP);
  if (error != KRPC_OK) {hasError = true;}

//****************************************************************************************************
// RCS TOGGLE
  TEMP = digitalRead(pRCS) == LOW;
  error = krpc_SpaceCenter_Control_set_RCS(conn, control, TEMP);
  if (error != KRPC_OK) {hasError = true;}

//****************************************************************************************************
// ABORT TOGGLE
  if (debounceAbort.pressed()){
    error = krpc_SpaceCenter_Control_set_Abort(conn, control, true);
    if (error != KRPC_OK) {hasError = true;}
  } else {
    error = krpc_SpaceCenter_Control_set_Abort(conn, control, false);
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
  error = krpc_SpaceCenter_Control_set_Throttle(conn, control, throttle_value/d_th);
  if (error != KRPC_OK) {hasError = true;}
  //Right X
  error = krpc_SpaceCenter_Control_set_Yaw(conn, control, rx_value/d_stix);
  if (error != KRPC_OK) {hasError = true;}
  //Right Y
  error = krpc_SpaceCenter_Control_set_Pitch(conn, control, ry_value/d_stix);
  if (error != KRPC_OK) {hasError = true;}
  //Right Z
  error = krpc_SpaceCenter_Control_set_Roll(conn, control, rz_value/d_stix);
  if (error != KRPC_OK) {hasError = true;}

  if (hasError) { errorLoop(); }
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
