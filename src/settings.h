
#ifndef SETTINGS_H
#define SETTINGS_H

extern volatile uint8_t dataAllowed;
extern volatile uint8_t customContract;
extern volatile uint8_t truncateAddress;


typedef struct internalStorage_t {
  unsigned char dataAllowed;
  unsigned char customContract;
  unsigned char truncateAddress;
  uint8_t initialized;
} internalStorage_t;

#define N_storage (*(volatile internalStorage_t*) PIC(&N_storage_real))

extern const internalStorage_t N_storage_real;

#endif