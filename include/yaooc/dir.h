#include <yaooc/file.h>
#include <yaooc/vector.h>

VECTOR_DEFINITION(yaooc_file,yaooc_file_vector)

yaooc_file_vector_t* yaooc_dir_entries(const char*);
yaooc_file_vector_t* yaooc_dir_glob(const char*);
