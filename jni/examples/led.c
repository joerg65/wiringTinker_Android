#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <string.h>

// #define LED 0 matches with ASUS_GPIO 164! This can be checked with command 'sudo gpio readall'.
#define LED    0

FILE *fp;
char reads[PATH_MAX];


/* Interrupt21: */
void Interrupt21(void) {
   fp = popen("input keyevent 3", "r");
   pclose(fp);
   printf ("Interrupt 21 / Go Home\n\r");
}

/* Interrupt22: */
void Interrupt22(void) {
   fp = popen("input keyevent 4", "r");
   pclose(fp);
   printf ("Interrupt 22 / Go Back\n\r");
}

/* Interrupt23: */
void Interrupt23(void) {
   fp = popen("input keyevent 24", "r");
   pclose(fp);
   printf ("Interrupt 23 / Volume Up\n\r");
}

/* Interrupt24: */
void Interrupt24(void) {
   fp = popen("input keyevent 25", "r");
   pclose(fp);
   printf ("Interrupt 24 / Volume down\n\r");
}

int main (void)
        {
        printf ("TB blink\n");

        wiringPiSetup();
        pinMode (LED, OUTPUT);

   /*Input GPIO228 / Pin 21/ Header.29*/
   pinMode(21, INPUT);
   pullUpDnControl (21, PUD_UP);

   /*Input GPIO219 / Pin 22 / Header.31*/
   pinMode(22, INPUT);
   pullUpDnControl (22, PUD_UP);

   /*Input GPIO234 / Pin 23 / Header.33*/
   pinMode(23, INPUT);
   pullUpDnControl (23, PUD_UP);

   /*Input GPIO214 / Pin 24 / Header.35*/
   pinMode(24, INPUT);
   pullUpDnControl (24, PUD_UP);

  if ( wiringPiISR (21, INT_EDGE_FALLING, &Interrupt21) < 0 ) {
      printf ("Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }

  if ( wiringPiISR (22, INT_EDGE_FALLING, &Interrupt22) < 0 ) {
      printf ("Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }

  if ( wiringPiISR (23, INT_EDGE_FALLING, &Interrupt23) < 0 ) {
      printf ("Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }

  if ( wiringPiISR (24, INT_EDGE_FALLING, &Interrupt24) < 0 ) {
      printf ("Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }

        for (;;)
        {
                printf ("led on\n");
                digitalWrite (LED, HIGH);
                delay (500);
                printf ("led off\n");
                digitalWrite (LED, LOW);
                delay (500);
         }
        return 0;
}
