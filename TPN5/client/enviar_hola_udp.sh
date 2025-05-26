# Crea un script llamado enviar_hola.sh
#!/bin/bash

# Conéctate al servidor usando netcat en modo interactivo
{
    sleep 0.5
    for i in {1..100}
    do
        echo "hola"
        sleep 1
    done
} | nc -u 192.168.1.8 8888
