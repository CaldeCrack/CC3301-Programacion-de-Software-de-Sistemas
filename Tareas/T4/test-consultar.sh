trap "rm -rf /tmp/dicc.txt" EXIT
ARCH=$(arch)
CONSULTAR=$1
chmod +x prof.ref-$ARCH

clean() {
  rm -rf /tmp/dicc.txt
}

test() {
  echo "Ejecutando: $CONSULTAR $*"
  ( $CONSULTAR $* > raw-std.txt ) >& err.txt
  RC=$?
  cat raw-std.txt | xargs > std.txt
  # ( ./prof.ref-$ARCH "$1" "$2" > raw-std-ref.txt ) >& err-ref.txt
  ( ./prof.ref-$ARCH $* > raw-std-ref.txt ) >& err-ref.txt
  REFRC=$?
  cat raw-std-ref.txt | xargs > std-ref.txt

  cmp err.txt err-ref.txt
  if [ $? -ne 0 ]
  then
    echo "*** Salida estandar de errores incorrecta ***"
    echo "Su solucion entrega en la salida estandar de errores:"
    echo "============================================================"
    cat err.txt
    echo "============================================================"
    echo "Debio ser:"
    echo "============================================================"
    cat err-ref.txt
    echo "============================================================"
    echo "Si la salida parece ser igual, instale xxdiff con:"
    echo "    sudo apt-get install xxdiff"
    echo "y luego compare los caracteres invisibles con:"
    echo "xxdiff err.txt err-ref.txt"
#   clean
    exit 1
  fi
  cat err.txt

  cmp std.txt std-ref.txt
  if [ $? -ne 0 ]
  then
    echo "*** Salida estandar incorrecta ***"
    echo "Su solucion entrega en la salida estandar:"
    echo "============================================================"
    cat std.txt
    echo "============================================================"
    echo "Debio ser:"
    echo "============================================================"
    cat std-ref.txt
    echo "============================================================"
    echo "Si la salida parece ser igual, instale xxdiff con:"
    echo "    sudo apt-get install xxdiff"
    echo "y luego compare los caracteres invisibles con:"
    echo "xxdiff std.txt std-ref.txt"
#   clean
    exit 1
  fi
  cat raw-std.txt

  if [ "$RC" == 0 ]
  then
    if [ "$REFRC" != 0 ]
    then
      echo "El codigo de retorno es incorrectamente 0.  Debio ser $REFRC"
#     clean
      exit 1
    fi
  fi
  if [ "$RC" != 0 ]
  then
    if [ "$REFRC" == 0 ]
    then
      echo "El codigo de retorno es incorrectamente $RC.  Debio ser 0"
#     clean
      exit 1
    fi
  fi
  if [ "$RC" != 0 ]
  then
    echo "Bien.  Se diagnostico correctamente el error."
  fi
}

echo "-----------------------------------------------------------"
echo "Test de la llaves existentes de dicc.txt"
test dicc.txt embarcacion
test dicc.txt casa
test dicc.txt lluvia
test dicc.txt alimento
test dicc.txt celular
test dicc.txt canario
test dicc.txt palacio
test dicc.txt bolsillo
test dicc.txt correr
test dicc.txt nadar
test dicc.txt posada
test dicc.txt taladro
test dicc.txt perro
test dicc.txt techo

echo "-----------------------------------------------------------"
echo "Test de una llave inexistente"
test dicc.txt gato
echo "-----------------------------------------------------------"
echo "Test con un diccionario inexistente"
test nodicc.txt bolsillo
echo "-----------------------------------------------------------"
echo "Test con diccionario sin permiso de lectura"
cp dicc.txt /tmp/
chmod -r /tmp/dicc.txt
test /tmp/dicc.txt posada

echo "-----------------------------------------------------------"
echo "Test de uso incorrecto de parametros"
test dicc.txt bolsillo bolsa
test bolsillo

echo "-----------------------------------------------------------"
echo "Test de un diccionario vacio"
test vacio.txt perro

echo "-----------------------------------------------------------"
echo "Test de un diccionario con lineas de tamaño variable"
test dicc-bad.txt perro
test dicc-bad2.txt taladro

echo "-----------------------------------------------------------"
echo "Test de un diccionario con una linea sin :"
test dicc-bad3.txt celular

echo "-----------------------------------------------------------"
echo "Test de un diccionario de tamano distinto"
test dicc2.txt celular
test dicc2.txt taladro
test dicc2.txt pedro

echo "-----------------------------------------------------------"
echo "Test de busqueda en un diccionario completamente lleno"
test dicc3.txt celular
test dicc3.txt posada
test dicc3.txt gato

echo
echo "Felicitaciones: aprobo todos los tests"
