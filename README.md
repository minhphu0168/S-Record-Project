# S-Record-Project

Title: S-Record Application
In this project, we will develop an application which manipulates on files in S-Record format.
S-Record is a file format which was invented by the Motorola corporation in mid-1970s.
This format conveys binary information in ASCII text form for hexa-decimal value.
This file format is commonly used for flash memory programming in microcontrollers, EPROMs, 
EEPROMs, etc.
Your application will have following features:
    - Form a sequence of integer values, which is input from keyboard by user, to S-Records then write
      them to a new S-Record file.
      Integer values are input by user are in decimal base and separated by Space character between 
      them. For example: 45 204 190 77 23 53 186
    - Convert 1-1 from a normal binary file to an S-Record file. The binary file contains only data, so 
      the application will build S-Records whose Data field is data got from a portion in binary file.
    - Convert binary data from a normal binary file to S-Records and add them to an existing SRecord file. (This feature is similar to the above feature, but it           doesn’t create new S-Record file, 
      it appends S-Records to an existing file). - Check corruption for an S-Record file.
    - The application must have appropriate menu so that user can use conveniently.
