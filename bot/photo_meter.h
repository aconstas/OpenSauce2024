#ifndef PHOTO_METER_H
#define PHOTO_METER_H

struct PhotoValues {
  int left;
  int right;
  int front;
};

// Function prototypes
PhotoValues readPhotoValues();
void setupPhotoSensor();

#endif