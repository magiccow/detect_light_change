int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

#define MAXI 21
int next=0;
int a[MAXI];
int b[MAXI];

void setup() {
  Serial.begin(9600);
  pinMode(A5, INPUT);

  // zero array for storing historical readings
  for(int i=0; i<MAXI; i++){
    a[i] = 0;
  }
}

// If reading is 5% different from central_value, return true
bool sufficiently_different(int central_value, int reading){
  int diff = abs( central_value - reading );
  int drift = 100 * diff / central_value;
  return drift>5;
}

// sort array of ints
void sorted( int *input, int *output, int maxi ){
  for (int i=0; i<maxi; i++){
    output[i] = input[i];
  }  
  qsort( output, maxi, sizeof(int), compare );
}


void loop() {
  
  int reading = analogRead(A5);
  a[next] = reading;
  next = (next + 1)% MAXI;

  sorted( a, b, MAXI );
  
  int median = b[ MAXI/2 ];
  if( sufficiently_different(median, reading) ){
    Serial.print(reading); Serial.println(" ****");
  }
  delay(100);  
}
