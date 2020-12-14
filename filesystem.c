#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 *   ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ ___ 
 *  |   |   |   |   |                       |   |
 *  | 0 | 1 | 2 | 3 |     .....             |127|
 *  |___|___|___|___|_______________________|___|
 *  |   \    <-----  data blocks ------>
 *  |     \
 *  |       \
 *  |         \
 *  |           \
 *  |             \
 *  |               \
 *  |                 \
 *  |                   \
 *  |                     \
 *  |                       \
 *  |                         \
 *  |                           \
 *  |                             \
 *  |                               \
 *  |                                 \
 *  |                                   \
 *  |                                     \
 *  |                                       \
 *  |                                         \
 *  |                                           \
 *  |     <--- super block --->                   \
 *  |______________________________________________|
 *  |               |      |      |        |       |
 *  |        free   |      |      |        |       |
 *  |       block   |inode0|inode1|   .... |inode15|
 *  |        list   |      |      |        |       |
 *  |_______________|______|______|________|_______|
 *
 *
 */


#define FILENAME_MAXLEN 8  // including the NULL char

/* 
 * inode 
 */

typedef struct inode {
  int  dir;  // boolean value. 1 if it's a directory.
  char name[FILENAME_MAXLEN];
  int  size;  // actual file/directory size in bytes.
  int  blockptrs [8];  // direct pointers to blocks containing file's content.
  int  used;  // boolean value. 1 if the entry is in use.
  int  rsvd;  // reserved for future use
} inode;


typedef struct data_block {
  char data[1024];
} data_block;

/* 
 * directory entry
 */

typedef struct dirent {
  char name[FILENAME_MAXLEN];
  int  namelen;  // length of entry name
  int  inode;  // this entry inode index
} dirent;


/*
 * functions
 */
// create file
// copy file
// remove/delete file
// move a file
// list file info
// create directory
// remove a directory

int create_fs() {
  printf( "Creating  a 128KB file\n");
  int fd = open("myfs",O_WRONLY | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR);
  printf("Formatting your filesystem...\n");
  close(fd);

  //create free list 
  FILE* fp = fopen("myfs", "r+");
  char* buf = (char*)calloc(128, sizeof(char));
  //super block occupied initially 
  buf[0] = 1;
  fwrite(buf, sizeof(char), sizeof(buf), fp);
  fseek(fp, 128, SEEK_SET);
  
  // create empty inodes and store them in super block.
  struct inode *inode_arr = (inode*)calloc(16, sizeof(struct inode));
  for (int i=0; i<16; i++) {
    inode_arr[i].used = 0;
  }
  fwrite(inode_arr, sizeof(struct inode), 16, fp);
  
  fseek(fp, 1024, SEEK_SET);
  // write data blocks into disk 
  fclose(fp);
  return 0;
}

// int create_file(char* disk, char filename[8], int size) {
//   int free = 0;
//   char buf[128];
//   char filestuff[size];
//   char buf2[896];

//   int fs = open(disk, O_RDWR);
//   if (lseek(fs, 0, SEEK_SET) >= 0) {
//     if (read(fs, buf, 128) >= 0) {
//       for (int i=0; i<128;i++) {
//         printf("%i", buf[i]);
//         if (buf[i] == 0) {
//           free++;
//         }
//       }
//       if (free >= size) {
//         if (lseek(fs, 128, SEEK_SET) >= 0) {
//           if (read(fs, buf2, 896)>=0) {
//             printf("\nyo3\n");
//             for (int i = 0; i<896;i++) {
//               printf("%i", buf2[i]);
//             }
//           }
//         }
//       }
//     }
//   }
// }


// int create_file(char filenam[8], char* disk, int size) {
//   int free = 0;
//   int fs = open(disk, O_RDWR);
//   char buf[128];
//   char cont[size];
  
  
//   if(read(fs, buf, 128) < 0) {
//     printf("error in reading disk\n");
//   } 
//   for (int i=0; i<128;i++){
//     printf("%i", buf[i]);
//     if (buf[i] == 0) {
//       free++;
//     }
//   }
//   printf("%i\n", free);
//   if (free >= size) {   
//     for (int i=0; i<size+1;i++) {
//       cont[i] = 'x';
//     }
    
//     char in_lst[896];
  
//     // read inode list 
//     if(read(fs, in_lst, 896) > 0) {
//       for (int i=0; i<896;i+56) {
//         char tmp[56];
//         for (int j=0;j<56;j++) {
//           tmp[j] = in_lst[i+j];
//         }
//         int zeros = 0;
//         for (int k=0;k<56;k++) {
//           zeros += tmp[k];
//         }
//         if (zeros == 0) {
           
//         }
//       }
//     }

//   }
      
//   return 1;
// }




/*
 * main
 */
int main (int argc, char* argv[]) {

  // while not EOF
    // read command
    
    // parse command
    
    // call appropriate function

  if (access("myfs", F_OK)<0) {
    if (create_fs() == 0) {
      printf("\nfile create now\n");  
    }
  }
  

	//return 0;
}
