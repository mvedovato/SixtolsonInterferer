#!/usr/bin/bash
#'<' es 60 o 0x3C
INICIOtRAMA=60;
GRADOS=$1;
CANTdIGITOS=`echo ${#GRADOS}`;
CHECKSUM=0;
#'-' es 45 o 0x2D
VALORsIGNOmENOS='-';
SIGNOmENOS=`echo ${GRADOS:0:1}`;
#echo $INICIOtRAMA | awk '{printf("%c\n",$1)}';
PROCESAR=0;

if [ "$#" -ne 1 ]
then
    	echo "Error en parametros. Ingresar grados (desde -90 a 90)";
else
	if [ $GRADOS -lt -90 ] || [ $GRADOS -gt 90 ]
	then
		echo "Error en Grados. Ingresar grados (desde -90 a 90)";	
	else
		PROCESAR=1;	    
	fi	
fi

if [ $PROCESAR -eq 1 ]
then
	if [ "$SIGNOmENOS" = "$VALORsIGNOmENOS" ]
	then
		case $CANTdIGITOS in
			1)
			
			;;
			
			2)
			PRIMERdIGITO=45;
			SEGUNDOdIGITO=`echo "${GRADOS:1:1}"| awk '{printf("%d\n",$1+48)}'`;
			CHECKSUM=$((INICIOtRAMA+PRIMERdIGITO+SEGUNDOdIGITO));
			echo "Checksum en Decimal - Hexadecimal - Caracter: ";
			echo $CHECKSUM;
			echo $CHECKSUM | awk '{printf("%x\n",$1)}';
			CHK=`echo $CHECKSUM | awk '{printf("%c\n",$1)}'`;
			echo $CHK;
			echo "Trama a enviar";
			TRAMA="<"$GRADOS$CHK">";
			echo $TRAMA;			
			;;
			
			3)
			PRIMERdIGITO=45;
			SEGUNDOdIGITO=`echo "${GRADOS:1:1}"| awk '{printf("%d\n",$1+48)}'`;
			TERCERdIGITO=`echo "${GRADOS:2:1}"| awk '{printf("%d\n",$1+48)}'`;
			CHECKSUM=$((INICIOtRAMA+PRIMERdIGITO+SEGUNDOdIGITO+TERCERdIGITO));
			echo "Checksum en Decimal - Hexadecimal - Caracter: ";
			echo $CHECKSUM;
			echo $CHECKSUM | awk '{printf("%x\n",$1)}';
			CHK=`echo $CHECKSUM | awk '{printf("%c\n",$1)}'`;
			echo $CHK;
			echo "Trama a enviar";
			TRAMA="<"$GRADOS$CHK">";
			echo $TRAMA;			
			;;
			
			*)
			
			;;
			
		esac
			

	else
		
		case $CANTdIGITOS in
			1)
			PRIMERdIGITO=`echo "${GRADOS:0:1}" | awk '{printf("%d\n",$1+48)}'`;
			CHECKSUM=$((INICIOtRAMA+PRIMERdIGITO));
			echo "Checksum en Decimal - Hexadecimal - Caracter: ";
			echo $CHECKSUM;
			echo $CHECKSUM | awk '{printf("%x\n",$1)}';
			CHK=`echo $CHECKSUM | awk '{printf("%c\n",$1)}'`;
			echo $CHK;
			echo "Trama a enviar";
			TRAMA="<"$GRADOS$CHK">";
			echo $TRAMA;
			;;
			
			2)
			PRIMERdIGITO=`echo "${GRADOS:0:1}" | awk '{printf("%d\n",$1+48)}'`;
			SEGUNDOdIGITO=`echo "${GRADOS:1:1}"| awk '{printf("%d\n",$1+48)}'`;
			CHECKSUM=$((INICIOtRAMA+PRIMERdIGITO+SEGUNDOdIGITO));
			echo "Checksum en Decimal - Hexadecimal - Caracter: ";
			echo $CHECKSUM;
			echo $CHECKSUM | awk '{printf("%x\n",$1)}';
			CHK=`echo $CHECKSUM | awk '{printf("%c\n",$1)}'`;
			echo $CHK;
			echo "Trama a enviar";
			TRAMA="<"$GRADOS$CHK">";
			echo $TRAMA;
			;;
			
			*)
			
			;;
		esac
		
	fi
fi


: '

for (( i=0; i<${#GRADOS}; i++ )); do
  echo "${GRADOS:$i:1}";
done

for (( i=0; i<${#CHECKSUM}; i++ )); do
  echo "${CHECKSUM:$i:1}";
  #SUMA=$(($SUMA+${CHECKSUM:$i:1}));
done

echo "Ingresar valor";
read hexNum
echo -n "The decimal value of $hexNum="
echo "obase=10; ibase=16; $hexNum" | bc
'
