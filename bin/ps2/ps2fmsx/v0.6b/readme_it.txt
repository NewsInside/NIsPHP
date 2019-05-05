                            PS2fMSX v0.6b (Nov-2009)
                            ------------------------
                            
Introducci�n
------------                            
Este es el port a PS2 de la versi�n 3.5 del emulador fMSX. Este emulador permite
recordar en la PS2 aquellos juegos que hace a�os disfrutamos en los ordenadores
de 8bits MSX.

Esta es una versi�n beta por lo que algunas funcionalidades del emulador han
sido recortadas, en concreto, algunas de las m�s notables y que se implementar�n
poco a poco son:

- Control de m�s par�metros de emulaci�n (memoria, etc...)
- Uso de m�s de un pad (actualmente el mando debe estar conectado en el puerto 
0)
- Personalizaci�n de asignaci�n de botones en el pad
- Soporte de NTSC (actualmente, el emulador soporta PAL)

Uso
---
PS2fMSX incluye soporte para dispositivos USB (siempre que sean compatibles con
usbd.irx y usbhdfsd.irx) y memory cards. Se inicia como cualquier ELF (yo
utilizo el uLauncher) desde la carpeta donde hayas descomprimido el .zip del
emulador.
El contenido de la misma debe ser el siguiente:

ps2fmsx.elf
mainwindow.jpg
fMSX.html
LEEME.TXT
README.TXT
*.ROM (varias ROMS de los sistemas de 8bits)
*.FNT (varias fonts)
                            
Una vez iniciado el emulador, la GUI permite navegar hacia la carpeta en la que
est�n las im�genes (DSK o ROM) que se quieran utilizar en la emulaci�n.
Usando el mando conectado al puerto 0 los controles son:
- D-PAD desplaza entre opciones (ARRIBA y ABAJO, dentro de la misma pantalla, 
IZQUIERDA y DERECHA entre tipos de men�).
- X - Seleccionar
- START - Iniciar emulaci�n
- SELECT y O - Continuar emulaci�n si el emulador lo pausamos para volver al men�
- L1 & R1 - Subir y bajar una pantalla completa en las listas de ROMS/DSKs

Durante la emulaci�n, la asignaci�n de botones del pad es la siguiente:
- R1 (mantener pulsado) muestra el teclado virtual
- R2 (mantener pulsado) equivale a mantener pulsado el CTRL del teclado virtual
- L1 vuelve al men� principal del emulador.
- D-PAD - Joystick de MSX
- X - Bot�n 1 del joystick
- O - Bot�n 2 del joystick
- ^ - Tecla "1" del teclado de MSX
- CUADRADO - Tecla espacio del teclado de MSX
- START - Tecla F1 del teclado de MSX
- SELECT - Volver al men� pero sin perder el estado de emulaci�n (muy �til por
ejemplo para utilizar los savestates).

Savestates (snapshots)
----------------------
La funcionalidad de salvar estado de emulaci�n permite que, una vez en el men� 
de emulaci�n, pero habiendo salido del emulador con SELECT, se pueda realizar el
salvado y cargado de estado de emulaci�n.
Esto permite que, aunque apaguemos el emulador, cuando volvamos a entrar podremos
cargar el estado y continuar donde nos quedamos.
La opci�n de cargar y salvar est� en el men� de opciones y debe tenerse en cuenta
que:
- El m�ximo de savestates que se puede tener simulat�neamente es 8
- Se pueden sobreescribir y borrar los existentes
- Cada combinaci�n de modelo de MSX emulado y ROMs cargadas tiene sus propios 
savestates. Esto significa que, para poder cargar un savestate o salvarlo debemos
poner previamente el emulador en el mismo modo (modelo) que estaba y cargar las mimas
ROMS. Hecho esto, en el men� de salvar y cargar mostrar� correctamente los save states
que correspondan. Esto significa por tanto que, cada .ROM tendr� su conjunto de 8 save
states (sin compartir con el resto de .ROMS) y que los DSKs comparten todos el mismo 
savestate en funci�n del modelo de MSX.
- Cada savestate tiene asociado un fichero .sta y .png. El fichero PNG contiene una
captura de la pantalla en el momento del salvado.

Cr�ditos
--------
PS2fMSX es un port realizado por Francisco Mayoral (direcci�n de correo:
ps2devel arroba wisecoding.es) del c�digo original de fMSX creado por 
Marat Fayzulllin (http://fms.komkon.org/).

El emulador se ha compilado utilizando el PS2SDK y gsKit. Gracias a todos los 
hackers y programadores de estos kits (http://www.ps2dev.org).

Gracias en especial a Ayadsign y El_Patas por todas sus sugerencias y pruebas.

Hilo oficial de ps2fmsx:
http://www.elotrolado.net/hilo_nuevo-port-emulador-msx-para-ps2_1308844

Hilo oficial de ROMs y DSKs de MSXs comprobados:
http://www.elotrolado.net/hilo_lista-de-juegos-msx-comprobados-con-el-emulador-ps2fmsx_1312075

Espero que disfrutes recordando aquellos juegos de 8bits tanto como yo.
