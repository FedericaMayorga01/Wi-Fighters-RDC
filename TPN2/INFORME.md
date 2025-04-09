# Trabajo Práctico N°2
# Topologias multi-path y evaluacion de performance en redes

**Nombres**  
_Elly I Esparza;_  
_Federica Mayorga;_  
_Ignacio Delamer;_  
_Ignacio A Rivarola_  
**Wi-Fighters**

**Universidad Nacional de Córdoba - FCEFyN**  
**Redes de Computadoras**  
**Profesores**  
Facundo N Oliva Cuneo  
Santiago M Henn  
**Fecha**
10/04/25  

---

### Información de los autores
 
- **Información de contacto**: _elly.indra.esparza@mi.unc.edu.ar_,  _federica.mayorga@mi.unc.edu.ar_,  _ignaciodelamer@mi.unc.edu.ar_,  _ignacio.rivarola@mi.unc.edu.ar_  

---

## Resumen
El TPN2 propone el diseño e implementación de una topología de red física multi-path entre varios grupos, usando equipamiento de laboratorio (PCs, switches y routers). Las tareas incluyen configuracion IP fija en cada dispositivo, el uso de **iperf3** para realizar pruebas de rendimiento, capturar y analizar tráfico con **Wireshark** y elaborar conclusiones en base a las mediciones recolectadas.  

**Palabras clave**: _Topología, enrutamiento, multi-path, iperf3, wireshark, TCP, UDP, ancho de banda, captura de trafico, performance_.

---

## Introducción
En este trabajo práctico se abordan conceptos fundamentales de enrutamiento y análisis de rendimiento en redes informáticas, aplicando configuraciones tanto estáticas como dinámicas. El enfoque principal está puesto en el diseño y evaluación de topologías de red físicas con multi-path, utilizando herramientas como **iperf3** y **Wireshark** para realizar mediciones y observar el comportamiento del tráfico. Se busca integrar conocimientos teóricos con la práctica en laboratorio, trabajando en conjunto para construir una red compleja y compartida entre grupos.

---

# Metodología

## Consignas

**1)**  
   Para cumplir con esta consigna, se configuraron las siguientes direcciones IP fijas en nuestras computadoras del grupo:
   - **PC1:** _192.168.3.88_
   - **PC2:** _192.168.3.89_  
  
  Se realizaron pruebas de conectividad con el comando `ping` con otros hosts dentro del mismo grupo, como de otros grupos (IP del hosts perteneciente a otro grupo es _192.168.3.100_).

  <p align="center">
    <img src="./img/TPN2_ping_PC1_a_PC2.png"><br>
    <em>Figura 1: ping de PC1 a PC2.</em>
  </p>

  <p align="center">
    <img src="./img/TPN2_ping_PC2_a_PC1.jpg"><br>
    <em>Figura 2: ping de PC2 a PC1.</em>
  </p>

  Se observa conectividad estable, sin perdida de paquetes y con tiempos similares.  

  En ambas PCs del grupo, se repitio el proceso a la IP del host de otro grupo:

  <p align="center">
    <img src="./img/TPN2_ping_PC1_a_Feli.png"><br>
    <em>Figura 3: ping de PC1 a otro host.</em>
  </p>

  <p align="center">
    <img src="./img/TPN2_ping_PC2_a_Feli.jpg"><br>
    <em>Figura 4: ping de PC2 a otro host.</em>
  </p>

  Se logro una respuesta positiva, sin perdida de paquetes. Los tiempos de respuesta fueron un poco más altos en comparacion entre PC1 y PC2, lo cual es esperable por el mayor recorrido dentro de la red.


2) HACER Descargar iperf3: https://iperf.fr y resumir los principales comandos para realizar pruebas configurando:  
    a) Protocolos TCP y UDP  
    b) Número y tamaño de paquetes  
    c) Frecuencia/tiempo  
    d) Ancho de banda  

3) HACER Configurar Wireshark (o algún software de sniffing similar) para filtrar tráfico basándose en las IPs de partida/destino. Capturar tráfico y ejecutar pruebas con un host (pc) como servidor y otro como cliente, con distintas configuraciones de protocolos y configuraciones entre:  
    a) Dos computadoras en un mismo grupo (no olvidar configurar el capturador en loopback)  
    b) Una computadora de un grupo y computadoras de al menos otros 2 (dos) grupos  

Documentar capturas de wireshark y las consolas corriendo iperf.

4) HACER Elaborar conclusiones sobre los siguientes aspectos:
¿Cuál es el ancho de banda promedio de la prueba? ¿Cuánto duró la prueba? ¿Cuál es el tamaño promedio de paquetes? ¿Observas alguna diferencia entre UDP y TCP?¿Observamos relación entre alguno de los parámetros de la prueba y la pérdida de paquetes?

5) HACER Ejecutar una prueba como cliente desde una computadora del grupo hacia un servidor propuesto en clase.
Documentar los resultados y elaborar conclusiones sobre los aspectos del punto 4, además de comparar
con los resultados de las pruebas del punto 3)

## Resultados

## Discusión y conclusiones

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.

## Referencias

[1] TITULO [AUTOR](link)
