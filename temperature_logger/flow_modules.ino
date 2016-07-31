// PINS 2 & 3 digital

/*
Liquid flow rate sensor -DIYhacking.com Arvind Sanjeev

Measure the liquid/water flow rate using this code. 
Connect Vcc and Gnd of sensor to arduino, and the 
signal line to arduino digital pin 2.
 
 */

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

volatile byte pulseCount[2];  

float flowRate[2];
unsigned int flowMilliLitres[2];

void flow_modules_setup()
{
  
  // Initialize a serial connection for reporting values to the host
  //Serial.begin(38400);
   
  // Set up the status LED line as an output
  //pinMode(statusLed, OUTPUT);
  //digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
  
#ifdef DEBUG  
  Serial.println("Initializing Flow MODULES");
#endif
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);
  
  pulseCount[0]        = 0;
  pulseCount[1]        = 0;
  flowRate[0]          = 0.0;
  flowRate[1]          = 0.0;
  flowMilliLitres[0]   = 0;
  flowMilliLitres[1]   = 0;
  oldTime              = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(0, pulseCounter0, FALLING);
  attachInterrupt(1, pulseCounter1, FALLING);
}

/**
 * Main program loop
 */

 // WARNING: MILLIS RESET AFTER 49+ DAYS
 
String flow_modules_get()
{
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(0);
    detachInterrupt(1);
        
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate[0] = ((1000.0 / (millis() - oldTime)) * pulseCount[0]) / calibrationFactor;
    flowRate[1] = ((1000.0 / (millis() - oldTime)) * pulseCount[1]) / calibrationFactor;

    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
    
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres[0] = (flowRate[0] / 60) * 1000;
    flowMilliLitres[1] = (flowRate[1] / 60) * 1000;
    
#ifdef DEBUG
    unsigned int frac0;
    unsigned int frac1;

    // Print the flow rate for this second in litres / minute
    //Serial.print("Flow rate: ");
    //Serial.print(int(flowRate));  // Print the integer part of the variable
    //Serial.print(".");             // Print the decimal point
    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
    frac0 = (flowRate[0] - int(flowRate[0])) * 10;
    //Serial.print(frac0, DEC) ;      // Print the fractional part of the variable
    //Serial.print("L/min");
    // Print the number of litres flowed in this second
    //Serial.print("  Current Liquid Flowing 0: ");             // Output separator
    //Serial.print(flowMilliLitres[0]);
    //Serial.println("mL/Sec");

    // Print the flow rate for this second in litres / minute
    //Serial.print("Flow rate: ");
    //Serial.print(int(flowRate));  // Print the integer part of the variable
    //Serial.print(".");             // Print the decimal point
    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
    frac1 = (flowRate[1] - int(flowRate[1])) * 10;
    //Serial.print(frac1, DEC) ;      // Print the fractional part of the variable
    //Serial.print("L/min");
    //Serial.print("  Current Liquid Flowing 1: ");             // Output separator
    //Serial.print(flowMilliLitres[1]);
    //Serial.println("mL/Sec");
#endif

    // Reset the pulse counter so we can start incrementing agaiun
    pulseCount[0] = 0;
    pulseCount[1] = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(0, pulseCounter0, FALLING);
    attachInterrupt(1, pulseCounter1, FALLING);
    
    return String(flowMilliLitres[0]) + "," + String(flowMilliLitres[1]);
    
}

/*
Insterrupt Service Routine
 */
void pulseCounter0()
{
  // Increment the pulse counter
  pulseCount[0]++;
}

void pulseCounter1()
{
  // Increment the pulse counter
  pulseCount[1]++;
}
