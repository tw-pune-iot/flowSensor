/*
YF‐ S201 Water Flow Sensor
Water Flow Sensor output processed to read in litres/hour
Adaptation Courtesy: www.hobbytronics.co.uk
*/
volatile int flow_frequency; // Measures flow sensor pulses
float l_sec;
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
unsigned long prev_high_time;
unsigned long cur_high_state_time;
unsigned long start_time;
float low_time_duration;
float water_drawn;
float low_time;
float high_time_duration;

void flow () // Interrupt function
{
   cur_high_state_time = millis();
   low_time_duration = (cur_high_state_time - prev_high_time)/1000;
   if(low_time_duration > 3){
      Serial.println("started...");
      start_time = millis();
//      flow_frequency = 0;
   }
   flow_frequency++;
   prev_high_time = millis();
}
void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, HIGH); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
   Serial.print("starting");
}
void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      low_time = (currentTime - prev_high_time)/1000;
      l_sec = (flow_frequency/7.5)/60;
      water_drawn+= l_sec*1000;
      if(low_time>3){
        // high_time_duration = (prev_high_time - start_time)/1000;  
//          l_sec = (flow_frequency/7.5)/60;
//          water_drawn = l_sec*1000;
          Serial.print("water drawn:");
          Serial.println(water_drawn);
          water_drawn = 0; 
      }
      flow_frequency = 0;
   }
}
