#ifndef DEFINES_H
#define DEFINES_H

#define UNIX_DELIM "/"
#define WINDOW_DELIM "\\"

#ifdef windows
#define DELIMITOR  WINDOW_DELIM
#elif unix
#define DELIMITOR  UNIX_DELIM
#endif

#define XKRYPT_REF_SIZE 3
#define XKRYPT_REF_VERSION 0x01
#define XKRYPT_REF_MODEL 0x24

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_ICON_WIDTH 35
#define WINDOW_ICON_HEIGHT 35
#define PROCESS_BAR_WIDTH 500

#define NO_KEY_LOADED "no key loaded!"
#define NO_FILE_LOADED "no file loaded!"

#define STYLE_NORMAL "background-color:rgba(0,0,0,0);"
#define STYLE_BLANK "background-color:rgba(0,0,0,0); color:rgba(0,0,0,0)"
#define STYLE_RED "background-color:rgba(0,0,0,0); color:rgba(255, 175, 50, 1);"

#define TAB_NAME_FILE "File"
#define TAB_NAME_TEXT "Text"

#define MESSAGE_END "</td>"
#define MESSAGE_SUCCESS_START "<td><img src=:/assets/success.png width=50 height=50/></td><td valign=middle>"
#define MESSAGE_ERROR_START "<td><img src=:/assets/error.png width=50 height=50/></td><td valign=middle>"
#define MESSAGE_NOKEY_START "<td><img src=:/assets/error.png width=50 height=50/></td><td valign=middle>-- error: Cannot "
#define MESSAGE_SUCCESS_END MESSAGE_END
#define MESSAGE_ERROR_END MESSAGE_END
#define MESSAGE_NOKEY_END " - No key loaded!<br />Please generate or import key and retry</td>"
#define MESSAGE_FILE_EXISTS_START "<td><img src=:/assets/warning.png width=50 height=50/></td><td valign=middle>"
#define MESSAGE_FILE_EXISTS_END MESSAGE_END
#define MESSAGE_INSERT_FNAME_START "<td><img src=:/assets/file.png width=50 height=50/></td><td valign=middle>"
#define MESSAGE_INSERT_FNAME_END MESSAGE_END
#define MESSAGE_CONFIRM_START "<td><img src=:/assets/warning.png width=50 height=50/></td><td valign=middle>"
#define MESSAGE_CONFIRM_END MESSAGE_END

#define ICON_SUCCESS ":/assets/success.ico"
#define ICON_ERROR ":/assets/error.ico"
#define ICON_WARNING ":/assets/warning.ico"
#define ICON_KEY_MANAGER ":/assets/key.ico"
#define ICON_ENCRYPT_MANAGER ":/assets/encrypt.ico"
#define ICON_DECRYPT_MANAGER ":/assets/decrypt.ico"
#define ICON_QUIT ":/assets/quit.ico"
#define ICON_FILE ":/assets/file.ico"
#define ICON_WINDOW_APP ":/assets/icon.ico"

#define IMG_SELECTED_SUFFIX "_selected.png"
#define IMG_UNSELECTED_SUFFIX ".png"
#define IMG_SUCCESS ":/assets/success.png"
#define IMG_ERROR ":/assets/error.png"
#define IMG_WARNING ":/assets/warning.png"
#define IMG_KEY_MANAGER ":/assets/key.png"
#define IMG_ENCRYPT_MANAGER ":/assets/encrypt.png"
#define IMG_DECRYPT_MANAGER ":/assets/decrypt.png"
#define IMG_KEY_MANAGER_SELECTED ":/assets/key_selected.png"
#define IMG_ENCRYPT_MANAGER_SELECTED ":/assets/encrypt_selected.png"
#define IMG_DECRYPT_MANAGER_SELECTED ":/assets/decrypt_selected.png"
#define IMG_QUIT ":/assets/quit.png"
#define IMG_FILE ":/assets/file.png"
#define IMG_WINDOW_APP ":/assets/icon.png"

#endif // DEFINES_H
