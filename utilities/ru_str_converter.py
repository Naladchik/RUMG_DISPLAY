print('Давай, жги:')
inp = input()
out_str = ' = {'
for g in inp:
    ucode = ord(g)
    if ucode >= 1040 and ucode <= 1071:
        ucode = ucode - 896
    elif ucode >= 1088 and ucode <= 1103:
        ucode = ucode - 960
    elif ucode >= 1072 and ucode <= 1087:
        ucode = ucode - 896
    elif ucode == 1025:
        ucode = 149
    elif ucode == 1105:
        ucode = 181
    elif ucode >= 32 and ucode <= 126:
        pass #do not change ucode
    else:
        ucode = 63
    out_str = out_str + str(ucode) + ', '

out_str = out_str[:-2]
out_str = out_str + ' ,0}; //' + inp + ' (autogenerated by ru_str_converter.py script)'
print(out_str)
