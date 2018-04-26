#ifndef CONFIG_H_HW87WHOK
#define CONFIG_H_HW87WHOK

#define VERSION_MAJOR 0
#define VERSION_MINOR 1

#define UDT_VERSION 4

#define MIN_DATA_SIZE (8 * sizeof(uint32_t))
#define MAX_DATA_SIZE 1024
#define MAX_PACKET_SIZE (4 * sizeof(uint32_t) + MAX_DATA_SIZE)

#define MAX_LOSS_SIZE 100

/* comment the following definition to turn off debuf */
#define DEBUG 1

#endif /* end of include guard: CONFIG_H_HW87WHOK */
