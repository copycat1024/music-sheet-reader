#include <iostream>
#include "cc_music_main.hh"

using namespace std;

int main(int argc, char** argv){
  switch (handleArguments(argc, argv)){
    case NO_ARGUMENT:
      cerr << "The program " << argv[0] << " require argument." << endl;
      cerr << "Usage: " << argv[0] << " <image_file_name>." << endl;
      break;
    case INPUT_FILE_ERROR:
      cerr << "File " << argv[1] << " doesn't exist." << endl;
      break;
    case PROCESS_INPUT_FILE:
      processImage(argv[1]);
      break;
    default:
      cerr << "Internal error: handleArguments return unknown result." << endl;
  }
  return 0;
}
