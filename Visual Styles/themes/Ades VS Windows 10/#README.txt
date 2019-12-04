                                                             ADES THEME 

#THIS THEME IS COMPATIBLE ONLY WITH THESE WINDOWS 10 VERSIONS:

- TH2 10586 

- ANNIVERSARY UPDATE 1607

EACH VERSION HAS ITS OWN FOLDER, MAKE SURE YOU INSTALL THE CORRECT VERSION FOR YOUR SYSTEM .
EASY CHECK: Open Notepad > Help > About Notepad. 
INSTALLING THE WRONG VERSION CAN BREAK YOUR SYSTEM (YOU CAN FIX IT WITH SYSTEM RESTORE IF YOU DID A RESTORE POINT BEFORE INSTALLING THE THEME).


#HOW TO APPLY
- You need to have your sistem patched for 3rd party themes 
- Copy the files in the Themes folder in C:\Windows\Resources\Themes


#RECOMMENDED
- Use ONE (OldNewExploer) for removing the Ribbon bar and other stuff. It also add some hacks for make the theme look better.
- MacType - Make fonts look nice :)


#WINDOWS BUG FIX
When windows enters sleep mode it breaks the theme colors, fix:
- Execute regedit.exe
- Go to HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Themes\
- Make a backup of DefaultColors.
- Take owernship of DefaultColors and delete it.




#INSTRUCTIONS FOR PATCH THE SYSTEM FOR ANNIVERSARY UPDATE

Install UxStyle http://uxstyle.com/

:)



#INSTRUCTIONS FOR PATCH THE SYSTEM FOR TH2 10586

Thanks to cleodesktop for this
http://www.cleodesktop.com/2015/11/install-uxthemepatcher-for-windows-10.html
- Create a restore point (Optional)
- Go to the link and download Theme Patcher
- Install "Add_Take_Ownership_to_context_menu.reg" 
- Go to System32 folder and look for the file "themeui.dll"
- Right click > Take Ownership 
- Rename it adding .backup at the end 
- Copy and paste the file themeui.dll provided in the downloaded folder (File Patch x86 for 32bits systems, File Patch x64 for 64bits systems).
- Do the same to uxinit.dll, uxtheme.dll
- Restart the PC 





