#ifndef CC_MUSIC_MAIN
#define CC_MUSIC_MAIN

namespace cc {

enum TaskNumber {
  NO_ARGUMENT,
  INPUT_FILE_ERROR,
  PROCESS_INPUT_FILE
};

class MusicSheetReaderProgram {
public:
  TaskNumber handleArguments(int, char**);
  void processImage(char*);
};

}
#endif
