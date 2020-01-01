def combo_gen(output_file, max_combo_len, tmp_file="tmp.dat"):
    #The '_' char means no char
    combo_chars = [ \
        'a','b','c','d','e','f','g','h','i','j',
        'k','l','m','n','o','p','q','r','s','t',
        'u','v','w','x','y','z','1','2','3',
        '4','5','6','7','8','9','0','A','B','C',
        'D','E','F','G','H','I','J','K','L','M',
        'N','O','Q','R','S','T','U','V','W','X',
        'Y','Z'
    ]

    print("[-] Generating combos")
    combos = open(output_file, 'w')
    print("[-] Writing combo level 1")
    for ch in combo_chars:
        combos.write(ch+'\n')
    combos.close()

    for i in range(1,max_combo_len):
       tmp = open(tmp_file, 'w')
       combos = open(output_file, 'r')

       for com in combos:
           for ch in combo_chars:
               tmp.write(com.split('\n')[0]+ch+'\n')
       tmp.close()
       combos.close()
       combos = open(output_file, 'a')

       print("[-] Writing combo level {}".format(i+1))
       tmp = open(tmp_file, 'r')
       for t in tmp:
           combos.write(t)
       combos.close()

    print("[-] Finished")
