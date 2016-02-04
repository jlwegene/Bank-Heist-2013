void initOptions(options* o);
void settingsMain(options op);
void updateSettingsSelect(int* skips, int* selected, nunchuk_t* nData);
int changeOption(int* skips, int* selected, options* op);
void settingsToggles(options* op, int c);
void drawIndicator(int x, int y, int onoff);