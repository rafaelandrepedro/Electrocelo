/* 
 * File:   eusartpackage.h
 * Author: rafael pedro
 *
 * Created on July 14, 2022, 8:27 AM
 */

#ifndef EUSARTPACKAGE_H
#define	EUSARTPACKAGE_H

#ifdef	__cplusplus
extern "C" {
#endif

    #include "mcc_generated_files/eusart1.h"

    #define STARTBYTE 0x0A 
    #define ENDBYTE 0x0D 
    #ifndef TRUE
    #define TRUE 1 
    #endif  /* TRUE */
    #ifndef FALSE
    #define FALSE 0 
    #endif	/* FALSE */

    /*
     * @brief union that allows the data to be read in separated bytes or in a 16 bit integer
     */
    union packagedata_t{
        uint16_t data16;
        uint8_t data8[2];
    };
    
    /*
     * @brief function operation modes
     */
    enum functioncode_t{
        READ=0,
        WRITE=1,
        PROGRAMMING_ENABLE=2,
        CONFIRM=3,
        NUM_COMMANDS_F=4,
        NUM_EMPTY_COMMANDS_F=5,
        OCCUPIED_POS_F=6,
        EMPTY_POS_F=7,
        SAVE_COMMAND_F=8,
        ERASE_COMMAND_F=9,
        READ_SERIAL_F=10,
        NUM_COMMANDS_W=11,
        NUM_EMPTY_COMMANDS_W=12,
        OCCUPIED_POS_W=13,
        EMPTY_POS_W=14,
        SAVE_COMMAND_W=15,
        ERASE_COMMAND_W=16,
        READ_SERIAL_W=17,
        READ_ALL=18
    };
    
    /*
     * @brief package that contains data for eusart transmission
     * @param functioncode code of the function
     * @param address address of the data that shall be acessed
     * @param data data of the command
     * @param startbyte byte at the beginning of a data-frame
     * @param endbyte byte at the end of a data-frame
     * @param valid checks if a package is valid
     */
    struct package_t{
        //public
        enum functioncode_t functioncode;
        uint8_t address;
        union packagedata_t data;
        
       
        //private
        uint8_t startbyte;
        uint8_t endbyte;
        bool valid;
    };
    
    /*
     * @brief sets the start and end bytes and validates the package
     * @package package to be reseted
     */
    void init_package(struct package_t* package);
    
    /*
     * @brief verifies if the package is valid
     * @package package to be initialized
     * @return 1 if valid
     */
    bool valid_package(const struct package_t package);
    
    /*
     * @brief reads a package
     * @return the package read in the uart
     */
    struct package_t read_package();
    
    /*
     * @brief writes a package
     * @param package to write in the uart
     */
    void write_package(const struct package_t package);


#ifdef	__cplusplus
}
#endif

#endif	/* EUSARTPACKAGE_H */

