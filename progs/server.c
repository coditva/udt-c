#include <stdlib.h>
#include "udt.h"

int main(int argc, char *argv[])
{
    int len;
    return accept(0, NULL, &len) == -1;
}
