#!/bin/bash
#------------------------------------------------------
# PALETA DE COLORES 
#------------------------------------------------------
#setaf para color de letras/setab: color de fondo
	red=`tput setaf 1`;
	green=`tput setaf 2`;
	blue=`tput setaf 4`;
	bg_blue=`tput setab 4`;
	reset=`tput sgr0`;
	bold=`tput setaf bold`;

#------------------------------------------------------
# TODO: Completar con su path
#------------------------------------------------------
proyectoActual="/home/$USER/Descargas/tpsor/"

#------------------------------------------------------
# FUNCTIONES AUXILIARES
#------------------------------------------------------

imprimir_encabezado () {
    clear;
    #Se le agrega formato a la fecha que muestra
    #Se agrega variable $USER para ver que usuario está ejecutando
    echo -e "`date +"%d-%m-%Y %T" `\t\t\t\t\t USERNAME:$USER";
    echo "";
    #Se agregan colores a encabezado
    echo -e "\t\t ${bg_blue} ${red} ${bold}--------------------------------------\t${reset}";
    echo -e "\t\t ${bold}${bg_blue}${red}$1\t\t${reset}";
    echo -e "\t\t ${bg_blue}${red} ${bold} --------------------------------------\t${reset}";
    echo "";
}

esperar () {
    echo "";
    echo -e "Presione enter para continuar";
    read ENTER ;
}

malaEleccion () {
    echo -e "Selección Inválida ..." ;
}

decidir () {
	echo $1;
	while true; do
		echo "desea ejecutar? (s/n)";
    		read respuesta;
    		case $respuesta in
        		[Nn]* ) break;;
       			[Ss]* ) eval $1
				break;;
        		* ) echo "Por favor tipear S/s ó N/n.";;
    		esac
	done
}

#------------------------------------------------------
# Chequea si esta actualizada
#------------------------------------------------------

necesitaPull(){
  git fetch upstream master > /dev/null 2>&1;
	gitLogOutput=$(git log master..upstream/master --oneline);  #comparamos el ultimo commit de mi master con el ultimo commit del upstream, y lo guardamos en la variable. 
	longDiff=${#gitLogOutput};    #guarda en longDiff la cantidad de 	caracteres de la salida de "gitLogOutput". 


if (($longDiff > 1))  #en caso de que sea mayor a uno quiere decir que hay diferencia entre los commits. 
	then	  		 		
	echo
	echo "Debe realizar un pull antes de empezar a trabajar";
	echo
else
	echo "Su proyecto  esta actualizado";
	fi
}
cd $proyectoActual;
necesitaPull;
esperar;

#------------------------------------------------------
# DISPLAY MENU
#------------------------------------------------------
imprimir_menu () {
       imprimir_encabezado "\t  S  U  P  E  R  -  M  E  N U ";
	
    echo -e "\t\t El proyecto actual es:";
    echo -e "\t\t $proyectoActual";
    
    echo -e "\t\t";
    echo -e "\t\t Opciones:";
    echo "";
    echo -e "\t\t\t a.  Ver estado del proyecto";
    echo -e "\t\t\t b.  Guardar cambios";
    echo -e "\t\t\t c.  Actualizar repo";
    echo -e "\t\t\t d.  Abrir en terminal";        
    echo -e "\t\t\t e.  Abrir en carpeta"; 
    echo -e "\t\t\t f.  Correr ejercio 1: Proceso y fork";			#Agregamos mas opciones al supermenu incluyendo los otros ejercicios.
    echo -e "\t\t\t g.  Correr ejercio 2: Filósofos chinos";
    echo -e "\t\t\t h.  Correr ejercio 2b: Sincronización"; 
    
    echo -e "\t\t\t q.  Salir";
    echo "";
    echo -e "Escriba la opción y presione ENTER";
}


#------------------------------------------------------
# FUNCTIONES del MENU
#------------------------------------------------------
a_funcion () {
    	imprimir_encabezado "\tOpción a.  Ver estado del proyecto";
	echo "---------------------------"        
	echo "Somthing to commit?"
        decidir "cd $proyectoActual; git status";

        echo "---------------------------"        
	echo "Incoming changes (need a pull)?"
	decidir "cd $proyectoActual; necesitaPull"			#llamamos a la funcion necesitaPull.

}

b_funcion () {
       	imprimir_encabezado "\tOpción b.  Guardar cambios";
       	decidir "cd $proyectoActual; git add -A";
       	echo "Ingrese mensaje para el commit:";
       	read mensaje;
       	decidir "cd $proyectoActual; git commit -m \"$mensaje\"";
       	decidir "cd $proyectoActual; git push origin master";		#Le pasamos la direccion de nuestro gitlab
}

c_funcion () {
      	imprimir_encabezado "\tOpción c.  Actualizar repo";
      	decidir "cd $proyectoActual; git pull upstream master";   	 #Le pasamos la direccion de nuestro gitlab
}

d_funcion () {
	imprimir_encabezado "\tOpción f.  Abrir en terminal"; 		#Aca tambien agregamos los demas ejercicios del tp para abrir por terminal

	echo -e "\t\t";
	echo -e "\t\t Opciones:";
	echo "";
	echo -e "\t\t\t a.  supermenu.sh";
	echo -e "\t\t\t b.  do_nothingSinFork.c";
	echo -e "\t\t\t c.  do_nothingFork.c";
	echo -e "\t\t\t d.  filosofosChinos.c";
	echo -e "\t\t\t e.  filosofosChinosDeadlock.c";
	echo -e "\t\t\t f.  sincronizacion.c";
	echo "";
	echo -e "Escriba la opción y presione ENTER";


	read eleccion;
 
	case $eleccion in
		a|A) archivo="supermenu.sh";;
		b|B) archivo="do_nothingSinFork.c";;
		c|C) archivo="do_nothingFork.c";;
		d|D) archivo="filosofosChinos.c";;
		e|E) archivo="filosofosChinosDeadlock.c";;
		f|F) archivo="sincronizacion.c";;
		*) malaEleccion;;
	esac      
	decidir "cd $proyectoActual; nano "$archivo;
}

e_funcion () {
	imprimir_encabezado "\tOpción g.  Abrir en carpeta";			#Lista los archivos que hay en la carpeta del proyecto
	echo "---------------------------";
	echo "Listar archivos de la carpeta?";
	decidir "cd $proyectoActual; ls -a | grep .";
	echo " ";
	echo "---------------------------";
	echo "Abrir carpeta";        											
	echo "---------------------------";
	decidir "gio open $proyectoActual > /dev/null 2>&1";			#Abre la carpeta y descarta el output en el archivo dev/null 
}


f_funcion () {
      	imprimir_encabezado "\tOpción d.  Correr ejercio 1: Proceso y fork";		#Ejecuta el programa Do_nothing con y sin fork.
	rm do_nothingSinFork.txt > /dev/null 2>&1;
	rm do_nothingFork.txt > /dev/null 2>&1;
	echo "Correr version sin implementacion de fork:";			
	decidir "cd $proyectoActual; gcc do_nothingSinFork.c -o do_nothingSinFork.e; (time ./do_nothingSinFork.e >> do_nothingSinFork.txt)";		
	echo "Desea ver de que forma se ejecutó:";
	decidir "cd $proyectoActual; cat do_nothingSinFork.txt";

	echo "Correr version implementando fork:";
	decidir "cd $proyectoActual; gcc do_nothingFork.c -o do_nothingFork.e; (time ./do_nothingFork.e) >> do_nothingFork.txt";
	echo "Desea ver de que forma se ejecutó:";
	decidir "cd $proyectoActual; cat do_nothingFork.txt";

	 	 
}

g_funcion () {
      	imprimir_encabezado "\tOpción e.  Correr ejercio 2: Filósofos chinos";						#Ejecuta el programa filofososChinos
	decidir "cd $proyectoActual; gcc filosofosChinos.c -o filosofosChinos.e -lpthread; ./filosofosChinos.e";   	 
}



h_funcion () {
	imprimir_encabezado "\tOpción h.  Correr ejercio 2b: Sincronización";						#Ejecuta el programa sincronizacion
	decidir "cd $proyectoActual; gcc sincronizacion.c -o sincronizacion.e -lpthread; ./sincronizacion.e";
}


#------------------------------------------------------
# LOGICA PRINCIPAL
#------------------------------------------------------
while  true
do
    # 1. mostrar el menu
    imprimir_menu;
    # 2. leer la opcion del usuario
    read opcion;
    
    case $opcion in
        a|A) a_funcion;;
        b|B) b_funcion;;
        c|C) c_funcion;;
        d|D) d_funcion;;
        e|E) e_funcion;;
        f|F) f_funcion;;
        g|G) g_funcion;;
	h|H) h_funcion;;
        q|Q) break;;
        *) malaEleccion;;
    esac
    esperar;
done
