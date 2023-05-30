==========================================================
Esta es la documentación para compilar y ejecutar su tarea
==========================================================

Se está ejecutando el comando: less README.txt

***************************
*** Para salir: tecla q ***
***************************

Para avanzar a una nueva página: tecla <page down>
Para retroceder a la página anterior: tecla <page up>
Para avanzar una sola línea: tecla <enter>
Para buscar un texto: tecla / seguido del texto (/...texto...)
         por ejemplo: /ddd

-----------------------------------------------

Instrucciones para la tarea de assembler Risc-V

En la clase auxiliar del viernes 19 de mayo se estudió la solución
de una tarea similar de un semestre pasado.

Programe primero en el archivo sort-c-rot13.c el algoritmo en C que ordena
strings codificados en rot13.  Haga un esfuerzo en llegar a la función
strCmp más pequeña, porque así será menor la cantidad de líneas en
assembler que deberá programar.  Pruebe con:

  make sort-c-rot13.run

Una vez que funcione correctamente, genere el código
en assembler para el programa sort-c-rot13.c con este comando:

  make sort-c-rot13.s

Estudie cuidadosamente el código en assembler de la función strCmp.  Base
su solución en ese código para el ordenamiento en assembler.  Podrá copiar la
mayor parte del código.

Modifique la función sort escrita en assembler en el archivo
sort-rv-rot13.s de modo que ordene de acuerdo a lo solicitado.
Para lograrlo, adapte el código que estudió en sort-c-rot13.s.  Recuerde que
en sort-rv-rot13.s solo puede modificar la parte señalada y además
no puede usar la instrucción ret (o equivalentes) ni llamar a otras funciones.

Pruebe que el ordenamiento en assembler funciona correctamente ingresando
estos comandos en un terminal de Debian:

   make sort-rv-rot13.run   (compila y ejecuta la versión en assembler)

Se exige que las ejecución de make sort-rv-rot13.run
terminen con el mensaje 'Felicitaciones: ...'.  De otra forma
su tarea será rechazada.

-----------------------------------------------

Tips para la depuración

Video con ejemplos de uso de ddd: https://youtu.be/FtHZy7UkTT4
Archivos con los ejemplos:
https://www.u-cursos.cl/ingenieria/2020/2/CC3301/1/novedades/r/demo-ddd.zip

Le serán utiles estos comandos:

   make sort-rv-rot13.ddd   (lanza ddd para depurar sort-rv-rot13.s)

En el momento que aparezca la ventana de ddd, la ejecución ya comenzó
y se detuvo en la función main.  Continúe la ejecución con el botón
cont.  La salida del programa se muestra en la ventana del terminal,
no en la ventana de ddd.  Seleccione el menú View->Machine Code Window
para ver el assembler.  Coloque breakpoints en lugares estratégico con
break .while_begin por ejemplo.

Si falla uno de los tests en la versión en assembler, lea atentamente el
mensaje.  Se le explicará cómo detener la ejecución justo antes de ordenar
el arreglo que fallará.

*** Importante ***

Antes de salir de ddd, asegúrese de terminar adecuadamente el programa
ingresando kill en el panel de comandos de ddd.  De otra forma tendrá
que matar el proceso de la manera que se explica más abajo.

*** Solución de problemas ***

Si el programa no termina porque hay un ciclo infinito, detenga la ejecución
con control-C en el terminal de Debian, no en la ventana de ddd.  No salga de
ddd porque el programa no ha terminado.  Ejecute con stepi para examinar
los registros y así diagnosticar el problema.  El programa todavía esta en el
ciclo infinito.

Es normal que ddd abra una ventana de diálogo para reclamar porque no
encuentra los fuentes de algunas funciones de biblioteca, como exit.
Ignore el problema presionando el botón OK y continúe.

Si al lanzar el depurador aparece la ventana de ddd en blanco o en el terminal
aparece este mensaje:

bind: Address already in use
qemu: could not open gdbserver on 1234

significa que su última ejecución del programa con ddd no terminó
adecuadamente.  Deberá matar el proceso (el programa) de la siguiente manera.
En el terminal de Debian ingrese este comando:

ps aux | grep qemu

Si la salida es:

pss        34660  0.0  0.2 4410944 7976 pts/2    Sl   15:40   0:00 qemu-riscv32 -g 1234 sort-c-rot13
pss        34682  0.0  0.0   6252   636 pts/3    S+   15:46   0:00 grep qemu

el identificador del proceso que no terminó adecuadamente es 34660.  Mate
el proceso con este comando:

kill -9 34660

Ahora podrá lanzar ddd nuevamente.

-----------------------------------------------

Entrega de la tarea

En un terminal ejecute el comando:

  make zip      (crea rot13.zip que contiene sort-c-rot13.c,
                 sort-rv-rot13.s y resultados.txt, con la ejecución
                 de su tarea)

Entregue por U-cursos el archivo rot13.zip

Recuerde descargar de u-cursos lo que entregó, descargar nuevamente los
archivos adjuntos y vuelva a probar la tarea tal cual como la entregó.
Esto es para evitar que Ud. reciba un 1.0 en su tarea porque entregó
los archivos equivocados.  Créame, sucede a menudo por ahorrarse esta
verificacion.  Su tarea debe ordenar correctamente, si no será rechazada.

-----------------------------------------------

Limpieza de archivos

make clean

Hace limpieza borrando todos los archivos que se pueden volver
a reconstruir a partir de los fuentes: *.o binarios etc.

-----------------------------------------------

Acerca del comando make

El comando make sirve para automatizar el proceso de compilación asegurando
recompilar el archivo binario ejecutable cuando cambió uno de los archivos
fuentes de los cuales depende.

A veces es útil usar make con la opción -n para que solo muestre
exactamente qué comandos va a ejecutar, sin ejecutarlos de verdad.
Por ejemplo:

   make -n sort-rv-rot13.ddd

También es útil usar make con la opción -B para forzar la recompilación
de los fuentes a pesar de que no han cambiado desde la última compilación.
Por ejemplo:

   make -B sort-rv-rot13

Recompilará para generar el archivo sort-rv-rot13 desde cero
