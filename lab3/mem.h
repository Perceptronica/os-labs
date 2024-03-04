#include <fcntl.h>

const char *CommonFile = "like_a_pipe";
const char *SemaphoreName = "my_semaphore";
unsigned mode = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;

