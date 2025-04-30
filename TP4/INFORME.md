# Trabajo Práctico N°4
# Ruteo externo dinámico y sistemas autónomos.

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
08/05/25  

---

### Información de los autores
 
- **Información de contacto**: _elly.indra.esparza@mi.unc.edu.ar_,  _federica.mayorga@mi.unc.edu.ar_,  _ignaciodelamer@mi.unc.edu.ar_,  _ignacio.rivarola@mi.unc.edu.ar_  

---

## Resumen  
El objetivo de este trabajo práctico es abordar el estudio del ruteo externo dinámico a través del protocolo **BGP** (Border Gateway Protocol) y su implementación en el contexto de Sistemas Autónomos (**AS**, Autonomous Systems). 

En una primera instancia, se realiza una investigación teórica sobre los conceptos fundamentales, como la definición de **AS**, **ASN**, funcionamiento y tipos de **BGP**, conexiones reales y casos históricos de fallos. 

En la segunda parte, se lleva a cabo una simulación práctica de una red que implementa **BGP**, incorporando **IPv6**, redistribución con **OSPF** y análisis de conectividad y comportamiento ante fallos. Este enfoque integral permite comprender tanto los fundamentos como la aplicación real del **BGP** en entornos de red complejos.

**Palabras clave**: _Border Gateway Protocol (BGP), Autonomous System (AS), ASN, Enrutamiento dinámico, IPv6, OSPF, Simulación de red, Redistribución de rutas, Packet Tracer_.

---

## Parte I - Integración de conceptos, actividades online e investigación  
## Introducción  
El primer apartado del trabajo lleva a comprender los fundamentos teóricos del ruteo entre sistemas autónomos mediante el protocolo **BGP**. Se abordan los conceptos esenciales como qué es un **AS**, cómo se identifican mediante números **ASN**, el funcionamiento del **BGP**, los tipos de mensajes que utiliza, y la diferencia entre **eBGP** e **iBGP**. Además, se analiza la infraestructura real de los **AS** a los que pertenecen distintas conexiones de red y se investiga un caso relevante de fallo en el enrutamiento **BGP**, evaluando su impacto a nivel nacional o internacional.

---

## Consignas

1)  Sobre AS:  
    1) Un _Autonomous System_ (**AS**) es un conjunto grande de redes **IP** interconectadas que operan bajo una única política de enrutamiento y que se identifican de forma unificada hacia el resto de Internet. Es uno de los componentes fundamentales de la arquitectura de Internet, que puede entenderse como una red de redes, donde cada **AS** representa una de esas grandes redes independientes.<br/><br/>
    Cada **AS** tiene asignado un conjunto específico de direcciones **IP**, conocido como su espacio de direcciones **IP**, y administra la entrega de datos dentro de ese espacio. Por fuera de sus límites, se encarga de intercambiar rutas y datos con otros **AS** utilizando protocolos de ruteo como el **BGP**.<br/><br/>
    Generalmente, un AS está operado por una única entidad de gran escala, como un proveedor de servicios de Internet (**ISP**), una universidad, una empresa tecnológica o una agencia gubernamental. En caso de que una red esté conectada solo a un **AS** y comparta su política de ruteo, puede considerarse simplemente una subred dentro de ese **AS**.

    2) Un _Autonomous System Number_ (**ASN**) es un número único que identifica oficialmente a cada **AS** en Internet. Su función principal es permitir que un **AS** sea reconocido y referenciado por otros sistemas cuando intercambian información de ruteo mediante protocolos como **BGP**. Cada **AS** cuenta con un **ASN** que lo distingue dentro del conjunto global de redes interconectadas.<br/><br/>
    Los **ASN** pueden ser de 16 bits, con valores que van desde el 1 al 65534, o de 32 bits, con un rango entre 131072 y 4294967294. Se presentan en el formato AS(número), por ejemplo, AS13335 (es el ASN de Cloudflare).<br/><br/>
    El uso de un **ASN** es indispensable cuando un **AS** necesita comunicarse con otros **AS**, es decir, para el enrutamiento externo. En cambio, los routers y dispositivos internos de un **AS** no necesitan necesariamente conocer ese número, ya que operan únicamente dentro del mismo sistema autónomo.

    3) Universidad Nacional de Córdoba (**UNC**):
       - ASN: AS27790
       - Asignado por: **LACNIC** (Registro de Direcciones de Internet para América Latina y el Caribe)
       - Descripcion: permite a la **UNC** gestionar su política de enrutamiento y conectividad con otras redes académicas y proveedores de servicios de Internet. Este número identifica a la universidad como un sistema autónomo dentro de la infraestructura global de Internet.
       <br/>
       
       Google LLC
       - ASN: AS15169
       - Asignado por: **ARIN** (American Registry for Internet Numbers)
       - Descripción: Este **ASN** es utilizado por Google para gestionar su vasta infraestructura global, incluyendo servicios como Google Search, Gmail, YouTube y Google Cloud Platform.​
       <br/>

       **ARSAT** – Empresa Argentina de Soluciones Satelitales S.A.
       - ASN: AS52361
       - Asignado por: **LACNIC** (Registro de Direcciones de Internet para América Latina y el Caribe)
       - Descripción: es una empresa estatal argentina que brinda servicios de telecomunicaciones, incluyendo conectividad satelital, transporte de datos y servicios mayoristas de Internet. Su **ASN** le permite operar su propia política de enrutamiento y conectarse con otros sistemas autónomos, facilitando la gestión de su infraestructura de red a nivel nacional.
    
    4) Para determinar el número de sistema autónomo (**ASN**) correspondiente a la conexión actual, utilicé la herramienta Hurricane Electric BGP Toolkit[1], que proporciona información sobre la dirección **IP** de origen y su asociación con un **ASN**. Observable en la _Figura 1_.<br/><br/>
    De acuerdo con el análisis, la conexión actual utiliza la dirección **IP** pública 181.89.220.125, la cual pertenece al **ASN** AS7303, correspondiente a la empresa Telecom Argentina S.A., uno de los principales proveedores de servicios de Internet en el país.
    <br/><br/>
    Esta organización anuncia más de 8 millones de direcciones **IPv4** (aproximadamente 8.4 millones) y más de 100 prefijos **IPv6**, lo que refleja su amplia infraestructura de red. Su presencia geográfica se concentra principalmente en Argentina, aunque cuenta con conectividad extendida en otros países de Sudamérica. El protocolo de enrutamiento que utiliza para intercambiar rutas con otros sistemas autónomos es **BGP**. Observable en la _Figura 2_.
    <br/><br/>
    En cuanto a los protocolos soportados, admite tanto **IPv4** como **IPv6**, pero no se especifica públicamente el soporte para multicast, lo cual puede indicar que podría estar implementado en algunos contextos específicos, pero no forma parte de sus capacidades anunciadas de forma abierta. Además, mantiene múltiples relaciones de peering con otros **AS**, lo que le permite garantizar una conectividad eficiente y estable a nivel regional e internacional, observable en _Figura 3_.
    <p align="center">
       <img src="./img/TPN4_ASN_Federica.PNG"><br>
       <em>Figura 1: Número de ASN de la conexión.</em>
       <br/>
    </p>
    
    <p align="center">
       <img src="./img/TPN4_BGP_Hurricane.PNG"><br>
       <em>Figura 2: Información relevante de la empresa Telecom.</em>
       <br/>
    </p>
    
    <p align="center">
       <img src="./img/TPN4_PeeringDB.PNG"><br>
       <em>Figura 3: Protocolos soportados.</em>
       <br/>
    </p>


---

## Parte II - Simulaciones y análisis  
## Introducción  
En la segunda parte, se traslada el conocimiento teórico a una implementación práctica mediante la simulación de una red que interconecta múltiples sistemas autónomos utilizando BGP. Se emplea un entorno virtual, para construir la topología de red, verificar conectividad entre hosts, introducir configuraciones para IPv6 y realizar pruebas de redistribución de rutas con OSPF. Buscamos analizar el comportamiento del protocolo ante distintos eventos como caídas de routers o cambios en la topología, reforzando así la comprensión del funcionamiento de BGP en escenarios reales y dinámicos.

---

## Consignas

## Resultados

## Discusión y conclusiones

[1] Hurricane Electric BGP toolkit Home [Hurricane Electric]([LINK](https://bgp.he.net/))