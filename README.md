# Command Line Interface for STM32

The command line is a text interface for stm32.
Here's an appendix of commands. :point_down:

1. `writew <register address in 32 bits> <few number data ....>` 
    - <address in 32 bits> is the value of register address in 32 bits 
    - <data> is the number of data write into that register address, the next data will write into next 32 bits address 
    - example:
      > writew 0x20000000 0xf 0xa 
      > write 0xf into address of 0x20000000
      > write 0xa into address of 0x20000001
      
2. `read <address in 32 bits> <number of data (increment each address by 32 bits)>`
    - <register address in 32 bits> is the value of register in 32 bits
    - <number of data (increment each address by 32 bits)> is the number of data read
    - example :
      > read 0x20000000 3
      > read first data start from 0x20000000 to 0x20000002 because of 3 data
      
 3. `spi <number of data transmit or receive> <number of data transmit through SPI>`
    - example :
      > spi 4 0x9f 0 0 0
      > transmit 4 byte and trasnmit buffer is 0x9f 0 0 0
  
4.  `flash read <memory address in 24 bits> <number of data read can up to 255 byte data>` **for windbond 25Q128FVFG external flash used SPI comunicate**
      - read data from the given address 
      - allow one or more data bytes to be sequentially read from the memory.
      - example :
        > flash read 0x000001 5
        > receive 5 byte of data sequentially from the 0x000001 address

5.  `flash write <memory address in 24 bits> <at least one data byte into memory>
      - write data into page program 
      - an entire 256 byte page to be programmed
      - example :
        > flash write 0x000005 0xa 0xb 0xc
        > write 0xa 0xb 0xc into 0x000005 page

6.  `flash erase <memory address 24 bits>`      
      - erase the sector page with given specified sector
      - example :
        > flash erase 0x010205
        > erase the 0x010205 sector page