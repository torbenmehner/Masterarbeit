Thank you for downloading / using this application note.


The project in this application note expects certain resources to be available at 
specific locations in the folder hierachy. Please make sure to install this 
application note at the correct place, normally in the root directory of the
exx32 sdk folder. For example, if Simplicity Studio is installed: 

For windows:
C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\exx32\v5.x.x.x

or

C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v1.0

The resulting path for a given application note will be:

....\v5.x.x.x\an\<application_note_name>

or

....\v1.0\an\<application_note_name>

The surrounding hierarchy must be as follows:

root_folder (e.g. C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\exx32\v5.x.x.x)
      |
      --> an
      |   |
      |   --> <application_note_name>
      |
      --> hardware
      |   |
      |   --> kit
      |
      |
      --> platform
      |   |
      |   --> CMSIS
      |   --> Device
      |   --> emdrv
      |   --> emlib
      |   --> middleware
      |
      |
      --> util
          |
          --> silicon_labs
          --> third_party

         
The other resources can be obtained through Simplicity Studio:
http://www.silabs.com/products/development-tools/software/simplicity-studio
or downloaded from the Silicon Labs webpage: 
http://www.silabs.com/products/development-tools/software
