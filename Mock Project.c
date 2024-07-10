#include <stdio.h>
#include <stdlib.h>

void DisplayMenu ()          /*Function to display menu*/
{
    printf("\n\n\n------------------------MENU------------------------");
    printf("\n1. Input a sequence of interger values to S-Records. ");
    printf("\n2. Check corruption for an S-Record file. ");
    printf("\n3. Exit the program. ");
    printf("\n----------------------------------------------------");
}

void DisplayConvertionMenu ()   /*Function to display convertion menu*/
{
    printf("\n----------CONVERTION MENU-----------");
    printf("\n---------------------------------------");
    printf("\n1. Convert to a new S-Record file ");
    printf("\n2. Convert to an existing S-Record file. ");
    printf("\n3. Return to menu. ");
    printf("\n4. Exit the program. ");
    printf("\n---------------------------------------");
}

int ConvertStringtoHexa (char cData[2])           /*Function to convert string in S-Record file to hexa*/
{   
    unsigned char cHexa;

    for (unsigned char i = 0; i < 2; i++)           /*Convert in pairs*/
    {
      if ((cData[i] >= '0') && (cData[i] <= '9'))     
      {
        cData[i] = cData[i] - 48;                     /*Numeric characters - 48 = numbmeric*/
      }
      else if ((cData[i] >= 'A') && (cData[i] <= 'F')) 
      {
        cData[i] = cData[i] - 65 + 10;                /*Alphabetic characters - 65 + 10 = Alphabetic in hexa*/
      }
      else            /*Other case is invalid*/
      {
        return 0;
      }

      if (i == 1)      /*The second hexa will go into this condition*/
      {
        cHexa = (cData[i -1] << 4) | cData[i];
        return cHexa;
      }
    }
}

int ConvertStringtoAddressHexa (char cData[8], unsigned char cByte)           /*Function to convert string in S-Record file to hexa*/
{   
    int cHexa;

    for (unsigned char i = 0; i < (2 * cByte); i++)           
    {
      if ((cData[i] >= '0') && (cData[i] <= '9'))     
      {
        cData[i] = cData[i] - 48;                     /*Numeric characters - 48 = numbmeric*/
      }
      else if ((cData[i] >= 'A') && (cData[i] <= 'F')) 
      {
        cData[i] = cData[i] - 65 + 10;                /*Alphabetic characters - 65 + 10 = Alphabetic in hexa*/
      }
      else            /*Other case is invalid*/
      {
        return 0;
      }
    }

    if (cByte == 2)     /*Convert to 4 hexa digits*/
    {
      cHexa = (cData[0] << 12) | cData[1] << 8 | cData[2] << 4 | cData[3];
      return cHexa;
      
    }
    else if (cByte == 3)   /*Convert to 6 hexa digits*/
    {
      cHexa = (cData[0] << 20) | cData[1] << 16 | cData[2] << 12 | cData[3] << 8 | cData[4] << 4 | cData[5];
      return cHexa;
    }
    else if (cByte == 4)   /*Convert to 8 hexa digits*/
    {
      cHexa = (cData[0] << 28) | cData[1] << 24 | cData[2] << 20 | cData[3] << 16 | cData[4] << 12 | cData[5] << 8 | cData[6] << 4| cData[7];
      return cHexa;
    }
  }

  int GetHexa (FILE *pGet, unsigned char cNumberofbyte)      /*Function to get 1 or 2 byte */
  {
    char cBufferfunct[2];
    short iChecksumfunct = 0;

    if (cNumberofbyte == 1)           /*Get 1 byte*/
    {
      fseek(pGet, -2, SEEK_END);     /*Move to the 2nd from the end to take 1 byte*/ 
      
      cBufferfunct[0] = fgetc(pGet);
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);  /*Call function to convert to hexa and add togerther*/
      
      return iChecksumfunct;
    }
    else if (cNumberofbyte == 2)    /*Get 2 bytes*/
    {
      fseek(pGet, -4, SEEK_END);     /*Move to the 4nd from the end to take 2 byte*/ 
      
      cBufferfunct[0] = fgetc(pGet);    /*Get 1st byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);    /*Call function to convert to hexa and add togerther*/

      cBufferfunct[0] = fgetc(pGet);   /*Get 2nd byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);  /*Call function to convert to hexa and add togerther*/

      return iChecksumfunct;
    }
    else if (cNumberofbyte == 3)    /*Get 3 bytes*/
    {
      fseek(pGet, -6, SEEK_END);     /*Move to the 6nd from the end to take 3 byte*/ 
      
      cBufferfunct[0] = fgetc(pGet);    /*Get 1st byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);    /*Call function to convert to hexa and add togerther*/

      cBufferfunct[0] = fgetc(pGet);   /*Get 2nd byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);  /*Call function to convert to hexa and add togerther*/

      cBufferfunct[0] = fgetc(pGet);   /*Get 3rd byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);  /*Call function to convert to hexa and add togerther*/
      
      return iChecksumfunct;
    }
    else if (cNumberofbyte == 4)    /*Get 4 bytes*/
    {
      fseek(pGet, -8, SEEK_END);     /*Move to the 8nd from the end to take 4 byte*/ 
      
      cBufferfunct[0] = fgetc(pGet);    /*Get 1st byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);    /*Call function to convert to hexa and add togerther*/

      cBufferfunct[0] = fgetc(pGet);   /*Get 2nd byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);  /*Call function to convert to hexa and add togerther*/

      cBufferfunct[0] = fgetc(pGet);   /*Get 3rd byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);  /*Call function to convert to hexa and add togerther*/
      
      cBufferfunct[0] = fgetc(pGet);   /*Get 4th byte*/
      cBufferfunct[1] = fgetc(pGet);

      iChecksumfunct = iChecksumfunct + ConvertStringtoHexa(cBufferfunct);  /*Call function to convert to hexa and add togerther*/

      return iChecksumfunct;
    }
  
}
  
int   ConvertToNewFile (int* pData, unsigned short iRange )   /*Function to convert to a new S-Record file*/
{
    char cBuffer[2];
    short iChecksum = 0;
    char count = 0;
    unsigned char cCounts1 = 0;
    unsigned short iCountdata = 0;
    unsigned char cTemp = 0;

    FILE *pConvert = fopen("./MockProject.srec","w+");

    if (pConvert == NULL)          /*Check address of pConvert*/
    {
      printf("\n\n\nCAN NOT OPEN FILE\n\n\n");         /*If error, finish fuction*/
      
      return 0;            
    }

    fputs("S0", pConvert);
    fprintf(pConvert, "%02X%02X%02X%X%X%X%X%X%X%X%X%X%X%X", 14, 0, 0, 'M', 'O', 'C', 'K', 'P', 'R', 'O', 'J', 'E', 'C', 'T');
    
    fseek(pConvert, 2, SEEK_SET);     /*Move to BYTE COUNT position*/ 

    short iEof;

    while (( iEof = fgetc(pConvert)) != EOF)   /* Check end of file*/
    {
      cBuffer[count] = iEof;

      count++;

      if (count == 2)       /*Handle in pairs*/
      {
        iChecksum = iChecksum + ConvertStringtoHexa(cBuffer); /*call the function to calculate checksum*/

        count = 0;   /*Resert count = 0*/
      }
    }

    iChecksum = iChecksum & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
    iChecksum = ~iChecksum & ~(0xFFFFFFFFFFFFF << 8);   /*Compute the ones' complement, discard the most significant byte and retain the least significant byte*/
    
    fprintf(pConvert, "%02X", iChecksum);

    unsigned short i = 0;

    while ( i < iRange)
    {
      int iChecksums1 = 0;   /*Resert iChecksums1 after writing a S-Record*/

      fputs("\nS1", pConvert);
      
      cCounts1++;   /*Variable to count S1 S-Record*/

      if ((iRange - i) >= 252)   /*If number of data > size of DATA*/
      {
        fputs("FF", pConvert);

        iChecksums1 = iChecksums1 + GetHexa (pConvert, 1);
      }
      else        /*If amount of remaining data < size of DATA*/
      {
        fprintf(pConvert, "%02X", (iRange - i + 3));

        iChecksums1 = iChecksums1 + GetHexa (pConvert, 1);
      }

        fprintf(pConvert, "%04X", iCountdata);    /*iCountdata is amount of data writed*/

        iChecksums1 = iChecksums1 + GetHexa (pConvert, 2); /*Adress have 2 bytes*/

        for (i; i < iRange; i++)
        {
          fprintf(pConvert, "%02X", pData[i]);

          iChecksums1 = iChecksums1 + GetHexa (pConvert, 1);
          
          iCountdata++;   /*Increment after writing data*/

          if (i == ((cCounts1 * 251) + cTemp))    /*cTemp is used to balance the data otherwise there will be 1 missing data*/
          {
            cTemp++;
            i++;

            break;
          }
        }
        
        iChecksums1 = iChecksums1 & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
        iChecksums1 = ~iChecksums1 & ~(0xFFFFFFFFFFFFF << 8);   /*Compute the ones' complement, discard the most significant byte and retain the least significant byte*/
      
        fprintf(pConvert, "%02X", iChecksums1);
      }

      int iChecksums1 = 0;  /*Resert to calculate the record count*/

      fputs("\nS503", pConvert);

      iChecksums1 = iChecksums1 + GetHexa (pConvert, 1);

      fprintf(pConvert, "%04X", cCounts1);

      iChecksums1 = iChecksums1 + GetHexa (pConvert, 2);

      iChecksums1 = iChecksums1 & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
      iChecksums1 = ~iChecksums1 & ~(0xFFFFFFFFFFFFF << 8);   /*Compute the ones' complement, discard the most significant byte and retain the least significant byte*/
      
      fprintf(pConvert, "%02X", iChecksums1);

      fputs("\nS9030000FC", pConvert); /*The last S-Record*/

      fclose (pConvert);  
}

int ConvertToExistingFile (int* pData, unsigned short iRange )
{
    char *pPath = (char*)malloc(100);      

    printf("\n\n\nInput the file path: ");
    gets(pPath);  

    FILE *pConvert = fopen(pPath, "a+");    /*Oper file follow to path*/

    if (pConvert == NULL)          /*Check address of pConvert*/
    {
      printf("\n\n\nCAN NOT OPEN FILE\n\n\n");         /*If error, finish fuction*/
        
      return 0;            
    }

    free(pPath);
    pPath = NULL;

    unsigned short i = 1;

    while(1)
    {
      fseek(pConvert, -i, SEEK_END);  /*Move up from last position*/

      char cTemp = fgetc(pConvert);

      i++;

      if (cTemp == 'S')  /*When reching to 'S', move on if*/
      {
        cTemp = fgetc(pConvert);  /*Get 1 more character*/

        char cBufferAddress[8];
        char cBufferByteCount[2];
        int iAppendAddress = 0;  /*The address value of the new data written to the file*/

        if (cTemp == '1')   /*If after 'S' is '1'*/
        {
          cBufferByteCount[0] = fgetc(pConvert); /*Get 2 more character*/
          cBufferByteCount[1] = fgetc(pConvert);

          iAppendAddress = (iAppendAddress + ConvertStringtoHexa (cBufferByteCount)) - 3 ; 

          for(unsigned j = 0; j < 4; j++)   /*Get 6 more character to convert to hexa*/
          {
            cBufferAddress[j] = fgetc(pConvert);
          } 

          iAppendAddress = iAppendAddress + ConvertStringtoAddressHexa (cBufferAddress, 2);

          fseek(pConvert, 0, SEEK_END);  /*Move to the last position*/

          unsigned char cCounts = 0;
          unsigned short iCountdata = 0;
          unsigned char cTemp = 0;
          unsigned short i = 0;

          while ( i < iRange)
          {
            int iChecksums = 0;   /*Resert iChecksums1 after writing a S-Record*/

            fputs("\nS1", pConvert);
        
            cCounts++;   /*Variable to count S1 S-Record*/

            if ((iRange - i) >= 252)   /*If number of data > size of DATA*/
            {
              fputs("FF", pConvert);

              iChecksums = iChecksums + GetHexa (pConvert, 1);
            }
            else        /*If amount of remaining data < size of DATA*/
            {
              fprintf(pConvert, "%02X", (iRange - i + 3));

              iChecksums = iChecksums + GetHexa (pConvert, 1);
            }

            fprintf(pConvert, "%04X", iAppendAddress + iCountdata);    /*iCountdata is amount of data writed*/

            iChecksums = iChecksums + GetHexa (pConvert, 2); /*Address have 2 bytes*/

            for (i; i < iRange; i++)
            {
              fprintf(pConvert, "%02X", pData[i]);

              iChecksums = iChecksums + GetHexa (pConvert, 1);
          
              iCountdata++;   /*Increment after writing data*/

              if (i == ((cCounts * 251) + cTemp))    /*cTemp is used to balance the data otherwise there will be 1 missing data*/
              {
                cTemp++;
                i++;

                break;
              }
            }
        
            iChecksums = iChecksums & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
            iChecksums = ~iChecksums & ~(0xFFFFFFFFFFFFF << 8);   /*Compute the ones' complement, discard the most significant byte and retain the least significant byte*/
      
            fprintf(pConvert, "%02X", iChecksums);
          }

          int iChecksums = 0;  /*Resert to calculate the record count*/

          fputs("\nS503", pConvert);

          iChecksums = iChecksums + GetHexa (pConvert, 1);

          fprintf(pConvert, "%04X", cCounts);

          iChecksums = iChecksums + GetHexa (pConvert, 2);

          iChecksums = iChecksums & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
          iChecksums = ~iChecksums & ~(0xFFFFFFFFFFFFF << 8);   /*Compute the ones' complement, discard the most significant byte and retain the least significant byte*/
      
          fprintf(pConvert, "%02X", iChecksums);

          fputs("\nS9030000FC", pConvert); /*The last S-Record*/

          fclose(pConvert);

          break;
        }
        else if (cTemp == '2')  /*If after 'S' is '1'*/
        {
          cBufferByteCount[0] = fgetc(pConvert);  /*Get 2 more character*/
          cBufferByteCount[1] = fgetc(pConvert);

          iAppendAddress = (iAppendAddress + ConvertStringtoHexa (cBufferByteCount) - 4 );

          for(unsigned j = 0; j < 6; j++)     /*Get 6 more character to convert to hexa*/
          {
            cBufferAddress[j] = fgetc(pConvert);
          } 

          iAppendAddress = iAppendAddress + ConvertStringtoAddressHexa (cBufferAddress, 3);

          fseek(pConvert, 0, SEEK_END);     /*Move to the last position*/

          unsigned char cCounts = 0;
          unsigned short iCountdata = 0;
          unsigned char cTemp = 0;
          unsigned short i = 0;

          while ( i < iRange)
          {
            int iChecksums = 0;   /*Resert iChecksums1 after writing a S-Record*/

            fputs("\nS2", pConvert);
        
            cCounts++;   /*Variable to count S2 S-Record*/

            if ((iRange - i) >= 251)   /*If number of data > size of DATA*/
            {
              fputs("FF", pConvert);

              iChecksums = iChecksums + GetHexa (pConvert, 1);
            }
            else        /*If amount of remaining data < size of DATA*/
            {
              fprintf(pConvert, "%02X", (iRange - i + 4));

              iChecksums = iChecksums + GetHexa (pConvert, 1);
            }

            fprintf(pConvert, "%06X", iAppendAddress + iCountdata);    /*iCountdata is amount of data writed*/

            iChecksums = iChecksums + GetHexa (pConvert, 3); /*Address have 3 bytes*/

            for (i; i < iRange; i++)
            {
              fprintf(pConvert, "%02X", pData[i]);

              iChecksums = iChecksums + GetHexa (pConvert, 1);
          
              iCountdata++;   /*Increment after writing data*/

              if (i == ((cCounts * 250) + cTemp))    /*cTemp is used to balance the data otherwise there will be 1 missing data*/
              {
                cTemp++;
                i++;

                break;
              }
            }
        
            iChecksums = iChecksums & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
            iChecksums = ~iChecksums & ~(0xFFFFFFFFFFFFF << 8);   /*Compute the ones' complement, discard the most significant byte and retain the least significant byte*/
      
            fprintf(pConvert, "%02X", iChecksums);
          }

          int iChecksums1 = 0;  /*Resert to calculate the record count*/

          fputs("\nS604", pConvert);

          iChecksums1 = iChecksums1 + GetHexa (pConvert, 1);

          fprintf(pConvert, "%06X", cCounts);

          iChecksums1 = iChecksums1 + GetHexa (pConvert, 3);

          iChecksums1 = iChecksums1 & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
          iChecksums1 = ~iChecksums1 & ~(0xFFFFFFFFFFFFF << 8);   /*Compute the ones' complement, discard the most significant byte and retain the least significant byte*/
      
          fprintf(pConvert, "%02X", iChecksums1);

          fputs("\nS804000000FB", pConvert); /*The last S-Record*/

          fclose(pConvert);
                
          break;
        }
        else if (cTemp == '3')      /*If after 'S' is '1'*/
        {
          cBufferByteCount[0] = fgetc(pConvert);  /*Get 2 more character*/
          cBufferByteCount[1] = fgetc(pConvert);

          iAppendAddress = (iAppendAddress + ConvertStringtoHexa (cBufferByteCount) - 5 );

          for(unsigned j = 0; j < 8; j++)    /*Get 8 more character to convert to hexa*/
          {
            cBufferAddress[j] = fgetc(pConvert);
          } 

          iAppendAddress = iAppendAddress + ConvertStringtoAddressHexa (cBufferAddress, 4);

          fseek(pConvert, 0, SEEK_END);   /*Move to the last position*/
          
          unsigned char cCounts = 0;
          unsigned short iCountdata = 0;
          unsigned char cTemp = 0;
          unsigned short i = 0;

          while ( i < iRange)
          {
            int iChecksums = 0;   /*Resert iChecksums1 after writing a S-Record*/

            fputs("\nS3", pConvert);
        
            cCounts++;   

            if ((iRange - i) >= 250)   /*If number of data > size of DATA*/
            {
              fputs("FF", pConvert);

              iChecksums = iChecksums + GetHexa (pConvert, 1);
            }
            else        /*If amount of remaining data < size of DATA*/
            {
              fprintf(pConvert, "%02X", (iRange - i + 5));

              iChecksums = iChecksums + GetHexa (pConvert, 1);
            }

            fprintf(pConvert, "%08X", iAppendAddress + iCountdata);    /*iCountdata is amount of data writed*/

            iChecksums = iChecksums + GetHexa (pConvert,4); /*Address have 4 bytes*/

            for (i; i < iRange; i++)
            {
              fprintf(pConvert, "%02X", pData[i]);

              iChecksums = iChecksums + GetHexa (pConvert, 1);
          
              iCountdata++;   /*Increment after writing data*/

              if (i == ((cCounts * 249) + cTemp))    /*cTemp is used to balance the data otherwise there will be 1 missing data*/
              {
                cTemp++;
                i++;

                break;
              }
            }
        
            iChecksums = iChecksums & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
            iChecksums = ~iChecksums & ~(0xFFFFFFFFFFFFF << 8);   /*Compute the ones' complement, discard the most significant byte and retain the least significant byte*/
      
            fprintf(pConvert, "%02X", iChecksums);
          }

          fputs("\nS70500000000FA", pConvert); /*The last S-Record*/

          fclose(pConvert);
                
          break;
        }
        else
        {
          continue;
        }
      }
    }

    printf("\n\n\n----------------------------------------------------------");
    printf("\n----------APPENED TO S-RECORD FILE SUCCESSFULLY-----------");
    printf("\n----------------------------------------------------------\n\n\n");
}

int Choose1 (int *pArray, unsigned short iCount)       /*Function to implement option 1*/
{
    printf("\nInput data: ");

    for(unsigned short i = 0; i < iCount; i++)           /*Loop to input data which iCount is entered by the user*/
    {  
        scanf("%d", pArray + i);
    }

    while (1)                
    {
        unsigned short cSelection;

        DisplayConvertionMenu ();           /*Call the function*/
    
        printf("\n\n\nPlease choose an option: ");
        scanf("%d", &cSelection);
        getc(stdin);

        if (cSelection == 1)               /*Convertion option 1 to Convert to a new S-Record file */
        {
          ConvertToNewFile (pArray, iCount); /*Call the function to convert to a new S-Record file*/
    
          printf("\n\n\n----------------------------------------------------------");
          printf("\n----------CREATED NEW S-RECORD FILE SUCCESSFULLY----------");
          printf("\n----------------------------------------------------------\n\n\n");

          return 0;
        }
        else if (cSelection == 2)          /*Convertion option 2 to Convert to an existing S-Record file */
        {
          ConvertToExistingFile (pArray, iCount);

          return 0;
        }
        else if (cSelection == 3)           /*Convertion option 3 to return to menu*/  /*Condition to stop infinity loop*/
        {
            return 0;
        }
        else if (cSelection == 4)           /*Convertion option 4 to exit the program*/ /*Condition to stop infinity loop*/
        {
            exit(0);
        }
        else                                /*Other options are invalid*/
        {
            printf("\n-------------------");
            printf("\n INVALID OPTION");
            printf("\n-------------------");
        }
    }
}

int CheckCorruption (FILE *pCheckFunct)    /*Function to check whether an S record is valid or not*/
{
    char cBuffer[2];
    unsigned char cChecksum;
    unsigned char cSRecord [1000];
    int iSum = 0;
    unsigned short iPosition;
    unsigned short iTemp;
    unsigned char cEof;
   
    while (1)
    {   
        cBuffer[0] = fgetc(pCheckFunct);        /*Check whether the first character is S or not*/
        
        if (cBuffer[0] == 'S')
        {   
            iPosition = ftell(pCheckFunct);
            iTemp = iPosition;
            fseek(pCheckFunct, (iPosition + 1), SEEK_SET);   /*Move to TYPE position*/

            while (1)    
            {
                cBuffer[0] = fgetc(pCheckFunct);
              
                if ((cBuffer[0]) == '\n' || (cBuffer[0]) == EOF)  /*Stop after reaching '\n' or EOF*/
                {   
                    break;
                }
                
                cBuffer[1] = fgetc(pCheckFunct);

                iSum = iSum + ConvertStringtoHexa (cBuffer);    /*Sum together each pair hex digits*/
            }

            if (cBuffer[0] == '\n' || (cBuffer[0]) == EOF)  /*Get into condition after go out loop '\n' or EOF*/
            {   
                if ((cBuffer[0]) == EOF)    /*assign value if EOF*/
                {
                  cEof = 1;
                }
                
                iPosition = ftell(pCheckFunct); /*Move to  the current position*/

                fseek(pCheckFunct, (iPosition - 4), SEEK_SET);  /*Move to the 4th from the current position to take CHECK SUM*/
                    
                cBuffer[0] = fgetc(pCheckFunct);
                cBuffer[1] = fgetc(pCheckFunct);

                cChecksum = ConvertStringtoHexa (cBuffer);  /*Convert string to hex*/
                iSum = iSum - cChecksum;   /*Subtract the CHECK SUM value*/

                iSum = iSum & 0xFF;    /*Discard the most significant byte of the sum and retain the least significant byte */
                iSum = ~iSum & ~(0xFFFFFFFFFFFFF << 8);  

                if (iSum == cChecksum)    /*Compare CHECK SUM with iSUm*/
                {
                    fseek(pCheckFunct, iTemp - 1 , SEEK_SET);   /*Move to the 1st position or after '\n'*/

                    fgets(cSRecord, iPosition, pCheckFunct);

                    printf("%s\n\n", cSRecord);
                    
                    iSum = 0;   /*Resert iSum to sum again*/
                }
                else   /*Not equal*/
                {
                    printf("S-RECORD ERROR\n\n\n");

                    fseek(pCheckFunct, iPosition, SEEK_SET);  /*Move to the current position*/

                    iSum = 0; /*Resert iSum to sum again*/
                }

                if(cEof == 1)
                {
                  return 0;   /*Return when reaching EOF*/
                }

                continue;
            }
        }
        else    /*The first is not 'S'*/
        {
            printf("S-RECORD ERROR\n\n");

            while (1)
            {
                cBuffer[0] = fgetc(pCheckFunct);   

                if ((cBuffer[0] == '\n') || (cBuffer[0] == EOF))  /*Move when reaching '\n' or EOF*/
                {
                  break;
                }
            }
            
            if (cBuffer[0] == '\n')  /*Continue loop*/
            {   
                continue;
            }
            else
            {
                return 0;       
            }
        }
    }
}

int main ()
{
    while (1)
    {
        DisplayMenu ();         /*Call the function*/

        unsigned char cOption;

        printf("\n\n\nPlease choose an option: ");
        scanf("%d", &cOption);
        getc(stdin);
    
        if (cOption == 1)        /*Option 1 to input a sequence of interger values to S-Records */
        {
            unsigned short iQuantity;

            printf("Input the quantity of data (1 <= quantity <= 600): ");
            scanf("%d", &iQuantity);    

            if ((iQuantity < 1) || (iQuantity > 600))    /*Condition to let the user re-enter if the value is invalid*/
            {
                do
                {   
                    printf("\n------------------");
                    printf("\n INVALID QUANTITY");
                    printf("\n------------------");
                    printf("\nInput the quantity of data again(1 <= quantity <= 600): ");
                    scanf("%d", &iQuantity);
                } 
                while ((iQuantity < 1) || (iQuantity > 600));
            }

            int *pMemory = (int*)malloc(sizeof(int) * iQuantity);  /*Dynamically allocate memory with size are iQuantity bytes*/

            Choose1 (pMemory, iQuantity);   /*Call the function*/

            free(pMemory);     /*Free memory*/
            pMemory = NULL;     /*Point to NULL to avoid DANGLING POINTER*/
        }
        else if (cOption == 2)  /*Option 2 to check corruption for an S-Record file */
        {
            char *pPathcheck = (char*)malloc(100);   
          
            printf("\n\n\nInput the file path to check: ");  
            gets(pPathcheck); 

            FILE *pCheck = fopen(pPathcheck, "r");    /*Oper file follow to path*/

            if (pCheck == NULL)          /*Check address of pConvert*/
            {
                printf("\n\n\nCAN NOT OPEN FILE\n\n\n");         /*If error, finish fuction*/
                  
                continue;          
            }

            free(pPathcheck);
            pPathcheck = NULL;

            printf("\n\n\nCHECK CORRUPTION SUCCESSFULLY\n\n\n");

            CheckCorruption (pCheck); 

            fclose(pCheck);
        }
        else if (cOption == 3)  /*Option 3 to exit the program*/
        {
            return 0;
        }
        else                    /*Other options are invalid*/
        { 
            printf("\n----------------");
            printf("\n INVALID OPTION");
            printf("\n----------------");
        }
    }   
}
