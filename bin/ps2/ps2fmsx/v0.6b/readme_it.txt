                            PS2fMSX v0.6b (Nov-2009)
                            ------------------------
                            
Introducción
------------                            
Este es el port a PS2 de la versión 3.5 del emulador fMSX. Este emulador permite
recordar en la PS2 aquellos juegos que hace años disfrutamos en los ordenadores
de 8bits MSX.

Esta es una versión beta por lo que algunas funcionalidades del emulador han
sido recortadas, en concreto, algunas de las más notables y que se implementarán
poco a poco son:

- Control de más parámetros de emulación (memoria, etc...)
- Uso de más de un pad (actualmente el mando debe estar conectado en el puerto 
0)
- Personalización de asignación de botones en el pad
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
estén las imágenes (DSK o ROM) que se quieran utilizar en la emulación.
Usando el mando conectado al puerto 0 los controles son:
- D-PAD desplaza entre opciones (ARRIBA y ABAJO, dentro de la misma pantalla, 
IZQUIERDA y DERECHA entre tipos de menú).
- X - Seleccionar
- START - Iniciar emulación
- SELECT y O - Continuar emulación si el emulador lo pausamos para volver al menú
- L1 & R1 - Subir y bajar una pantalla completa en las listas de ROMS/DSKs

Durante la emulación, la asignación de botones del pad es la siguiente:
- R1 (mantener pulsado) muestra el teclado virtual
- R2 (mantener pulsado) equivale a mantener pulsado el CTRL del teclado virtual
- L1 vuelve al menú principal del emulador.
- D-PAD - Joystick de MSX
- X - Botón 1 del joystick
- O - Botón 2 del joystick
- ^ - Tecla "1" del teclado de MSX
- CUADRADO - Tecla espacio del teclado de MSX
- START - Tecla F1 del teclado de MSX
- SELECT - Volver al menú pero sin perder el estado de emulación (muy útil por
ejemplo para utilizar los savestates).

Savestates (snapshots)
----------------------
La funcionalidad de salvar estado de emulación permite que, una vez en el menú 
de emulación, pero habiendo salido del emulador con SELECT, se pueda realizar el
salvado y cargado de estado de emulación.
Esto permite que, aunque apaguemos el emulador, cuando volvamos a entrar podremos
cargar el estado y continuar donde nos quedamos.
La opción de cargar y salvar está en el menú de opciones y debe tenerse en cuenta
que:
- El máximo de savestates que se puede tener simulatáneamente es 8
- Se pueden sobreescribir y borrar los existentes
- Cada combinación de modelo de MSX emulado y ROMs cargadas tiene sus propios 
savestates. Esto significa que, para poder cargar un savestate o salvarlo debemos
poner previamente el emulador en el mismo modo (modelo) que estaba y cargar las mimas
ROMS. Hecho esto, en el menú de salvar y cargar mostrará correctamente los save states
que correspondan. Esto significa por tanto que, cada .ROM tendrá su conjunto de 8 save
states (sin compartir con el resto de .ROMS) y que los DSKs comparten todos el mismo 
savestate en función del modelo de MSX.
- Cada savestate tiene asociado un fichero .sta y .png. El fichero PNG contiene una
captura de la pantalla en el momento del salvado.

Créditos
--------
PS2fMSX es un port realizado por Francisco Mayoral (dirección de correo:
ps2devel arroba wisecoding.es) del código original de fMSX creado por 
Marat Fayzulllin (http://fms.komkon.org/).

El emulador se ha compilado utilizando el PS2SDK y gsKit. Gracias a todos los 
hackers y programadores de estos kits (http://www.ps2dev.org).

Gracias en especial a Ayadsign y El_Patas por todas sus sugerencias y pruebas.

Hilo oficial de ps2fmsx:
http://www.elotrolado.net/hilo_nuevo-port-emulador-msx-para-ps2_1308844

Hilo oficial de ROMs y DSKs de MSXs comprobados:
http://www.elotrolado.net/hilo_lista-de-juegos-msx-comprobados-con-el-emulador-ps2fmsx_1312075

Espero que disfrutes recordando aquellos juegos de 8bits tanto como yo.
