# sort: Ordena ascendentemente un arreglo de enteros sin signo usando un
# algoritmo ridiculamente ineficiente.

# La funcion sort esta programada en assembler RiscV. El codigo equivalente
# en C esta comentado, mostrando la ubicacion de las variables en los
# registros.  La funcion recorre el arreglo revisando que los elementos
# consecutivos esten ordenados.  Si encuentra 2 elementos consecutivos
# desordenados, los intercambia y reinicia el recorrido del arreglo
# desde el comienzo.  El arreglo esta ordenado cuando se recorre
# completamente sin encontrar elementos consecutivos desordenados.

    .file "sort-rv.s"
    .text
    .globl sort         # Se necesita para que la etiqueta sea conocida en
                        # test-sort.c
    .type sort, @function # typedef unsigned int uint;

sort:                   # void sort(uint nums[], int n) { // registros a0, a1
    addi    sp,sp,-64   #   Apila registro de activacion
    sw      ra, 60(sp)  #   resguarda direccion de retorno
    sw      a0,56(sp)   #   uint *p= nums; // p esta en sp+56
    addi    a1,a1,-1    #   uint *ult= &nums[n-1]; // ult esta en sp+52
    slli    a1,a1,2     #   tamanno del arreglo
    add     a1,a0,a1
    sw      a1,52(sp)
    sw      a0,48(sp)   #   nums esta en direccion sp+48
    mv      t0,a0       #   p esta en registro t0
                        #   while (p<ult) {
    j       .while_cond #     la condicion del while se evalua al final
.while_begin:           #     del ciclo para mayor eficiencia

    sw      t0,56(sp)   # resguardar p en memoria

    # Hasta aca no puede modificar nada

    #################################################
    ### Comienza el codigo que Ud. debe modificar ###
    #################################################

    # no puede alterar los registros s0-s11, si lo hace debe resguardarlos
    # en 0(sp), 4(sp), ... o 44(sp)
    # El valor de p esta temporalmente en el registro t0
    # No puede hacer mas trabajo que la comparacion (no puede usar ret)
    lw      a0,0(t0)    # int rc= strcmp(p[0], p[1]); // registro t1
    lw      a1,4(t0)
	li	    a3,96       # para usar en condición mayor a 'a'
	li	    a2,109      # 'm'
	li	    a6,122      # 'z'
	j	    .L7         # jump to L7
.L3:
	bgtu	a5,a6,.L2   # if(c1>122) jump to L2
	addi	a5,a5,-13   # c1-=13
	andi	a5,a5,0xff  # idk (supongo que esto es para que sea un valor de 8 bytes si o si)
.L2:
	bleu	a4,a3,.L4   # if(c2<=96) jump to L4
	bgtu	a4,a2,.L5   # if(c2>109) jump to L5
	addi	a4,a4,13    # c2+=13
	andi	a4,a4,0xff  # idk
.L4:
	bne	    a5,a4,.L6   # if(c1!=c2) break;
	addi	a0,a0,1     # s1++;
	addi	a1,a1,1     # s2++;
	beq	    a5,zero,.L6 # while(c1)
.L7:
	lbu	    a5,0(a0)    # c1 = *a0
	lbu	    a4,0(a1)    # c2 = *a1
	bleu	a5,a3,.L2   # if(c1<=96) jump to L2
	bgtu	a5,a2,.L3   # if(c1>109) jump to L3
	addi	a5,a5,13    # c1+=13
	andi	a5,a5,0xff  # idk
	j	    .L2         # jump to L2
.L5:
	bgtu	a4,a6,.L4   # if(c2>122) jump to L4
	addi	a4,a4,-13   # c2-=13
	andi	a4,a4,0xff  # idk
	j	    .L4         # jump to L4
.L6:
    sub	    a0,a5,a4            # a0 = c1-c2
    mv      t1,a0               # almacenar en t1 el resultado anterior
    bge     zero,t1,.decision   # if(t1<=0) jump to decision
    mv      t1,a0               # dejar resultado de la comparacion en t1

    # En el registro t1 debe quedar la conclusion de la comparacion:
    # si t1<=0 p[0] y p[1] estan en orden y no se intercambiaran.

    #################################################
    ### Fin del codigo que Ud. debe modificar     ###
    #################################################

    # Desde aca no puede modificar nada
    # Si t1>0 se intercambian p[0] y p[1] y se asigna p= noms para revisar
    # nuevamente que los elementos esten ordenados desde el comienzo del arreglo

.decision:              #     if (0>=rc) {
    lw      t0,56(sp)   #       p esta en registro t0
    blt     zero,t1,.else
    addi    t0,t0,4     #       p++; // avanzar en arreglo de enteros
    j       .while_cond #     }

.else:                  #     else { // intercambar p[0] y p[1], y reiniciar
    lw      a0,0(t0)    #       int aux= p[0]; // a0
    lw      a1,4(t0)    #       int aux2= p[1];
    sw      a0,4(t0)    #       p[0]= aux2;
    sw      a1,0(t0)    #       p[1]= aux;
    lw      t0,48(sp)   #       p= noms;
                        #     }

.while_cond:            #     se evalua la condicion del while
    lw      t1,52(sp)   #     ult esta en t1
    bltu    t0,t1,.while_begin #  Condicion del while es p<ult
			#   }
    lw      ra,60(sp)   #   Se restaura direccion de retorno
    addi    sp,sp,64    #   Desapila registro de activacion
    ret			# }