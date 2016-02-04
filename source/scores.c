#include <structures.h>
#include <scores.h>
#include <stm32f30x.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <math.h>
#include <f3d_lcd_sd.h>

FIL Fil;
BYTE Buff[512];
FATFS Fatfs;
DIR dir;
FILINFO fno;
FRESULT rc;
UINT bw,br;

static int MAXSCORES = 10;

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  f3d_lcd_drawString(20,30,"High scores could not be displayed.",WHITE,BLACK);
  while(1);
}

void initScores(scores *s){
  int i,j;
  for (i=0; i<MAXSCORES; i++){
    for (j=0; j<25; j++){
      (*s).names[i][j]='\0';
      if(j<5){
        (*s).strmoves[i][j]='\0';
      }
    }
    (*s).moves[i]=0;
  }
}

void displayScores(scores* s, int sr){
  f3d_lcd_fillScreen(BLACK);
  f3d_lcd_drawString(30,10,"High Scores",RED,BLACK);
	f_mount(0, &Fatfs);
	setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
	int i,j;
	int currname = 0, currletter = 0, currmoves=0, currdigit = 0;
  if(!sr){
  	rc = f_open(&Fil, "SCORES.TXT", FA_READ);
  	if(rc) die(rc);
  	for (;;) {
      rc = f_read(&Fil, Buff, sizeof Buff, &br);	/* Read a chunk of file */
      if(rc) die(rc);
      if (rc || !br) break;			/* Error or end of file */
      for (i = 0; i < br; i++){
      	while(Buff[i]!='.'){
      		(*s).names[currname][currletter]=Buff[i];
      		currletter++;
      		i++;
      	}
      	i++;
      	currname++;
      	currletter = 0;
      	while(Buff[i]>=48&&Buff[i]<=57){
      		(*s).strmoves[currmoves][currdigit]=Buff[i];
      		currdigit++;
      		i++;
      	}
      	currdigit = 0;
      	int numdigits = 0;
      	for(j=0;j<5;j++){
      		if((*s).strmoves[currmoves][j]!='\0')
      			numdigits++;
      		else
      			break;
      	}
      	for(j=0;j<5;j++){
      		if((*s).strmoves[currmoves][j]=='\0')
      			break;
      		(*s).moves[currmoves]+=((*s).strmoves[currmoves][j]-48)*pow(10,(numdigits-j-1));
      	}
      	currmoves++;
      	}
    	}
    	rc = f_close(&Fil);
    	if(rc) die(rc);
      sortScores(s);
    }
  	for(i=0;i<currname;i++)
  	{
  		f3d_lcd_drawString(10,30+10*i,(*s).names[i],WHITE,BLACK);
  		f3d_lcd_drawString(100,30+10*i,(*s).strmoves[i],WHITE,BLACK);

  	}
}

void writeScores(scores* s){
  f_mount(0, &Fatfs);
  rc = f_open(&Fil, "SCORES.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if (rc) die(rc);
  int i,j;
  while((*s).moves[i]!=0){
    rc = f_write(&Fil, (*s).names[i], 25, &bw);
    if (rc) die(rc);
    rc = f_write(&Fil, ".", 1, &bw);
    if (rc) die(rc);
    rc = f_write(&Fil, (*s).strmoves[i], 5, &bw);
    if (rc) die(rc);
    rc = f_write(&Fil, "\n", 1, &bw);
    if (rc) die(rc);
    i++;
  }
}

void sortScores(scores* s){
  int i,j,numscores=0;
  char tname[25], tstrn[25];
  int lowpos = 0;
  for(i=0;i<MAXSCORES;i++){
    if((*s).moves[i]!=0)
      numscores++;
  }
  for(i=0;i<numscores;i++){
    lowpos = i;
    for(j=i;j<numscores;j++){
      if((*s).moves[j]<(*s).moves[lowpos])
        lowpos = j;
    }
    if(lowpos!=j){
      strCopy(tname, (*s).names[i],25);
      strCopy((*s).names[i], (*s).names[lowpos],25);
      strCopy((*s).names[lowpos], tname,25);
      strCopy(tstrn, (*s).strmoves[i],5);
      strCopy((*s).strmoves[i], (*s).strmoves[lowpos],5);
      strCopy((*s).strmoves[lowpos], tstrn,5);
      int tmv = (*s).moves[i];
      (*s).moves[i] = (*s).moves[lowpos];
      (*s).moves[lowpos] = tmv;
    }
  }
}

void addScore(scores* s, int m){
  int i, numchars = 0, numscores = 0;
  for(i=0;i<MAXSCORES;i++){
    if((*s).moves[i]!=0)
      numscores++;
  }
  if(numscores==10&&m>(*s).moves[9])
    return;
  printf("Type in your name: ");
  char ch = 'a';
  char name[25];
  while(ch!='\n'){
    if(numchars=25)
      break;
    ch = getchar();
    if(ch!='\x01'){
      putchar(ch);
      name[numchars] = ch;
      numchars++;
    }
  }
  if(numscores==10)
    numscores=9;
  strCopy((*s).names[numscores],name,25);
  (*s).moves[numscores] = m;
  i=0;
  int temp = m;
  while(temp>0){
    temp/=10;
    i++;
  }
  i--;
  for(i=i; i>=0; i--){
    (*s).strmoves[numscores][i]=m%10;
    m/=10;
  }
  sortScores(s);
}

void strCopy(char* dest, char* source, int strsize)
{
  int i= 0;
  for(i=0;i<strsize;i++){
    dest[i]=source[i];
    source[i]='\0';
  }
}

void printDirectory(){
	rc = f_opendir(&dir, "");
  	if (rc) die(rc);
	for (;;) {
    rc = f_readdir(&dir, &fno);		/* Read a directory item */
    if (rc || !fno.fname[0]) break;	/* Error or end of dir */
    if (fno.fattrib & AM_DIR)
      printf("   <dir>  %s\n", fno.fname);
    else
      printf("%8lu  %s\n", fno.fsize, fno.fname);
  }
  if (rc) die(rc);
}