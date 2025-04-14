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
17/04/25  

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

1) HACER Elaborar una pequeña introducción teórica al OSPF, clases de redes y algoritmos de shortest path. ¿Cómo se aplica la teoría de grafos (graphs) a las redes, y en particular, a las redes OSPF?
   
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

10) HACER Explicar el impacto en toda la red si se cae una interfaz del router R2 (R2 - R1, R2 - R3, R2 - S1).
    
11) HACER ¿La tabla RIB (Routing Information Base) es lo mismo que la tabla FIB (Forwarding Information Base)? Justificar con capturas del práctico.


## Resultados

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.


## Discusión y conclusiones

Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.

## Referencias

[1] TITULO [AUTORES](LINK)
