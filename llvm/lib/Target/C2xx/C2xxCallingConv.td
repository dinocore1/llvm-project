

def CC_C2xx : CallingConv<[
    // Promote i8 arguments to i16.
    CCIfType<[i8], CCPromoteToType<i16>>,

    CCIfType<[i32], CCAssignToReg<[ACC, XAR4, XAR5]>>,
    CCIfType<[i32], CCAssignToStack<4, 4>>,
    CCIfType<[i16], CCAssignToReg<[AL, AH]>>,
]>;