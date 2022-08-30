
if [ "$1" == "" ]; then
	echo "Error, falta la ruta del archivo a comprimir/descomprimir"
	exit 1
else
    mkdir -p salida
    ./compresor.exe "$1"
fi
