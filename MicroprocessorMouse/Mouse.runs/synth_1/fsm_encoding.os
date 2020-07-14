
 add_fsm_encoding \
       {Processor.CurrState} \
       { }  \
       {{00000000 00000} {00010000 00001} {00010001 00010} {00010010 00011} {00010011 00100} {00010100 11001} {00100000 00101} {00100001 00110} {00100010 00111} {00110000 01000} {00110001 01001} {00110010 01010} {01000000 01011} {01000001 01100} {01010000 10010} {01010001 10011} {01010010 10100} {01110000 10001} {01110001 10101} {10000000 10110} {10000001 10111} {10000010 11000} {11110000 01101} {11110001 01110} {11110010 01111} {11110011 10000} }

 add_fsm_encoding \
       {MouseTransmitter.Curr_State} \
       { }  \
       {{0000 0000} {0001 0001} {0010 0010} {0011 0011} {0100 0100} {0101 0101} {0110 0110} {0111 0111} {1000 1000} {1001 1001} }

 add_fsm_encoding \
       {MouseReceiver.Curr_State} \
       { }  \
       {{000 000} {001 001} {010 010} {011 011} {100 100} }

 add_fsm_encoding \
       {MouseMasterSM.Curr_State} \
       { }  \
       {{0000 0000} {0001 0001} {0010 0010} {0011 0011} {0100 0100} {0101 0101} {0110 0110} {0111 0111} {1000 1000} {1001 1001} {1010 1010} {1011 1011} {1100 1100} }
