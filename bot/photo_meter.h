#ifndef PHOTO_METER_H
#define PHOTO_METER_H

struct PhotoValues {
  int left;
  int right;
  int front;
};

// Function prototypes
void setRGBOutput(int r, int g, int b);
PhotoValues readPhotoValues();
void setupPhotoSensor();

#endif