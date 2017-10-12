#ifndef CC_MUSIC_MAIN
#define CC_MUSIC_MAIN

enum TaskNumber {
  NO_ARGUMENT,
  INPUT_FILE_ERROR,
  PROCESS_INPUT_FILE
};

TaskNumber handleArguments(int, char**);
bool fileExist(char*);
void processImage(char*);

#endif
