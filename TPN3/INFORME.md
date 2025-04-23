# Trabajo Práctico N°3
# Performance de redes y ruteo interno dinámico.

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
24/04/25  

---

### Información de los autores
 
- **Información de contacto**: _elly.indra.esparza@mi.unc.edu.ar_,  _federica.mayorga@mi.unc.edu.ar_,  _ignaciodelamer@mi.unc.edu.ar_,  _ignacio.rivarola@mi.unc.edu.ar_  

---

## Resumen
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.  

**Palabras clave**: _Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua._.

---

## Introducción
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.

---

# Metodología

## Consignas

1)  
Open Shortest Path First (**OSPF**) es un protocolo de enrutamiento dinámico de tipo Interior Gateway Protocol (**IGP**), diseñado específicamente para redes **IP**. Desarrollado por el grupo de trabajo **OSPF** de la **IETF**, su versión más conocida y utilizada es la versión 2 (definida en el **RFC 2328**), especialmente implementada en entornos Cisco. **OSPF** permite el enrutamiento dentro de un sistema autónomo mediante un enfoque jerárquico basado en áreas y tiene la capacidad de manejar redes complejas, redistribuir rutas desde otros protocolos, autenticar paquetes y optimizar el uso del ancho de banda utilizando **IP** multicast.

Desde el punto de vista teórico, **OSPF** está fuertemente basado en la teoría de grafos. La red se representa como un grafo dirigido y ponderado, donde:
- Cada router es un nodo.
- Cada enlace entre routers es una arista con un peso (costo) asociado.

Para determinar la mejor ruta a cada destino, **OSPF** utiliza el algoritmo de Dijkstra, también conocido como Shortest Path First (**SPF**). Este algoritmo encuentra el camino más corto desde un nodo origen (el router) hacia todos los demás nodos del grafo (la red), tomando como criterio de optimización el menor costo acumulado.


El proceso para encontrar los caminos más cortos con el algoritmo de Dijkstra es el siguiente:
- Se inicializa la distancia del nodo origen en 0 y todas las demás distancias en infinito.
- Se introduce el nodo origen en una estructura eficiente como un min heap (cola de prioridad) con la forma <distancia, nodo>.
- Se extrae el nodo con menor distancia del heap.
- Para cada vecino del nodo actual:
    - Se calcula la nueva distancia: ``dist[v] = dist[u] + peso[u][v]``
    - Si la nueva distancia es menor a la registrada, se actualiza y se reintroduce en el heap.
- Este proceso se repite hasta que el heap esté vacío.
- El resultado es una tabla con la menor distancia desde el origen a cada nodo.

**OSPF** aplica este algoritmo sobre su base de datos de estado de enlace (**LSDB**) para generar la tabla de enrutamiento más eficiente posible.

En cuanto al direccionamiento **IP**, **OSPF** opera sobre redes **IP** divididas en clases, aunque en la práctica moderna se utiliza subneteo sin depender estrictamente de las clases originales:
- **Clase A (rango 0.0.0.0 a 127.255.255.255):** para grandes redes con muchos hosts.
- **Clase B (rango 128.0.0.0 a 191.255.255.255):** para redes medianas.
- **Clase C (rango 192.0.0.0 a 223.255.255.255):** para redes pequeñas, comúnmente usada para enlaces entre routers por su tamaño reducido.

**OSPF** distingue varios tipos de redes físicas y lógicas, lo que permite optimizar su funcionamiento en cada caso:
- Redes broadcast (Ethernet, **FDDI**)
- Redes **NBMA** (non-broadcast multi-access) como Frame Relay o X.25
- Redes punto a punto (**PPP**, **HDLC**)
- Redes punto a multipunto, una mezcla entre **NBMA** y punto a punto, útil en topologías parcialmente malladas

Cada tipo tiene implicancias sobre cómo se detectan los vecinos y cómo se elige el router designado (**DR**).
   
2) HACER Diseñar el esquema de direccionamiento IP de la red, utilizando la segmentación de una red clase A (o B) para las redes de hosts y una red clase C para las conexiones entre routers. Elaborar una tabla de direccionamiento que refleje esta configuración.

3) HACER Configurar cada router para que utilice el protocolo OSPF y verificar la conexión punto a punto entre los dispositivos enlazados. Verificar que las tablas de enrutamiento contienen rutas OSPF.

4) HACER Identificar y analizar los mensajes de OSPF para comprender su funcionamiento y su impacto en la red.

5) HACER Configurar los routers para:
    a) Notificar las redes conectadas directamente al router.
    b) Leer las entradas de la Base de Datos de Estado de Enlace (LSDB) en cada uno de los routers.

6) HACER Definir las áreas de OSPF de la siguiente manera: R1 y R2 están en el área A, el resto de los routers estarán en el área B. Leer las entradas LSDB en cada uno de los routers.
   
7) HACER Verificar el funcionamiento de OSPF:
    a) En el router R2 consultar la información acerca de los vecinos R1 y R3 de OSPF.
    b) En el router R2 consultar la información sobre las operaciones del protocolo de enrutamiento.

8) HACER Configurar el costo de OSPF:
    a) Modificar los costos de las rutas OSPF para observar cómo afecta el funcionamiento del protocolo.
    b) Realizar pruebas entre los clientes de los diferentes routers utilizando traceroute antes y después de la modificación para verificar el funcionamiento.

9) HACER Redistribuir una ruta OSPF predeterminada:
    a) Configurar una dirección de loopback en R1 para simular un enlace a un proveedor de servicios de Internet (ISP).
    b) Configurar una ruta estática predeterminada en el router R1.
    c) Incluir la ruta estática predeterminada en las actualizaciones de OSPF enviadas desde el router R1.

10)  HACER Explicar el impacto en toda la red si se cae una interfaz del router R2 (R2 - R1, R2 - R3, R2 - S1).
    
11) HACER ¿La tabla RIB (Routing Information Base) es lo mismo que la tabla FIB (Forwarding Information Base)? Justificar con capturas del práctico.


## Resultados

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.


## Discusión y conclusiones

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.

## Referencias

[1] TITULO [AUTORES](LINK)
