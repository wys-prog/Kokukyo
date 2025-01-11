// コクウキョウ - Kokūkyō
//            - Wys
// This code is free, and open source.

#ifndef KARGS_H
#define KARGS_H

#define KOKUYO_VERSION            1.0
#define KOKUYO_ARCH               "x87-64"
#define KOKUYO_SUPPORTS_BIOS      true
#define KOKUYO_EXTERNAL_CODE      "./"
#define KOKUYO_LIB_PATH_1         "./"
#define KOKUYO_LIB_PATH_2         "./../"
#define KOKUYO_MEMORY             (2 * 1024 * 1024 * 1024)
#define KOKUYO_THREADS            (4)
#define KOKUYO_NODE_VERSION       1.1
#define KOKUYO_BOOT_SECTOR_SIZE   512 // For now, this is not supported
#define KOKUYO_BOOT_FILE          "./koot.kovm"

#ifndef KOKUYO_CONFIG_TEMPLATE_CREATED
#define KOKUYO_CONFIG_TEMPLATE_CREATED 1

  typedef struct {
    int           version;
    char         *arch;
    int           support_bios;
    unsigned long memory;
    int           threads;
    int           node_version;
    char         *boot_file;
  } konfig;

#endif // KOKUYO_CONFIG_TEMPLATE_CREATED

#endif // KARGS_H