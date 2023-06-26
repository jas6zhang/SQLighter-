#include "Pager.h"

Pager* pager_start(const char* filename) {
  int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

  if (fd == -1) {
   printf("Unable to open file\n");
    exit(EXIT_FAILURE);
  }

  off_t file_length = lseek(fd, 0, SEEK_END);

  Pager* pager = malloc(sizeof(Pager));
  pager->file_desc = fd;
  pager->file_len = file_length;
  pager->num_pages = (file_length / PAGE_SIZE);

  if (file_length % PAGE_SIZE != 0) {
    printf("Corrupt file. DB not whole number of pages\n");
    exit(EXIT_FAILURE);
  } 
  for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
    pager->pages[i] = NULL;
  }

  return pager;
}

void* get_page(Pager* pager, uint32_t page_num){
  // Out of bounds
  if (page_num > TABLE_MAX_PAGES) {
    printf("Page number out of bounds!");
    exit(EXIT_FAILURE);
  }

  if (pager->pages[page_num] == NULL) {
    // Not in memory, check disk
    void* page = malloc(PAGE_SIZE);
    uint32_t num_pages = pager->file_len / PAGE_SIZE;
    
    if (pager->file_len % PAGE_SIZE) {
      num_pages += 1;
    }
    if (page_num <= num_pages) {
      lseek(pager->file_desc, page_num * PAGE_SIZE, SEEK_SET);
      ssize_t bytes_read = read(pager->file_desc, page, PAGE_SIZE);
      if (bytes_read == -1) {
        printf("Error reading file\n");
        exit(EXIT_FAILURE);
      }
    }

    pager->pages[page_num] = page;
    if (page_num >= pager->num_pages) {
      pager->num_pages = page_num + 1;
    }
  }
  return pager->pages[page_num];
}

void pager_flush(Pager* pager, uint32_t page_num) {
  if (pager->pages[page_num] == NULL) {
    printf("Cannot flush null page\n");
    exit(EXIT_FAILURE);
  }

  off_t offset = lseek(pager->file_desc, page_num * PAGE_SIZE, SEEK_SET);

  if (offset == -1) {
    exit(EXIT_FAILURE);
  }

  ssize_t bytes_written =
      write(pager->file_desc, pager->pages[page_num], PAGE_SIZE);

  if (bytes_written == -1) {
    printf("Error writing: %d\n", errno);
    exit(EXIT_FAILURE);
  }
}
