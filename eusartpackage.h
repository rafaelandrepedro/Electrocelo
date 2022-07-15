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
     *\brief union that allows the data to be read in separated bytes or in a 16 bit integer
     */
    union packagedata_t{
        uint16_t data16;
        uint8_t data8[2];
    };
    
    /*
     *\brief function operation modes
     */
    enum functioncode_t{
        READ=0,
        WRITE=1,
        PROGRAMMING_ENABLE=2
    };
    
    /*
     *\brief package that contains data for eusart transmission
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
     *\brief sets the start and end bytes and validates the package
     */
    void init_package(struct package_t* package);
    
    /*
     *\brief verifies if the package is valid
     */
    bool valid_package(const struct package_t package);
    
    /*
     *\brief reads a package
     */
    struct package_t read_package();
    
    /*
     *\brief writes a package
     */
    void write_package(const struct package_t package);


#ifdef	__cplusplus
}
#endif

#endif	/* EUSARTPACKAGE_H */

