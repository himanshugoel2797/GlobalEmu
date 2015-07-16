MAIN:            
            LDX    #0
            LDA    MSG,X    ; load initial char
    @LP:    JSR    DUMMY    ; chrout
            INX
            LDA    MSG,X
            BNE    @LP
LOOP:       clc
            bcc LOOP
DUMMY:      RTS
MSG:   .ASCIIZ "Hello, world!"
