#include <audioPlayer.h>
#include <stm32f30x.h> 
#include <f3d_i2c.h>
#include <f3d_rtc.h>
#include <f3d_dac.h>
#include <f3d_timer2.h>
#include <ff.h>
#include <diskio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TIMER 20000
#define AUDIOBUFSIZE 128

extern uint8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;

FATFS Fatfs;    /* File system object */
FIL fid;    /* File object */
BYTE Buff[512];   /* File read buffer */
int ret;
int trackselect = 0;

struct ckhd {
  uint32_t ckID;
  uint32_t cksize;
};

struct fmtck {
  uint16_t wFormatTag;      
  uint16_t nChannels;
  uint32_t nSamplesPerSec;
  uint32_t nAvgBytesPerSec;
  uint16_t nBlockAlign;
  uint16_t wBitsPerSample;
};

void readckhd(FIL *fid, struct ckhd *hd, uint32_t ckID) {
  f_read(fid, hd, sizeof(struct ckhd), &ret);
  if (ret != sizeof(struct ckhd))
    exit(-1);
  if (ckID && (ckID != hd->ckID))
    exit(-1);
}

void die2 (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
}



int playFile(char* fname) {
  FRESULT rc;     /* Result code */
  DIR dir;      /* Directory object */
  FILINFO fno;      /* File information object */
  UINT bw, br;
  unsigned int retval;
  int bytesread;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  rc = f_open(&fid, fname, FA_READ);
  //printf("Playing %s\n",fname);
  if (!rc) {
    struct ckhd hd;
    uint32_t  waveid;
    struct fmtck fck;
    readckhd(&fid, &hd, 'FFIR');
    
    f_read(&fid, &waveid, sizeof(waveid), &ret);
    if ((ret != sizeof(waveid)) || (waveid != 'EVAW'))
      return -1;

    readckhd(&fid, &hd, ' tmf');
    
    f_read(&fid, &fck, sizeof(fck), &ret);
    // skip over extra info
    
    if (hd.cksize != 16) {
      // printf("extra header info %d\n", hd.cksize - 16);
      f_lseek(&fid, hd.cksize - 16);
    }
  
    // now skip all non-data chunks !
    
    while(1){
      readckhd(&fid, &hd, 0);
      if (hd.ckID == 'atad')
  break;
      f_lseek(&fid, hd.cksize);
    }
    
    // printf("Samples %d\n", hd.cksize);
    
    // Play it !
    
    //      audioplayerInit(fck.nSamplesPerSec);
    
    f_read(&fid, Audiobuf, AUDIOBUFSIZE, &ret);
    hd.cksize -= ret;
    audioplayerStart();
    while (hd.cksize) {
      int next = hd.cksize > AUDIOBUFSIZE/2 ? AUDIOBUFSIZE/2 : hd.cksize;
      if (audioplayerHalf) {
  if (next < AUDIOBUFSIZE/2)
    bzero(Audiobuf, AUDIOBUFSIZE/2);
  f_read(&fid, Audiobuf, next, &ret);
  hd.cksize -= ret;
  audioplayerHalf = 0;
      }
      if (audioplayerWhole) {
  if (next < AUDIOBUFSIZE/2)
    bzero(&Audiobuf[AUDIOBUFSIZE/2], AUDIOBUFSIZE/2);
  f_read(&fid, &Audiobuf[AUDIOBUFSIZE/2], next, &ret);
  hd.cksize -= ret;
  audioplayerWhole = 0;
      }
    }
    audioplayerStop();
  }
  
  // printf("\nClose the file.\n"); 
  if (rc) die2(rc);
  rc = f_close(&fid);
  
  
}