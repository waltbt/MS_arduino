    #include <SPI.h>
    void setup() {
      // have to send on master in, *slave out*
      pinMode(MISO, OUTPUT);
      // turn on SPI in slave mode
      SPCR |= _BV(SPE);
      // turn on interrupts
      SPI.attachInterrupt();
    }
    // SPI interrupt routine
    ISR (SPI_STC_vect)
    {
      byte c = SPDR;
      c = SPDR;
       c=SPDR;
      SPDR = 5;
      
      SPDR =10;
     
      SPDR = 14;
      
    }  // end of interrupt service routine (ISR) for SPI

    
    void loop () { }
