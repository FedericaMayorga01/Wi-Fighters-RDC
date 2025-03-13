# Trabajo Práctico N°1 - Parte I - Conguración y Análisis de tráfico IPv4/IPv6

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
27/03/25  

---

### Información de los autores
 
- **Información de contacto**: _elly.indra.esparza@mi.unc.edu.ar_,  _federica.mayorga@mi.unc.edu.ar_,  _ignaciodelamer@mi.unc.edu.ar_,  _ignacio.rivarola@mi.unc.edu.ar_  

---

## Resumen

En esta primera parte del Trabajo Práctico N°1, el objetivo es configurar un esquema de red dual stack, utilizando tanto IPv4 como IPv6, en un entorno simulado o emulado. Se analizará el tráfico de red y el comportamiento de protocolos clave como ARP, NDP e ICMP, además de implementar la asignación dinámica de direcciones mediante DHCP.  

**Palabras clave**: _Redes, IPv4, IPv6, ARP, NDP, ICMP, ping, DHCP, switch, router_

---

## Introducción

El objetivo principal es comprender el funcionamiento de estos protocolos en un entorno controlado, analizando el tráfico de red mediante herramientas especializadas y respondiendo preguntas fundamentales sobre la comunicación entre dispositivos. Para ello, se realizarán pruebas de conectividad con paquetes ICMPv4 e ICMPv6, se capturarán y examinarán los intercambios de información en la red y se evaluará el rol de los distintos dispositivos involucrados. Esta experiencia permitirá afianzar conceptos teóricos y desarrollar habilidades prácticas en el diseño y análisis de redes de computadoras.

---

# Metodología

## Consignas

**1)** HACER Desarrollar un marco teórico resumido, suficiente para fundamentar los procedimientos a realizar.  

**2)** Para la construcción del diagrama de red propuesto, utilizamos **Packet Tracer**, un simulador de redes que permite diseñar y configurar topologías de manera intuitiva. Este software fue elegido debido a su interfaz sencilla, su capacidad para simular el comportamiento de dispositivos de red, incluyendo routers, switches y computadoras, sin necesidad de hardware físico, así como también los conocimientos previos de su uso en otras materias.  

<p align="center">
    <img src="./img/TPN1_diagrama.jpg"><br>
    <em>Figura 1: Diagrama de red propuesto en Packet Tracer.</em>
</p>


**3)** Los simuladores son herramientas diseñadas para reproducir el comportamiento de sistemas reales o abstractos con el propósito de facilitar su comprensión y aprendizaje. Aunque pueden modelar el funcionamiento de un sistema, no necesariamente replican su estructura interna. Por ejemplo, un simulador de tráfico puede representar el movimiento de los vehículos en una ciudad sin reproducir el hardware involucrado.

Por otro lado, los emuladores permiten ejecutar software destinado a una plataforma específica en un entorno diferente, garantizando la compatibilidad entre sistemas. Su función es recrear tanto el software como el hardware del sistema original, imitando aspectos como la arquitectura del procesador, la memoria y otros componentes. Un ejemplo común es el emulador de consolas retro, que posibilita la ejecución de videojuegos antiguos en computadoras modernas. A diferencia de los simuladores, los emuladores buscan replicar con precisión la plataforma original, permitiendo que el software funcione como lo haría en su entorno nativo.

**4)** Para evaluar la conectividad entre los dispositivos en la red configurada, realizamos pruebas de conectividad enviando paquetes ICMPv4 mediante el comando `ping` a las direcciones IP de los distintos hosts.

<p align="center">
    <img src="./img/TPN1_h1pingIPv4.jpg"><br>
    <em>Figura 2: Comando ping desde h1.</em>
</p>

Los resultados obtenidos en la prueba de conectividad con ICMPv4 fueron que se enviaron 4 paquetes, de los cuales 3 fueron recibidos correctamente y 1 se perdió, resultando en una pérdida del 25%. En ambos casos, el tiempo de ida y vuelta de los paquetes recibidos fue 0 ms y el TTL (Time To Live) de las respuestas de los hosts de destino fue 127 (indicando que los dispositivos se encontraban a un solo salto de distancia).

**5)** Para la evaluación de la conectividad en IPv6, realizamos pruebas enviando los paquetes ICMPv6 a cada host de la red, mediante el comando `ping` (y no `ping6`). 

<p align="center">
    <img src="./img/TPN1_h1pingIPv6.jpg"><br>
    <em>Figura 3: Comando ping desde h1.</em>
</p>

Los resultados obtenidos fueron que la conectividad en la red IPv6 se encuentra en óptimas condiciones, sin pérdidas de paquetes y con un tiempo de ida y vuelta mínimo de 0 ms. En las pruebas de IPv6, el TTL en las respuestas es 255, lo que indica que los dispositivos están dentro de la misma red (a diferencia con las pruebas en IPv4).

**6)** Desde el diagrama de red propuesto, iniciamos el tráfico ICMP para analizarlo sobre las dos redes.

<p align="center">
    <img src="./img/TPN1_traficoICMP.jpg"><br>
    <em>Figura 4: Simulación del trafico ICMP.</em>
</p>

  1) HACER ¿Cuáles son las comunicaciones ARP que observan? observan? Explicar y ejemplicar con capturas cómo funciona la traducción de direcciones lógicas a direcciones físicas.

  <p align="center">
      <img src="./img/TPN1_traficoICMPlogicasfisicasInbound.jpg"><br>
      <em>Figura 4: PDU Information Inbound.</em>
  </p>

  <p align="center">
      <img src="./img/TPN1_traficoICMPlogicasfisicasOutbound.jpg"><br>
      <em>Figura 5: PDU Information Outbound.</em>
   </p>

  2) HACER ¿Cuáles son las direcciones IP en los datagramas? Indicar con un ejemplo.

  3) HACER ¿Cómo determina el enrutador la comunicación entre un host y otro?

  4) HACER ¿Para qué usamos el switch? ¿Por qué el switch no tiene asignadas direcciones IP en sus interfaces?

  5) En la tabla ARP de h1 vemos: la dirección IP, la dirección MAC y el tipo de entrada, en este caso, dinámica.

  <p align="center">
      <img src="./img/TPN1_h1tablaARP.jpg"><br>
      <em>Figura 6: Tabla ARP de h1.</em>
  </p>

  Esto indica que el dispositivo h1 aprendió la dirección MAC correspondiente a la IP `192.168.2.10` de manera dinámica a través del protocolo ARP.

  6) En la tabla ARP de h3, vemos los mismo datos que mencionamos anteriormente.

  <p align="center">
      <img src="./img/TPN1_h3tablaARP.jpg"><br>
      <em>Figura 7: Tabla ARP de h3.</em>
  </p>

  7) En la tabla ARP del router vemos las direcciones IP y sus direcciones MAC correspondientes para los dispositivos en la red, asociadas a las interfaces de red del router (GigabitEthernet0/0 y GigabitEthernet0/1). Para esto, utilizamos el comando `show arp`
  
  <p align="center">
      <img src="./img/TPN1_routertablaARP.jpg"><br>
      <em>Figura 8: Tabla ARP del router.</em>
  </p>

  En este caso, podemos ver que las direcciones IP 192.168.1.10 y 192.168.2.10 tienen direcciones MAC asociadas (0007.ECBC.D7D y 00E0.B016.E1E5, respectivamente).

  8) En el entorno de IPv4, donde las direcciones IP tienen una longitud de 32 bits, una dirección de broadcast se define cuando todos los bits correspondientes al host están en 1. Un ejemplo de esto es 255.255.255.255, que representa el broadcast universal. Sin embargo, existe un aspecto clave a considerar: la dirección de broadcast de una red depende de su dirección IP y de la máscara de subred. 
  Por ejemplo, si una red tiene como gateway predeterminado la dirección 192.168.0.0 y usa la máscara de subred 255.255.255.0, entonces su dirección de broadcast será 192.168.0.255. Cuando un dispositivo envía un mensaje a esta dirección, la comunicación se dirige a todos los dispositivos dentro de la misma red. No obstante, los mensajes de broadcast no pueden atravesar de una red a otra a través de un gateway.

  9) En IPv4, la multidifusión o multicast es un método de transmisión que permite enviar información a un grupo específico de receptores configurados para recibirla. En lugar de enviar múltiples copias individuales, el emisor transmite los datos una sola vez a una dirección de multicast, y la red se encarga de distribuirlos eficientemente a todos los destinatarios dentro del grupo.
  Este tipo de tráfico es especialmente útil para la distribución masiva de datos, permitiendo que un único flujo llegue simultáneamente a múltiples dispositivos. Se emplea comúnmente en aplicaciones de transmisión multimedia, como streaming de video y música, así como en videoconferencias y en la distribución de configuraciones o actualizaciones a varios dispositivos dentro de una red local.

**7)** HACER Iniciar tráfico ICMPv3 (IPv6) entre h1 y h3. Analizar el tráfico sobre las dos redes, capturar screenshots y responder las siguientes preguntas:



---

## Resultados

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tempor, mauris sit amet aliquet vestibulum, enim ante consectetur enim, vel sollicitudin odio risus vel libero. Integer eget ipsum sed eros luctus laoreet vel vel leo. Fusce ut dapibus nisl. Aliquam erat volutpat. Donec in elit non justo convallis vestibulum.

---

## Discusión y conclusiones

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tempor, mauris sit amet aliquet vestibulum, enim ante consectetur enim, vel sollicitudin odio risus vel libero. Integer eget ipsum sed eros luctus laoreet vel vel leo. Fusce ut dapibus nisl. Aliquam erat volutpat. Donec in elit non justo convallis vestibulum.

## Referencias

[1] Consultar [Normas APA](https://normas-apa.org/referencias/)

[2] ...

[3] ...