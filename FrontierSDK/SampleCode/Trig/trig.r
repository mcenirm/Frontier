
/*	$Id$    */

data 'MENU' (128, "Apple") {
	$"0080 0000 0000 0000 0000 FFFF FFFB 0114"            /* .�........����.. */
	$"0B41 626F 7574 2054 7269 67C9 0000 0000"            /* .About Trig�.... */
	$"012D 0000 0000 00"                                  /* .-..... */
};

data 'MENU' (129, "File") {
	$"0081 0000 0000 0000 0000 FFFF FFFF 0446"            /* .�........����.F */
	$"696C 6504 5175 6974 0051 0000 00"                   /* ile.Quit.Q... */
};

data 'DITL' (261, "Requires System 7") {
	$"0002 0000 0000 004E 0014 0062 0050 0402"            /* .......N...b.P.. */
	$"4F4B 0000 0000 000A 0020 002A 0040 A002"            /* OK.....�. .*.@�. */
	$"0000 0000 0000 000A 006E 004C 0176 8839"            /* .......�.n.L.v�9 */
	$"5468 6973 2061 7070 6C69 6361 7469 6F6E"            /* This application */
	$"2072 6571 7569 7265 7320 4D61 6369 6E74"            /*  requires Macint */
	$"6F73 6820 5379 7374 656D 2037 2E30 206F"            /* osh System 7.0 o */
	$"7220 6869 6768 6572 2E00"                           /* r higher.. */
};

data 'DITL' (263, "Requires System 7") {
	$"0002 0000 0000 0060 00FC 0074 0138 0402"            /* .......`.�.t.8.. */
	$"4F4B 0000 0000 000C 003C 004E 0136 8802"            /* OK.......<.N.6�. */
	$"5E30 0000 0000 000C 000C 002C 002C A002"            /* ^0.........,.,�. */
	$"0000"                                               /* .. */
};

data 'DITL' (262, "About Command") {
	$"0002 0000 0000 004E 0014 0062 0050 0402"            /* .......N...b.P.. */
	$"4F4B 0000 0000 000A 0020 002A 0040 A002"            /* OK.....�. .*.@�. */
	$"0001 0000 0000 000A 006E 004C 0176 886F"            /* .......�.n.L.v�o */
	$"5472 6967 2069 7320 6120 7061 636B 6167"            /* Trig is a packag */
	$"6520 6F66 2031 3920 7472 6967 6F6E 6F6D"            /* e of 19 trigonom */
	$"6574 7269 6320 6675 6E63 7469 6F6E 7320"            /* etric functions  */
	$"666F 7220 4672 6F6E 7469 6572 2073 6372"            /* for Frontier scr */
	$"6970 7420 7772 6974 6572 732E 0D0D A920"            /* ipt writers...�  */
	$"3139 3932 2D39 3420 5573 6572 4C61 6E64"            /* 1992-94 UserLand */
	$"2053 6F66 7477 6172 652C 2049 6E63 2E00"            /*  Software, Inc.. */
};

data 'ALRT' (261, "Requires System 7") {
	$"0040 0038 00AC 01A4 0105 5555 0000"                 /* .@.8.�.�..UU.. */
};

data 'ALRT' (263, "Script Error") {
	$"003C 003E 00BC 0182 0107 5555 0000"                 /* .<.>.�.�..UU.. */
};

data 'ALRT' (262, "About Command") {
	$"0056 001E 00CE 01B2 0106 5555 7374"                 /* .V...�.�..UUst */
};

data 'WIND' (128, "main window") {
	$"0053 0043 00AF 01E1 0000 0000 0000 0000"            /* .S.C.�.�........ */
	$"0000 0454 7269 6700 8020"                           /* ...Trig.�  */
};

data 'vers' (2) {
	$"0303 8001 0000 0533 2E30 2E33 2250 6163"            /* ..�....3.0.3"Pac */
	$"6B61 6765 206F 6620 7472 6967 6F6E 6F6D"            /* kage of trigonom */
	$"6574 7269 6320 6675 6E63 7469 6F6E 73"              /* etric functions */
};

data 'vers' (1) {
	$"0400 6002 0000 0534 2E30 6232 3534 2E30"            /* ..`....4.0b254.0 */
	$"6232 2E20 436F 7079 7269 6768 7420 A920"            /* b2. Copyright �  */
	$"3139 3932 2D31 3939 362C 2055 7365 724C"            /* 1992-1996, UserL */
	$"616E 6420 536F 6674 7761 7265 2C20 496E"            /* and Software, In */
	$"632E"                                               /* c. */
};

