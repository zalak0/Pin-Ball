# MTRX2700-game-show

- Annabelle Flannery	520637045
- Devagya Budhiraja	520578391
- Michael Delano	530371788
- Shun Ying Wong	520623004
- VarunVarshan Sideshkumar	520534445
- Zahi-Al-Aker	530478294


## User Intructions to Run the Game

To be able to run the STMBall machine, we have an RFID card, once you put in your RFID into the module, there is a button to start the game, to start the game, once the button is pressed a timer for the game is started which is lasted for one minute that counts the score and adds it towards the end of the minute. Once, the first round is completed, we can tap onn and once we click the button again the second round will start. 

## Performance using the STM32

Currently we are using 4 microcontroller using the STM32F303VCT6 Discovery board, they are distributed like the following:

- 2 STM32 for the flipper mechanism working independantly
- 1 STM32 for the RFID, 2 motors for the 
- 1 STM32 for the score and for LDRs, that will be used for serial communication to show the interface

## Breakdown of the modules

## Flipper mechanism for 2 STM32
Flipper mechanism wiring diagram:

![image](https://github.com/Devagya-Budhiraja/MTRX2700-Game-Show/assets/157797069/76ccdea5-1337-4cd2-ac9f-ab629ba7a7b9)

The flipper mechanism is using a stepper motor, H-Bridge, Arcade Button, external source for 12V.

## RFID module and the motors



## RFID and the Motors

The wiring diagrams for the RFIS to the STM32 looks like the following:

