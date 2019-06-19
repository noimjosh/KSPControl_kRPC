#include <krpc.h>
#include <krpc/services/krpc.h>
#include <krpc/services/space_center.h>
#include <krpc/services/ui.h>

#include <Button.h>


//****************************************************************************************************
//                                    VARIABLE DECLARATIONS
//****************************************************************************************************

// ####### CONSTANTS #######

// Throttle
const byte pTHROTTLE = A3;
// Left Stick
const byte pTX = A5;       //translation x-axis
const byte pTY = A4;       //translation y-axis
const byte pTZ = A14;       //translation z-axis
// Right Stick
const byte pRX = A7;       //rotation x-axis
const byte pRY = A6;       //rotation y-axis
const byte pRZ = A15;       //rotation z-axis
// Buttons
const byte pA1 = 24;
const byte pA2 = 43;
const byte pA3 = 41;
const byte pA4 = 32;
const byte pA5 = 30;
const byte pA6 = 28;
const byte pSAVE = 36;
const byte pMAP = 34;
const byte pLADDER = 29;
const byte pCHUTES = 33;
const byte pSOLAR = 22;
const byte pGEAR = 31;
const byte pBRAKES = 35;
const byte pLIGHTS = 26;
const byte pFWD = 40;
const byte pREV = 45;
const byte pTIMENORM = 46;
const byte pTIMESLOW = 47;
const byte pTIMEFAST = 48;
const byte pARM = 39;
const byte pABORT = 37;
const byte pRCS = 25;
const byte pSAS = 2;
const byte pPRECISE = 27;
const byte pMAX = 3;
const byte pMIN = 23;
const byte pRSTAGE = 53;
const byte pLSTAGE = 44;
const byte pPAUSE = 38;
const byte pDEBUG = 49;
const byte pORBIT = 42;
const byte pSURFACE = 50;
const byte pTARGET = 51;
const byte pBODY = 52;
const byte pMOTORON = 11;
const byte pMOTORDOWN = 12;
const byte pMOTORUP = 13;


// ####### LEDS #######
const byte lCHUTES = 7;
const byte lBRAKES = 6;
const byte lLIGHTS = 4;
const byte lLADDER = 9;
const byte lGEAR = 8;
const byte lSOLAR = 5;

bool LADDER = false;
bool CHUTES = false;
bool GEAR = true;
bool BRAKES = false;
bool SOLAR = false;
bool LIGHTS = false;

// ####### MIN/MAX THROTTLE STUFF #######
unsigned long startMillis;
unsigned long currMillis;
const unsigned long deltaMillis = 250;
bool maxTH = false;
bool minTH = false;

// ####### BUTTONS #######
Button debounceBrakes(pBRAKES);
Button debounceGear(pGEAR);
Button debounceLadder(pLADDER);
Button debounceChutes(pCHUTES);
Button debounceSolar(pSOLAR);
Button debounceLights(pLIGHTS);
Button debounceStage(pRSTAGE);
Button debounceAbort(pABORT);
Button debounceMax(pMAX);
Button debounceMin(pMIN);
Button debounceMap(pMAP);
Button debounceSave(pSAVE);
Button debounceTIMENORM(pTIMENORM);
Button debounceTIMESLOW(pTIMESLOW);
Button debounceTIMEFAST(pTIMEFAST);
Button debouncePause(pPAUSE);


// ####### RESOURCE VARIABLES #######
float amt_el;
float max_el;
bool has_el;
float amt_mp;
float max_mp;
bool has_mp;
float amt_lf;
float max_lf;
bool has_lf;
float amt_ox;
float max_ox;
bool has_ox;
float amt_sf;
float max_sf;
bool has_sf;
float amt_xe;
float max_xe;
bool has_xe;
float amt_air;
float max_air;
bool has_air;

const char lf = "LiquidFuel";
const char ox = "Oxidizer";
const char sf = "SolidFuel";
const char mp = "MonoPropellant";
const char xe = "XenonGas";
const char el = "ElectricCharge";
const char air = "IntakeAir";


// ####### OTHER #######
int val;
bool debug;
bool debugDisp;
bool hasError;
bool PAUSED = false;
bool MAP = false;
int rightScreen;

//input value variables
int throttle_value;
int tx_value;
int ty_value;
int tz_value;
int rx_value;
int ry_value;
int rz_value;

void(* softReboot) (void) = 0;

//****************************************************************************************************
//                                  kRPC VARIABLES
//****************************************************************************************************
HardwareSerial *conn;
krpc_SpaceCenter_Control_t instance;
krpc_SpaceCenter_Vessel_t vessel;
krpc_SpaceCenter_Control_t control;
krpc_SpaceCenter_Camera_t camera;
const krpc_tuple_double_double_double_t yellow = {255, 255, 0};
const krpc_tuple_double_double_double_t red = {255, 0, 0};
const krpc_tuple_double_double_double_t green = {0, 255, 0};
const krpc_tuple_double_double_double_t blue = {0, 0, 255};
krpc_SpaceCenter_Resources_t resources;
krpc_error_t error;


//****************************************************************************************************

void setup() {

  // put your setup code here, to run once:
  InitializeDisplays();

// ############### PIN SETUP ###############

    pinMode(pMOTORON, OUTPUT);
    digitalWrite(pMOTORON, LOW);
    pinMode(pMOTORUP, OUTPUT);
    analogWrite(pMOTORUP, 0);
    pinMode(pMOTORDOWN, OUTPUT);
    analogWrite(pMOTORDOWN, 0);

    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);

    pinMode(2, INPUT);
    pinMode(3, INPUT);
    
    for (int i = 22; i <= 53; i++) {
      pinMode(i, INPUT);
    }


// ############### kRPC Variable Setup ###############
conn = &Serial;
delay(1000);

if (!digitalRead(pDEBUG)){
    
  } else {
    runToConnect();
  }
}

//****************************************************************************************************

void loop() {
   // put your main code here, to run repeatedly:
   // right now we're running the debug loop indefinitely to test it out
  if (!digitalRead(pDEBUG) && debug){
    displayDebug();
    debugLoop();
    debug = true;
  } else if (!digitalRead(pDEBUG) && !debug){
    debug = true;
  } else if (digitalRead(pDEBUG) && debug) {
    debug = false;
    softReboot();
  } else {
    setDisplays();
    get_data();
    send_data();
  }
}

void runToConnect(){
  sendToDisplay1(String("page 1"));
  sendToDisplay2(String("page 1"));

  // Connect to kRPC on PC
  do {
    error = krpc_open(&conn, NULL);
    if (error != KRPC_OK){
      delay(100);
    }
  } while (error != KRPC_OK && digitalRead(pDEBUG));

  
  do {
    error = krpc_connect(conn, "KSP Controller");
    if (error != KRPC_OK){
      delay(100);
    }
  } while (error != KRPC_OK && digitalRead(pDEBUG));

  // Get the active vessel on the screen (only when in flight mode)
  do {
    error = krpc_SpaceCenter_ActiveVessel(conn, &vessel);
    if (error != KRPC_OK){
      delay(100);
    }
  } while (error != KRPC_OK && digitalRead(pDEBUG));

  // Get the controls for the active vessel
  do {
    error = krpc_SpaceCenter_Vessel_Control(conn, &control, vessel);
    if (error != KRPC_OK){
      delay(100);
    }
  } while (error != KRPC_OK && digitalRead(pDEBUG));

  // Get camera object for map button
  do {
    error = krpc_SpaceCenter_Camera(conn, &camera);
    if (error != KRPC_OK){
      delay(100);
    }
  } while (error != KRPC_OK && digitalRead(pDEBUG));

  // Get resource object for active vessel (whole vessel)
  do {
    error = krpc_SpaceCenter_Vessel_Resources(conn, &resources, vessel);
    if (error != KRPC_OK){
      delay(100);
    }
  } while (error != KRPC_OK && digitalRead(pDEBUG));

  // Get resource object for active vessel (whole vessel & stage)
  do {
    error = krpc_SpaceCenter_Vessel_Resources(conn, &resources, vessel);
    if (error != KRPC_OK){
      delay(100);
    }
  } while (error != KRPC_OK && digitalRead(pDEBUG));

  // Set control mode to override inputs (not add to already available inputs)
  do {
    error = krpc_SpaceCenter_Control_set_InputMode(conn, control, KRPC_SPACECENTER_CONTROLINPUTMODE_OVERRIDE);
    if (error != KRPC_OK){
      delay(100);
    }
  } while (error != KRPC_OK && digitalRead(pDEBUG));

  do {
    hasError = false;
    error = krpc_SpaceCenter_Resources_HasResource(conn, resources, &has_lf, lf);
    if (error != KRPC_OK) {hasError = true;}
    if (!has_lf){
      sendToDisplay1(String("tlf.txt=\"0/0\""));
      sendToDisplay1(String("jlf.val=100"));
    }
    error = krpc_SpaceCenter_Resources_HasResource(conn, resources, &has_ox, ox);
    if (error != KRPC_OK) {hasError = true;}
    if (!has_ox){
      sendToDisplay1(String("tox.txt=\"0/0\""));
      sendToDisplay1(String("jox.val=100"));
    }
    error = krpc_SpaceCenter_Resources_HasResource(conn, resources, &has_sf, sf);
    if (error != KRPC_OK) {hasError = true;}
    if (!has_sf){
      sendToDisplay1(String("tsf.txt=\"0/0\""));
      sendToDisplay1(String("jsf.val=100"));
    }
    error = krpc_SpaceCenter_Resources_HasResource(conn, resources, &has_mp, mp);
    if (error != KRPC_OK) {hasError = true;}
    if (!has_mp){
      sendToDisplay1(String("tmp.txt=\"0/0\""));
      sendToDisplay1(String("jmp.val=100"));
    }
    error = krpc_SpaceCenter_Resources_HasResource(conn, resources, &has_xe, xe);
    if (error != KRPC_OK) {hasError = true;}
    if (!has_xe){
      sendToDisplay1(String("txe.txt=\"0/0\""));
      sendToDisplay1(String("jxe.val=100"));
    }
    error = krpc_SpaceCenter_Resources_HasResource(conn, resources, &has_el, el);
    if (error != KRPC_OK) {hasError = true;}
    if (!has_el){
      sendToDisplay1(String("tel.txt=\"0/0\""));
      sendToDisplay1(String("jel.val=100"));
    }
    error = krpc_SpaceCenter_Resources_HasResource(conn, resources, &has_air, air);
    if (error != KRPC_OK) {hasError = true;}
    if (!has_air){
      sendToDisplay1(String("tair.txt=\"0/0\""));
      sendToDisplay1(String("jair.val=100"));
    }
  } while (hasError);


  sendToDisplay1(String("page 2"));
  sendToDisplay2(String("page 2"));
}


void errorLoop(){
  hasError = false;
  runToConnect();
}

